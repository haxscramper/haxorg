/* clang-format off */
#include "node_utils.hpp"
#include "node_org_include.hpp"
using namespace org::bind::js;
struct UserTimeBreakdownJs : public Napi::ObjectWrap<UserTimeBreakdownJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "UserTimeBreakdownJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<hstd::UserTimeBreakdown> _stored;
  hstd::UserTimeBreakdown* getPtr() { return _stored.get(); }
};

struct UserTimeJs : public Napi::ObjectWrap<UserTimeJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "UserTimeJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<hstd::UserTime> _stored;
  hstd::UserTime* getPtr() { return _stored.get(); }
};

struct LineColJs : public Napi::ObjectWrap<LineColJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LineColJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::parse::LineCol> _stored;
  org::parse::LineCol* getPtr() { return _stored.get(); }
};

struct OrgJsonJs : public Napi::ObjectWrap<OrgJsonJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgJsonJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::OrgJson> _stored;
  org::sem::OrgJson* getPtr() { return _stored.get(); }
};

struct OperationsTracerJs : public Napi::ObjectWrap<OperationsTracerJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OperationsTracerJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<hstd::OperationsTracer> _stored;
  hstd::OperationsTracer* getPtr() { return _stored.get(); }
};

struct ImmIdJs : public Napi::ObjectWrap<ImmIdJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmId> _stored;
  org::imm::ImmId* getPtr() { return _stored.get(); }
};

struct ImmPathStepJs : public Napi::ObjectWrap<ImmPathStepJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPathStepJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmPathStep> _stored;
  org::imm::ImmPathStep* getPtr() { return _stored.get(); }
};

struct ImmPathJs : public Napi::ObjectWrap<ImmPathJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPathJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmPath> _stored;
  org::imm::ImmPath* getPtr() { return _stored.get(); }
};

struct ImmUniqIdJs : public Napi::ObjectWrap<ImmUniqIdJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmUniqIdJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmUniqId> _stored;
  org::imm::ImmUniqId* getPtr() { return _stored.get(); }
};

struct ImmNoneValueReadJs : public Napi::ObjectWrap<ImmNoneValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNoneValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNoneValueReadJs", func);
    return exports;
  }
  ImmNoneValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmNoneValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmNoneValueRead> _stored;
  org::imm::ImmNoneValueRead* getPtr() { return _stored.get(); }
};

struct ImmErrorItemValueReadJs : public Napi::ObjectWrap<ImmErrorItemValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorItemValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorItemValueReadJs", func);
    return exports;
  }
  ImmErrorItemValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmErrorItemValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmErrorItemValueRead> _stored;
  org::imm::ImmErrorItemValueRead* getPtr() { return _stored.get(); }
};

struct ImmErrorGroupValueReadJs : public Napi::ObjectWrap<ImmErrorGroupValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorGroupValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorGroupValueReadJs", func);
    return exports;
  }
  ImmErrorGroupValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmErrorGroupValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmErrorGroupValueRead> _stored;
  org::imm::ImmErrorGroupValueRead* getPtr() { return _stored.get(); }
};

struct ImmStmtListValueReadJs : public Napi::ObjectWrap<ImmStmtListValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStmtListValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStmtListValueReadJs", func);
    return exports;
  }
  ImmStmtListValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmStmtListValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmStmtListValueRead> _stored;
  org::imm::ImmStmtListValueRead* getPtr() { return _stored.get(); }
};

struct ImmEmptyValueReadJs : public Napi::ObjectWrap<ImmEmptyValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEmptyValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEmptyValueReadJs", func);
    return exports;
  }
  ImmEmptyValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmEmptyValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmEmptyValueRead> _stored;
  org::imm::ImmEmptyValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdCaptionValueReadJs : public Napi::ObjectWrap<ImmCmdCaptionValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCaptionValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCaptionValueReadJs", func);
    return exports;
  }
  ImmCmdCaptionValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCaptionValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdCaptionValueRead> _stored;
  org::imm::ImmCmdCaptionValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdColumnsValueReadJs : public Napi::ObjectWrap<ImmCmdColumnsValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdColumnsValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdColumnsValueReadJs", func);
    return exports;
  }
  ImmCmdColumnsValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdColumnsValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdColumnsValueRead> _stored;
  org::imm::ImmCmdColumnsValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdNameValueReadJs : public Napi::ObjectWrap<ImmCmdNameValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdNameValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdNameValueReadJs", func);
    return exports;
  }
  ImmCmdNameValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdNameValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdNameValueRead> _stored;
  org::imm::ImmCmdNameValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomArgsValueReadJs : public Napi::ObjectWrap<ImmCmdCustomArgsValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomArgsValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomArgsValueReadJs", func);
    return exports;
  }
  ImmCmdCustomArgsValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomArgsValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdCustomArgsValueRead> _stored;
  org::imm::ImmCmdCustomArgsValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomRawValueReadJs : public Napi::ObjectWrap<ImmCmdCustomRawValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomRawValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomRawValueReadJs", func);
    return exports;
  }
  ImmCmdCustomRawValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomRawValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdCustomRawValueRead> _stored;
  org::imm::ImmCmdCustomRawValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomTextValueReadJs : public Napi::ObjectWrap<ImmCmdCustomTextValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomTextValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomTextValueReadJs", func);
    return exports;
  }
  ImmCmdCustomTextValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomTextValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdCustomTextValueRead> _stored;
  org::imm::ImmCmdCustomTextValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdCallValueReadJs : public Napi::ObjectWrap<ImmCmdCallValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCallValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCallValueReadJs", func);
    return exports;
  }
  ImmCmdCallValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCallValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdCallValueRead> _stored;
  org::imm::ImmCmdCallValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdTblfmValueReadJs : public Napi::ObjectWrap<ImmCmdTblfmValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdTblfmValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdTblfmValueReadJs", func);
    return exports;
  }
  ImmCmdTblfmValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdTblfmValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdTblfmValueRead> _stored;
  org::imm::ImmCmdTblfmValueRead* getPtr() { return _stored.get(); }
};

struct ImmHashTagValueReadJs : public Napi::ObjectWrap<ImmHashTagValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmHashTagValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmHashTagValueReadJs", func);
    return exports;
  }
  ImmHashTagValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmHashTagValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmHashTagValueRead> _stored;
  org::imm::ImmHashTagValueRead* getPtr() { return _stored.get(); }
};

struct ImmInlineFootnoteValueReadJs : public Napi::ObjectWrap<ImmInlineFootnoteValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineFootnoteValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineFootnoteValueReadJs", func);
    return exports;
  }
  ImmInlineFootnoteValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmInlineFootnoteValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmInlineFootnoteValueRead> _stored;
  org::imm::ImmInlineFootnoteValueRead* getPtr() { return _stored.get(); }
};

struct ImmInlineExportValueReadJs : public Napi::ObjectWrap<ImmInlineExportValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineExportValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineExportValueReadJs", func);
    return exports;
  }
  ImmInlineExportValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmInlineExportValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmInlineExportValueRead> _stored;
  org::imm::ImmInlineExportValueRead* getPtr() { return _stored.get(); }
};

struct ImmTimeValueReadJs : public Napi::ObjectWrap<ImmTimeValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeValueReadJs", func);
    return exports;
  }
  ImmTimeValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTimeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmTimeValueRead> _stored;
  org::imm::ImmTimeValueRead* getPtr() { return _stored.get(); }
};

struct ImmTimeRangeValueReadJs : public Napi::ObjectWrap<ImmTimeRangeValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeRangeValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeRangeValueReadJs", func);
    return exports;
  }
  ImmTimeRangeValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTimeRangeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmTimeRangeValueRead> _stored;
  org::imm::ImmTimeRangeValueRead* getPtr() { return _stored.get(); }
};

struct ImmMacroValueReadJs : public Napi::ObjectWrap<ImmMacroValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMacroValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMacroValueReadJs", func);
    return exports;
  }
  ImmMacroValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMacroValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmMacroValueRead> _stored;
  org::imm::ImmMacroValueRead* getPtr() { return _stored.get(); }
};

struct ImmSymbolValueReadJs : public Napi::ObjectWrap<ImmSymbolValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymbolValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymbolValueReadJs", func);
    return exports;
  }
  ImmSymbolValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSymbolValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmSymbolValueRead> _stored;
  org::imm::ImmSymbolValueRead* getPtr() { return _stored.get(); }
};

struct ImmEscapedValueReadJs : public Napi::ObjectWrap<ImmEscapedValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEscapedValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEscapedValueReadJs", func);
    return exports;
  }
  ImmEscapedValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmEscapedValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmEscapedValueRead> _stored;
  org::imm::ImmEscapedValueRead* getPtr() { return _stored.get(); }
};

struct ImmNewlineValueReadJs : public Napi::ObjectWrap<ImmNewlineValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNewlineValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNewlineValueReadJs", func);
    return exports;
  }
  ImmNewlineValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmNewlineValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmNewlineValueRead> _stored;
  org::imm::ImmNewlineValueRead* getPtr() { return _stored.get(); }
};

struct ImmSpaceValueReadJs : public Napi::ObjectWrap<ImmSpaceValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSpaceValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSpaceValueReadJs", func);
    return exports;
  }
  ImmSpaceValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSpaceValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmSpaceValueRead> _stored;
  org::imm::ImmSpaceValueRead* getPtr() { return _stored.get(); }
};

struct ImmWordValueReadJs : public Napi::ObjectWrap<ImmWordValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmWordValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmWordValueReadJs", func);
    return exports;
  }
  ImmWordValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmWordValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmWordValueRead> _stored;
  org::imm::ImmWordValueRead* getPtr() { return _stored.get(); }
};

struct ImmAtMentionValueReadJs : public Napi::ObjectWrap<ImmAtMentionValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAtMentionValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAtMentionValueReadJs", func);
    return exports;
  }
  ImmAtMentionValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmAtMentionValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAtMentionValueRead> _stored;
  org::imm::ImmAtMentionValueRead* getPtr() { return _stored.get(); }
};

struct ImmRawTextValueReadJs : public Napi::ObjectWrap<ImmRawTextValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRawTextValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRawTextValueReadJs", func);
    return exports;
  }
  ImmRawTextValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRawTextValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmRawTextValueRead> _stored;
  org::imm::ImmRawTextValueRead* getPtr() { return _stored.get(); }
};

struct ImmPunctuationValueReadJs : public Napi::ObjectWrap<ImmPunctuationValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPunctuationValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPunctuationValueReadJs", func);
    return exports;
  }
  ImmPunctuationValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPunctuationValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmPunctuationValueRead> _stored;
  org::imm::ImmPunctuationValueRead* getPtr() { return _stored.get(); }
};

struct ImmPlaceholderValueReadJs : public Napi::ObjectWrap<ImmPlaceholderValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPlaceholderValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPlaceholderValueReadJs", func);
    return exports;
  }
  ImmPlaceholderValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPlaceholderValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmPlaceholderValueRead> _stored;
  org::imm::ImmPlaceholderValueRead* getPtr() { return _stored.get(); }
};

struct ImmBigIdentValueReadJs : public Napi::ObjectWrap<ImmBigIdentValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBigIdentValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBigIdentValueReadJs", func);
    return exports;
  }
  ImmBigIdentValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBigIdentValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBigIdentValueRead> _stored;
  org::imm::ImmBigIdentValueRead* getPtr() { return _stored.get(); }
};

struct ImmTextTargetValueReadJs : public Napi::ObjectWrap<ImmTextTargetValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextTargetValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextTargetValueReadJs", func);
    return exports;
  }
  ImmTextTargetValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTextTargetValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmTextTargetValueRead> _stored;
  org::imm::ImmTextTargetValueRead* getPtr() { return _stored.get(); }
};

struct ImmBoldValueReadJs : public Napi::ObjectWrap<ImmBoldValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBoldValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBoldValueReadJs", func);
    return exports;
  }
  ImmBoldValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBoldValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBoldValueRead> _stored;
  org::imm::ImmBoldValueRead* getPtr() { return _stored.get(); }
};

struct ImmUnderlineValueReadJs : public Napi::ObjectWrap<ImmUnderlineValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmUnderlineValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmUnderlineValueReadJs", func);
    return exports;
  }
  ImmUnderlineValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmUnderlineValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmUnderlineValueRead> _stored;
  org::imm::ImmUnderlineValueRead* getPtr() { return _stored.get(); }
};

struct ImmMonospaceValueReadJs : public Napi::ObjectWrap<ImmMonospaceValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMonospaceValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMonospaceValueReadJs", func);
    return exports;
  }
  ImmMonospaceValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMonospaceValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmMonospaceValueRead> _stored;
  org::imm::ImmMonospaceValueRead* getPtr() { return _stored.get(); }
};

struct ImmMarkQuoteValueReadJs : public Napi::ObjectWrap<ImmMarkQuoteValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMarkQuoteValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMarkQuoteValueReadJs", func);
    return exports;
  }
  ImmMarkQuoteValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMarkQuoteValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmMarkQuoteValueRead> _stored;
  org::imm::ImmMarkQuoteValueRead* getPtr() { return _stored.get(); }
};

struct ImmVerbatimValueReadJs : public Napi::ObjectWrap<ImmVerbatimValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmVerbatimValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmVerbatimValueReadJs", func);
    return exports;
  }
  ImmVerbatimValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmVerbatimValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmVerbatimValueRead> _stored;
  org::imm::ImmVerbatimValueRead* getPtr() { return _stored.get(); }
};

struct ImmItalicValueReadJs : public Napi::ObjectWrap<ImmItalicValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmItalicValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmItalicValueReadJs", func);
    return exports;
  }
  ImmItalicValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmItalicValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmItalicValueRead> _stored;
  org::imm::ImmItalicValueRead* getPtr() { return _stored.get(); }
};

struct ImmStrikeValueReadJs : public Napi::ObjectWrap<ImmStrikeValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStrikeValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStrikeValueReadJs", func);
    return exports;
  }
  ImmStrikeValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmStrikeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmStrikeValueRead> _stored;
  org::imm::ImmStrikeValueRead* getPtr() { return _stored.get(); }
};

