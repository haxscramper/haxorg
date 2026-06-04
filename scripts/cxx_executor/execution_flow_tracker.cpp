#include <csignal>
#include <cerrno>
#include <chrono>
#include <cctype>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <sys/epoll.h>
#include <sys/signalfd.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <unistd.h>

#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/JsonCLIParser.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/JsonUse.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/TraceBaseStructuredLog.hpp>
#include <hstd/stdlib/VariantSerde.hpp>
#include <hstd/stdlib/Vec.hpp>

using namespace hstd;
using namespace hstd::log::record;

struct Conf {
    Vec<int>    pids;
    std::string path;
    bool        emitExisting = true;
    DESC_FIELDS(Conf, (pids, path, emitExisting));
};

struct ProcInfo {
    int pid  = 0;
    int ppid = 0;
    Str cmdline;
    Str cwd;
};

struct ProcSnapshot {
    int ppid = 0;
};

static double now_us() {
    auto tp = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<
               std::chrono::duration<double, std::micro>>(tp)
        .count();
}

static void check_syscall(int rc, Str const& what) {
    if (rc == -1) {
        throw std::runtime_error(what + ": " + std::strerror(errno));
    }
}

static bool is_numeric(Str const& s) {
    if (s.empty()) { return false; }
    for (char c : s) {
        if (c < '0' || c > '9') { return false; }
    }
    return true;
}

static Str trim(Str const& s) {
    int b = 0;
    while (b < s.size()
           && std::isspace(static_cast<unsigned char>(s[b]))) {
        ++b;
    }
    int e = s.size();
    while (e > b && std::isspace(static_cast<unsigned char>(s[e - 1]))) {
        --e;
    }
    return s.substr(b, e - b);
}

static std::optional<ProcSnapshot> try_read_proc_snapshot(int pid) {
    Str           path = "/proc/" + std::to_string(pid) + "/stat";
    std::ifstream in(path);
    if (!in) { return std::nullopt; }

    Str line;
    std::getline(in, line);
    if (line.empty()) { return std::nullopt; }

    auto rparen = line.rfind(')');
    if (rparen == Str::npos || line.size() <= rparen + 2) {
        return std::nullopt;
    }

    std::istringstream tail(line.substr(rparen + 2).toBase());
    char               state = 0;
    int                ppid  = 0;
    if (!(tail >> state >> ppid)) { return std::nullopt; }

    return ProcSnapshot{.ppid = ppid};
}

