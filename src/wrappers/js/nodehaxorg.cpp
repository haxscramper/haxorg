/* clang-format off */
#include "node_utils.hpp"
#include "node_org_include.hpp"
using namespace org::bind::js;
struct UserTimeBreakdownJs : public Napi::ObjectWrap<UserTimeBreakdownJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "UserTimeBreakdownJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("UserTimeBreakdownJs", func);
    return exports;
  }
  UserTimeBreakdownJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<UserTimeBreakdownJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<hstd::UserTimeBreakdown>();
  }
  UserTimeBreakdownJs(Napi::CallbackInfo const& info, std::shared_ptr<hstd::UserTimeBreakdown> const& ptr) : Napi::ObjectWrap<UserTimeBreakdownJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<hstd::UserTimeBreakdown> _stored;
  hstd::UserTimeBreakdown* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<UserTimeBreakdownJs> {
  using type = hstd::UserTimeBreakdown;
};

template <>
struct org_to_js_type<hstd::UserTimeBreakdown> {
  using type = UserTimeBreakdownJs;
};

struct UserTimeJs : public Napi::ObjectWrap<UserTimeJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "UserTimeJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("UserTimeJs", func);
    return exports;
  }
  UserTimeJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<UserTimeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<hstd::UserTime>();
  }
  UserTimeJs(Napi::CallbackInfo const& info, std::shared_ptr<hstd::UserTime> const& ptr) : Napi::ObjectWrap<UserTimeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<hstd::UserTime> _stored;
  hstd::UserTime* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<UserTimeJs> {
  using type = hstd::UserTime;
};

template <>
struct org_to_js_type<hstd::UserTime> {
  using type = UserTimeJs;
};

struct LineColJs : public Napi::ObjectWrap<LineColJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LineColJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("LineColJs", func);
    return exports;
  }
  LineColJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<LineColJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::parse::LineCol>();
  }
  LineColJs(Napi::CallbackInfo const& info, std::shared_ptr<org::parse::LineCol> const& ptr) : Napi::ObjectWrap<LineColJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::parse::LineCol> _stored;
  org::parse::LineCol* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<LineColJs> {
  using type = org::parse::LineCol;
};

template <>
struct org_to_js_type<org::parse::LineCol> {
  using type = LineColJs;
};

struct OrgJsonJs : public Napi::ObjectWrap<OrgJsonJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgJsonJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OrgJsonJs", func);
    return exports;
  }
  OrgJsonJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<OrgJsonJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::OrgJson>();
  }
  OrgJsonJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::OrgJson> const& ptr) : Napi::ObjectWrap<OrgJsonJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::OrgJson> _stored;
  org::sem::OrgJson* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<OrgJsonJs> {
  using type = org::sem::OrgJson;
};

template <>
struct org_to_js_type<org::sem::OrgJson> {
  using type = OrgJsonJs;
};

struct OperationsTracerJs : public Napi::ObjectWrap<OperationsTracerJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OperationsTracerJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OperationsTracerJs", func);
    return exports;
  }
  OperationsTracerJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<OperationsTracerJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<hstd::OperationsTracer>();
  }
  OperationsTracerJs(Napi::CallbackInfo const& info, std::shared_ptr<hstd::OperationsTracer> const& ptr) : Napi::ObjectWrap<OperationsTracerJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<hstd::OperationsTracer> _stored;
  hstd::OperationsTracer* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<OperationsTracerJs> {
  using type = hstd::OperationsTracer;
};

template <>
struct org_to_js_type<hstd::OperationsTracer> {
  using type = OperationsTracerJs;
};

struct ImmIdJs : public Napi::ObjectWrap<ImmIdJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdJs", func);
    return exports;
  }
  ImmIdJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmId>();
  }
  ImmIdJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmId> const& ptr) : Napi::ObjectWrap<ImmIdJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmId> _stored;
  org::imm::ImmId* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdJs> {
  using type = org::imm::ImmId;
};

template <>
struct org_to_js_type<org::imm::ImmId> {
  using type = ImmIdJs;
};

struct ImmPathStepJs : public Napi::ObjectWrap<ImmPathStepJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPathStepJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPathStepJs", func);
    return exports;
  }
  ImmPathStepJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPathStepJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmPathStep>();
  }
  ImmPathStepJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmPathStep> const& ptr) : Napi::ObjectWrap<ImmPathStepJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmPathStep> _stored;
  org::imm::ImmPathStep* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmPathStepJs> {
  using type = org::imm::ImmPathStep;
};

template <>
struct org_to_js_type<org::imm::ImmPathStep> {
  using type = ImmPathStepJs;
};

struct ImmPathJs : public Napi::ObjectWrap<ImmPathJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPathJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPathJs", func);
    return exports;
  }
  ImmPathJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPathJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmPath>();
  }
  ImmPathJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmPath> const& ptr) : Napi::ObjectWrap<ImmPathJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmPath> _stored;
  org::imm::ImmPath* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmPathJs> {
  using type = org::imm::ImmPath;
};

template <>
struct org_to_js_type<org::imm::ImmPath> {
  using type = ImmPathJs;
};

struct ImmUniqIdJs : public Napi::ObjectWrap<ImmUniqIdJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmUniqIdJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmUniqIdJs", func);
    return exports;
  }
  ImmUniqIdJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmUniqIdJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmUniqId>();
  }
  ImmUniqIdJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmUniqId> const& ptr) : Napi::ObjectWrap<ImmUniqIdJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmUniqId> _stored;
  org::imm::ImmUniqId* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmUniqIdJs> {
  using type = org::imm::ImmUniqId;
};

template <>
struct org_to_js_type<org::imm::ImmUniqId> {
  using type = ImmUniqIdJs;
};

struct ImmNoneValueReadJs : public Napi::ObjectWrap<ImmNoneValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNoneValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNoneValueReadJs", func);
    return exports;
  }
  ImmNoneValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmNoneValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmNoneValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmNoneValueRead> const& ptr) : Napi::ObjectWrap<ImmNoneValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmNoneValueRead> _stored;
  org::imm::ImmNoneValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmNoneValueReadJs> {
  using type = org::imm::ImmNoneValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmNoneValueRead> {
  using type = ImmNoneValueReadJs;
};

struct ImmErrorItemValueReadJs : public Napi::ObjectWrap<ImmErrorItemValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorItemValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorItemValueReadJs", func);
    return exports;
  }
  ImmErrorItemValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmErrorItemValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmErrorItemValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmErrorItemValueRead> const& ptr) : Napi::ObjectWrap<ImmErrorItemValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmErrorItemValueRead> _stored;
  org::imm::ImmErrorItemValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmErrorItemValueReadJs> {
  using type = org::imm::ImmErrorItemValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmErrorItemValueRead> {
  using type = ImmErrorItemValueReadJs;
};

struct ImmErrorGroupValueReadJs : public Napi::ObjectWrap<ImmErrorGroupValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorGroupValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorGroupValueReadJs", func);
    return exports;
  }
  ImmErrorGroupValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmErrorGroupValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmErrorGroupValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmErrorGroupValueRead> const& ptr) : Napi::ObjectWrap<ImmErrorGroupValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmErrorGroupValueRead> _stored;
  org::imm::ImmErrorGroupValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmErrorGroupValueReadJs> {
  using type = org::imm::ImmErrorGroupValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmErrorGroupValueRead> {
  using type = ImmErrorGroupValueReadJs;
};

struct ImmStmtListValueReadJs : public Napi::ObjectWrap<ImmStmtListValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStmtListValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStmtListValueReadJs", func);
    return exports;
  }
  ImmStmtListValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmStmtListValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmStmtListValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmStmtListValueRead> const& ptr) : Napi::ObjectWrap<ImmStmtListValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmStmtListValueRead> _stored;
  org::imm::ImmStmtListValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmStmtListValueReadJs> {
  using type = org::imm::ImmStmtListValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmStmtListValueRead> {
  using type = ImmStmtListValueReadJs;
};

struct ImmEmptyValueReadJs : public Napi::ObjectWrap<ImmEmptyValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEmptyValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEmptyValueReadJs", func);
    return exports;
  }
  ImmEmptyValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmEmptyValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmEmptyValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmEmptyValueRead> const& ptr) : Napi::ObjectWrap<ImmEmptyValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmEmptyValueRead> _stored;
  org::imm::ImmEmptyValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmEmptyValueReadJs> {
  using type = org::imm::ImmEmptyValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmEmptyValueRead> {
  using type = ImmEmptyValueReadJs;
};

struct ImmCmdCaptionValueReadJs : public Napi::ObjectWrap<ImmCmdCaptionValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCaptionValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCaptionValueReadJs", func);
    return exports;
  }
  ImmCmdCaptionValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCaptionValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCaptionValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdCaptionValueRead> const& ptr) : Napi::ObjectWrap<ImmCmdCaptionValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdCaptionValueRead> _stored;
  org::imm::ImmCmdCaptionValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCaptionValueReadJs> {
  using type = org::imm::ImmCmdCaptionValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCmdCaptionValueRead> {
  using type = ImmCmdCaptionValueReadJs;
};

struct ImmCmdColumnsValueReadJs : public Napi::ObjectWrap<ImmCmdColumnsValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdColumnsValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdColumnsValueReadJs", func);
    return exports;
  }
  ImmCmdColumnsValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdColumnsValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdColumnsValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdColumnsValueRead> const& ptr) : Napi::ObjectWrap<ImmCmdColumnsValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdColumnsValueRead> _stored;
  org::imm::ImmCmdColumnsValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdColumnsValueReadJs> {
  using type = org::imm::ImmCmdColumnsValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCmdColumnsValueRead> {
  using type = ImmCmdColumnsValueReadJs;
};

struct ImmCmdNameValueReadJs : public Napi::ObjectWrap<ImmCmdNameValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdNameValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdNameValueReadJs", func);
    return exports;
  }
  ImmCmdNameValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdNameValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdNameValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdNameValueRead> const& ptr) : Napi::ObjectWrap<ImmCmdNameValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdNameValueRead> _stored;
  org::imm::ImmCmdNameValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdNameValueReadJs> {
  using type = org::imm::ImmCmdNameValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCmdNameValueRead> {
  using type = ImmCmdNameValueReadJs;
};

struct ImmCmdCustomArgsValueReadJs : public Napi::ObjectWrap<ImmCmdCustomArgsValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomArgsValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomArgsValueReadJs", func);
    return exports;
  }
  ImmCmdCustomArgsValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomArgsValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCustomArgsValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdCustomArgsValueRead> const& ptr) : Napi::ObjectWrap<ImmCmdCustomArgsValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdCustomArgsValueRead> _stored;
  org::imm::ImmCmdCustomArgsValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCustomArgsValueReadJs> {
  using type = org::imm::ImmCmdCustomArgsValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCmdCustomArgsValueRead> {
  using type = ImmCmdCustomArgsValueReadJs;
};

struct ImmCmdCustomRawValueReadJs : public Napi::ObjectWrap<ImmCmdCustomRawValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomRawValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomRawValueReadJs", func);
    return exports;
  }
  ImmCmdCustomRawValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomRawValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCustomRawValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdCustomRawValueRead> const& ptr) : Napi::ObjectWrap<ImmCmdCustomRawValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdCustomRawValueRead> _stored;
  org::imm::ImmCmdCustomRawValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCustomRawValueReadJs> {
  using type = org::imm::ImmCmdCustomRawValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCmdCustomRawValueRead> {
  using type = ImmCmdCustomRawValueReadJs;
};

struct ImmCmdCustomTextValueReadJs : public Napi::ObjectWrap<ImmCmdCustomTextValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomTextValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomTextValueReadJs", func);
    return exports;
  }
  ImmCmdCustomTextValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomTextValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCustomTextValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdCustomTextValueRead> const& ptr) : Napi::ObjectWrap<ImmCmdCustomTextValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdCustomTextValueRead> _stored;
  org::imm::ImmCmdCustomTextValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCustomTextValueReadJs> {
  using type = org::imm::ImmCmdCustomTextValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCmdCustomTextValueRead> {
  using type = ImmCmdCustomTextValueReadJs;
};

struct ImmCmdCallValueReadJs : public Napi::ObjectWrap<ImmCmdCallValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCallValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCallValueReadJs", func);
    return exports;
  }
  ImmCmdCallValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCallValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCallValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdCallValueRead> const& ptr) : Napi::ObjectWrap<ImmCmdCallValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdCallValueRead> _stored;
  org::imm::ImmCmdCallValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCallValueReadJs> {
  using type = org::imm::ImmCmdCallValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCmdCallValueRead> {
  using type = ImmCmdCallValueReadJs;
};

struct ImmCmdTblfmValueReadJs : public Napi::ObjectWrap<ImmCmdTblfmValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdTblfmValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdTblfmValueReadJs", func);
    return exports;
  }
  ImmCmdTblfmValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdTblfmValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdTblfmValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdTblfmValueRead> const& ptr) : Napi::ObjectWrap<ImmCmdTblfmValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdTblfmValueRead> _stored;
  org::imm::ImmCmdTblfmValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdTblfmValueReadJs> {
  using type = org::imm::ImmCmdTblfmValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCmdTblfmValueRead> {
  using type = ImmCmdTblfmValueReadJs;
};

struct ImmHashTagValueReadJs : public Napi::ObjectWrap<ImmHashTagValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmHashTagValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmHashTagValueReadJs", func);
    return exports;
  }
  ImmHashTagValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmHashTagValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmHashTagValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmHashTagValueRead> const& ptr) : Napi::ObjectWrap<ImmHashTagValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmHashTagValueRead> _stored;
  org::imm::ImmHashTagValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmHashTagValueReadJs> {
  using type = org::imm::ImmHashTagValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmHashTagValueRead> {
  using type = ImmHashTagValueReadJs;
};

struct ImmInlineFootnoteValueReadJs : public Napi::ObjectWrap<ImmInlineFootnoteValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineFootnoteValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineFootnoteValueReadJs", func);
    return exports;
  }
  ImmInlineFootnoteValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmInlineFootnoteValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmInlineFootnoteValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmInlineFootnoteValueRead> const& ptr) : Napi::ObjectWrap<ImmInlineFootnoteValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmInlineFootnoteValueRead> _stored;
  org::imm::ImmInlineFootnoteValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmInlineFootnoteValueReadJs> {
  using type = org::imm::ImmInlineFootnoteValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmInlineFootnoteValueRead> {
  using type = ImmInlineFootnoteValueReadJs;
};

struct ImmInlineExportValueReadJs : public Napi::ObjectWrap<ImmInlineExportValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineExportValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineExportValueReadJs", func);
    return exports;
  }
  ImmInlineExportValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmInlineExportValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmInlineExportValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmInlineExportValueRead> const& ptr) : Napi::ObjectWrap<ImmInlineExportValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmInlineExportValueRead> _stored;
  org::imm::ImmInlineExportValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmInlineExportValueReadJs> {
  using type = org::imm::ImmInlineExportValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmInlineExportValueRead> {
  using type = ImmInlineExportValueReadJs;
};

struct ImmTimeValueReadJs : public Napi::ObjectWrap<ImmTimeValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeValueReadJs", func);
    return exports;
  }
  ImmTimeValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTimeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTimeValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmTimeValueRead> const& ptr) : Napi::ObjectWrap<ImmTimeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmTimeValueRead> _stored;
  org::imm::ImmTimeValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTimeValueReadJs> {
  using type = org::imm::ImmTimeValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmTimeValueRead> {
  using type = ImmTimeValueReadJs;
};

struct ImmTimeRangeValueReadJs : public Napi::ObjectWrap<ImmTimeRangeValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeRangeValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeRangeValueReadJs", func);
    return exports;
  }
  ImmTimeRangeValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTimeRangeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTimeRangeValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmTimeRangeValueRead> const& ptr) : Napi::ObjectWrap<ImmTimeRangeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmTimeRangeValueRead> _stored;
  org::imm::ImmTimeRangeValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTimeRangeValueReadJs> {
  using type = org::imm::ImmTimeRangeValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmTimeRangeValueRead> {
  using type = ImmTimeRangeValueReadJs;
};

struct ImmMacroValueReadJs : public Napi::ObjectWrap<ImmMacroValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMacroValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMacroValueReadJs", func);
    return exports;
  }
  ImmMacroValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMacroValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmMacroValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmMacroValueRead> const& ptr) : Napi::ObjectWrap<ImmMacroValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmMacroValueRead> _stored;
  org::imm::ImmMacroValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmMacroValueReadJs> {
  using type = org::imm::ImmMacroValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmMacroValueRead> {
  using type = ImmMacroValueReadJs;
};

struct ImmSymbolValueReadJs : public Napi::ObjectWrap<ImmSymbolValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymbolValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymbolValueReadJs", func);
    return exports;
  }
  ImmSymbolValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSymbolValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSymbolValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmSymbolValueRead> const& ptr) : Napi::ObjectWrap<ImmSymbolValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmSymbolValueRead> _stored;
  org::imm::ImmSymbolValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSymbolValueReadJs> {
  using type = org::imm::ImmSymbolValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmSymbolValueRead> {
  using type = ImmSymbolValueReadJs;
};

struct ImmEscapedValueReadJs : public Napi::ObjectWrap<ImmEscapedValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEscapedValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEscapedValueReadJs", func);
    return exports;
  }
  ImmEscapedValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmEscapedValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmEscapedValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmEscapedValueRead> const& ptr) : Napi::ObjectWrap<ImmEscapedValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmEscapedValueRead> _stored;
  org::imm::ImmEscapedValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmEscapedValueReadJs> {
  using type = org::imm::ImmEscapedValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmEscapedValueRead> {
  using type = ImmEscapedValueReadJs;
};

struct ImmNewlineValueReadJs : public Napi::ObjectWrap<ImmNewlineValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNewlineValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNewlineValueReadJs", func);
    return exports;
  }
  ImmNewlineValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmNewlineValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmNewlineValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmNewlineValueRead> const& ptr) : Napi::ObjectWrap<ImmNewlineValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmNewlineValueRead> _stored;
  org::imm::ImmNewlineValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmNewlineValueReadJs> {
  using type = org::imm::ImmNewlineValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmNewlineValueRead> {
  using type = ImmNewlineValueReadJs;
};

struct ImmSpaceValueReadJs : public Napi::ObjectWrap<ImmSpaceValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSpaceValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSpaceValueReadJs", func);
    return exports;
  }
  ImmSpaceValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSpaceValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSpaceValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmSpaceValueRead> const& ptr) : Napi::ObjectWrap<ImmSpaceValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmSpaceValueRead> _stored;
  org::imm::ImmSpaceValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSpaceValueReadJs> {
  using type = org::imm::ImmSpaceValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmSpaceValueRead> {
  using type = ImmSpaceValueReadJs;
};

struct ImmWordValueReadJs : public Napi::ObjectWrap<ImmWordValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmWordValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmWordValueReadJs", func);
    return exports;
  }
  ImmWordValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmWordValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmWordValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmWordValueRead> const& ptr) : Napi::ObjectWrap<ImmWordValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmWordValueRead> _stored;
  org::imm::ImmWordValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmWordValueReadJs> {
  using type = org::imm::ImmWordValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmWordValueRead> {
  using type = ImmWordValueReadJs;
};

struct ImmAtMentionValueReadJs : public Napi::ObjectWrap<ImmAtMentionValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAtMentionValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAtMentionValueReadJs", func);
    return exports;
  }
  ImmAtMentionValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmAtMentionValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmAtMentionValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAtMentionValueRead> const& ptr) : Napi::ObjectWrap<ImmAtMentionValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAtMentionValueRead> _stored;
  org::imm::ImmAtMentionValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmAtMentionValueReadJs> {
  using type = org::imm::ImmAtMentionValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmAtMentionValueRead> {
  using type = ImmAtMentionValueReadJs;
};

struct ImmRawTextValueReadJs : public Napi::ObjectWrap<ImmRawTextValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRawTextValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRawTextValueReadJs", func);
    return exports;
  }
  ImmRawTextValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRawTextValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmRawTextValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmRawTextValueRead> const& ptr) : Napi::ObjectWrap<ImmRawTextValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmRawTextValueRead> _stored;
  org::imm::ImmRawTextValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmRawTextValueReadJs> {
  using type = org::imm::ImmRawTextValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmRawTextValueRead> {
  using type = ImmRawTextValueReadJs;
};

struct ImmPunctuationValueReadJs : public Napi::ObjectWrap<ImmPunctuationValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPunctuationValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPunctuationValueReadJs", func);
    return exports;
  }
  ImmPunctuationValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPunctuationValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmPunctuationValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmPunctuationValueRead> const& ptr) : Napi::ObjectWrap<ImmPunctuationValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmPunctuationValueRead> _stored;
  org::imm::ImmPunctuationValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmPunctuationValueReadJs> {
  using type = org::imm::ImmPunctuationValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmPunctuationValueRead> {
  using type = ImmPunctuationValueReadJs;
};

struct ImmPlaceholderValueReadJs : public Napi::ObjectWrap<ImmPlaceholderValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPlaceholderValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPlaceholderValueReadJs", func);
    return exports;
  }
  ImmPlaceholderValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPlaceholderValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmPlaceholderValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmPlaceholderValueRead> const& ptr) : Napi::ObjectWrap<ImmPlaceholderValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmPlaceholderValueRead> _stored;
  org::imm::ImmPlaceholderValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmPlaceholderValueReadJs> {
  using type = org::imm::ImmPlaceholderValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmPlaceholderValueRead> {
  using type = ImmPlaceholderValueReadJs;
};

struct ImmBigIdentValueReadJs : public Napi::ObjectWrap<ImmBigIdentValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBigIdentValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBigIdentValueReadJs", func);
    return exports;
  }
  ImmBigIdentValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBigIdentValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBigIdentValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBigIdentValueRead> const& ptr) : Napi::ObjectWrap<ImmBigIdentValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBigIdentValueRead> _stored;
  org::imm::ImmBigIdentValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBigIdentValueReadJs> {
  using type = org::imm::ImmBigIdentValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmBigIdentValueRead> {
  using type = ImmBigIdentValueReadJs;
};

struct ImmTextTargetValueReadJs : public Napi::ObjectWrap<ImmTextTargetValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextTargetValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextTargetValueReadJs", func);
    return exports;
  }
  ImmTextTargetValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTextTargetValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTextTargetValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmTextTargetValueRead> const& ptr) : Napi::ObjectWrap<ImmTextTargetValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmTextTargetValueRead> _stored;
  org::imm::ImmTextTargetValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTextTargetValueReadJs> {
  using type = org::imm::ImmTextTargetValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmTextTargetValueRead> {
  using type = ImmTextTargetValueReadJs;
};

struct ImmBoldValueReadJs : public Napi::ObjectWrap<ImmBoldValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBoldValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBoldValueReadJs", func);
    return exports;
  }
  ImmBoldValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBoldValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBoldValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBoldValueRead> const& ptr) : Napi::ObjectWrap<ImmBoldValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBoldValueRead> _stored;
  org::imm::ImmBoldValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBoldValueReadJs> {
  using type = org::imm::ImmBoldValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmBoldValueRead> {
  using type = ImmBoldValueReadJs;
};

struct ImmUnderlineValueReadJs : public Napi::ObjectWrap<ImmUnderlineValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmUnderlineValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmUnderlineValueReadJs", func);
    return exports;
  }
  ImmUnderlineValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmUnderlineValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmUnderlineValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmUnderlineValueRead> const& ptr) : Napi::ObjectWrap<ImmUnderlineValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmUnderlineValueRead> _stored;
  org::imm::ImmUnderlineValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmUnderlineValueReadJs> {
  using type = org::imm::ImmUnderlineValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmUnderlineValueRead> {
  using type = ImmUnderlineValueReadJs;
};

struct ImmMonospaceValueReadJs : public Napi::ObjectWrap<ImmMonospaceValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMonospaceValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMonospaceValueReadJs", func);
    return exports;
  }
  ImmMonospaceValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMonospaceValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmMonospaceValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmMonospaceValueRead> const& ptr) : Napi::ObjectWrap<ImmMonospaceValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmMonospaceValueRead> _stored;
  org::imm::ImmMonospaceValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmMonospaceValueReadJs> {
  using type = org::imm::ImmMonospaceValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmMonospaceValueRead> {
  using type = ImmMonospaceValueReadJs;
};

struct ImmMarkQuoteValueReadJs : public Napi::ObjectWrap<ImmMarkQuoteValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMarkQuoteValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMarkQuoteValueReadJs", func);
    return exports;
  }
  ImmMarkQuoteValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMarkQuoteValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmMarkQuoteValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmMarkQuoteValueRead> const& ptr) : Napi::ObjectWrap<ImmMarkQuoteValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmMarkQuoteValueRead> _stored;
  org::imm::ImmMarkQuoteValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmMarkQuoteValueReadJs> {
  using type = org::imm::ImmMarkQuoteValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmMarkQuoteValueRead> {
  using type = ImmMarkQuoteValueReadJs;
};

struct ImmVerbatimValueReadJs : public Napi::ObjectWrap<ImmVerbatimValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmVerbatimValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmVerbatimValueReadJs", func);
    return exports;
  }
  ImmVerbatimValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmVerbatimValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmVerbatimValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmVerbatimValueRead> const& ptr) : Napi::ObjectWrap<ImmVerbatimValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmVerbatimValueRead> _stored;
  org::imm::ImmVerbatimValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmVerbatimValueReadJs> {
  using type = org::imm::ImmVerbatimValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmVerbatimValueRead> {
  using type = ImmVerbatimValueReadJs;
};

struct ImmItalicValueReadJs : public Napi::ObjectWrap<ImmItalicValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmItalicValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmItalicValueReadJs", func);
    return exports;
  }
  ImmItalicValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmItalicValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmItalicValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmItalicValueRead> const& ptr) : Napi::ObjectWrap<ImmItalicValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmItalicValueRead> _stored;
  org::imm::ImmItalicValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmItalicValueReadJs> {
  using type = org::imm::ImmItalicValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmItalicValueRead> {
  using type = ImmItalicValueReadJs;
};

struct ImmStrikeValueReadJs : public Napi::ObjectWrap<ImmStrikeValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStrikeValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStrikeValueReadJs", func);
    return exports;
  }
  ImmStrikeValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmStrikeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmStrikeValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmStrikeValueRead> const& ptr) : Napi::ObjectWrap<ImmStrikeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmStrikeValueRead> _stored;
  org::imm::ImmStrikeValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmStrikeValueReadJs> {
  using type = org::imm::ImmStrikeValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmStrikeValueRead> {
  using type = ImmStrikeValueReadJs;
};

struct ImmParValueReadJs : public Napi::ObjectWrap<ImmParValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParValueReadJs", func);
    return exports;
  }
  ImmParValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmParValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmParValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmParValueRead> const& ptr) : Napi::ObjectWrap<ImmParValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmParValueRead> _stored;
  org::imm::ImmParValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmParValueReadJs> {
  using type = org::imm::ImmParValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmParValueRead> {
  using type = ImmParValueReadJs;
};

struct ImmRadioTargetValueReadJs : public Napi::ObjectWrap<ImmRadioTargetValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRadioTargetValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRadioTargetValueReadJs", func);
    return exports;
  }
  ImmRadioTargetValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRadioTargetValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmRadioTargetValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmRadioTargetValueRead> const& ptr) : Napi::ObjectWrap<ImmRadioTargetValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmRadioTargetValueRead> _stored;
  org::imm::ImmRadioTargetValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmRadioTargetValueReadJs> {
  using type = org::imm::ImmRadioTargetValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmRadioTargetValueRead> {
  using type = ImmRadioTargetValueReadJs;
};

struct ImmLatexValueReadJs : public Napi::ObjectWrap<ImmLatexValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLatexValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLatexValueReadJs", func);
    return exports;
  }
  ImmLatexValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmLatexValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmLatexValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmLatexValueRead> const& ptr) : Napi::ObjectWrap<ImmLatexValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmLatexValueRead> _stored;
  org::imm::ImmLatexValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmLatexValueReadJs> {
  using type = org::imm::ImmLatexValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmLatexValueRead> {
  using type = ImmLatexValueReadJs;
};

struct ImmLinkValueReadJs : public Napi::ObjectWrap<ImmLinkValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLinkValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLinkValueReadJs", func);
    return exports;
  }
  ImmLinkValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmLinkValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmLinkValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmLinkValueRead> const& ptr) : Napi::ObjectWrap<ImmLinkValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmLinkValueRead> _stored;
  org::imm::ImmLinkValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmLinkValueReadJs> {
  using type = org::imm::ImmLinkValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmLinkValueRead> {
  using type = ImmLinkValueReadJs;
};

struct ImmBlockCenterValueReadJs : public Napi::ObjectWrap<ImmBlockCenterValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCenterValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCenterValueReadJs", func);
    return exports;
  }
  ImmBlockCenterValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCenterValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockCenterValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockCenterValueRead> const& ptr) : Napi::ObjectWrap<ImmBlockCenterValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockCenterValueRead> _stored;
  org::imm::ImmBlockCenterValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockCenterValueReadJs> {
  using type = org::imm::ImmBlockCenterValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmBlockCenterValueRead> {
  using type = ImmBlockCenterValueReadJs;
};

struct ImmBlockQuoteValueReadJs : public Napi::ObjectWrap<ImmBlockQuoteValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockQuoteValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockQuoteValueReadJs", func);
    return exports;
  }
  ImmBlockQuoteValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockQuoteValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockQuoteValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockQuoteValueRead> const& ptr) : Napi::ObjectWrap<ImmBlockQuoteValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockQuoteValueRead> _stored;
  org::imm::ImmBlockQuoteValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockQuoteValueReadJs> {
  using type = org::imm::ImmBlockQuoteValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmBlockQuoteValueRead> {
  using type = ImmBlockQuoteValueReadJs;
};

struct ImmBlockCommentValueReadJs : public Napi::ObjectWrap<ImmBlockCommentValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCommentValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCommentValueReadJs", func);
    return exports;
  }
  ImmBlockCommentValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCommentValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockCommentValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockCommentValueRead> const& ptr) : Napi::ObjectWrap<ImmBlockCommentValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockCommentValueRead> _stored;
  org::imm::ImmBlockCommentValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockCommentValueReadJs> {
  using type = org::imm::ImmBlockCommentValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmBlockCommentValueRead> {
  using type = ImmBlockCommentValueReadJs;
};

struct ImmBlockVerseValueReadJs : public Napi::ObjectWrap<ImmBlockVerseValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockVerseValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockVerseValueReadJs", func);
    return exports;
  }
  ImmBlockVerseValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockVerseValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockVerseValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockVerseValueRead> const& ptr) : Napi::ObjectWrap<ImmBlockVerseValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockVerseValueRead> _stored;
  org::imm::ImmBlockVerseValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockVerseValueReadJs> {
  using type = org::imm::ImmBlockVerseValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmBlockVerseValueRead> {
  using type = ImmBlockVerseValueReadJs;
};

struct ImmBlockDynamicFallbackValueReadJs : public Napi::ObjectWrap<ImmBlockDynamicFallbackValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockDynamicFallbackValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockDynamicFallbackValueReadJs", func);
    return exports;
  }
  ImmBlockDynamicFallbackValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockDynamicFallbackValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockDynamicFallbackValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockDynamicFallbackValueRead> const& ptr) : Napi::ObjectWrap<ImmBlockDynamicFallbackValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockDynamicFallbackValueRead> _stored;
  org::imm::ImmBlockDynamicFallbackValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockDynamicFallbackValueReadJs> {
  using type = org::imm::ImmBlockDynamicFallbackValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmBlockDynamicFallbackValueRead> {
  using type = ImmBlockDynamicFallbackValueReadJs;
};

struct ImmBlockExampleValueReadJs : public Napi::ObjectWrap<ImmBlockExampleValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExampleValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExampleValueReadJs", func);
    return exports;
  }
  ImmBlockExampleValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockExampleValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockExampleValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockExampleValueRead> const& ptr) : Napi::ObjectWrap<ImmBlockExampleValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockExampleValueRead> _stored;
  org::imm::ImmBlockExampleValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockExampleValueReadJs> {
  using type = org::imm::ImmBlockExampleValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmBlockExampleValueRead> {
  using type = ImmBlockExampleValueReadJs;
};

struct ImmBlockExportValueReadJs : public Napi::ObjectWrap<ImmBlockExportValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExportValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExportValueReadJs", func);
    return exports;
  }
  ImmBlockExportValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockExportValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockExportValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockExportValueRead> const& ptr) : Napi::ObjectWrap<ImmBlockExportValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockExportValueRead> _stored;
  org::imm::ImmBlockExportValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockExportValueReadJs> {
  using type = org::imm::ImmBlockExportValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmBlockExportValueRead> {
  using type = ImmBlockExportValueReadJs;
};

struct ImmBlockAdmonitionValueReadJs : public Napi::ObjectWrap<ImmBlockAdmonitionValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockAdmonitionValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockAdmonitionValueReadJs", func);
    return exports;
  }
  ImmBlockAdmonitionValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockAdmonitionValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockAdmonitionValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockAdmonitionValueRead> const& ptr) : Napi::ObjectWrap<ImmBlockAdmonitionValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockAdmonitionValueRead> _stored;
  org::imm::ImmBlockAdmonitionValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockAdmonitionValueReadJs> {
  using type = org::imm::ImmBlockAdmonitionValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmBlockAdmonitionValueRead> {
  using type = ImmBlockAdmonitionValueReadJs;
};

struct ImmBlockCodeEvalResultValueReadJs : public Napi::ObjectWrap<ImmBlockCodeEvalResultValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeEvalResultValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeEvalResultValueReadJs", func);
    return exports;
  }
  ImmBlockCodeEvalResultValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCodeEvalResultValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockCodeEvalResultValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockCodeEvalResultValueRead> const& ptr) : Napi::ObjectWrap<ImmBlockCodeEvalResultValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockCodeEvalResultValueRead> _stored;
  org::imm::ImmBlockCodeEvalResultValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockCodeEvalResultValueReadJs> {
  using type = org::imm::ImmBlockCodeEvalResultValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmBlockCodeEvalResultValueRead> {
  using type = ImmBlockCodeEvalResultValueReadJs;
};

struct ImmBlockCodeValueReadJs : public Napi::ObjectWrap<ImmBlockCodeValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeValueReadJs", func);
    return exports;
  }
  ImmBlockCodeValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCodeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockCodeValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockCodeValueRead> const& ptr) : Napi::ObjectWrap<ImmBlockCodeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockCodeValueRead> _stored;
  org::imm::ImmBlockCodeValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockCodeValueReadJs> {
  using type = org::imm::ImmBlockCodeValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmBlockCodeValueRead> {
  using type = ImmBlockCodeValueReadJs;
};

struct ImmSubtreeLogValueReadJs : public Napi::ObjectWrap<ImmSubtreeLogValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeLogValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeLogValueReadJs", func);
    return exports;
  }
  ImmSubtreeLogValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSubtreeLogValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSubtreeLogValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmSubtreeLogValueRead> const& ptr) : Napi::ObjectWrap<ImmSubtreeLogValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmSubtreeLogValueRead> _stored;
  org::imm::ImmSubtreeLogValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSubtreeLogValueReadJs> {
  using type = org::imm::ImmSubtreeLogValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmSubtreeLogValueRead> {
  using type = ImmSubtreeLogValueReadJs;
};

struct ImmSubtreeValueReadJs : public Napi::ObjectWrap<ImmSubtreeValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeValueReadJs", func);
    return exports;
  }
  ImmSubtreeValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSubtreeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSubtreeValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmSubtreeValueRead> const& ptr) : Napi::ObjectWrap<ImmSubtreeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmSubtreeValueRead> _stored;
  org::imm::ImmSubtreeValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSubtreeValueReadJs> {
  using type = org::imm::ImmSubtreeValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmSubtreeValueRead> {
  using type = ImmSubtreeValueReadJs;
};

struct ImmCellValueReadJs : public Napi::ObjectWrap<ImmCellValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCellValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCellValueReadJs", func);
    return exports;
  }
  ImmCellValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCellValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCellValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCellValueRead> const& ptr) : Napi::ObjectWrap<ImmCellValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCellValueRead> _stored;
  org::imm::ImmCellValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCellValueReadJs> {
  using type = org::imm::ImmCellValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCellValueRead> {
  using type = ImmCellValueReadJs;
};

struct ImmRowValueReadJs : public Napi::ObjectWrap<ImmRowValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRowValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRowValueReadJs", func);
    return exports;
  }
  ImmRowValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRowValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmRowValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmRowValueRead> const& ptr) : Napi::ObjectWrap<ImmRowValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmRowValueRead> _stored;
  org::imm::ImmRowValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmRowValueReadJs> {
  using type = org::imm::ImmRowValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmRowValueRead> {
  using type = ImmRowValueReadJs;
};

struct ImmTableValueReadJs : public Napi::ObjectWrap<ImmTableValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTableValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTableValueReadJs", func);
    return exports;
  }
  ImmTableValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTableValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTableValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmTableValueRead> const& ptr) : Napi::ObjectWrap<ImmTableValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmTableValueRead> _stored;
  org::imm::ImmTableValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTableValueReadJs> {
  using type = org::imm::ImmTableValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmTableValueRead> {
  using type = ImmTableValueReadJs;
};

struct ImmParagraphValueReadJs : public Napi::ObjectWrap<ImmParagraphValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParagraphValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParagraphValueReadJs", func);
    return exports;
  }
  ImmParagraphValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmParagraphValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmParagraphValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmParagraphValueRead> const& ptr) : Napi::ObjectWrap<ImmParagraphValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmParagraphValueRead> _stored;
  org::imm::ImmParagraphValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmParagraphValueReadJs> {
  using type = org::imm::ImmParagraphValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmParagraphValueRead> {
  using type = ImmParagraphValueReadJs;
};

struct ImmColonExampleValueReadJs : public Napi::ObjectWrap<ImmColonExampleValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmColonExampleValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmColonExampleValueReadJs", func);
    return exports;
  }
  ImmColonExampleValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmColonExampleValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmColonExampleValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmColonExampleValueRead> const& ptr) : Napi::ObjectWrap<ImmColonExampleValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmColonExampleValueRead> _stored;
  org::imm::ImmColonExampleValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmColonExampleValueReadJs> {
  using type = org::imm::ImmColonExampleValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmColonExampleValueRead> {
  using type = ImmColonExampleValueReadJs;
};

struct ImmCmdAttrValueReadJs : public Napi::ObjectWrap<ImmCmdAttrValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdAttrValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdAttrValueReadJs", func);
    return exports;
  }
  ImmCmdAttrValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdAttrValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdAttrValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdAttrValueRead> const& ptr) : Napi::ObjectWrap<ImmCmdAttrValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdAttrValueRead> _stored;
  org::imm::ImmCmdAttrValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdAttrValueReadJs> {
  using type = org::imm::ImmCmdAttrValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCmdAttrValueRead> {
  using type = ImmCmdAttrValueReadJs;
};

struct ImmCmdExportValueReadJs : public Napi::ObjectWrap<ImmCmdExportValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdExportValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdExportValueReadJs", func);
    return exports;
  }
  ImmCmdExportValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdExportValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdExportValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdExportValueRead> const& ptr) : Napi::ObjectWrap<ImmCmdExportValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdExportValueRead> _stored;
  org::imm::ImmCmdExportValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdExportValueReadJs> {
  using type = org::imm::ImmCmdExportValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCmdExportValueRead> {
  using type = ImmCmdExportValueReadJs;
};

struct ImmCallValueReadJs : public Napi::ObjectWrap<ImmCallValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCallValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCallValueReadJs", func);
    return exports;
  }
  ImmCallValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCallValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCallValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCallValueRead> const& ptr) : Napi::ObjectWrap<ImmCallValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCallValueRead> _stored;
  org::imm::ImmCallValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCallValueReadJs> {
  using type = org::imm::ImmCallValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCallValueRead> {
  using type = ImmCallValueReadJs;
};

struct ImmListValueReadJs : public Napi::ObjectWrap<ImmListValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListValueReadJs", func);
    return exports;
  }
  ImmListValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmListValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmListValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmListValueRead> const& ptr) : Napi::ObjectWrap<ImmListValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmListValueRead> _stored;
  org::imm::ImmListValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmListValueReadJs> {
  using type = org::imm::ImmListValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmListValueRead> {
  using type = ImmListValueReadJs;
};

struct ImmListItemValueReadJs : public Napi::ObjectWrap<ImmListItemValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListItemValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListItemValueReadJs", func);
    return exports;
  }
  ImmListItemValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmListItemValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmListItemValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmListItemValueRead> const& ptr) : Napi::ObjectWrap<ImmListItemValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmListItemValueRead> _stored;
  org::imm::ImmListItemValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmListItemValueReadJs> {
  using type = org::imm::ImmListItemValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmListItemValueRead> {
  using type = ImmListItemValueReadJs;
};

struct ImmDocumentOptionsValueReadJs : public Napi::ObjectWrap<ImmDocumentOptionsValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentOptionsValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentOptionsValueReadJs", func);
    return exports;
  }
  ImmDocumentOptionsValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentOptionsValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDocumentOptionsValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmDocumentOptionsValueRead> const& ptr) : Napi::ObjectWrap<ImmDocumentOptionsValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmDocumentOptionsValueRead> _stored;
  org::imm::ImmDocumentOptionsValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDocumentOptionsValueReadJs> {
  using type = org::imm::ImmDocumentOptionsValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmDocumentOptionsValueRead> {
  using type = ImmDocumentOptionsValueReadJs;
};

struct ImmDocumentFragmentValueReadJs : public Napi::ObjectWrap<ImmDocumentFragmentValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentFragmentValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentFragmentValueReadJs", func);
    return exports;
  }
  ImmDocumentFragmentValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentFragmentValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDocumentFragmentValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmDocumentFragmentValueRead> const& ptr) : Napi::ObjectWrap<ImmDocumentFragmentValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmDocumentFragmentValueRead> _stored;
  org::imm::ImmDocumentFragmentValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDocumentFragmentValueReadJs> {
  using type = org::imm::ImmDocumentFragmentValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmDocumentFragmentValueRead> {
  using type = ImmDocumentFragmentValueReadJs;
};

struct ImmCriticMarkupValueReadJs : public Napi::ObjectWrap<ImmCriticMarkupValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCriticMarkupValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCriticMarkupValueReadJs", func);
    return exports;
  }
  ImmCriticMarkupValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCriticMarkupValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCriticMarkupValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCriticMarkupValueRead> const& ptr) : Napi::ObjectWrap<ImmCriticMarkupValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCriticMarkupValueRead> _stored;
  org::imm::ImmCriticMarkupValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCriticMarkupValueReadJs> {
  using type = org::imm::ImmCriticMarkupValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCriticMarkupValueRead> {
  using type = ImmCriticMarkupValueReadJs;
};

struct ImmDocumentValueReadJs : public Napi::ObjectWrap<ImmDocumentValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentValueReadJs", func);
    return exports;
  }
  ImmDocumentValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDocumentValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmDocumentValueRead> const& ptr) : Napi::ObjectWrap<ImmDocumentValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmDocumentValueRead> _stored;
  org::imm::ImmDocumentValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDocumentValueReadJs> {
  using type = org::imm::ImmDocumentValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmDocumentValueRead> {
  using type = ImmDocumentValueReadJs;
};

struct ImmFileTargetValueReadJs : public Napi::ObjectWrap<ImmFileTargetValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileTargetValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileTargetValueReadJs", func);
    return exports;
  }
  ImmFileTargetValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmFileTargetValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmFileTargetValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmFileTargetValueRead> const& ptr) : Napi::ObjectWrap<ImmFileTargetValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmFileTargetValueRead> _stored;
  org::imm::ImmFileTargetValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmFileTargetValueReadJs> {
  using type = org::imm::ImmFileTargetValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmFileTargetValueRead> {
  using type = ImmFileTargetValueReadJs;
};

struct ImmTextSeparatorValueReadJs : public Napi::ObjectWrap<ImmTextSeparatorValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextSeparatorValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextSeparatorValueReadJs", func);
    return exports;
  }
  ImmTextSeparatorValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTextSeparatorValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTextSeparatorValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmTextSeparatorValueRead> const& ptr) : Napi::ObjectWrap<ImmTextSeparatorValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmTextSeparatorValueRead> _stored;
  org::imm::ImmTextSeparatorValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTextSeparatorValueReadJs> {
  using type = org::imm::ImmTextSeparatorValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmTextSeparatorValueRead> {
  using type = ImmTextSeparatorValueReadJs;
};

struct ImmDocumentGroupValueReadJs : public Napi::ObjectWrap<ImmDocumentGroupValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentGroupValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentGroupValueReadJs", func);
    return exports;
  }
  ImmDocumentGroupValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentGroupValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDocumentGroupValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmDocumentGroupValueRead> const& ptr) : Napi::ObjectWrap<ImmDocumentGroupValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmDocumentGroupValueRead> _stored;
  org::imm::ImmDocumentGroupValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDocumentGroupValueReadJs> {
  using type = org::imm::ImmDocumentGroupValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmDocumentGroupValueRead> {
  using type = ImmDocumentGroupValueReadJs;
};

struct ImmFileValueReadJs : public Napi::ObjectWrap<ImmFileValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileValueReadJs", func);
    return exports;
  }
  ImmFileValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmFileValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmFileValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmFileValueRead> const& ptr) : Napi::ObjectWrap<ImmFileValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmFileValueRead> _stored;
  org::imm::ImmFileValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmFileValueReadJs> {
  using type = org::imm::ImmFileValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmFileValueRead> {
  using type = ImmFileValueReadJs;
};

struct ImmDirectoryValueReadJs : public Napi::ObjectWrap<ImmDirectoryValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDirectoryValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDirectoryValueReadJs", func);
    return exports;
  }
  ImmDirectoryValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDirectoryValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDirectoryValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmDirectoryValueRead> const& ptr) : Napi::ObjectWrap<ImmDirectoryValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmDirectoryValueRead> _stored;
  org::imm::ImmDirectoryValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDirectoryValueReadJs> {
  using type = org::imm::ImmDirectoryValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmDirectoryValueRead> {
  using type = ImmDirectoryValueReadJs;
};

struct ImmSymlinkValueReadJs : public Napi::ObjectWrap<ImmSymlinkValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymlinkValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymlinkValueReadJs", func);
    return exports;
  }
  ImmSymlinkValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSymlinkValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSymlinkValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmSymlinkValueRead> const& ptr) : Napi::ObjectWrap<ImmSymlinkValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmSymlinkValueRead> _stored;
  org::imm::ImmSymlinkValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSymlinkValueReadJs> {
  using type = org::imm::ImmSymlinkValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmSymlinkValueRead> {
  using type = ImmSymlinkValueReadJs;
};

struct ImmCmdIncludeValueReadJs : public Napi::ObjectWrap<ImmCmdIncludeValueReadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdIncludeValueReadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdIncludeValueReadJs", func);
    return exports;
  }
  ImmCmdIncludeValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdIncludeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdIncludeValueReadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdIncludeValueRead> const& ptr) : Napi::ObjectWrap<ImmCmdIncludeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdIncludeValueRead> _stored;
  org::imm::ImmCmdIncludeValueRead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdIncludeValueReadJs> {
  using type = org::imm::ImmCmdIncludeValueRead;
};