struct ImmParValueReadJs : public Napi::ObjectWrap<ImmParValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParValueReadJs", func);
    return exports;
  }
  ImmParValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmParValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmParValueRead> _stored;
  org::imm::ImmParValueRead* getPtr() { return _stored.get(); }
};

struct ImmRadioTargetValueReadJs : public Napi::ObjectWrap<ImmRadioTargetValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRadioTargetValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRadioTargetValueReadJs", func);
    return exports;
  }
  ImmRadioTargetValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRadioTargetValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmRadioTargetValueRead> _stored;
  org::imm::ImmRadioTargetValueRead* getPtr() { return _stored.get(); }
};

struct ImmLatexValueReadJs : public Napi::ObjectWrap<ImmLatexValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLatexValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLatexValueReadJs", func);
    return exports;
  }
  ImmLatexValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmLatexValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmLatexValueRead> _stored;
  org::imm::ImmLatexValueRead* getPtr() { return _stored.get(); }
};

struct ImmLinkValueReadJs : public Napi::ObjectWrap<ImmLinkValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLinkValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLinkValueReadJs", func);
    return exports;
  }
  ImmLinkValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmLinkValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmLinkValueRead> _stored;
  org::imm::ImmLinkValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockCenterValueReadJs : public Napi::ObjectWrap<ImmBlockCenterValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCenterValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCenterValueReadJs", func);
    return exports;
  }
  ImmBlockCenterValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCenterValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockCenterValueRead> _stored;
  org::imm::ImmBlockCenterValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockQuoteValueReadJs : public Napi::ObjectWrap<ImmBlockQuoteValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockQuoteValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockQuoteValueReadJs", func);
    return exports;
  }
  ImmBlockQuoteValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockQuoteValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockQuoteValueRead> _stored;
  org::imm::ImmBlockQuoteValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockCommentValueReadJs : public Napi::ObjectWrap<ImmBlockCommentValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCommentValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCommentValueReadJs", func);
    return exports;
  }
  ImmBlockCommentValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCommentValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockCommentValueRead> _stored;
  org::imm::ImmBlockCommentValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockVerseValueReadJs : public Napi::ObjectWrap<ImmBlockVerseValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockVerseValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockVerseValueReadJs", func);
    return exports;
  }
  ImmBlockVerseValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockVerseValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockVerseValueRead> _stored;
  org::imm::ImmBlockVerseValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockDynamicFallbackValueReadJs : public Napi::ObjectWrap<ImmBlockDynamicFallbackValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockDynamicFallbackValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockDynamicFallbackValueReadJs", func);
    return exports;
  }
  ImmBlockDynamicFallbackValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockDynamicFallbackValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockDynamicFallbackValueRead> _stored;
  org::imm::ImmBlockDynamicFallbackValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockExampleValueReadJs : public Napi::ObjectWrap<ImmBlockExampleValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExampleValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExampleValueReadJs", func);
    return exports;
  }
  ImmBlockExampleValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockExampleValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockExampleValueRead> _stored;
  org::imm::ImmBlockExampleValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockExportValueReadJs : public Napi::ObjectWrap<ImmBlockExportValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExportValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExportValueReadJs", func);
    return exports;
  }
  ImmBlockExportValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockExportValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockExportValueRead> _stored;
  org::imm::ImmBlockExportValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockAdmonitionValueReadJs : public Napi::ObjectWrap<ImmBlockAdmonitionValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockAdmonitionValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockAdmonitionValueReadJs", func);
    return exports;
  }
  ImmBlockAdmonitionValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockAdmonitionValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockAdmonitionValueRead> _stored;
  org::imm::ImmBlockAdmonitionValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockCodeEvalResultValueReadJs : public Napi::ObjectWrap<ImmBlockCodeEvalResultValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeEvalResultValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeEvalResultValueReadJs", func);
    return exports;
  }
  ImmBlockCodeEvalResultValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCodeEvalResultValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockCodeEvalResultValueRead> _stored;
  org::imm::ImmBlockCodeEvalResultValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockCodeValueReadJs : public Napi::ObjectWrap<ImmBlockCodeValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeValueReadJs", func);
    return exports;
  }
  ImmBlockCodeValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCodeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockCodeValueRead> _stored;
  org::imm::ImmBlockCodeValueRead* getPtr() { return _stored.get(); }
};

struct ImmSubtreeLogValueReadJs : public Napi::ObjectWrap<ImmSubtreeLogValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeLogValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeLogValueReadJs", func);
    return exports;
  }
  ImmSubtreeLogValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSubtreeLogValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmSubtreeLogValueRead> _stored;
  org::imm::ImmSubtreeLogValueRead* getPtr() { return _stored.get(); }
};

struct ImmSubtreeValueReadJs : public Napi::ObjectWrap<ImmSubtreeValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeValueReadJs", func);
    return exports;
  }
  ImmSubtreeValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSubtreeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmSubtreeValueRead> _stored;
  org::imm::ImmSubtreeValueRead* getPtr() { return _stored.get(); }
};

struct ImmCellValueReadJs : public Napi::ObjectWrap<ImmCellValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCellValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCellValueReadJs", func);
    return exports;
  }
  ImmCellValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCellValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCellValueRead> _stored;
  org::imm::ImmCellValueRead* getPtr() { return _stored.get(); }
};

struct ImmRowValueReadJs : public Napi::ObjectWrap<ImmRowValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRowValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRowValueReadJs", func);
    return exports;
  }
  ImmRowValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRowValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmRowValueRead> _stored;
  org::imm::ImmRowValueRead* getPtr() { return _stored.get(); }
};

struct ImmTableValueReadJs : public Napi::ObjectWrap<ImmTableValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTableValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTableValueReadJs", func);
    return exports;
  }
  ImmTableValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTableValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmTableValueRead> _stored;
  org::imm::ImmTableValueRead* getPtr() { return _stored.get(); }
};

struct ImmParagraphValueReadJs : public Napi::ObjectWrap<ImmParagraphValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParagraphValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParagraphValueReadJs", func);
    return exports;
  }
  ImmParagraphValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmParagraphValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmParagraphValueRead> _stored;
  org::imm::ImmParagraphValueRead* getPtr() { return _stored.get(); }
};

struct ImmColonExampleValueReadJs : public Napi::ObjectWrap<ImmColonExampleValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmColonExampleValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmColonExampleValueReadJs", func);
    return exports;
  }
  ImmColonExampleValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmColonExampleValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmColonExampleValueRead> _stored;
  org::imm::ImmColonExampleValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdAttrValueReadJs : public Napi::ObjectWrap<ImmCmdAttrValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdAttrValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdAttrValueReadJs", func);
    return exports;
  }
  ImmCmdAttrValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdAttrValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdAttrValueRead> _stored;
  org::imm::ImmCmdAttrValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdExportValueReadJs : public Napi::ObjectWrap<ImmCmdExportValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdExportValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdExportValueReadJs", func);
    return exports;
  }
  ImmCmdExportValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdExportValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdExportValueRead> _stored;
  org::imm::ImmCmdExportValueRead* getPtr() { return _stored.get(); }
};

struct ImmCallValueReadJs : public Napi::ObjectWrap<ImmCallValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCallValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCallValueReadJs", func);
    return exports;
  }
  ImmCallValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCallValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCallValueRead> _stored;
  org::imm::ImmCallValueRead* getPtr() { return _stored.get(); }
};

struct ImmListValueReadJs : public Napi::ObjectWrap<ImmListValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListValueReadJs", func);
    return exports;
  }
  ImmListValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmListValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmListValueRead> _stored;
  org::imm::ImmListValueRead* getPtr() { return _stored.get(); }
};

struct ImmListItemValueReadJs : public Napi::ObjectWrap<ImmListItemValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListItemValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListItemValueReadJs", func);
    return exports;
  }
  ImmListItemValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmListItemValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmListItemValueRead> _stored;
  org::imm::ImmListItemValueRead* getPtr() { return _stored.get(); }
};

struct ImmDocumentOptionsValueReadJs : public Napi::ObjectWrap<ImmDocumentOptionsValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentOptionsValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentOptionsValueReadJs", func);
    return exports;
  }
  ImmDocumentOptionsValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentOptionsValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmDocumentOptionsValueRead> _stored;
  org::imm::ImmDocumentOptionsValueRead* getPtr() { return _stored.get(); }
};

struct ImmDocumentFragmentValueReadJs : public Napi::ObjectWrap<ImmDocumentFragmentValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentFragmentValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentFragmentValueReadJs", func);
    return exports;
  }
  ImmDocumentFragmentValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentFragmentValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmDocumentFragmentValueRead> _stored;
  org::imm::ImmDocumentFragmentValueRead* getPtr() { return _stored.get(); }
};

struct ImmCriticMarkupValueReadJs : public Napi::ObjectWrap<ImmCriticMarkupValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCriticMarkupValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCriticMarkupValueReadJs", func);
    return exports;
  }
  ImmCriticMarkupValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCriticMarkupValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCriticMarkupValueRead> _stored;
  org::imm::ImmCriticMarkupValueRead* getPtr() { return _stored.get(); }
};

struct ImmDocumentValueReadJs : public Napi::ObjectWrap<ImmDocumentValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentValueReadJs", func);
    return exports;
  }
  ImmDocumentValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmDocumentValueRead> _stored;
  org::imm::ImmDocumentValueRead* getPtr() { return _stored.get(); }
};

struct ImmFileTargetValueReadJs : public Napi::ObjectWrap<ImmFileTargetValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileTargetValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileTargetValueReadJs", func);
    return exports;
  }
  ImmFileTargetValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmFileTargetValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmFileTargetValueRead> _stored;
  org::imm::ImmFileTargetValueRead* getPtr() { return _stored.get(); }
};

struct ImmTextSeparatorValueReadJs : public Napi::ObjectWrap<ImmTextSeparatorValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextSeparatorValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextSeparatorValueReadJs", func);
    return exports;
  }
  ImmTextSeparatorValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTextSeparatorValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmTextSeparatorValueRead> _stored;
  org::imm::ImmTextSeparatorValueRead* getPtr() { return _stored.get(); }
};

struct ImmDocumentGroupValueReadJs : public Napi::ObjectWrap<ImmDocumentGroupValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentGroupValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentGroupValueReadJs", func);
    return exports;
  }
  ImmDocumentGroupValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentGroupValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmDocumentGroupValueRead> _stored;
  org::imm::ImmDocumentGroupValueRead* getPtr() { return _stored.get(); }
};

struct ImmFileValueReadJs : public Napi::ObjectWrap<ImmFileValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileValueReadJs", func);
    return exports;
  }
  ImmFileValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmFileValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmFileValueRead> _stored;
  org::imm::ImmFileValueRead* getPtr() { return _stored.get(); }
};

struct ImmDirectoryValueReadJs : public Napi::ObjectWrap<ImmDirectoryValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDirectoryValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDirectoryValueReadJs", func);
    return exports;
  }
  ImmDirectoryValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDirectoryValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmDirectoryValueRead> _stored;
  org::imm::ImmDirectoryValueRead* getPtr() { return _stored.get(); }
};

struct ImmSymlinkValueReadJs : public Napi::ObjectWrap<ImmSymlinkValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymlinkValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymlinkValueReadJs", func);
    return exports;
  }
  ImmSymlinkValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSymlinkValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmSymlinkValueRead> _stored;
  org::imm::ImmSymlinkValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdIncludeValueReadJs : public Napi::ObjectWrap<ImmCmdIncludeValueReadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdIncludeValueReadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdIncludeValueReadJs", func);
    return exports;
  }
  ImmCmdIncludeValueReadJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdIncludeValueReadJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdIncludeValueRead> _stored;
  org::imm::ImmCmdIncludeValueRead* getPtr() { return _stored.get(); }
};

struct ImmAstContextJs : public Napi::ObjectWrap<ImmAstContextJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAstContextJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAstContextJs", func);
    return exports;
  }
  ImmAstContextJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmAstContextJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAstContext> _stored;
  org::imm::ImmAstContext* getPtr() { return _stored.get(); }
};

struct ImmAstVersionJs : public Napi::ObjectWrap<ImmAstVersionJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAstVersionJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmAstVersion> _stored;
  org::imm::ImmAstVersion* getPtr() { return _stored.get(); }
};

struct ImmAdapterJs : public Napi::ObjectWrap<ImmAdapterJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterJs", func);
    return exports;
  }
  ImmAdapterJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmAdapterJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapter> _stored;
  org::imm::ImmAdapter* getPtr() { return _stored.get(); }
};

struct OrgParseFragmentJs : public Napi::ObjectWrap<OrgParseFragmentJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgParseFragmentJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::OrgParseFragment> _stored;
  org::OrgParseFragment* getPtr() { return _stored.get(); }
};

struct OrgParseParametersJs : public Napi::ObjectWrap<OrgParseParametersJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgParseParametersJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::OrgParseParameters> _stored;
  org::OrgParseParameters* getPtr() { return _stored.get(); }
};

struct OrgDirectoryParseParametersJs : public Napi::ObjectWrap<OrgDirectoryParseParametersJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgDirectoryParseParametersJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::OrgDirectoryParseParameters> _stored;
  org::OrgDirectoryParseParameters* getPtr() { return _stored.get(); }
};

struct OrgYamlExportOptsJs : public Napi::ObjectWrap<OrgYamlExportOptsJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgYamlExportOptsJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::OrgYamlExportOpts> _stored;
  org::OrgYamlExportOpts* getPtr() { return _stored.get(); }
};

struct OrgTreeExportOptsJs : public Napi::ObjectWrap<OrgTreeExportOptsJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgTreeExportOptsJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::OrgTreeExportOpts> _stored;
  org::OrgTreeExportOpts* getPtr() { return _stored.get(); }
};