static std::optional<Str> try_read_cmdline(int pid) {
    Str           path = "/proc/" + std::to_string(pid) + "/cmdline";
    std::ifstream in(path, std::ios::binary);
    if (!in) { return std::nullopt; }

    std::string data(
        (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());

    for (char& c : data) {
        if (c == '\0') { c = ' '; }
    }

    return trim(data);
}

static std::optional<Str> try_read_cwd(int pid) {
    std::error_code ec;
    auto            p = std::filesystem::read_symlink(
        "/proc/" + std::to_string(pid) + "/cwd", ec);
    if (ec) { return std::nullopt; }
    return p.string();
}

static StructuredValue make_scalar(Str const& repr) {
    StructuredValue value;
    value.shortRepr = repr;
    value.data      = StructuredValue::Scalar{};
    return value;
}

static StructuredValue make_proc_value(ProcInfo const& info) {
    StructuredValue         root;
    StructuredValue::Object obj;
    obj.type = "ProcessInfo";

    StructuredValue cmd  = make_scalar(info.cmdline);
    StructuredValue cwd  = make_scalar(info.cwd);
    StructuredValue ppid = make_scalar(std::to_string(info.ppid));

    obj.fields.push_back(
        StructuredValue::Field{
            "cmdline", std::make_shared<StructuredValue>(cmd)});
    obj.fields.push_back(
        StructuredValue::Field{
            "cwd", std::make_shared<StructuredValue>(cwd)});
    obj.fields.push_back(
        StructuredValue::Field{
            "ppid", std::make_shared<StructuredValue>(ppid)});

    root.data = obj;
    return root;
}

template <typename T>
static void emit_event(T const& event) {
    nlohmann::json j = hstd::to_json_eval(event);
    std::cout << j.dump() << '\n';
    std::cout.flush();
}

class ProcTracker {
  public:
    explicit ProcTracker(Conf const& conf)
        : conf(conf), roots(conf.pids.begin(), conf.pids.end()) {
        LOGIC_ASSERTION_CHECK(!conf.path.empty(), "");
        file = std::ofstream{conf.path, std::ios::out | std::ios::trunc};
    }

    void run() {
        setup_fds();
        prime_existing();
        event_loop();
    }

  private:
    std::ofstream file;
    Conf          conf;

    std::unordered_set<int>               roots;
    std::unordered_set<int>               tracked;
    std::unordered_map<int, ProcInfo>     infoByPid;
    std::unordered_map<int, ProcSnapshot> seen;

    int epollFd  = -1;
    int signalFd = -1;
    int timerFd  = -1;

    void setup_fds() {
        sigset_t mask;
        check_syscall(sigemptyset(&mask), "sigemptyset");
        check_syscall(sigaddset(&mask, SIGINT), "sigaddset SIGINT");
        check_syscall(sigaddset(&mask, SIGTERM), "sigaddset SIGTERM");
        check_syscall(
            sigprocmask(SIG_BLOCK, &mask, nullptr), "sigprocmask");

        signalFd = signalfd(-1, &mask, SFD_NONBLOCK | SFD_CLOEXEC);
        check_syscall(signalFd, "signalfd");

        timerFd = timerfd_create(
            CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
        check_syscall(timerFd, "timerfd_create");

        itimerspec ts{};
        ts.it_value.tv_nsec    = 5'000'000;
        ts.it_interval.tv_nsec = 5'000'000;
        check_syscall(
            timerfd_settime(timerFd, 0, &ts, nullptr), "timerfd_settime");

        epollFd = epoll_create1(EPOLL_CLOEXEC);
        check_syscall(epollFd, "epoll_create1");

        epoll_event evTimer{};
        evTimer.events  = EPOLLIN;
        evTimer.data.fd = timerFd;
        check_syscall(
            epoll_ctl(epollFd, EPOLL_CTL_ADD, timerFd, &evTimer),
            "epoll_ctl add timerfd");

        epoll_event evSig{};
        evSig.events  = EPOLLIN;
        evSig.data.fd = signalFd;
        check_syscall(
            epoll_ctl(epollFd, EPOLL_CTL_ADD, signalFd, &evSig),
            "epoll_ctl add signalfd");
    }

    std::unordered_map<int, ProcSnapshot> list_all_proc_snapshots() {
        std::unordered_map<int, ProcSnapshot> result;
        for (auto const& entry :
             std::filesystem::directory_iterator("/proc")) {
            if (!entry.is_directory()) { continue; }
            Str name = entry.path().filename().string();
            if (!is_numeric(name)) { continue; }

            int  pid = std::stoi(name);
            auto s   = try_read_proc_snapshot(pid);
            if (s.has_value()) { result.emplace(pid, *s); }
        }
        return result;
    }

    void try_enrich_info(int pid) {
        auto it = infoByPid.find(pid);
        if (it == infoByPid.end()) { return; }

        if (it->second.cmdline.empty()) {
            auto c = try_read_cmdline(pid);
            if (c.has_value()) { it->second.cmdline = *c; }
        }

        if (it->second.cwd.empty()) {
            auto c = try_read_cwd(pid);
            if (c.has_value()) { it->second.cwd = *c; }
        }
    }

    void prime_existing() {
        auto snap = list_all_proc_snapshots();

        for (int root : roots) {
            if (snap.find(root) != snap.end()) { tracked.insert(root); }
        }

        bool changed = true;
        while (changed) {
            changed = false;
            for (auto const& [pid, s] : snap) {
                if (tracked.find(pid) == tracked.end()
                    && tracked.find(s.ppid) != tracked.end()) {
                    tracked.insert(pid);
                    changed = true;
                }
            }
        }

        for (int pid : tracked) {
            ProcInfo info;
            info.pid       = pid;
            info.ppid      = snap.at(pid).ppid;
            info.cmdline   = "";
            info.cwd       = "";
            infoByPid[pid] = info;

            try_enrich_info(pid);
            if (conf.emitExisting) { emit_start(infoByPid[pid]); }
        }

        seen = std::move(snap);
    }

    void poll_proc_snapshot() {
        auto current = list_all_proc_snapshots();

        std::unordered_set<int> newPids;
        for (auto const& [pid, _] : current) {
            if (seen.find(pid) == seen.end()) { newPids.insert(pid); }
        }

        std::unordered_set<int> toTrack;
        for (int pid : newPids) {
            auto const& s = current.at(pid);
            if (roots.find(pid) != roots.end()
                || tracked.find(s.ppid) != tracked.end()) {
                toTrack.insert(pid);
            }
        }

        bool changed = true;
        while (changed) {
            changed = false;
            for (int pid : newPids) {
                if (toTrack.find(pid) != toTrack.end()) { continue; }
                auto const& s = current.at(pid);
                if (toTrack.find(s.ppid) != toTrack.end()) {
                    toTrack.insert(pid);
                    changed = true;
                }
            }
        }

        for (int pid : toTrack) {
            tracked.insert(pid);

            ProcInfo info;
            info.pid       = pid;
            info.ppid      = current.at(pid).ppid;
            info.cmdline   = "";
            info.cwd       = "";
            infoByPid[pid] = info;

            try_enrich_info(pid);
            emit_start(infoByPid[pid]);
        }

        for (int pid : tracked) {
            if (current.find(pid) != current.end()) {
                try_enrich_info(pid);
            }
        }

        Vec<int> ended;
        for (int pid : tracked) {
            if (current.find(pid) == current.end()) {
                ended.push_back(pid);
            }
        }

        for (int pid : ended) {
            auto it = infoByPid.find(pid);
            if (it != infoByPid.end()) {
                emit_end(it->second);
                infoByPid.erase(it);
            }
            tracked.erase(pid);
        }

        seen = std::move(current);
    }

    void consume_timer() {
        uint64_t expirations = 0;
        ssize_t  rc = read(timerFd, &expirations, sizeof(expirations));
        if (rc == -1 && errno == EAGAIN) { return; }
        check_syscall(static_cast<int>(rc), "read timerfd");
        poll_proc_snapshot();
    }

    void event_loop() {
        epoll_event events[8];
        while (true) {
            int n = epoll_wait(epollFd, events, 8, -1);
            check_syscall(n, "epoll_wait");
            for (int i = 0; i < n; ++i) {
                int fd = events[i].data.fd;
                if (fd == signalFd) {
                    signalfd_siginfo siginfo{};
                    ssize_t rc = read(signalFd, &siginfo, sizeof(siginfo));
                    if (rc == -1 && errno == EAGAIN) { continue; }
                    check_syscall(static_cast<int>(rc), "read signalfd");
                    return;
                } else if (fd == timerFd) {
                    consume_timer();
                }
            }
        }
    }

    TraceEventState make_state(ProcInfo const& info) {
        TraceEventState state;
        state.value = make_proc_value(info);
        return state;
    }

    void emit_start(ProcInfo const& info) {
        AsyncEventStart ev;
        ev.name                             = Str("proc.start");
        ev.cat                              = Vec<Str>{"proc"};
        ev.ts                               = now_us();
        ev.pid                              = info.pid;
        ev.tid                              = info.pid;
        ev.id                               = StrOrInt(info.pid);
        static_cast<TraceEventBase&>(ev).id = StrOrInt(info.pid);

        ev.args.file     = "proc_tracker";
        ev.args.function = "proc_tracker";
        ev.args.line     = 0;
        ev.args.message  = Str("start");
        ev.args.state    = make_state(info);

        emit_event(ev);
    }

    void emit_end(ProcInfo const& info) {
        AsyncEventEnd ev;
        ev.name                             = Str("proc.end");
        ev.cat                              = Vec<Str>{"proc"};
        ev.ts                               = now_us();
        ev.pid                              = info.pid;
        ev.tid                              = info.pid;
        ev.id                               = StrOrInt(info.pid);
        static_cast<TraceEventBase&>(ev).id = StrOrInt(info.pid);

        ev.args.file     = "proc_tracker";
        ev.args.function = "proc_tracker";
        ev.args.line     = 0;
        ev.args.message  = Str("end");
        ev.args.state    = make_state(info);

        emit_event(ev);
    }
};

int main(int argc, char* argv[]) {
    auto        conf = hstd::parse_json_argc<Conf>(argc, argv);
    ProcTracker tracker(conf);
    tracker.run();
    return 0;
}