template <>
struct org_to_js_type<org::imm::ImmCmdIncludeValueRead> {
  using type = ImmCmdIncludeValueReadJs;
};

struct ImmAstContextJs : public Napi::ObjectWrap<ImmAstContextJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAstContextJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAstContextJs", func);
    return exports;
  }
  ImmAstContextJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmAstContextJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmAstContextJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAstContext> const& ptr) : Napi::ObjectWrap<ImmAstContextJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAstContext> _stored;
  org::imm::ImmAstContext* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmAstContextJs> {
  using type = org::imm::ImmAstContext;
};

template <>
struct org_to_js_type<org::imm::ImmAstContext> {
  using type = ImmAstContextJs;
};

struct ImmAstVersionJs : public Napi::ObjectWrap<ImmAstVersionJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAstVersionJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAstVersionJs", func);
    return exports;
  }
  ImmAstVersionJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmAstVersionJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmAstVersion>();
  }
  ImmAstVersionJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAstVersion> const& ptr) : Napi::ObjectWrap<ImmAstVersionJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAstVersion> _stored;
  org::imm::ImmAstVersion* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmAstVersionJs> {
  using type = org::imm::ImmAstVersion;
};

template <>
struct org_to_js_type<org::imm::ImmAstVersion> {
  using type = ImmAstVersionJs;
};

struct ImmAdapterJs : public Napi::ObjectWrap<ImmAdapterJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterJs", func);
    return exports;
  }
  ImmAdapterJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmAdapterJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmAdapterJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapter> const& ptr) : Napi::ObjectWrap<ImmAdapterJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapter> _stored;
  org::imm::ImmAdapter* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmAdapterJs> {
  using type = org::imm::ImmAdapter;
};

template <>
struct org_to_js_type<org::imm::ImmAdapter> {
  using type = ImmAdapterJs;
};

struct OrgParseFragmentJs : public Napi::ObjectWrap<OrgParseFragmentJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgParseFragmentJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OrgParseFragmentJs", func);
    return exports;
  }
  OrgParseFragmentJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<OrgParseFragmentJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::OrgParseFragment>();
  }
  OrgParseFragmentJs(Napi::CallbackInfo const& info, std::shared_ptr<org::OrgParseFragment> const& ptr) : Napi::ObjectWrap<OrgParseFragmentJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::OrgParseFragment> _stored;
  org::OrgParseFragment* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<OrgParseFragmentJs> {
  using type = org::OrgParseFragment;
};

template <>
struct org_to_js_type<org::OrgParseFragment> {
  using type = OrgParseFragmentJs;
};

struct OrgParseParametersJs : public Napi::ObjectWrap<OrgParseParametersJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgParseParametersJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OrgParseParametersJs", func);
    return exports;
  }
  OrgParseParametersJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<OrgParseParametersJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::OrgParseParameters>();
  }
  OrgParseParametersJs(Napi::CallbackInfo const& info, std::shared_ptr<org::OrgParseParameters> const& ptr) : Napi::ObjectWrap<OrgParseParametersJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::OrgParseParameters> _stored;
  org::OrgParseParameters* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<OrgParseParametersJs> {
  using type = org::OrgParseParameters;
};

template <>
struct org_to_js_type<org::OrgParseParameters> {
  using type = OrgParseParametersJs;
};

struct OrgDirectoryParseParametersJs : public Napi::ObjectWrap<OrgDirectoryParseParametersJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgDirectoryParseParametersJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OrgDirectoryParseParametersJs", func);
    return exports;
  }
  OrgDirectoryParseParametersJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<OrgDirectoryParseParametersJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::OrgDirectoryParseParameters>();
  }
  OrgDirectoryParseParametersJs(Napi::CallbackInfo const& info, std::shared_ptr<org::OrgDirectoryParseParameters> const& ptr) : Napi::ObjectWrap<OrgDirectoryParseParametersJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::OrgDirectoryParseParameters> _stored;
  org::OrgDirectoryParseParameters* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<OrgDirectoryParseParametersJs> {
  using type = org::OrgDirectoryParseParameters;
};

template <>
struct org_to_js_type<org::OrgDirectoryParseParameters> {
  using type = OrgDirectoryParseParametersJs;
};

struct OrgYamlExportOptsJs : public Napi::ObjectWrap<OrgYamlExportOptsJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgYamlExportOptsJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OrgYamlExportOptsJs", func);
    return exports;
  }
  OrgYamlExportOptsJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<OrgYamlExportOptsJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::OrgYamlExportOpts>();
  }
  OrgYamlExportOptsJs(Napi::CallbackInfo const& info, std::shared_ptr<org::OrgYamlExportOpts> const& ptr) : Napi::ObjectWrap<OrgYamlExportOptsJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::OrgYamlExportOpts> _stored;
  org::OrgYamlExportOpts* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<OrgYamlExportOptsJs> {
  using type = org::OrgYamlExportOpts;
};

template <>
struct org_to_js_type<org::OrgYamlExportOpts> {
  using type = OrgYamlExportOptsJs;
};

struct OrgTreeExportOptsJs : public Napi::ObjectWrap<OrgTreeExportOptsJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgTreeExportOptsJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OrgTreeExportOptsJs", func);
    return exports;
  }
  OrgTreeExportOptsJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<OrgTreeExportOptsJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::OrgTreeExportOpts>();
  }
  OrgTreeExportOptsJs(Napi::CallbackInfo const& info, std::shared_ptr<org::OrgTreeExportOpts> const& ptr) : Napi::ObjectWrap<OrgTreeExportOptsJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::OrgTreeExportOpts> _stored;
  org::OrgTreeExportOpts* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<OrgTreeExportOptsJs> {
  using type = org::OrgTreeExportOpts;
};

template <>
struct org_to_js_type<org::OrgTreeExportOpts> {
  using type = OrgTreeExportOptsJs;
};

struct AstTrackingPathJs : public Napi::ObjectWrap<AstTrackingPathJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AstTrackingPathJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AstTrackingPathJs", func);
    return exports;
  }
  AstTrackingPathJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<AstTrackingPathJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::AstTrackingPath>();
  }
  AstTrackingPathJs(Napi::CallbackInfo const& info, std::shared_ptr<org::AstTrackingPath> const& ptr) : Napi::ObjectWrap<AstTrackingPathJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::AstTrackingPath> _stored;
  org::AstTrackingPath* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<AstTrackingPathJs> {
  using type = org::AstTrackingPath;
};

template <>
struct org_to_js_type<org::AstTrackingPath> {
  using type = AstTrackingPathJs;
};

struct AstTrackingAlternativesJs : public Napi::ObjectWrap<AstTrackingAlternativesJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AstTrackingAlternativesJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AstTrackingAlternativesJs", func);
    return exports;
  }
  AstTrackingAlternativesJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<AstTrackingAlternativesJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::AstTrackingAlternatives>();
  }
  AstTrackingAlternativesJs(Napi::CallbackInfo const& info, std::shared_ptr<org::AstTrackingAlternatives> const& ptr) : Napi::ObjectWrap<AstTrackingAlternativesJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::AstTrackingAlternatives> _stored;
  org::AstTrackingAlternatives* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<AstTrackingAlternativesJs> {
  using type = org::AstTrackingAlternatives;
};

template <>
struct org_to_js_type<org::AstTrackingAlternatives> {
  using type = AstTrackingAlternativesJs;
};

struct AstTrackingGroupJs : public Napi::ObjectWrap<AstTrackingGroupJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AstTrackingGroupJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AstTrackingGroupJs", func);
    return exports;
  }
  AstTrackingGroupJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<AstTrackingGroupJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::AstTrackingGroup>();
  }
  AstTrackingGroupJs(Napi::CallbackInfo const& info, std::shared_ptr<org::AstTrackingGroup> const& ptr) : Napi::ObjectWrap<AstTrackingGroupJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::AstTrackingGroup> _stored;
  org::AstTrackingGroup* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<AstTrackingGroupJs> {
  using type = org::AstTrackingGroup;
};

template <>
struct org_to_js_type<org::AstTrackingGroup> {
  using type = AstTrackingGroupJs;
};

struct AstTrackingMapJs : public Napi::ObjectWrap<AstTrackingMapJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AstTrackingMapJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AstTrackingMapJs", func);
    return exports;
  }
  AstTrackingMapJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<AstTrackingMapJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::AstTrackingMap>();
  }
  AstTrackingMapJs(Napi::CallbackInfo const& info, std::shared_ptr<org::AstTrackingMap> const& ptr) : Napi::ObjectWrap<AstTrackingMapJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::AstTrackingMap> _stored;
  org::AstTrackingMap* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<AstTrackingMapJs> {
  using type = org::AstTrackingMap;
};

template <>
struct org_to_js_type<org::AstTrackingMap> {
  using type = AstTrackingMapJs;
};

struct SequenceSegmentJs : public Napi::ObjectWrap<SequenceSegmentJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SequenceSegmentJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SequenceSegmentJs", func);
    return exports;
  }
  SequenceSegmentJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SequenceSegmentJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<hstd::SequenceSegment>();
  }
  SequenceSegmentJs(Napi::CallbackInfo const& info, std::shared_ptr<hstd::SequenceSegment> const& ptr) : Napi::ObjectWrap<SequenceSegmentJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<hstd::SequenceSegment> _stored;
  hstd::SequenceSegment* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SequenceSegmentJs> {
  using type = hstd::SequenceSegment;
};

template <>
struct org_to_js_type<hstd::SequenceSegment> {
  using type = SequenceSegmentJs;
};

struct SequenceSegmentGroupJs : public Napi::ObjectWrap<SequenceSegmentGroupJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SequenceSegmentGroupJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SequenceSegmentGroupJs", func);
    return exports;
  }
  SequenceSegmentGroupJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SequenceSegmentGroupJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<hstd::SequenceSegmentGroup>();
  }
  SequenceSegmentGroupJs(Napi::CallbackInfo const& info, std::shared_ptr<hstd::SequenceSegmentGroup> const& ptr) : Napi::ObjectWrap<SequenceSegmentGroupJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<hstd::SequenceSegmentGroup> _stored;
  hstd::SequenceSegmentGroup* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SequenceSegmentGroupJs> {
  using type = hstd::SequenceSegmentGroup;
};

template <>
struct org_to_js_type<hstd::SequenceSegmentGroup> {
  using type = SequenceSegmentGroupJs;
};

struct SequenceAnnotationTagJs : public Napi::ObjectWrap<SequenceAnnotationTagJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SequenceAnnotationTagJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SequenceAnnotationTagJs", func);
    return exports;
  }
  SequenceAnnotationTagJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SequenceAnnotationTagJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<hstd::SequenceAnnotationTag>();
  }
  SequenceAnnotationTagJs(Napi::CallbackInfo const& info, std::shared_ptr<hstd::SequenceAnnotationTag> const& ptr) : Napi::ObjectWrap<SequenceAnnotationTagJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<hstd::SequenceAnnotationTag> _stored;
  hstd::SequenceAnnotationTag* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SequenceAnnotationTagJs> {
  using type = hstd::SequenceAnnotationTag;
};

template <>
struct org_to_js_type<hstd::SequenceAnnotationTag> {
  using type = SequenceAnnotationTagJs;
};

struct SequenceAnnotationJs : public Napi::ObjectWrap<SequenceAnnotationJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SequenceAnnotationJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SequenceAnnotationJs", func);
    return exports;
  }
  SequenceAnnotationJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SequenceAnnotationJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<hstd::SequenceAnnotation>();
  }
  SequenceAnnotationJs(Napi::CallbackInfo const& info, std::shared_ptr<hstd::SequenceAnnotation> const& ptr) : Napi::ObjectWrap<SequenceAnnotationJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<hstd::SequenceAnnotation> _stored;
  hstd::SequenceAnnotation* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SequenceAnnotationJs> {
  using type = hstd::SequenceAnnotation;
};

template <>
struct org_to_js_type<hstd::SequenceAnnotation> {
  using type = SequenceAnnotationJs;
};

struct MapLinkJs : public Napi::ObjectWrap<MapLinkJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapLinkJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MapLinkJs", func);
    return exports;
  }
  MapLinkJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<MapLinkJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::graph::MapLink>();
  }
  MapLinkJs(Napi::CallbackInfo const& info, std::shared_ptr<org::graph::MapLink> const& ptr) : Napi::ObjectWrap<MapLinkJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::graph::MapLink> _stored;
  org::graph::MapLink* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<MapLinkJs> {
  using type = org::graph::MapLink;
};

template <>
struct org_to_js_type<org::graph::MapLink> {
  using type = MapLinkJs;
};

struct MapNodePropJs : public Napi::ObjectWrap<MapNodePropJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapNodePropJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MapNodePropJs", func);
    return exports;
  }
  MapNodePropJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<MapNodePropJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::graph::MapNodeProp>();
  }
  MapNodePropJs(Napi::CallbackInfo const& info, std::shared_ptr<org::graph::MapNodeProp> const& ptr) : Napi::ObjectWrap<MapNodePropJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::graph::MapNodeProp> _stored;
  org::graph::MapNodeProp* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<MapNodePropJs> {
  using type = org::graph::MapNodeProp;
};

template <>
struct org_to_js_type<org::graph::MapNodeProp> {
  using type = MapNodePropJs;
};

struct MapEdgePropJs : public Napi::ObjectWrap<MapEdgePropJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapEdgePropJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MapEdgePropJs", func);
    return exports;
  }
  MapEdgePropJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<MapEdgePropJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::graph::MapEdgeProp>();
  }
  MapEdgePropJs(Napi::CallbackInfo const& info, std::shared_ptr<org::graph::MapEdgeProp> const& ptr) : Napi::ObjectWrap<MapEdgePropJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::graph::MapEdgeProp> _stored;
  org::graph::MapEdgeProp* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<MapEdgePropJs> {
  using type = org::graph::MapEdgeProp;
};

template <>
struct org_to_js_type<org::graph::MapEdgeProp> {
  using type = MapEdgePropJs;
};

struct MapNodeJs : public Napi::ObjectWrap<MapNodeJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapNodeJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MapNodeJs", func);
    return exports;
  }
  MapNodeJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<MapNodeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::graph::MapNode>();
  }
  MapNodeJs(Napi::CallbackInfo const& info, std::shared_ptr<org::graph::MapNode> const& ptr) : Napi::ObjectWrap<MapNodeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::graph::MapNode> _stored;
  org::graph::MapNode* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<MapNodeJs> {
  using type = org::graph::MapNode;
};

template <>
struct org_to_js_type<org::graph::MapNode> {
  using type = MapNodeJs;
};

struct MapEdgeJs : public Napi::ObjectWrap<MapEdgeJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapEdgeJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MapEdgeJs", func);
    return exports;
  }
  MapEdgeJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<MapEdgeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::graph::MapEdge>();
  }
  MapEdgeJs(Napi::CallbackInfo const& info, std::shared_ptr<org::graph::MapEdge> const& ptr) : Napi::ObjectWrap<MapEdgeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::graph::MapEdge> _stored;
  org::graph::MapEdge* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<MapEdgeJs> {
  using type = org::graph::MapEdge;
};

template <>
struct org_to_js_type<org::graph::MapEdge> {
  using type = MapEdgeJs;
};

struct MapGraphJs : public Napi::ObjectWrap<MapGraphJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapGraphJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MapGraphJs", func);
    return exports;
  }
  MapGraphJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<MapGraphJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::graph::MapGraph>();
  }
  MapGraphJs(Napi::CallbackInfo const& info, std::shared_ptr<org::graph::MapGraph> const& ptr) : Napi::ObjectWrap<MapGraphJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::graph::MapGraph> _stored;
  org::graph::MapGraph* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<MapGraphJs> {
  using type = org::graph::MapGraph;
};

template <>
struct org_to_js_type<org::graph::MapGraph> {
  using type = MapGraphJs;
};

struct MapGraphStateJs : public Napi::ObjectWrap<MapGraphStateJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapGraphStateJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MapGraphStateJs", func);
    return exports;
  }
  MapGraphStateJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<MapGraphStateJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  MapGraphStateJs(Napi::CallbackInfo const& info, std::shared_ptr<org::graph::MapGraphState> const& ptr) : Napi::ObjectWrap<MapGraphStateJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::graph::MapGraphState> _stored;
  org::graph::MapGraphState* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<MapGraphStateJs> {
  using type = org::graph::MapGraphState;
};

template <>
struct org_to_js_type<org::graph::MapGraphState> {
  using type = MapGraphStateJs;
};

struct LispCodeJs : public Napi::ObjectWrap<LispCodeJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LispCodeJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("LispCodeJs", func);
    return exports;
  }
  LispCodeJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<LispCodeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::LispCode>();
  }
  LispCodeJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::LispCode> const& ptr) : Napi::ObjectWrap<LispCodeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::LispCode> _stored;
  org::sem::LispCode* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<LispCodeJs> {
  using type = org::sem::LispCode;
};

template <>
struct org_to_js_type<org::sem::LispCode> {
  using type = LispCodeJs;
};

struct TblfmJs : public Napi::ObjectWrap<TblfmJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TblfmJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("TblfmJs", func);
    return exports;
  }
  TblfmJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<TblfmJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Tblfm>();
  }
  TblfmJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Tblfm> const& ptr) : Napi::ObjectWrap<TblfmJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Tblfm> _stored;
  org::sem::Tblfm* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<TblfmJs> {
  using type = org::sem::Tblfm;
};

template <>
struct org_to_js_type<org::sem::Tblfm> {
  using type = TblfmJs;
};

struct AttrValueJs : public Napi::ObjectWrap<AttrValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AttrValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AttrValueJs", func);
    return exports;
  }
  AttrValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<AttrValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::AttrValue>();
  }
  AttrValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::AttrValue> const& ptr) : Napi::ObjectWrap<AttrValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::AttrValue> _stored;
  org::sem::AttrValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<AttrValueJs> {
  using type = org::sem::AttrValue;
};

template <>
struct org_to_js_type<org::sem::AttrValue> {
  using type = AttrValueJs;
};

struct HashTagFlatJs : public Napi::ObjectWrap<HashTagFlatJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "HashTagFlatJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("HashTagFlatJs", func);
    return exports;
  }
  HashTagFlatJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<HashTagFlatJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::HashTagFlat>();
  }
  HashTagFlatJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::HashTagFlat> const& ptr) : Napi::ObjectWrap<HashTagFlatJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::HashTagFlat> _stored;
  org::sem::HashTagFlat* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<HashTagFlatJs> {
  using type = org::sem::HashTagFlat;
};

template <>
struct org_to_js_type<org::sem::HashTagFlat> {
  using type = HashTagFlatJs;
};

struct HashTagTextJs : public Napi::ObjectWrap<HashTagTextJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "HashTagTextJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("HashTagTextJs", func);
    return exports;
  }
  HashTagTextJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<HashTagTextJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::HashTagText>();
  }
  HashTagTextJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::HashTagText> const& ptr) : Napi::ObjectWrap<HashTagTextJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::HashTagText> _stored;
  org::sem::HashTagText* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<HashTagTextJs> {
  using type = org::sem::HashTagText;
};