struct AstTrackingPathJs : public Napi::ObjectWrap<AstTrackingPathJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AstTrackingPathJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::AstTrackingPath> _stored;
  org::AstTrackingPath* getPtr() { return _stored.get(); }
};

struct AstTrackingAlternativesJs : public Napi::ObjectWrap<AstTrackingAlternativesJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AstTrackingAlternativesJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::AstTrackingAlternatives> _stored;
  org::AstTrackingAlternatives* getPtr() { return _stored.get(); }
};

struct AstTrackingGroupJs : public Napi::ObjectWrap<AstTrackingGroupJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AstTrackingGroupJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::AstTrackingGroup> _stored;
  org::AstTrackingGroup* getPtr() { return _stored.get(); }
};

struct AstTrackingMapJs : public Napi::ObjectWrap<AstTrackingMapJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AstTrackingMapJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::AstTrackingMap> _stored;
  org::AstTrackingMap* getPtr() { return _stored.get(); }
};

struct SequenceSegmentJs : public Napi::ObjectWrap<SequenceSegmentJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SequenceSegmentJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<hstd::SequenceSegment> _stored;
  hstd::SequenceSegment* getPtr() { return _stored.get(); }
};

struct SequenceSegmentGroupJs : public Napi::ObjectWrap<SequenceSegmentGroupJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SequenceSegmentGroupJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<hstd::SequenceSegmentGroup> _stored;
  hstd::SequenceSegmentGroup* getPtr() { return _stored.get(); }
};

struct SequenceAnnotationTagJs : public Napi::ObjectWrap<SequenceAnnotationTagJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SequenceAnnotationTagJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<hstd::SequenceAnnotationTag> _stored;
  hstd::SequenceAnnotationTag* getPtr() { return _stored.get(); }
};

struct SequenceAnnotationJs : public Napi::ObjectWrap<SequenceAnnotationJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SequenceAnnotationJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<hstd::SequenceAnnotation> _stored;
  hstd::SequenceAnnotation* getPtr() { return _stored.get(); }
};

struct MapLinkJs : public Napi::ObjectWrap<MapLinkJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapLinkJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::graph::MapLink> _stored;
  org::graph::MapLink* getPtr() { return _stored.get(); }
};

struct MapNodePropJs : public Napi::ObjectWrap<MapNodePropJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapNodePropJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::graph::MapNodeProp> _stored;
  org::graph::MapNodeProp* getPtr() { return _stored.get(); }
};

struct MapEdgePropJs : public Napi::ObjectWrap<MapEdgePropJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapEdgePropJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::graph::MapEdgeProp> _stored;
  org::graph::MapEdgeProp* getPtr() { return _stored.get(); }
};

struct MapNodeJs : public Napi::ObjectWrap<MapNodeJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapNodeJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::graph::MapNode> _stored;
  org::graph::MapNode* getPtr() { return _stored.get(); }
};

struct MapEdgeJs : public Napi::ObjectWrap<MapEdgeJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapEdgeJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::graph::MapEdge> _stored;
  org::graph::MapEdge* getPtr() { return _stored.get(); }
};

struct MapGraphJs : public Napi::ObjectWrap<MapGraphJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapGraphJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::graph::MapGraph> _stored;
  org::graph::MapGraph* getPtr() { return _stored.get(); }
};

struct MapGraphStateJs : public Napi::ObjectWrap<MapGraphStateJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapGraphStateJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MapGraphStateJs", func);
    return exports;
  }
  MapGraphStateJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<MapGraphStateJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::graph::MapGraphState> _stored;
  org::graph::MapGraphState* getPtr() { return _stored.get(); }
};

struct LispCodeJs : public Napi::ObjectWrap<LispCodeJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LispCodeJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::LispCode> _stored;
  org::sem::LispCode* getPtr() { return _stored.get(); }
};

struct TblfmJs : public Napi::ObjectWrap<TblfmJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TblfmJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Tblfm> _stored;
  org::sem::Tblfm* getPtr() { return _stored.get(); }
};

struct AttrValueJs : public Napi::ObjectWrap<AttrValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AttrValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::AttrValue> _stored;
  org::sem::AttrValue* getPtr() { return _stored.get(); }
};

struct HashTagFlatJs : public Napi::ObjectWrap<HashTagFlatJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "HashTagFlatJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::HashTagFlat> _stored;
  org::sem::HashTagFlat* getPtr() { return _stored.get(); }
};

struct HashTagTextJs : public Napi::ObjectWrap<HashTagTextJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "HashTagTextJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::HashTagText> _stored;
  org::sem::HashTagText* getPtr() { return _stored.get(); }
};

struct SubtreePathJs : public Napi::ObjectWrap<SubtreePathJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreePathJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::SubtreePath> _stored;
  org::sem::SubtreePath* getPtr() { return _stored.get(); }
};

struct LinkTargetJs : public Napi::ObjectWrap<LinkTargetJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LinkTargetJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::LinkTarget> _stored;
  org::sem::LinkTarget* getPtr() { return _stored.get(); }
};

struct SubtreeLogHeadJs : public Napi::ObjectWrap<SubtreeLogHeadJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreeLogHeadJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::SubtreeLogHead> _stored;
  org::sem::SubtreeLogHead* getPtr() { return _stored.get(); }
};

struct SubtreeCompletionJs : public Napi::ObjectWrap<SubtreeCompletionJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreeCompletionJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::SubtreeCompletion> _stored;
  org::sem::SubtreeCompletion* getPtr() { return _stored.get(); }
};

struct AttrListJs : public Napi::ObjectWrap<AttrListJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AttrListJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::AttrList> _stored;
  org::sem::AttrList* getPtr() { return _stored.get(); }
};

struct AttrGroupJs : public Napi::ObjectWrap<AttrGroupJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AttrGroupJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::AttrGroup> _stored;
  org::sem::AttrGroup* getPtr() { return _stored.get(); }
};

struct OrgCodeEvalInputJs : public Napi::ObjectWrap<OrgCodeEvalInputJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgCodeEvalInputJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::OrgCodeEvalInput> _stored;
  org::sem::OrgCodeEvalInput* getPtr() { return _stored.get(); }
};

struct OrgCodeEvalOutputJs : public Napi::ObjectWrap<OrgCodeEvalOutputJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgCodeEvalOutputJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::OrgCodeEvalOutput> _stored;
  org::sem::OrgCodeEvalOutput* getPtr() { return _stored.get(); }
};

struct ColumnViewJs : public Napi::ObjectWrap<ColumnViewJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ColumnViewJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::ColumnView> _stored;
  org::sem::ColumnView* getPtr() { return _stored.get(); }
};

struct BlockCodeLineJs : public Napi::ObjectWrap<BlockCodeLineJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCodeLineJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::BlockCodeLine> _stored;
  org::sem::BlockCodeLine* getPtr() { return _stored.get(); }
};

struct DocumentExportConfigJs : public Napi::ObjectWrap<DocumentExportConfigJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentExportConfigJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::DocumentExportConfig> _stored;
  org::sem::DocumentExportConfig* getPtr() { return _stored.get(); }
};

struct SubtreePeriodJs : public Napi::ObjectWrap<SubtreePeriodJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreePeriodJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::SubtreePeriod> _stored;
  org::sem::SubtreePeriod* getPtr() { return _stored.get(); }
};

struct NamedPropertyJs : public Napi::ObjectWrap<NamedPropertyJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "NamedPropertyJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::NamedProperty> _stored;
  org::sem::NamedProperty* getPtr() { return _stored.get(); }
};

struct NoneJs : public Napi::ObjectWrap<NoneJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "NoneJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::None> _stored;
  org::sem::None* getPtr() { return _stored.get(); }
};

struct ErrorItemJs : public Napi::ObjectWrap<ErrorItemJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ErrorItemJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::ErrorItem> _stored;
  org::sem::ErrorItem* getPtr() { return _stored.get(); }
};

struct ErrorGroupJs : public Napi::ObjectWrap<ErrorGroupJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ErrorGroupJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::ErrorGroup> _stored;
  org::sem::ErrorGroup* getPtr() { return _stored.get(); }
};

struct StmtListJs : public Napi::ObjectWrap<StmtListJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "StmtListJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::StmtList> _stored;
  org::sem::StmtList* getPtr() { return _stored.get(); }
};

struct EmptyJs : public Napi::ObjectWrap<EmptyJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "EmptyJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Empty> _stored;
  org::sem::Empty* getPtr() { return _stored.get(); }
};

struct TimeJs : public Napi::ObjectWrap<TimeJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TimeJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Time> _stored;
  org::sem::Time* getPtr() { return _stored.get(); }
};

struct TimeRangeJs : public Napi::ObjectWrap<TimeRangeJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TimeRangeJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::TimeRange> _stored;
  org::sem::TimeRange* getPtr() { return _stored.get(); }
};

struct MacroJs : public Napi::ObjectWrap<MacroJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MacroJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Macro> _stored;
  org::sem::Macro* getPtr() { return _stored.get(); }
};

struct SymbolJs : public Napi::ObjectWrap<SymbolJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SymbolJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Symbol> _stored;
  org::sem::Symbol* getPtr() { return _stored.get(); }
};

struct RadioTargetJs : public Napi::ObjectWrap<RadioTargetJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "RadioTargetJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::RadioTarget> _stored;
  org::sem::RadioTarget* getPtr() { return _stored.get(); }
};

struct LatexJs : public Napi::ObjectWrap<LatexJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LatexJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Latex> _stored;
  org::sem::Latex* getPtr() { return _stored.get(); }
};

struct SubtreeLogJs : public Napi::ObjectWrap<SubtreeLogJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreeLogJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::SubtreeLog> _stored;
  org::sem::SubtreeLog* getPtr() { return _stored.get(); }
};

struct SubtreeJs : public Napi::ObjectWrap<SubtreeJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreeJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Subtree> _stored;
  org::sem::Subtree* getPtr() { return _stored.get(); }
};

struct ColonExampleJs : public Napi::ObjectWrap<ColonExampleJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ColonExampleJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::ColonExample> _stored;
  org::sem::ColonExample* getPtr() { return _stored.get(); }
};

struct CallJs : public Napi::ObjectWrap<CallJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CallJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Call> _stored;
  org::sem::Call* getPtr() { return _stored.get(); }
};

struct ListItemJs : public Napi::ObjectWrap<ListItemJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ListItemJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::ListItem> _stored;
  org::sem::ListItem* getPtr() { return _stored.get(); }
};

struct DocumentOptionsJs : public Napi::ObjectWrap<DocumentOptionsJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentOptionsJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::DocumentOptions> _stored;
  org::sem::DocumentOptions* getPtr() { return _stored.get(); }
};

struct DocumentFragmentJs : public Napi::ObjectWrap<DocumentFragmentJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentFragmentJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::DocumentFragment> _stored;
  org::sem::DocumentFragment* getPtr() { return _stored.get(); }
};

struct CriticMarkupJs : public Napi::ObjectWrap<CriticMarkupJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CriticMarkupJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::CriticMarkup> _stored;
  org::sem::CriticMarkup* getPtr() { return _stored.get(); }
};

struct DocumentJs : public Napi::ObjectWrap<DocumentJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Document> _stored;
  org::sem::Document* getPtr() { return _stored.get(); }
};

struct FileTargetJs : public Napi::ObjectWrap<FileTargetJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "FileTargetJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::FileTarget> _stored;
  org::sem::FileTarget* getPtr() { return _stored.get(); }
};

struct TextSeparatorJs : public Napi::ObjectWrap<TextSeparatorJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TextSeparatorJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::TextSeparator> _stored;
  org::sem::TextSeparator* getPtr() { return _stored.get(); }
};

struct DocumentGroupJs : public Napi::ObjectWrap<DocumentGroupJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentGroupJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::DocumentGroup> _stored;
  org::sem::DocumentGroup* getPtr() { return _stored.get(); }
};

struct FileJs : public Napi::ObjectWrap<FileJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "FileJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::File> _stored;
  org::sem::File* getPtr() { return _stored.get(); }
};

struct DirectoryJs : public Napi::ObjectWrap<DirectoryJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DirectoryJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Directory> _stored;
  org::sem::Directory* getPtr() { return _stored.get(); }
};

struct SymlinkJs : public Napi::ObjectWrap<SymlinkJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SymlinkJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Symlink> _stored;
  org::sem::Symlink* getPtr() { return _stored.get(); }
};

struct CmdIncludeJs : public Napi::ObjectWrap<CmdIncludeJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdIncludeJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::CmdInclude> _stored;
  org::sem::CmdInclude* getPtr() { return _stored.get(); }
};

struct MapConfigJs : public Napi::ObjectWrap<MapConfigJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapConfigJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::graph::MapConfig> _stored;
  org::graph::MapConfig* getPtr() { return _stored.get(); }
};

struct ImmIdTNone : public Napi::ObjectWrap<ImmIdTNone> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTNone", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmNone>> _stored;
  org::imm::ImmIdT<org::imm::ImmNone>* getPtr() { return _stored.get(); }
};

struct ImmIdTErrorItem : public Napi::ObjectWrap<ImmIdTErrorItem> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTErrorItem", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmErrorItem>> _stored;
  org::imm::ImmIdT<org::imm::ImmErrorItem>* getPtr() { return _stored.get(); }
};

struct ImmIdTErrorGroup : public Napi::ObjectWrap<ImmIdTErrorGroup> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTErrorGroup", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmErrorGroup>> _stored;
  org::imm::ImmIdT<org::imm::ImmErrorGroup>* getPtr() { return _stored.get(); }
};

struct ImmIdTStmt : public Napi::ObjectWrap<ImmIdTStmt> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTStmt", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmStmt>> _stored;
  org::imm::ImmIdT<org::imm::ImmStmt>* getPtr() { return _stored.get(); }
};

struct ImmIdTInline : public Napi::ObjectWrap<ImmIdTInline> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTInline", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmInline>> _stored;
  org::imm::ImmIdT<org::imm::ImmInline>* getPtr() { return _stored.get(); }
};

