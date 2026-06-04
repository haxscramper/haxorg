#include <csignal>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <sys/epoll.h>
#include <sys/inotify.h>
#include <sys/signalfd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/timerfd.h>

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/JsonCLIParser.hpp>
#include <hstd/stdlib/TraceBaseStructuredLog.hpp>
#include <hstd/stdlib/JsonUse.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/VariantSerde.hpp>

using namespace hstd;
using namespace hstd::log::record;

struct Conf {
    Vec<int>    pids;
    std::string path;
    bool        emitExisting = true;
    DESC_FIELDS(Conf, (pids, path, emitExisting));
};

struct ProcInfo {
    int pid;
    int ppid;
    Str cmdline;
    Str cwd;
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

static Str read_cmdline(int pid) {
    Str           path = "/proc/" + std::to_string(pid) + "/cmdline";
    std::ifstream in(path, std::ios::binary);
    if (!in) { throw std::runtime_error("failed to open " + path); }
    std::string data(
        (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());
    for (char& c : data) {
        if (c == '\0') { c = ' '; }
    }
    return trim(data);
}

static int read_ppid(int pid) {
    Str           path = "/proc/" + std::to_string(pid) + "/status";
    std::ifstream in(path);
    if (!in) { throw std::runtime_error("failed to open " + path); }
    Str line;
    while (std::getline(in, line)) {
        if (line.rfind("PPid:", 0) == 0) {
            auto rest = trim(line.substr(5));
            return std::stoi(rest);
        }
    }
    throw std::runtime_error("PPid not found in " + path);
}

static Str read_cwd(int pid) {
    Str path = "/proc/" + std::to_string(pid) + "/cwd";
    return std::filesystem::read_symlink(path.toBase()).string();
}

static ProcInfo read_proc_info(int pid) {
    ProcInfo info;
    info.pid     = pid;
    info.ppid    = read_ppid(pid);
    info.cmdline = read_cmdline(pid);
    info.cwd     = read_cwd(pid);
    return info;
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

    std::unordered_set<int>           roots;
    std::unordered_set<int>           tracked;
    std::unordered_map<int, ProcInfo> infoByPid;

    int epollFd  = -1;
    int signalFd = -1;
    int timerFd  = -1;

    std::unordered_set<int> seenPids;

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
        ts.it_value.tv_nsec    = 50'000'000; // 50ms initial
        ts.it_interval.tv_nsec = 50'000'000; // 50ms periodic
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

    Vec<int> list_all_pids() {
        Vec<int> result;
        for (auto const& entry :
             std::filesystem::directory_iterator("/proc")) {
            if (!entry.is_directory()) { continue; }
            Str name = entry.path().filename().string();
            if (!is_numeric(name)) { continue; }
            result.push_back(std::stoi(name));
        }
        return result;
    }

    void prime_existing() {
        std::unordered_map<int, int> ppidByPid;
        for (int pid : list_all_pids()) {
            ppidByPid[pid] = read_ppid(pid);
        }

        for (int root : roots) {
            if (ppidByPid.find(root) != ppidByPid.end()) {
                tracked.insert(root);
            }
        }

        bool changed = true;
        while (changed) {
            changed = false;
            for (auto const& [pid, ppid] : ppidByPid) {
                if (tracked.find(pid) == tracked.end()
                    && tracked.find(ppid) != tracked.end()) {
                    tracked.insert(pid);
                    changed = true;
                }
            }
        }

        for (int pid : tracked) {
            ProcInfo info  = read_proc_info(pid);
            infoByPid[pid] = info;
            if (conf.emitExisting) { emit_start(info); }
        }

        seenPids.clear();
        for (auto const& [pid, _] : ppidByPid) { seenPids.insert(pid); }
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

    void consume_timer() {
        uint64_t expirations = 0;
        ssize_t  rc = read(timerFd, &expirations, sizeof(expirations));
        if (rc == -1 && errno == EAGAIN) { return; }
        check_syscall(static_cast<int>(rc), "read timerfd");
        poll_proc_snapshot();
    }

    void poll_proc_snapshot() {
        std::unordered_set<int> current;
        for (int pid : list_all_pids()) { current.insert(pid); }

        for (int pid : current) {
            if (seenPids.find(pid) == seenPids.end()) {
                on_proc_create(pid);
            }
        }

        for (int pid : seenPids) {
            if (current.find(pid) == current.end()) {
                on_proc_delete(pid);
            }
        }

        seenPids = std::move(current);
    }

    void on_proc_create(int pid) {
        if (tracked.find(pid) != tracked.end()) { return; }

        ProcInfo info        = read_proc_info(pid);
        bool     shouldTrack = roots.find(pid) != roots.end()
                            || tracked.find(info.ppid) != tracked.end();
        if (!shouldTrack) { return; }

        tracked.insert(pid);
        infoByPid[pid] = info;
        emit_start(info);
    }

    void on_proc_delete(int pid) {
        if (tracked.find(pid) == tracked.end()) { return; }
        auto it = infoByPid.find(pid);
        if (it == infoByPid.end()) {
            throw std::runtime_error(
                "tracked pid missing info: " + std::to_string(pid));
        }
        emit_end(it->second);
        infoByPid.erase(it);
        tracked.erase(pid);
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