template <>
struct org_to_js_type<org::sem::HashTagText> {
  using type = HashTagTextJs;
};

struct SubtreePathJs : public Napi::ObjectWrap<SubtreePathJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreePathJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SubtreePathJs", func);
    return exports;
  }
  SubtreePathJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SubtreePathJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::SubtreePath>();
  }
  SubtreePathJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::SubtreePath> const& ptr) : Napi::ObjectWrap<SubtreePathJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::SubtreePath> _stored;
  org::sem::SubtreePath* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SubtreePathJs> {
  using type = org::sem::SubtreePath;
};

template <>
struct org_to_js_type<org::sem::SubtreePath> {
  using type = SubtreePathJs;
};

struct LinkTargetJs : public Napi::ObjectWrap<LinkTargetJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LinkTargetJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("LinkTargetJs", func);
    return exports;
  }
  LinkTargetJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<LinkTargetJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::LinkTarget>();
  }
  LinkTargetJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::LinkTarget> const& ptr) : Napi::ObjectWrap<LinkTargetJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::LinkTarget> _stored;
  org::sem::LinkTarget* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<LinkTargetJs> {
  using type = org::sem::LinkTarget;
};

template <>
struct org_to_js_type<org::sem::LinkTarget> {
  using type = LinkTargetJs;
};

struct SubtreeLogHeadJs : public Napi::ObjectWrap<SubtreeLogHeadJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreeLogHeadJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SubtreeLogHeadJs", func);
    return exports;
  }
  SubtreeLogHeadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SubtreeLogHeadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::SubtreeLogHead>();
  }
  SubtreeLogHeadJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::SubtreeLogHead> const& ptr) : Napi::ObjectWrap<SubtreeLogHeadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::SubtreeLogHead> _stored;
  org::sem::SubtreeLogHead* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SubtreeLogHeadJs> {
  using type = org::sem::SubtreeLogHead;
};

template <>
struct org_to_js_type<org::sem::SubtreeLogHead> {
  using type = SubtreeLogHeadJs;
};

struct SubtreeCompletionJs : public Napi::ObjectWrap<SubtreeCompletionJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreeCompletionJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SubtreeCompletionJs", func);
    return exports;
  }
  SubtreeCompletionJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SubtreeCompletionJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::SubtreeCompletion>();
  }
  SubtreeCompletionJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::SubtreeCompletion> const& ptr) : Napi::ObjectWrap<SubtreeCompletionJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::SubtreeCompletion> _stored;
  org::sem::SubtreeCompletion* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SubtreeCompletionJs> {
  using type = org::sem::SubtreeCompletion;
};

template <>
struct org_to_js_type<org::sem::SubtreeCompletion> {
  using type = SubtreeCompletionJs;
};

struct AttrListJs : public Napi::ObjectWrap<AttrListJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AttrListJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AttrListJs", func);
    return exports;
  }
  AttrListJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<AttrListJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::AttrList>();
  }
  AttrListJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::AttrList> const& ptr) : Napi::ObjectWrap<AttrListJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::AttrList> _stored;
  org::sem::AttrList* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<AttrListJs> {
  using type = org::sem::AttrList;
};

template <>
struct org_to_js_type<org::sem::AttrList> {
  using type = AttrListJs;
};

struct AttrGroupJs : public Napi::ObjectWrap<AttrGroupJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AttrGroupJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AttrGroupJs", func);
    return exports;
  }
  AttrGroupJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<AttrGroupJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::AttrGroup>();
  }
  AttrGroupJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::AttrGroup> const& ptr) : Napi::ObjectWrap<AttrGroupJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::AttrGroup> _stored;
  org::sem::AttrGroup* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<AttrGroupJs> {
  using type = org::sem::AttrGroup;
};

template <>
struct org_to_js_type<org::sem::AttrGroup> {
  using type = AttrGroupJs;
};

struct OrgCodeEvalInputJs : public Napi::ObjectWrap<OrgCodeEvalInputJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgCodeEvalInputJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OrgCodeEvalInputJs", func);
    return exports;
  }
  OrgCodeEvalInputJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<OrgCodeEvalInputJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::OrgCodeEvalInput>();
  }
  OrgCodeEvalInputJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::OrgCodeEvalInput> const& ptr) : Napi::ObjectWrap<OrgCodeEvalInputJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::OrgCodeEvalInput> _stored;
  org::sem::OrgCodeEvalInput* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<OrgCodeEvalInputJs> {
  using type = org::sem::OrgCodeEvalInput;
};

template <>
struct org_to_js_type<org::sem::OrgCodeEvalInput> {
  using type = OrgCodeEvalInputJs;
};

struct OrgCodeEvalOutputJs : public Napi::ObjectWrap<OrgCodeEvalOutputJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgCodeEvalOutputJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OrgCodeEvalOutputJs", func);
    return exports;
  }
  OrgCodeEvalOutputJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<OrgCodeEvalOutputJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::OrgCodeEvalOutput>();
  }
  OrgCodeEvalOutputJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::OrgCodeEvalOutput> const& ptr) : Napi::ObjectWrap<OrgCodeEvalOutputJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::OrgCodeEvalOutput> _stored;
  org::sem::OrgCodeEvalOutput* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<OrgCodeEvalOutputJs> {
  using type = org::sem::OrgCodeEvalOutput;
};

template <>
struct org_to_js_type<org::sem::OrgCodeEvalOutput> {
  using type = OrgCodeEvalOutputJs;
};

struct ColumnViewJs : public Napi::ObjectWrap<ColumnViewJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ColumnViewJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ColumnViewJs", func);
    return exports;
  }
  ColumnViewJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ColumnViewJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::ColumnView>();
  }
  ColumnViewJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::ColumnView> const& ptr) : Napi::ObjectWrap<ColumnViewJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::ColumnView> _stored;
  org::sem::ColumnView* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ColumnViewJs> {
  using type = org::sem::ColumnView;
};

template <>
struct org_to_js_type<org::sem::ColumnView> {
  using type = ColumnViewJs;
};

struct BlockCodeLineJs : public Napi::ObjectWrap<BlockCodeLineJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCodeLineJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockCodeLineJs", func);
    return exports;
  }
  BlockCodeLineJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BlockCodeLineJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::BlockCodeLine>();
  }
  BlockCodeLineJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::BlockCodeLine> const& ptr) : Napi::ObjectWrap<BlockCodeLineJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::BlockCodeLine> _stored;
  org::sem::BlockCodeLine* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BlockCodeLineJs> {
  using type = org::sem::BlockCodeLine;
};

template <>
struct org_to_js_type<org::sem::BlockCodeLine> {
  using type = BlockCodeLineJs;
};

struct DocumentExportConfigJs : public Napi::ObjectWrap<DocumentExportConfigJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentExportConfigJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("DocumentExportConfigJs", func);
    return exports;
  }
  DocumentExportConfigJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<DocumentExportConfigJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::DocumentExportConfig>();
  }
  DocumentExportConfigJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::DocumentExportConfig> const& ptr) : Napi::ObjectWrap<DocumentExportConfigJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::DocumentExportConfig> _stored;
  org::sem::DocumentExportConfig* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<DocumentExportConfigJs> {
  using type = org::sem::DocumentExportConfig;
};

template <>
struct org_to_js_type<org::sem::DocumentExportConfig> {
  using type = DocumentExportConfigJs;
};

struct SubtreePeriodJs : public Napi::ObjectWrap<SubtreePeriodJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreePeriodJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SubtreePeriodJs", func);
    return exports;
  }
  SubtreePeriodJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SubtreePeriodJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::SubtreePeriod>();
  }
  SubtreePeriodJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::SubtreePeriod> const& ptr) : Napi::ObjectWrap<SubtreePeriodJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::SubtreePeriod> _stored;
  org::sem::SubtreePeriod* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SubtreePeriodJs> {
  using type = org::sem::SubtreePeriod;
};

template <>
struct org_to_js_type<org::sem::SubtreePeriod> {
  using type = SubtreePeriodJs;
};

struct NamedPropertyJs : public Napi::ObjectWrap<NamedPropertyJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "NamedPropertyJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("NamedPropertyJs", func);
    return exports;
  }
  NamedPropertyJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<NamedPropertyJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::NamedProperty>();
  }
  NamedPropertyJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::NamedProperty> const& ptr) : Napi::ObjectWrap<NamedPropertyJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::NamedProperty> _stored;
  org::sem::NamedProperty* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<NamedPropertyJs> {
  using type = org::sem::NamedProperty;
};

template <>
struct org_to_js_type<org::sem::NamedProperty> {
  using type = NamedPropertyJs;
};

struct NoneJs : public Napi::ObjectWrap<NoneJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "NoneJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("NoneJs", func);
    return exports;
  }
  NoneJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<NoneJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::None>();
  }
  NoneJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::None> const& ptr) : Napi::ObjectWrap<NoneJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::None> _stored;
  org::sem::None* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<NoneJs> {
  using type = org::sem::None;
};

template <>
struct org_to_js_type<org::sem::None> {
  using type = NoneJs;
};

struct ErrorItemJs : public Napi::ObjectWrap<ErrorItemJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ErrorItemJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ErrorItemJs", func);
    return exports;
  }
  ErrorItemJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ErrorItemJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::ErrorItem>();
  }
  ErrorItemJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::ErrorItem> const& ptr) : Napi::ObjectWrap<ErrorItemJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::ErrorItem> _stored;
  org::sem::ErrorItem* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ErrorItemJs> {
  using type = org::sem::ErrorItem;
};

template <>
struct org_to_js_type<org::sem::ErrorItem> {
  using type = ErrorItemJs;
};

struct ErrorGroupJs : public Napi::ObjectWrap<ErrorGroupJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ErrorGroupJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ErrorGroupJs", func);
    return exports;
  }
  ErrorGroupJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ErrorGroupJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::ErrorGroup>();
  }
  ErrorGroupJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::ErrorGroup> const& ptr) : Napi::ObjectWrap<ErrorGroupJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::ErrorGroup> _stored;
  org::sem::ErrorGroup* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ErrorGroupJs> {
  using type = org::sem::ErrorGroup;
};

template <>
struct org_to_js_type<org::sem::ErrorGroup> {
  using type = ErrorGroupJs;
};

struct StmtListJs : public Napi::ObjectWrap<StmtListJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "StmtListJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("StmtListJs", func);
    return exports;
  }
  StmtListJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<StmtListJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::StmtList>();
  }
  StmtListJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::StmtList> const& ptr) : Napi::ObjectWrap<StmtListJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::StmtList> _stored;
  org::sem::StmtList* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<StmtListJs> {
  using type = org::sem::StmtList;
};

template <>
struct org_to_js_type<org::sem::StmtList> {
  using type = StmtListJs;
};

struct EmptyJs : public Napi::ObjectWrap<EmptyJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "EmptyJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("EmptyJs", func);
    return exports;
  }
  EmptyJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<EmptyJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Empty>();
  }
  EmptyJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Empty> const& ptr) : Napi::ObjectWrap<EmptyJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Empty> _stored;
  org::sem::Empty* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<EmptyJs> {
  using type = org::sem::Empty;
};

template <>
struct org_to_js_type<org::sem::Empty> {
  using type = EmptyJs;
};

struct TimeJs : public Napi::ObjectWrap<TimeJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TimeJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("TimeJs", func);
    return exports;
  }
  TimeJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<TimeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Time>();
  }
  TimeJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Time> const& ptr) : Napi::ObjectWrap<TimeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Time> _stored;
  org::sem::Time* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<TimeJs> {
  using type = org::sem::Time;
};

template <>
struct org_to_js_type<org::sem::Time> {
  using type = TimeJs;
};

struct TimeRangeJs : public Napi::ObjectWrap<TimeRangeJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TimeRangeJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("TimeRangeJs", func);
    return exports;
  }
  TimeRangeJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<TimeRangeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::TimeRange>();
  }
  TimeRangeJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::TimeRange> const& ptr) : Napi::ObjectWrap<TimeRangeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::TimeRange> _stored;
  org::sem::TimeRange* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<TimeRangeJs> {
  using type = org::sem::TimeRange;
};

template <>
struct org_to_js_type<org::sem::TimeRange> {
  using type = TimeRangeJs;
};

struct MacroJs : public Napi::ObjectWrap<MacroJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MacroJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MacroJs", func);
    return exports;
  }
  MacroJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<MacroJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Macro>();
  }
  MacroJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Macro> const& ptr) : Napi::ObjectWrap<MacroJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Macro> _stored;
  org::sem::Macro* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<MacroJs> {
  using type = org::sem::Macro;
};

template <>
struct org_to_js_type<org::sem::Macro> {
  using type = MacroJs;
};

struct SymbolJs : public Napi::ObjectWrap<SymbolJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SymbolJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SymbolJs", func);
    return exports;
  }
  SymbolJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SymbolJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Symbol>();
  }
  SymbolJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Symbol> const& ptr) : Napi::ObjectWrap<SymbolJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Symbol> _stored;
  org::sem::Symbol* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SymbolJs> {
  using type = org::sem::Symbol;
};

template <>
struct org_to_js_type<org::sem::Symbol> {
  using type = SymbolJs;
};

struct RadioTargetJs : public Napi::ObjectWrap<RadioTargetJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "RadioTargetJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("RadioTargetJs", func);
    return exports;
  }
  RadioTargetJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<RadioTargetJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::RadioTarget>();
  }
  RadioTargetJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::RadioTarget> const& ptr) : Napi::ObjectWrap<RadioTargetJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::RadioTarget> _stored;
  org::sem::RadioTarget* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<RadioTargetJs> {
  using type = org::sem::RadioTarget;
};

template <>
struct org_to_js_type<org::sem::RadioTarget> {
  using type = RadioTargetJs;
};

struct LatexJs : public Napi::ObjectWrap<LatexJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LatexJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("LatexJs", func);
    return exports;
  }
  LatexJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<LatexJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Latex>();
  }
  LatexJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Latex> const& ptr) : Napi::ObjectWrap<LatexJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Latex> _stored;
  org::sem::Latex* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<LatexJs> {
  using type = org::sem::Latex;
};

template <>
struct org_to_js_type<org::sem::Latex> {
  using type = LatexJs;
};

struct SubtreeLogJs : public Napi::ObjectWrap<SubtreeLogJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreeLogJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SubtreeLogJs", func);
    return exports;
  }
  SubtreeLogJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SubtreeLogJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::SubtreeLog>();
  }
  SubtreeLogJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::SubtreeLog> const& ptr) : Napi::ObjectWrap<SubtreeLogJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::SubtreeLog> _stored;
  org::sem::SubtreeLog* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SubtreeLogJs> {
  using type = org::sem::SubtreeLog;
};

template <>
struct org_to_js_type<org::sem::SubtreeLog> {
  using type = SubtreeLogJs;
};

struct SubtreeJs : public Napi::ObjectWrap<SubtreeJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreeJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SubtreeJs", func);
    return exports;
  }
  SubtreeJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SubtreeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Subtree>();
  }
  SubtreeJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Subtree> const& ptr) : Napi::ObjectWrap<SubtreeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Subtree> _stored;
  org::sem::Subtree* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SubtreeJs> {
  using type = org::sem::Subtree;
};

template <>
struct org_to_js_type<org::sem::Subtree> {
  using type = SubtreeJs;
};

struct ColonExampleJs : public Napi::ObjectWrap<ColonExampleJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ColonExampleJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ColonExampleJs", func);
    return exports;
  }
  ColonExampleJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ColonExampleJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::ColonExample>();
  }
  ColonExampleJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::ColonExample> const& ptr) : Napi::ObjectWrap<ColonExampleJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::ColonExample> _stored;
  org::sem::ColonExample* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ColonExampleJs> {
  using type = org::sem::ColonExample;
};

template <>
struct org_to_js_type<org::sem::ColonExample> {
  using type = ColonExampleJs;
};

struct CallJs : public Napi::ObjectWrap<CallJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CallJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CallJs", func);
    return exports;
  }
  CallJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CallJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Call>();
  }
  CallJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Call> const& ptr) : Napi::ObjectWrap<CallJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Call> _stored;
  org::sem::Call* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CallJs> {
  using type = org::sem::Call;
};

template <>
struct org_to_js_type<org::sem::Call> {
  using type = CallJs;
};

struct ListItemJs : public Napi::ObjectWrap<ListItemJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ListItemJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ListItemJs", func);
    return exports;
  }
  ListItemJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ListItemJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::ListItem>();
  }
  ListItemJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::ListItem> const& ptr) : Napi::ObjectWrap<ListItemJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::ListItem> _stored;
  org::sem::ListItem* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ListItemJs> {
  using type = org::sem::ListItem;
};

template <>
struct org_to_js_type<org::sem::ListItem> {
  using type = ListItemJs;
};

struct DocumentOptionsJs : public Napi::ObjectWrap<DocumentOptionsJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentOptionsJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("DocumentOptionsJs", func);
    return exports;
  }
  DocumentOptionsJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<DocumentOptionsJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::DocumentOptions>();
  }
  DocumentOptionsJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::DocumentOptions> const& ptr) : Napi::ObjectWrap<DocumentOptionsJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::DocumentOptions> _stored;
  org::sem::DocumentOptions* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<DocumentOptionsJs> {
  using type = org::sem::DocumentOptions;
};

template <>
struct org_to_js_type<org::sem::DocumentOptions> {
  using type = DocumentOptionsJs;
};

struct DocumentFragmentJs : public Napi::ObjectWrap<DocumentFragmentJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentFragmentJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("DocumentFragmentJs", func);
    return exports;
  }
  DocumentFragmentJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<DocumentFragmentJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::DocumentFragment>();
  }
  DocumentFragmentJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::DocumentFragment> const& ptr) : Napi::ObjectWrap<DocumentFragmentJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::DocumentFragment> _stored;
  org::sem::DocumentFragment* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<DocumentFragmentJs> {
  using type = org::sem::DocumentFragment;
};

template <>
struct org_to_js_type<org::sem::DocumentFragment> {
  using type = DocumentFragmentJs;
};

struct CriticMarkupJs : public Napi::ObjectWrap<CriticMarkupJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CriticMarkupJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CriticMarkupJs", func);
    return exports;
  }
  CriticMarkupJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CriticMarkupJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::CriticMarkup>();
  }
  CriticMarkupJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::CriticMarkup> const& ptr) : Napi::ObjectWrap<CriticMarkupJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::CriticMarkup> _stored;
  org::sem::CriticMarkup* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CriticMarkupJs> {
  using type = org::sem::CriticMarkup;
};

template <>
struct org_to_js_type<org::sem::CriticMarkup> {
  using type = CriticMarkupJs;
};

struct DocumentJs : public Napi::ObjectWrap<DocumentJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("DocumentJs", func);
    return exports;
  }
  DocumentJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<DocumentJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Document>();
  }
  DocumentJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Document> const& ptr) : Napi::ObjectWrap<DocumentJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Document> _stored;
  org::sem::Document* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<DocumentJs> {
  using type = org::sem::Document;
};

template <>
struct org_to_js_type<org::sem::Document> {
  using type = DocumentJs;
};

struct FileTargetJs : public Napi::ObjectWrap<FileTargetJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "FileTargetJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("FileTargetJs", func);
    return exports;
  }
  FileTargetJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<FileTargetJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::FileTarget>();
  }
  FileTargetJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::FileTarget> const& ptr) : Napi::ObjectWrap<FileTargetJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::FileTarget> _stored;
  org::sem::FileTarget* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<FileTargetJs> {
  using type = org::sem::FileTarget;
};

template <>
struct org_to_js_type<org::sem::FileTarget> {
  using type = FileTargetJs;
};

struct TextSeparatorJs : public Napi::ObjectWrap<TextSeparatorJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TextSeparatorJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("TextSeparatorJs", func);
    return exports;
  }
  TextSeparatorJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<TextSeparatorJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::TextSeparator>();
  }
  TextSeparatorJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::TextSeparator> const& ptr) : Napi::ObjectWrap<TextSeparatorJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::TextSeparator> _stored;
  org::sem::TextSeparator* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<TextSeparatorJs> {
  using type = org::sem::TextSeparator;
};

template <>
struct org_to_js_type<org::sem::TextSeparator> {
  using type = TextSeparatorJs;
};

struct DocumentGroupJs : public Napi::ObjectWrap<DocumentGroupJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentGroupJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("DocumentGroupJs", func);
    return exports;
  }
  DocumentGroupJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<DocumentGroupJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::DocumentGroup>();
  }
  DocumentGroupJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::DocumentGroup> const& ptr) : Napi::ObjectWrap<DocumentGroupJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::DocumentGroup> _stored;
  org::sem::DocumentGroup* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<DocumentGroupJs> {
  using type = org::sem::DocumentGroup;
};

template <>
struct org_to_js_type<org::sem::DocumentGroup> {
  using type = DocumentGroupJs;
};

struct FileJs : public Napi::ObjectWrap<FileJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "FileJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("FileJs", func);
    return exports;
  }
  FileJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<FileJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::File>();
  }
  FileJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::File> const& ptr) : Napi::ObjectWrap<FileJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::File> _stored;
  org::sem::File* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<FileJs> {
  using type = org::sem::File;
};

template <>
struct org_to_js_type<org::sem::File> {
  using type = FileJs;
};

struct DirectoryJs : public Napi::ObjectWrap<DirectoryJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DirectoryJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("DirectoryJs", func);
    return exports;
  }
  DirectoryJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<DirectoryJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Directory>();
  }
  DirectoryJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Directory> const& ptr) : Napi::ObjectWrap<DirectoryJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Directory> _stored;
  org::sem::Directory* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<DirectoryJs> {
  using type = org::sem::Directory;
};

template <>
struct org_to_js_type<org::sem::Directory> {
  using type = DirectoryJs;
};

struct SymlinkJs : public Napi::ObjectWrap<SymlinkJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SymlinkJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SymlinkJs", func);
    return exports;
  }
  SymlinkJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SymlinkJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Symlink>();
  }
  SymlinkJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Symlink> const& ptr) : Napi::ObjectWrap<SymlinkJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Symlink> _stored;
  org::sem::Symlink* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SymlinkJs> {
  using type = org::sem::Symlink;
};

template <>
struct org_to_js_type<org::sem::Symlink> {
  using type = SymlinkJs;
};

struct CmdIncludeJs : public Napi::ObjectWrap<CmdIncludeJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdIncludeJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdIncludeJs", func);
    return exports;
  }
  CmdIncludeJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CmdIncludeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::CmdInclude>();
  }
  CmdIncludeJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::CmdInclude> const& ptr) : Napi::ObjectWrap<CmdIncludeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::CmdInclude> _stored;
  org::sem::CmdInclude* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CmdIncludeJs> {
  using type = org::sem::CmdInclude;
};

template <>
struct org_to_js_type<org::sem::CmdInclude> {
  using type = CmdIncludeJs;
};

struct MapConfigJs : public Napi::ObjectWrap<MapConfigJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapConfigJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MapConfigJs", func);
    return exports;
  }
  MapConfigJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<MapConfigJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::graph::MapConfig>();
  }
  MapConfigJs(Napi::CallbackInfo const& info, std::shared_ptr<org::graph::MapConfig> const& ptr) : Napi::ObjectWrap<MapConfigJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::graph::MapConfig> _stored;
  org::graph::MapConfig* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<MapConfigJs> {
  using type = org::graph::MapConfig;
};

template <>
struct org_to_js_type<org::graph::MapConfig> {
  using type = MapConfigJs;
};