struct ImmIdTStmtList : public Napi::ObjectWrap<ImmIdTStmtList> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTStmtList", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmStmtList>> _stored;
  org::imm::ImmIdT<org::imm::ImmStmtList>* getPtr() { return _stored.get(); }
};

struct ImmIdTEmpty : public Napi::ObjectWrap<ImmIdTEmpty> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTEmpty", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmEmpty>> _stored;
  org::imm::ImmIdT<org::imm::ImmEmpty>* getPtr() { return _stored.get(); }
};

struct ImmIdTCmd : public Napi::ObjectWrap<ImmIdTCmd> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmd", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmd>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmd>* getPtr() { return _stored.get(); }
};

struct ImmIdTBlock : public Napi::ObjectWrap<ImmIdTBlock> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlock", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlock>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlock>* getPtr() { return _stored.get(); }
};

struct ImmIdTLineCommand : public Napi::ObjectWrap<ImmIdTLineCommand> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTLineCommand", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmLineCommand>> _stored;
  org::imm::ImmIdT<org::imm::ImmLineCommand>* getPtr() { return _stored.get(); }
};

struct ImmIdTAttached : public Napi::ObjectWrap<ImmIdTAttached> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTAttached", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmAttached>> _stored;
  org::imm::ImmIdT<org::imm::ImmAttached>* getPtr() { return _stored.get(); }
};

struct ImmIdTLeaf : public Napi::ObjectWrap<ImmIdTLeaf> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTLeaf", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmLeaf>> _stored;
  org::imm::ImmIdT<org::imm::ImmLeaf>* getPtr() { return _stored.get(); }
};

struct ImmIdTCmdCaption : public Napi::ObjectWrap<ImmIdTCmdCaption> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdCaption", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCaption>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdCaption>* getPtr() { return _stored.get(); }
};

struct ImmIdTCmdColumns : public Napi::ObjectWrap<ImmIdTCmdColumns> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdColumns", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdColumns>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdColumns>* getPtr() { return _stored.get(); }
};

struct ImmIdTCmdName : public Napi::ObjectWrap<ImmIdTCmdName> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdName", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdName>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdName>* getPtr() { return _stored.get(); }
};

struct ImmIdTCmdCustomArgs : public Napi::ObjectWrap<ImmIdTCmdCustomArgs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdCustomArgs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCustomArgs>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdCustomArgs>* getPtr() { return _stored.get(); }
};

struct ImmIdTCmdCustomRaw : public Napi::ObjectWrap<ImmIdTCmdCustomRaw> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdCustomRaw", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCustomRaw>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdCustomRaw>* getPtr() { return _stored.get(); }
};

struct ImmIdTCmdCustomText : public Napi::ObjectWrap<ImmIdTCmdCustomText> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdCustomText", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCustomText>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdCustomText>* getPtr() { return _stored.get(); }
};

struct ImmIdTCmdCall : public Napi::ObjectWrap<ImmIdTCmdCall> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdCall", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdCall>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdCall>* getPtr() { return _stored.get(); }
};

struct ImmIdTCmdTblfm : public Napi::ObjectWrap<ImmIdTCmdTblfm> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdTblfm", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdTblfm>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdTblfm>* getPtr() { return _stored.get(); }
};

struct ImmIdTHashTag : public Napi::ObjectWrap<ImmIdTHashTag> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTHashTag", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmHashTag>> _stored;
  org::imm::ImmIdT<org::imm::ImmHashTag>* getPtr() { return _stored.get(); }
};

struct ImmIdTInlineFootnote : public Napi::ObjectWrap<ImmIdTInlineFootnote> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTInlineFootnote", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmInlineFootnote>> _stored;
  org::imm::ImmIdT<org::imm::ImmInlineFootnote>* getPtr() { return _stored.get(); }
};

struct ImmIdTInlineExport : public Napi::ObjectWrap<ImmIdTInlineExport> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTInlineExport", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmInlineExport>> _stored;
  org::imm::ImmIdT<org::imm::ImmInlineExport>* getPtr() { return _stored.get(); }
};

struct ImmIdTTime : public Napi::ObjectWrap<ImmIdTTime> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTTime", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTime>> _stored;
  org::imm::ImmIdT<org::imm::ImmTime>* getPtr() { return _stored.get(); }
};

struct ImmIdTTimeRange : public Napi::ObjectWrap<ImmIdTTimeRange> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTTimeRange", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTimeRange>> _stored;
  org::imm::ImmIdT<org::imm::ImmTimeRange>* getPtr() { return _stored.get(); }
};

struct ImmIdTMacro : public Napi::ObjectWrap<ImmIdTMacro> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTMacro", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmMacro>> _stored;
  org::imm::ImmIdT<org::imm::ImmMacro>* getPtr() { return _stored.get(); }
};

struct ImmIdTSymbol : public Napi::ObjectWrap<ImmIdTSymbol> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTSymbol", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSymbol>> _stored;
  org::imm::ImmIdT<org::imm::ImmSymbol>* getPtr() { return _stored.get(); }
};

struct ImmIdTEscaped : public Napi::ObjectWrap<ImmIdTEscaped> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTEscaped", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmEscaped>> _stored;
  org::imm::ImmIdT<org::imm::ImmEscaped>* getPtr() { return _stored.get(); }
};

struct ImmIdTNewline : public Napi::ObjectWrap<ImmIdTNewline> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTNewline", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmNewline>> _stored;
  org::imm::ImmIdT<org::imm::ImmNewline>* getPtr() { return _stored.get(); }
};

struct ImmIdTSpace : public Napi::ObjectWrap<ImmIdTSpace> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTSpace", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSpace>> _stored;
  org::imm::ImmIdT<org::imm::ImmSpace>* getPtr() { return _stored.get(); }
};

struct ImmIdTWord : public Napi::ObjectWrap<ImmIdTWord> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTWord", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmWord>> _stored;
  org::imm::ImmIdT<org::imm::ImmWord>* getPtr() { return _stored.get(); }
};

struct ImmIdTAtMention : public Napi::ObjectWrap<ImmIdTAtMention> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTAtMention", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmAtMention>> _stored;
  org::imm::ImmIdT<org::imm::ImmAtMention>* getPtr() { return _stored.get(); }
};

struct ImmIdTRawText : public Napi::ObjectWrap<ImmIdTRawText> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTRawText", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmRawText>> _stored;
  org::imm::ImmIdT<org::imm::ImmRawText>* getPtr() { return _stored.get(); }
};

struct ImmIdTPunctuation : public Napi::ObjectWrap<ImmIdTPunctuation> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTPunctuation", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmPunctuation>> _stored;
  org::imm::ImmIdT<org::imm::ImmPunctuation>* getPtr() { return _stored.get(); }
};

struct ImmIdTPlaceholder : public Napi::ObjectWrap<ImmIdTPlaceholder> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTPlaceholder", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmPlaceholder>> _stored;
  org::imm::ImmIdT<org::imm::ImmPlaceholder>* getPtr() { return _stored.get(); }
};

struct ImmIdTBigIdent : public Napi::ObjectWrap<ImmIdTBigIdent> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBigIdent", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBigIdent>> _stored;
  org::imm::ImmIdT<org::imm::ImmBigIdent>* getPtr() { return _stored.get(); }
};

struct ImmIdTTextTarget : public Napi::ObjectWrap<ImmIdTTextTarget> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTTextTarget", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTextTarget>> _stored;
  org::imm::ImmIdT<org::imm::ImmTextTarget>* getPtr() { return _stored.get(); }
};

struct ImmIdTMarkup : public Napi::ObjectWrap<ImmIdTMarkup> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTMarkup", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmMarkup>> _stored;
  org::imm::ImmIdT<org::imm::ImmMarkup>* getPtr() { return _stored.get(); }
};

struct ImmIdTBold : public Napi::ObjectWrap<ImmIdTBold> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBold", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBold>> _stored;
  org::imm::ImmIdT<org::imm::ImmBold>* getPtr() { return _stored.get(); }
};

struct ImmIdTUnderline : public Napi::ObjectWrap<ImmIdTUnderline> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTUnderline", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmUnderline>> _stored;
  org::imm::ImmIdT<org::imm::ImmUnderline>* getPtr() { return _stored.get(); }
};

struct ImmIdTMonospace : public Napi::ObjectWrap<ImmIdTMonospace> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTMonospace", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmMonospace>> _stored;
  org::imm::ImmIdT<org::imm::ImmMonospace>* getPtr() { return _stored.get(); }
};

struct ImmIdTMarkQuote : public Napi::ObjectWrap<ImmIdTMarkQuote> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTMarkQuote", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmMarkQuote>> _stored;
  org::imm::ImmIdT<org::imm::ImmMarkQuote>* getPtr() { return _stored.get(); }
};

struct ImmIdTVerbatim : public Napi::ObjectWrap<ImmIdTVerbatim> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTVerbatim", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmVerbatim>> _stored;
  org::imm::ImmIdT<org::imm::ImmVerbatim>* getPtr() { return _stored.get(); }
};

struct ImmIdTItalic : public Napi::ObjectWrap<ImmIdTItalic> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTItalic", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmItalic>> _stored;
  org::imm::ImmIdT<org::imm::ImmItalic>* getPtr() { return _stored.get(); }
};

struct ImmIdTStrike : public Napi::ObjectWrap<ImmIdTStrike> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTStrike", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmStrike>> _stored;
  org::imm::ImmIdT<org::imm::ImmStrike>* getPtr() { return _stored.get(); }
};

struct ImmIdTPar : public Napi::ObjectWrap<ImmIdTPar> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTPar", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmPar>> _stored;
  org::imm::ImmIdT<org::imm::ImmPar>* getPtr() { return _stored.get(); }
};

struct ImmIdTRadioTarget : public Napi::ObjectWrap<ImmIdTRadioTarget> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTRadioTarget", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmRadioTarget>> _stored;
  org::imm::ImmIdT<org::imm::ImmRadioTarget>* getPtr() { return _stored.get(); }
};

struct ImmIdTLatex : public Napi::ObjectWrap<ImmIdTLatex> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTLatex", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmLatex>> _stored;
  org::imm::ImmIdT<org::imm::ImmLatex>* getPtr() { return _stored.get(); }
};

struct ImmIdTLink : public Napi::ObjectWrap<ImmIdTLink> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTLink", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmLink>> _stored;
  org::imm::ImmIdT<org::imm::ImmLink>* getPtr() { return _stored.get(); }
};

struct ImmIdTBlockCenter : public Napi::ObjectWrap<ImmIdTBlockCenter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockCenter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockCenter>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockCenter>* getPtr() { return _stored.get(); }
};

struct ImmIdTBlockQuote : public Napi::ObjectWrap<ImmIdTBlockQuote> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockQuote", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockQuote>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockQuote>* getPtr() { return _stored.get(); }
};

struct ImmIdTBlockComment : public Napi::ObjectWrap<ImmIdTBlockComment> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockComment", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockComment>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockComment>* getPtr() { return _stored.get(); }
};

struct ImmIdTBlockVerse : public Napi::ObjectWrap<ImmIdTBlockVerse> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockVerse", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockVerse>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockVerse>* getPtr() { return _stored.get(); }
};

struct ImmIdTBlockDynamicFallback : public Napi::ObjectWrap<ImmIdTBlockDynamicFallback> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockDynamicFallback", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockDynamicFallback>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockDynamicFallback>* getPtr() { return _stored.get(); }
};

struct ImmIdTBlockExample : public Napi::ObjectWrap<ImmIdTBlockExample> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockExample", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockExample>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockExample>* getPtr() { return _stored.get(); }
};

struct ImmIdTBlockExport : public Napi::ObjectWrap<ImmIdTBlockExport> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockExport", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockExport>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockExport>* getPtr() { return _stored.get(); }
};

struct ImmIdTBlockAdmonition : public Napi::ObjectWrap<ImmIdTBlockAdmonition> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockAdmonition", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockAdmonition>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockAdmonition>* getPtr() { return _stored.get(); }
};

struct ImmIdTBlockCodeEvalResult : public Napi::ObjectWrap<ImmIdTBlockCodeEvalResult> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockCodeEvalResult", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>* getPtr() { return _stored.get(); }
};

struct ImmIdTBlockCode : public Napi::ObjectWrap<ImmIdTBlockCode> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTBlockCode", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmBlockCode>> _stored;
  org::imm::ImmIdT<org::imm::ImmBlockCode>* getPtr() { return _stored.get(); }
};

struct ImmIdTSubtreeLog : public Napi::ObjectWrap<ImmIdTSubtreeLog> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTSubtreeLog", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> _stored;
  org::imm::ImmIdT<org::imm::ImmSubtreeLog>* getPtr() { return _stored.get(); }
};

struct ImmIdTSubtree : public Napi::ObjectWrap<ImmIdTSubtree> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTSubtree", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSubtree>> _stored;
  org::imm::ImmIdT<org::imm::ImmSubtree>* getPtr() { return _stored.get(); }
};

struct ImmIdTCell : public Napi::ObjectWrap<ImmIdTCell> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCell", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCell>> _stored;
  org::imm::ImmIdT<org::imm::ImmCell>* getPtr() { return _stored.get(); }
};

struct ImmIdTRow : public Napi::ObjectWrap<ImmIdTRow> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTRow", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmRow>> _stored;
  org::imm::ImmIdT<org::imm::ImmRow>* getPtr() { return _stored.get(); }
};

struct ImmIdTTable : public Napi::ObjectWrap<ImmIdTTable> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTTable", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTable>> _stored;
  org::imm::ImmIdT<org::imm::ImmTable>* getPtr() { return _stored.get(); }
};

struct ImmIdTParagraph : public Napi::ObjectWrap<ImmIdTParagraph> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTParagraph", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmParagraph>> _stored;
  org::imm::ImmIdT<org::imm::ImmParagraph>* getPtr() { return _stored.get(); }
};

struct ImmIdTColonExample : public Napi::ObjectWrap<ImmIdTColonExample> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTColonExample", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmColonExample>> _stored;
  org::imm::ImmIdT<org::imm::ImmColonExample>* getPtr() { return _stored.get(); }
};

struct ImmIdTCmdAttr : public Napi::ObjectWrap<ImmIdTCmdAttr> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdAttr", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdAttr>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdAttr>* getPtr() { return _stored.get(); }
};

struct ImmIdTCmdExport : public Napi::ObjectWrap<ImmIdTCmdExport> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdExport", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdExport>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdExport>* getPtr() { return _stored.get(); }
};

struct ImmIdTCall : public Napi::ObjectWrap<ImmIdTCall> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCall", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCall>> _stored;
  org::imm::ImmIdT<org::imm::ImmCall>* getPtr() { return _stored.get(); }
};

struct ImmIdTList : public Napi::ObjectWrap<ImmIdTList> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTList", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmList>> _stored;
  org::imm::ImmIdT<org::imm::ImmList>* getPtr() { return _stored.get(); }
};

struct ImmIdTListItem : public Napi::ObjectWrap<ImmIdTListItem> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTListItem", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmListItem>> _stored;
  org::imm::ImmIdT<org::imm::ImmListItem>* getPtr() { return _stored.get(); }
};

struct ImmIdTDocumentOptions : public Napi::ObjectWrap<ImmIdTDocumentOptions> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTDocumentOptions", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDocumentOptions>> _stored;
  org::imm::ImmIdT<org::imm::ImmDocumentOptions>* getPtr() { return _stored.get(); }
};

struct ImmIdTDocumentFragment : public Napi::ObjectWrap<ImmIdTDocumentFragment> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTDocumentFragment", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDocumentFragment>> _stored;
  org::imm::ImmIdT<org::imm::ImmDocumentFragment>* getPtr() { return _stored.get(); }
};

struct ImmIdTCriticMarkup : public Napi::ObjectWrap<ImmIdTCriticMarkup> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCriticMarkup", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCriticMarkup>> _stored;
  org::imm::ImmIdT<org::imm::ImmCriticMarkup>* getPtr() { return _stored.get(); }
};

struct ImmIdTDocument : public Napi::ObjectWrap<ImmIdTDocument> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTDocument", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDocument>> _stored;
  org::imm::ImmIdT<org::imm::ImmDocument>* getPtr() { return _stored.get(); }
};

struct ImmIdTFileTarget : public Napi::ObjectWrap<ImmIdTFileTarget> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTFileTarget", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmFileTarget>> _stored;
  org::imm::ImmIdT<org::imm::ImmFileTarget>* getPtr() { return _stored.get(); }
};

struct ImmIdTTextSeparator : public Napi::ObjectWrap<ImmIdTTextSeparator> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTTextSeparator", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmTextSeparator>> _stored;
  org::imm::ImmIdT<org::imm::ImmTextSeparator>* getPtr() { return _stored.get(); }
};

struct ImmIdTDocumentGroup : public Napi::ObjectWrap<ImmIdTDocumentGroup> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTDocumentGroup", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDocumentGroup>> _stored;
  org::imm::ImmIdT<org::imm::ImmDocumentGroup>* getPtr() { return _stored.get(); }
};

struct ImmIdTFile : public Napi::ObjectWrap<ImmIdTFile> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTFile", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmFile>> _stored;
  org::imm::ImmIdT<org::imm::ImmFile>* getPtr() { return _stored.get(); }
};

struct ImmIdTDirectory : public Napi::ObjectWrap<ImmIdTDirectory> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTDirectory", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmDirectory>> _stored;
  org::imm::ImmIdT<org::imm::ImmDirectory>* getPtr() { return _stored.get(); }
};

struct ImmIdTSymlink : public Napi::ObjectWrap<ImmIdTSymlink> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTSymlink", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmSymlink>> _stored;
  org::imm::ImmIdT<org::imm::ImmSymlink>* getPtr() { return _stored.get(); }
};

struct ImmIdTCmdInclude : public Napi::ObjectWrap<ImmIdTCmdInclude> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdTCmdInclude", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::imm::ImmIdT<org::imm::ImmCmdInclude>> _stored;
  org::imm::ImmIdT<org::imm::ImmCmdInclude>* getPtr() { return _stored.get(); }
};

struct ImmNoneValueJs : public Napi::ObjectWrap<ImmNoneValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNoneValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNoneValueJs", func);
    return exports;
  }
  ImmNoneValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmNoneValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmNoneValue> _stored;
  org::imm::ImmNoneValue* getPtr() { return _stored.get(); }
};

struct ImmErrorItemValueJs : public Napi::ObjectWrap<ImmErrorItemValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorItemValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorItemValueJs", func);
    return exports;
  }
  ImmErrorItemValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmErrorItemValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmErrorItemValue> _stored;
  org::imm::ImmErrorItemValue* getPtr() { return _stored.get(); }
};

struct ImmErrorGroupValueJs : public Napi::ObjectWrap<ImmErrorGroupValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorGroupValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorGroupValueJs", func);
    return exports;
  }
  ImmErrorGroupValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmErrorGroupValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmErrorGroupValue> _stored;
  org::imm::ImmErrorGroupValue* getPtr() { return _stored.get(); }
};

struct ImmStmtListValueJs : public Napi::ObjectWrap<ImmStmtListValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStmtListValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStmtListValueJs", func);
    return exports;
  }
  ImmStmtListValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmStmtListValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmStmtListValue> _stored;
  org::imm::ImmStmtListValue* getPtr() { return _stored.get(); }
};

struct ImmEmptyValueJs : public Napi::ObjectWrap<ImmEmptyValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEmptyValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEmptyValueJs", func);
    return exports;
  }
  ImmEmptyValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmEmptyValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmEmptyValue> _stored;
  org::imm::ImmEmptyValue* getPtr() { return _stored.get(); }
};

struct ImmCmdCaptionValueJs : public Napi::ObjectWrap<ImmCmdCaptionValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCaptionValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCaptionValueJs", func);
    return exports;
  }
  ImmCmdCaptionValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCaptionValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdCaptionValue> _stored;
  org::imm::ImmCmdCaptionValue* getPtr() { return _stored.get(); }
};

struct ImmCmdColumnsValueJs : public Napi::ObjectWrap<ImmCmdColumnsValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdColumnsValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdColumnsValueJs", func);
    return exports;
  }
  ImmCmdColumnsValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdColumnsValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdColumnsValue> _stored;
  org::imm::ImmCmdColumnsValue* getPtr() { return _stored.get(); }
};

struct ImmCmdNameValueJs : public Napi::ObjectWrap<ImmCmdNameValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdNameValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdNameValueJs", func);
    return exports;
  }
  ImmCmdNameValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdNameValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdNameValue> _stored;
  org::imm::ImmCmdNameValue* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomArgsValueJs : public Napi::ObjectWrap<ImmCmdCustomArgsValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomArgsValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomArgsValueJs", func);
    return exports;
  }
  ImmCmdCustomArgsValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomArgsValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdCustomArgsValue> _stored;
  org::imm::ImmCmdCustomArgsValue* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomRawValueJs : public Napi::ObjectWrap<ImmCmdCustomRawValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomRawValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomRawValueJs", func);
    return exports;
  }
  ImmCmdCustomRawValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomRawValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdCustomRawValue> _stored;
  org::imm::ImmCmdCustomRawValue* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomTextValueJs : public Napi::ObjectWrap<ImmCmdCustomTextValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomTextValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomTextValueJs", func);
    return exports;
  }
  ImmCmdCustomTextValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomTextValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdCustomTextValue> _stored;
  org::imm::ImmCmdCustomTextValue* getPtr() { return _stored.get(); }
};

struct ImmCmdCallValueJs : public Napi::ObjectWrap<ImmCmdCallValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCallValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCallValueJs", func);
    return exports;
  }
  ImmCmdCallValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCallValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdCallValue> _stored;
  org::imm::ImmCmdCallValue* getPtr() { return _stored.get(); }
};

struct ImmCmdTblfmValueJs : public Napi::ObjectWrap<ImmCmdTblfmValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdTblfmValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdTblfmValueJs", func);
    return exports;
  }
  ImmCmdTblfmValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdTblfmValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdTblfmValue> _stored;
  org::imm::ImmCmdTblfmValue* getPtr() { return _stored.get(); }
};

struct ImmHashTagValueJs : public Napi::ObjectWrap<ImmHashTagValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmHashTagValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmHashTagValueJs", func);
    return exports;
  }
  ImmHashTagValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmHashTagValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmHashTagValue> _stored;
  org::imm::ImmHashTagValue* getPtr() { return _stored.get(); }
};

struct ImmInlineFootnoteValueJs : public Napi::ObjectWrap<ImmInlineFootnoteValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineFootnoteValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineFootnoteValueJs", func);
    return exports;
  }
  ImmInlineFootnoteValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmInlineFootnoteValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmInlineFootnoteValue> _stored;
  org::imm::ImmInlineFootnoteValue* getPtr() { return _stored.get(); }
};

struct ImmInlineExportValueJs : public Napi::ObjectWrap<ImmInlineExportValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineExportValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineExportValueJs", func);
    return exports;
  }
  ImmInlineExportValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmInlineExportValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmInlineExportValue> _stored;
  org::imm::ImmInlineExportValue* getPtr() { return _stored.get(); }
};

struct ImmTimeValueJs : public Napi::ObjectWrap<ImmTimeValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeValueJs", func);
    return exports;
  }
  ImmTimeValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTimeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmTimeValue> _stored;
  org::imm::ImmTimeValue* getPtr() { return _stored.get(); }
};

struct ImmTimeRangeValueJs : public Napi::ObjectWrap<ImmTimeRangeValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeRangeValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeRangeValueJs", func);
    return exports;
  }
  ImmTimeRangeValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTimeRangeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmTimeRangeValue> _stored;
  org::imm::ImmTimeRangeValue* getPtr() { return _stored.get(); }
};

struct ImmMacroValueJs : public Napi::ObjectWrap<ImmMacroValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMacroValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMacroValueJs", func);
    return exports;
  }
  ImmMacroValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMacroValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmMacroValue> _stored;
  org::imm::ImmMacroValue* getPtr() { return _stored.get(); }
};

struct ImmSymbolValueJs : public Napi::ObjectWrap<ImmSymbolValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymbolValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymbolValueJs", func);
    return exports;
  }
  ImmSymbolValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSymbolValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmSymbolValue> _stored;
  org::imm::ImmSymbolValue* getPtr() { return _stored.get(); }
};

struct ImmEscapedValueJs : public Napi::ObjectWrap<ImmEscapedValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEscapedValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEscapedValueJs", func);
    return exports;
  }
  ImmEscapedValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmEscapedValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmEscapedValue> _stored;
  org::imm::ImmEscapedValue* getPtr() { return _stored.get(); }
};

struct ImmNewlineValueJs : public Napi::ObjectWrap<ImmNewlineValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNewlineValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNewlineValueJs", func);
    return exports;
  }
  ImmNewlineValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmNewlineValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmNewlineValue> _stored;
  org::imm::ImmNewlineValue* getPtr() { return _stored.get(); }
};

struct ImmSpaceValueJs : public Napi::ObjectWrap<ImmSpaceValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSpaceValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSpaceValueJs", func);
    return exports;
  }
  ImmSpaceValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSpaceValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmSpaceValue> _stored;
  org::imm::ImmSpaceValue* getPtr() { return _stored.get(); }
};

struct ImmWordValueJs : public Napi::ObjectWrap<ImmWordValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmWordValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmWordValueJs", func);
    return exports;
  }
  ImmWordValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmWordValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmWordValue> _stored;
  org::imm::ImmWordValue* getPtr() { return _stored.get(); }
};

struct ImmAtMentionValueJs : public Napi::ObjectWrap<ImmAtMentionValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAtMentionValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAtMentionValueJs", func);
    return exports;
  }
  ImmAtMentionValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmAtMentionValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAtMentionValue> _stored;
  org::imm::ImmAtMentionValue* getPtr() { return _stored.get(); }
};

struct ImmRawTextValueJs : public Napi::ObjectWrap<ImmRawTextValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRawTextValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRawTextValueJs", func);
    return exports;
  }
  ImmRawTextValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRawTextValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmRawTextValue> _stored;
  org::imm::ImmRawTextValue* getPtr() { return _stored.get(); }
};

struct ImmPunctuationValueJs : public Napi::ObjectWrap<ImmPunctuationValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPunctuationValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPunctuationValueJs", func);
    return exports;
  }
  ImmPunctuationValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPunctuationValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmPunctuationValue> _stored;
  org::imm::ImmPunctuationValue* getPtr() { return _stored.get(); }
};

struct ImmPlaceholderValueJs : public Napi::ObjectWrap<ImmPlaceholderValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPlaceholderValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPlaceholderValueJs", func);
    return exports;
  }
  ImmPlaceholderValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPlaceholderValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmPlaceholderValue> _stored;
  org::imm::ImmPlaceholderValue* getPtr() { return _stored.get(); }
};

struct ImmBigIdentValueJs : public Napi::ObjectWrap<ImmBigIdentValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBigIdentValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBigIdentValueJs", func);
    return exports;
  }
  ImmBigIdentValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBigIdentValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBigIdentValue> _stored;
  org::imm::ImmBigIdentValue* getPtr() { return _stored.get(); }
};

struct ImmTextTargetValueJs : public Napi::ObjectWrap<ImmTextTargetValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextTargetValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextTargetValueJs", func);
    return exports;
  }
  ImmTextTargetValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTextTargetValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmTextTargetValue> _stored;
  org::imm::ImmTextTargetValue* getPtr() { return _stored.get(); }
};

struct ImmBoldValueJs : public Napi::ObjectWrap<ImmBoldValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBoldValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBoldValueJs", func);
    return exports;
  }
  ImmBoldValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBoldValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBoldValue> _stored;
  org::imm::ImmBoldValue* getPtr() { return _stored.get(); }
};

struct ImmUnderlineValueJs : public Napi::ObjectWrap<ImmUnderlineValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmUnderlineValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmUnderlineValueJs", func);
    return exports;
  }
  ImmUnderlineValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmUnderlineValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmUnderlineValue> _stored;
  org::imm::ImmUnderlineValue* getPtr() { return _stored.get(); }
};

struct ImmMonospaceValueJs : public Napi::ObjectWrap<ImmMonospaceValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMonospaceValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMonospaceValueJs", func);
    return exports;
  }
  ImmMonospaceValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMonospaceValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmMonospaceValue> _stored;
  org::imm::ImmMonospaceValue* getPtr() { return _stored.get(); }
};