struct ImmIdTNone : public Napi::ObjectWrap<ImmIdTNone> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTNone", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTNone", func);
    return exports;
  }
  ImmIdTNone(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTNone>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmNone>>();
  }
  ImmIdTNone(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmNone>> const& ptr) : Napi::ObjectWrap<ImmIdTNone>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmNone>> _stored;
  org::imm::ImmIdT<org::imm::ImmNone>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTNone> {
  using type = org::imm::ImmIdT<org::imm::ImmNone>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmNone>> {
  using type = ImmIdTNone;
};

struct ImmIdTErrorItem : public Napi::ObjectWrap<ImmIdTErrorItem> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTErrorItem", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTErrorItem", func);
    return exports;
  }
  ImmIdTErrorItem(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTErrorItem>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmErrorItem>>();
  }
  ImmIdTErrorItem(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmErrorItem>> const& ptr) : Napi::ObjectWrap<ImmIdTErrorItem>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmErrorItem>> _stored;
  org::imm::ImmIdT<org::imm::ImmErrorItem>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTErrorItem> {
  using type = org::imm::ImmIdT<org::imm::ImmErrorItem>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmErrorItem>> {
  using type = ImmIdTErrorItem;
};

struct ImmIdTErrorGroup : public Napi::ObjectWrap<ImmIdTErrorGroup> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTErrorGroup", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTErrorGroup", func);
    return exports;
  }
  ImmIdTErrorGroup(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTErrorGroup>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmErrorGroup>>();
  }
  ImmIdTErrorGroup(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmErrorGroup>> const& ptr) : Napi::ObjectWrap<ImmIdTErrorGroup>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmErrorGroup>> _stored;
  org::imm::ImmIdT<org::imm::ImmErrorGroup>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTErrorGroup> {
  using type = org::imm::ImmIdT<org::imm::ImmErrorGroup>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmErrorGroup>> {
  using type = ImmIdTErrorGroup;
};

struct ImmIdTStmt : public Napi::ObjectWrap<ImmIdTStmt> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTStmt", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTStmt", func);
    return exports;
  }
  ImmIdTStmt(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTStmt>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmStmt>>();
  }
  ImmIdTStmt(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmStmt>> const& ptr) : Napi::ObjectWrap<ImmIdTStmt>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmStmt>> _stored;
  org::imm::ImmIdT<org::imm::ImmStmt>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTStmt> {
  using type = org::imm::ImmIdT<org::imm::ImmStmt>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmStmt>> {
  using type = ImmIdTStmt;
};

struct ImmIdTInline : public Napi::ObjectWrap<ImmIdTInline> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTInline", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTInline", func);
    return exports;
  }
  ImmIdTInline(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTInline>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmInline>>();
  }
  ImmIdTInline(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmInline>> const& ptr) : Napi::ObjectWrap<ImmIdTInline>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmInline>> _stored;
  org::imm::ImmIdT<org::imm::ImmInline>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTInline> {
  using type = org::imm::ImmIdT<org::imm::ImmInline>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmInline>> {
  using type = ImmIdTInline;
};

struct ImmIdTStmtList : public Napi::ObjectWrap<ImmIdTStmtList> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTStmtList", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTStmtList", func);
    return exports;
  }
  ImmIdTStmtList(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTStmtList>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmStmtList>>();
  }
  ImmIdTStmtList(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmStmtList>> const& ptr) : Napi::ObjectWrap<ImmIdTStmtList>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmStmtList>> _stored;
  org::imm::ImmIdT<org::imm::ImmStmtList>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTStmtList> {
  using type = org::imm::ImmIdT<org::imm::ImmStmtList>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmStmtList>> {
  using type = ImmIdTStmtList;
};

struct ImmIdTEmpty : public Napi::ObjectWrap<ImmIdTEmpty> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTEmpty", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTEmpty", func);
    return exports;
  }
  ImmIdTEmpty(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTEmpty>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmEmpty>>();
  }
  ImmIdTEmpty(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmEmpty>> const& ptr) : Napi::ObjectWrap<ImmIdTEmpty>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmEmpty>> _stored;
  org::imm::ImmIdT<org::imm::ImmEmpty>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTEmpty> {
  using type = org::imm::ImmIdT<org::imm::ImmEmpty>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmEmpty>> {
  using type = ImmIdTEmpty;
};

struct ImmIdTCmd : public Napi::ObjectWrap<ImmIdTCmd> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmd", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCmd", func);
    return exports;
  }
  ImmIdTCmd(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCmd>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCmd>>();
  }
  ImmIdTCmd(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmd>> const& ptr) : Napi::ObjectWrap<ImmIdTCmd>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmd>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmd>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCmd> {
  using type = org::imm::ImmIdT<org::imm::ImmCmd>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCmd>> {
  using type = ImmIdTCmd;
};

struct ImmIdTBlock : public Napi::ObjectWrap<ImmIdTBlock> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlock", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBlock", func);
    return exports;
  }
  ImmIdTBlock(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBlock>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBlock>>();
  }
  ImmIdTBlock(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlock>> const& ptr) : Napi::ObjectWrap<ImmIdTBlock>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlock>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlock>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBlock> {
  using type = org::imm::ImmIdT<org::imm::ImmBlock>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBlock>> {
  using type = ImmIdTBlock;
};

struct ImmIdTLineCommand : public Napi::ObjectWrap<ImmIdTLineCommand> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTLineCommand", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTLineCommand", func);
    return exports;
  }
  ImmIdTLineCommand(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTLineCommand>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmLineCommand>>();
  }
  ImmIdTLineCommand(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmLineCommand>> const& ptr) : Napi::ObjectWrap<ImmIdTLineCommand>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmLineCommand>> _stored;
  org::imm::ImmIdT<org::imm::ImmLineCommand>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTLineCommand> {
  using type = org::imm::ImmIdT<org::imm::ImmLineCommand>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmLineCommand>> {
  using type = ImmIdTLineCommand;
};

struct ImmIdTAttached : public Napi::ObjectWrap<ImmIdTAttached> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTAttached", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTAttached", func);
    return exports;
  }
  ImmIdTAttached(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTAttached>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmAttached>>();
  }
  ImmIdTAttached(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmAttached>> const& ptr) : Napi::ObjectWrap<ImmIdTAttached>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmAttached>> _stored;
  org::imm::ImmIdT<org::imm::ImmAttached>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTAttached> {
  using type = org::imm::ImmIdT<org::imm::ImmAttached>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmAttached>> {
  using type = ImmIdTAttached;
};

struct ImmIdTLeaf : public Napi::ObjectWrap<ImmIdTLeaf> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTLeaf", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTLeaf", func);
    return exports;
  }
  ImmIdTLeaf(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTLeaf>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmLeaf>>();
  }
  ImmIdTLeaf(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmLeaf>> const& ptr) : Napi::ObjectWrap<ImmIdTLeaf>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmLeaf>> _stored;
  org::imm::ImmIdT<org::imm::ImmLeaf>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTLeaf> {
  using type = org::imm::ImmIdT<org::imm::ImmLeaf>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmLeaf>> {
  using type = ImmIdTLeaf;
};

struct ImmIdTCmdCaption : public Napi::ObjectWrap<ImmIdTCmdCaption> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdCaption", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCmdCaption", func);
    return exports;
  }
  ImmIdTCmdCaption(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCmdCaption>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCmdCaption>>();
  }
  ImmIdTCmdCaption(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCaption>> const& ptr) : Napi::ObjectWrap<ImmIdTCmdCaption>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCaption>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdCaption>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCmdCaption> {
  using type = org::imm::ImmIdT<org::imm::ImmCmdCaption>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCmdCaption>> {
  using type = ImmIdTCmdCaption;
};

struct ImmIdTCmdColumns : public Napi::ObjectWrap<ImmIdTCmdColumns> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdColumns", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCmdColumns", func);
    return exports;
  }
  ImmIdTCmdColumns(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCmdColumns>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCmdColumns>>();
  }
  ImmIdTCmdColumns(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdColumns>> const& ptr) : Napi::ObjectWrap<ImmIdTCmdColumns>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdColumns>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdColumns>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCmdColumns> {
  using type = org::imm::ImmIdT<org::imm::ImmCmdColumns>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCmdColumns>> {
  using type = ImmIdTCmdColumns;
};

struct ImmIdTCmdName : public Napi::ObjectWrap<ImmIdTCmdName> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdName", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCmdName", func);
    return exports;
  }
  ImmIdTCmdName(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCmdName>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCmdName>>();
  }
  ImmIdTCmdName(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdName>> const& ptr) : Napi::ObjectWrap<ImmIdTCmdName>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdName>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdName>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCmdName> {
  using type = org::imm::ImmIdT<org::imm::ImmCmdName>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCmdName>> {
  using type = ImmIdTCmdName;
};

struct ImmIdTCmdCustomArgs : public Napi::ObjectWrap<ImmIdTCmdCustomArgs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdCustomArgs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCmdCustomArgs", func);
    return exports;
  }
  ImmIdTCmdCustomArgs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCmdCustomArgs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCmdCustomArgs>>();
  }
  ImmIdTCmdCustomArgs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCustomArgs>> const& ptr) : Napi::ObjectWrap<ImmIdTCmdCustomArgs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCustomArgs>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdCustomArgs>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCmdCustomArgs> {
  using type = org::imm::ImmIdT<org::imm::ImmCmdCustomArgs>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCmdCustomArgs>> {
  using type = ImmIdTCmdCustomArgs;
};

struct ImmIdTCmdCustomRaw : public Napi::ObjectWrap<ImmIdTCmdCustomRaw> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdCustomRaw", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCmdCustomRaw", func);
    return exports;
  }
  ImmIdTCmdCustomRaw(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCmdCustomRaw>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCmdCustomRaw>>();
  }
  ImmIdTCmdCustomRaw(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCustomRaw>> const& ptr) : Napi::ObjectWrap<ImmIdTCmdCustomRaw>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCustomRaw>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdCustomRaw>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCmdCustomRaw> {
  using type = org::imm::ImmIdT<org::imm::ImmCmdCustomRaw>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCmdCustomRaw>> {
  using type = ImmIdTCmdCustomRaw;
};

struct ImmIdTCmdCustomText : public Napi::ObjectWrap<ImmIdTCmdCustomText> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdCustomText", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCmdCustomText", func);
    return exports;
  }
  ImmIdTCmdCustomText(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCmdCustomText>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCmdCustomText>>();
  }
  ImmIdTCmdCustomText(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCustomText>> const& ptr) : Napi::ObjectWrap<ImmIdTCmdCustomText>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCustomText>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdCustomText>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCmdCustomText> {
  using type = org::imm::ImmIdT<org::imm::ImmCmdCustomText>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCmdCustomText>> {
  using type = ImmIdTCmdCustomText;
};

struct ImmIdTCmdCall : public Napi::ObjectWrap<ImmIdTCmdCall> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdCall", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCmdCall", func);
    return exports;
  }
  ImmIdTCmdCall(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCmdCall>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCmdCall>>();
  }
  ImmIdTCmdCall(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCall>> const& ptr) : Napi::ObjectWrap<ImmIdTCmdCall>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCall>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdCall>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCmdCall> {
  using type = org::imm::ImmIdT<org::imm::ImmCmdCall>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCmdCall>> {
  using type = ImmIdTCmdCall;
};

struct ImmIdTCmdTblfm : public Napi::ObjectWrap<ImmIdTCmdTblfm> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdTblfm", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCmdTblfm", func);
    return exports;
  }
  ImmIdTCmdTblfm(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCmdTblfm>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCmdTblfm>>();
  }
  ImmIdTCmdTblfm(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdTblfm>> const& ptr) : Napi::ObjectWrap<ImmIdTCmdTblfm>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdTblfm>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdTblfm>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCmdTblfm> {
  using type = org::imm::ImmIdT<org::imm::ImmCmdTblfm>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCmdTblfm>> {
  using type = ImmIdTCmdTblfm;
};

struct ImmIdTHashTag : public Napi::ObjectWrap<ImmIdTHashTag> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTHashTag", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTHashTag", func);
    return exports;
  }
  ImmIdTHashTag(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTHashTag>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmHashTag>>();
  }
  ImmIdTHashTag(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmHashTag>> const& ptr) : Napi::ObjectWrap<ImmIdTHashTag>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmHashTag>> _stored;
  org::imm::ImmIdT<org::imm::ImmHashTag>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTHashTag> {
  using type = org::imm::ImmIdT<org::imm::ImmHashTag>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmHashTag>> {
  using type = ImmIdTHashTag;
};

struct ImmIdTInlineFootnote : public Napi::ObjectWrap<ImmIdTInlineFootnote> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTInlineFootnote", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTInlineFootnote", func);
    return exports;
  }
  ImmIdTInlineFootnote(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTInlineFootnote>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmInlineFootnote>>();
  }
  ImmIdTInlineFootnote(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmInlineFootnote>> const& ptr) : Napi::ObjectWrap<ImmIdTInlineFootnote>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmInlineFootnote>> _stored;
  org::imm::ImmIdT<org::imm::ImmInlineFootnote>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTInlineFootnote> {
  using type = org::imm::ImmIdT<org::imm::ImmInlineFootnote>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmInlineFootnote>> {
  using type = ImmIdTInlineFootnote;
};

struct ImmIdTInlineExport : public Napi::ObjectWrap<ImmIdTInlineExport> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTInlineExport", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTInlineExport", func);
    return exports;
  }
  ImmIdTInlineExport(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTInlineExport>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmInlineExport>>();
  }
  ImmIdTInlineExport(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmInlineExport>> const& ptr) : Napi::ObjectWrap<ImmIdTInlineExport>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmInlineExport>> _stored;
  org::imm::ImmIdT<org::imm::ImmInlineExport>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTInlineExport> {
  using type = org::imm::ImmIdT<org::imm::ImmInlineExport>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmInlineExport>> {
  using type = ImmIdTInlineExport;
};

struct ImmIdTTime : public Napi::ObjectWrap<ImmIdTTime> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTTime", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTTime", func);
    return exports;
  }
  ImmIdTTime(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTTime>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmTime>>();
  }
  ImmIdTTime(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTime>> const& ptr) : Napi::ObjectWrap<ImmIdTTime>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTime>> _stored;
  org::imm::ImmIdT<org::imm::ImmTime>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTTime> {
  using type = org::imm::ImmIdT<org::imm::ImmTime>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmTime>> {
  using type = ImmIdTTime;
};

struct ImmIdTTimeRange : public Napi::ObjectWrap<ImmIdTTimeRange> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTTimeRange", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTTimeRange", func);
    return exports;
  }
  ImmIdTTimeRange(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTTimeRange>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmTimeRange>>();
  }
  ImmIdTTimeRange(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTimeRange>> const& ptr) : Napi::ObjectWrap<ImmIdTTimeRange>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTimeRange>> _stored;
  org::imm::ImmIdT<org::imm::ImmTimeRange>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTTimeRange> {
  using type = org::imm::ImmIdT<org::imm::ImmTimeRange>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmTimeRange>> {
  using type = ImmIdTTimeRange;
};

struct ImmIdTMacro : public Napi::ObjectWrap<ImmIdTMacro> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTMacro", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTMacro", func);
    return exports;
  }
  ImmIdTMacro(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTMacro>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmMacro>>();
  }
  ImmIdTMacro(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmMacro>> const& ptr) : Napi::ObjectWrap<ImmIdTMacro>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmMacro>> _stored;
  org::imm::ImmIdT<org::imm::ImmMacro>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTMacro> {
  using type = org::imm::ImmIdT<org::imm::ImmMacro>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmMacro>> {
  using type = ImmIdTMacro;
};

struct ImmIdTSymbol : public Napi::ObjectWrap<ImmIdTSymbol> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTSymbol", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTSymbol", func);
    return exports;
  }
  ImmIdTSymbol(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTSymbol>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmSymbol>>();
  }
  ImmIdTSymbol(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSymbol>> const& ptr) : Napi::ObjectWrap<ImmIdTSymbol>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSymbol>> _stored;
  org::imm::ImmIdT<org::imm::ImmSymbol>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTSymbol> {
  using type = org::imm::ImmIdT<org::imm::ImmSymbol>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmSymbol>> {
  using type = ImmIdTSymbol;
};

struct ImmIdTEscaped : public Napi::ObjectWrap<ImmIdTEscaped> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTEscaped", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTEscaped", func);
    return exports;
  }
  ImmIdTEscaped(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTEscaped>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmEscaped>>();
  }
  ImmIdTEscaped(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmEscaped>> const& ptr) : Napi::ObjectWrap<ImmIdTEscaped>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmEscaped>> _stored;
  org::imm::ImmIdT<org::imm::ImmEscaped>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTEscaped> {
  using type = org::imm::ImmIdT<org::imm::ImmEscaped>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmEscaped>> {
  using type = ImmIdTEscaped;
};

struct ImmIdTNewline : public Napi::ObjectWrap<ImmIdTNewline> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTNewline", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTNewline", func);
    return exports;
  }
  ImmIdTNewline(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTNewline>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmNewline>>();
  }
  ImmIdTNewline(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmNewline>> const& ptr) : Napi::ObjectWrap<ImmIdTNewline>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmNewline>> _stored;
  org::imm::ImmIdT<org::imm::ImmNewline>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTNewline> {
  using type = org::imm::ImmIdT<org::imm::ImmNewline>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmNewline>> {
  using type = ImmIdTNewline;
};

struct ImmIdTSpace : public Napi::ObjectWrap<ImmIdTSpace> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTSpace", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTSpace", func);
    return exports;
  }
  ImmIdTSpace(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTSpace>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmSpace>>();
  }
  ImmIdTSpace(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSpace>> const& ptr) : Napi::ObjectWrap<ImmIdTSpace>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSpace>> _stored;
  org::imm::ImmIdT<org::imm::ImmSpace>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTSpace> {
  using type = org::imm::ImmIdT<org::imm::ImmSpace>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmSpace>> {
  using type = ImmIdTSpace;
};

struct ImmIdTWord : public Napi::ObjectWrap<ImmIdTWord> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTWord", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTWord", func);
    return exports;
  }
  ImmIdTWord(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTWord>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmWord>>();
  }
  ImmIdTWord(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmWord>> const& ptr) : Napi::ObjectWrap<ImmIdTWord>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmWord>> _stored;
  org::imm::ImmIdT<org::imm::ImmWord>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTWord> {
  using type = org::imm::ImmIdT<org::imm::ImmWord>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmWord>> {
  using type = ImmIdTWord;
};

struct ImmIdTAtMention : public Napi::ObjectWrap<ImmIdTAtMention> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTAtMention", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTAtMention", func);
    return exports;
  }
  ImmIdTAtMention(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTAtMention>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmAtMention>>();
  }
  ImmIdTAtMention(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmAtMention>> const& ptr) : Napi::ObjectWrap<ImmIdTAtMention>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmAtMention>> _stored;
  org::imm::ImmIdT<org::imm::ImmAtMention>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTAtMention> {
  using type = org::imm::ImmIdT<org::imm::ImmAtMention>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmAtMention>> {
  using type = ImmIdTAtMention;
};

struct ImmIdTRawText : public Napi::ObjectWrap<ImmIdTRawText> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTRawText", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTRawText", func);
    return exports;
  }
  ImmIdTRawText(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTRawText>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmRawText>>();
  }
  ImmIdTRawText(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmRawText>> const& ptr) : Napi::ObjectWrap<ImmIdTRawText>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmRawText>> _stored;
  org::imm::ImmIdT<org::imm::ImmRawText>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTRawText> {
  using type = org::imm::ImmIdT<org::imm::ImmRawText>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmRawText>> {
  using type = ImmIdTRawText;
};

struct ImmIdTPunctuation : public Napi::ObjectWrap<ImmIdTPunctuation> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTPunctuation", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTPunctuation", func);
    return exports;
  }
  ImmIdTPunctuation(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTPunctuation>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmPunctuation>>();
  }
  ImmIdTPunctuation(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmPunctuation>> const& ptr) : Napi::ObjectWrap<ImmIdTPunctuation>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmPunctuation>> _stored;
  org::imm::ImmIdT<org::imm::ImmPunctuation>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTPunctuation> {
  using type = org::imm::ImmIdT<org::imm::ImmPunctuation>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmPunctuation>> {
  using type = ImmIdTPunctuation;
};

struct ImmIdTPlaceholder : public Napi::ObjectWrap<ImmIdTPlaceholder> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTPlaceholder", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTPlaceholder", func);
    return exports;
  }
  ImmIdTPlaceholder(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTPlaceholder>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmPlaceholder>>();
  }
  ImmIdTPlaceholder(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmPlaceholder>> const& ptr) : Napi::ObjectWrap<ImmIdTPlaceholder>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmPlaceholder>> _stored;
  org::imm::ImmIdT<org::imm::ImmPlaceholder>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTPlaceholder> {
  using type = org::imm::ImmIdT<org::imm::ImmPlaceholder>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmPlaceholder>> {
  using type = ImmIdTPlaceholder;
};

struct ImmIdTBigIdent : public Napi::ObjectWrap<ImmIdTBigIdent> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBigIdent", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBigIdent", func);
    return exports;
  }
  ImmIdTBigIdent(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBigIdent>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBigIdent>>();
  }
  ImmIdTBigIdent(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBigIdent>> const& ptr) : Napi::ObjectWrap<ImmIdTBigIdent>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBigIdent>> _stored;
  org::imm::ImmIdT<org::imm::ImmBigIdent>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBigIdent> {
  using type = org::imm::ImmIdT<org::imm::ImmBigIdent>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBigIdent>> {
  using type = ImmIdTBigIdent;
};

struct ImmIdTTextTarget : public Napi::ObjectWrap<ImmIdTTextTarget> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTTextTarget", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTTextTarget", func);
    return exports;
  }
  ImmIdTTextTarget(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTTextTarget>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmTextTarget>>();
  }
  ImmIdTTextTarget(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTextTarget>> const& ptr) : Napi::ObjectWrap<ImmIdTTextTarget>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTextTarget>> _stored;
  org::imm::ImmIdT<org::imm::ImmTextTarget>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTTextTarget> {
  using type = org::imm::ImmIdT<org::imm::ImmTextTarget>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmTextTarget>> {
  using type = ImmIdTTextTarget;
};

struct ImmIdTMarkup : public Napi::ObjectWrap<ImmIdTMarkup> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTMarkup", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTMarkup", func);
    return exports;
  }
  ImmIdTMarkup(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTMarkup>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmMarkup>>();
  }
  ImmIdTMarkup(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmMarkup>> const& ptr) : Napi::ObjectWrap<ImmIdTMarkup>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmMarkup>> _stored;
  org::imm::ImmIdT<org::imm::ImmMarkup>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTMarkup> {
  using type = org::imm::ImmIdT<org::imm::ImmMarkup>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmMarkup>> {
  using type = ImmIdTMarkup;
};

struct ImmIdTBold : public Napi::ObjectWrap<ImmIdTBold> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBold", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBold", func);
    return exports;
  }
  ImmIdTBold(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBold>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBold>>();
  }
  ImmIdTBold(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBold>> const& ptr) : Napi::ObjectWrap<ImmIdTBold>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBold>> _stored;
  org::imm::ImmIdT<org::imm::ImmBold>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBold> {
  using type = org::imm::ImmIdT<org::imm::ImmBold>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBold>> {
  using type = ImmIdTBold;
};

struct ImmIdTUnderline : public Napi::ObjectWrap<ImmIdTUnderline> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTUnderline", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTUnderline", func);
    return exports;
  }
  ImmIdTUnderline(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTUnderline>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmUnderline>>();
  }
  ImmIdTUnderline(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmUnderline>> const& ptr) : Napi::ObjectWrap<ImmIdTUnderline>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmUnderline>> _stored;
  org::imm::ImmIdT<org::imm::ImmUnderline>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTUnderline> {
  using type = org::imm::ImmIdT<org::imm::ImmUnderline>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmUnderline>> {
  using type = ImmIdTUnderline;
};

struct ImmIdTMonospace : public Napi::ObjectWrap<ImmIdTMonospace> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTMonospace", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTMonospace", func);
    return exports;
  }
  ImmIdTMonospace(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTMonospace>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmMonospace>>();
  }
  ImmIdTMonospace(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmMonospace>> const& ptr) : Napi::ObjectWrap<ImmIdTMonospace>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmMonospace>> _stored;
  org::imm::ImmIdT<org::imm::ImmMonospace>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTMonospace> {
  using type = org::imm::ImmIdT<org::imm::ImmMonospace>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmMonospace>> {
  using type = ImmIdTMonospace;
};

struct ImmIdTMarkQuote : public Napi::ObjectWrap<ImmIdTMarkQuote> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTMarkQuote", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTMarkQuote", func);
    return exports;
  }
  ImmIdTMarkQuote(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTMarkQuote>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmMarkQuote>>();
  }
  ImmIdTMarkQuote(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmMarkQuote>> const& ptr) : Napi::ObjectWrap<ImmIdTMarkQuote>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmMarkQuote>> _stored;
  org::imm::ImmIdT<org::imm::ImmMarkQuote>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTMarkQuote> {
  using type = org::imm::ImmIdT<org::imm::ImmMarkQuote>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmMarkQuote>> {
  using type = ImmIdTMarkQuote;
};

struct ImmIdTVerbatim : public Napi::ObjectWrap<ImmIdTVerbatim> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTVerbatim", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTVerbatim", func);
    return exports;
  }
  ImmIdTVerbatim(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTVerbatim>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmVerbatim>>();
  }
  ImmIdTVerbatim(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmVerbatim>> const& ptr) : Napi::ObjectWrap<ImmIdTVerbatim>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmVerbatim>> _stored;
  org::imm::ImmIdT<org::imm::ImmVerbatim>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTVerbatim> {
  using type = org::imm::ImmIdT<org::imm::ImmVerbatim>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmVerbatim>> {
  using type = ImmIdTVerbatim;
};

struct ImmIdTItalic : public Napi::ObjectWrap<ImmIdTItalic> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTItalic", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTItalic", func);
    return exports;
  }
  ImmIdTItalic(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTItalic>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmItalic>>();
  }
  ImmIdTItalic(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmItalic>> const& ptr) : Napi::ObjectWrap<ImmIdTItalic>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmItalic>> _stored;
  org::imm::ImmIdT<org::imm::ImmItalic>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTItalic> {
  using type = org::imm::ImmIdT<org::imm::ImmItalic>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmItalic>> {
  using type = ImmIdTItalic;
};

struct ImmIdTStrike : public Napi::ObjectWrap<ImmIdTStrike> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTStrike", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTStrike", func);
    return exports;
  }
  ImmIdTStrike(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTStrike>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmStrike>>();
  }
  ImmIdTStrike(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmStrike>> const& ptr) : Napi::ObjectWrap<ImmIdTStrike>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmStrike>> _stored;
  org::imm::ImmIdT<org::imm::ImmStrike>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTStrike> {
  using type = org::imm::ImmIdT<org::imm::ImmStrike>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmStrike>> {
  using type = ImmIdTStrike;
};

struct ImmIdTPar : public Napi::ObjectWrap<ImmIdTPar> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTPar", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTPar", func);
    return exports;
  }
  ImmIdTPar(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTPar>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmPar>>();
  }
  ImmIdTPar(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmPar>> const& ptr) : Napi::ObjectWrap<ImmIdTPar>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmPar>> _stored;
  org::imm::ImmIdT<org::imm::ImmPar>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTPar> {
  using type = org::imm::ImmIdT<org::imm::ImmPar>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmPar>> {
  using type = ImmIdTPar;
};

struct ImmIdTRadioTarget : public Napi::ObjectWrap<ImmIdTRadioTarget> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTRadioTarget", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTRadioTarget", func);
    return exports;
  }
  ImmIdTRadioTarget(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTRadioTarget>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmRadioTarget>>();
  }
  ImmIdTRadioTarget(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmRadioTarget>> const& ptr) : Napi::ObjectWrap<ImmIdTRadioTarget>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmRadioTarget>> _stored;
  org::imm::ImmIdT<org::imm::ImmRadioTarget>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTRadioTarget> {
  using type = org::imm::ImmIdT<org::imm::ImmRadioTarget>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmRadioTarget>> {
  using type = ImmIdTRadioTarget;
};

struct ImmIdTLatex : public Napi::ObjectWrap<ImmIdTLatex> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTLatex", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTLatex", func);
    return exports;
  }
  ImmIdTLatex(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTLatex>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmLatex>>();
  }
  ImmIdTLatex(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmLatex>> const& ptr) : Napi::ObjectWrap<ImmIdTLatex>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmLatex>> _stored;
  org::imm::ImmIdT<org::imm::ImmLatex>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTLatex> {
  using type = org::imm::ImmIdT<org::imm::ImmLatex>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmLatex>> {
  using type = ImmIdTLatex;
};

struct ImmIdTLink : public Napi::ObjectWrap<ImmIdTLink> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTLink", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTLink", func);
    return exports;
  }
  ImmIdTLink(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTLink>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmLink>>();
  }
  ImmIdTLink(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmLink>> const& ptr) : Napi::ObjectWrap<ImmIdTLink>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmLink>> _stored;
  org::imm::ImmIdT<org::imm::ImmLink>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTLink> {
  using type = org::imm::ImmIdT<org::imm::ImmLink>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmLink>> {
  using type = ImmIdTLink;
};

struct ImmIdTBlockCenter : public Napi::ObjectWrap<ImmIdTBlockCenter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockCenter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBlockCenter", func);
    return exports;
  }
  ImmIdTBlockCenter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBlockCenter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBlockCenter>>();
  }
  ImmIdTBlockCenter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockCenter>> const& ptr) : Napi::ObjectWrap<ImmIdTBlockCenter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockCenter>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockCenter>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBlockCenter> {
  using type = org::imm::ImmIdT<org::imm::ImmBlockCenter>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBlockCenter>> {
  using type = ImmIdTBlockCenter;
};

struct ImmIdTBlockQuote : public Napi::ObjectWrap<ImmIdTBlockQuote> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockQuote", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBlockQuote", func);
    return exports;
  }
  ImmIdTBlockQuote(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBlockQuote>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBlockQuote>>();
  }
  ImmIdTBlockQuote(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockQuote>> const& ptr) : Napi::ObjectWrap<ImmIdTBlockQuote>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockQuote>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockQuote>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBlockQuote> {
  using type = org::imm::ImmIdT<org::imm::ImmBlockQuote>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBlockQuote>> {
  using type = ImmIdTBlockQuote;
};

struct ImmIdTBlockComment : public Napi::ObjectWrap<ImmIdTBlockComment> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockComment", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBlockComment", func);
    return exports;
  }
  ImmIdTBlockComment(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBlockComment>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBlockComment>>();
  }
  ImmIdTBlockComment(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockComment>> const& ptr) : Napi::ObjectWrap<ImmIdTBlockComment>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockComment>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockComment>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBlockComment> {
  using type = org::imm::ImmIdT<org::imm::ImmBlockComment>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBlockComment>> {
  using type = ImmIdTBlockComment;
};

struct ImmIdTBlockVerse : public Napi::ObjectWrap<ImmIdTBlockVerse> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockVerse", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBlockVerse", func);
    return exports;
  }
  ImmIdTBlockVerse(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBlockVerse>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBlockVerse>>();
  }
  ImmIdTBlockVerse(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockVerse>> const& ptr) : Napi::ObjectWrap<ImmIdTBlockVerse>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockVerse>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockVerse>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBlockVerse> {
  using type = org::imm::ImmIdT<org::imm::ImmBlockVerse>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBlockVerse>> {
  using type = ImmIdTBlockVerse;
};

struct ImmIdTBlockDynamicFallback : public Napi::ObjectWrap<ImmIdTBlockDynamicFallback> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockDynamicFallback", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBlockDynamicFallback", func);
    return exports;
  }
  ImmIdTBlockDynamicFallback(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBlockDynamicFallback>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBlockDynamicFallback>>();
  }
  ImmIdTBlockDynamicFallback(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockDynamicFallback>> const& ptr) : Napi::ObjectWrap<ImmIdTBlockDynamicFallback>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockDynamicFallback>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockDynamicFallback>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBlockDynamicFallback> {
  using type = org::imm::ImmIdT<org::imm::ImmBlockDynamicFallback>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBlockDynamicFallback>> {
  using type = ImmIdTBlockDynamicFallback;
};

struct ImmIdTBlockExample : public Napi::ObjectWrap<ImmIdTBlockExample> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockExample", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBlockExample", func);
    return exports;
  }
  ImmIdTBlockExample(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBlockExample>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBlockExample>>();
  }
  ImmIdTBlockExample(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockExample>> const& ptr) : Napi::ObjectWrap<ImmIdTBlockExample>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockExample>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockExample>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBlockExample> {
  using type = org::imm::ImmIdT<org::imm::ImmBlockExample>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBlockExample>> {
  using type = ImmIdTBlockExample;
};

struct ImmIdTBlockExport : public Napi::ObjectWrap<ImmIdTBlockExport> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockExport", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBlockExport", func);
    return exports;
  }
  ImmIdTBlockExport(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBlockExport>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBlockExport>>();
  }
  ImmIdTBlockExport(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockExport>> const& ptr) : Napi::ObjectWrap<ImmIdTBlockExport>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockExport>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockExport>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBlockExport> {
  using type = org::imm::ImmIdT<org::imm::ImmBlockExport>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBlockExport>> {
  using type = ImmIdTBlockExport;
};

struct ImmIdTBlockAdmonition : public Napi::ObjectWrap<ImmIdTBlockAdmonition> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockAdmonition", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBlockAdmonition", func);
    return exports;
  }
  ImmIdTBlockAdmonition(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBlockAdmonition>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBlockAdmonition>>();
  }
  ImmIdTBlockAdmonition(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockAdmonition>> const& ptr) : Napi::ObjectWrap<ImmIdTBlockAdmonition>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockAdmonition>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockAdmonition>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBlockAdmonition> {
  using type = org::imm::ImmIdT<org::imm::ImmBlockAdmonition>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBlockAdmonition>> {
  using type = ImmIdTBlockAdmonition;
};

struct ImmIdTBlockCodeEvalResult : public Napi::ObjectWrap<ImmIdTBlockCodeEvalResult> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockCodeEvalResult", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBlockCodeEvalResult", func);
    return exports;
  }
  ImmIdTBlockCodeEvalResult(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBlockCodeEvalResult>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>();
  }
  ImmIdTBlockCodeEvalResult(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const& ptr) : Napi::ObjectWrap<ImmIdTBlockCodeEvalResult>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBlockCodeEvalResult> {
  using type = org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> {
  using type = ImmIdTBlockCodeEvalResult;
};

struct ImmIdTBlockCode : public Napi::ObjectWrap<ImmIdTBlockCode> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockCode", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTBlockCode", func);
    return exports;
  }
  ImmIdTBlockCode(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTBlockCode>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmBlockCode>>();
  }
  ImmIdTBlockCode(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockCode>> const& ptr) : Napi::ObjectWrap<ImmIdTBlockCode>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockCode>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockCode>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTBlockCode> {
  using type = org::imm::ImmIdT<org::imm::ImmBlockCode>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmBlockCode>> {
  using type = ImmIdTBlockCode;
};

struct ImmIdTSubtreeLog : public Napi::ObjectWrap<ImmIdTSubtreeLog> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTSubtreeLog", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTSubtreeLog", func);
    return exports;
  }
  ImmIdTSubtreeLog(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTSubtreeLog>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmSubtreeLog>>();
  }
  ImmIdTSubtreeLog(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> const& ptr) : Napi::ObjectWrap<ImmIdTSubtreeLog>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> _stored;
  org::imm::ImmIdT<org::imm::ImmSubtreeLog>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTSubtreeLog> {
  using type = org::imm::ImmIdT<org::imm::ImmSubtreeLog>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> {
  using type = ImmIdTSubtreeLog;
};

struct ImmIdTSubtree : public Napi::ObjectWrap<ImmIdTSubtree> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTSubtree", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTSubtree", func);
    return exports;
  }
  ImmIdTSubtree(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTSubtree>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmSubtree>>();
  }
  ImmIdTSubtree(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSubtree>> const& ptr) : Napi::ObjectWrap<ImmIdTSubtree>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSubtree>> _stored;
  org::imm::ImmIdT<org::imm::ImmSubtree>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTSubtree> {
  using type = org::imm::ImmIdT<org::imm::ImmSubtree>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmSubtree>> {
  using type = ImmIdTSubtree;
};

struct ImmIdTCell : public Napi::ObjectWrap<ImmIdTCell> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCell", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCell", func);
    return exports;
  }
  ImmIdTCell(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCell>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCell>>();
  }
  ImmIdTCell(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCell>> const& ptr) : Napi::ObjectWrap<ImmIdTCell>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCell>> _stored;
  org::imm::ImmIdT<org::imm::ImmCell>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCell> {
  using type = org::imm::ImmIdT<org::imm::ImmCell>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCell>> {
  using type = ImmIdTCell;
};

struct ImmIdTRow : public Napi::ObjectWrap<ImmIdTRow> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTRow", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTRow", func);
    return exports;
  }
  ImmIdTRow(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTRow>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmRow>>();
  }
  ImmIdTRow(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmRow>> const& ptr) : Napi::ObjectWrap<ImmIdTRow>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmRow>> _stored;
  org::imm::ImmIdT<org::imm::ImmRow>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTRow> {
  using type = org::imm::ImmIdT<org::imm::ImmRow>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmRow>> {
  using type = ImmIdTRow;
};

struct ImmIdTTable : public Napi::ObjectWrap<ImmIdTTable> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTTable", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTTable", func);
    return exports;
  }
  ImmIdTTable(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTTable>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmTable>>();
  }
  ImmIdTTable(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTable>> const& ptr) : Napi::ObjectWrap<ImmIdTTable>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTable>> _stored;
  org::imm::ImmIdT<org::imm::ImmTable>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTTable> {
  using type = org::imm::ImmIdT<org::imm::ImmTable>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmTable>> {
  using type = ImmIdTTable;
};

struct ImmIdTParagraph : public Napi::ObjectWrap<ImmIdTParagraph> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTParagraph", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTParagraph", func);
    return exports;
  }
  ImmIdTParagraph(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTParagraph>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmParagraph>>();
  }
  ImmIdTParagraph(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmParagraph>> const& ptr) : Napi::ObjectWrap<ImmIdTParagraph>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmParagraph>> _stored;
  org::imm::ImmIdT<org::imm::ImmParagraph>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTParagraph> {
  using type = org::imm::ImmIdT<org::imm::ImmParagraph>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmParagraph>> {
  using type = ImmIdTParagraph;
};

struct ImmIdTColonExample : public Napi::ObjectWrap<ImmIdTColonExample> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTColonExample", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTColonExample", func);
    return exports;
  }
  ImmIdTColonExample(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTColonExample>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmColonExample>>();
  }
  ImmIdTColonExample(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmColonExample>> const& ptr) : Napi::ObjectWrap<ImmIdTColonExample>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmColonExample>> _stored;
  org::imm::ImmIdT<org::imm::ImmColonExample>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTColonExample> {
  using type = org::imm::ImmIdT<org::imm::ImmColonExample>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmColonExample>> {
  using type = ImmIdTColonExample;
};

struct ImmIdTCmdAttr : public Napi::ObjectWrap<ImmIdTCmdAttr> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdAttr", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCmdAttr", func);
    return exports;
  }
  ImmIdTCmdAttr(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCmdAttr>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCmdAttr>>();
  }
  ImmIdTCmdAttr(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdAttr>> const& ptr) : Napi::ObjectWrap<ImmIdTCmdAttr>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdAttr>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdAttr>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCmdAttr> {
  using type = org::imm::ImmIdT<org::imm::ImmCmdAttr>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCmdAttr>> {
  using type = ImmIdTCmdAttr;
};

struct ImmIdTCmdExport : public Napi::ObjectWrap<ImmIdTCmdExport> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdExport", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCmdExport", func);
    return exports;
  }
  ImmIdTCmdExport(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCmdExport>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCmdExport>>();
  }
  ImmIdTCmdExport(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdExport>> const& ptr) : Napi::ObjectWrap<ImmIdTCmdExport>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdExport>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdExport>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCmdExport> {
  using type = org::imm::ImmIdT<org::imm::ImmCmdExport>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCmdExport>> {
  using type = ImmIdTCmdExport;
};

struct ImmIdTCall : public Napi::ObjectWrap<ImmIdTCall> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCall", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCall", func);
    return exports;
  }
  ImmIdTCall(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCall>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCall>>();
  }
  ImmIdTCall(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCall>> const& ptr) : Napi::ObjectWrap<ImmIdTCall>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCall>> _stored;
  org::imm::ImmIdT<org::imm::ImmCall>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCall> {
  using type = org::imm::ImmIdT<org::imm::ImmCall>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCall>> {
  using type = ImmIdTCall;
};

struct ImmIdTList : public Napi::ObjectWrap<ImmIdTList> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTList", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTList", func);
    return exports;
  }
  ImmIdTList(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTList>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmList>>();
  }
  ImmIdTList(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmList>> const& ptr) : Napi::ObjectWrap<ImmIdTList>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmList>> _stored;
  org::imm::ImmIdT<org::imm::ImmList>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTList> {
  using type = org::imm::ImmIdT<org::imm::ImmList>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmList>> {
  using type = ImmIdTList;
};

struct ImmIdTListItem : public Napi::ObjectWrap<ImmIdTListItem> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTListItem", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTListItem", func);
    return exports;
  }
  ImmIdTListItem(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTListItem>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmListItem>>();
  }
  ImmIdTListItem(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmListItem>> const& ptr) : Napi::ObjectWrap<ImmIdTListItem>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmListItem>> _stored;
  org::imm::ImmIdT<org::imm::ImmListItem>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTListItem> {
  using type = org::imm::ImmIdT<org::imm::ImmListItem>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmListItem>> {
  using type = ImmIdTListItem;
};

struct ImmIdTDocumentOptions : public Napi::ObjectWrap<ImmIdTDocumentOptions> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTDocumentOptions", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTDocumentOptions", func);
    return exports;
  }
  ImmIdTDocumentOptions(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTDocumentOptions>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmDocumentOptions>>();
  }
  ImmIdTDocumentOptions(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDocumentOptions>> const& ptr) : Napi::ObjectWrap<ImmIdTDocumentOptions>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDocumentOptions>> _stored;
  org::imm::ImmIdT<org::imm::ImmDocumentOptions>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTDocumentOptions> {
  using type = org::imm::ImmIdT<org::imm::ImmDocumentOptions>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmDocumentOptions>> {
  using type = ImmIdTDocumentOptions;
};

struct ImmIdTDocumentFragment : public Napi::ObjectWrap<ImmIdTDocumentFragment> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTDocumentFragment", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTDocumentFragment", func);
    return exports;
  }
  ImmIdTDocumentFragment(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTDocumentFragment>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmDocumentFragment>>();
  }
  ImmIdTDocumentFragment(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDocumentFragment>> const& ptr) : Napi::ObjectWrap<ImmIdTDocumentFragment>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDocumentFragment>> _stored;
  org::imm::ImmIdT<org::imm::ImmDocumentFragment>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTDocumentFragment> {
  using type = org::imm::ImmIdT<org::imm::ImmDocumentFragment>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmDocumentFragment>> {
  using type = ImmIdTDocumentFragment;
};

struct ImmIdTCriticMarkup : public Napi::ObjectWrap<ImmIdTCriticMarkup> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCriticMarkup", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCriticMarkup", func);
    return exports;
  }
  ImmIdTCriticMarkup(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCriticMarkup>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCriticMarkup>>();
  }
  ImmIdTCriticMarkup(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCriticMarkup>> const& ptr) : Napi::ObjectWrap<ImmIdTCriticMarkup>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCriticMarkup>> _stored;
  org::imm::ImmIdT<org::imm::ImmCriticMarkup>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCriticMarkup> {
  using type = org::imm::ImmIdT<org::imm::ImmCriticMarkup>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCriticMarkup>> {
  using type = ImmIdTCriticMarkup;
};

struct ImmIdTDocument : public Napi::ObjectWrap<ImmIdTDocument> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTDocument", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTDocument", func);
    return exports;
  }
  ImmIdTDocument(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTDocument>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmDocument>>();
  }
  ImmIdTDocument(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDocument>> const& ptr) : Napi::ObjectWrap<ImmIdTDocument>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDocument>> _stored;
  org::imm::ImmIdT<org::imm::ImmDocument>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTDocument> {
  using type = org::imm::ImmIdT<org::imm::ImmDocument>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmDocument>> {
  using type = ImmIdTDocument;
};

struct ImmIdTFileTarget : public Napi::ObjectWrap<ImmIdTFileTarget> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTFileTarget", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTFileTarget", func);
    return exports;
  }
  ImmIdTFileTarget(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTFileTarget>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmFileTarget>>();
  }
  ImmIdTFileTarget(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmFileTarget>> const& ptr) : Napi::ObjectWrap<ImmIdTFileTarget>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmFileTarget>> _stored;
  org::imm::ImmIdT<org::imm::ImmFileTarget>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTFileTarget> {
  using type = org::imm::ImmIdT<org::imm::ImmFileTarget>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmFileTarget>> {
  using type = ImmIdTFileTarget;
};

struct ImmIdTTextSeparator : public Napi::ObjectWrap<ImmIdTTextSeparator> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTTextSeparator", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTTextSeparator", func);
    return exports;
  }
  ImmIdTTextSeparator(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTTextSeparator>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmTextSeparator>>();
  }
  ImmIdTTextSeparator(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTextSeparator>> const& ptr) : Napi::ObjectWrap<ImmIdTTextSeparator>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTextSeparator>> _stored;
  org::imm::ImmIdT<org::imm::ImmTextSeparator>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTTextSeparator> {
  using type = org::imm::ImmIdT<org::imm::ImmTextSeparator>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmTextSeparator>> {
  using type = ImmIdTTextSeparator;
};

struct ImmIdTDocumentGroup : public Napi::ObjectWrap<ImmIdTDocumentGroup> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTDocumentGroup", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTDocumentGroup", func);
    return exports;
  }
  ImmIdTDocumentGroup(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTDocumentGroup>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmDocumentGroup>>();
  }
  ImmIdTDocumentGroup(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDocumentGroup>> const& ptr) : Napi::ObjectWrap<ImmIdTDocumentGroup>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDocumentGroup>> _stored;
  org::imm::ImmIdT<org::imm::ImmDocumentGroup>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTDocumentGroup> {
  using type = org::imm::ImmIdT<org::imm::ImmDocumentGroup>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmDocumentGroup>> {
  using type = ImmIdTDocumentGroup;
};

struct ImmIdTFile : public Napi::ObjectWrap<ImmIdTFile> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTFile", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTFile", func);
    return exports;
  }
  ImmIdTFile(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTFile>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmFile>>();
  }
  ImmIdTFile(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmFile>> const& ptr) : Napi::ObjectWrap<ImmIdTFile>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmFile>> _stored;
  org::imm::ImmIdT<org::imm::ImmFile>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTFile> {
  using type = org::imm::ImmIdT<org::imm::ImmFile>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmFile>> {
  using type = ImmIdTFile;
};

struct ImmIdTDirectory : public Napi::ObjectWrap<ImmIdTDirectory> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTDirectory", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTDirectory", func);
    return exports;
  }
  ImmIdTDirectory(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTDirectory>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmDirectory>>();
  }
  ImmIdTDirectory(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDirectory>> const& ptr) : Napi::ObjectWrap<ImmIdTDirectory>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDirectory>> _stored;
  org::imm::ImmIdT<org::imm::ImmDirectory>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTDirectory> {
  using type = org::imm::ImmIdT<org::imm::ImmDirectory>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmDirectory>> {
  using type = ImmIdTDirectory;
};

struct ImmIdTSymlink : public Napi::ObjectWrap<ImmIdTSymlink> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTSymlink", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTSymlink", func);
    return exports;
  }
  ImmIdTSymlink(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTSymlink>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmSymlink>>();
  }
  ImmIdTSymlink(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSymlink>> const& ptr) : Napi::ObjectWrap<ImmIdTSymlink>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSymlink>> _stored;
  org::imm::ImmIdT<org::imm::ImmSymlink>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTSymlink> {
  using type = org::imm::ImmIdT<org::imm::ImmSymlink>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmSymlink>> {
  using type = ImmIdTSymlink;
};

struct ImmIdTCmdInclude : public Napi::ObjectWrap<ImmIdTCmdInclude> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdInclude", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdTCmdInclude", func);
    return exports;
  }
  ImmIdTCmdInclude(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmIdTCmdInclude>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::imm::ImmIdT<org::imm::ImmCmdInclude>>();
  }
  ImmIdTCmdInclude(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdInclude>> const& ptr) : Napi::ObjectWrap<ImmIdTCmdInclude>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdInclude>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdInclude>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmIdTCmdInclude> {
  using type = org::imm::ImmIdT<org::imm::ImmCmdInclude>;
};