struct ImmMarkQuoteValueJs : public Napi::ObjectWrap<ImmMarkQuoteValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMarkQuoteValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMarkQuoteValueJs", func);
    return exports;
  }
  ImmMarkQuoteValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMarkQuoteValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmMarkQuoteValue> _stored;
  org::imm::ImmMarkQuoteValue* getPtr() { return _stored.get(); }
};

struct ImmVerbatimValueJs : public Napi::ObjectWrap<ImmVerbatimValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmVerbatimValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmVerbatimValueJs", func);
    return exports;
  }
  ImmVerbatimValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmVerbatimValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmVerbatimValue> _stored;
  org::imm::ImmVerbatimValue* getPtr() { return _stored.get(); }
};

struct ImmItalicValueJs : public Napi::ObjectWrap<ImmItalicValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmItalicValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmItalicValueJs", func);
    return exports;
  }
  ImmItalicValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmItalicValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmItalicValue> _stored;
  org::imm::ImmItalicValue* getPtr() { return _stored.get(); }
};

struct ImmStrikeValueJs : public Napi::ObjectWrap<ImmStrikeValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStrikeValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStrikeValueJs", func);
    return exports;
  }
  ImmStrikeValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmStrikeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmStrikeValue> _stored;
  org::imm::ImmStrikeValue* getPtr() { return _stored.get(); }
};

struct ImmParValueJs : public Napi::ObjectWrap<ImmParValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParValueJs", func);
    return exports;
  }
  ImmParValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmParValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmParValue> _stored;
  org::imm::ImmParValue* getPtr() { return _stored.get(); }
};

struct ImmRadioTargetValueJs : public Napi::ObjectWrap<ImmRadioTargetValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRadioTargetValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRadioTargetValueJs", func);
    return exports;
  }
  ImmRadioTargetValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRadioTargetValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmRadioTargetValue> _stored;
  org::imm::ImmRadioTargetValue* getPtr() { return _stored.get(); }
};

struct ImmLatexValueJs : public Napi::ObjectWrap<ImmLatexValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLatexValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLatexValueJs", func);
    return exports;
  }
  ImmLatexValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmLatexValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmLatexValue> _stored;
  org::imm::ImmLatexValue* getPtr() { return _stored.get(); }
};

struct ImmLinkValueJs : public Napi::ObjectWrap<ImmLinkValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLinkValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLinkValueJs", func);
    return exports;
  }
  ImmLinkValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmLinkValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmLinkValue> _stored;
  org::imm::ImmLinkValue* getPtr() { return _stored.get(); }
};

struct ImmBlockCenterValueJs : public Napi::ObjectWrap<ImmBlockCenterValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCenterValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCenterValueJs", func);
    return exports;
  }
  ImmBlockCenterValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCenterValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockCenterValue> _stored;
  org::imm::ImmBlockCenterValue* getPtr() { return _stored.get(); }
};

struct ImmBlockQuoteValueJs : public Napi::ObjectWrap<ImmBlockQuoteValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockQuoteValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockQuoteValueJs", func);
    return exports;
  }
  ImmBlockQuoteValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockQuoteValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockQuoteValue> _stored;
  org::imm::ImmBlockQuoteValue* getPtr() { return _stored.get(); }
};

struct ImmBlockCommentValueJs : public Napi::ObjectWrap<ImmBlockCommentValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCommentValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCommentValueJs", func);
    return exports;
  }
  ImmBlockCommentValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCommentValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockCommentValue> _stored;
  org::imm::ImmBlockCommentValue* getPtr() { return _stored.get(); }
};

struct ImmBlockVerseValueJs : public Napi::ObjectWrap<ImmBlockVerseValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockVerseValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockVerseValueJs", func);
    return exports;
  }
  ImmBlockVerseValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockVerseValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockVerseValue> _stored;
  org::imm::ImmBlockVerseValue* getPtr() { return _stored.get(); }
};

struct ImmBlockDynamicFallbackValueJs : public Napi::ObjectWrap<ImmBlockDynamicFallbackValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockDynamicFallbackValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockDynamicFallbackValueJs", func);
    return exports;
  }
  ImmBlockDynamicFallbackValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockDynamicFallbackValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockDynamicFallbackValue> _stored;
  org::imm::ImmBlockDynamicFallbackValue* getPtr() { return _stored.get(); }
};

struct ImmBlockExampleValueJs : public Napi::ObjectWrap<ImmBlockExampleValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExampleValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExampleValueJs", func);
    return exports;
  }
  ImmBlockExampleValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockExampleValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockExampleValue> _stored;
  org::imm::ImmBlockExampleValue* getPtr() { return _stored.get(); }
};

struct ImmBlockExportValueJs : public Napi::ObjectWrap<ImmBlockExportValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExportValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExportValueJs", func);
    return exports;
  }
  ImmBlockExportValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockExportValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockExportValue> _stored;
  org::imm::ImmBlockExportValue* getPtr() { return _stored.get(); }
};

struct ImmBlockAdmonitionValueJs : public Napi::ObjectWrap<ImmBlockAdmonitionValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockAdmonitionValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockAdmonitionValueJs", func);
    return exports;
  }
  ImmBlockAdmonitionValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockAdmonitionValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockAdmonitionValue> _stored;
  org::imm::ImmBlockAdmonitionValue* getPtr() { return _stored.get(); }
};

struct ImmBlockCodeEvalResultValueJs : public Napi::ObjectWrap<ImmBlockCodeEvalResultValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeEvalResultValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeEvalResultValueJs", func);
    return exports;
  }
  ImmBlockCodeEvalResultValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCodeEvalResultValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockCodeEvalResultValue> _stored;
  org::imm::ImmBlockCodeEvalResultValue* getPtr() { return _stored.get(); }
};

struct ImmBlockCodeValueJs : public Napi::ObjectWrap<ImmBlockCodeValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeValueJs", func);
    return exports;
  }
  ImmBlockCodeValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCodeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmBlockCodeValue> _stored;
  org::imm::ImmBlockCodeValue* getPtr() { return _stored.get(); }
};

struct ImmSubtreeLogValueJs : public Napi::ObjectWrap<ImmSubtreeLogValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeLogValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeLogValueJs", func);
    return exports;
  }
  ImmSubtreeLogValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSubtreeLogValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmSubtreeLogValue> _stored;
  org::imm::ImmSubtreeLogValue* getPtr() { return _stored.get(); }
};

struct ImmSubtreeValueJs : public Napi::ObjectWrap<ImmSubtreeValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeValueJs", func);
    return exports;
  }
  ImmSubtreeValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSubtreeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmSubtreeValue> _stored;
  org::imm::ImmSubtreeValue* getPtr() { return _stored.get(); }
};

struct ImmCellValueJs : public Napi::ObjectWrap<ImmCellValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCellValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCellValueJs", func);
    return exports;
  }
  ImmCellValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCellValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCellValue> _stored;
  org::imm::ImmCellValue* getPtr() { return _stored.get(); }
};

struct ImmRowValueJs : public Napi::ObjectWrap<ImmRowValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRowValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRowValueJs", func);
    return exports;
  }
  ImmRowValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRowValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmRowValue> _stored;
  org::imm::ImmRowValue* getPtr() { return _stored.get(); }
};

struct ImmTableValueJs : public Napi::ObjectWrap<ImmTableValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTableValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTableValueJs", func);
    return exports;
  }
  ImmTableValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTableValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmTableValue> _stored;
  org::imm::ImmTableValue* getPtr() { return _stored.get(); }
};

struct ImmParagraphValueJs : public Napi::ObjectWrap<ImmParagraphValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParagraphValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParagraphValueJs", func);
    return exports;
  }
  ImmParagraphValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmParagraphValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmParagraphValue> _stored;
  org::imm::ImmParagraphValue* getPtr() { return _stored.get(); }
};

struct ImmColonExampleValueJs : public Napi::ObjectWrap<ImmColonExampleValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmColonExampleValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmColonExampleValueJs", func);
    return exports;
  }
  ImmColonExampleValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmColonExampleValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmColonExampleValue> _stored;
  org::imm::ImmColonExampleValue* getPtr() { return _stored.get(); }
};

struct ImmCmdAttrValueJs : public Napi::ObjectWrap<ImmCmdAttrValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdAttrValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdAttrValueJs", func);
    return exports;
  }
  ImmCmdAttrValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdAttrValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdAttrValue> _stored;
  org::imm::ImmCmdAttrValue* getPtr() { return _stored.get(); }
};

struct ImmCmdExportValueJs : public Napi::ObjectWrap<ImmCmdExportValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdExportValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdExportValueJs", func);
    return exports;
  }
  ImmCmdExportValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdExportValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdExportValue> _stored;
  org::imm::ImmCmdExportValue* getPtr() { return _stored.get(); }
};

struct ImmCallValueJs : public Napi::ObjectWrap<ImmCallValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCallValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCallValueJs", func);
    return exports;
  }
  ImmCallValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCallValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCallValue> _stored;
  org::imm::ImmCallValue* getPtr() { return _stored.get(); }
};

struct ImmListValueJs : public Napi::ObjectWrap<ImmListValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListValueJs", func);
    return exports;
  }
  ImmListValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmListValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmListValue> _stored;
  org::imm::ImmListValue* getPtr() { return _stored.get(); }
};

struct ImmListItemValueJs : public Napi::ObjectWrap<ImmListItemValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListItemValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListItemValueJs", func);
    return exports;
  }
  ImmListItemValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmListItemValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmListItemValue> _stored;
  org::imm::ImmListItemValue* getPtr() { return _stored.get(); }
};

struct ImmDocumentOptionsValueJs : public Napi::ObjectWrap<ImmDocumentOptionsValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentOptionsValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentOptionsValueJs", func);
    return exports;
  }
  ImmDocumentOptionsValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentOptionsValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmDocumentOptionsValue> _stored;
  org::imm::ImmDocumentOptionsValue* getPtr() { return _stored.get(); }
};

struct ImmDocumentFragmentValueJs : public Napi::ObjectWrap<ImmDocumentFragmentValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentFragmentValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentFragmentValueJs", func);
    return exports;
  }
  ImmDocumentFragmentValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentFragmentValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmDocumentFragmentValue> _stored;
  org::imm::ImmDocumentFragmentValue* getPtr() { return _stored.get(); }
};

struct ImmCriticMarkupValueJs : public Napi::ObjectWrap<ImmCriticMarkupValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCriticMarkupValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCriticMarkupValueJs", func);
    return exports;
  }
  ImmCriticMarkupValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCriticMarkupValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCriticMarkupValue> _stored;
  org::imm::ImmCriticMarkupValue* getPtr() { return _stored.get(); }
};

struct ImmDocumentValueJs : public Napi::ObjectWrap<ImmDocumentValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentValueJs", func);
    return exports;
  }
  ImmDocumentValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmDocumentValue> _stored;
  org::imm::ImmDocumentValue* getPtr() { return _stored.get(); }
};

struct ImmFileTargetValueJs : public Napi::ObjectWrap<ImmFileTargetValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileTargetValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileTargetValueJs", func);
    return exports;
  }
  ImmFileTargetValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmFileTargetValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmFileTargetValue> _stored;
  org::imm::ImmFileTargetValue* getPtr() { return _stored.get(); }
};

struct ImmTextSeparatorValueJs : public Napi::ObjectWrap<ImmTextSeparatorValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextSeparatorValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextSeparatorValueJs", func);
    return exports;
  }
  ImmTextSeparatorValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTextSeparatorValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmTextSeparatorValue> _stored;
  org::imm::ImmTextSeparatorValue* getPtr() { return _stored.get(); }
};

struct ImmDocumentGroupValueJs : public Napi::ObjectWrap<ImmDocumentGroupValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentGroupValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentGroupValueJs", func);
    return exports;
  }
  ImmDocumentGroupValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentGroupValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmDocumentGroupValue> _stored;
  org::imm::ImmDocumentGroupValue* getPtr() { return _stored.get(); }
};

struct ImmFileValueJs : public Napi::ObjectWrap<ImmFileValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileValueJs", func);
    return exports;
  }
  ImmFileValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmFileValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmFileValue> _stored;
  org::imm::ImmFileValue* getPtr() { return _stored.get(); }
};

struct ImmDirectoryValueJs : public Napi::ObjectWrap<ImmDirectoryValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDirectoryValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDirectoryValueJs", func);
    return exports;
  }
  ImmDirectoryValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDirectoryValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmDirectoryValue> _stored;
  org::imm::ImmDirectoryValue* getPtr() { return _stored.get(); }
};

struct ImmSymlinkValueJs : public Napi::ObjectWrap<ImmSymlinkValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymlinkValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymlinkValueJs", func);
    return exports;
  }
  ImmSymlinkValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSymlinkValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmSymlinkValue> _stored;
  org::imm::ImmSymlinkValue* getPtr() { return _stored.get(); }
};

struct ImmCmdIncludeValueJs : public Napi::ObjectWrap<ImmCmdIncludeValueJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdIncludeValueJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdIncludeValueJs", func);
    return exports;
  }
  ImmCmdIncludeValueJs(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdIncludeValueJs>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmCmdIncludeValue> _stored;
  org::imm::ImmCmdIncludeValue* getPtr() { return _stored.get(); }
};

struct CmdCustomRawJs : public Napi::ObjectWrap<CmdCustomRawJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCustomRawJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::CmdCustomRaw> _stored;
  org::sem::CmdCustomRaw* getPtr() { return _stored.get(); }
};

struct CmdCustomTextJs : public Napi::ObjectWrap<CmdCustomTextJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCustomTextJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::CmdCustomText> _stored;
  org::sem::CmdCustomText* getPtr() { return _stored.get(); }
};

struct LinkJs : public Napi::ObjectWrap<LinkJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LinkJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Link> _stored;
  org::sem::Link* getPtr() { return _stored.get(); }
};