template <>
struct org_to_js_type<org::imm::ImmIdT<org::imm::ImmCmdInclude>> {
  using type = ImmIdTCmdInclude;
};

struct ImmNoneValueJs : public Napi::ObjectWrap<ImmNoneValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNoneValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNoneValueJs", func);
    return exports;
  }
  ImmNoneValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmNoneValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmNoneValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmNoneValue> const& ptr) : Napi::ObjectWrap<ImmNoneValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmNoneValue> _stored;
  org::imm::ImmNoneValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmNoneValueJs> {
  using type = org::imm::ImmNoneValue;
};

template <>
struct org_to_js_type<org::imm::ImmNoneValue> {
  using type = ImmNoneValueJs;
};

struct ImmErrorItemValueJs : public Napi::ObjectWrap<ImmErrorItemValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorItemValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorItemValueJs", func);
    return exports;
  }
  ImmErrorItemValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmErrorItemValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmErrorItemValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmErrorItemValue> const& ptr) : Napi::ObjectWrap<ImmErrorItemValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmErrorItemValue> _stored;
  org::imm::ImmErrorItemValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmErrorItemValueJs> {
  using type = org::imm::ImmErrorItemValue;
};

template <>
struct org_to_js_type<org::imm::ImmErrorItemValue> {
  using type = ImmErrorItemValueJs;
};

struct ImmErrorGroupValueJs : public Napi::ObjectWrap<ImmErrorGroupValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorGroupValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorGroupValueJs", func);
    return exports;
  }
  ImmErrorGroupValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmErrorGroupValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmErrorGroupValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmErrorGroupValue> const& ptr) : Napi::ObjectWrap<ImmErrorGroupValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmErrorGroupValue> _stored;
  org::imm::ImmErrorGroupValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmErrorGroupValueJs> {
  using type = org::imm::ImmErrorGroupValue;
};

template <>
struct org_to_js_type<org::imm::ImmErrorGroupValue> {
  using type = ImmErrorGroupValueJs;
};

struct ImmStmtListValueJs : public Napi::ObjectWrap<ImmStmtListValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStmtListValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStmtListValueJs", func);
    return exports;
  }
  ImmStmtListValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmStmtListValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmStmtListValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmStmtListValue> const& ptr) : Napi::ObjectWrap<ImmStmtListValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmStmtListValue> _stored;
  org::imm::ImmStmtListValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmStmtListValueJs> {
  using type = org::imm::ImmStmtListValue;
};

template <>
struct org_to_js_type<org::imm::ImmStmtListValue> {
  using type = ImmStmtListValueJs;
};

struct ImmEmptyValueJs : public Napi::ObjectWrap<ImmEmptyValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEmptyValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEmptyValueJs", func);
    return exports;
  }
  ImmEmptyValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmEmptyValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmEmptyValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmEmptyValue> const& ptr) : Napi::ObjectWrap<ImmEmptyValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmEmptyValue> _stored;
  org::imm::ImmEmptyValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmEmptyValueJs> {
  using type = org::imm::ImmEmptyValue;
};

template <>
struct org_to_js_type<org::imm::ImmEmptyValue> {
  using type = ImmEmptyValueJs;
};

struct ImmCmdCaptionValueJs : public Napi::ObjectWrap<ImmCmdCaptionValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCaptionValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCaptionValueJs", func);
    return exports;
  }
  ImmCmdCaptionValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCaptionValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCaptionValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdCaptionValue> const& ptr) : Napi::ObjectWrap<ImmCmdCaptionValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdCaptionValue> _stored;
  org::imm::ImmCmdCaptionValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCaptionValueJs> {
  using type = org::imm::ImmCmdCaptionValue;
};

template <>
struct org_to_js_type<org::imm::ImmCmdCaptionValue> {
  using type = ImmCmdCaptionValueJs;
};

struct ImmCmdColumnsValueJs : public Napi::ObjectWrap<ImmCmdColumnsValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdColumnsValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdColumnsValueJs", func);
    return exports;
  }
  ImmCmdColumnsValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdColumnsValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdColumnsValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdColumnsValue> const& ptr) : Napi::ObjectWrap<ImmCmdColumnsValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdColumnsValue> _stored;
  org::imm::ImmCmdColumnsValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdColumnsValueJs> {
  using type = org::imm::ImmCmdColumnsValue;
};

template <>
struct org_to_js_type<org::imm::ImmCmdColumnsValue> {
  using type = ImmCmdColumnsValueJs;
};

struct ImmCmdNameValueJs : public Napi::ObjectWrap<ImmCmdNameValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdNameValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdNameValueJs", func);
    return exports;
  }
  ImmCmdNameValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdNameValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdNameValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdNameValue> const& ptr) : Napi::ObjectWrap<ImmCmdNameValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdNameValue> _stored;
  org::imm::ImmCmdNameValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdNameValueJs> {
  using type = org::imm::ImmCmdNameValue;
};

template <>
struct org_to_js_type<org::imm::ImmCmdNameValue> {
  using type = ImmCmdNameValueJs;
};

struct ImmCmdCustomArgsValueJs : public Napi::ObjectWrap<ImmCmdCustomArgsValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomArgsValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomArgsValueJs", func);
    return exports;
  }
  ImmCmdCustomArgsValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomArgsValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCustomArgsValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdCustomArgsValue> const& ptr) : Napi::ObjectWrap<ImmCmdCustomArgsValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdCustomArgsValue> _stored;
  org::imm::ImmCmdCustomArgsValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCustomArgsValueJs> {
  using type = org::imm::ImmCmdCustomArgsValue;
};

template <>
struct org_to_js_type<org::imm::ImmCmdCustomArgsValue> {
  using type = ImmCmdCustomArgsValueJs;
};

struct ImmCmdCustomRawValueJs : public Napi::ObjectWrap<ImmCmdCustomRawValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomRawValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomRawValueJs", func);
    return exports;
  }
  ImmCmdCustomRawValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomRawValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCustomRawValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdCustomRawValue> const& ptr) : Napi::ObjectWrap<ImmCmdCustomRawValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdCustomRawValue> _stored;
  org::imm::ImmCmdCustomRawValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCustomRawValueJs> {
  using type = org::imm::ImmCmdCustomRawValue;
};

template <>
struct org_to_js_type<org::imm::ImmCmdCustomRawValue> {
  using type = ImmCmdCustomRawValueJs;
};

struct ImmCmdCustomTextValueJs : public Napi::ObjectWrap<ImmCmdCustomTextValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomTextValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomTextValueJs", func);
    return exports;
  }
  ImmCmdCustomTextValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomTextValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCustomTextValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdCustomTextValue> const& ptr) : Napi::ObjectWrap<ImmCmdCustomTextValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdCustomTextValue> _stored;
  org::imm::ImmCmdCustomTextValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCustomTextValueJs> {
  using type = org::imm::ImmCmdCustomTextValue;
};

template <>
struct org_to_js_type<org::imm::ImmCmdCustomTextValue> {
  using type = ImmCmdCustomTextValueJs;
};

struct ImmCmdCallValueJs : public Napi::ObjectWrap<ImmCmdCallValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCallValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCallValueJs", func);
    return exports;
  }
  ImmCmdCallValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCallValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCallValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdCallValue> const& ptr) : Napi::ObjectWrap<ImmCmdCallValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdCallValue> _stored;
  org::imm::ImmCmdCallValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCallValueJs> {
  using type = org::imm::ImmCmdCallValue;
};

template <>
struct org_to_js_type<org::imm::ImmCmdCallValue> {
  using type = ImmCmdCallValueJs;
};

struct ImmCmdTblfmValueJs : public Napi::ObjectWrap<ImmCmdTblfmValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdTblfmValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdTblfmValueJs", func);
    return exports;
  }
  ImmCmdTblfmValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdTblfmValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdTblfmValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdTblfmValue> const& ptr) : Napi::ObjectWrap<ImmCmdTblfmValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdTblfmValue> _stored;
  org::imm::ImmCmdTblfmValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdTblfmValueJs> {
  using type = org::imm::ImmCmdTblfmValue;
};

template <>
struct org_to_js_type<org::imm::ImmCmdTblfmValue> {
  using type = ImmCmdTblfmValueJs;
};

struct ImmHashTagValueJs : public Napi::ObjectWrap<ImmHashTagValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmHashTagValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmHashTagValueJs", func);
    return exports;
  }
  ImmHashTagValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmHashTagValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmHashTagValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmHashTagValue> const& ptr) : Napi::ObjectWrap<ImmHashTagValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmHashTagValue> _stored;
  org::imm::ImmHashTagValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmHashTagValueJs> {
  using type = org::imm::ImmHashTagValue;
};

template <>
struct org_to_js_type<org::imm::ImmHashTagValue> {
  using type = ImmHashTagValueJs;
};

struct ImmInlineFootnoteValueJs : public Napi::ObjectWrap<ImmInlineFootnoteValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineFootnoteValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineFootnoteValueJs", func);
    return exports;
  }
  ImmInlineFootnoteValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmInlineFootnoteValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmInlineFootnoteValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmInlineFootnoteValue> const& ptr) : Napi::ObjectWrap<ImmInlineFootnoteValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmInlineFootnoteValue> _stored;
  org::imm::ImmInlineFootnoteValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmInlineFootnoteValueJs> {
  using type = org::imm::ImmInlineFootnoteValue;
};

template <>
struct org_to_js_type<org::imm::ImmInlineFootnoteValue> {
  using type = ImmInlineFootnoteValueJs;
};

struct ImmInlineExportValueJs : public Napi::ObjectWrap<ImmInlineExportValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineExportValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineExportValueJs", func);
    return exports;
  }
  ImmInlineExportValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmInlineExportValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmInlineExportValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmInlineExportValue> const& ptr) : Napi::ObjectWrap<ImmInlineExportValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmInlineExportValue> _stored;
  org::imm::ImmInlineExportValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmInlineExportValueJs> {
  using type = org::imm::ImmInlineExportValue;
};

template <>
struct org_to_js_type<org::imm::ImmInlineExportValue> {
  using type = ImmInlineExportValueJs;
};

struct ImmTimeValueJs : public Napi::ObjectWrap<ImmTimeValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeValueJs", func);
    return exports;
  }
  ImmTimeValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTimeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTimeValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmTimeValue> const& ptr) : Napi::ObjectWrap<ImmTimeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmTimeValue> _stored;
  org::imm::ImmTimeValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTimeValueJs> {
  using type = org::imm::ImmTimeValue;
};

template <>
struct org_to_js_type<org::imm::ImmTimeValue> {
  using type = ImmTimeValueJs;
};

struct ImmTimeRangeValueJs : public Napi::ObjectWrap<ImmTimeRangeValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeRangeValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeRangeValueJs", func);
    return exports;
  }
  ImmTimeRangeValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTimeRangeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTimeRangeValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmTimeRangeValue> const& ptr) : Napi::ObjectWrap<ImmTimeRangeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmTimeRangeValue> _stored;
  org::imm::ImmTimeRangeValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTimeRangeValueJs> {
  using type = org::imm::ImmTimeRangeValue;
};

template <>
struct org_to_js_type<org::imm::ImmTimeRangeValue> {
  using type = ImmTimeRangeValueJs;
};

struct ImmMacroValueJs : public Napi::ObjectWrap<ImmMacroValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMacroValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMacroValueJs", func);
    return exports;
  }
  ImmMacroValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMacroValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmMacroValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmMacroValue> const& ptr) : Napi::ObjectWrap<ImmMacroValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmMacroValue> _stored;
  org::imm::ImmMacroValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmMacroValueJs> {
  using type = org::imm::ImmMacroValue;
};

template <>
struct org_to_js_type<org::imm::ImmMacroValue> {
  using type = ImmMacroValueJs;
};

struct ImmSymbolValueJs : public Napi::ObjectWrap<ImmSymbolValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymbolValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymbolValueJs", func);
    return exports;
  }
  ImmSymbolValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSymbolValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSymbolValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmSymbolValue> const& ptr) : Napi::ObjectWrap<ImmSymbolValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmSymbolValue> _stored;
  org::imm::ImmSymbolValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSymbolValueJs> {
  using type = org::imm::ImmSymbolValue;
};

template <>
struct org_to_js_type<org::imm::ImmSymbolValue> {
  using type = ImmSymbolValueJs;
};

struct ImmEscapedValueJs : public Napi::ObjectWrap<ImmEscapedValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEscapedValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEscapedValueJs", func);
    return exports;
  }
  ImmEscapedValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmEscapedValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmEscapedValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmEscapedValue> const& ptr) : Napi::ObjectWrap<ImmEscapedValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmEscapedValue> _stored;
  org::imm::ImmEscapedValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmEscapedValueJs> {
  using type = org::imm::ImmEscapedValue;
};

template <>
struct org_to_js_type<org::imm::ImmEscapedValue> {
  using type = ImmEscapedValueJs;
};

struct ImmNewlineValueJs : public Napi::ObjectWrap<ImmNewlineValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNewlineValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNewlineValueJs", func);
    return exports;
  }
  ImmNewlineValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmNewlineValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmNewlineValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmNewlineValue> const& ptr) : Napi::ObjectWrap<ImmNewlineValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmNewlineValue> _stored;
  org::imm::ImmNewlineValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmNewlineValueJs> {
  using type = org::imm::ImmNewlineValue;
};

template <>
struct org_to_js_type<org::imm::ImmNewlineValue> {
  using type = ImmNewlineValueJs;
};

struct ImmSpaceValueJs : public Napi::ObjectWrap<ImmSpaceValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSpaceValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSpaceValueJs", func);
    return exports;
  }
  ImmSpaceValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSpaceValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSpaceValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmSpaceValue> const& ptr) : Napi::ObjectWrap<ImmSpaceValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmSpaceValue> _stored;
  org::imm::ImmSpaceValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSpaceValueJs> {
  using type = org::imm::ImmSpaceValue;
};

template <>
struct org_to_js_type<org::imm::ImmSpaceValue> {
  using type = ImmSpaceValueJs;
};

struct ImmWordValueJs : public Napi::ObjectWrap<ImmWordValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmWordValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmWordValueJs", func);
    return exports;
  }
  ImmWordValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmWordValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmWordValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmWordValue> const& ptr) : Napi::ObjectWrap<ImmWordValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmWordValue> _stored;
  org::imm::ImmWordValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmWordValueJs> {
  using type = org::imm::ImmWordValue;
};

template <>
struct org_to_js_type<org::imm::ImmWordValue> {
  using type = ImmWordValueJs;
};

struct ImmAtMentionValueJs : public Napi::ObjectWrap<ImmAtMentionValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAtMentionValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAtMentionValueJs", func);
    return exports;
  }
  ImmAtMentionValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmAtMentionValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmAtMentionValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAtMentionValue> const& ptr) : Napi::ObjectWrap<ImmAtMentionValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAtMentionValue> _stored;
  org::imm::ImmAtMentionValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmAtMentionValueJs> {
  using type = org::imm::ImmAtMentionValue;
};

template <>
struct org_to_js_type<org::imm::ImmAtMentionValue> {
  using type = ImmAtMentionValueJs;
};

struct ImmRawTextValueJs : public Napi::ObjectWrap<ImmRawTextValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRawTextValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRawTextValueJs", func);
    return exports;
  }
  ImmRawTextValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRawTextValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmRawTextValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmRawTextValue> const& ptr) : Napi::ObjectWrap<ImmRawTextValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmRawTextValue> _stored;
  org::imm::ImmRawTextValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmRawTextValueJs> {
  using type = org::imm::ImmRawTextValue;
};

template <>
struct org_to_js_type<org::imm::ImmRawTextValue> {
  using type = ImmRawTextValueJs;
};

struct ImmPunctuationValueJs : public Napi::ObjectWrap<ImmPunctuationValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPunctuationValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPunctuationValueJs", func);
    return exports;
  }
  ImmPunctuationValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPunctuationValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmPunctuationValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmPunctuationValue> const& ptr) : Napi::ObjectWrap<ImmPunctuationValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmPunctuationValue> _stored;
  org::imm::ImmPunctuationValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmPunctuationValueJs> {
  using type = org::imm::ImmPunctuationValue;
};

template <>
struct org_to_js_type<org::imm::ImmPunctuationValue> {
  using type = ImmPunctuationValueJs;
};

struct ImmPlaceholderValueJs : public Napi::ObjectWrap<ImmPlaceholderValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPlaceholderValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPlaceholderValueJs", func);
    return exports;
  }
  ImmPlaceholderValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPlaceholderValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmPlaceholderValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmPlaceholderValue> const& ptr) : Napi::ObjectWrap<ImmPlaceholderValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmPlaceholderValue> _stored;
  org::imm::ImmPlaceholderValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmPlaceholderValueJs> {
  using type = org::imm::ImmPlaceholderValue;
};

template <>
struct org_to_js_type<org::imm::ImmPlaceholderValue> {
  using type = ImmPlaceholderValueJs;
};

struct ImmBigIdentValueJs : public Napi::ObjectWrap<ImmBigIdentValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBigIdentValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBigIdentValueJs", func);
    return exports;
  }
  ImmBigIdentValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBigIdentValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBigIdentValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBigIdentValue> const& ptr) : Napi::ObjectWrap<ImmBigIdentValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBigIdentValue> _stored;
  org::imm::ImmBigIdentValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBigIdentValueJs> {
  using type = org::imm::ImmBigIdentValue;
};

template <>
struct org_to_js_type<org::imm::ImmBigIdentValue> {
  using type = ImmBigIdentValueJs;
};

struct ImmTextTargetValueJs : public Napi::ObjectWrap<ImmTextTargetValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextTargetValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextTargetValueJs", func);
    return exports;
  }
  ImmTextTargetValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTextTargetValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTextTargetValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmTextTargetValue> const& ptr) : Napi::ObjectWrap<ImmTextTargetValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmTextTargetValue> _stored;
  org::imm::ImmTextTargetValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTextTargetValueJs> {
  using type = org::imm::ImmTextTargetValue;
};

template <>
struct org_to_js_type<org::imm::ImmTextTargetValue> {
  using type = ImmTextTargetValueJs;
};

struct ImmBoldValueJs : public Napi::ObjectWrap<ImmBoldValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBoldValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBoldValueJs", func);
    return exports;
  }
  ImmBoldValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBoldValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBoldValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBoldValue> const& ptr) : Napi::ObjectWrap<ImmBoldValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBoldValue> _stored;
  org::imm::ImmBoldValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBoldValueJs> {
  using type = org::imm::ImmBoldValue;
};

template <>
struct org_to_js_type<org::imm::ImmBoldValue> {
  using type = ImmBoldValueJs;
};

struct ImmUnderlineValueJs : public Napi::ObjectWrap<ImmUnderlineValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmUnderlineValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmUnderlineValueJs", func);
    return exports;
  }
  ImmUnderlineValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmUnderlineValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmUnderlineValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmUnderlineValue> const& ptr) : Napi::ObjectWrap<ImmUnderlineValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmUnderlineValue> _stored;
  org::imm::ImmUnderlineValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmUnderlineValueJs> {
  using type = org::imm::ImmUnderlineValue;
};

template <>
struct org_to_js_type<org::imm::ImmUnderlineValue> {
  using type = ImmUnderlineValueJs;
};

struct ImmMonospaceValueJs : public Napi::ObjectWrap<ImmMonospaceValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMonospaceValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMonospaceValueJs", func);
    return exports;
  }
  ImmMonospaceValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMonospaceValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmMonospaceValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmMonospaceValue> const& ptr) : Napi::ObjectWrap<ImmMonospaceValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmMonospaceValue> _stored;
  org::imm::ImmMonospaceValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmMonospaceValueJs> {
  using type = org::imm::ImmMonospaceValue;
};

template <>
struct org_to_js_type<org::imm::ImmMonospaceValue> {
  using type = ImmMonospaceValueJs;
};

struct ImmMarkQuoteValueJs : public Napi::ObjectWrap<ImmMarkQuoteValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMarkQuoteValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMarkQuoteValueJs", func);
    return exports;
  }
  ImmMarkQuoteValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMarkQuoteValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmMarkQuoteValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmMarkQuoteValue> const& ptr) : Napi::ObjectWrap<ImmMarkQuoteValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmMarkQuoteValue> _stored;
  org::imm::ImmMarkQuoteValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmMarkQuoteValueJs> {
  using type = org::imm::ImmMarkQuoteValue;
};

template <>
struct org_to_js_type<org::imm::ImmMarkQuoteValue> {
  using type = ImmMarkQuoteValueJs;
};

struct ImmVerbatimValueJs : public Napi::ObjectWrap<ImmVerbatimValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmVerbatimValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmVerbatimValueJs", func);
    return exports;
  }
  ImmVerbatimValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmVerbatimValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmVerbatimValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmVerbatimValue> const& ptr) : Napi::ObjectWrap<ImmVerbatimValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmVerbatimValue> _stored;
  org::imm::ImmVerbatimValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmVerbatimValueJs> {
  using type = org::imm::ImmVerbatimValue;
};

template <>
struct org_to_js_type<org::imm::ImmVerbatimValue> {
  using type = ImmVerbatimValueJs;
};

struct ImmItalicValueJs : public Napi::ObjectWrap<ImmItalicValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmItalicValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmItalicValueJs", func);
    return exports;
  }
  ImmItalicValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmItalicValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmItalicValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmItalicValue> const& ptr) : Napi::ObjectWrap<ImmItalicValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmItalicValue> _stored;
  org::imm::ImmItalicValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmItalicValueJs> {
  using type = org::imm::ImmItalicValue;
};

template <>
struct org_to_js_type<org::imm::ImmItalicValue> {
  using type = ImmItalicValueJs;
};

struct ImmStrikeValueJs : public Napi::ObjectWrap<ImmStrikeValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStrikeValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStrikeValueJs", func);
    return exports;
  }
  ImmStrikeValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmStrikeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmStrikeValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmStrikeValue> const& ptr) : Napi::ObjectWrap<ImmStrikeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmStrikeValue> _stored;
  org::imm::ImmStrikeValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmStrikeValueJs> {
  using type = org::imm::ImmStrikeValue;
};

template <>
struct org_to_js_type<org::imm::ImmStrikeValue> {
  using type = ImmStrikeValueJs;
};

struct ImmParValueJs : public Napi::ObjectWrap<ImmParValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParValueJs", func);
    return exports;
  }
  ImmParValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmParValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmParValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmParValue> const& ptr) : Napi::ObjectWrap<ImmParValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmParValue> _stored;
  org::imm::ImmParValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmParValueJs> {
  using type = org::imm::ImmParValue;
};

template <>
struct org_to_js_type<org::imm::ImmParValue> {
  using type = ImmParValueJs;
};

struct ImmRadioTargetValueJs : public Napi::ObjectWrap<ImmRadioTargetValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRadioTargetValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRadioTargetValueJs", func);
    return exports;
  }
  ImmRadioTargetValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRadioTargetValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmRadioTargetValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmRadioTargetValue> const& ptr) : Napi::ObjectWrap<ImmRadioTargetValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmRadioTargetValue> _stored;
  org::imm::ImmRadioTargetValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmRadioTargetValueJs> {
  using type = org::imm::ImmRadioTargetValue;
};

template <>
struct org_to_js_type<org::imm::ImmRadioTargetValue> {
  using type = ImmRadioTargetValueJs;
};

struct ImmLatexValueJs : public Napi::ObjectWrap<ImmLatexValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLatexValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLatexValueJs", func);
    return exports;
  }
  ImmLatexValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmLatexValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmLatexValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmLatexValue> const& ptr) : Napi::ObjectWrap<ImmLatexValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmLatexValue> _stored;
  org::imm::ImmLatexValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmLatexValueJs> {
  using type = org::imm::ImmLatexValue;
};

template <>
struct org_to_js_type<org::imm::ImmLatexValue> {
  using type = ImmLatexValueJs;
};

struct ImmLinkValueJs : public Napi::ObjectWrap<ImmLinkValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLinkValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLinkValueJs", func);
    return exports;
  }
  ImmLinkValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmLinkValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmLinkValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmLinkValue> const& ptr) : Napi::ObjectWrap<ImmLinkValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmLinkValue> _stored;
  org::imm::ImmLinkValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmLinkValueJs> {
  using type = org::imm::ImmLinkValue;
};

template <>
struct org_to_js_type<org::imm::ImmLinkValue> {
  using type = ImmLinkValueJs;
};

struct ImmBlockCenterValueJs : public Napi::ObjectWrap<ImmBlockCenterValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCenterValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCenterValueJs", func);
    return exports;
  }
  ImmBlockCenterValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCenterValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockCenterValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockCenterValue> const& ptr) : Napi::ObjectWrap<ImmBlockCenterValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockCenterValue> _stored;
  org::imm::ImmBlockCenterValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockCenterValueJs> {
  using type = org::imm::ImmBlockCenterValue;
};

template <>
struct org_to_js_type<org::imm::ImmBlockCenterValue> {
  using type = ImmBlockCenterValueJs;
};

struct ImmBlockQuoteValueJs : public Napi::ObjectWrap<ImmBlockQuoteValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockQuoteValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockQuoteValueJs", func);
    return exports;
  }
  ImmBlockQuoteValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockQuoteValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockQuoteValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockQuoteValue> const& ptr) : Napi::ObjectWrap<ImmBlockQuoteValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockQuoteValue> _stored;
  org::imm::ImmBlockQuoteValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockQuoteValueJs> {
  using type = org::imm::ImmBlockQuoteValue;
};

template <>
struct org_to_js_type<org::imm::ImmBlockQuoteValue> {
  using type = ImmBlockQuoteValueJs;
};

struct ImmBlockCommentValueJs : public Napi::ObjectWrap<ImmBlockCommentValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCommentValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCommentValueJs", func);
    return exports;
  }
  ImmBlockCommentValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCommentValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockCommentValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockCommentValue> const& ptr) : Napi::ObjectWrap<ImmBlockCommentValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockCommentValue> _stored;
  org::imm::ImmBlockCommentValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockCommentValueJs> {
  using type = org::imm::ImmBlockCommentValue;
};

template <>
struct org_to_js_type<org::imm::ImmBlockCommentValue> {
  using type = ImmBlockCommentValueJs;
};

struct ImmBlockVerseValueJs : public Napi::ObjectWrap<ImmBlockVerseValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockVerseValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockVerseValueJs", func);
    return exports;
  }
  ImmBlockVerseValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockVerseValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockVerseValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockVerseValue> const& ptr) : Napi::ObjectWrap<ImmBlockVerseValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockVerseValue> _stored;
  org::imm::ImmBlockVerseValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockVerseValueJs> {
  using type = org::imm::ImmBlockVerseValue;
};

template <>
struct org_to_js_type<org::imm::ImmBlockVerseValue> {
  using type = ImmBlockVerseValueJs;
};

struct ImmBlockDynamicFallbackValueJs : public Napi::ObjectWrap<ImmBlockDynamicFallbackValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockDynamicFallbackValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockDynamicFallbackValueJs", func);
    return exports;
  }
  ImmBlockDynamicFallbackValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockDynamicFallbackValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockDynamicFallbackValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockDynamicFallbackValue> const& ptr) : Napi::ObjectWrap<ImmBlockDynamicFallbackValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockDynamicFallbackValue> _stored;
  org::imm::ImmBlockDynamicFallbackValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockDynamicFallbackValueJs> {
  using type = org::imm::ImmBlockDynamicFallbackValue;
};

template <>
struct org_to_js_type<org::imm::ImmBlockDynamicFallbackValue> {
  using type = ImmBlockDynamicFallbackValueJs;
};

struct ImmBlockExampleValueJs : public Napi::ObjectWrap<ImmBlockExampleValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExampleValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExampleValueJs", func);
    return exports;
  }
  ImmBlockExampleValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockExampleValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockExampleValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockExampleValue> const& ptr) : Napi::ObjectWrap<ImmBlockExampleValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockExampleValue> _stored;
  org::imm::ImmBlockExampleValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockExampleValueJs> {
  using type = org::imm::ImmBlockExampleValue;
};

template <>
struct org_to_js_type<org::imm::ImmBlockExampleValue> {
  using type = ImmBlockExampleValueJs;
};

struct ImmBlockExportValueJs : public Napi::ObjectWrap<ImmBlockExportValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExportValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExportValueJs", func);
    return exports;
  }
  ImmBlockExportValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockExportValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockExportValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockExportValue> const& ptr) : Napi::ObjectWrap<ImmBlockExportValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockExportValue> _stored;
  org::imm::ImmBlockExportValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockExportValueJs> {
  using type = org::imm::ImmBlockExportValue;
};