struct BlockCommentJs : public Napi::ObjectWrap<BlockCommentJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCommentJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::BlockComment> _stored;
  org::sem::BlockComment* getPtr() { return _stored.get(); }
};

struct ParagraphJs : public Napi::ObjectWrap<ParagraphJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ParagraphJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Paragraph> _stored;
  org::sem::Paragraph* getPtr() { return _stored.get(); }
};

struct ListJs : public Napi::ObjectWrap<ListJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ListJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::List> _stored;
  org::sem::List* getPtr() { return _stored.get(); }
};

struct HashTagJs : public Napi::ObjectWrap<HashTagJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "HashTagJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::HashTag> _stored;
  org::sem::HashTag* getPtr() { return _stored.get(); }
};

struct InlineFootnoteJs : public Napi::ObjectWrap<InlineFootnoteJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "InlineFootnoteJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::InlineFootnote> _stored;
  org::sem::InlineFootnote* getPtr() { return _stored.get(); }
};

struct InlineExportJs : public Napi::ObjectWrap<InlineExportJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "InlineExportJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::InlineExport> _stored;
  org::sem::InlineExport* getPtr() { return _stored.get(); }
};

struct EscapedJs : public Napi::ObjectWrap<EscapedJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "EscapedJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Escaped> _stored;
  org::sem::Escaped* getPtr() { return _stored.get(); }
};

struct NewlineJs : public Napi::ObjectWrap<NewlineJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "NewlineJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Newline> _stored;
  org::sem::Newline* getPtr() { return _stored.get(); }
};

struct SpaceJs : public Napi::ObjectWrap<SpaceJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SpaceJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Space> _stored;
  org::sem::Space* getPtr() { return _stored.get(); }
};

struct WordJs : public Napi::ObjectWrap<WordJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "WordJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Word> _stored;
  org::sem::Word* getPtr() { return _stored.get(); }
};

struct AtMentionJs : public Napi::ObjectWrap<AtMentionJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AtMentionJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::AtMention> _stored;
  org::sem::AtMention* getPtr() { return _stored.get(); }
};

struct RawTextJs : public Napi::ObjectWrap<RawTextJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "RawTextJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::RawText> _stored;
  org::sem::RawText* getPtr() { return _stored.get(); }
};

struct PunctuationJs : public Napi::ObjectWrap<PunctuationJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "PunctuationJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Punctuation> _stored;
  org::sem::Punctuation* getPtr() { return _stored.get(); }
};

struct PlaceholderJs : public Napi::ObjectWrap<PlaceholderJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "PlaceholderJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Placeholder> _stored;
  org::sem::Placeholder* getPtr() { return _stored.get(); }
};

struct BigIdentJs : public Napi::ObjectWrap<BigIdentJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BigIdentJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::BigIdent> _stored;
  org::sem::BigIdent* getPtr() { return _stored.get(); }
};

struct TextTargetJs : public Napi::ObjectWrap<TextTargetJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TextTargetJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::TextTarget> _stored;
  org::sem::TextTarget* getPtr() { return _stored.get(); }
};

struct BoldJs : public Napi::ObjectWrap<BoldJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BoldJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Bold> _stored;
  org::sem::Bold* getPtr() { return _stored.get(); }
};

struct UnderlineJs : public Napi::ObjectWrap<UnderlineJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "UnderlineJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Underline> _stored;
  org::sem::Underline* getPtr() { return _stored.get(); }
};

struct MonospaceJs : public Napi::ObjectWrap<MonospaceJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MonospaceJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Monospace> _stored;
  org::sem::Monospace* getPtr() { return _stored.get(); }
};

struct MarkQuoteJs : public Napi::ObjectWrap<MarkQuoteJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MarkQuoteJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::MarkQuote> _stored;
  org::sem::MarkQuote* getPtr() { return _stored.get(); }
};

struct VerbatimJs : public Napi::ObjectWrap<VerbatimJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "VerbatimJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Verbatim> _stored;
  org::sem::Verbatim* getPtr() { return _stored.get(); }
};

struct ItalicJs : public Napi::ObjectWrap<ItalicJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ItalicJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Italic> _stored;
  org::sem::Italic* getPtr() { return _stored.get(); }
};

struct StrikeJs : public Napi::ObjectWrap<StrikeJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "StrikeJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Strike> _stored;
  org::sem::Strike* getPtr() { return _stored.get(); }
};

struct ParJs : public Napi::ObjectWrap<ParJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ParJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Par> _stored;
  org::sem::Par* getPtr() { return _stored.get(); }
};

struct CmdCustomArgsJs : public Napi::ObjectWrap<CmdCustomArgsJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCustomArgsJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::CmdCustomArgs> _stored;
  org::sem::CmdCustomArgs* getPtr() { return _stored.get(); }
};

struct CmdTblfmJs : public Napi::ObjectWrap<CmdTblfmJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdTblfmJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::CmdTblfm> _stored;
  org::sem::CmdTblfm* getPtr() { return _stored.get(); }
};

struct CellJs : public Napi::ObjectWrap<CellJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CellJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Cell> _stored;
  org::sem::Cell* getPtr() { return _stored.get(); }
};

struct RowJs : public Napi::ObjectWrap<RowJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "RowJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Row> _stored;
  org::sem::Row* getPtr() { return _stored.get(); }
};

struct ImmSubtreeAdapter : public Napi::ObjectWrap<ImmSubtreeAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeAdapter", func);
    return exports;
  }
  ImmSubtreeAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSubtreeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSubtree>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSubtree>* getPtr() { return _stored.get(); }
};

struct ImmNoneAdapter : public Napi::ObjectWrap<ImmNoneAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNoneAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNoneAdapter", func);
    return exports;
  }
  ImmNoneAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmNoneAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmNone>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmNone>* getPtr() { return _stored.get(); }
};

struct ImmErrorItemAdapter : public Napi::ObjectWrap<ImmErrorItemAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorItemAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorItemAdapter", func);
    return exports;
  }
  ImmErrorItemAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmErrorItemAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmErrorItem>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmErrorItem>* getPtr() { return _stored.get(); }
};

struct ImmErrorGroupAdapter : public Napi::ObjectWrap<ImmErrorGroupAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorGroupAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorGroupAdapter", func);
    return exports;
  }
  ImmErrorGroupAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmErrorGroupAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmErrorGroup>* getPtr() { return _stored.get(); }
};

struct ImmStmtListAdapter : public Napi::ObjectWrap<ImmStmtListAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStmtListAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStmtListAdapter", func);
    return exports;
  }
  ImmStmtListAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmStmtListAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmStmtList>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmStmtList>* getPtr() { return _stored.get(); }
};

struct ImmEmptyAdapter : public Napi::ObjectWrap<ImmEmptyAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEmptyAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEmptyAdapter", func);
    return exports;
  }
  ImmEmptyAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmEmptyAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmEmpty>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmEmpty>* getPtr() { return _stored.get(); }
};

struct ImmTimeAdapter : public Napi::ObjectWrap<ImmTimeAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeAdapter", func);
    return exports;
  }
  ImmTimeAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTimeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTime>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTime>* getPtr() { return _stored.get(); }
};

struct ImmTimeRangeAdapter : public Napi::ObjectWrap<ImmTimeRangeAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeRangeAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeRangeAdapter", func);
    return exports;
  }
  ImmTimeRangeAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTimeRangeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTimeRange>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTimeRange>* getPtr() { return _stored.get(); }
};

struct ImmMacroAdapter : public Napi::ObjectWrap<ImmMacroAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMacroAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMacroAdapter", func);
    return exports;
  }
  ImmMacroAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMacroAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmMacro>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmMacro>* getPtr() { return _stored.get(); }
};

struct ImmSymbolAdapter : public Napi::ObjectWrap<ImmSymbolAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymbolAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymbolAdapter", func);
    return exports;
  }
  ImmSymbolAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSymbolAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSymbol>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSymbol>* getPtr() { return _stored.get(); }
};

struct ImmLatexAdapter : public Napi::ObjectWrap<ImmLatexAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLatexAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLatexAdapter", func);
    return exports;
  }
  ImmLatexAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmLatexAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmLatex>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmLatex>* getPtr() { return _stored.get(); }
};

struct ImmSubtreeLogAdapter : public Napi::ObjectWrap<ImmSubtreeLogAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeLogAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeLogAdapter", func);
    return exports;
  }
  ImmSubtreeLogAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSubtreeLogAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>* getPtr() { return _stored.get(); }
};

struct ImmColonExampleAdapter : public Napi::ObjectWrap<ImmColonExampleAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmColonExampleAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmColonExampleAdapter", func);
    return exports;
  }
  ImmColonExampleAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmColonExampleAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmColonExample>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmColonExample>* getPtr() { return _stored.get(); }
};

struct ImmCallAdapter : public Napi::ObjectWrap<ImmCallAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCallAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCallAdapter", func);
    return exports;
  }
  ImmCallAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCallAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCall>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCall>* getPtr() { return _stored.get(); }
};

struct ImmFileAdapter : public Napi::ObjectWrap<ImmFileAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileAdapter", func);
    return exports;
  }
  ImmFileAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmFileAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmFile>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmFile>* getPtr() { return _stored.get(); }
};

struct ImmDirectoryAdapter : public Napi::ObjectWrap<ImmDirectoryAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDirectoryAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDirectoryAdapter", func);
    return exports;
  }
  ImmDirectoryAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDirectoryAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDirectory>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDirectory>* getPtr() { return _stored.get(); }
};

struct ImmSymlinkAdapter : public Napi::ObjectWrap<ImmSymlinkAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymlinkAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymlinkAdapter", func);
    return exports;
  }
  ImmSymlinkAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSymlinkAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSymlink>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSymlink>* getPtr() { return _stored.get(); }
};

struct ImmDocumentFragmentAdapter : public Napi::ObjectWrap<ImmDocumentFragmentAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentFragmentAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentFragmentAdapter", func);
    return exports;
  }
  ImmDocumentFragmentAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentFragmentAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>* getPtr() { return _stored.get(); }
};

struct ImmCriticMarkupAdapter : public Napi::ObjectWrap<ImmCriticMarkupAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCriticMarkupAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCriticMarkupAdapter", func);
    return exports;
  }
  ImmCriticMarkupAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCriticMarkupAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>* getPtr() { return _stored.get(); }
};

struct ImmListItemAdapter : public Napi::ObjectWrap<ImmListItemAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListItemAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListItemAdapter", func);
    return exports;
  }
  ImmListItemAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmListItemAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmListItem>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmListItem>* getPtr() { return _stored.get(); }
};

struct ImmDocumentOptionsAdapter : public Napi::ObjectWrap<ImmDocumentOptionsAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentOptionsAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentOptionsAdapter", func);
    return exports;
  }
  ImmDocumentOptionsAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentOptionsAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>* getPtr() { return _stored.get(); }
};

struct ImmDocumentAdapter : public Napi::ObjectWrap<ImmDocumentAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentAdapter", func);
    return exports;
  }
  ImmDocumentAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocument>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDocument>* getPtr() { return _stored.get(); }
};

struct ImmFileTargetAdapter : public Napi::ObjectWrap<ImmFileTargetAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileTargetAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileTargetAdapter", func);
    return exports;
  }
  ImmFileTargetAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmFileTargetAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmFileTarget>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmFileTarget>* getPtr() { return _stored.get(); }
};

struct ImmTextSeparatorAdapter : public Napi::ObjectWrap<ImmTextSeparatorAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextSeparatorAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextSeparatorAdapter", func);
    return exports;
  }
  ImmTextSeparatorAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTextSeparatorAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTextSeparator>* getPtr() { return _stored.get(); }
};

struct ImmCmdIncludeAdapter : public Napi::ObjectWrap<ImmCmdIncludeAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdIncludeAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdIncludeAdapter", func);
    return exports;
  }
  ImmCmdIncludeAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdIncludeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdInclude>* getPtr() { return _stored.get(); }
};

struct ImmDocumentGroupAdapter : public Napi::ObjectWrap<ImmDocumentGroupAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentGroupAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentGroupAdapter", func);
    return exports;
  }
  ImmDocumentGroupAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmDocumentGroupAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>* getPtr() { return _stored.get(); }
};

struct BlockCenterJs : public Napi::ObjectWrap<BlockCenterJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCenterJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::BlockCenter> _stored;
  org::sem::BlockCenter* getPtr() { return _stored.get(); }
};

struct BlockQuoteJs : public Napi::ObjectWrap<BlockQuoteJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockQuoteJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::BlockQuote> _stored;
  org::sem::BlockQuote* getPtr() { return _stored.get(); }
};

struct BlockVerseJs : public Napi::ObjectWrap<BlockVerseJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockVerseJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::BlockVerse> _stored;
  org::sem::BlockVerse* getPtr() { return _stored.get(); }
};

struct BlockDynamicFallbackJs : public Napi::ObjectWrap<BlockDynamicFallbackJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockDynamicFallbackJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::BlockDynamicFallback> _stored;
  org::sem::BlockDynamicFallback* getPtr() { return _stored.get(); }
};

struct BlockExampleJs : public Napi::ObjectWrap<BlockExampleJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockExampleJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::BlockExample> _stored;
  org::sem::BlockExample* getPtr() { return _stored.get(); }
};

struct BlockExportJs : public Napi::ObjectWrap<BlockExportJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockExportJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::BlockExport> _stored;
  org::sem::BlockExport* getPtr() { return _stored.get(); }
};

struct BlockAdmonitionJs : public Napi::ObjectWrap<BlockAdmonitionJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockAdmonitionJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::BlockAdmonition> _stored;
  org::sem::BlockAdmonition* getPtr() { return _stored.get(); }
};

struct BlockCodeEvalResultJs : public Napi::ObjectWrap<BlockCodeEvalResultJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCodeEvalResultJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::BlockCodeEvalResult> _stored;
  org::sem::BlockCodeEvalResult* getPtr() { return _stored.get(); }
};

struct BlockCodeJs : public Napi::ObjectWrap<BlockCodeJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCodeJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::BlockCode> _stored;
  org::sem::BlockCode* getPtr() { return _stored.get(); }
};