template <>
struct org_to_js_type<org::imm::ImmBlockExportValue> {
  using type = ImmBlockExportValueJs;
};

struct ImmBlockAdmonitionValueJs : public Napi::ObjectWrap<ImmBlockAdmonitionValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockAdmonitionValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockAdmonitionValueJs", func);
    return exports;
  }
  ImmBlockAdmonitionValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockAdmonitionValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockAdmonitionValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockAdmonitionValue> const& ptr) : Napi::ObjectWrap<ImmBlockAdmonitionValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockAdmonitionValue> _stored;
  org::imm::ImmBlockAdmonitionValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockAdmonitionValueJs> {
  using type = org::imm::ImmBlockAdmonitionValue;
};

template <>
struct org_to_js_type<org::imm::ImmBlockAdmonitionValue> {
  using type = ImmBlockAdmonitionValueJs;
};

struct ImmBlockCodeEvalResultValueJs : public Napi::ObjectWrap<ImmBlockCodeEvalResultValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeEvalResultValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeEvalResultValueJs", func);
    return exports;
  }
  ImmBlockCodeEvalResultValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCodeEvalResultValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockCodeEvalResultValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockCodeEvalResultValue> const& ptr) : Napi::ObjectWrap<ImmBlockCodeEvalResultValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockCodeEvalResultValue> _stored;
  org::imm::ImmBlockCodeEvalResultValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockCodeEvalResultValueJs> {
  using type = org::imm::ImmBlockCodeEvalResultValue;
};

template <>
struct org_to_js_type<org::imm::ImmBlockCodeEvalResultValue> {
  using type = ImmBlockCodeEvalResultValueJs;
};

struct ImmBlockCodeValueJs : public Napi::ObjectWrap<ImmBlockCodeValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeValueJs", func);
    return exports;
  }
  ImmBlockCodeValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCodeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockCodeValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmBlockCodeValue> const& ptr) : Napi::ObjectWrap<ImmBlockCodeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmBlockCodeValue> _stored;
  org::imm::ImmBlockCodeValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockCodeValueJs> {
  using type = org::imm::ImmBlockCodeValue;
};

template <>
struct org_to_js_type<org::imm::ImmBlockCodeValue> {
  using type = ImmBlockCodeValueJs;
};

struct ImmSubtreeLogValueJs : public Napi::ObjectWrap<ImmSubtreeLogValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeLogValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeLogValueJs", func);
    return exports;
  }
  ImmSubtreeLogValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSubtreeLogValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSubtreeLogValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmSubtreeLogValue> const& ptr) : Napi::ObjectWrap<ImmSubtreeLogValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmSubtreeLogValue> _stored;
  org::imm::ImmSubtreeLogValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSubtreeLogValueJs> {
  using type = org::imm::ImmSubtreeLogValue;
};

template <>
struct org_to_js_type<org::imm::ImmSubtreeLogValue> {
  using type = ImmSubtreeLogValueJs;
};

struct ImmSubtreeValueJs : public Napi::ObjectWrap<ImmSubtreeValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeValueJs", func);
    return exports;
  }
  ImmSubtreeValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSubtreeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSubtreeValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmSubtreeValue> const& ptr) : Napi::ObjectWrap<ImmSubtreeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmSubtreeValue> _stored;
  org::imm::ImmSubtreeValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSubtreeValueJs> {
  using type = org::imm::ImmSubtreeValue;
};

template <>
struct org_to_js_type<org::imm::ImmSubtreeValue> {
  using type = ImmSubtreeValueJs;
};

struct ImmCellValueJs : public Napi::ObjectWrap<ImmCellValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCellValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCellValueJs", func);
    return exports;
  }
  ImmCellValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCellValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCellValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCellValue> const& ptr) : Napi::ObjectWrap<ImmCellValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCellValue> _stored;
  org::imm::ImmCellValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCellValueJs> {
  using type = org::imm::ImmCellValue;
};

template <>
struct org_to_js_type<org::imm::ImmCellValue> {
  using type = ImmCellValueJs;
};

struct ImmRowValueJs : public Napi::ObjectWrap<ImmRowValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRowValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRowValueJs", func);
    return exports;
  }
  ImmRowValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRowValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmRowValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmRowValue> const& ptr) : Napi::ObjectWrap<ImmRowValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmRowValue> _stored;
  org::imm::ImmRowValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmRowValueJs> {
  using type = org::imm::ImmRowValue;
};

template <>
struct org_to_js_type<org::imm::ImmRowValue> {
  using type = ImmRowValueJs;
};

struct ImmTableValueJs : public Napi::ObjectWrap<ImmTableValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTableValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTableValueJs", func);
    return exports;
  }
  ImmTableValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTableValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTableValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmTableValue> const& ptr) : Napi::ObjectWrap<ImmTableValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmTableValue> _stored;
  org::imm::ImmTableValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTableValueJs> {
  using type = org::imm::ImmTableValue;
};

template <>
struct org_to_js_type<org::imm::ImmTableValue> {
  using type = ImmTableValueJs;
};

struct ImmParagraphValueJs : public Napi::ObjectWrap<ImmParagraphValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParagraphValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParagraphValueJs", func);
    return exports;
  }
  ImmParagraphValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmParagraphValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmParagraphValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmParagraphValue> const& ptr) : Napi::ObjectWrap<ImmParagraphValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmParagraphValue> _stored;
  org::imm::ImmParagraphValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmParagraphValueJs> {
  using type = org::imm::ImmParagraphValue;
};

template <>
struct org_to_js_type<org::imm::ImmParagraphValue> {
  using type = ImmParagraphValueJs;
};

struct ImmColonExampleValueJs : public Napi::ObjectWrap<ImmColonExampleValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmColonExampleValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmColonExampleValueJs", func);
    return exports;
  }
  ImmColonExampleValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmColonExampleValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmColonExampleValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmColonExampleValue> const& ptr) : Napi::ObjectWrap<ImmColonExampleValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmColonExampleValue> _stored;
  org::imm::ImmColonExampleValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmColonExampleValueJs> {
  using type = org::imm::ImmColonExampleValue;
};

template <>
struct org_to_js_type<org::imm::ImmColonExampleValue> {
  using type = ImmColonExampleValueJs;
};

struct ImmCmdAttrValueJs : public Napi::ObjectWrap<ImmCmdAttrValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdAttrValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdAttrValueJs", func);
    return exports;
  }
  ImmCmdAttrValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdAttrValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdAttrValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdAttrValue> const& ptr) : Napi::ObjectWrap<ImmCmdAttrValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdAttrValue> _stored;
  org::imm::ImmCmdAttrValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdAttrValueJs> {
  using type = org::imm::ImmCmdAttrValue;
};

template <>
struct org_to_js_type<org::imm::ImmCmdAttrValue> {
  using type = ImmCmdAttrValueJs;
};

struct ImmCmdExportValueJs : public Napi::ObjectWrap<ImmCmdExportValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdExportValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdExportValueJs", func);
    return exports;
  }
  ImmCmdExportValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdExportValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdExportValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdExportValue> const& ptr) : Napi::ObjectWrap<ImmCmdExportValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdExportValue> _stored;
  org::imm::ImmCmdExportValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdExportValueJs> {
  using type = org::imm::ImmCmdExportValue;
};

template <>
struct org_to_js_type<org::imm::ImmCmdExportValue> {
  using type = ImmCmdExportValueJs;
};

struct ImmCallValueJs : public Napi::ObjectWrap<ImmCallValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCallValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCallValueJs", func);
    return exports;
  }
  ImmCallValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCallValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCallValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCallValue> const& ptr) : Napi::ObjectWrap<ImmCallValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCallValue> _stored;
  org::imm::ImmCallValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCallValueJs> {
  using type = org::imm::ImmCallValue;
};

template <>
struct org_to_js_type<org::imm::ImmCallValue> {
  using type = ImmCallValueJs;
};

struct ImmListValueJs : public Napi::ObjectWrap<ImmListValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListValueJs", func);
    return exports;
  }
  ImmListValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmListValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmListValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmListValue> const& ptr) : Napi::ObjectWrap<ImmListValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmListValue> _stored;
  org::imm::ImmListValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmListValueJs> {
  using type = org::imm::ImmListValue;
};

template <>
struct org_to_js_type<org::imm::ImmListValue> {
  using type = ImmListValueJs;
};

struct ImmListItemValueJs : public Napi::ObjectWrap<ImmListItemValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListItemValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListItemValueJs", func);
    return exports;
  }
  ImmListItemValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmListItemValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmListItemValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmListItemValue> const& ptr) : Napi::ObjectWrap<ImmListItemValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmListItemValue> _stored;
  org::imm::ImmListItemValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmListItemValueJs> {
  using type = org::imm::ImmListItemValue;
};

template <>
struct org_to_js_type<org::imm::ImmListItemValue> {
  using type = ImmListItemValueJs;
};

struct ImmDocumentOptionsValueJs : public Napi::ObjectWrap<ImmDocumentOptionsValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentOptionsValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentOptionsValueJs", func);
    return exports;
  }
  ImmDocumentOptionsValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentOptionsValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDocumentOptionsValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmDocumentOptionsValue> const& ptr) : Napi::ObjectWrap<ImmDocumentOptionsValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmDocumentOptionsValue> _stored;
  org::imm::ImmDocumentOptionsValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDocumentOptionsValueJs> {
  using type = org::imm::ImmDocumentOptionsValue;
};

template <>
struct org_to_js_type<org::imm::ImmDocumentOptionsValue> {
  using type = ImmDocumentOptionsValueJs;
};

struct ImmDocumentFragmentValueJs : public Napi::ObjectWrap<ImmDocumentFragmentValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentFragmentValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentFragmentValueJs", func);
    return exports;
  }
  ImmDocumentFragmentValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentFragmentValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDocumentFragmentValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmDocumentFragmentValue> const& ptr) : Napi::ObjectWrap<ImmDocumentFragmentValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmDocumentFragmentValue> _stored;
  org::imm::ImmDocumentFragmentValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDocumentFragmentValueJs> {
  using type = org::imm::ImmDocumentFragmentValue;
};

template <>
struct org_to_js_type<org::imm::ImmDocumentFragmentValue> {
  using type = ImmDocumentFragmentValueJs;
};

struct ImmCriticMarkupValueJs : public Napi::ObjectWrap<ImmCriticMarkupValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCriticMarkupValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCriticMarkupValueJs", func);
    return exports;
  }
  ImmCriticMarkupValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCriticMarkupValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCriticMarkupValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCriticMarkupValue> const& ptr) : Napi::ObjectWrap<ImmCriticMarkupValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCriticMarkupValue> _stored;
  org::imm::ImmCriticMarkupValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCriticMarkupValueJs> {
  using type = org::imm::ImmCriticMarkupValue;
};

template <>
struct org_to_js_type<org::imm::ImmCriticMarkupValue> {
  using type = ImmCriticMarkupValueJs;
};

struct ImmDocumentValueJs : public Napi::ObjectWrap<ImmDocumentValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentValueJs", func);
    return exports;
  }
  ImmDocumentValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDocumentValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmDocumentValue> const& ptr) : Napi::ObjectWrap<ImmDocumentValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmDocumentValue> _stored;
  org::imm::ImmDocumentValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDocumentValueJs> {
  using type = org::imm::ImmDocumentValue;
};

template <>
struct org_to_js_type<org::imm::ImmDocumentValue> {
  using type = ImmDocumentValueJs;
};

struct ImmFileTargetValueJs : public Napi::ObjectWrap<ImmFileTargetValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileTargetValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileTargetValueJs", func);
    return exports;
  }
  ImmFileTargetValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmFileTargetValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmFileTargetValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmFileTargetValue> const& ptr) : Napi::ObjectWrap<ImmFileTargetValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmFileTargetValue> _stored;
  org::imm::ImmFileTargetValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmFileTargetValueJs> {
  using type = org::imm::ImmFileTargetValue;
};

template <>
struct org_to_js_type<org::imm::ImmFileTargetValue> {
  using type = ImmFileTargetValueJs;
};

struct ImmTextSeparatorValueJs : public Napi::ObjectWrap<ImmTextSeparatorValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextSeparatorValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextSeparatorValueJs", func);
    return exports;
  }
  ImmTextSeparatorValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTextSeparatorValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTextSeparatorValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmTextSeparatorValue> const& ptr) : Napi::ObjectWrap<ImmTextSeparatorValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmTextSeparatorValue> _stored;
  org::imm::ImmTextSeparatorValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTextSeparatorValueJs> {
  using type = org::imm::ImmTextSeparatorValue;
};

template <>
struct org_to_js_type<org::imm::ImmTextSeparatorValue> {
  using type = ImmTextSeparatorValueJs;
};

struct ImmDocumentGroupValueJs : public Napi::ObjectWrap<ImmDocumentGroupValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentGroupValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentGroupValueJs", func);
    return exports;
  }
  ImmDocumentGroupValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentGroupValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDocumentGroupValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmDocumentGroupValue> const& ptr) : Napi::ObjectWrap<ImmDocumentGroupValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmDocumentGroupValue> _stored;
  org::imm::ImmDocumentGroupValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDocumentGroupValueJs> {
  using type = org::imm::ImmDocumentGroupValue;
};

template <>
struct org_to_js_type<org::imm::ImmDocumentGroupValue> {
  using type = ImmDocumentGroupValueJs;
};

struct ImmFileValueJs : public Napi::ObjectWrap<ImmFileValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileValueJs", func);
    return exports;
  }
  ImmFileValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmFileValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmFileValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmFileValue> const& ptr) : Napi::ObjectWrap<ImmFileValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmFileValue> _stored;
  org::imm::ImmFileValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmFileValueJs> {
  using type = org::imm::ImmFileValue;
};

template <>
struct org_to_js_type<org::imm::ImmFileValue> {
  using type = ImmFileValueJs;
};

struct ImmDirectoryValueJs : public Napi::ObjectWrap<ImmDirectoryValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDirectoryValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDirectoryValueJs", func);
    return exports;
  }
  ImmDirectoryValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDirectoryValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDirectoryValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmDirectoryValue> const& ptr) : Napi::ObjectWrap<ImmDirectoryValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmDirectoryValue> _stored;
  org::imm::ImmDirectoryValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDirectoryValueJs> {
  using type = org::imm::ImmDirectoryValue;
};

template <>
struct org_to_js_type<org::imm::ImmDirectoryValue> {
  using type = ImmDirectoryValueJs;
};

struct ImmSymlinkValueJs : public Napi::ObjectWrap<ImmSymlinkValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymlinkValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymlinkValueJs", func);
    return exports;
  }
  ImmSymlinkValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSymlinkValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSymlinkValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmSymlinkValue> const& ptr) : Napi::ObjectWrap<ImmSymlinkValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmSymlinkValue> _stored;
  org::imm::ImmSymlinkValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSymlinkValueJs> {
  using type = org::imm::ImmSymlinkValue;
};

template <>
struct org_to_js_type<org::imm::ImmSymlinkValue> {
  using type = ImmSymlinkValueJs;
};

struct ImmCmdIncludeValueJs : public Napi::ObjectWrap<ImmCmdIncludeValueJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdIncludeValueJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdIncludeValueJs", func);
    return exports;
  }
  ImmCmdIncludeValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdIncludeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdIncludeValueJs(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmCmdIncludeValue> const& ptr) : Napi::ObjectWrap<ImmCmdIncludeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmCmdIncludeValue> _stored;
  org::imm::ImmCmdIncludeValue* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdIncludeValueJs> {
  using type = org::imm::ImmCmdIncludeValue;
};

template <>
struct org_to_js_type<org::imm::ImmCmdIncludeValue> {
  using type = ImmCmdIncludeValueJs;
};

struct CmdCustomRawJs : public Napi::ObjectWrap<CmdCustomRawJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCustomRawJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdCustomRawJs", func);
    return exports;
  }
  CmdCustomRawJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CmdCustomRawJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::CmdCustomRaw>();
  }
  CmdCustomRawJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::CmdCustomRaw> const& ptr) : Napi::ObjectWrap<CmdCustomRawJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::CmdCustomRaw> _stored;
  org::sem::CmdCustomRaw* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CmdCustomRawJs> {
  using type = org::sem::CmdCustomRaw;
};

template <>
struct org_to_js_type<org::sem::CmdCustomRaw> {
  using type = CmdCustomRawJs;
};

struct CmdCustomTextJs : public Napi::ObjectWrap<CmdCustomTextJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCustomTextJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdCustomTextJs", func);
    return exports;
  }
  CmdCustomTextJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CmdCustomTextJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::CmdCustomText>();
  }
  CmdCustomTextJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::CmdCustomText> const& ptr) : Napi::ObjectWrap<CmdCustomTextJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::CmdCustomText> _stored;
  org::sem::CmdCustomText* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CmdCustomTextJs> {
  using type = org::sem::CmdCustomText;
};

template <>
struct org_to_js_type<org::sem::CmdCustomText> {
  using type = CmdCustomTextJs;
};

struct LinkJs : public Napi::ObjectWrap<LinkJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LinkJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("LinkJs", func);
    return exports;
  }
  LinkJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<LinkJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Link>();
  }
  LinkJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Link> const& ptr) : Napi::ObjectWrap<LinkJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Link> _stored;
  org::sem::Link* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<LinkJs> {
  using type = org::sem::Link;
};

template <>
struct org_to_js_type<org::sem::Link> {
  using type = LinkJs;
};

struct BlockCommentJs : public Napi::ObjectWrap<BlockCommentJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCommentJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockCommentJs", func);
    return exports;
  }
  BlockCommentJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BlockCommentJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::BlockComment>();
  }
  BlockCommentJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::BlockComment> const& ptr) : Napi::ObjectWrap<BlockCommentJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::BlockComment> _stored;
  org::sem::BlockComment* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BlockCommentJs> {
  using type = org::sem::BlockComment;
};

template <>
struct org_to_js_type<org::sem::BlockComment> {
  using type = BlockCommentJs;
};

struct ParagraphJs : public Napi::ObjectWrap<ParagraphJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ParagraphJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ParagraphJs", func);
    return exports;
  }
  ParagraphJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ParagraphJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Paragraph>();
  }
  ParagraphJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Paragraph> const& ptr) : Napi::ObjectWrap<ParagraphJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Paragraph> _stored;
  org::sem::Paragraph* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ParagraphJs> {
  using type = org::sem::Paragraph;
};

template <>
struct org_to_js_type<org::sem::Paragraph> {
  using type = ParagraphJs;
};

struct ListJs : public Napi::ObjectWrap<ListJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ListJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ListJs", func);
    return exports;
  }
  ListJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ListJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::List>();
  }
  ListJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::List> const& ptr) : Napi::ObjectWrap<ListJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::List> _stored;
  org::sem::List* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ListJs> {
  using type = org::sem::List;
};

template <>
struct org_to_js_type<org::sem::List> {
  using type = ListJs;
};

struct HashTagJs : public Napi::ObjectWrap<HashTagJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "HashTagJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("HashTagJs", func);
    return exports;
  }
  HashTagJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<HashTagJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::HashTag>();
  }
  HashTagJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::HashTag> const& ptr) : Napi::ObjectWrap<HashTagJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::HashTag> _stored;
  org::sem::HashTag* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<HashTagJs> {
  using type = org::sem::HashTag;
};

template <>
struct org_to_js_type<org::sem::HashTag> {
  using type = HashTagJs;
};

struct InlineFootnoteJs : public Napi::ObjectWrap<InlineFootnoteJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "InlineFootnoteJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("InlineFootnoteJs", func);
    return exports;
  }
  InlineFootnoteJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<InlineFootnoteJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::InlineFootnote>();
  }
  InlineFootnoteJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::InlineFootnote> const& ptr) : Napi::ObjectWrap<InlineFootnoteJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::InlineFootnote> _stored;
  org::sem::InlineFootnote* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<InlineFootnoteJs> {
  using type = org::sem::InlineFootnote;
};

template <>
struct org_to_js_type<org::sem::InlineFootnote> {
  using type = InlineFootnoteJs;
};

struct InlineExportJs : public Napi::ObjectWrap<InlineExportJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "InlineExportJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("InlineExportJs", func);
    return exports;
  }
  InlineExportJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<InlineExportJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::InlineExport>();
  }
  InlineExportJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::InlineExport> const& ptr) : Napi::ObjectWrap<InlineExportJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::InlineExport> _stored;
  org::sem::InlineExport* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<InlineExportJs> {
  using type = org::sem::InlineExport;
};

template <>
struct org_to_js_type<org::sem::InlineExport> {
  using type = InlineExportJs;
};

struct EscapedJs : public Napi::ObjectWrap<EscapedJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "EscapedJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("EscapedJs", func);
    return exports;
  }
  EscapedJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<EscapedJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Escaped>();
  }
  EscapedJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Escaped> const& ptr) : Napi::ObjectWrap<EscapedJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Escaped> _stored;
  org::sem::Escaped* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<EscapedJs> {
  using type = org::sem::Escaped;
};

template <>
struct org_to_js_type<org::sem::Escaped> {
  using type = EscapedJs;
};

struct NewlineJs : public Napi::ObjectWrap<NewlineJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "NewlineJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("NewlineJs", func);
    return exports;
  }
  NewlineJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<NewlineJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Newline>();
  }
  NewlineJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Newline> const& ptr) : Napi::ObjectWrap<NewlineJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Newline> _stored;
  org::sem::Newline* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<NewlineJs> {
  using type = org::sem::Newline;
};

template <>
struct org_to_js_type<org::sem::Newline> {
  using type = NewlineJs;
};

struct SpaceJs : public Napi::ObjectWrap<SpaceJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SpaceJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SpaceJs", func);
    return exports;
  }
  SpaceJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<SpaceJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Space>();
  }
  SpaceJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Space> const& ptr) : Napi::ObjectWrap<SpaceJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Space> _stored;
  org::sem::Space* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<SpaceJs> {
  using type = org::sem::Space;
};

template <>
struct org_to_js_type<org::sem::Space> {
  using type = SpaceJs;
};

struct WordJs : public Napi::ObjectWrap<WordJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "WordJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("WordJs", func);
    return exports;
  }
  WordJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<WordJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Word>();
  }
  WordJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Word> const& ptr) : Napi::ObjectWrap<WordJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Word> _stored;
  org::sem::Word* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<WordJs> {
  using type = org::sem::Word;
};

template <>
struct org_to_js_type<org::sem::Word> {
  using type = WordJs;
};

struct AtMentionJs : public Napi::ObjectWrap<AtMentionJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AtMentionJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AtMentionJs", func);
    return exports;
  }
  AtMentionJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<AtMentionJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::AtMention>();
  }
  AtMentionJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::AtMention> const& ptr) : Napi::ObjectWrap<AtMentionJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::AtMention> _stored;
  org::sem::AtMention* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<AtMentionJs> {
  using type = org::sem::AtMention;
};

template <>
struct org_to_js_type<org::sem::AtMention> {
  using type = AtMentionJs;
};

struct RawTextJs : public Napi::ObjectWrap<RawTextJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "RawTextJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("RawTextJs", func);
    return exports;
  }
  RawTextJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<RawTextJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::RawText>();
  }
  RawTextJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::RawText> const& ptr) : Napi::ObjectWrap<RawTextJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::RawText> _stored;
  org::sem::RawText* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<RawTextJs> {
  using type = org::sem::RawText;
};

template <>
struct org_to_js_type<org::sem::RawText> {
  using type = RawTextJs;
};

struct PunctuationJs : public Napi::ObjectWrap<PunctuationJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "PunctuationJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("PunctuationJs", func);
    return exports;
  }
  PunctuationJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<PunctuationJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Punctuation>();
  }
  PunctuationJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Punctuation> const& ptr) : Napi::ObjectWrap<PunctuationJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Punctuation> _stored;
  org::sem::Punctuation* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<PunctuationJs> {
  using type = org::sem::Punctuation;
};

template <>
struct org_to_js_type<org::sem::Punctuation> {
  using type = PunctuationJs;
};

struct PlaceholderJs : public Napi::ObjectWrap<PlaceholderJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "PlaceholderJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("PlaceholderJs", func);
    return exports;
  }
  PlaceholderJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<PlaceholderJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Placeholder>();
  }
  PlaceholderJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Placeholder> const& ptr) : Napi::ObjectWrap<PlaceholderJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Placeholder> _stored;
  org::sem::Placeholder* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<PlaceholderJs> {
  using type = org::sem::Placeholder;
};

template <>
struct org_to_js_type<org::sem::Placeholder> {
  using type = PlaceholderJs;
};

struct BigIdentJs : public Napi::ObjectWrap<BigIdentJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BigIdentJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BigIdentJs", func);
    return exports;
  }
  BigIdentJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BigIdentJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::BigIdent>();
  }
  BigIdentJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::BigIdent> const& ptr) : Napi::ObjectWrap<BigIdentJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::BigIdent> _stored;
  org::sem::BigIdent* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BigIdentJs> {
  using type = org::sem::BigIdent;
};

template <>
struct org_to_js_type<org::sem::BigIdent> {
  using type = BigIdentJs;
};

struct TextTargetJs : public Napi::ObjectWrap<TextTargetJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TextTargetJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("TextTargetJs", func);
    return exports;
  }
  TextTargetJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<TextTargetJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::TextTarget>();
  }
  TextTargetJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::TextTarget> const& ptr) : Napi::ObjectWrap<TextTargetJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::TextTarget> _stored;
  org::sem::TextTarget* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<TextTargetJs> {
  using type = org::sem::TextTarget;
};

template <>
struct org_to_js_type<org::sem::TextTarget> {
  using type = TextTargetJs;
};

struct BoldJs : public Napi::ObjectWrap<BoldJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BoldJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BoldJs", func);
    return exports;
  }
  BoldJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BoldJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Bold>();
  }
  BoldJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Bold> const& ptr) : Napi::ObjectWrap<BoldJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Bold> _stored;
  org::sem::Bold* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BoldJs> {
  using type = org::sem::Bold;
};

template <>
struct org_to_js_type<org::sem::Bold> {
  using type = BoldJs;
};

struct UnderlineJs : public Napi::ObjectWrap<UnderlineJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "UnderlineJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("UnderlineJs", func);
    return exports;
  }
  UnderlineJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<UnderlineJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Underline>();
  }
  UnderlineJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Underline> const& ptr) : Napi::ObjectWrap<UnderlineJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Underline> _stored;
  org::sem::Underline* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<UnderlineJs> {
  using type = org::sem::Underline;
};

template <>
struct org_to_js_type<org::sem::Underline> {
  using type = UnderlineJs;
};

struct MonospaceJs : public Napi::ObjectWrap<MonospaceJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MonospaceJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MonospaceJs", func);
    return exports;
  }
  MonospaceJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<MonospaceJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Monospace>();
  }
  MonospaceJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Monospace> const& ptr) : Napi::ObjectWrap<MonospaceJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Monospace> _stored;
  org::sem::Monospace* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<MonospaceJs> {
  using type = org::sem::Monospace;
};

template <>
struct org_to_js_type<org::sem::Monospace> {
  using type = MonospaceJs;
};

struct MarkQuoteJs : public Napi::ObjectWrap<MarkQuoteJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MarkQuoteJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MarkQuoteJs", func);
    return exports;
  }
  MarkQuoteJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<MarkQuoteJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::MarkQuote>();
  }
  MarkQuoteJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::MarkQuote> const& ptr) : Napi::ObjectWrap<MarkQuoteJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::MarkQuote> _stored;
  org::sem::MarkQuote* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<MarkQuoteJs> {
  using type = org::sem::MarkQuote;
};

template <>
struct org_to_js_type<org::sem::MarkQuote> {
  using type = MarkQuoteJs;
};

struct VerbatimJs : public Napi::ObjectWrap<VerbatimJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "VerbatimJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("VerbatimJs", func);
    return exports;
  }
  VerbatimJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<VerbatimJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Verbatim>();
  }
  VerbatimJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Verbatim> const& ptr) : Napi::ObjectWrap<VerbatimJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Verbatim> _stored;
  org::sem::Verbatim* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<VerbatimJs> {
  using type = org::sem::Verbatim;
};

template <>
struct org_to_js_type<org::sem::Verbatim> {
  using type = VerbatimJs;
};

struct ItalicJs : public Napi::ObjectWrap<ItalicJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ItalicJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ItalicJs", func);
    return exports;
  }
  ItalicJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ItalicJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Italic>();
  }
  ItalicJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Italic> const& ptr) : Napi::ObjectWrap<ItalicJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Italic> _stored;
  org::sem::Italic* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ItalicJs> {
  using type = org::sem::Italic;
};

template <>
struct org_to_js_type<org::sem::Italic> {
  using type = ItalicJs;
};

struct StrikeJs : public Napi::ObjectWrap<StrikeJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "StrikeJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("StrikeJs", func);
    return exports;
  }
  StrikeJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<StrikeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Strike>();
  }
  StrikeJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Strike> const& ptr) : Napi::ObjectWrap<StrikeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Strike> _stored;
  org::sem::Strike* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<StrikeJs> {
  using type = org::sem::Strike;
};

template <>
struct org_to_js_type<org::sem::Strike> {
  using type = StrikeJs;
};

struct ParJs : public Napi::ObjectWrap<ParJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ParJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ParJs", func);
    return exports;
  }
  ParJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ParJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Par>();
  }
  ParJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Par> const& ptr) : Napi::ObjectWrap<ParJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Par> _stored;
  org::sem::Par* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ParJs> {
  using type = org::sem::Par;
};

template <>
struct org_to_js_type<org::sem::Par> {
  using type = ParJs;
};

struct CmdCustomArgsJs : public Napi::ObjectWrap<CmdCustomArgsJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCustomArgsJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdCustomArgsJs", func);
    return exports;
  }
  CmdCustomArgsJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CmdCustomArgsJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::CmdCustomArgs>();
  }
  CmdCustomArgsJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::CmdCustomArgs> const& ptr) : Napi::ObjectWrap<CmdCustomArgsJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::CmdCustomArgs> _stored;
  org::sem::CmdCustomArgs* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CmdCustomArgsJs> {
  using type = org::sem::CmdCustomArgs;
};

template <>
struct org_to_js_type<org::sem::CmdCustomArgs> {
  using type = CmdCustomArgsJs;
};

struct CmdTblfmJs : public Napi::ObjectWrap<CmdTblfmJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdTblfmJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdTblfmJs", func);
    return exports;
  }
  CmdTblfmJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CmdTblfmJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::CmdTblfm>();
  }
  CmdTblfmJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::CmdTblfm> const& ptr) : Napi::ObjectWrap<CmdTblfmJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::CmdTblfm> _stored;
  org::sem::CmdTblfm* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CmdTblfmJs> {
  using type = org::sem::CmdTblfm;
};

template <>
struct org_to_js_type<org::sem::CmdTblfm> {
  using type = CmdTblfmJs;
};

struct CellJs : public Napi::ObjectWrap<CellJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CellJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CellJs", func);
    return exports;
  }
  CellJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CellJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Cell>();
  }
  CellJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Cell> const& ptr) : Napi::ObjectWrap<CellJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Cell> _stored;
  org::sem::Cell* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CellJs> {
  using type = org::sem::Cell;
};

template <>
struct org_to_js_type<org::sem::Cell> {
  using type = CellJs;
};

struct RowJs : public Napi::ObjectWrap<RowJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "RowJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("RowJs", func);
    return exports;
  }
  RowJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<RowJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Row>();
  }
  RowJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Row> const& ptr) : Napi::ObjectWrap<RowJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Row> _stored;
  org::sem::Row* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<RowJs> {
  using type = org::sem::Row;
};

template <>
struct org_to_js_type<org::sem::Row> {
  using type = RowJs;
};

struct ImmSubtreeAdapter : public Napi::ObjectWrap<ImmSubtreeAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeAdapter", func);
    return exports;
  }
  ImmSubtreeAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSubtreeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSubtreeAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSubtree>> const& ptr) : Napi::ObjectWrap<ImmSubtreeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSubtree>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSubtree>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSubtreeAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmSubtree>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmSubtree>> {
  using type = ImmSubtreeAdapter;
};

struct ImmNoneAdapter : public Napi::ObjectWrap<ImmNoneAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNoneAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNoneAdapter", func);
    return exports;
  }
  ImmNoneAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmNoneAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmNoneAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmNone>> const& ptr) : Napi::ObjectWrap<ImmNoneAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmNone>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmNone>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmNoneAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmNone>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmNone>> {
  using type = ImmNoneAdapter;
};

struct ImmErrorItemAdapter : public Napi::ObjectWrap<ImmErrorItemAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorItemAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorItemAdapter", func);
    return exports;
  }
  ImmErrorItemAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmErrorItemAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmErrorItemAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmErrorItem>> const& ptr) : Napi::ObjectWrap<ImmErrorItemAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmErrorItem>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmErrorItem>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmErrorItemAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmErrorItem>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmErrorItem>> {
  using type = ImmErrorItemAdapter;
};

struct ImmErrorGroupAdapter : public Napi::ObjectWrap<ImmErrorGroupAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorGroupAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorGroupAdapter", func);
    return exports;
  }
  ImmErrorGroupAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmErrorGroupAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmErrorGroupAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>> const& ptr) : Napi::ObjectWrap<ImmErrorGroupAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmErrorGroup>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmErrorGroupAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmErrorGroup>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>> {
  using type = ImmErrorGroupAdapter;
};

struct ImmStmtListAdapter : public Napi::ObjectWrap<ImmStmtListAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStmtListAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStmtListAdapter", func);
    return exports;
  }
  ImmStmtListAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmStmtListAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmStmtListAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmStmtList>> const& ptr) : Napi::ObjectWrap<ImmStmtListAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmStmtList>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmStmtList>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmStmtListAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmStmtList>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmStmtList>> {
  using type = ImmStmtListAdapter;
};

struct ImmEmptyAdapter : public Napi::ObjectWrap<ImmEmptyAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEmptyAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEmptyAdapter", func);
    return exports;
  }
  ImmEmptyAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmEmptyAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmEmptyAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmEmpty>> const& ptr) : Napi::ObjectWrap<ImmEmptyAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmEmpty>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmEmpty>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmEmptyAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmEmpty>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmEmpty>> {
  using type = ImmEmptyAdapter;
};

struct ImmTimeAdapter : public Napi::ObjectWrap<ImmTimeAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeAdapter", func);
    return exports;
  }
  ImmTimeAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTimeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTimeAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTime>> const& ptr) : Napi::ObjectWrap<ImmTimeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTime>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTime>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTimeAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmTime>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmTime>> {
  using type = ImmTimeAdapter;
};

struct ImmTimeRangeAdapter : public Napi::ObjectWrap<ImmTimeRangeAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeRangeAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeRangeAdapter", func);
    return exports;
  }
  ImmTimeRangeAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTimeRangeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTimeRangeAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTimeRange>> const& ptr) : Napi::ObjectWrap<ImmTimeRangeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTimeRange>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTimeRange>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTimeRangeAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmTimeRange>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmTimeRange>> {
  using type = ImmTimeRangeAdapter;
};

struct ImmMacroAdapter : public Napi::ObjectWrap<ImmMacroAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMacroAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMacroAdapter", func);
    return exports;
  }
  ImmMacroAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMacroAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmMacroAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmMacro>> const& ptr) : Napi::ObjectWrap<ImmMacroAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmMacro>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmMacro>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmMacroAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmMacro>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmMacro>> {
  using type = ImmMacroAdapter;
};

struct ImmSymbolAdapter : public Napi::ObjectWrap<ImmSymbolAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymbolAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymbolAdapter", func);
    return exports;
  }
  ImmSymbolAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSymbolAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSymbolAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSymbol>> const& ptr) : Napi::ObjectWrap<ImmSymbolAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSymbol>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSymbol>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSymbolAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmSymbol>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmSymbol>> {
  using type = ImmSymbolAdapter;
};

struct ImmLatexAdapter : public Napi::ObjectWrap<ImmLatexAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLatexAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLatexAdapter", func);
    return exports;
  }
  ImmLatexAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmLatexAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmLatexAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmLatex>> const& ptr) : Napi::ObjectWrap<ImmLatexAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmLatex>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmLatex>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmLatexAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmLatex>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmLatex>> {
  using type = ImmLatexAdapter;
};

struct ImmSubtreeLogAdapter : public Napi::ObjectWrap<ImmSubtreeLogAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeLogAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeLogAdapter", func);
    return exports;
  }
  ImmSubtreeLogAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSubtreeLogAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSubtreeLogAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>> const& ptr) : Napi::ObjectWrap<ImmSubtreeLogAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSubtreeLogAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>> {
  using type = ImmSubtreeLogAdapter;
};

struct ImmColonExampleAdapter : public Napi::ObjectWrap<ImmColonExampleAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmColonExampleAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmColonExampleAdapter", func);
    return exports;
  }
  ImmColonExampleAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmColonExampleAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmColonExampleAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmColonExample>> const& ptr) : Napi::ObjectWrap<ImmColonExampleAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmColonExample>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmColonExample>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmColonExampleAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmColonExample>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmColonExample>> {
  using type = ImmColonExampleAdapter;
};

struct ImmCallAdapter : public Napi::ObjectWrap<ImmCallAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCallAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCallAdapter", func);
    return exports;
  }
  ImmCallAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCallAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCallAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCall>> const& ptr) : Napi::ObjectWrap<ImmCallAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCall>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCall>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCallAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCall>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCall>> {
  using type = ImmCallAdapter;
};

struct ImmFileAdapter : public Napi::ObjectWrap<ImmFileAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileAdapter", func);
    return exports;
  }
  ImmFileAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmFileAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmFileAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmFile>> const& ptr) : Napi::ObjectWrap<ImmFileAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmFile>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmFile>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmFileAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmFile>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmFile>> {
  using type = ImmFileAdapter;
};

struct ImmDirectoryAdapter : public Napi::ObjectWrap<ImmDirectoryAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDirectoryAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDirectoryAdapter", func);
    return exports;
  }
  ImmDirectoryAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDirectoryAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDirectoryAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDirectory>> const& ptr) : Napi::ObjectWrap<ImmDirectoryAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDirectory>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDirectory>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDirectoryAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmDirectory>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmDirectory>> {
  using type = ImmDirectoryAdapter;
};

struct ImmSymlinkAdapter : public Napi::ObjectWrap<ImmSymlinkAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymlinkAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymlinkAdapter", func);
    return exports;
  }
  ImmSymlinkAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSymlinkAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSymlinkAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSymlink>> const& ptr) : Napi::ObjectWrap<ImmSymlinkAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSymlink>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSymlink>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSymlinkAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmSymlink>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmSymlink>> {
  using type = ImmSymlinkAdapter;
};

struct ImmDocumentFragmentAdapter : public Napi::ObjectWrap<ImmDocumentFragmentAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentFragmentAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentFragmentAdapter", func);
    return exports;
  }
  ImmDocumentFragmentAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentFragmentAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDocumentFragmentAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>> const& ptr) : Napi::ObjectWrap<ImmDocumentFragmentAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDocumentFragmentAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>> {
  using type = ImmDocumentFragmentAdapter;
};

struct ImmCriticMarkupAdapter : public Napi::ObjectWrap<ImmCriticMarkupAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCriticMarkupAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCriticMarkupAdapter", func);
    return exports;
  }
  ImmCriticMarkupAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCriticMarkupAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCriticMarkupAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>> const& ptr) : Napi::ObjectWrap<ImmCriticMarkupAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCriticMarkupAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>> {
  using type = ImmCriticMarkupAdapter;
};

struct ImmListItemAdapter : public Napi::ObjectWrap<ImmListItemAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListItemAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListItemAdapter", func);
    return exports;
  }
  ImmListItemAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmListItemAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmListItemAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmListItem>> const& ptr) : Napi::ObjectWrap<ImmListItemAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmListItem>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmListItem>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmListItemAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmListItem>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmListItem>> {
  using type = ImmListItemAdapter;
};

struct ImmDocumentOptionsAdapter : public Napi::ObjectWrap<ImmDocumentOptionsAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentOptionsAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentOptionsAdapter", func);
    return exports;
  }
  ImmDocumentOptionsAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentOptionsAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDocumentOptionsAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>> const& ptr) : Napi::ObjectWrap<ImmDocumentOptionsAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDocumentOptionsAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>> {
  using type = ImmDocumentOptionsAdapter;
};

struct ImmDocumentAdapter : public Napi::ObjectWrap<ImmDocumentAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentAdapter", func);
    return exports;
  }
  ImmDocumentAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDocumentAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocument>> const& ptr) : Napi::ObjectWrap<ImmDocumentAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocument>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDocument>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDocumentAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmDocument>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmDocument>> {
  using type = ImmDocumentAdapter;
};

struct ImmFileTargetAdapter : public Napi::ObjectWrap<ImmFileTargetAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileTargetAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileTargetAdapter", func);
    return exports;
  }
  ImmFileTargetAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmFileTargetAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmFileTargetAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmFileTarget>> const& ptr) : Napi::ObjectWrap<ImmFileTargetAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmFileTarget>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmFileTarget>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmFileTargetAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmFileTarget>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmFileTarget>> {
  using type = ImmFileTargetAdapter;
};

struct ImmTextSeparatorAdapter : public Napi::ObjectWrap<ImmTextSeparatorAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextSeparatorAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextSeparatorAdapter", func);
    return exports;
  }
  ImmTextSeparatorAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTextSeparatorAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTextSeparatorAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>> const& ptr) : Napi::ObjectWrap<ImmTextSeparatorAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTextSeparator>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTextSeparatorAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmTextSeparator>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>> {
  using type = ImmTextSeparatorAdapter;
};

struct ImmCmdIncludeAdapter : public Napi::ObjectWrap<ImmCmdIncludeAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdIncludeAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdIncludeAdapter", func);
    return exports;
  }
  ImmCmdIncludeAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdIncludeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdIncludeAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>> const& ptr) : Napi::ObjectWrap<ImmCmdIncludeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdInclude>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdIncludeAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCmdInclude>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>> {
  using type = ImmCmdIncludeAdapter;
};

struct ImmDocumentGroupAdapter : public Napi::ObjectWrap<ImmDocumentGroupAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentGroupAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentGroupAdapter", func);
    return exports;
  }
  ImmDocumentGroupAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentGroupAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmDocumentGroupAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>> const& ptr) : Napi::ObjectWrap<ImmDocumentGroupAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmDocumentGroupAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>> {
  using type = ImmDocumentGroupAdapter;
};

struct BlockCenterJs : public Napi::ObjectWrap<BlockCenterJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCenterJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockCenterJs", func);
    return exports;
  }
  BlockCenterJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BlockCenterJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::BlockCenter>();
  }
  BlockCenterJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::BlockCenter> const& ptr) : Napi::ObjectWrap<BlockCenterJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::BlockCenter> _stored;
  org::sem::BlockCenter* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BlockCenterJs> {
  using type = org::sem::BlockCenter;
};

template <>
struct org_to_js_type<org::sem::BlockCenter> {
  using type = BlockCenterJs;
};

struct BlockQuoteJs : public Napi::ObjectWrap<BlockQuoteJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockQuoteJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockQuoteJs", func);
    return exports;
  }
  BlockQuoteJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BlockQuoteJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::BlockQuote>();
  }
  BlockQuoteJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::BlockQuote> const& ptr) : Napi::ObjectWrap<BlockQuoteJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::BlockQuote> _stored;
  org::sem::BlockQuote* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BlockQuoteJs> {
  using type = org::sem::BlockQuote;
};

template <>
struct org_to_js_type<org::sem::BlockQuote> {
  using type = BlockQuoteJs;
};

struct BlockVerseJs : public Napi::ObjectWrap<BlockVerseJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockVerseJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockVerseJs", func);
    return exports;
  }
  BlockVerseJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BlockVerseJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::BlockVerse>();
  }
  BlockVerseJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::BlockVerse> const& ptr) : Napi::ObjectWrap<BlockVerseJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::BlockVerse> _stored;
  org::sem::BlockVerse* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BlockVerseJs> {
  using type = org::sem::BlockVerse;
};

template <>
struct org_to_js_type<org::sem::BlockVerse> {
  using type = BlockVerseJs;
};

struct BlockDynamicFallbackJs : public Napi::ObjectWrap<BlockDynamicFallbackJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockDynamicFallbackJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockDynamicFallbackJs", func);
    return exports;
  }
  BlockDynamicFallbackJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BlockDynamicFallbackJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::BlockDynamicFallback>();
  }
  BlockDynamicFallbackJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::BlockDynamicFallback> const& ptr) : Napi::ObjectWrap<BlockDynamicFallbackJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::BlockDynamicFallback> _stored;
  org::sem::BlockDynamicFallback* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BlockDynamicFallbackJs> {
  using type = org::sem::BlockDynamicFallback;
};

template <>
struct org_to_js_type<org::sem::BlockDynamicFallback> {
  using type = BlockDynamicFallbackJs;
};

struct BlockExampleJs : public Napi::ObjectWrap<BlockExampleJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockExampleJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockExampleJs", func);
    return exports;
  }
  BlockExampleJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BlockExampleJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::BlockExample>();
  }
  BlockExampleJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::BlockExample> const& ptr) : Napi::ObjectWrap<BlockExampleJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::BlockExample> _stored;
  org::sem::BlockExample* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BlockExampleJs> {
  using type = org::sem::BlockExample;
};

template <>
struct org_to_js_type<org::sem::BlockExample> {
  using type = BlockExampleJs;
};

struct BlockExportJs : public Napi::ObjectWrap<BlockExportJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockExportJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockExportJs", func);
    return exports;
  }
  BlockExportJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BlockExportJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::BlockExport>();
  }
  BlockExportJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::BlockExport> const& ptr) : Napi::ObjectWrap<BlockExportJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::BlockExport> _stored;
  org::sem::BlockExport* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BlockExportJs> {
  using type = org::sem::BlockExport;
};

template <>
struct org_to_js_type<org::sem::BlockExport> {
  using type = BlockExportJs;
};

struct BlockAdmonitionJs : public Napi::ObjectWrap<BlockAdmonitionJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockAdmonitionJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockAdmonitionJs", func);
    return exports;
  }
  BlockAdmonitionJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BlockAdmonitionJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::BlockAdmonition>();
  }
  BlockAdmonitionJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::BlockAdmonition> const& ptr) : Napi::ObjectWrap<BlockAdmonitionJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::BlockAdmonition> _stored;
  org::sem::BlockAdmonition* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BlockAdmonitionJs> {
  using type = org::sem::BlockAdmonition;
};

template <>
struct org_to_js_type<org::sem::BlockAdmonition> {
  using type = BlockAdmonitionJs;
};

struct BlockCodeEvalResultJs : public Napi::ObjectWrap<BlockCodeEvalResultJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCodeEvalResultJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockCodeEvalResultJs", func);
    return exports;
  }
  BlockCodeEvalResultJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BlockCodeEvalResultJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::BlockCodeEvalResult>();
  }
  BlockCodeEvalResultJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::BlockCodeEvalResult> const& ptr) : Napi::ObjectWrap<BlockCodeEvalResultJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::BlockCodeEvalResult> _stored;
  org::sem::BlockCodeEvalResult* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BlockCodeEvalResultJs> {
  using type = org::sem::BlockCodeEvalResult;
};

template <>
struct org_to_js_type<org::sem::BlockCodeEvalResult> {
  using type = BlockCodeEvalResultJs;
};

struct BlockCodeJs : public Napi::ObjectWrap<BlockCodeJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCodeJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockCodeJs", func);
    return exports;
  }
  BlockCodeJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<BlockCodeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::BlockCode>();
  }
  BlockCodeJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::BlockCode> const& ptr) : Napi::ObjectWrap<BlockCodeJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::BlockCode> _stored;
  org::sem::BlockCode* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<BlockCodeJs> {
  using type = org::sem::BlockCode;
};

template <>
struct org_to_js_type<org::sem::BlockCode> {
  using type = BlockCodeJs;
};

struct TableJs : public Napi::ObjectWrap<TableJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TableJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("TableJs", func);
    return exports;
  }
  TableJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<TableJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::Table>();
  }
  TableJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::Table> const& ptr) : Napi::ObjectWrap<TableJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::Table> _stored;
  org::sem::Table* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<TableJs> {
  using type = org::sem::Table;
};

template <>
struct org_to_js_type<org::sem::Table> {
  using type = TableJs;
};

struct ImmCmdCustomRawAdapter : public Napi::ObjectWrap<ImmCmdCustomRawAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomRawAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomRawAdapter", func);
    return exports;
  }
  ImmCmdCustomRawAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomRawAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCustomRawAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>> const& ptr) : Napi::ObjectWrap<ImmCmdCustomRawAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCustomRawAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>> {
  using type = ImmCmdCustomRawAdapter;
};

struct ImmCmdCustomTextAdapter : public Napi::ObjectWrap<ImmCmdCustomTextAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomTextAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomTextAdapter", func);
    return exports;
  }
  ImmCmdCustomTextAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomTextAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCustomTextAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>> const& ptr) : Napi::ObjectWrap<ImmCmdCustomTextAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCustomTextAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>> {
  using type = ImmCmdCustomTextAdapter;
};

struct ImmLinkAdapter : public Napi::ObjectWrap<ImmLinkAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLinkAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLinkAdapter", func);
    return exports;
  }
  ImmLinkAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmLinkAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmLinkAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmLink>> const& ptr) : Napi::ObjectWrap<ImmLinkAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmLink>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmLink>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmLinkAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmLink>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmLink>> {
  using type = ImmLinkAdapter;
};

struct ImmBlockCommentAdapter : public Napi::ObjectWrap<ImmBlockCommentAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCommentAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCommentAdapter", func);
    return exports;
  }
  ImmBlockCommentAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCommentAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockCommentAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockComment>> const& ptr) : Napi::ObjectWrap<ImmBlockCommentAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockComment>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockComment>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockCommentAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmBlockComment>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmBlockComment>> {
  using type = ImmBlockCommentAdapter;
};

struct ImmParagraphAdapter : public Napi::ObjectWrap<ImmParagraphAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParagraphAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParagraphAdapter", func);
    return exports;
  }
  ImmParagraphAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmParagraphAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmParagraphAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmParagraph>> const& ptr) : Napi::ObjectWrap<ImmParagraphAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmParagraph>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmParagraph>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmParagraphAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmParagraph>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmParagraph>> {
  using type = ImmParagraphAdapter;
};

struct ImmListAdapter : public Napi::ObjectWrap<ImmListAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListAdapter", func);
    return exports;
  }
  ImmListAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmListAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmListAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmList>> const& ptr) : Napi::ObjectWrap<ImmListAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmList>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmList>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmListAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmList>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmList>> {
  using type = ImmListAdapter;
};

struct ImmHashTagAdapter : public Napi::ObjectWrap<ImmHashTagAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmHashTagAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmHashTagAdapter", func);
    return exports;
  }
  ImmHashTagAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmHashTagAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmHashTagAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmHashTag>> const& ptr) : Napi::ObjectWrap<ImmHashTagAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmHashTag>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmHashTag>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmHashTagAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmHashTag>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmHashTag>> {
  using type = ImmHashTagAdapter;
};

struct ImmInlineFootnoteAdapter : public Napi::ObjectWrap<ImmInlineFootnoteAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineFootnoteAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineFootnoteAdapter", func);
    return exports;
  }
  ImmInlineFootnoteAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmInlineFootnoteAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmInlineFootnoteAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>> const& ptr) : Napi::ObjectWrap<ImmInlineFootnoteAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmInlineFootnoteAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>> {
  using type = ImmInlineFootnoteAdapter;
};

struct ImmEscapedAdapter : public Napi::ObjectWrap<ImmEscapedAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEscapedAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEscapedAdapter", func);
    return exports;
  }
  ImmEscapedAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmEscapedAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmEscapedAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmEscaped>> const& ptr) : Napi::ObjectWrap<ImmEscapedAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmEscaped>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmEscaped>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmEscapedAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmEscaped>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmEscaped>> {
  using type = ImmEscapedAdapter;
};

struct ImmNewlineAdapter : public Napi::ObjectWrap<ImmNewlineAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNewlineAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNewlineAdapter", func);
    return exports;
  }
  ImmNewlineAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmNewlineAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmNewlineAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmNewline>> const& ptr) : Napi::ObjectWrap<ImmNewlineAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmNewline>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmNewline>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmNewlineAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmNewline>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmNewline>> {
  using type = ImmNewlineAdapter;
};

struct ImmSpaceAdapter : public Napi::ObjectWrap<ImmSpaceAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSpaceAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSpaceAdapter", func);
    return exports;
  }
  ImmSpaceAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSpaceAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmSpaceAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSpace>> const& ptr) : Napi::ObjectWrap<ImmSpaceAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSpace>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSpace>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmSpaceAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmSpace>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmSpace>> {
  using type = ImmSpaceAdapter;
};

struct ImmWordAdapter : public Napi::ObjectWrap<ImmWordAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmWordAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmWordAdapter", func);
    return exports;
  }
  ImmWordAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmWordAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmWordAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmWord>> const& ptr) : Napi::ObjectWrap<ImmWordAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmWord>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmWord>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmWordAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmWord>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmWord>> {
  using type = ImmWordAdapter;
};

struct ImmAtMentionAdapter : public Napi::ObjectWrap<ImmAtMentionAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAtMentionAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAtMentionAdapter", func);
    return exports;
  }
  ImmAtMentionAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmAtMentionAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmAtMentionAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmAtMention>> const& ptr) : Napi::ObjectWrap<ImmAtMentionAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmAtMention>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmAtMention>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmAtMentionAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmAtMention>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmAtMention>> {
  using type = ImmAtMentionAdapter;
};

struct ImmRawTextAdapter : public Napi::ObjectWrap<ImmRawTextAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRawTextAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRawTextAdapter", func);
    return exports;
  }
  ImmRawTextAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRawTextAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmRawTextAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmRawText>> const& ptr) : Napi::ObjectWrap<ImmRawTextAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmRawText>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmRawText>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmRawTextAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmRawText>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmRawText>> {
  using type = ImmRawTextAdapter;
};

struct ImmPunctuationAdapter : public Napi::ObjectWrap<ImmPunctuationAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPunctuationAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPunctuationAdapter", func);
    return exports;
  }
  ImmPunctuationAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPunctuationAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmPunctuationAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmPunctuation>> const& ptr) : Napi::ObjectWrap<ImmPunctuationAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmPunctuation>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmPunctuation>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmPunctuationAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmPunctuation>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmPunctuation>> {
  using type = ImmPunctuationAdapter;
};

struct ImmPlaceholderAdapter : public Napi::ObjectWrap<ImmPlaceholderAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPlaceholderAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPlaceholderAdapter", func);
    return exports;
  }
  ImmPlaceholderAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPlaceholderAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmPlaceholderAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>> const& ptr) : Napi::ObjectWrap<ImmPlaceholderAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmPlaceholder>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmPlaceholderAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmPlaceholder>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>> {
  using type = ImmPlaceholderAdapter;
};

struct ImmBigIdentAdapter : public Napi::ObjectWrap<ImmBigIdentAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBigIdentAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBigIdentAdapter", func);
    return exports;
  }
  ImmBigIdentAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBigIdentAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBigIdentAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBigIdent>> const& ptr) : Napi::ObjectWrap<ImmBigIdentAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBigIdent>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBigIdent>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBigIdentAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmBigIdent>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmBigIdent>> {
  using type = ImmBigIdentAdapter;
};

struct ImmTextTargetAdapter : public Napi::ObjectWrap<ImmTextTargetAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextTargetAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextTargetAdapter", func);
    return exports;
  }
  ImmTextTargetAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTextTargetAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTextTargetAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTextTarget>> const& ptr) : Napi::ObjectWrap<ImmTextTargetAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTextTarget>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTextTarget>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTextTargetAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmTextTarget>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmTextTarget>> {
  using type = ImmTextTargetAdapter;
};

struct ImmBoldAdapter : public Napi::ObjectWrap<ImmBoldAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBoldAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBoldAdapter", func);
    return exports;
  }
  ImmBoldAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBoldAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBoldAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBold>> const& ptr) : Napi::ObjectWrap<ImmBoldAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBold>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBold>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBoldAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmBold>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmBold>> {
  using type = ImmBoldAdapter;
};

struct ImmUnderlineAdapter : public Napi::ObjectWrap<ImmUnderlineAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmUnderlineAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmUnderlineAdapter", func);
    return exports;
  }
  ImmUnderlineAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmUnderlineAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmUnderlineAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmUnderline>> const& ptr) : Napi::ObjectWrap<ImmUnderlineAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmUnderline>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmUnderline>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmUnderlineAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmUnderline>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmUnderline>> {
  using type = ImmUnderlineAdapter;
};

struct ImmMonospaceAdapter : public Napi::ObjectWrap<ImmMonospaceAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMonospaceAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMonospaceAdapter", func);
    return exports;
  }
  ImmMonospaceAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMonospaceAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmMonospaceAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmMonospace>> const& ptr) : Napi::ObjectWrap<ImmMonospaceAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmMonospace>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmMonospace>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmMonospaceAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmMonospace>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmMonospace>> {
  using type = ImmMonospaceAdapter;
};

struct ImmMarkQuoteAdapter : public Napi::ObjectWrap<ImmMarkQuoteAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMarkQuoteAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMarkQuoteAdapter", func);
    return exports;
  }
  ImmMarkQuoteAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMarkQuoteAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmMarkQuoteAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>> const& ptr) : Napi::ObjectWrap<ImmMarkQuoteAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmMarkQuote>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmMarkQuoteAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmMarkQuote>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>> {
  using type = ImmMarkQuoteAdapter;
};

struct ImmRadioTargetAdapter : public Napi::ObjectWrap<ImmRadioTargetAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRadioTargetAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRadioTargetAdapter", func);
    return exports;
  }
  ImmRadioTargetAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRadioTargetAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmRadioTargetAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>> const& ptr) : Napi::ObjectWrap<ImmRadioTargetAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmRadioTarget>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmRadioTargetAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmRadioTarget>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>> {
  using type = ImmRadioTargetAdapter;
};

struct ImmVerbatimAdapter : public Napi::ObjectWrap<ImmVerbatimAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmVerbatimAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmVerbatimAdapter", func);
    return exports;
  }
  ImmVerbatimAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmVerbatimAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmVerbatimAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmVerbatim>> const& ptr) : Napi::ObjectWrap<ImmVerbatimAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmVerbatim>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmVerbatim>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmVerbatimAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmVerbatim>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmVerbatim>> {
  using type = ImmVerbatimAdapter;
};

struct ImmItalicAdapter : public Napi::ObjectWrap<ImmItalicAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmItalicAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmItalicAdapter", func);
    return exports;
  }
  ImmItalicAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmItalicAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmItalicAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmItalic>> const& ptr) : Napi::ObjectWrap<ImmItalicAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmItalic>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmItalic>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmItalicAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmItalic>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmItalic>> {
  using type = ImmItalicAdapter;
};

struct ImmStrikeAdapter : public Napi::ObjectWrap<ImmStrikeAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStrikeAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStrikeAdapter", func);
    return exports;
  }
  ImmStrikeAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmStrikeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmStrikeAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmStrike>> const& ptr) : Napi::ObjectWrap<ImmStrikeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmStrike>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmStrike>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmStrikeAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmStrike>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmStrike>> {
  using type = ImmStrikeAdapter;
};

struct ImmParAdapter : public Napi::ObjectWrap<ImmParAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParAdapter", func);
    return exports;
  }
  ImmParAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmParAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmParAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmPar>> const& ptr) : Napi::ObjectWrap<ImmParAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmPar>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmPar>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmParAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmPar>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmPar>> {
  using type = ImmParAdapter;
};

struct CmdCaptionJs : public Napi::ObjectWrap<CmdCaptionJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCaptionJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdCaptionJs", func);
    return exports;
  }
  CmdCaptionJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CmdCaptionJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::CmdCaption>();
  }
  CmdCaptionJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::CmdCaption> const& ptr) : Napi::ObjectWrap<CmdCaptionJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::CmdCaption> _stored;
  org::sem::CmdCaption* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CmdCaptionJs> {
  using type = org::sem::CmdCaption;
};

template <>
struct org_to_js_type<org::sem::CmdCaption> {
  using type = CmdCaptionJs;
};

struct CmdColumnsJs : public Napi::ObjectWrap<CmdColumnsJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdColumnsJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdColumnsJs", func);
    return exports;
  }
  CmdColumnsJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CmdColumnsJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::CmdColumns>();
  }
  CmdColumnsJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::CmdColumns> const& ptr) : Napi::ObjectWrap<CmdColumnsJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::CmdColumns> _stored;
  org::sem::CmdColumns* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CmdColumnsJs> {
  using type = org::sem::CmdColumns;
};

template <>
struct org_to_js_type<org::sem::CmdColumns> {
  using type = CmdColumnsJs;
};

struct CmdNameJs : public Napi::ObjectWrap<CmdNameJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdNameJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdNameJs", func);
    return exports;
  }
  CmdNameJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CmdNameJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::CmdName>();
  }
  CmdNameJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::CmdName> const& ptr) : Napi::ObjectWrap<CmdNameJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::CmdName> _stored;
  org::sem::CmdName* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CmdNameJs> {
  using type = org::sem::CmdName;
};

template <>
struct org_to_js_type<org::sem::CmdName> {
  using type = CmdNameJs;
};

struct CmdCallJs : public Napi::ObjectWrap<CmdCallJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCallJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdCallJs", func);
    return exports;
  }
  CmdCallJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CmdCallJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::CmdCall>();
  }
  CmdCallJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::CmdCall> const& ptr) : Napi::ObjectWrap<CmdCallJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::CmdCall> _stored;
  org::sem::CmdCall* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CmdCallJs> {
  using type = org::sem::CmdCall;
};

template <>
struct org_to_js_type<org::sem::CmdCall> {
  using type = CmdCallJs;
};

struct CmdAttrJs : public Napi::ObjectWrap<CmdAttrJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdAttrJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdAttrJs", func);
    return exports;
  }
  CmdAttrJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CmdAttrJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::CmdAttr>();
  }
  CmdAttrJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::CmdAttr> const& ptr) : Napi::ObjectWrap<CmdAttrJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::CmdAttr> _stored;
  org::sem::CmdAttr* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CmdAttrJs> {
  using type = org::sem::CmdAttr;
};

template <>
struct org_to_js_type<org::sem::CmdAttr> {
  using type = CmdAttrJs;
};

struct CmdExportJs : public Napi::ObjectWrap<CmdExportJs> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdExportJs", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdExportJs", func);
    return exports;
  }
  CmdExportJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<CmdExportJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = std::make_shared<org::sem::CmdExport>();
  }
  CmdExportJs(Napi::CallbackInfo const& info, std::shared_ptr<org::sem::CmdExport> const& ptr) : Napi::ObjectWrap<CmdExportJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::sem::CmdExport> _stored;
  org::sem::CmdExport* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<CmdExportJs> {
  using type = org::sem::CmdExport;
};

template <>
struct org_to_js_type<org::sem::CmdExport> {
  using type = CmdExportJs;
};

struct ImmCmdCustomArgsAdapter : public Napi::ObjectWrap<ImmCmdCustomArgsAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomArgsAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomArgsAdapter", func);
    return exports;
  }
  ImmCmdCustomArgsAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomArgsAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCustomArgsAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>> const& ptr) : Napi::ObjectWrap<ImmCmdCustomArgsAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCustomArgsAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>> {
  using type = ImmCmdCustomArgsAdapter;
};

struct ImmCmdTblfmAdapter : public Napi::ObjectWrap<ImmCmdTblfmAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdTblfmAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdTblfmAdapter", func);
    return exports;
  }
  ImmCmdTblfmAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdTblfmAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdTblfmAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>> const& ptr) : Napi::ObjectWrap<ImmCmdTblfmAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdTblfmAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>> {
  using type = ImmCmdTblfmAdapter;
};

struct ImmCellAdapter : public Napi::ObjectWrap<ImmCellAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCellAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCellAdapter", func);
    return exports;
  }
  ImmCellAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCellAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCellAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCell>> const& ptr) : Napi::ObjectWrap<ImmCellAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCell>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCell>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCellAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCell>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCell>> {
  using type = ImmCellAdapter;
};

struct ImmRowAdapter : public Napi::ObjectWrap<ImmRowAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRowAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRowAdapter", func);
    return exports;
  }
  ImmRowAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRowAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmRowAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmRow>> const& ptr) : Napi::ObjectWrap<ImmRowAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmRow>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmRow>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmRowAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmRow>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmRow>> {
  using type = ImmRowAdapter;
};

struct ImmBlockCenterAdapter : public Napi::ObjectWrap<ImmBlockCenterAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCenterAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCenterAdapter", func);
    return exports;
  }
  ImmBlockCenterAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCenterAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockCenterAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>> const& ptr) : Napi::ObjectWrap<ImmBlockCenterAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockCenter>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockCenterAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmBlockCenter>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>> {
  using type = ImmBlockCenterAdapter;
};

struct ImmBlockQuoteAdapter : public Napi::ObjectWrap<ImmBlockQuoteAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockQuoteAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockQuoteAdapter", func);
    return exports;
  }
  ImmBlockQuoteAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockQuoteAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockQuoteAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>> const& ptr) : Napi::ObjectWrap<ImmBlockQuoteAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockQuote>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockQuoteAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmBlockQuote>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>> {
  using type = ImmBlockQuoteAdapter;
};

struct ImmBlockVerseAdapter : public Napi::ObjectWrap<ImmBlockVerseAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockVerseAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockVerseAdapter", func);
    return exports;
  }
  ImmBlockVerseAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockVerseAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockVerseAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>> const& ptr) : Napi::ObjectWrap<ImmBlockVerseAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockVerse>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockVerseAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmBlockVerse>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>> {
  using type = ImmBlockVerseAdapter;
};

struct ImmBlockExampleAdapter : public Napi::ObjectWrap<ImmBlockExampleAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExampleAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExampleAdapter", func);
    return exports;
  }
  ImmBlockExampleAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockExampleAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockExampleAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockExample>> const& ptr) : Napi::ObjectWrap<ImmBlockExampleAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockExample>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockExample>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockExampleAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmBlockExample>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmBlockExample>> {
  using type = ImmBlockExampleAdapter;
};

struct ImmInlineExportAdapter : public Napi::ObjectWrap<ImmInlineExportAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineExportAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineExportAdapter", func);
    return exports;
  }
  ImmInlineExportAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmInlineExportAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmInlineExportAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmInlineExport>> const& ptr) : Napi::ObjectWrap<ImmInlineExportAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmInlineExport>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmInlineExport>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmInlineExportAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmInlineExport>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmInlineExport>> {
  using type = ImmInlineExportAdapter;
};