struct TableJs : public Napi::ObjectWrap<TableJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TableJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::Table> _stored;
  org::sem::Table* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomRawAdapter : public Napi::ObjectWrap<ImmCmdCustomRawAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomRawAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomRawAdapter", func);
    return exports;
  }
  ImmCmdCustomRawAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomRawAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomTextAdapter : public Napi::ObjectWrap<ImmCmdCustomTextAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomTextAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomTextAdapter", func);
    return exports;
  }
  ImmCmdCustomTextAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomTextAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>* getPtr() { return _stored.get(); }
};

struct ImmLinkAdapter : public Napi::ObjectWrap<ImmLinkAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLinkAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLinkAdapter", func);
    return exports;
  }
  ImmLinkAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmLinkAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmLink>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmLink>* getPtr() { return _stored.get(); }
};

struct ImmBlockCommentAdapter : public Napi::ObjectWrap<ImmBlockCommentAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCommentAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCommentAdapter", func);
    return exports;
  }
  ImmBlockCommentAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCommentAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockComment>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockComment>* getPtr() { return _stored.get(); }
};

struct ImmParagraphAdapter : public Napi::ObjectWrap<ImmParagraphAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParagraphAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParagraphAdapter", func);
    return exports;
  }
  ImmParagraphAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmParagraphAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmParagraph>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmParagraph>* getPtr() { return _stored.get(); }
};

struct ImmListAdapter : public Napi::ObjectWrap<ImmListAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListAdapter", func);
    return exports;
  }
  ImmListAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmListAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmList>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmList>* getPtr() { return _stored.get(); }
};

struct ImmHashTagAdapter : public Napi::ObjectWrap<ImmHashTagAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmHashTagAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmHashTagAdapter", func);
    return exports;
  }
  ImmHashTagAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmHashTagAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmHashTag>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmHashTag>* getPtr() { return _stored.get(); }
};

struct ImmInlineFootnoteAdapter : public Napi::ObjectWrap<ImmInlineFootnoteAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineFootnoteAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineFootnoteAdapter", func);
    return exports;
  }
  ImmInlineFootnoteAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmInlineFootnoteAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>* getPtr() { return _stored.get(); }
};

struct ImmEscapedAdapter : public Napi::ObjectWrap<ImmEscapedAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEscapedAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEscapedAdapter", func);
    return exports;
  }
  ImmEscapedAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmEscapedAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmEscaped>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmEscaped>* getPtr() { return _stored.get(); }
};

struct ImmNewlineAdapter : public Napi::ObjectWrap<ImmNewlineAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNewlineAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNewlineAdapter", func);
    return exports;
  }
  ImmNewlineAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmNewlineAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmNewline>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmNewline>* getPtr() { return _stored.get(); }
};

struct ImmSpaceAdapter : public Napi::ObjectWrap<ImmSpaceAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSpaceAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSpaceAdapter", func);
    return exports;
  }
  ImmSpaceAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmSpaceAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSpace>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSpace>* getPtr() { return _stored.get(); }
};

struct ImmWordAdapter : public Napi::ObjectWrap<ImmWordAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmWordAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmWordAdapter", func);
    return exports;
  }
  ImmWordAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmWordAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmWord>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmWord>* getPtr() { return _stored.get(); }
};

struct ImmAtMentionAdapter : public Napi::ObjectWrap<ImmAtMentionAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAtMentionAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAtMentionAdapter", func);
    return exports;
  }
  ImmAtMentionAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmAtMentionAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmAtMention>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmAtMention>* getPtr() { return _stored.get(); }
};

struct ImmRawTextAdapter : public Napi::ObjectWrap<ImmRawTextAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRawTextAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRawTextAdapter", func);
    return exports;
  }
  ImmRawTextAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRawTextAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmRawText>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmRawText>* getPtr() { return _stored.get(); }
};

struct ImmPunctuationAdapter : public Napi::ObjectWrap<ImmPunctuationAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPunctuationAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPunctuationAdapter", func);
    return exports;
  }
  ImmPunctuationAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPunctuationAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmPunctuation>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmPunctuation>* getPtr() { return _stored.get(); }
};

struct ImmPlaceholderAdapter : public Napi::ObjectWrap<ImmPlaceholderAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPlaceholderAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPlaceholderAdapter", func);
    return exports;
  }
  ImmPlaceholderAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmPlaceholderAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmPlaceholder>* getPtr() { return _stored.get(); }
};

struct ImmBigIdentAdapter : public Napi::ObjectWrap<ImmBigIdentAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBigIdentAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBigIdentAdapter", func);
    return exports;
  }
  ImmBigIdentAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBigIdentAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBigIdent>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBigIdent>* getPtr() { return _stored.get(); }
};

struct ImmTextTargetAdapter : public Napi::ObjectWrap<ImmTextTargetAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextTargetAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextTargetAdapter", func);
    return exports;
  }
  ImmTextTargetAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTextTargetAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTextTarget>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTextTarget>* getPtr() { return _stored.get(); }
};

struct ImmBoldAdapter : public Napi::ObjectWrap<ImmBoldAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBoldAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBoldAdapter", func);
    return exports;
  }
  ImmBoldAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBoldAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBold>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBold>* getPtr() { return _stored.get(); }
};

struct ImmUnderlineAdapter : public Napi::ObjectWrap<ImmUnderlineAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmUnderlineAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmUnderlineAdapter", func);
    return exports;
  }
  ImmUnderlineAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmUnderlineAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmUnderline>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmUnderline>* getPtr() { return _stored.get(); }
};

struct ImmMonospaceAdapter : public Napi::ObjectWrap<ImmMonospaceAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMonospaceAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMonospaceAdapter", func);
    return exports;
  }
  ImmMonospaceAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMonospaceAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmMonospace>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmMonospace>* getPtr() { return _stored.get(); }
};

struct ImmMarkQuoteAdapter : public Napi::ObjectWrap<ImmMarkQuoteAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMarkQuoteAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMarkQuoteAdapter", func);
    return exports;
  }
  ImmMarkQuoteAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmMarkQuoteAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmMarkQuote>* getPtr() { return _stored.get(); }
};

struct ImmRadioTargetAdapter : public Napi::ObjectWrap<ImmRadioTargetAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRadioTargetAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRadioTargetAdapter", func);
    return exports;
  }
  ImmRadioTargetAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRadioTargetAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmRadioTarget>* getPtr() { return _stored.get(); }
};

struct ImmVerbatimAdapter : public Napi::ObjectWrap<ImmVerbatimAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmVerbatimAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmVerbatimAdapter", func);
    return exports;
  }
  ImmVerbatimAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmVerbatimAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmVerbatim>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmVerbatim>* getPtr() { return _stored.get(); }
};

struct ImmItalicAdapter : public Napi::ObjectWrap<ImmItalicAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmItalicAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmItalicAdapter", func);
    return exports;
  }
  ImmItalicAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmItalicAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmItalic>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmItalic>* getPtr() { return _stored.get(); }
};

struct ImmStrikeAdapter : public Napi::ObjectWrap<ImmStrikeAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStrikeAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStrikeAdapter", func);
    return exports;
  }
  ImmStrikeAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmStrikeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmStrike>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmStrike>* getPtr() { return _stored.get(); }
};

struct ImmParAdapter : public Napi::ObjectWrap<ImmParAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParAdapter", func);
    return exports;
  }
  ImmParAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmParAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmPar>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmPar>* getPtr() { return _stored.get(); }
};

struct CmdCaptionJs : public Napi::ObjectWrap<CmdCaptionJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCaptionJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::CmdCaption> _stored;
  org::sem::CmdCaption* getPtr() { return _stored.get(); }
};

struct CmdColumnsJs : public Napi::ObjectWrap<CmdColumnsJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdColumnsJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::CmdColumns> _stored;
  org::sem::CmdColumns* getPtr() { return _stored.get(); }
};

struct CmdNameJs : public Napi::ObjectWrap<CmdNameJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdNameJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::CmdName> _stored;
  org::sem::CmdName* getPtr() { return _stored.get(); }
};

struct CmdCallJs : public Napi::ObjectWrap<CmdCallJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCallJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::CmdCall> _stored;
  org::sem::CmdCall* getPtr() { return _stored.get(); }
};

struct CmdAttrJs : public Napi::ObjectWrap<CmdAttrJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdAttrJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::CmdAttr> _stored;
  org::sem::CmdAttr* getPtr() { return _stored.get(); }
};

struct CmdExportJs : public Napi::ObjectWrap<CmdExportJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdExportJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
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
  std::shared_ptr<org::sem::CmdExport> _stored;
  org::sem::CmdExport* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomArgsAdapter : public Napi::ObjectWrap<ImmCmdCustomArgsAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomArgsAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomArgsAdapter", func);
    return exports;
  }
  ImmCmdCustomArgsAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCustomArgsAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>* getPtr() { return _stored.get(); }
};

struct ImmCmdTblfmAdapter : public Napi::ObjectWrap<ImmCmdTblfmAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdTblfmAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdTblfmAdapter", func);
    return exports;
  }
  ImmCmdTblfmAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdTblfmAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>* getPtr() { return _stored.get(); }
};

struct ImmCellAdapter : public Napi::ObjectWrap<ImmCellAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCellAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCellAdapter", func);
    return exports;
  }
  ImmCellAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCellAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCell>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCell>* getPtr() { return _stored.get(); }
};

struct ImmRowAdapter : public Napi::ObjectWrap<ImmRowAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRowAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRowAdapter", func);
    return exports;
  }
  ImmRowAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmRowAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmRow>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmRow>* getPtr() { return _stored.get(); }
};

struct ImmBlockCenterAdapter : public Napi::ObjectWrap<ImmBlockCenterAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCenterAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCenterAdapter", func);
    return exports;
  }
  ImmBlockCenterAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCenterAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockCenter>* getPtr() { return _stored.get(); }
};

struct ImmBlockQuoteAdapter : public Napi::ObjectWrap<ImmBlockQuoteAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockQuoteAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockQuoteAdapter", func);
    return exports;
  }
  ImmBlockQuoteAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockQuoteAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockQuote>* getPtr() { return _stored.get(); }
};

struct ImmBlockVerseAdapter : public Napi::ObjectWrap<ImmBlockVerseAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockVerseAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockVerseAdapter", func);
    return exports;
  }
  ImmBlockVerseAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockVerseAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockVerse>* getPtr() { return _stored.get(); }
};

struct ImmBlockExampleAdapter : public Napi::ObjectWrap<ImmBlockExampleAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExampleAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExampleAdapter", func);
    return exports;
  }
  ImmBlockExampleAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockExampleAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockExample>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockExample>* getPtr() { return _stored.get(); }
};

struct ImmInlineExportAdapter : public Napi::ObjectWrap<ImmInlineExportAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineExportAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineExportAdapter", func);
    return exports;
  }
  ImmInlineExportAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmInlineExportAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmInlineExport>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmInlineExport>* getPtr() { return _stored.get(); }
};

struct ImmCmdExportAdapter : public Napi::ObjectWrap<ImmCmdExportAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdExportAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdExportAdapter", func);
    return exports;
  }
  ImmCmdExportAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdExportAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdExport>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdExport>* getPtr() { return _stored.get(); }
};

struct ImmBlockExportAdapter : public Napi::ObjectWrap<ImmBlockExportAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExportAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExportAdapter", func);
    return exports;
  }
  ImmBlockExportAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockExportAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockExport>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockExport>* getPtr() { return _stored.get(); }
};

struct ImmBlockDynamicFallbackAdapter : public Napi::ObjectWrap<ImmBlockDynamicFallbackAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockDynamicFallbackAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockDynamicFallbackAdapter", func);
    return exports;
  }
  ImmBlockDynamicFallbackAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockDynamicFallbackAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>* getPtr() { return _stored.get(); }
};

struct ImmBlockAdmonitionAdapter : public Napi::ObjectWrap<ImmBlockAdmonitionAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockAdmonitionAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockAdmonitionAdapter", func);
    return exports;
  }
  ImmBlockAdmonitionAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockAdmonitionAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>* getPtr() { return _stored.get(); }
};

struct ImmBlockCodeEvalResultAdapter : public Napi::ObjectWrap<ImmBlockCodeEvalResultAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeEvalResultAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeEvalResultAdapter", func);
    return exports;
  }
  ImmBlockCodeEvalResultAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCodeEvalResultAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>* getPtr() { return _stored.get(); }
};

struct ImmBlockCodeAdapter : public Napi::ObjectWrap<ImmBlockCodeAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeAdapter", func);
    return exports;
  }
  ImmBlockCodeAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmBlockCodeAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockCode>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockCode>* getPtr() { return _stored.get(); }
};

struct ImmTableAdapter : public Napi::ObjectWrap<ImmTableAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTableAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTableAdapter", func);
    return exports;
  }
  ImmTableAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmTableAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTable>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTable>* getPtr() { return _stored.get(); }
};

struct ImmCmdCaptionAdapter : public Napi::ObjectWrap<ImmCmdCaptionAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCaptionAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCaptionAdapter", func);
    return exports;
  }
  ImmCmdCaptionAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCaptionAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCaption>* getPtr() { return _stored.get(); }
};

struct ImmCmdColumnsAdapter : public Napi::ObjectWrap<ImmCmdColumnsAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdColumnsAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdColumnsAdapter", func);
    return exports;
  }
  ImmCmdColumnsAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdColumnsAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdColumns>* getPtr() { return _stored.get(); }
};

struct ImmCmdNameAdapter : public Napi::ObjectWrap<ImmCmdNameAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdNameAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdNameAdapter", func);
    return exports;
  }
  ImmCmdNameAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdNameAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdName>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdName>* getPtr() { return _stored.get(); }
};

struct ImmCmdCallAdapter : public Napi::ObjectWrap<ImmCmdCallAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCallAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCallAdapter", func);
    return exports;
  }
  ImmCmdCallAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdCallAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCall>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCall>* getPtr() { return _stored.get(); }
};

struct ImmCmdAttrAdapter : public Napi::ObjectWrap<ImmCmdAttrAdapter> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdAttrAdapter", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdAttrAdapter", func);
    return exports;
  }
  ImmCmdAttrAdapter(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ImmCmdAttrAdapter>{info} {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdAttr>* getPtr() { return _stored.get(); }
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
  return exports;
}

NODE_API_MODULE(pyhaxorg, InitModule);
/* clang-format on */