struct ImmCmdExportAdapter : public Napi::ObjectWrap<ImmCmdExportAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdExportAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdExportAdapter", func);
    return exports;
  }
  ImmCmdExportAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdExportAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdExportAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdExport>> const& ptr) : Napi::ObjectWrap<ImmCmdExportAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdExport>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdExport>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdExportAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCmdExport>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCmdExport>> {
  using type = ImmCmdExportAdapter;
};

struct ImmBlockExportAdapter : public Napi::ObjectWrap<ImmBlockExportAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExportAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExportAdapter", func);
    return exports;
  }
  ImmBlockExportAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockExportAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockExportAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockExport>> const& ptr) : Napi::ObjectWrap<ImmBlockExportAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockExport>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockExport>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockExportAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmBlockExport>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmBlockExport>> {
  using type = ImmBlockExportAdapter;
};

struct ImmBlockDynamicFallbackAdapter : public Napi::ObjectWrap<ImmBlockDynamicFallbackAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockDynamicFallbackAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockDynamicFallbackAdapter", func);
    return exports;
  }
  ImmBlockDynamicFallbackAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockDynamicFallbackAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockDynamicFallbackAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>> const& ptr) : Napi::ObjectWrap<ImmBlockDynamicFallbackAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockDynamicFallbackAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>> {
  using type = ImmBlockDynamicFallbackAdapter;
};

struct ImmBlockAdmonitionAdapter : public Napi::ObjectWrap<ImmBlockAdmonitionAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockAdmonitionAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockAdmonitionAdapter", func);
    return exports;
  }
  ImmBlockAdmonitionAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockAdmonitionAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockAdmonitionAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>> const& ptr) : Napi::ObjectWrap<ImmBlockAdmonitionAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockAdmonitionAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>> {
  using type = ImmBlockAdmonitionAdapter;
};

struct ImmBlockCodeEvalResultAdapter : public Napi::ObjectWrap<ImmBlockCodeEvalResultAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeEvalResultAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeEvalResultAdapter", func);
    return exports;
  }
  ImmBlockCodeEvalResultAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCodeEvalResultAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockCodeEvalResultAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>> const& ptr) : Napi::ObjectWrap<ImmBlockCodeEvalResultAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockCodeEvalResultAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>> {
  using type = ImmBlockCodeEvalResultAdapter;
};

struct ImmBlockCodeAdapter : public Napi::ObjectWrap<ImmBlockCodeAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeAdapter", func);
    return exports;
  }
  ImmBlockCodeAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCodeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmBlockCodeAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockCode>> const& ptr) : Napi::ObjectWrap<ImmBlockCodeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockCode>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockCode>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmBlockCodeAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmBlockCode>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmBlockCode>> {
  using type = ImmBlockCodeAdapter;
};

struct ImmTableAdapter : public Napi::ObjectWrap<ImmTableAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTableAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTableAdapter", func);
    return exports;
  }
  ImmTableAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTableAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmTableAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTable>> const& ptr) : Napi::ObjectWrap<ImmTableAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTable>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTable>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmTableAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmTable>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmTable>> {
  using type = ImmTableAdapter;
};

struct ImmCmdCaptionAdapter : public Napi::ObjectWrap<ImmCmdCaptionAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCaptionAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCaptionAdapter", func);
    return exports;
  }
  ImmCmdCaptionAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCaptionAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCaptionAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>> const& ptr) : Napi::ObjectWrap<ImmCmdCaptionAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCaption>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCaptionAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCmdCaption>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>> {
  using type = ImmCmdCaptionAdapter;
};

struct ImmCmdColumnsAdapter : public Napi::ObjectWrap<ImmCmdColumnsAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdColumnsAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdColumnsAdapter", func);
    return exports;
  }
  ImmCmdColumnsAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdColumnsAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdColumnsAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>> const& ptr) : Napi::ObjectWrap<ImmCmdColumnsAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdColumns>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdColumnsAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCmdColumns>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>> {
  using type = ImmCmdColumnsAdapter;
};

struct ImmCmdNameAdapter : public Napi::ObjectWrap<ImmCmdNameAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdNameAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdNameAdapter", func);
    return exports;
  }
  ImmCmdNameAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdNameAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdNameAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdName>> const& ptr) : Napi::ObjectWrap<ImmCmdNameAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdName>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdName>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdNameAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCmdName>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCmdName>> {
  using type = ImmCmdNameAdapter;
};

struct ImmCmdCallAdapter : public Napi::ObjectWrap<ImmCmdCallAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCallAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCallAdapter", func);
    return exports;
  }
  ImmCmdCallAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCallAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdCallAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCall>> const& ptr) : Napi::ObjectWrap<ImmCmdCallAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCall>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCall>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdCallAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCmdCall>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCmdCall>> {
  using type = ImmCmdCallAdapter;
};

struct ImmCmdAttrAdapter : public Napi::ObjectWrap<ImmCmdAttrAdapter> {
  static inline Napi::FunctionReference* constructor;
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdAttrAdapter", {});
    constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdAttrAdapter", func);
    return exports;
  }
  ImmCmdAttrAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdAttrAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  ImmCmdAttrAdapter(Napi::CallbackInfo const& info, std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>> const& ptr) : Napi::ObjectWrap<ImmCmdAttrAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    _stored = ptr;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdAttr>* getPtr() { return _stored.get(); }
};

template <>
struct js_to_org_type<ImmCmdAttrAdapter> {
  using type = org::imm::ImmAdapterT<org::imm::ImmCmdAttr>;
};

template <>
struct org_to_js_type<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>> {
  using type = ImmCmdAttrAdapter;
};

Napi::Object InitModule(Napi::Env env, Napi::Object exports) {
  UserTimeBreakdownJs::Init(env, exports);
  UserTimeJs::Init(env, exports);
  LineColJs::Init(env, exports);
  OrgJsonJs::Init(env, exports);
  OperationsTracerJs::Init(env, exports);
  ImmIdJs::Init(env, exports);
  ImmPathStepJs::Init(env, exports);
  ImmPathJs::Init(env, exports);
  ImmUniqIdJs::Init(env, exports);
  ImmNoneValueReadJs::Init(env, exports);
  ImmErrorItemValueReadJs::Init(env, exports);
  ImmErrorGroupValueReadJs::Init(env, exports);
  ImmStmtListValueReadJs::Init(env, exports);
  ImmEmptyValueReadJs::Init(env, exports);
  ImmCmdCaptionValueReadJs::Init(env, exports);
  ImmCmdColumnsValueReadJs::Init(env, exports);
  ImmCmdNameValueReadJs::Init(env, exports);
  ImmCmdCustomArgsValueReadJs::Init(env, exports);
  ImmCmdCustomRawValueReadJs::Init(env, exports);
  ImmCmdCustomTextValueReadJs::Init(env, exports);
  ImmCmdCallValueReadJs::Init(env, exports);
  ImmCmdTblfmValueReadJs::Init(env, exports);
  ImmHashTagValueReadJs::Init(env, exports);
  ImmInlineFootnoteValueReadJs::Init(env, exports);
  ImmInlineExportValueReadJs::Init(env, exports);
  ImmTimeValueReadJs::Init(env, exports);
  ImmTimeRangeValueReadJs::Init(env, exports);
  ImmMacroValueReadJs::Init(env, exports);
  ImmSymbolValueReadJs::Init(env, exports);
  ImmEscapedValueReadJs::Init(env, exports);
  ImmNewlineValueReadJs::Init(env, exports);
  ImmSpaceValueReadJs::Init(env, exports);
  ImmWordValueReadJs::Init(env, exports);
  ImmAtMentionValueReadJs::Init(env, exports);
  ImmRawTextValueReadJs::Init(env, exports);
  ImmPunctuationValueReadJs::Init(env, exports);
  ImmPlaceholderValueReadJs::Init(env, exports);
  ImmBigIdentValueReadJs::Init(env, exports);
  ImmTextTargetValueReadJs::Init(env, exports);
  ImmBoldValueReadJs::Init(env, exports);
  ImmUnderlineValueReadJs::Init(env, exports);
  ImmMonospaceValueReadJs::Init(env, exports);
  ImmMarkQuoteValueReadJs::Init(env, exports);
  ImmVerbatimValueReadJs::Init(env, exports);
  ImmItalicValueReadJs::Init(env, exports);
  ImmStrikeValueReadJs::Init(env, exports);
  ImmParValueReadJs::Init(env, exports);
  ImmRadioTargetValueReadJs::Init(env, exports);
  ImmLatexValueReadJs::Init(env, exports);
  ImmLinkValueReadJs::Init(env, exports);
  ImmBlockCenterValueReadJs::Init(env, exports);
  ImmBlockQuoteValueReadJs::Init(env, exports);
  ImmBlockCommentValueReadJs::Init(env, exports);
  ImmBlockVerseValueReadJs::Init(env, exports);
  ImmBlockDynamicFallbackValueReadJs::Init(env, exports);
  ImmBlockExampleValueReadJs::Init(env, exports);
  ImmBlockExportValueReadJs::Init(env, exports);
  ImmBlockAdmonitionValueReadJs::Init(env, exports);
  ImmBlockCodeEvalResultValueReadJs::Init(env, exports);
  ImmBlockCodeValueReadJs::Init(env, exports);
  ImmSubtreeLogValueReadJs::Init(env, exports);
  ImmSubtreeValueReadJs::Init(env, exports);
  ImmCellValueReadJs::Init(env, exports);
  ImmRowValueReadJs::Init(env, exports);
  ImmTableValueReadJs::Init(env, exports);
  ImmParagraphValueReadJs::Init(env, exports);
  ImmColonExampleValueReadJs::Init(env, exports);
  ImmCmdAttrValueReadJs::Init(env, exports);
  ImmCmdExportValueReadJs::Init(env, exports);
  ImmCallValueReadJs::Init(env, exports);
  ImmListValueReadJs::Init(env, exports);
  ImmListItemValueReadJs::Init(env, exports);
  ImmDocumentOptionsValueReadJs::Init(env, exports);
  ImmDocumentFragmentValueReadJs::Init(env, exports);
  ImmCriticMarkupValueReadJs::Init(env, exports);
  ImmDocumentValueReadJs::Init(env, exports);
  ImmFileTargetValueReadJs::Init(env, exports);
  ImmTextSeparatorValueReadJs::Init(env, exports);
  ImmDocumentGroupValueReadJs::Init(env, exports);
  ImmFileValueReadJs::Init(env, exports);
  ImmDirectoryValueReadJs::Init(env, exports);
  ImmSymlinkValueReadJs::Init(env, exports);
  ImmCmdIncludeValueReadJs::Init(env, exports);
  ImmAstContextJs::Init(env, exports);
  ImmAstVersionJs::Init(env, exports);
  ImmAdapterJs::Init(env, exports);
  OrgParseFragmentJs::Init(env, exports);
  OrgParseParametersJs::Init(env, exports);
  OrgDirectoryParseParametersJs::Init(env, exports);
  OrgYamlExportOptsJs::Init(env, exports);
  OrgTreeExportOptsJs::Init(env, exports);
  AstTrackingPathJs::Init(env, exports);
  AstTrackingAlternativesJs::Init(env, exports);
  AstTrackingGroupJs::Init(env, exports);
  AstTrackingMapJs::Init(env, exports);
  SequenceSegmentJs::Init(env, exports);
  SequenceSegmentGroupJs::Init(env, exports);
  SequenceAnnotationTagJs::Init(env, exports);
  SequenceAnnotationJs::Init(env, exports);
  MapLinkJs::Init(env, exports);
  MapNodePropJs::Init(env, exports);
  MapEdgePropJs::Init(env, exports);
  MapNodeJs::Init(env, exports);
  MapEdgeJs::Init(env, exports);
  MapGraphJs::Init(env, exports);
  MapGraphStateJs::Init(env, exports);
  LispCodeJs::Init(env, exports);
  TblfmJs::Init(env, exports);
  AttrValueJs::Init(env, exports);
  HashTagFlatJs::Init(env, exports);
  HashTagTextJs::Init(env, exports);
  SubtreePathJs::Init(env, exports);
  LinkTargetJs::Init(env, exports);
  SubtreeLogHeadJs::Init(env, exports);
  SubtreeCompletionJs::Init(env, exports);
  AttrListJs::Init(env, exports);
  AttrGroupJs::Init(env, exports);
  OrgCodeEvalInputJs::Init(env, exports);
  OrgCodeEvalOutputJs::Init(env, exports);
  ColumnViewJs::Init(env, exports);
  BlockCodeLineJs::Init(env, exports);
  DocumentExportConfigJs::Init(env, exports);
  SubtreePeriodJs::Init(env, exports);
  NamedPropertyJs::Init(env, exports);
  NoneJs::Init(env, exports);
  ErrorItemJs::Init(env, exports);
  ErrorGroupJs::Init(env, exports);
  StmtListJs::Init(env, exports);
  EmptyJs::Init(env, exports);
  TimeJs::Init(env, exports);
  TimeRangeJs::Init(env, exports);
  MacroJs::Init(env, exports);
  SymbolJs::Init(env, exports);
  RadioTargetJs::Init(env, exports);
  LatexJs::Init(env, exports);
  SubtreeLogJs::Init(env, exports);
  SubtreeJs::Init(env, exports);
  ColonExampleJs::Init(env, exports);
  CallJs::Init(env, exports);
  ListItemJs::Init(env, exports);
  DocumentOptionsJs::Init(env, exports);
  DocumentFragmentJs::Init(env, exports);
  CriticMarkupJs::Init(env, exports);
  DocumentJs::Init(env, exports);
  FileTargetJs::Init(env, exports);
  TextSeparatorJs::Init(env, exports);
  DocumentGroupJs::Init(env, exports);
  FileJs::Init(env, exports);
  DirectoryJs::Init(env, exports);
  SymlinkJs::Init(env, exports);
  CmdIncludeJs::Init(env, exports);
  MapConfigJs::Init(env, exports);
  ImmIdTNone::Init(env, exports);
  ImmIdTErrorItem::Init(env, exports);
  ImmIdTErrorGroup::Init(env, exports);
  ImmIdTStmt::Init(env, exports);
  ImmIdTInline::Init(env, exports);
  ImmIdTStmtList::Init(env, exports);
  ImmIdTEmpty::Init(env, exports);
  ImmIdTCmd::Init(env, exports);
  ImmIdTBlock::Init(env, exports);
  ImmIdTLineCommand::Init(env, exports);
  ImmIdTAttached::Init(env, exports);
  ImmIdTLeaf::Init(env, exports);
  ImmIdTCmdCaption::Init(env, exports);
  ImmIdTCmdColumns::Init(env, exports);
  ImmIdTCmdName::Init(env, exports);
  ImmIdTCmdCustomArgs::Init(env, exports);
  ImmIdTCmdCustomRaw::Init(env, exports);
  ImmIdTCmdCustomText::Init(env, exports);
  ImmIdTCmdCall::Init(env, exports);
  ImmIdTCmdTblfm::Init(env, exports);
  ImmIdTHashTag::Init(env, exports);
  ImmIdTInlineFootnote::Init(env, exports);
  ImmIdTInlineExport::Init(env, exports);
  ImmIdTTime::Init(env, exports);
  ImmIdTTimeRange::Init(env, exports);
  ImmIdTMacro::Init(env, exports);
  ImmIdTSymbol::Init(env, exports);
  ImmIdTEscaped::Init(env, exports);
  ImmIdTNewline::Init(env, exports);
  ImmIdTSpace::Init(env, exports);
  ImmIdTWord::Init(env, exports);
  ImmIdTAtMention::Init(env, exports);
  ImmIdTRawText::Init(env, exports);
  ImmIdTPunctuation::Init(env, exports);
  ImmIdTPlaceholder::Init(env, exports);
  ImmIdTBigIdent::Init(env, exports);
  ImmIdTTextTarget::Init(env, exports);
  ImmIdTMarkup::Init(env, exports);
  ImmIdTBold::Init(env, exports);
  ImmIdTUnderline::Init(env, exports);
  ImmIdTMonospace::Init(env, exports);
  ImmIdTMarkQuote::Init(env, exports);
  ImmIdTVerbatim::Init(env, exports);
  ImmIdTItalic::Init(env, exports);
  ImmIdTStrike::Init(env, exports);
  ImmIdTPar::Init(env, exports);
  ImmIdTRadioTarget::Init(env, exports);
  ImmIdTLatex::Init(env, exports);
  ImmIdTLink::Init(env, exports);
  ImmIdTBlockCenter::Init(env, exports);
  ImmIdTBlockQuote::Init(env, exports);
  ImmIdTBlockComment::Init(env, exports);
  ImmIdTBlockVerse::Init(env, exports);
  ImmIdTBlockDynamicFallback::Init(env, exports);
  ImmIdTBlockExample::Init(env, exports);
  ImmIdTBlockExport::Init(env, exports);
  ImmIdTBlockAdmonition::Init(env, exports);
  ImmIdTBlockCodeEvalResult::Init(env, exports);
  ImmIdTBlockCode::Init(env, exports);
  ImmIdTSubtreeLog::Init(env, exports);
  ImmIdTSubtree::Init(env, exports);
  ImmIdTCell::Init(env, exports);
  ImmIdTRow::Init(env, exports);
  ImmIdTTable::Init(env, exports);
  ImmIdTParagraph::Init(env, exports);
  ImmIdTColonExample::Init(env, exports);
  ImmIdTCmdAttr::Init(env, exports);
  ImmIdTCmdExport::Init(env, exports);
  ImmIdTCall::Init(env, exports);
  ImmIdTList::Init(env, exports);
  ImmIdTListItem::Init(env, exports);
  ImmIdTDocumentOptions::Init(env, exports);
  ImmIdTDocumentFragment::Init(env, exports);
  ImmIdTCriticMarkup::Init(env, exports);
  ImmIdTDocument::Init(env, exports);
  ImmIdTFileTarget::Init(env, exports);
  ImmIdTTextSeparator::Init(env, exports);
  ImmIdTDocumentGroup::Init(env, exports);
  ImmIdTFile::Init(env, exports);
  ImmIdTDirectory::Init(env, exports);
  ImmIdTSymlink::Init(env, exports);
  ImmIdTCmdInclude::Init(env, exports);
  ImmNoneValueJs::Init(env, exports);
  ImmErrorItemValueJs::Init(env, exports);
  ImmErrorGroupValueJs::Init(env, exports);
  ImmStmtListValueJs::Init(env, exports);
  ImmEmptyValueJs::Init(env, exports);
  ImmCmdCaptionValueJs::Init(env, exports);
  ImmCmdColumnsValueJs::Init(env, exports);
  ImmCmdNameValueJs::Init(env, exports);
  ImmCmdCustomArgsValueJs::Init(env, exports);
  ImmCmdCustomRawValueJs::Init(env, exports);
  ImmCmdCustomTextValueJs::Init(env, exports);
  ImmCmdCallValueJs::Init(env, exports);
  ImmCmdTblfmValueJs::Init(env, exports);
  ImmHashTagValueJs::Init(env, exports);
  ImmInlineFootnoteValueJs::Init(env, exports);
  ImmInlineExportValueJs::Init(env, exports);
  ImmTimeValueJs::Init(env, exports);
  ImmTimeRangeValueJs::Init(env, exports);
  ImmMacroValueJs::Init(env, exports);
  ImmSymbolValueJs::Init(env, exports);
  ImmEscapedValueJs::Init(env, exports);
  ImmNewlineValueJs::Init(env, exports);
  ImmSpaceValueJs::Init(env, exports);
  ImmWordValueJs::Init(env, exports);
  ImmAtMentionValueJs::Init(env, exports);
  ImmRawTextValueJs::Init(env, exports);
  ImmPunctuationValueJs::Init(env, exports);
  ImmPlaceholderValueJs::Init(env, exports);
  ImmBigIdentValueJs::Init(env, exports);
  ImmTextTargetValueJs::Init(env, exports);
  ImmBoldValueJs::Init(env, exports);
  ImmUnderlineValueJs::Init(env, exports);
  ImmMonospaceValueJs::Init(env, exports);
  ImmMarkQuoteValueJs::Init(env, exports);
  ImmVerbatimValueJs::Init(env, exports);
  ImmItalicValueJs::Init(env, exports);
  ImmStrikeValueJs::Init(env, exports);
  ImmParValueJs::Init(env, exports);
  ImmRadioTargetValueJs::Init(env, exports);
  ImmLatexValueJs::Init(env, exports);
  ImmLinkValueJs::Init(env, exports);
  ImmBlockCenterValueJs::Init(env, exports);
  ImmBlockQuoteValueJs::Init(env, exports);
  ImmBlockCommentValueJs::Init(env, exports);
  ImmBlockVerseValueJs::Init(env, exports);
  ImmBlockDynamicFallbackValueJs::Init(env, exports);
  ImmBlockExampleValueJs::Init(env, exports);
  ImmBlockExportValueJs::Init(env, exports);
  ImmBlockAdmonitionValueJs::Init(env, exports);
  ImmBlockCodeEvalResultValueJs::Init(env, exports);
  ImmBlockCodeValueJs::Init(env, exports);
  ImmSubtreeLogValueJs::Init(env, exports);
  ImmSubtreeValueJs::Init(env, exports);
  ImmCellValueJs::Init(env, exports);
  ImmRowValueJs::Init(env, exports);
  ImmTableValueJs::Init(env, exports);
  ImmParagraphValueJs::Init(env, exports);
  ImmColonExampleValueJs::Init(env, exports);
  ImmCmdAttrValueJs::Init(env, exports);
  ImmCmdExportValueJs::Init(env, exports);
  ImmCallValueJs::Init(env, exports);
  ImmListValueJs::Init(env, exports);
  ImmListItemValueJs::Init(env, exports);
  ImmDocumentOptionsValueJs::Init(env, exports);
  ImmDocumentFragmentValueJs::Init(env, exports);
  ImmCriticMarkupValueJs::Init(env, exports);
  ImmDocumentValueJs::Init(env, exports);
  ImmFileTargetValueJs::Init(env, exports);
  ImmTextSeparatorValueJs::Init(env, exports);
  ImmDocumentGroupValueJs::Init(env, exports);
  ImmFileValueJs::Init(env, exports);
  ImmDirectoryValueJs::Init(env, exports);
  ImmSymlinkValueJs::Init(env, exports);
  ImmCmdIncludeValueJs::Init(env, exports);
  CmdCustomRawJs::Init(env, exports);
  CmdCustomTextJs::Init(env, exports);
  LinkJs::Init(env, exports);
  BlockCommentJs::Init(env, exports);
  ParagraphJs::Init(env, exports);
  ListJs::Init(env, exports);
  HashTagJs::Init(env, exports);
  InlineFootnoteJs::Init(env, exports);
  InlineExportJs::Init(env, exports);
  EscapedJs::Init(env, exports);
  NewlineJs::Init(env, exports);
  SpaceJs::Init(env, exports);
  WordJs::Init(env, exports);
  AtMentionJs::Init(env, exports);
  RawTextJs::Init(env, exports);
  PunctuationJs::Init(env, exports);
  PlaceholderJs::Init(env, exports);
  BigIdentJs::Init(env, exports);
  TextTargetJs::Init(env, exports);
  BoldJs::Init(env, exports);
  UnderlineJs::Init(env, exports);
  MonospaceJs::Init(env, exports);
  MarkQuoteJs::Init(env, exports);
  VerbatimJs::Init(env, exports);
  ItalicJs::Init(env, exports);
  StrikeJs::Init(env, exports);
  ParJs::Init(env, exports);
  CmdCustomArgsJs::Init(env, exports);
  CmdTblfmJs::Init(env, exports);
  CellJs::Init(env, exports);
  RowJs::Init(env, exports);
  ImmSubtreeAdapter::Init(env, exports);
  ImmNoneAdapter::Init(env, exports);
  ImmErrorItemAdapter::Init(env, exports);
  ImmErrorGroupAdapter::Init(env, exports);
  ImmStmtListAdapter::Init(env, exports);
  ImmEmptyAdapter::Init(env, exports);
  ImmTimeAdapter::Init(env, exports);
  ImmTimeRangeAdapter::Init(env, exports);
  ImmMacroAdapter::Init(env, exports);
  ImmSymbolAdapter::Init(env, exports);
  ImmLatexAdapter::Init(env, exports);
  ImmSubtreeLogAdapter::Init(env, exports);
  ImmColonExampleAdapter::Init(env, exports);
  ImmCallAdapter::Init(env, exports);
  ImmFileAdapter::Init(env, exports);
  ImmDirectoryAdapter::Init(env, exports);
  ImmSymlinkAdapter::Init(env, exports);
  ImmDocumentFragmentAdapter::Init(env, exports);
  ImmCriticMarkupAdapter::Init(env, exports);
  ImmListItemAdapter::Init(env, exports);
  ImmDocumentOptionsAdapter::Init(env, exports);
  ImmDocumentAdapter::Init(env, exports);
  ImmFileTargetAdapter::Init(env, exports);
  ImmTextSeparatorAdapter::Init(env, exports);
  ImmCmdIncludeAdapter::Init(env, exports);
  ImmDocumentGroupAdapter::Init(env, exports);
  BlockCenterJs::Init(env, exports);
  BlockQuoteJs::Init(env, exports);
  BlockVerseJs::Init(env, exports);
  BlockDynamicFallbackJs::Init(env, exports);
  BlockExampleJs::Init(env, exports);
  BlockExportJs::Init(env, exports);
  BlockAdmonitionJs::Init(env, exports);
  BlockCodeEvalResultJs::Init(env, exports);
  BlockCodeJs::Init(env, exports);
  TableJs::Init(env, exports);
  ImmCmdCustomRawAdapter::Init(env, exports);
  ImmCmdCustomTextAdapter::Init(env, exports);
  ImmLinkAdapter::Init(env, exports);
  ImmBlockCommentAdapter::Init(env, exports);
  ImmParagraphAdapter::Init(env, exports);
  ImmListAdapter::Init(env, exports);
  ImmHashTagAdapter::Init(env, exports);
  ImmInlineFootnoteAdapter::Init(env, exports);
  ImmEscapedAdapter::Init(env, exports);
  ImmNewlineAdapter::Init(env, exports);
  ImmSpaceAdapter::Init(env, exports);
  ImmWordAdapter::Init(env, exports);
  ImmAtMentionAdapter::Init(env, exports);
  ImmRawTextAdapter::Init(env, exports);
  ImmPunctuationAdapter::Init(env, exports);
  ImmPlaceholderAdapter::Init(env, exports);
  ImmBigIdentAdapter::Init(env, exports);
  ImmTextTargetAdapter::Init(env, exports);
  ImmBoldAdapter::Init(env, exports);
  ImmUnderlineAdapter::Init(env, exports);
  ImmMonospaceAdapter::Init(env, exports);
  ImmMarkQuoteAdapter::Init(env, exports);
  ImmRadioTargetAdapter::Init(env, exports);
  ImmVerbatimAdapter::Init(env, exports);
  ImmItalicAdapter::Init(env, exports);
  ImmStrikeAdapter::Init(env, exports);
  ImmParAdapter::Init(env, exports);
  CmdCaptionJs::Init(env, exports);
  CmdColumnsJs::Init(env, exports);
  CmdNameJs::Init(env, exports);
  CmdCallJs::Init(env, exports);
  CmdAttrJs::Init(env, exports);
  CmdExportJs::Init(env, exports);
  ImmCmdCustomArgsAdapter::Init(env, exports);
  ImmCmdTblfmAdapter::Init(env, exports);
  ImmCellAdapter::Init(env, exports);
  ImmRowAdapter::Init(env, exports);
  ImmBlockCenterAdapter::Init(env, exports);
  ImmBlockQuoteAdapter::Init(env, exports);
  ImmBlockVerseAdapter::Init(env, exports);
  ImmBlockExampleAdapter::Init(env, exports);
  ImmInlineExportAdapter::Init(env, exports);
  ImmCmdExportAdapter::Init(env, exports);
  ImmBlockExportAdapter::Init(env, exports);
  ImmBlockDynamicFallbackAdapter::Init(env, exports);
  ImmBlockAdmonitionAdapter::Init(env, exports);
  ImmBlockCodeEvalResultAdapter::Init(env, exports);
  ImmBlockCodeAdapter::Init(env, exports);
  ImmTableAdapter::Init(env, exports);
  ImmCmdCaptionAdapter::Init(env, exports);
  ImmCmdColumnsAdapter::Init(env, exports);
  ImmCmdNameAdapter::Init(env, exports);
  ImmCmdCallAdapter::Init(env, exports);
  ImmCmdAttrAdapter::Init(env, exports);
  {
    auto callable = makeCallable(&org::newSemTimeStatic, std::make_tuple(CxxArgSpec<hstd::UserTimeBreakdown>{"breakdown"},
                                                                         CxxArgSpec<bool>{"isActive", 0}));
    exports.Set("newSemTimeStatic", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::parseFile, std::make_tuple(CxxArgSpec<std::string>{"file"},
                                                                  CxxArgSpec<org::OrgParseParameters>{"opts"}));
    exports.Set("parseFile", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::parseString, std::make_tuple(CxxArgSpec<std::string>{"text"}));
    exports.Set("parseString", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::parseStringOpts, std::make_tuple(CxxArgSpec<std::string>{"text"},
                                                                        CxxArgSpec<org::OrgParseParameters>{"opts"}));
    exports.Set("parseStringOpts", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::parseDirectoryOpts, std::make_tuple(CxxArgSpec<std::string>{"path"},
                                                                           CxxArgSpec<org::OrgDirectoryParseParameters>{"opts"}));
    exports.Set("parseDirectoryOpts", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::parseFileWithIncludes, std::make_tuple(CxxArgSpec<std::string>{"file"},
                                                                              CxxArgSpec<org::OrgDirectoryParseParameters>{"opts"}));
    exports.Set("parseFileWithIncludes", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::initImmutableAstContext, std::make_tuple());
    exports.Set("initImmutableAstContext", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::asOneNode, std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::Org>>{"arg"}));
    exports.Set("asOneNode", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::formatToString, std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::Org>>{"arg"}));
    exports.Set("formatToString", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::exportToYamlString, std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::Org>>{"node"},
                                                                           CxxArgSpec<org::OrgYamlExportOpts>{"opts"}));
    exports.Set("exportToYamlString", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::exportToYamlFile, std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::Org>>{"node"},
                                                                         CxxArgSpec<std::string>{"path"},
                                                                         CxxArgSpec<org::OrgYamlExportOpts>{"opts"}));
    exports.Set("exportToYamlFile", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::exportToJsonString, std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::Org>>{"node"}));
    exports.Set("exportToJsonString", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::exportToJsonFile, std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::Org>>{"node"},
                                                                         CxxArgSpec<std::string>{"path"}));
    exports.Set("exportToJsonFile", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::readProtobufFile, std::make_tuple(CxxArgSpec<std::string>{"file"}));
    exports.Set("readProtobufFile", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::exportToProtobufFile, std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::Document>>{"doc"},
                                                                             CxxArgSpec<std::string>{"file"}));
    exports.Set("exportToProtobufFile", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::exportToTreeString, std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::Org>>{"node"},
                                                                           CxxArgSpec<org::OrgTreeExportOpts>{"opts"}));
    exports.Set("exportToTreeString", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::exportToTreeFile, std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::Org>>{"node"},
                                                                         CxxArgSpec<std::string>{"path"},
                                                                         CxxArgSpec<org::OrgTreeExportOpts>{"opts"}));
    exports.Set("exportToTreeFile", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::getAstTrackingMap, std::make_tuple(CxxArgSpec<hstd::Vec<org::sem::SemId<org::sem::Org>>>{"nodes"}));
    exports.Set("getAstTrackingMap", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::getSubnodeGroups, std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::Org>>{"node"},
                                                                         CxxArgSpec<org::AstTrackingMap>{"map"}));
    exports.Set("getSubnodeGroups", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&hstd::annotateSequence, std::make_tuple(CxxArgSpec<hstd::Vec<hstd::SequenceSegmentGroup>>{"groups"},
                                                                          CxxArgSpec<int>{"first"},
                                                                          CxxArgSpec<int>{"last"}));
    exports.Set("annotateSequence", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::graph::registerNode, std::make_tuple(CxxArgSpec<org::graph::MapGraphState>{"s"},
                                                                            CxxArgSpec<org::graph::MapNodeProp>{"node"},
                                                                            CxxArgSpec<org::graph::MapConfig>{"conf"}));
    exports.Set("registerNode", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::graph::addNode, std::make_tuple(CxxArgSpec<org::graph::MapGraphState>{"g"},
                                                                       CxxArgSpec<org::imm::ImmAdapter>{"node"},
                                                                       CxxArgSpec<org::graph::MapConfig>{"conf"}));
    exports.Set("addNode", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::graph::addNodeRec, std::make_tuple(CxxArgSpec<org::graph::MapGraphState>{"g"},
                                                                          CxxArgSpec<org::imm::ImmAdapter>{"node"},
                                                                          CxxArgSpec<org::graph::MapConfig>{"conf"}));
    exports.Set("addNodeRec", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::graph::getUnresolvedSubtreeLinks, std::make_tuple(CxxArgSpec<org::graph::MapGraphState>{"s"},
                                                                                         CxxArgSpec<org::imm::ImmAdapterT<org::imm::ImmSubtree>>{"node"},
                                                                                         CxxArgSpec<org::graph::MapConfig>{"conf"}));
    exports.Set("getUnresolvedSubtreeLinks", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  {
    auto callable = makeCallable(&org::graph::getUnresolvedLink, std::make_tuple(CxxArgSpec<org::graph::MapGraphState>{"s"},
                                                                                 CxxArgSpec<org::imm::ImmAdapterT<org::imm::ImmLink>>{"node"},
                                                                                 CxxArgSpec<org::graph::MapConfig>{"conf"}));
    exports.Set("getUnresolvedLink", Napi::Function::New(env, [callable](Napi::CallbackInfo const& info) -> auto { return WrapFunction(info, callable); }));
  }
  return exports;
}

NODE_API_MODULE(pyhaxorg, InitModule);
/* clang-format on */
