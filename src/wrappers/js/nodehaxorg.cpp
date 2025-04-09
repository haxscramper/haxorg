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
  std::shared_ptr<hstd::UserTimeBreakdown> _stored;
  hstd::UserTimeBreakdown* getPtr() { return _stored.get(); }
};

struct UserTimeJs : public Napi::ObjectWrap<UserTimeJs> {
  Napi::Value getBreakdown(Napi::CallbackInfo const& info) {
    return WrapConstMethod<hstd::UserTime, hstd::UserTimeBreakdown>(info,
                                                                    getPtr(),
                                                                    static_cast<hstd::UserTimeBreakdown(hstd::UserTime::*)() const>(&hstd::UserTime::getBreakdown),
                                                                    std::make_tuple());
  }
  Napi::Value format(Napi::CallbackInfo const& info) {
    return WrapConstMethod<hstd::UserTime, std::string>(info,
                                                        getPtr(),
                                                        static_cast<std::string(hstd::UserTime::*)() const>(&hstd::UserTime::format),
                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "UserTimeJs", {InstanceMethod("getBreakdown", &UserTimeJs::getBreakdown),
                                                          InstanceMethod("format", &UserTimeJs::format)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("UserTimeJs", func);
    return exports;
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
  std::shared_ptr<org::parse::LineCol> _stored;
  org::parse::LineCol* getPtr() { return _stored.get(); }
};

struct OrgJsonJs : public Napi::ObjectWrap<OrgJsonJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::OrgJson, OrgJsonKind>(info,
                                                           getPtr(),
                                                           static_cast<OrgJsonKind(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getKind),
                                                           std::make_tuple());
  }
  Napi::Value getJsonString(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::OrgJson, std::string>(info,
                                                           getPtr(),
                                                           static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getJsonString),
                                                           std::make_tuple());
  }
  Napi::Value atIndex(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::OrgJson, org::sem::OrgJson>(info,
                                                                 getPtr(),
                                                                 static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::at),
                                                                 std::make_tuple(CxxArgSpec<int>{"idx"}));
  }
  Napi::Value atField(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::OrgJson, org::sem::OrgJson>(info,
                                                                 getPtr(),
                                                                 static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::at),
                                                                 std::make_tuple(CxxArgSpec<std::string>{"name"}));
  }
  Napi::Value getString(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::OrgJson, std::string>(info,
                                                           getPtr(),
                                                           static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getString),
                                                           std::make_tuple());
  }
  Napi::Value getField(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::OrgJson, org::sem::OrgJson>(info,
                                                                 getPtr(),
                                                                 static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::getField),
                                                                 std::make_tuple(CxxArgSpec<std::string>{"name"}));
  }
  Napi::Value getItem(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::OrgJson, org::sem::OrgJson>(info,
                                                                 getPtr(),
                                                                 static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::getItem),
                                                                 std::make_tuple(CxxArgSpec<int>{"index"}));
  }
  Napi::Value getInt(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::OrgJson, int>(info,
                                                   getPtr(),
                                                   static_cast<int(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getInt),
                                                   std::make_tuple());
  }
  Napi::Value getBool(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::OrgJson, bool>(info,
                                                    getPtr(),
                                                    static_cast<bool(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getBool),
                                                    std::make_tuple());
  }
  Napi::Value getArray(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::OrgJson, hstd::Vec<org::sem::OrgJson>>(info,
                                                                            getPtr(),
                                                                            static_cast<hstd::Vec<org::sem::OrgJson>(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getArray),
                                                                            std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgJsonJs", {InstanceMethod("getKind", &OrgJsonJs::getKind),
                                                         InstanceMethod("getJsonString", &OrgJsonJs::getJsonString),
                                                         InstanceMethod("atIndex", &OrgJsonJs::atIndex),
                                                         InstanceMethod("atField", &OrgJsonJs::atField),
                                                         InstanceMethod("getString", &OrgJsonJs::getString),
                                                         InstanceMethod("getField", &OrgJsonJs::getField),
                                                         InstanceMethod("getItem", &OrgJsonJs::getItem),
                                                         InstanceMethod("getInt", &OrgJsonJs::getInt),
                                                         InstanceMethod("getBool", &OrgJsonJs::getBool),
                                                         InstanceMethod("getArray", &OrgJsonJs::getArray)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OrgJsonJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::OrgJson> _stored;
  org::sem::OrgJson* getPtr() { return _stored.get(); }
};

struct OrgJs : public Napi::ObjectWrap<OrgJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Org, OrgSemKind>(info,
                                                      getPtr(),
                                                      static_cast<OrgSemKind(org::sem::Org::*)() const>(&org::sem::Org::getKind),
                                                      std::make_tuple());
  }
  Napi::Value isGenerated(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Org, bool>(info,
                                                getPtr(),
                                                static_cast<bool(org::sem::Org::*)() const>(&org::sem::Org::isGenerated),
                                                std::make_tuple());
  }
  Napi::Value push_back(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::Org, void>(info,
                                           getPtr(),
                                           static_cast<void(org::sem::Org::*)(org::sem::SemId<org::sem::Org>)>(&org::sem::Org::push_back),
                                           std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::Org>>{"sub"}));
  }
  Napi::Value insert(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::Org, void>(info,
                                           getPtr(),
                                           static_cast<void(org::sem::Org::*)(int, org::sem::SemId<org::sem::Org>)>(&org::sem::Org::insert),
                                           std::make_tuple(CxxArgSpec<int>{"pos"},
                                                           CxxArgSpec<org::sem::SemId<org::sem::Org>>{"node"}));
  }
  Napi::Value at(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Org, org::sem::SemId<org::sem::Org>>(info,
                                                                          getPtr(),
                                                                          static_cast<org::sem::SemId<org::sem::Org>(org::sem::Org::*)(int) const>(&org::sem::Org::at),
                                                                          std::make_tuple(CxxArgSpec<int>{"idx"}));
  }
  Napi::Value is(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Org, bool>(info,
                                                getPtr(),
                                                static_cast<bool(org::sem::Org::*)(OrgSemKind) const>(&org::sem::Org::is),
                                                std::make_tuple(CxxArgSpec<OrgSemKind>{"kind"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgJs", {InstanceMethod("getKind", &OrgJs::getKind),
                                                     InstanceMethod("isGenerated", &OrgJs::isGenerated),
                                                     InstanceMethod("push_back", &OrgJs::push_back),
                                                     InstanceMethod("insert", &OrgJs::insert),
                                                     InstanceMethod("at", &OrgJs::at),
                                                     InstanceMethod("is", &OrgJs::is)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OrgJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Org> _stored;
  org::sem::Org* getPtr() { return _stored.get(); }
};

struct OperationsTracerJs : public Napi::ObjectWrap<OperationsTracerJs> {
  Napi::Value setTraceFileStr(Napi::CallbackInfo const& info) {
    return WrapMethod<hstd::OperationsTracer, void>(info,
                                                    getPtr(),
                                                    static_cast<void(hstd::OperationsTracer::*)(std::string const&, bool)>(&hstd::OperationsTracer::setTraceFileStr),
                                                    std::make_tuple(CxxArgSpec<std::string>{"outfile"},
                                                                    CxxArgSpec<bool>{"overwrite"}));
  }
  Napi::Value sendMessage(Napi::CallbackInfo const& info) {
    return WrapMethod<hstd::OperationsTracer, void>(info,
                                                    getPtr(),
                                                    static_cast<void(hstd::OperationsTracer::*)(std::string const&, std::string const&, int, std::string const&)>(&hstd::OperationsTracer::sendMessage),
                                                    std::make_tuple(CxxArgSpec<std::string>{"value"},
                                                                    CxxArgSpec<std::string>{"function"},
                                                                    CxxArgSpec<int>{"line"},
                                                                    CxxArgSpec<std::string>{"file"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OperationsTracerJs", {InstanceMethod("setTraceFileStr", &OperationsTracerJs::setTraceFileStr),
                                                                  InstanceMethod("sendMessage", &OperationsTracerJs::sendMessage)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OperationsTracerJs", func);
    return exports;
  }
  std::shared_ptr<hstd::OperationsTracer> _stored;
  hstd::OperationsTracer* getPtr() { return _stored.get(); }
};

struct ImmIdJs : public Napi::ObjectWrap<ImmIdJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmId, OrgSemKind>(info,
                                                        getPtr(),
                                                        static_cast<OrgSemKind(org::imm::ImmId::*)() const>(&org::imm::ImmId::getKind),
                                                        std::make_tuple());
  }
  Napi::Value is(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmId, bool>(info,
                                                  getPtr(),
                                                  static_cast<bool(org::imm::ImmId::*)(OrgSemKind) const>(&org::imm::ImmId::is),
                                                  std::make_tuple(CxxArgSpec<OrgSemKind>{"kind"}));
  }
  Napi::Value getNodeIndex(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmId, org::imm::ImmId::NodeIdxT>(info,
                                                                       getPtr(),
                                                                       static_cast<org::imm::ImmId::NodeIdxT(org::imm::ImmId::*)() const>(&org::imm::ImmId::getNodeIndex),
                                                                       std::make_tuple());
  }
  Napi::Value getReadableId(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmId, std::string>(info,
                                                         getPtr(),
                                                         static_cast<std::string(org::imm::ImmId::*)() const>(&org::imm::ImmId::getReadableId),
                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmIdJs", {InstanceMethod("getKind", &ImmIdJs::getKind),
                                                       InstanceMethod("is", &ImmIdJs::is),
                                                       InstanceMethod("getNodeIndex", &ImmIdJs::getNodeIndex),
                                                       InstanceMethod("getReadableId", &ImmIdJs::getReadableId)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmIdJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmPathStep> _stored;
  org::imm::ImmPathStep* getPtr() { return _stored.get(); }
};

struct ImmPathJs : public Napi::ObjectWrap<ImmPathJs> {
  Napi::Value empty(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmPath, bool>(info,
                                                    getPtr(),
                                                    static_cast<bool(org::imm::ImmPath::*)() const>(&org::imm::ImmPath::empty),
                                                    std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPathJs", {InstanceMethod("empty", &ImmPathJs::empty)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPathJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmNoneValueRead> _stored;
  org::imm::ImmNoneValueRead* getPtr() { return _stored.get(); }
};

struct ImmErrorItemValueReadJs : public Napi::ObjectWrap<ImmErrorItemValueReadJs> {
  Napi::Value getMessage(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmErrorItemValueRead, immer::box<hstd::Str> const&>(info,
                                                                                          getPtr(),
                                                                                          static_cast<immer::box<hstd::Str> const&(org::imm::ImmErrorItemValueRead::*)() const>(&org::imm::ImmErrorItemValueRead::getMessage),
                                                                                          std::make_tuple());
  }
  Napi::Value getFunction(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmErrorItemValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                         getPtr(),
                                                                                                         static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmErrorItemValueRead::*)() const>(&org::imm::ImmErrorItemValueRead::getFunction),
                                                                                                         std::make_tuple());
  }
  Napi::Value getLine(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmErrorItemValueRead, immer::box<std::optional<int>> const&>(info,
                                                                                                   getPtr(),
                                                                                                   static_cast<immer::box<std::optional<int>> const&(org::imm::ImmErrorItemValueRead::*)() const>(&org::imm::ImmErrorItemValueRead::getLine),
                                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorItemValueReadJs", {InstanceMethod("getMessage", &ImmErrorItemValueReadJs::getMessage),
                                                                       InstanceMethod("getFunction", &ImmErrorItemValueReadJs::getFunction),
                                                                       InstanceMethod("getLine", &ImmErrorItemValueReadJs::getLine)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorItemValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmErrorItemValueRead> _stored;
  org::imm::ImmErrorItemValueRead* getPtr() { return _stored.get(); }
};

struct ImmErrorGroupValueReadJs : public Napi::ObjectWrap<ImmErrorGroupValueReadJs> {
  Napi::Value getDiagnostics(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmErrorGroupValueRead, immer::flex_vector<org::imm::ImmIdT<org::imm::ImmErrorItem>> const&>(info,
                                                                                                                                  getPtr(),
                                                                                                                                  static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmErrorItem>> const&(org::imm::ImmErrorGroupValueRead::*)() const>(&org::imm::ImmErrorGroupValueRead::getDiagnostics),
                                                                                                                                  std::make_tuple());
  }
  Napi::Value getFunction(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmErrorGroupValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                          getPtr(),
                                                                                                          static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmErrorGroupValueRead::*)() const>(&org::imm::ImmErrorGroupValueRead::getFunction),
                                                                                                          std::make_tuple());
  }
  Napi::Value getLine(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmErrorGroupValueRead, immer::box<std::optional<int>> const&>(info,
                                                                                                    getPtr(),
                                                                                                    static_cast<immer::box<std::optional<int>> const&(org::imm::ImmErrorGroupValueRead::*)() const>(&org::imm::ImmErrorGroupValueRead::getLine),
                                                                                                    std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorGroupValueReadJs", {InstanceMethod("getDiagnostics", &ImmErrorGroupValueReadJs::getDiagnostics),
                                                                        InstanceMethod("getFunction", &ImmErrorGroupValueReadJs::getFunction),
                                                                        InstanceMethod("getLine", &ImmErrorGroupValueReadJs::getLine)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorGroupValueReadJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmEmptyValueRead> _stored;
  org::imm::ImmEmptyValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdCaptionValueReadJs : public Napi::ObjectWrap<ImmCmdCaptionValueReadJs> {
  Napi::Value getText(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCaptionValueRead, org::imm::ImmIdT<org::imm::ImmParagraph> const&>(info,
                                                                                                              getPtr(),
                                                                                                              static_cast<org::imm::ImmIdT<org::imm::ImmParagraph> const&(org::imm::ImmCmdCaptionValueRead::*)() const>(&org::imm::ImmCmdCaptionValueRead::getText),
                                                                                                              std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCaptionValueReadJs", {InstanceMethod("getText", &ImmCmdCaptionValueReadJs::getText)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCaptionValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdCaptionValueRead> _stored;
  org::imm::ImmCmdCaptionValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdColumnsValueReadJs : public Napi::ObjectWrap<ImmCmdColumnsValueReadJs> {
  Napi::Value getView(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdColumnsValueRead, org::sem::ColumnView const&>(info,
                                                                                          getPtr(),
                                                                                          static_cast<org::sem::ColumnView const&(org::imm::ImmCmdColumnsValueRead::*)() const>(&org::imm::ImmCmdColumnsValueRead::getView),
                                                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdColumnsValueReadJs", {InstanceMethod("getView", &ImmCmdColumnsValueReadJs::getView)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdColumnsValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdColumnsValueRead> _stored;
  org::imm::ImmCmdColumnsValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdNameValueReadJs : public Napi::ObjectWrap<ImmCmdNameValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdNameValueRead, immer::box<hstd::Str> const&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdNameValueRead::*)() const>(&org::imm::ImmCmdNameValueRead::getName),
                                                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdNameValueReadJs", {InstanceMethod("getName", &ImmCmdNameValueReadJs::getName)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdNameValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdNameValueRead> _stored;
  org::imm::ImmCmdNameValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomArgsValueReadJs : public Napi::ObjectWrap<ImmCmdCustomArgsValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCustomArgsValueRead, immer::box<hstd::Str> const&>(info,
                                                                                              getPtr(),
                                                                                              static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdCustomArgsValueRead::*)() const>(&org::imm::ImmCmdCustomArgsValueRead::getName),
                                                                                              std::make_tuple());
  }
  Napi::Value getIsattached(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCustomArgsValueRead, bool const&>(info,
                                                                             getPtr(),
                                                                             static_cast<bool const&(org::imm::ImmCmdCustomArgsValueRead::*)() const>(&org::imm::ImmCmdCustomArgsValueRead::getIsattached),
                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomArgsValueReadJs", {InstanceMethod("getName", &ImmCmdCustomArgsValueReadJs::getName),
                                                                           InstanceMethod("getIsattached", &ImmCmdCustomArgsValueReadJs::getIsattached)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomArgsValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdCustomArgsValueRead> _stored;
  org::imm::ImmCmdCustomArgsValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomRawValueReadJs : public Napi::ObjectWrap<ImmCmdCustomRawValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCustomRawValueRead, immer::box<hstd::Str> const&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdCustomRawValueRead::*)() const>(&org::imm::ImmCmdCustomRawValueRead::getName),
                                                                                             std::make_tuple());
  }
  Napi::Value getIsattached(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCustomRawValueRead, bool const&>(info,
                                                                            getPtr(),
                                                                            static_cast<bool const&(org::imm::ImmCmdCustomRawValueRead::*)() const>(&org::imm::ImmCmdCustomRawValueRead::getIsattached),
                                                                            std::make_tuple());
  }
  Napi::Value getText(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCustomRawValueRead, immer::box<hstd::Str> const&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdCustomRawValueRead::*)() const>(&org::imm::ImmCmdCustomRawValueRead::getText),
                                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomRawValueReadJs", {InstanceMethod("getName", &ImmCmdCustomRawValueReadJs::getName),
                                                                          InstanceMethod("getIsattached", &ImmCmdCustomRawValueReadJs::getIsattached),
                                                                          InstanceMethod("getText", &ImmCmdCustomRawValueReadJs::getText)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomRawValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdCustomRawValueRead> _stored;
  org::imm::ImmCmdCustomRawValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomTextValueReadJs : public Napi::ObjectWrap<ImmCmdCustomTextValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCustomTextValueRead, immer::box<hstd::Str> const&>(info,
                                                                                              getPtr(),
                                                                                              static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdCustomTextValueRead::*)() const>(&org::imm::ImmCmdCustomTextValueRead::getName),
                                                                                              std::make_tuple());
  }
  Napi::Value getIsattached(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCustomTextValueRead, bool const&>(info,
                                                                             getPtr(),
                                                                             static_cast<bool const&(org::imm::ImmCmdCustomTextValueRead::*)() const>(&org::imm::ImmCmdCustomTextValueRead::getIsattached),
                                                                             std::make_tuple());
  }
  Napi::Value getText(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCustomTextValueRead, org::imm::ImmIdT<org::imm::ImmParagraph> const&>(info,
                                                                                                                 getPtr(),
                                                                                                                 static_cast<org::imm::ImmIdT<org::imm::ImmParagraph> const&(org::imm::ImmCmdCustomTextValueRead::*)() const>(&org::imm::ImmCmdCustomTextValueRead::getText),
                                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomTextValueReadJs", {InstanceMethod("getName", &ImmCmdCustomTextValueReadJs::getName),
                                                                           InstanceMethod("getIsattached", &ImmCmdCustomTextValueReadJs::getIsattached),
                                                                           InstanceMethod("getText", &ImmCmdCustomTextValueReadJs::getText)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomTextValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdCustomTextValueRead> _stored;
  org::imm::ImmCmdCustomTextValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdCallValueReadJs : public Napi::ObjectWrap<ImmCmdCallValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCallValueRead, immer::box<hstd::Str> const&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getName),
                                                                                        std::make_tuple());
  }
  Napi::Value getFilename(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCallValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getFilename),
                                                                                                       std::make_tuple());
  }
  Napi::Value getInsideheaderattrs(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCallValueRead, org::sem::AttrGroup const&>(info,
                                                                                      getPtr(),
                                                                                      static_cast<org::sem::AttrGroup const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getInsideheaderattrs),
                                                                                      std::make_tuple());
  }
  Napi::Value getCallattrs(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCallValueRead, org::sem::AttrGroup const&>(info,
                                                                                      getPtr(),
                                                                                      static_cast<org::sem::AttrGroup const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getCallattrs),
                                                                                      std::make_tuple());
  }
  Napi::Value getEndheaderattrs(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCallValueRead, org::sem::AttrGroup const&>(info,
                                                                                      getPtr(),
                                                                                      static_cast<org::sem::AttrGroup const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getEndheaderattrs),
                                                                                      std::make_tuple());
  }
  Napi::Value getResult(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdCallValueRead, immer::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&>(info,
                                                                                                                                         getPtr(),
                                                                                                                                         static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getResult),
                                                                                                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCallValueReadJs", {InstanceMethod("getName", &ImmCmdCallValueReadJs::getName),
                                                                     InstanceMethod("getFilename", &ImmCmdCallValueReadJs::getFilename),
                                                                     InstanceMethod("getInsideheaderattrs", &ImmCmdCallValueReadJs::getInsideheaderattrs),
                                                                     InstanceMethod("getCallattrs", &ImmCmdCallValueReadJs::getCallattrs),
                                                                     InstanceMethod("getEndheaderattrs", &ImmCmdCallValueReadJs::getEndheaderattrs),
                                                                     InstanceMethod("getResult", &ImmCmdCallValueReadJs::getResult)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCallValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdCallValueRead> _stored;
  org::imm::ImmCmdCallValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdTblfmValueReadJs : public Napi::ObjectWrap<ImmCmdTblfmValueReadJs> {
  Napi::Value getExpr(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdTblfmValueRead, org::sem::Tblfm const&>(info,
                                                                                   getPtr(),
                                                                                   static_cast<org::sem::Tblfm const&(org::imm::ImmCmdTblfmValueRead::*)() const>(&org::imm::ImmCmdTblfmValueRead::getExpr),
                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdTblfmValueReadJs", {InstanceMethod("getExpr", &ImmCmdTblfmValueReadJs::getExpr)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdTblfmValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdTblfmValueRead> _stored;
  org::imm::ImmCmdTblfmValueRead* getPtr() { return _stored.get(); }
};

struct ImmHashTagValueReadJs : public Napi::ObjectWrap<ImmHashTagValueReadJs> {
  Napi::Value getText(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmHashTagValueRead, org::sem::HashTagText const&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<org::sem::HashTagText const&(org::imm::ImmHashTagValueRead::*)() const>(&org::imm::ImmHashTagValueRead::getText),
                                                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmHashTagValueReadJs", {InstanceMethod("getText", &ImmHashTagValueReadJs::getText)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmHashTagValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmHashTagValueRead> _stored;
  org::imm::ImmHashTagValueRead* getPtr() { return _stored.get(); }
};

struct ImmInlineFootnoteValueReadJs : public Napi::ObjectWrap<ImmInlineFootnoteValueReadJs> {
  Napi::Value getTag(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmInlineFootnoteValueRead, immer::box<hstd::Str> const&>(info,
                                                                                               getPtr(),
                                                                                               static_cast<immer::box<hstd::Str> const&(org::imm::ImmInlineFootnoteValueRead::*)() const>(&org::imm::ImmInlineFootnoteValueRead::getTag),
                                                                                               std::make_tuple());
  }
  Napi::Value getDefinition(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmInlineFootnoteValueRead, immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>> const&>(info,
                                                                                                                                       getPtr(),
                                                                                                                                       static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>> const&(org::imm::ImmInlineFootnoteValueRead::*)() const>(&org::imm::ImmInlineFootnoteValueRead::getDefinition),
                                                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineFootnoteValueReadJs", {InstanceMethod("getTag", &ImmInlineFootnoteValueReadJs::getTag),
                                                                            InstanceMethod("getDefinition", &ImmInlineFootnoteValueReadJs::getDefinition)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineFootnoteValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmInlineFootnoteValueRead> _stored;
  org::imm::ImmInlineFootnoteValueRead* getPtr() { return _stored.get(); }
};

struct ImmInlineExportValueReadJs : public Napi::ObjectWrap<ImmInlineExportValueReadJs> {
  Napi::Value getExporter(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmInlineExportValueRead, immer::box<hstd::Str> const&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<immer::box<hstd::Str> const&(org::imm::ImmInlineExportValueRead::*)() const>(&org::imm::ImmInlineExportValueRead::getExporter),
                                                                                             std::make_tuple());
  }
  Napi::Value getContent(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmInlineExportValueRead, immer::box<hstd::Str> const&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<immer::box<hstd::Str> const&(org::imm::ImmInlineExportValueRead::*)() const>(&org::imm::ImmInlineExportValueRead::getContent),
                                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineExportValueReadJs", {InstanceMethod("getExporter", &ImmInlineExportValueReadJs::getExporter),
                                                                          InstanceMethod("getContent", &ImmInlineExportValueReadJs::getContent)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineExportValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmInlineExportValueRead> _stored;
  org::imm::ImmInlineExportValueRead* getPtr() { return _stored.get(); }
};

struct ImmTimeValueReadJs : public Napi::ObjectWrap<ImmTimeValueReadJs> {
  Napi::Value getIsactive(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmTimeValueRead, bool const&>(info,
                                                                    getPtr(),
                                                                    static_cast<bool const&(org::imm::ImmTimeValueRead::*)() const>(&org::imm::ImmTimeValueRead::getIsactive),
                                                                    std::make_tuple());
  }
  Napi::Value getTime(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmTimeValueRead, org::imm::ImmTime::TimeVariant const&>(info,
                                                                                              getPtr(),
                                                                                              static_cast<org::imm::ImmTime::TimeVariant const&(org::imm::ImmTimeValueRead::*)() const>(&org::imm::ImmTimeValueRead::getTime),
                                                                                              std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeValueReadJs", {InstanceMethod("getIsactive", &ImmTimeValueReadJs::getIsactive),
                                                                  InstanceMethod("getTime", &ImmTimeValueReadJs::getTime)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmTimeValueRead> _stored;
  org::imm::ImmTimeValueRead* getPtr() { return _stored.get(); }
};

struct ImmTimeRangeValueReadJs : public Napi::ObjectWrap<ImmTimeRangeValueReadJs> {
  Napi::Value getFrom(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmTimeRangeValueRead, org::imm::ImmIdT<org::imm::ImmTime> const&>(info,
                                                                                                        getPtr(),
                                                                                                        static_cast<org::imm::ImmIdT<org::imm::ImmTime> const&(org::imm::ImmTimeRangeValueRead::*)() const>(&org::imm::ImmTimeRangeValueRead::getFrom),
                                                                                                        std::make_tuple());
  }
  Napi::Value getTo(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmTimeRangeValueRead, org::imm::ImmIdT<org::imm::ImmTime> const&>(info,
                                                                                                        getPtr(),
                                                                                                        static_cast<org::imm::ImmIdT<org::imm::ImmTime> const&(org::imm::ImmTimeRangeValueRead::*)() const>(&org::imm::ImmTimeRangeValueRead::getTo),
                                                                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeRangeValueReadJs", {InstanceMethod("getFrom", &ImmTimeRangeValueReadJs::getFrom),
                                                                       InstanceMethod("getTo", &ImmTimeRangeValueReadJs::getTo)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeRangeValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmTimeRangeValueRead> _stored;
  org::imm::ImmTimeRangeValueRead* getPtr() { return _stored.get(); }
};

struct ImmMacroValueReadJs : public Napi::ObjectWrap<ImmMacroValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmMacroValueRead, immer::box<hstd::Str> const&>(info,
                                                                                      getPtr(),
                                                                                      static_cast<immer::box<hstd::Str> const&(org::imm::ImmMacroValueRead::*)() const>(&org::imm::ImmMacroValueRead::getName),
                                                                                      std::make_tuple());
  }
  Napi::Value getAttrs(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmMacroValueRead, org::sem::AttrGroup const&>(info,
                                                                                    getPtr(),
                                                                                    static_cast<org::sem::AttrGroup const&(org::imm::ImmMacroValueRead::*)() const>(&org::imm::ImmMacroValueRead::getAttrs),
                                                                                    std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMacroValueReadJs", {InstanceMethod("getName", &ImmMacroValueReadJs::getName),
                                                                   InstanceMethod("getAttrs", &ImmMacroValueReadJs::getAttrs)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMacroValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmMacroValueRead> _stored;
  org::imm::ImmMacroValueRead* getPtr() { return _stored.get(); }
};

struct ImmSymbolValueReadJs : public Napi::ObjectWrap<ImmSymbolValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSymbolValueRead, immer::box<hstd::Str> const&>(info,
                                                                                       getPtr(),
                                                                                       static_cast<immer::box<hstd::Str> const&(org::imm::ImmSymbolValueRead::*)() const>(&org::imm::ImmSymbolValueRead::getName),
                                                                                       std::make_tuple());
  }
  Napi::Value getParameters(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSymbolValueRead, immer::flex_vector<org::imm::ImmSymbol::Param> const&>(info,
                                                                                                                getPtr(),
                                                                                                                static_cast<immer::flex_vector<org::imm::ImmSymbol::Param> const&(org::imm::ImmSymbolValueRead::*)() const>(&org::imm::ImmSymbolValueRead::getParameters),
                                                                                                                std::make_tuple());
  }
  Napi::Value getPositional(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSymbolValueRead, immer::flex_vector<org::imm::ImmIdT<org::imm::ImmOrg>> const&>(info,
                                                                                                                        getPtr(),
                                                                                                                        static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmOrg>> const&(org::imm::ImmSymbolValueRead::*)() const>(&org::imm::ImmSymbolValueRead::getPositional),
                                                                                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymbolValueReadJs", {InstanceMethod("getName", &ImmSymbolValueReadJs::getName),
                                                                    InstanceMethod("getParameters", &ImmSymbolValueReadJs::getParameters),
                                                                    InstanceMethod("getPositional", &ImmSymbolValueReadJs::getPositional)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymbolValueReadJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmParValueRead> _stored;
  org::imm::ImmParValueRead* getPtr() { return _stored.get(); }
};

struct ImmRadioTargetValueReadJs : public Napi::ObjectWrap<ImmRadioTargetValueReadJs> {
  Napi::Value getWords(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmRadioTargetValueRead, immer::flex_vector<hstd::Str> const&>(info,
                                                                                                    getPtr(),
                                                                                                    static_cast<immer::flex_vector<hstd::Str> const&(org::imm::ImmRadioTargetValueRead::*)() const>(&org::imm::ImmRadioTargetValueRead::getWords),
                                                                                                    std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRadioTargetValueReadJs", {InstanceMethod("getWords", &ImmRadioTargetValueReadJs::getWords)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRadioTargetValueReadJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmLatexValueRead> _stored;
  org::imm::ImmLatexValueRead* getPtr() { return _stored.get(); }
};

struct ImmLinkValueReadJs : public Napi::ObjectWrap<ImmLinkValueReadJs> {
  Napi::Value getDescription(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmLinkValueRead, immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&>(info,
                                                                                                                                   getPtr(),
                                                                                                                                   static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmLinkValueRead::*)() const>(&org::imm::ImmLinkValueRead::getDescription),
                                                                                                                                   std::make_tuple());
  }
  Napi::Value getTarget(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmLinkValueRead, org::sem::LinkTarget const&>(info,
                                                                                    getPtr(),
                                                                                    static_cast<org::sem::LinkTarget const&(org::imm::ImmLinkValueRead::*)() const>(&org::imm::ImmLinkValueRead::getTarget),
                                                                                    std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLinkValueReadJs", {InstanceMethod("getDescription", &ImmLinkValueReadJs::getDescription),
                                                                  InstanceMethod("getTarget", &ImmLinkValueReadJs::getTarget)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLinkValueReadJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmBlockVerseValueRead> _stored;
  org::imm::ImmBlockVerseValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockDynamicFallbackValueReadJs : public Napi::ObjectWrap<ImmBlockDynamicFallbackValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockDynamicFallbackValueRead, immer::box<hstd::Str> const&>(info,
                                                                                                     getPtr(),
                                                                                                     static_cast<immer::box<hstd::Str> const&(org::imm::ImmBlockDynamicFallbackValueRead::*)() const>(&org::imm::ImmBlockDynamicFallbackValueRead::getName),
                                                                                                     std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockDynamicFallbackValueReadJs", {InstanceMethod("getName", &ImmBlockDynamicFallbackValueReadJs::getName)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockDynamicFallbackValueReadJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmBlockExampleValueRead> _stored;
  org::imm::ImmBlockExampleValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockExportValueReadJs : public Napi::ObjectWrap<ImmBlockExportValueReadJs> {
  Napi::Value getExporter(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockExportValueRead, immer::box<hstd::Str> const&>(info,
                                                                                            getPtr(),
                                                                                            static_cast<immer::box<hstd::Str> const&(org::imm::ImmBlockExportValueRead::*)() const>(&org::imm::ImmBlockExportValueRead::getExporter),
                                                                                            std::make_tuple());
  }
  Napi::Value getContent(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockExportValueRead, immer::box<hstd::Str> const&>(info,
                                                                                            getPtr(),
                                                                                            static_cast<immer::box<hstd::Str> const&(org::imm::ImmBlockExportValueRead::*)() const>(&org::imm::ImmBlockExportValueRead::getContent),
                                                                                            std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExportValueReadJs", {InstanceMethod("getExporter", &ImmBlockExportValueReadJs::getExporter),
                                                                         InstanceMethod("getContent", &ImmBlockExportValueReadJs::getContent)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExportValueReadJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmBlockAdmonitionValueRead> _stored;
  org::imm::ImmBlockAdmonitionValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockCodeEvalResultValueReadJs : public Napi::ObjectWrap<ImmBlockCodeEvalResultValueReadJs> {
  Napi::Value getRaw(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockCodeEvalResultValueRead, immer::flex_vector<org::sem::OrgCodeEvalOutput> const&>(info,
                                                                                                                              getPtr(),
                                                                                                                              static_cast<immer::flex_vector<org::sem::OrgCodeEvalOutput> const&(org::imm::ImmBlockCodeEvalResultValueRead::*)() const>(&org::imm::ImmBlockCodeEvalResultValueRead::getRaw),
                                                                                                                              std::make_tuple());
  }
  Napi::Value getNode(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockCodeEvalResultValueRead, org::imm::ImmIdT<org::imm::ImmOrg> const&>(info,
                                                                                                                 getPtr(),
                                                                                                                 static_cast<org::imm::ImmIdT<org::imm::ImmOrg> const&(org::imm::ImmBlockCodeEvalResultValueRead::*)() const>(&org::imm::ImmBlockCodeEvalResultValueRead::getNode),
                                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeEvalResultValueReadJs", {InstanceMethod("getRaw", &ImmBlockCodeEvalResultValueReadJs::getRaw),
                                                                                 InstanceMethod("getNode", &ImmBlockCodeEvalResultValueReadJs::getNode)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeEvalResultValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmBlockCodeEvalResultValueRead> _stored;
  org::imm::ImmBlockCodeEvalResultValueRead* getPtr() { return _stored.get(); }
};

struct ImmBlockCodeValueReadJs : public Napi::ObjectWrap<ImmBlockCodeValueReadJs> {
  Napi::Value getLang(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockCodeValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                         getPtr(),
                                                                                                         static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getLang),
                                                                                                         std::make_tuple());
  }
  Napi::Value getExports(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockCodeValueRead, BlockCodeExports const&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<BlockCodeExports const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getExports),
                                                                                     std::make_tuple());
  }
  Napi::Value getResult(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockCodeValueRead, immer::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&>(info,
                                                                                                                                           getPtr(),
                                                                                                                                           static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getResult),
                                                                                                                                           std::make_tuple());
  }
  Napi::Value getLines(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockCodeValueRead, immer::flex_vector<org::sem::BlockCodeLine> const&>(info,
                                                                                                                getPtr(),
                                                                                                                static_cast<immer::flex_vector<org::sem::BlockCodeLine> const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getLines),
                                                                                                                std::make_tuple());
  }
  Napi::Value getCache(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockCodeValueRead, bool const&>(info,
                                                                         getPtr(),
                                                                         static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getCache),
                                                                         std::make_tuple());
  }
  Napi::Value getEval(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockCodeValueRead, bool const&>(info,
                                                                         getPtr(),
                                                                         static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getEval),
                                                                         std::make_tuple());
  }
  Napi::Value getNoweb(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockCodeValueRead, bool const&>(info,
                                                                         getPtr(),
                                                                         static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getNoweb),
                                                                         std::make_tuple());
  }
  Napi::Value getHlines(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockCodeValueRead, bool const&>(info,
                                                                         getPtr(),
                                                                         static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getHlines),
                                                                         std::make_tuple());
  }
  Napi::Value getTangle(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockCodeValueRead, bool const&>(info,
                                                                         getPtr(),
                                                                         static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getTangle),
                                                                         std::make_tuple());
  }
  Napi::Value getSwitches(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmBlockCodeValueRead, org::sem::AttrGroup const&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<org::sem::AttrGroup const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getSwitches),
                                                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeValueReadJs", {InstanceMethod("getLang", &ImmBlockCodeValueReadJs::getLang),
                                                                       InstanceMethod("getExports", &ImmBlockCodeValueReadJs::getExports),
                                                                       InstanceMethod("getResult", &ImmBlockCodeValueReadJs::getResult),
                                                                       InstanceMethod("getLines", &ImmBlockCodeValueReadJs::getLines),
                                                                       InstanceMethod("getCache", &ImmBlockCodeValueReadJs::getCache),
                                                                       InstanceMethod("getEval", &ImmBlockCodeValueReadJs::getEval),
                                                                       InstanceMethod("getNoweb", &ImmBlockCodeValueReadJs::getNoweb),
                                                                       InstanceMethod("getHlines", &ImmBlockCodeValueReadJs::getHlines),
                                                                       InstanceMethod("getTangle", &ImmBlockCodeValueReadJs::getTangle),
                                                                       InstanceMethod("getSwitches", &ImmBlockCodeValueReadJs::getSwitches)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmBlockCodeValueRead> _stored;
  org::imm::ImmBlockCodeValueRead* getPtr() { return _stored.get(); }
};

struct ImmSubtreeLogValueReadJs : public Napi::ObjectWrap<ImmSubtreeLogValueReadJs> {
  Napi::Value getHead(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeLogValueRead, org::sem::SubtreeLogHead const&>(info,
                                                                                              getPtr(),
                                                                                              static_cast<org::sem::SubtreeLogHead const&(org::imm::ImmSubtreeLogValueRead::*)() const>(&org::imm::ImmSubtreeLogValueRead::getHead),
                                                                                              std::make_tuple());
  }
  Napi::Value getDesc(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeLogValueRead, immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>> const&>(info,
                                                                                                                                        getPtr(),
                                                                                                                                        static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>> const&(org::imm::ImmSubtreeLogValueRead::*)() const>(&org::imm::ImmSubtreeLogValueRead::getDesc),
                                                                                                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeLogValueReadJs", {InstanceMethod("getHead", &ImmSubtreeLogValueReadJs::getHead),
                                                                        InstanceMethod("getDesc", &ImmSubtreeLogValueReadJs::getDesc)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeLogValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmSubtreeLogValueRead> _stored;
  org::imm::ImmSubtreeLogValueRead* getPtr() { return _stored.get(); }
};

struct ImmSubtreeValueReadJs : public Napi::ObjectWrap<ImmSubtreeValueReadJs> {
  Napi::Value getLevel(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, int const&>(info,
                                                                      getPtr(),
                                                                      static_cast<int const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getLevel),
                                                                      std::make_tuple());
  }
  Napi::Value getTreeid(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getTreeid),
                                                                                                       std::make_tuple());
  }
  Napi::Value getTodo(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getTodo),
                                                                                                       std::make_tuple());
  }
  Napi::Value getCompletion(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, immer::box<std::optional<org::sem::SubtreeCompletion>> const&>(info,
                                                                                                                         getPtr(),
                                                                                                                         static_cast<immer::box<std::optional<org::sem::SubtreeCompletion>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getCompletion),
                                                                                                                         std::make_tuple());
  }
  Napi::Value getDescription(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&>(info,
                                                                                                                                      getPtr(),
                                                                                                                                      static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getDescription),
                                                                                                                                      std::make_tuple());
  }
  Napi::Value getTags(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, immer::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&>(info,
                                                                                                                             getPtr(),
                                                                                                                             static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getTags),
                                                                                                                             std::make_tuple());
  }
  Napi::Value getTitle(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, org::imm::ImmIdT<org::imm::ImmParagraph> const&>(info,
                                                                                                           getPtr(),
                                                                                                           static_cast<org::imm::ImmIdT<org::imm::ImmParagraph> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getTitle),
                                                                                                           std::make_tuple());
  }
  Napi::Value getLogbook(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, immer::flex_vector<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> const&>(info,
                                                                                                                                getPtr(),
                                                                                                                                static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getLogbook),
                                                                                                                                std::make_tuple());
  }
  Napi::Value getProperties(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, immer::flex_vector<org::sem::NamedProperty> const&>(info,
                                                                                                              getPtr(),
                                                                                                              static_cast<immer::flex_vector<org::sem::NamedProperty> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getProperties),
                                                                                                              std::make_tuple());
  }
  Napi::Value getClosed(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, immer::box<std::optional<hstd::UserTime>> const&>(info,
                                                                                                            getPtr(),
                                                                                                            static_cast<immer::box<std::optional<hstd::UserTime>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getClosed),
                                                                                                            std::make_tuple());
  }
  Napi::Value getDeadline(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, immer::box<std::optional<hstd::UserTime>> const&>(info,
                                                                                                            getPtr(),
                                                                                                            static_cast<immer::box<std::optional<hstd::UserTime>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getDeadline),
                                                                                                            std::make_tuple());
  }
  Napi::Value getScheduled(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, immer::box<std::optional<hstd::UserTime>> const&>(info,
                                                                                                            getPtr(),
                                                                                                            static_cast<immer::box<std::optional<hstd::UserTime>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getScheduled),
                                                                                                            std::make_tuple());
  }
  Napi::Value getIscomment(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, bool const&>(info,
                                                                       getPtr(),
                                                                       static_cast<bool const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getIscomment),
                                                                       std::make_tuple());
  }
  Napi::Value getIsarchived(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, bool const&>(info,
                                                                       getPtr(),
                                                                       static_cast<bool const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getIsarchived),
                                                                       std::make_tuple());
  }
  Napi::Value getPriority(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSubtreeValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getPriority),
                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeValueReadJs", {InstanceMethod("getLevel", &ImmSubtreeValueReadJs::getLevel),
                                                                     InstanceMethod("getTreeid", &ImmSubtreeValueReadJs::getTreeid),
                                                                     InstanceMethod("getTodo", &ImmSubtreeValueReadJs::getTodo),
                                                                     InstanceMethod("getCompletion", &ImmSubtreeValueReadJs::getCompletion),
                                                                     InstanceMethod("getDescription", &ImmSubtreeValueReadJs::getDescription),
                                                                     InstanceMethod("getTags", &ImmSubtreeValueReadJs::getTags),
                                                                     InstanceMethod("getTitle", &ImmSubtreeValueReadJs::getTitle),
                                                                     InstanceMethod("getLogbook", &ImmSubtreeValueReadJs::getLogbook),
                                                                     InstanceMethod("getProperties", &ImmSubtreeValueReadJs::getProperties),
                                                                     InstanceMethod("getClosed", &ImmSubtreeValueReadJs::getClosed),
                                                                     InstanceMethod("getDeadline", &ImmSubtreeValueReadJs::getDeadline),
                                                                     InstanceMethod("getScheduled", &ImmSubtreeValueReadJs::getScheduled),
                                                                     InstanceMethod("getIscomment", &ImmSubtreeValueReadJs::getIscomment),
                                                                     InstanceMethod("getIsarchived", &ImmSubtreeValueReadJs::getIsarchived),
                                                                     InstanceMethod("getPriority", &ImmSubtreeValueReadJs::getPriority)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmSubtreeValueRead> _stored;
  org::imm::ImmSubtreeValueRead* getPtr() { return _stored.get(); }
};

struct ImmCellValueReadJs : public Napi::ObjectWrap<ImmCellValueReadJs> {
  Napi::Value getIsblock(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCellValueRead, bool const&>(info,
                                                                    getPtr(),
                                                                    static_cast<bool const&(org::imm::ImmCellValueRead::*)() const>(&org::imm::ImmCellValueRead::getIsblock),
                                                                    std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCellValueReadJs", {InstanceMethod("getIsblock", &ImmCellValueReadJs::getIsblock)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCellValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCellValueRead> _stored;
  org::imm::ImmCellValueRead* getPtr() { return _stored.get(); }
};

struct ImmRowValueReadJs : public Napi::ObjectWrap<ImmRowValueReadJs> {
  Napi::Value getCells(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmRowValueRead, immer::flex_vector<org::imm::ImmIdT<org::imm::ImmCell>> const&>(info,
                                                                                                                      getPtr(),
                                                                                                                      static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmCell>> const&(org::imm::ImmRowValueRead::*)() const>(&org::imm::ImmRowValueRead::getCells),
                                                                                                                      std::make_tuple());
  }
  Napi::Value getIsblock(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmRowValueRead, bool const&>(info,
                                                                   getPtr(),
                                                                   static_cast<bool const&(org::imm::ImmRowValueRead::*)() const>(&org::imm::ImmRowValueRead::getIsblock),
                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRowValueReadJs", {InstanceMethod("getCells", &ImmRowValueReadJs::getCells),
                                                                 InstanceMethod("getIsblock", &ImmRowValueReadJs::getIsblock)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRowValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmRowValueRead> _stored;
  org::imm::ImmRowValueRead* getPtr() { return _stored.get(); }
};

struct ImmTableValueReadJs : public Napi::ObjectWrap<ImmTableValueReadJs> {
  Napi::Value getRows(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmTableValueRead, immer::flex_vector<org::imm::ImmIdT<org::imm::ImmRow>> const&>(info,
                                                                                                                       getPtr(),
                                                                                                                       static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmRow>> const&(org::imm::ImmTableValueRead::*)() const>(&org::imm::ImmTableValueRead::getRows),
                                                                                                                       std::make_tuple());
  }
  Napi::Value getIsblock(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmTableValueRead, bool const&>(info,
                                                                     getPtr(),
                                                                     static_cast<bool const&(org::imm::ImmTableValueRead::*)() const>(&org::imm::ImmTableValueRead::getIsblock),
                                                                     std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTableValueReadJs", {InstanceMethod("getRows", &ImmTableValueReadJs::getRows),
                                                                   InstanceMethod("getIsblock", &ImmTableValueReadJs::getIsblock)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTableValueReadJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmColonExampleValueRead> _stored;
  org::imm::ImmColonExampleValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdAttrValueReadJs : public Napi::ObjectWrap<ImmCmdAttrValueReadJs> {
  Napi::Value getTarget(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdAttrValueRead, immer::box<hstd::Str> const&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdAttrValueRead::*)() const>(&org::imm::ImmCmdAttrValueRead::getTarget),
                                                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdAttrValueReadJs", {InstanceMethod("getTarget", &ImmCmdAttrValueReadJs::getTarget)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdAttrValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdAttrValueRead> _stored;
  org::imm::ImmCmdAttrValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdExportValueReadJs : public Napi::ObjectWrap<ImmCmdExportValueReadJs> {
  Napi::Value getExporter(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdExportValueRead, immer::box<hstd::Str> const&>(info,
                                                                                          getPtr(),
                                                                                          static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdExportValueRead::*)() const>(&org::imm::ImmCmdExportValueRead::getExporter),
                                                                                          std::make_tuple());
  }
  Napi::Value getContent(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdExportValueRead, immer::box<hstd::Str> const&>(info,
                                                                                          getPtr(),
                                                                                          static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdExportValueRead::*)() const>(&org::imm::ImmCmdExportValueRead::getContent),
                                                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdExportValueReadJs", {InstanceMethod("getExporter", &ImmCmdExportValueReadJs::getExporter),
                                                                       InstanceMethod("getContent", &ImmCmdExportValueReadJs::getContent)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdExportValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdExportValueRead> _stored;
  org::imm::ImmCmdExportValueRead* getPtr() { return _stored.get(); }
};

struct ImmCallValueReadJs : public Napi::ObjectWrap<ImmCallValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCallValueRead, immer::box<hstd::Str> const&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<immer::box<hstd::Str> const&(org::imm::ImmCallValueRead::*)() const>(&org::imm::ImmCallValueRead::getName),
                                                                                     std::make_tuple());
  }
  Napi::Value getAttrs(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCallValueRead, org::sem::AttrGroup const&>(info,
                                                                                   getPtr(),
                                                                                   static_cast<org::sem::AttrGroup const&(org::imm::ImmCallValueRead::*)() const>(&org::imm::ImmCallValueRead::getAttrs),
                                                                                   std::make_tuple());
  }
  Napi::Value getIscommand(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCallValueRead, bool const&>(info,
                                                                    getPtr(),
                                                                    static_cast<bool const&(org::imm::ImmCallValueRead::*)() const>(&org::imm::ImmCallValueRead::getIscommand),
                                                                    std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCallValueReadJs", {InstanceMethod("getName", &ImmCallValueReadJs::getName),
                                                                  InstanceMethod("getAttrs", &ImmCallValueReadJs::getAttrs),
                                                                  InstanceMethod("getIscommand", &ImmCallValueReadJs::getIscommand)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCallValueReadJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmListValueRead> _stored;
  org::imm::ImmListValueRead* getPtr() { return _stored.get(); }
};

struct ImmListItemValueReadJs : public Napi::ObjectWrap<ImmListItemValueReadJs> {
  Napi::Value getCheckbox(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmListItemValueRead, org::imm::ImmListItem::Checkbox const&>(info,
                                                                                                   getPtr(),
                                                                                                   static_cast<org::imm::ImmListItem::Checkbox const&(org::imm::ImmListItemValueRead::*)() const>(&org::imm::ImmListItemValueRead::getCheckbox),
                                                                                                   std::make_tuple());
  }
  Napi::Value getHeader(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmListItemValueRead, immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&>(info,
                                                                                                                                       getPtr(),
                                                                                                                                       static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmListItemValueRead::*)() const>(&org::imm::ImmListItemValueRead::getHeader),
                                                                                                                                       std::make_tuple());
  }
  Napi::Value getBullet(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmListItemValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                        getPtr(),
                                                                                                        static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmListItemValueRead::*)() const>(&org::imm::ImmListItemValueRead::getBullet),
                                                                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListItemValueReadJs", {InstanceMethod("getCheckbox", &ImmListItemValueReadJs::getCheckbox),
                                                                      InstanceMethod("getHeader", &ImmListItemValueReadJs::getHeader),
                                                                      InstanceMethod("getBullet", &ImmListItemValueReadJs::getBullet)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListItemValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmListItemValueRead> _stored;
  org::imm::ImmListItemValueRead* getPtr() { return _stored.get(); }
};

struct ImmDocumentOptionsValueReadJs : public Napi::ObjectWrap<ImmDocumentOptionsValueReadJs> {
  Napi::Value getInitialvisibility(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentOptionsValueRead, InitialSubtreeVisibility const&>(info,
                                                                                                   getPtr(),
                                                                                                   static_cast<InitialSubtreeVisibility const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getInitialvisibility),
                                                                                                   std::make_tuple());
  }
  Napi::Value getProperties(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentOptionsValueRead, immer::flex_vector<org::sem::NamedProperty> const&>(info,
                                                                                                                      getPtr(),
                                                                                                                      static_cast<immer::flex_vector<org::sem::NamedProperty> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getProperties),
                                                                                                                      std::make_tuple());
  }
  Napi::Value getExportconfig(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentOptionsValueRead, org::sem::DocumentExportConfig const&>(info,
                                                                                                         getPtr(),
                                                                                                         static_cast<org::sem::DocumentExportConfig const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getExportconfig),
                                                                                                         std::make_tuple());
  }
  Napi::Value getFixedwidthsections(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentOptionsValueRead, immer::box<std::optional<bool>> const&>(info,
                                                                                                          getPtr(),
                                                                                                          static_cast<immer::box<std::optional<bool>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getFixedwidthsections),
                                                                                                          std::make_tuple());
  }
  Napi::Value getStartupindented(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentOptionsValueRead, immer::box<std::optional<bool>> const&>(info,
                                                                                                          getPtr(),
                                                                                                          static_cast<immer::box<std::optional<bool>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getStartupindented),
                                                                                                          std::make_tuple());
  }
  Napi::Value getCategory(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentOptionsValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                               getPtr(),
                                                                                                               static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getCategory),
                                                                                                               std::make_tuple());
  }
  Napi::Value getSetupfile(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentOptionsValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                               getPtr(),
                                                                                                               static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getSetupfile),
                                                                                                               std::make_tuple());
  }
  Napi::Value getMaxsubtreelevelexport(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentOptionsValueRead, immer::box<std::optional<int>> const&>(info,
                                                                                                         getPtr(),
                                                                                                         static_cast<immer::box<std::optional<int>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getMaxsubtreelevelexport),
                                                                                                         std::make_tuple());
  }
  Napi::Value getColumns(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentOptionsValueRead, immer::box<std::optional<org::sem::ColumnView>> const&>(info,
                                                                                                                          getPtr(),
                                                                                                                          static_cast<immer::box<std::optional<org::sem::ColumnView>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getColumns),
                                                                                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentOptionsValueReadJs", {InstanceMethod("getInitialvisibility", &ImmDocumentOptionsValueReadJs::getInitialvisibility),
                                                                             InstanceMethod("getProperties", &ImmDocumentOptionsValueReadJs::getProperties),
                                                                             InstanceMethod("getExportconfig", &ImmDocumentOptionsValueReadJs::getExportconfig),
                                                                             InstanceMethod("getFixedwidthsections", &ImmDocumentOptionsValueReadJs::getFixedwidthsections),
                                                                             InstanceMethod("getStartupindented", &ImmDocumentOptionsValueReadJs::getStartupindented),
                                                                             InstanceMethod("getCategory", &ImmDocumentOptionsValueReadJs::getCategory),
                                                                             InstanceMethod("getSetupfile", &ImmDocumentOptionsValueReadJs::getSetupfile),
                                                                             InstanceMethod("getMaxsubtreelevelexport", &ImmDocumentOptionsValueReadJs::getMaxsubtreelevelexport),
                                                                             InstanceMethod("getColumns", &ImmDocumentOptionsValueReadJs::getColumns)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentOptionsValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmDocumentOptionsValueRead> _stored;
  org::imm::ImmDocumentOptionsValueRead* getPtr() { return _stored.get(); }
};

struct ImmDocumentFragmentValueReadJs : public Napi::ObjectWrap<ImmDocumentFragmentValueReadJs> {
  Napi::Value getBaseline(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentFragmentValueRead, int const&>(info,
                                                                               getPtr(),
                                                                               static_cast<int const&(org::imm::ImmDocumentFragmentValueRead::*)() const>(&org::imm::ImmDocumentFragmentValueRead::getBaseline),
                                                                               std::make_tuple());
  }
  Napi::Value getBasecol(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentFragmentValueRead, int const&>(info,
                                                                               getPtr(),
                                                                               static_cast<int const&(org::imm::ImmDocumentFragmentValueRead::*)() const>(&org::imm::ImmDocumentFragmentValueRead::getBasecol),
                                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentFragmentValueReadJs", {InstanceMethod("getBaseline", &ImmDocumentFragmentValueReadJs::getBaseline),
                                                                              InstanceMethod("getBasecol", &ImmDocumentFragmentValueReadJs::getBasecol)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentFragmentValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmDocumentFragmentValueRead> _stored;
  org::imm::ImmDocumentFragmentValueRead* getPtr() { return _stored.get(); }
};

struct ImmCriticMarkupValueReadJs : public Napi::ObjectWrap<ImmCriticMarkupValueReadJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCriticMarkupValueRead, org::imm::ImmCriticMarkup::Kind const&>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<org::imm::ImmCriticMarkup::Kind const&(org::imm::ImmCriticMarkupValueRead::*)() const>(&org::imm::ImmCriticMarkupValueRead::getKind),
                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCriticMarkupValueReadJs", {InstanceMethod("getKind", &ImmCriticMarkupValueReadJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCriticMarkupValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCriticMarkupValueRead> _stored;
  org::imm::ImmCriticMarkupValueRead* getPtr() { return _stored.get(); }
};

struct ImmDocumentValueReadJs : public Napi::ObjectWrap<ImmDocumentValueReadJs> {
  Napi::Value getTitle(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentValueRead, immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&>(info,
                                                                                                                                       getPtr(),
                                                                                                                                       static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getTitle),
                                                                                                                                       std::make_tuple());
  }
  Napi::Value getAuthor(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentValueRead, immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&>(info,
                                                                                                                                       getPtr(),
                                                                                                                                       static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getAuthor),
                                                                                                                                       std::make_tuple());
  }
  Napi::Value getCreator(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentValueRead, immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&>(info,
                                                                                                                                       getPtr(),
                                                                                                                                       static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getCreator),
                                                                                                                                       std::make_tuple());
  }
  Napi::Value getFiletags(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentValueRead, immer::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&>(info,
                                                                                                                              getPtr(),
                                                                                                                              static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getFiletags),
                                                                                                                              std::make_tuple());
  }
  Napi::Value getEmail(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentValueRead, immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>> const&>(info,
                                                                                                                                     getPtr(),
                                                                                                                                     static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getEmail),
                                                                                                                                     std::make_tuple());
  }
  Napi::Value getLanguage(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentValueRead, immer::flex_vector<hstd::Str> const&>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<immer::flex_vector<hstd::Str> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getLanguage),
                                                                                                 std::make_tuple());
  }
  Napi::Value getOptions(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentValueRead, org::imm::ImmIdT<org::imm::ImmDocumentOptions> const&>(info,
                                                                                                                  getPtr(),
                                                                                                                  static_cast<org::imm::ImmIdT<org::imm::ImmDocumentOptions> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getOptions),
                                                                                                                  std::make_tuple());
  }
  Napi::Value getExportfilename(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDocumentValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                        getPtr(),
                                                                                                        static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getExportfilename),
                                                                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentValueReadJs", {InstanceMethod("getTitle", &ImmDocumentValueReadJs::getTitle),
                                                                      InstanceMethod("getAuthor", &ImmDocumentValueReadJs::getAuthor),
                                                                      InstanceMethod("getCreator", &ImmDocumentValueReadJs::getCreator),
                                                                      InstanceMethod("getFiletags", &ImmDocumentValueReadJs::getFiletags),
                                                                      InstanceMethod("getEmail", &ImmDocumentValueReadJs::getEmail),
                                                                      InstanceMethod("getLanguage", &ImmDocumentValueReadJs::getLanguage),
                                                                      InstanceMethod("getOptions", &ImmDocumentValueReadJs::getOptions),
                                                                      InstanceMethod("getExportfilename", &ImmDocumentValueReadJs::getExportfilename)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmDocumentValueRead> _stored;
  org::imm::ImmDocumentValueRead* getPtr() { return _stored.get(); }
};

struct ImmFileTargetValueReadJs : public Napi::ObjectWrap<ImmFileTargetValueReadJs> {
  Napi::Value getPath(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmFileTargetValueRead, immer::box<hstd::Str> const&>(info,
                                                                                           getPtr(),
                                                                                           static_cast<immer::box<hstd::Str> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getPath),
                                                                                           std::make_tuple());
  }
  Napi::Value getLine(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmFileTargetValueRead, immer::box<std::optional<int>> const&>(info,
                                                                                                    getPtr(),
                                                                                                    static_cast<immer::box<std::optional<int>> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getLine),
                                                                                                    std::make_tuple());
  }
  Napi::Value getSearchtarget(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmFileTargetValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                          getPtr(),
                                                                                                          static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getSearchtarget),
                                                                                                          std::make_tuple());
  }
  Napi::Value getRestricttoheadlines(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmFileTargetValueRead, bool const&>(info,
                                                                          getPtr(),
                                                                          static_cast<bool const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getRestricttoheadlines),
                                                                          std::make_tuple());
  }
  Napi::Value getTargetid(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmFileTargetValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                          getPtr(),
                                                                                                          static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getTargetid),
                                                                                                          std::make_tuple());
  }
  Napi::Value getRegexp(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmFileTargetValueRead, immer::box<std::optional<hstd::Str>> const&>(info,
                                                                                                          getPtr(),
                                                                                                          static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getRegexp),
                                                                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileTargetValueReadJs", {InstanceMethod("getPath", &ImmFileTargetValueReadJs::getPath),
                                                                        InstanceMethod("getLine", &ImmFileTargetValueReadJs::getLine),
                                                                        InstanceMethod("getSearchtarget", &ImmFileTargetValueReadJs::getSearchtarget),
                                                                        InstanceMethod("getRestricttoheadlines", &ImmFileTargetValueReadJs::getRestricttoheadlines),
                                                                        InstanceMethod("getTargetid", &ImmFileTargetValueReadJs::getTargetid),
                                                                        InstanceMethod("getRegexp", &ImmFileTargetValueReadJs::getRegexp)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileTargetValueReadJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmDocumentGroupValueRead> _stored;
  org::imm::ImmDocumentGroupValueRead* getPtr() { return _stored.get(); }
};

struct ImmFileValueReadJs : public Napi::ObjectWrap<ImmFileValueReadJs> {
  Napi::Value getRelpath(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmFileValueRead, immer::box<hstd::Str> const&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<immer::box<hstd::Str> const&(org::imm::ImmFileValueRead::*)() const>(&org::imm::ImmFileValueRead::getRelpath),
                                                                                     std::make_tuple());
  }
  Napi::Value getAbspath(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmFileValueRead, immer::box<hstd::Str> const&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<immer::box<hstd::Str> const&(org::imm::ImmFileValueRead::*)() const>(&org::imm::ImmFileValueRead::getAbspath),
                                                                                     std::make_tuple());
  }
  Napi::Value getData(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmFileValueRead, org::imm::ImmFile::Data const&>(info,
                                                                                       getPtr(),
                                                                                       static_cast<org::imm::ImmFile::Data const&(org::imm::ImmFileValueRead::*)() const>(&org::imm::ImmFileValueRead::getData),
                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileValueReadJs", {InstanceMethod("getRelpath", &ImmFileValueReadJs::getRelpath),
                                                                  InstanceMethod("getAbspath", &ImmFileValueReadJs::getAbspath),
                                                                  InstanceMethod("getData", &ImmFileValueReadJs::getData)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmFileValueRead> _stored;
  org::imm::ImmFileValueRead* getPtr() { return _stored.get(); }
};

struct ImmDirectoryValueReadJs : public Napi::ObjectWrap<ImmDirectoryValueReadJs> {
  Napi::Value getRelpath(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDirectoryValueRead, immer::box<hstd::Str> const&>(info,
                                                                                          getPtr(),
                                                                                          static_cast<immer::box<hstd::Str> const&(org::imm::ImmDirectoryValueRead::*)() const>(&org::imm::ImmDirectoryValueRead::getRelpath),
                                                                                          std::make_tuple());
  }
  Napi::Value getAbspath(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmDirectoryValueRead, immer::box<hstd::Str> const&>(info,
                                                                                          getPtr(),
                                                                                          static_cast<immer::box<hstd::Str> const&(org::imm::ImmDirectoryValueRead::*)() const>(&org::imm::ImmDirectoryValueRead::getAbspath),
                                                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDirectoryValueReadJs", {InstanceMethod("getRelpath", &ImmDirectoryValueReadJs::getRelpath),
                                                                       InstanceMethod("getAbspath", &ImmDirectoryValueReadJs::getAbspath)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDirectoryValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmDirectoryValueRead> _stored;
  org::imm::ImmDirectoryValueRead* getPtr() { return _stored.get(); }
};

struct ImmSymlinkValueReadJs : public Napi::ObjectWrap<ImmSymlinkValueReadJs> {
  Napi::Value getIsdirectory(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSymlinkValueRead, bool const&>(info,
                                                                       getPtr(),
                                                                       static_cast<bool const&(org::imm::ImmSymlinkValueRead::*)() const>(&org::imm::ImmSymlinkValueRead::getIsdirectory),
                                                                       std::make_tuple());
  }
  Napi::Value getAbspath(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmSymlinkValueRead, immer::box<hstd::Str> const&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<immer::box<hstd::Str> const&(org::imm::ImmSymlinkValueRead::*)() const>(&org::imm::ImmSymlinkValueRead::getAbspath),
                                                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymlinkValueReadJs", {InstanceMethod("getIsdirectory", &ImmSymlinkValueReadJs::getIsdirectory),
                                                                     InstanceMethod("getAbspath", &ImmSymlinkValueReadJs::getAbspath)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymlinkValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmSymlinkValueRead> _stored;
  org::imm::ImmSymlinkValueRead* getPtr() { return _stored.get(); }
};

struct ImmCmdIncludeValueReadJs : public Napi::ObjectWrap<ImmCmdIncludeValueReadJs> {
  Napi::Value getPath(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdIncludeValueRead, immer::box<hstd::Str> const&>(info,
                                                                                           getPtr(),
                                                                                           static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdIncludeValueRead::*)() const>(&org::imm::ImmCmdIncludeValueRead::getPath),
                                                                                           std::make_tuple());
  }
  Napi::Value getFirstline(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdIncludeValueRead, immer::box<std::optional<int>> const&>(info,
                                                                                                    getPtr(),
                                                                                                    static_cast<immer::box<std::optional<int>> const&(org::imm::ImmCmdIncludeValueRead::*)() const>(&org::imm::ImmCmdIncludeValueRead::getFirstline),
                                                                                                    std::make_tuple());
  }
  Napi::Value getLastline(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdIncludeValueRead, immer::box<std::optional<int>> const&>(info,
                                                                                                    getPtr(),
                                                                                                    static_cast<immer::box<std::optional<int>> const&(org::imm::ImmCmdIncludeValueRead::*)() const>(&org::imm::ImmCmdIncludeValueRead::getLastline),
                                                                                                    std::make_tuple());
  }
  Napi::Value getData(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmCmdIncludeValueRead, org::imm::ImmCmdInclude::Data const&>(info,
                                                                                                   getPtr(),
                                                                                                   static_cast<org::imm::ImmCmdInclude::Data const&(org::imm::ImmCmdIncludeValueRead::*)() const>(&org::imm::ImmCmdIncludeValueRead::getData),
                                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdIncludeValueReadJs", {InstanceMethod("getPath", &ImmCmdIncludeValueReadJs::getPath),
                                                                        InstanceMethod("getFirstline", &ImmCmdIncludeValueReadJs::getFirstline),
                                                                        InstanceMethod("getLastline", &ImmCmdIncludeValueReadJs::getLastline),
                                                                        InstanceMethod("getData", &ImmCmdIncludeValueReadJs::getData)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdIncludeValueReadJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdIncludeValueRead> _stored;
  org::imm::ImmCmdIncludeValueRead* getPtr() { return _stored.get(); }
};

struct ImmAstContextJs : public Napi::ObjectWrap<ImmAstContextJs> {
  Napi::Value addRoot(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmAstContext, org::imm::ImmAstVersion>(info,
                                                                        getPtr(),
                                                                        static_cast<org::imm::ImmAstVersion(org::imm::ImmAstContext::*)(org::sem::SemId<org::sem::Org>)>(&org::imm::ImmAstContext::addRoot),
                                                                        std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::Org>>{"data"}));
  }
  Napi::Value get(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmAstContext, org::sem::SemId<org::sem::Org>>(info,
                                                                               getPtr(),
                                                                               static_cast<org::sem::SemId<org::sem::Org>(org::imm::ImmAstContext::*)(org::imm::ImmId)>(&org::imm::ImmAstContext::get),
                                                                               std::make_tuple(CxxArgSpec<org::imm::ImmId>{"id"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAstContextJs", {InstanceMethod("addRoot", &ImmAstContextJs::addRoot),
                                                               InstanceMethod("get", &ImmAstContextJs::get)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAstContextJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAstContext> _stored;
  org::imm::ImmAstContext* getPtr() { return _stored.get(); }
};

struct ImmAstVersionJs : public Napi::ObjectWrap<ImmAstVersionJs> {
  Napi::Value getRoot(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAstVersion, org::imm::ImmId>(info,
                                                                     getPtr(),
                                                                     static_cast<org::imm::ImmId(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getRoot),
                                                                     std::make_tuple());
  }
  Napi::Value getRootAdapter(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAstVersion, org::imm::ImmAdapter>(info,
                                                                          getPtr(),
                                                                          static_cast<org::imm::ImmAdapter(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getRootAdapter),
                                                                          std::make_tuple());
  }
  Napi::Value getContext(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAstVersion, std::shared_ptr<org::imm::ImmAstContext>>(info,
                                                                                              getPtr(),
                                                                                              static_cast<std::shared_ptr<org::imm::ImmAstContext>(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getContext),
                                                                                              std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAstVersionJs", {InstanceMethod("getRoot", &ImmAstVersionJs::getRoot),
                                                               InstanceMethod("getRootAdapter", &ImmAstVersionJs::getRootAdapter),
                                                               InstanceMethod("getContext", &ImmAstVersionJs::getContext)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAstVersionJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAstVersion> _stored;
  org::imm::ImmAstVersion* getPtr() { return _stored.get(); }
};

struct ImmAdapterJs : public Napi::ObjectWrap<ImmAdapterJs> {
  Napi::Value size(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, int>(info,
                                                      getPtr(),
                                                      static_cast<int(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::size),
                                                      std::make_tuple());
  }
  Napi::Value isNil(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::isNil),
                                                       std::make_tuple());
  }
  Napi::Value isRoot(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::isRoot),
                                                       std::make_tuple());
  }
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, OrgSemKind>(info,
                                                             getPtr(),
                                                             static_cast<OrgSemKind(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getKind),
                                                             std::make_tuple());
  }
  Napi::Value uniq(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, org::imm::ImmUniqId>(info,
                                                                      getPtr(),
                                                                      static_cast<org::imm::ImmUniqId(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::uniq),
                                                                      std::make_tuple());
  }
  Napi::Value treeReprString(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, std::string>(info,
                                                              getPtr(),
                                                              static_cast<std::string(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::treeReprString),
                                                              std::make_tuple());
  }
  Napi::Value treeReprStringOpts(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, std::string>(info,
                                                              getPtr(),
                                                              static_cast<std::string(org::imm::ImmAdapter::*)(org::imm::ImmAdapter::TreeReprConf const&) const>(&org::imm::ImmAdapter::treeReprStringOpts),
                                                              std::make_tuple(CxxArgSpec<org::imm::ImmAdapter::TreeReprConf>{"conf"}));
  }
  Napi::Value isDirectParentOf(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isDirectParentOf),
                                                       std::make_tuple(CxxArgSpec<org::imm::ImmAdapter>{"other"}));
  }
  Napi::Value isIndirectParentOf(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isIndirectParentOf),
                                                       std::make_tuple(CxxArgSpec<org::imm::ImmAdapter>{"other"}));
  }
  Napi::Value isSubnodeOf(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isSubnodeOf),
                                                       std::make_tuple(CxxArgSpec<org::imm::ImmAdapter>{"other"}));
  }
  Napi::Value getParent(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, std::optional<org::imm::ImmAdapter>>(info,
                                                                                      getPtr(),
                                                                                      static_cast<std::optional<org::imm::ImmAdapter>(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getParent),
                                                                                      std::make_tuple());
  }
  Napi::Value getSelfIndex(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, int>(info,
                                                      getPtr(),
                                                      static_cast<int(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getSelfIndex),
                                                      std::make_tuple());
  }
  Napi::Value atIdReflPathStep(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, org::imm::ImmAdapter>(info,
                                                                       getPtr(),
                                                                       static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(org::imm::ImmId, org::imm::ImmPathStep) const>(&org::imm::ImmAdapter::at),
                                                                       std::make_tuple(CxxArgSpec<org::imm::ImmId>{"id"},
                                                                                       CxxArgSpec<org::imm::ImmPathStep>{"idx"}));
  }
  Napi::Value atField(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, org::imm::ImmAdapter>(info,
                                                                       getPtr(),
                                                                       static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(org::imm::ImmReflFieldId const&) const>(&org::imm::ImmAdapter::at),
                                                                       std::make_tuple(CxxArgSpec<org::imm::ImmReflFieldId>{"field"}));
  }
  Napi::Value atIndex(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, org::imm::ImmAdapter>(info,
                                                                       getPtr(),
                                                                       static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(int, bool) const>(&org::imm::ImmAdapter::at),
                                                                       std::make_tuple(CxxArgSpec<int>{"idx"},
                                                                                       CxxArgSpec<bool>{"withPath", 1}));
  }
  Napi::Value atPath(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, org::imm::ImmAdapter>(info,
                                                                       getPtr(),
                                                                       static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(hstd::Vec<int> const&, bool) const>(&org::imm::ImmAdapter::at),
                                                                       std::make_tuple(CxxArgSpec<hstd::Vec<int>>{"path"},
                                                                                       CxxArgSpec<bool>{"withPath", 1}));
  }
  Napi::Value is(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::imm::ImmAdapter::*)(OrgSemKind) const>(&org::imm::ImmAdapter::is),
                                                       std::make_tuple(CxxArgSpec<OrgSemKind>{"kind"}));
  }
  Napi::Value sub(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapter, hstd::Vec<org::imm::ImmAdapter>>(info,
                                                                                  getPtr(),
                                                                                  static_cast<hstd::Vec<org::imm::ImmAdapter>(org::imm::ImmAdapter::*)(bool) const>(&org::imm::ImmAdapter::sub),
                                                                                  std::make_tuple(CxxArgSpec<bool>{"withPath", 1}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterJs", {InstanceMethod("size", &ImmAdapterJs::size),
                                                            InstanceMethod("isNil", &ImmAdapterJs::isNil),
                                                            InstanceMethod("isRoot", &ImmAdapterJs::isRoot),
                                                            InstanceMethod("getKind", &ImmAdapterJs::getKind),
                                                            InstanceMethod("uniq", &ImmAdapterJs::uniq),
                                                            InstanceMethod("treeReprString", &ImmAdapterJs::treeReprString),
                                                            InstanceMethod("treeReprStringOpts", &ImmAdapterJs::treeReprStringOpts),
                                                            InstanceMethod("isDirectParentOf", &ImmAdapterJs::isDirectParentOf),
                                                            InstanceMethod("isIndirectParentOf", &ImmAdapterJs::isIndirectParentOf),
                                                            InstanceMethod("isSubnodeOf", &ImmAdapterJs::isSubnodeOf),
                                                            InstanceMethod("getParent", &ImmAdapterJs::getParent),
                                                            InstanceMethod("getSelfIndex", &ImmAdapterJs::getSelfIndex),
                                                            InstanceMethod("atIdReflPathStep", &ImmAdapterJs::atIdReflPathStep),
                                                            InstanceMethod("atField", &ImmAdapterJs::atField),
                                                            InstanceMethod("atIndex", &ImmAdapterJs::atIndex),
                                                            InstanceMethod("atPath", &ImmAdapterJs::atPath),
                                                            InstanceMethod("is", &ImmAdapterJs::is),
                                                            InstanceMethod("sub", &ImmAdapterJs::sub)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapter> _stored;
  org::imm::ImmAdapter* getPtr() { return _stored.get(); }
};

struct ImmAdapterVirtualBaseJs : public Napi::ObjectWrap<ImmAdapterVirtualBaseJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterVirtualBaseJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterVirtualBaseJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterVirtualBase> _stored;
  org::imm::ImmAdapterVirtualBase* getPtr() { return _stored.get(); }
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
  std::shared_ptr<org::OrgTreeExportOpts> _stored;
  org::OrgTreeExportOpts* getPtr() { return _stored.get(); }
};

struct AstTrackingPathJs : public Napi::ObjectWrap<AstTrackingPathJs> {
  Napi::Value getParent(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingPath, org::sem::SemId<org::sem::Org>>(info,
                                                                                 getPtr(),
                                                                                 static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)(int) const>(&org::AstTrackingPath::getParent),
                                                                                 std::make_tuple(CxxArgSpec<int>{"offset", 0}));
  }
  Napi::Value getNode(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingPath, org::sem::SemId<org::sem::Org>>(info,
                                                                                 getPtr(),
                                                                                 static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)() const>(&org::AstTrackingPath::getNode),
                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AstTrackingPathJs", {InstanceMethod("getParent", &AstTrackingPathJs::getParent),
                                                                 InstanceMethod("getNode", &AstTrackingPathJs::getNode)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AstTrackingPathJs", func);
    return exports;
  }
  std::shared_ptr<org::AstTrackingPath> _stored;
  org::AstTrackingPath* getPtr() { return _stored.get(); }
};

struct AstTrackingAlternativesJs : public Napi::ObjectWrap<AstTrackingAlternativesJs> {
  Napi::Value getAllNodes(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingAlternatives, hstd::Vec<org::sem::SemId<org::sem::Org>>>(info,
                                                                                                    getPtr(),
                                                                                                    static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getAllNodes),
                                                                                                    std::make_tuple());
  }
  Napi::Value getNode(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingAlternatives, org::sem::SemId<org::sem::Org>>(info,
                                                                                         getPtr(),
                                                                                         static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getNode),
                                                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AstTrackingAlternativesJs", {InstanceMethod("getAllNodes", &AstTrackingAlternativesJs::getAllNodes),
                                                                         InstanceMethod("getNode", &AstTrackingAlternativesJs::getNode)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AstTrackingAlternativesJs", func);
    return exports;
  }
  std::shared_ptr<org::AstTrackingAlternatives> _stored;
  org::AstTrackingAlternatives* getPtr() { return _stored.get(); }
};

struct AstTrackingGroupJs : public Napi::ObjectWrap<AstTrackingGroupJs> {
  Napi::Value getRadioTargetConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingGroup, org::AstTrackingGroup::RadioTarget const&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<org::AstTrackingGroup::RadioTarget const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getRadioTarget),
                                                                                             std::make_tuple());
  }
  Napi::Value getTrackedHashtagConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingGroup, org::AstTrackingGroup::TrackedHashtag const&>(info,
                                                                                                getPtr(),
                                                                                                static_cast<org::AstTrackingGroup::TrackedHashtag const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getTrackedHashtag),
                                                                                                std::make_tuple());
  }
  Napi::Value getTrackedHashtagMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::AstTrackingGroup, org::AstTrackingGroup::TrackedHashtag&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<org::AstTrackingGroup::TrackedHashtag&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getTrackedHashtag),
                                                                                     std::make_tuple());
  }
  Napi::Value getSingleConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingGroup, org::AstTrackingGroup::Single const&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<org::AstTrackingGroup::Single const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getSingle),
                                                                                        std::make_tuple());
  }
  Napi::Value getRadioTargetMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::AstTrackingGroup, org::AstTrackingGroup::RadioTarget&>(info,
                                                                                  getPtr(),
                                                                                  static_cast<org::AstTrackingGroup::RadioTarget&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getRadioTarget),
                                                                                  std::make_tuple());
  }
  Napi::Value getSingleMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::AstTrackingGroup, org::AstTrackingGroup::Single&>(info,
                                                                             getPtr(),
                                                                             static_cast<org::AstTrackingGroup::Single&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getSingle),
                                                                             std::make_tuple());
  }
  Napi::Value isSingle(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingGroup, bool>(info,
                                                        getPtr(),
                                                        static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isSingle),
                                                        std::make_tuple());
  }
  Napi::Value isTrackedHashtag(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingGroup, bool>(info,
                                                        getPtr(),
                                                        static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isTrackedHashtag),
                                                        std::make_tuple());
  }
  Napi::Value isRadioTarget(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingGroup, bool>(info,
                                                        getPtr(),
                                                        static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isRadioTarget),
                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AstTrackingGroupJs", {InstanceMethod("getRadioTargetConst", &AstTrackingGroupJs::getRadioTargetConst),
                                                                  InstanceMethod("getTrackedHashtagConst", &AstTrackingGroupJs::getTrackedHashtagConst),
                                                                  InstanceMethod("getTrackedHashtagMut", &AstTrackingGroupJs::getTrackedHashtagMut),
                                                                  InstanceMethod("getSingleConst", &AstTrackingGroupJs::getSingleConst),
                                                                  InstanceMethod("getRadioTargetMut", &AstTrackingGroupJs::getRadioTargetMut),
                                                                  InstanceMethod("getSingleMut", &AstTrackingGroupJs::getSingleMut),
                                                                  InstanceMethod("isSingle", &AstTrackingGroupJs::isSingle),
                                                                  InstanceMethod("isTrackedHashtag", &AstTrackingGroupJs::isTrackedHashtag),
                                                                  InstanceMethod("isRadioTarget", &AstTrackingGroupJs::isRadioTarget)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AstTrackingGroupJs", func);
    return exports;
  }
  std::shared_ptr<org::AstTrackingGroup> _stored;
  org::AstTrackingGroup* getPtr() { return _stored.get(); }
};

struct AstTrackingMapJs : public Napi::ObjectWrap<AstTrackingMapJs> {
  Napi::Value getIdPath(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingMap, std::optional<org::AstTrackingAlternatives>>(info,
                                                                                             getPtr(),
                                                                                             static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getIdPath),
                                                                                             std::make_tuple(CxxArgSpec<hstd::Str>{"id"}));
  }
  Napi::Value getNamePath(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingMap, std::optional<org::AstTrackingAlternatives>>(info,
                                                                                             getPtr(),
                                                                                             static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getNamePath),
                                                                                             std::make_tuple(CxxArgSpec<hstd::Str>{"id"}));
  }
  Napi::Value getAnchorTarget(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingMap, std::optional<org::AstTrackingAlternatives>>(info,
                                                                                             getPtr(),
                                                                                             static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getAnchorTarget),
                                                                                             std::make_tuple(CxxArgSpec<hstd::Str>{"id"}));
  }
  Napi::Value getFootnotePath(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::AstTrackingMap, std::optional<org::AstTrackingAlternatives>>(info,
                                                                                             getPtr(),
                                                                                             static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getFootnotePath),
                                                                                             std::make_tuple(CxxArgSpec<hstd::Str>{"id"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AstTrackingMapJs", {InstanceMethod("getIdPath", &AstTrackingMapJs::getIdPath),
                                                                InstanceMethod("getNamePath", &AstTrackingMapJs::getNamePath),
                                                                InstanceMethod("getAnchorTarget", &AstTrackingMapJs::getAnchorTarget),
                                                                InstanceMethod("getFootnotePath", &AstTrackingMapJs::getFootnotePath)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AstTrackingMapJs", func);
    return exports;
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
  std::shared_ptr<hstd::SequenceAnnotationTag> _stored;
  hstd::SequenceAnnotationTag* getPtr() { return _stored.get(); }
};

struct SequenceAnnotationJs : public Napi::ObjectWrap<SequenceAnnotationJs> {
  Napi::Value isAnnotatedWith(Napi::CallbackInfo const& info) {
    return WrapConstMethod<hstd::SequenceAnnotation, bool>(info,
                                                           getPtr(),
                                                           static_cast<bool(hstd::SequenceAnnotation::*)(int, int) const>(&hstd::SequenceAnnotation::isAnnotatedWith),
                                                           std::make_tuple(CxxArgSpec<int>{"groupKind"},
                                                                           CxxArgSpec<int>{"segmentKind"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SequenceAnnotationJs", {InstanceMethod("isAnnotatedWith", &SequenceAnnotationJs::isAnnotatedWith)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SequenceAnnotationJs", func);
    return exports;
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
  std::shared_ptr<org::graph::MapLink> _stored;
  org::graph::MapLink* getPtr() { return _stored.get(); }
};

struct MapNodePropJs : public Napi::ObjectWrap<MapNodePropJs> {
  Napi::Value getSubtreeId(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapNodeProp, std::optional<hstd::Str>>(info,
                                                                              getPtr(),
                                                                              static_cast<std::optional<hstd::Str>(org::graph::MapNodeProp::*)() const>(&org::graph::MapNodeProp::getSubtreeId),
                                                                              std::make_tuple());
  }
  Napi::Value getFootnoteName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapNodeProp, std::optional<hstd::Str>>(info,
                                                                              getPtr(),
                                                                              static_cast<std::optional<hstd::Str>(org::graph::MapNodeProp::*)() const>(&org::graph::MapNodeProp::getFootnoteName),
                                                                              std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapNodePropJs", {InstanceMethod("getSubtreeId", &MapNodePropJs::getSubtreeId),
                                                             InstanceMethod("getFootnoteName", &MapNodePropJs::getFootnoteName)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MapNodePropJs", func);
    return exports;
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
  std::shared_ptr<org::graph::MapEdgeProp> _stored;
  org::graph::MapEdgeProp* getPtr() { return _stored.get(); }
};

struct MapNodeJs : public Napi::ObjectWrap<MapNodeJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapNode, bool>(info,
                                                      getPtr(),
                                                      static_cast<bool(org::graph::MapNode::*)(org::graph::MapNode const&) const>(&org::graph::MapNode::operator==),
                                                      std::make_tuple(CxxArgSpec<org::graph::MapNode>{"other"}));
  }
  Napi::Value operator<(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapNode, bool>(info,
                                                      getPtr(),
                                                      static_cast<bool(org::graph::MapNode::*)(org::graph::MapNode const&) const>(&org::graph::MapNode::operator<),
                                                      std::make_tuple(CxxArgSpec<org::graph::MapNode>{"other"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapNodeJs", {InstanceMethod("operator==", &MapNodeJs::operator==),
                                                         InstanceMethod("operator<", &MapNodeJs::operator<)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MapNodeJs", func);
    return exports;
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
  std::shared_ptr<org::graph::MapEdge> _stored;
  org::graph::MapEdge* getPtr() { return _stored.get(); }
};

struct MapGraphJs : public Napi::ObjectWrap<MapGraphJs> {
  Napi::Value nodeCount(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, int>(info,
                                                      getPtr(),
                                                      static_cast<int(org::graph::MapGraph::*)() const>(&org::graph::MapGraph::nodeCount),
                                                      std::make_tuple());
  }
  Napi::Value edgeCount(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, int>(info,
                                                      getPtr(),
                                                      static_cast<int(org::graph::MapGraph::*)() const>(&org::graph::MapGraph::edgeCount),
                                                      std::make_tuple());
  }
  Napi::Value outNodes(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, org::graph::AdjNodesList const&>(info,
                                                                                  getPtr(),
                                                                                  static_cast<org::graph::AdjNodesList const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outNodes),
                                                                                  std::make_tuple(CxxArgSpec<org::graph::MapNode>{"node"}));
  }
  Napi::Value inNodes(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, org::graph::AdjNodesList const&>(info,
                                                                                  getPtr(),
                                                                                  static_cast<org::graph::AdjNodesList const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inNodes),
                                                                                  std::make_tuple(CxxArgSpec<org::graph::MapNode>{"node"}));
  }
  Napi::Value adjEdges(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, hstd::Vec<org::graph::MapEdge>>(info,
                                                                                 getPtr(),
                                                                                 static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::adjEdges),
                                                                                 std::make_tuple(CxxArgSpec<org::graph::MapNode>{"node"}));
  }
  Napi::Value adjNodes(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, hstd::Vec<org::graph::MapNode>>(info,
                                                                                 getPtr(),
                                                                                 static_cast<hstd::Vec<org::graph::MapNode>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::adjNodes),
                                                                                 std::make_tuple(CxxArgSpec<org::graph::MapNode>{"node"}));
  }
  Napi::Value outEdges(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, hstd::Vec<org::graph::MapEdge>>(info,
                                                                                 getPtr(),
                                                                                 static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outEdges),
                                                                                 std::make_tuple(CxxArgSpec<org::graph::MapNode>{"node"}));
  }
  Napi::Value inEdges(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, hstd::Vec<org::graph::MapEdge>>(info,
                                                                                 getPtr(),
                                                                                 static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inEdges),
                                                                                 std::make_tuple(CxxArgSpec<org::graph::MapNode>{"node"}));
  }
  Napi::Value outDegree(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, int>(info,
                                                      getPtr(),
                                                      static_cast<int(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outDegree),
                                                      std::make_tuple(CxxArgSpec<org::graph::MapNode>{"node"}));
  }
  Napi::Value inDegree(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, int>(info,
                                                      getPtr(),
                                                      static_cast<int(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inDegree),
                                                      std::make_tuple(CxxArgSpec<org::graph::MapNode>{"node"}));
  }
  Napi::Value isRegisteredNode(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::isRegisteredNode),
                                                       std::make_tuple(CxxArgSpec<org::graph::MapNode>{"id"}));
  }
  Napi::Value isRegisteredNodeById(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::graph::MapGraph::*)(org::imm::ImmUniqId const&) const>(&org::graph::MapGraph::isRegisteredNode),
                                                       std::make_tuple(CxxArgSpec<org::imm::ImmUniqId>{"id"}));
  }
  Napi::Value atMapNode(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, org::graph::MapNodeProp const&>(info,
                                                                                 getPtr(),
                                                                                 static_cast<org::graph::MapNodeProp const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::at),
                                                                                 std::make_tuple(CxxArgSpec<org::graph::MapNode>{"node"}));
  }
  Napi::Value atMapEdge(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, org::graph::MapEdgeProp const&>(info,
                                                                                 getPtr(),
                                                                                 static_cast<org::graph::MapEdgeProp const&(org::graph::MapGraph::*)(org::graph::MapEdge const&) const>(&org::graph::MapGraph::at),
                                                                                 std::make_tuple(CxxArgSpec<org::graph::MapEdge>{"edge"}));
  }
  Napi::Value addEdge(Napi::CallbackInfo const& info) {
    return WrapMethod<org::graph::MapGraph, void>(info,
                                                  getPtr(),
                                                  static_cast<void(org::graph::MapGraph::*)(org::graph::MapEdge const&)>(&org::graph::MapGraph::addEdge),
                                                  std::make_tuple(CxxArgSpec<org::graph::MapEdge>{"edge"}));
  }
  Napi::Value addEdgeWithProp(Napi::CallbackInfo const& info) {
    return WrapMethod<org::graph::MapGraph, void>(info,
                                                  getPtr(),
                                                  static_cast<void(org::graph::MapGraph::*)(org::graph::MapEdge const&, org::graph::MapEdgeProp const&)>(&org::graph::MapGraph::addEdge),
                                                  std::make_tuple(CxxArgSpec<org::graph::MapEdge>{"edge"},
                                                                  CxxArgSpec<org::graph::MapEdgeProp>{"prop"}));
  }
  Napi::Value addNode(Napi::CallbackInfo const& info) {
    return WrapMethod<org::graph::MapGraph, void>(info,
                                                  getPtr(),
                                                  static_cast<void(org::graph::MapGraph::*)(org::graph::MapNode const&)>(&org::graph::MapGraph::addNode),
                                                  std::make_tuple(CxxArgSpec<org::graph::MapNode>{"node"}));
  }
  Napi::Value addNodeWithProp(Napi::CallbackInfo const& info) {
    return WrapMethod<org::graph::MapGraph, void>(info,
                                                  getPtr(),
                                                  static_cast<void(org::graph::MapGraph::*)(org::graph::MapNode const&, org::graph::MapNodeProp const&)>(&org::graph::MapGraph::addNode),
                                                  std::make_tuple(CxxArgSpec<org::graph::MapNode>{"node"},
                                                                  CxxArgSpec<org::graph::MapNodeProp>{"prop"}));
  }
  Napi::Value hasEdge(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&, org::graph::MapNode const&) const>(&org::graph::MapGraph::hasEdge),
                                                       std::make_tuple(CxxArgSpec<org::graph::MapNode>{"source"},
                                                                       CxxArgSpec<org::graph::MapNode>{"target"}));
  }
  Napi::Value hasNode(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::hasNode),
                                                       std::make_tuple(CxxArgSpec<org::graph::MapNode>{"node"}));
  }
  Napi::Value has2AdapterEdge(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::graph::MapGraph, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::graph::MapGraph::*)(org::imm::ImmAdapter const&, org::imm::ImmAdapter const&) const>(&org::graph::MapGraph::hasEdge),
                                                       std::make_tuple(CxxArgSpec<org::imm::ImmAdapter>{"source"},
                                                                       CxxArgSpec<org::imm::ImmAdapter>{"target"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MapGraphJs", {InstanceMethod("nodeCount", &MapGraphJs::nodeCount),
                                                          InstanceMethod("edgeCount", &MapGraphJs::edgeCount),
                                                          InstanceMethod("outNodes", &MapGraphJs::outNodes),
                                                          InstanceMethod("inNodes", &MapGraphJs::inNodes),
                                                          InstanceMethod("adjEdges", &MapGraphJs::adjEdges),
                                                          InstanceMethod("adjNodes", &MapGraphJs::adjNodes),
                                                          InstanceMethod("outEdges", &MapGraphJs::outEdges),
                                                          InstanceMethod("inEdges", &MapGraphJs::inEdges),
                                                          InstanceMethod("outDegree", &MapGraphJs::outDegree),
                                                          InstanceMethod("inDegree", &MapGraphJs::inDegree),
                                                          InstanceMethod("isRegisteredNode", &MapGraphJs::isRegisteredNode),
                                                          InstanceMethod("isRegisteredNodeById", &MapGraphJs::isRegisteredNodeById),
                                                          InstanceMethod("atMapNode", &MapGraphJs::atMapNode),
                                                          InstanceMethod("atMapEdge", &MapGraphJs::atMapEdge),
                                                          InstanceMethod("addEdge", &MapGraphJs::addEdge),
                                                          InstanceMethod("addEdgeWithProp", &MapGraphJs::addEdgeWithProp),
                                                          InstanceMethod("addNode", &MapGraphJs::addNode),
                                                          InstanceMethod("addNodeWithProp", &MapGraphJs::addNodeWithProp),
                                                          InstanceMethod("hasEdge", &MapGraphJs::hasEdge),
                                                          InstanceMethod("hasNode", &MapGraphJs::hasNode),
                                                          InstanceMethod("has2AdapterEdge", &MapGraphJs::has2AdapterEdge)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MapGraphJs", func);
    return exports;
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
  std::shared_ptr<org::graph::MapGraphState> _stored;
  org::graph::MapGraphState* getPtr() { return _stored.get(); }
};

struct LispCodeJs : public Napi::ObjectWrap<LispCodeJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, bool>(info,
                                                     getPtr(),
                                                     static_cast<bool(org::sem::LispCode::*)(org::sem::LispCode const&) const>(&org::sem::LispCode::operator==),
                                                     std::make_tuple(CxxArgSpec<org::sem::LispCode>{"other"}));
  }
  Napi::Value isCall(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, bool>(info,
                                                     getPtr(),
                                                     static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isCall),
                                                     std::make_tuple());
  }
  Napi::Value getCallConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, org::sem::LispCode::Call const&>(info,
                                                                                getPtr(),
                                                                                static_cast<org::sem::LispCode::Call const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getCall),
                                                                                std::make_tuple());
  }
  Napi::Value getCallMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LispCode, org::sem::LispCode::Call&>(info,
                                                                     getPtr(),
                                                                     static_cast<org::sem::LispCode::Call&(org::sem::LispCode::*)()>(&org::sem::LispCode::getCall),
                                                                     std::make_tuple());
  }
  Napi::Value isList(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, bool>(info,
                                                     getPtr(),
                                                     static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isList),
                                                     std::make_tuple());
  }
  Napi::Value getListConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, org::sem::LispCode::List const&>(info,
                                                                                getPtr(),
                                                                                static_cast<org::sem::LispCode::List const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getList),
                                                                                std::make_tuple());
  }
  Napi::Value getListMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LispCode, org::sem::LispCode::List&>(info,
                                                                     getPtr(),
                                                                     static_cast<org::sem::LispCode::List&(org::sem::LispCode::*)()>(&org::sem::LispCode::getList),
                                                                     std::make_tuple());
  }
  Napi::Value isKeyValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, bool>(info,
                                                     getPtr(),
                                                     static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isKeyValue),
                                                     std::make_tuple());
  }
  Napi::Value getKeyValueConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, org::sem::LispCode::KeyValue const&>(info,
                                                                                    getPtr(),
                                                                                    static_cast<org::sem::LispCode::KeyValue const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKeyValue),
                                                                                    std::make_tuple());
  }
  Napi::Value getKeyValueMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LispCode, org::sem::LispCode::KeyValue&>(info,
                                                                         getPtr(),
                                                                         static_cast<org::sem::LispCode::KeyValue&(org::sem::LispCode::*)()>(&org::sem::LispCode::getKeyValue),
                                                                         std::make_tuple());
  }
  Napi::Value isNumber(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, bool>(info,
                                                     getPtr(),
                                                     static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isNumber),
                                                     std::make_tuple());
  }
  Napi::Value getNumberConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, org::sem::LispCode::Number const&>(info,
                                                                                  getPtr(),
                                                                                  static_cast<org::sem::LispCode::Number const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getNumber),
                                                                                  std::make_tuple());
  }
  Napi::Value getNumberMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LispCode, org::sem::LispCode::Number&>(info,
                                                                       getPtr(),
                                                                       static_cast<org::sem::LispCode::Number&(org::sem::LispCode::*)()>(&org::sem::LispCode::getNumber),
                                                                       std::make_tuple());
  }
  Napi::Value isText(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, bool>(info,
                                                     getPtr(),
                                                     static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isText),
                                                     std::make_tuple());
  }
  Napi::Value getTextConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, org::sem::LispCode::Text const&>(info,
                                                                                getPtr(),
                                                                                static_cast<org::sem::LispCode::Text const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getText),
                                                                                std::make_tuple());
  }
  Napi::Value getTextMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LispCode, org::sem::LispCode::Text&>(info,
                                                                     getPtr(),
                                                                     static_cast<org::sem::LispCode::Text&(org::sem::LispCode::*)()>(&org::sem::LispCode::getText),
                                                                     std::make_tuple());
  }
  Napi::Value isIdent(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, bool>(info,
                                                     getPtr(),
                                                     static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isIdent),
                                                     std::make_tuple());
  }
  Napi::Value getIdentConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, org::sem::LispCode::Ident const&>(info,
                                                                                 getPtr(),
                                                                                 static_cast<org::sem::LispCode::Ident const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getIdent),
                                                                                 std::make_tuple());
  }
  Napi::Value getIdentMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LispCode, org::sem::LispCode::Ident&>(info,
                                                                      getPtr(),
                                                                      static_cast<org::sem::LispCode::Ident&(org::sem::LispCode::*)()>(&org::sem::LispCode::getIdent),
                                                                      std::make_tuple());
  }
  Napi::Value isBoolean(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, bool>(info,
                                                     getPtr(),
                                                     static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isBoolean),
                                                     std::make_tuple());
  }
  Napi::Value getBooleanConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, org::sem::LispCode::Boolean const&>(info,
                                                                                   getPtr(),
                                                                                   static_cast<org::sem::LispCode::Boolean const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getBoolean),
                                                                                   std::make_tuple());
  }
  Napi::Value getBooleanMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LispCode, org::sem::LispCode::Boolean&>(info,
                                                                        getPtr(),
                                                                        static_cast<org::sem::LispCode::Boolean&(org::sem::LispCode::*)()>(&org::sem::LispCode::getBoolean),
                                                                        std::make_tuple());
  }
  Napi::Value isReal(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, bool>(info,
                                                     getPtr(),
                                                     static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isReal),
                                                     std::make_tuple());
  }
  Napi::Value getRealConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, org::sem::LispCode::Real const&>(info,
                                                                                getPtr(),
                                                                                static_cast<org::sem::LispCode::Real const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getReal),
                                                                                std::make_tuple());
  }
  Napi::Value getRealMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LispCode, org::sem::LispCode::Real&>(info,
                                                                     getPtr(),
                                                                     static_cast<org::sem::LispCode::Real&(org::sem::LispCode::*)()>(&org::sem::LispCode::getReal),
                                                                     std::make_tuple());
  }
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, org::sem::LispCode::Kind>(info,
                                                                         getPtr(),
                                                                         static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKind),
                                                                         std::make_tuple());
  }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, char const*>(info,
                                                            getPtr(),
                                                            static_cast<char const*(org::sem::LispCode::*)() const>(&org::sem::LispCode::sub_variant_get_name),
                                                            std::make_tuple());
  }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, org::sem::LispCode::Data const&>(info,
                                                                                getPtr(),
                                                                                static_cast<org::sem::LispCode::Data const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::sub_variant_get_data),
                                                                                std::make_tuple());
  }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LispCode, org::sem::LispCode::Kind>(info,
                                                                         getPtr(),
                                                                         static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::sub_variant_get_kind),
                                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LispCodeJs", {InstanceMethod("operator==", &LispCodeJs::operator==),
                                                          InstanceMethod("isCall", &LispCodeJs::isCall),
                                                          InstanceMethod("getCallConst", &LispCodeJs::getCallConst),
                                                          InstanceMethod("getCallMut", &LispCodeJs::getCallMut),
                                                          InstanceMethod("isList", &LispCodeJs::isList),
                                                          InstanceMethod("getListConst", &LispCodeJs::getListConst),
                                                          InstanceMethod("getListMut", &LispCodeJs::getListMut),
                                                          InstanceMethod("isKeyValue", &LispCodeJs::isKeyValue),
                                                          InstanceMethod("getKeyValueConst", &LispCodeJs::getKeyValueConst),
                                                          InstanceMethod("getKeyValueMut", &LispCodeJs::getKeyValueMut),
                                                          InstanceMethod("isNumber", &LispCodeJs::isNumber),
                                                          InstanceMethod("getNumberConst", &LispCodeJs::getNumberConst),
                                                          InstanceMethod("getNumberMut", &LispCodeJs::getNumberMut),
                                                          InstanceMethod("isText", &LispCodeJs::isText),
                                                          InstanceMethod("getTextConst", &LispCodeJs::getTextConst),
                                                          InstanceMethod("getTextMut", &LispCodeJs::getTextMut),
                                                          InstanceMethod("isIdent", &LispCodeJs::isIdent),
                                                          InstanceMethod("getIdentConst", &LispCodeJs::getIdentConst),
                                                          InstanceMethod("getIdentMut", &LispCodeJs::getIdentMut),
                                                          InstanceMethod("isBoolean", &LispCodeJs::isBoolean),
                                                          InstanceMethod("getBooleanConst", &LispCodeJs::getBooleanConst),
                                                          InstanceMethod("getBooleanMut", &LispCodeJs::getBooleanMut),
                                                          InstanceMethod("isReal", &LispCodeJs::isReal),
                                                          InstanceMethod("getRealConst", &LispCodeJs::getRealConst),
                                                          InstanceMethod("getRealMut", &LispCodeJs::getRealMut),
                                                          InstanceMethod("getKind", &LispCodeJs::getKind),
                                                          InstanceMethod("sub_variant_get_name", &LispCodeJs::sub_variant_get_name),
                                                          InstanceMethod("sub_variant_get_data", &LispCodeJs::sub_variant_get_data),
                                                          InstanceMethod("sub_variant_get_kind", &LispCodeJs::sub_variant_get_kind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("LispCodeJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::LispCode> _stored;
  org::sem::LispCode* getPtr() { return _stored.get(); }
};

struct TblfmJs : public Napi::ObjectWrap<TblfmJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Tblfm, bool>(info,
                                                  getPtr(),
                                                  static_cast<bool(org::sem::Tblfm::*)(org::sem::Tblfm const&) const>(&org::sem::Tblfm::operator==),
                                                  std::make_tuple(CxxArgSpec<org::sem::Tblfm>{"other"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TblfmJs", {InstanceMethod("operator==", &TblfmJs::operator==)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("TblfmJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Tblfm> _stored;
  org::sem::Tblfm* getPtr() { return _stored.get(); }
};

struct AttrValueJs : public Napi::ObjectWrap<AttrValueJs> {
  Napi::Value getBool(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, hstd::Opt<bool>>(info,
                                                                 getPtr(),
                                                                 static_cast<hstd::Opt<bool>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getBool),
                                                                 std::make_tuple());
  }
  Napi::Value getInt(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, hstd::Opt<int>>(info,
                                                                getPtr(),
                                                                static_cast<hstd::Opt<int>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getInt),
                                                                std::make_tuple());
  }
  Napi::Value getString(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, hstd::Str>(info,
                                                           getPtr(),
                                                           static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getString),
                                                           std::make_tuple());
  }
  Napi::Value getFile(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, hstd::Str>(info,
                                                           getPtr(),
                                                           static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getFile),
                                                           std::make_tuple());
  }
  Napi::Value getReference(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, hstd::Str>(info,
                                                           getPtr(),
                                                           static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getReference),
                                                           std::make_tuple());
  }
  Napi::Value getDouble(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, hstd::Opt<double>>(info,
                                                                   getPtr(),
                                                                   static_cast<hstd::Opt<double>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getDouble),
                                                                   std::make_tuple());
  }
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, bool>(info,
                                                      getPtr(),
                                                      static_cast<bool(org::sem::AttrValue::*)(org::sem::AttrValue const&) const>(&org::sem::AttrValue::operator==),
                                                      std::make_tuple(CxxArgSpec<org::sem::AttrValue>{"other"}));
  }
  Napi::Value isTextValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, bool>(info,
                                                      getPtr(),
                                                      static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isTextValue),
                                                      std::make_tuple());
  }
  Napi::Value getTextValueConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, org::sem::AttrValue::TextValue const&>(info,
                                                                                       getPtr(),
                                                                                       static_cast<org::sem::AttrValue::TextValue const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getTextValue),
                                                                                       std::make_tuple());
  }
  Napi::Value getTextValueMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::AttrValue, org::sem::AttrValue::TextValue&>(info,
                                                                            getPtr(),
                                                                            static_cast<org::sem::AttrValue::TextValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getTextValue),
                                                                            std::make_tuple());
  }
  Napi::Value isFileReference(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, bool>(info,
                                                      getPtr(),
                                                      static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isFileReference),
                                                      std::make_tuple());
  }
  Napi::Value getFileReferenceConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, org::sem::AttrValue::FileReference const&>(info,
                                                                                           getPtr(),
                                                                                           static_cast<org::sem::AttrValue::FileReference const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getFileReference),
                                                                                           std::make_tuple());
  }
  Napi::Value getFileReferenceMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::AttrValue, org::sem::AttrValue::FileReference&>(info,
                                                                                getPtr(),
                                                                                static_cast<org::sem::AttrValue::FileReference&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getFileReference),
                                                                                std::make_tuple());
  }
  Napi::Value isLispValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, bool>(info,
                                                      getPtr(),
                                                      static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isLispValue),
                                                      std::make_tuple());
  }
  Napi::Value getLispValueConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, org::sem::AttrValue::LispValue const&>(info,
                                                                                       getPtr(),
                                                                                       static_cast<org::sem::AttrValue::LispValue const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getLispValue),
                                                                                       std::make_tuple());
  }
  Napi::Value getLispValueMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::AttrValue, org::sem::AttrValue::LispValue&>(info,
                                                                            getPtr(),
                                                                            static_cast<org::sem::AttrValue::LispValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getLispValue),
                                                                            std::make_tuple());
  }
  Napi::Value getDataKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, org::sem::AttrValue::DataKind>(info,
                                                                               getPtr(),
                                                                               static_cast<org::sem::AttrValue::DataKind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getDataKind),
                                                                               std::make_tuple());
  }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, char const*>(info,
                                                             getPtr(),
                                                             static_cast<char const*(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::sub_variant_get_name),
                                                             std::make_tuple());
  }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, org::sem::AttrValue::DataVariant const&>(info,
                                                                                         getPtr(),
                                                                                         static_cast<org::sem::AttrValue::DataVariant const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::sub_variant_get_data),
                                                                                         std::make_tuple());
  }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrValue, org::sem::AttrValue::DataKind>(info,
                                                                               getPtr(),
                                                                               static_cast<org::sem::AttrValue::DataKind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::sub_variant_get_kind),
                                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AttrValueJs", {InstanceMethod("getBool", &AttrValueJs::getBool),
                                                           InstanceMethod("getInt", &AttrValueJs::getInt),
                                                           InstanceMethod("getString", &AttrValueJs::getString),
                                                           InstanceMethod("getFile", &AttrValueJs::getFile),
                                                           InstanceMethod("getReference", &AttrValueJs::getReference),
                                                           InstanceMethod("getDouble", &AttrValueJs::getDouble),
                                                           InstanceMethod("operator==", &AttrValueJs::operator==),
                                                           InstanceMethod("isTextValue", &AttrValueJs::isTextValue),
                                                           InstanceMethod("getTextValueConst", &AttrValueJs::getTextValueConst),
                                                           InstanceMethod("getTextValueMut", &AttrValueJs::getTextValueMut),
                                                           InstanceMethod("isFileReference", &AttrValueJs::isFileReference),
                                                           InstanceMethod("getFileReferenceConst", &AttrValueJs::getFileReferenceConst),
                                                           InstanceMethod("getFileReferenceMut", &AttrValueJs::getFileReferenceMut),
                                                           InstanceMethod("isLispValue", &AttrValueJs::isLispValue),
                                                           InstanceMethod("getLispValueConst", &AttrValueJs::getLispValueConst),
                                                           InstanceMethod("getLispValueMut", &AttrValueJs::getLispValueMut),
                                                           InstanceMethod("getDataKind", &AttrValueJs::getDataKind),
                                                           InstanceMethod("sub_variant_get_name", &AttrValueJs::sub_variant_get_name),
                                                           InstanceMethod("sub_variant_get_data", &AttrValueJs::sub_variant_get_data),
                                                           InstanceMethod("sub_variant_get_kind", &AttrValueJs::sub_variant_get_kind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AttrValueJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::AttrValue> _stored;
  org::sem::AttrValue* getPtr() { return _stored.get(); }
};

struct HashTagFlatJs : public Napi::ObjectWrap<HashTagFlatJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::HashTagFlat, bool>(info,
                                                        getPtr(),
                                                        static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator==),
                                                        std::make_tuple(CxxArgSpec<org::sem::HashTagFlat>{"other"}));
  }
  Napi::Value operator<(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::HashTagFlat, bool>(info,
                                                        getPtr(),
                                                        static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator<),
                                                        std::make_tuple(CxxArgSpec<org::sem::HashTagFlat>{"other"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "HashTagFlatJs", {InstanceMethod("operator==", &HashTagFlatJs::operator==),
                                                             InstanceMethod("operator<", &HashTagFlatJs::operator<)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("HashTagFlatJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::HashTagFlat> _stored;
  org::sem::HashTagFlat* getPtr() { return _stored.get(); }
};

struct HashTagTextJs : public Napi::ObjectWrap<HashTagTextJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::HashTagText, bool>(info,
                                                        getPtr(),
                                                        static_cast<bool(org::sem::HashTagText::*)(org::sem::HashTagText const&) const>(&org::sem::HashTagText::operator==),
                                                        std::make_tuple(CxxArgSpec<org::sem::HashTagText>{"other"}));
  }
  Napi::Value prefixMatch(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::HashTagText, bool>(info,
                                                        getPtr(),
                                                        static_cast<bool(org::sem::HashTagText::*)(hstd::Vec<hstd::Str> const&) const>(&org::sem::HashTagText::prefixMatch),
                                                        std::make_tuple(CxxArgSpec<hstd::Vec<hstd::Str>>{"prefix"}));
  }
  Napi::Value getFlatHashes(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::HashTagText, hstd::Vec<org::sem::HashTagFlat>>(info,
                                                                                    getPtr(),
                                                                                    static_cast<hstd::Vec<org::sem::HashTagFlat>(org::sem::HashTagText::*)(bool) const>(&org::sem::HashTagText::getFlatHashes),
                                                                                    std::make_tuple(CxxArgSpec<bool>{"withIntermediate", true}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "HashTagTextJs", {InstanceMethod("operator==", &HashTagTextJs::operator==),
                                                             InstanceMethod("prefixMatch", &HashTagTextJs::prefixMatch),
                                                             InstanceMethod("getFlatHashes", &HashTagTextJs::getFlatHashes)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("HashTagTextJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::HashTagText> _stored;
  org::sem::HashTagText* getPtr() { return _stored.get(); }
};

struct SubtreePathJs : public Napi::ObjectWrap<SubtreePathJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreePath, bool>(info,
                                                        getPtr(),
                                                        static_cast<bool(org::sem::SubtreePath::*)(org::sem::SubtreePath const&) const>(&org::sem::SubtreePath::operator==),
                                                        std::make_tuple(CxxArgSpec<org::sem::SubtreePath>{"other"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreePathJs", {InstanceMethod("operator==", &SubtreePathJs::operator==)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SubtreePathJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::SubtreePath> _stored;
  org::sem::SubtreePath* getPtr() { return _stored.get(); }
};

struct LinkTargetJs : public Napi::ObjectWrap<LinkTargetJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::LinkTarget::*)(org::sem::LinkTarget const&) const>(&org::sem::LinkTarget::operator==),
                                                       std::make_tuple(CxxArgSpec<org::sem::LinkTarget>{"other"}));
  }
  Napi::Value isRaw(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isRaw),
                                                       std::make_tuple());
  }
  Napi::Value getRawConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::Raw const&>(info,
                                                                                   getPtr(),
                                                                                   static_cast<org::sem::LinkTarget::Raw const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getRaw),
                                                                                   std::make_tuple());
  }
  Napi::Value getRawMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LinkTarget, org::sem::LinkTarget::Raw&>(info,
                                                                        getPtr(),
                                                                        static_cast<org::sem::LinkTarget::Raw&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getRaw),
                                                                        std::make_tuple());
  }
  Napi::Value isId(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isId),
                                                       std::make_tuple());
  }
  Napi::Value getIdConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::Id const&>(info,
                                                                                  getPtr(),
                                                                                  static_cast<org::sem::LinkTarget::Id const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getId),
                                                                                  std::make_tuple());
  }
  Napi::Value getIdMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LinkTarget, org::sem::LinkTarget::Id&>(info,
                                                                       getPtr(),
                                                                       static_cast<org::sem::LinkTarget::Id&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getId),
                                                                       std::make_tuple());
  }
  Napi::Value isCustomId(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isCustomId),
                                                       std::make_tuple());
  }
  Napi::Value getCustomIdConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::CustomId const&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<org::sem::LinkTarget::CustomId const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getCustomId),
                                                                                        std::make_tuple());
  }
  Napi::Value getCustomIdMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LinkTarget, org::sem::LinkTarget::CustomId&>(info,
                                                                             getPtr(),
                                                                             static_cast<org::sem::LinkTarget::CustomId&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getCustomId),
                                                                             std::make_tuple());
  }
  Napi::Value isSubtreeTitle(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isSubtreeTitle),
                                                       std::make_tuple());
  }
  Napi::Value getSubtreeTitleConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::SubtreeTitle const&>(info,
                                                                                            getPtr(),
                                                                                            static_cast<org::sem::LinkTarget::SubtreeTitle const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getSubtreeTitle),
                                                                                            std::make_tuple());
  }
  Napi::Value getSubtreeTitleMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LinkTarget, org::sem::LinkTarget::SubtreeTitle&>(info,
                                                                                 getPtr(),
                                                                                 static_cast<org::sem::LinkTarget::SubtreeTitle&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getSubtreeTitle),
                                                                                 std::make_tuple());
  }
  Napi::Value isPerson(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isPerson),
                                                       std::make_tuple());
  }
  Napi::Value getPersonConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::Person const&>(info,
                                                                                      getPtr(),
                                                                                      static_cast<org::sem::LinkTarget::Person const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getPerson),
                                                                                      std::make_tuple());
  }
  Napi::Value getPersonMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LinkTarget, org::sem::LinkTarget::Person&>(info,
                                                                           getPtr(),
                                                                           static_cast<org::sem::LinkTarget::Person&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getPerson),
                                                                           std::make_tuple());
  }
  Napi::Value isUserProtocol(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isUserProtocol),
                                                       std::make_tuple());
  }
  Napi::Value getUserProtocolConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::UserProtocol const&>(info,
                                                                                            getPtr(),
                                                                                            static_cast<org::sem::LinkTarget::UserProtocol const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getUserProtocol),
                                                                                            std::make_tuple());
  }
  Napi::Value getUserProtocolMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LinkTarget, org::sem::LinkTarget::UserProtocol&>(info,
                                                                                 getPtr(),
                                                                                 static_cast<org::sem::LinkTarget::UserProtocol&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getUserProtocol),
                                                                                 std::make_tuple());
  }
  Napi::Value isInternal(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isInternal),
                                                       std::make_tuple());
  }
  Napi::Value getInternalConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::Internal const&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<org::sem::LinkTarget::Internal const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getInternal),
                                                                                        std::make_tuple());
  }
  Napi::Value getInternalMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LinkTarget, org::sem::LinkTarget::Internal&>(info,
                                                                             getPtr(),
                                                                             static_cast<org::sem::LinkTarget::Internal&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getInternal),
                                                                             std::make_tuple());
  }
  Napi::Value isFootnote(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFootnote),
                                                       std::make_tuple());
  }
  Napi::Value getFootnoteConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::Footnote const&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<org::sem::LinkTarget::Footnote const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getFootnote),
                                                                                        std::make_tuple());
  }
  Napi::Value getFootnoteMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LinkTarget, org::sem::LinkTarget::Footnote&>(info,
                                                                             getPtr(),
                                                                             static_cast<org::sem::LinkTarget::Footnote&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFootnote),
                                                                             std::make_tuple());
  }
  Napi::Value isFile(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFile),
                                                       std::make_tuple());
  }
  Napi::Value getFileConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::File const&>(info,
                                                                                    getPtr(),
                                                                                    static_cast<org::sem::LinkTarget::File const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getFile),
                                                                                    std::make_tuple());
  }
  Napi::Value getFileMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LinkTarget, org::sem::LinkTarget::File&>(info,
                                                                         getPtr(),
                                                                         static_cast<org::sem::LinkTarget::File&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFile),
                                                                         std::make_tuple());
  }
  Napi::Value isAttachment(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isAttachment),
                                                       std::make_tuple());
  }
  Napi::Value getAttachmentConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::Attachment const&>(info,
                                                                                          getPtr(),
                                                                                          static_cast<org::sem::LinkTarget::Attachment const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getAttachment),
                                                                                          std::make_tuple());
  }
  Napi::Value getAttachmentMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::LinkTarget, org::sem::LinkTarget::Attachment&>(info,
                                                                               getPtr(),
                                                                               static_cast<org::sem::LinkTarget::Attachment&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getAttachment),
                                                                               std::make_tuple());
  }
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::Kind>(info,
                                                                             getPtr(),
                                                                             static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getKind),
                                                                             std::make_tuple());
  }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, char const*>(info,
                                                              getPtr(),
                                                              static_cast<char const*(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::sub_variant_get_name),
                                                              std::make_tuple());
  }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::Data const&>(info,
                                                                                    getPtr(),
                                                                                    static_cast<org::sem::LinkTarget::Data const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::sub_variant_get_data),
                                                                                    std::make_tuple());
  }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::LinkTarget, org::sem::LinkTarget::Kind>(info,
                                                                             getPtr(),
                                                                             static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::sub_variant_get_kind),
                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LinkTargetJs", {InstanceMethod("operator==", &LinkTargetJs::operator==),
                                                            InstanceMethod("isRaw", &LinkTargetJs::isRaw),
                                                            InstanceMethod("getRawConst", &LinkTargetJs::getRawConst),
                                                            InstanceMethod("getRawMut", &LinkTargetJs::getRawMut),
                                                            InstanceMethod("isId", &LinkTargetJs::isId),
                                                            InstanceMethod("getIdConst", &LinkTargetJs::getIdConst),
                                                            InstanceMethod("getIdMut", &LinkTargetJs::getIdMut),
                                                            InstanceMethod("isCustomId", &LinkTargetJs::isCustomId),
                                                            InstanceMethod("getCustomIdConst", &LinkTargetJs::getCustomIdConst),
                                                            InstanceMethod("getCustomIdMut", &LinkTargetJs::getCustomIdMut),
                                                            InstanceMethod("isSubtreeTitle", &LinkTargetJs::isSubtreeTitle),
                                                            InstanceMethod("getSubtreeTitleConst", &LinkTargetJs::getSubtreeTitleConst),
                                                            InstanceMethod("getSubtreeTitleMut", &LinkTargetJs::getSubtreeTitleMut),
                                                            InstanceMethod("isPerson", &LinkTargetJs::isPerson),
                                                            InstanceMethod("getPersonConst", &LinkTargetJs::getPersonConst),
                                                            InstanceMethod("getPersonMut", &LinkTargetJs::getPersonMut),
                                                            InstanceMethod("isUserProtocol", &LinkTargetJs::isUserProtocol),
                                                            InstanceMethod("getUserProtocolConst", &LinkTargetJs::getUserProtocolConst),
                                                            InstanceMethod("getUserProtocolMut", &LinkTargetJs::getUserProtocolMut),
                                                            InstanceMethod("isInternal", &LinkTargetJs::isInternal),
                                                            InstanceMethod("getInternalConst", &LinkTargetJs::getInternalConst),
                                                            InstanceMethod("getInternalMut", &LinkTargetJs::getInternalMut),
                                                            InstanceMethod("isFootnote", &LinkTargetJs::isFootnote),
                                                            InstanceMethod("getFootnoteConst", &LinkTargetJs::getFootnoteConst),
                                                            InstanceMethod("getFootnoteMut", &LinkTargetJs::getFootnoteMut),
                                                            InstanceMethod("isFile", &LinkTargetJs::isFile),
                                                            InstanceMethod("getFileConst", &LinkTargetJs::getFileConst),
                                                            InstanceMethod("getFileMut", &LinkTargetJs::getFileMut),
                                                            InstanceMethod("isAttachment", &LinkTargetJs::isAttachment),
                                                            InstanceMethod("getAttachmentConst", &LinkTargetJs::getAttachmentConst),
                                                            InstanceMethod("getAttachmentMut", &LinkTargetJs::getAttachmentMut),
                                                            InstanceMethod("getKind", &LinkTargetJs::getKind),
                                                            InstanceMethod("sub_variant_get_name", &LinkTargetJs::sub_variant_get_name),
                                                            InstanceMethod("sub_variant_get_data", &LinkTargetJs::sub_variant_get_data),
                                                            InstanceMethod("sub_variant_get_kind", &LinkTargetJs::sub_variant_get_kind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("LinkTargetJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::LinkTarget> _stored;
  org::sem::LinkTarget* getPtr() { return _stored.get(); }
};

struct SubtreeLogHeadJs : public Napi::ObjectWrap<SubtreeLogHeadJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, bool>(info,
                                                           getPtr(),
                                                           static_cast<bool(org::sem::SubtreeLogHead::*)(org::sem::SubtreeLogHead const&) const>(&org::sem::SubtreeLogHead::operator==),
                                                           std::make_tuple(CxxArgSpec<org::sem::SubtreeLogHead>{"other"}));
  }
  Napi::Value isPriority(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, bool>(info,
                                                           getPtr(),
                                                           static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isPriority),
                                                           std::make_tuple());
  }
  Napi::Value getPriorityConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Priority const&>(info,
                                                                                                getPtr(),
                                                                                                static_cast<org::sem::SubtreeLogHead::Priority const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getPriority),
                                                                                                std::make_tuple());
  }
  Napi::Value getPriorityMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Priority&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<org::sem::SubtreeLogHead::Priority&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getPriority),
                                                                                     std::make_tuple());
  }
  Napi::Value isNote(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, bool>(info,
                                                           getPtr(),
                                                           static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isNote),
                                                           std::make_tuple());
  }
  Napi::Value getNoteConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Note const&>(info,
                                                                                            getPtr(),
                                                                                            static_cast<org::sem::SubtreeLogHead::Note const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getNote),
                                                                                            std::make_tuple());
  }
  Napi::Value getNoteMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Note&>(info,
                                                                                 getPtr(),
                                                                                 static_cast<org::sem::SubtreeLogHead::Note&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getNote),
                                                                                 std::make_tuple());
  }
  Napi::Value isRefile(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, bool>(info,
                                                           getPtr(),
                                                           static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isRefile),
                                                           std::make_tuple());
  }
  Napi::Value getRefileConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Refile const&>(info,
                                                                                              getPtr(),
                                                                                              static_cast<org::sem::SubtreeLogHead::Refile const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getRefile),
                                                                                              std::make_tuple());
  }
  Napi::Value getRefileMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Refile&>(info,
                                                                                   getPtr(),
                                                                                   static_cast<org::sem::SubtreeLogHead::Refile&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getRefile),
                                                                                   std::make_tuple());
  }
  Napi::Value isClock(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, bool>(info,
                                                           getPtr(),
                                                           static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isClock),
                                                           std::make_tuple());
  }
  Napi::Value getClockConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Clock const&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<org::sem::SubtreeLogHead::Clock const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getClock),
                                                                                             std::make_tuple());
  }
  Napi::Value getClockMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Clock&>(info,
                                                                                  getPtr(),
                                                                                  static_cast<org::sem::SubtreeLogHead::Clock&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getClock),
                                                                                  std::make_tuple());
  }
  Napi::Value isState(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, bool>(info,
                                                           getPtr(),
                                                           static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isState),
                                                           std::make_tuple());
  }
  Napi::Value getStateConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::State const&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<org::sem::SubtreeLogHead::State const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getState),
                                                                                             std::make_tuple());
  }
  Napi::Value getStateMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::State&>(info,
                                                                                  getPtr(),
                                                                                  static_cast<org::sem::SubtreeLogHead::State&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getState),
                                                                                  std::make_tuple());
  }
  Napi::Value isDeadline(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, bool>(info,
                                                           getPtr(),
                                                           static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isDeadline),
                                                           std::make_tuple());
  }
  Napi::Value getDeadlineConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Deadline const&>(info,
                                                                                                getPtr(),
                                                                                                static_cast<org::sem::SubtreeLogHead::Deadline const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getDeadline),
                                                                                                std::make_tuple());
  }
  Napi::Value getDeadlineMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Deadline&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<org::sem::SubtreeLogHead::Deadline&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getDeadline),
                                                                                     std::make_tuple());
  }
  Napi::Value isSchedule(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, bool>(info,
                                                           getPtr(),
                                                           static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isSchedule),
                                                           std::make_tuple());
  }
  Napi::Value getScheduleConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Schedule const&>(info,
                                                                                                getPtr(),
                                                                                                static_cast<org::sem::SubtreeLogHead::Schedule const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getSchedule),
                                                                                                std::make_tuple());
  }
  Napi::Value getScheduleMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Schedule&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<org::sem::SubtreeLogHead::Schedule&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getSchedule),
                                                                                     std::make_tuple());
  }
  Napi::Value isTag(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, bool>(info,
                                                           getPtr(),
                                                           static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isTag),
                                                           std::make_tuple());
  }
  Napi::Value getTagConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Tag const&>(info,
                                                                                           getPtr(),
                                                                                           static_cast<org::sem::SubtreeLogHead::Tag const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getTag),
                                                                                           std::make_tuple());
  }
  Napi::Value getTagMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Tag&>(info,
                                                                                getPtr(),
                                                                                static_cast<org::sem::SubtreeLogHead::Tag&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getTag),
                                                                                std::make_tuple());
  }
  Napi::Value isUnknown(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, bool>(info,
                                                           getPtr(),
                                                           static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isUnknown),
                                                           std::make_tuple());
  }
  Napi::Value getUnknownConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Unknown const&>(info,
                                                                                               getPtr(),
                                                                                               static_cast<org::sem::SubtreeLogHead::Unknown const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getUnknown),
                                                                                               std::make_tuple());
  }
  Napi::Value getUnknownMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Unknown&>(info,
                                                                                    getPtr(),
                                                                                    static_cast<org::sem::SubtreeLogHead::Unknown&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getUnknown),
                                                                                    std::make_tuple());
  }
  Napi::Value getLogKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Kind>(info,
                                                                                     getPtr(),
                                                                                     static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getLogKind),
                                                                                     std::make_tuple());
  }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, char const*>(info,
                                                                  getPtr(),
                                                                  static_cast<char const*(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::sub_variant_get_name),
                                                                  std::make_tuple());
  }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::LogEntry const&>(info,
                                                                                                getPtr(),
                                                                                                static_cast<org::sem::SubtreeLogHead::LogEntry const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::sub_variant_get_data),
                                                                                                std::make_tuple());
  }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLogHead, org::sem::SubtreeLogHead::Kind>(info,
                                                                                     getPtr(),
                                                                                     static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::sub_variant_get_kind),
                                                                                     std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreeLogHeadJs", {InstanceMethod("operator==", &SubtreeLogHeadJs::operator==),
                                                                InstanceMethod("isPriority", &SubtreeLogHeadJs::isPriority),
                                                                InstanceMethod("getPriorityConst", &SubtreeLogHeadJs::getPriorityConst),
                                                                InstanceMethod("getPriorityMut", &SubtreeLogHeadJs::getPriorityMut),
                                                                InstanceMethod("isNote", &SubtreeLogHeadJs::isNote),
                                                                InstanceMethod("getNoteConst", &SubtreeLogHeadJs::getNoteConst),
                                                                InstanceMethod("getNoteMut", &SubtreeLogHeadJs::getNoteMut),
                                                                InstanceMethod("isRefile", &SubtreeLogHeadJs::isRefile),
                                                                InstanceMethod("getRefileConst", &SubtreeLogHeadJs::getRefileConst),
                                                                InstanceMethod("getRefileMut", &SubtreeLogHeadJs::getRefileMut),
                                                                InstanceMethod("isClock", &SubtreeLogHeadJs::isClock),
                                                                InstanceMethod("getClockConst", &SubtreeLogHeadJs::getClockConst),
                                                                InstanceMethod("getClockMut", &SubtreeLogHeadJs::getClockMut),
                                                                InstanceMethod("isState", &SubtreeLogHeadJs::isState),
                                                                InstanceMethod("getStateConst", &SubtreeLogHeadJs::getStateConst),
                                                                InstanceMethod("getStateMut", &SubtreeLogHeadJs::getStateMut),
                                                                InstanceMethod("isDeadline", &SubtreeLogHeadJs::isDeadline),
                                                                InstanceMethod("getDeadlineConst", &SubtreeLogHeadJs::getDeadlineConst),
                                                                InstanceMethod("getDeadlineMut", &SubtreeLogHeadJs::getDeadlineMut),
                                                                InstanceMethod("isSchedule", &SubtreeLogHeadJs::isSchedule),
                                                                InstanceMethod("getScheduleConst", &SubtreeLogHeadJs::getScheduleConst),
                                                                InstanceMethod("getScheduleMut", &SubtreeLogHeadJs::getScheduleMut),
                                                                InstanceMethod("isTag", &SubtreeLogHeadJs::isTag),
                                                                InstanceMethod("getTagConst", &SubtreeLogHeadJs::getTagConst),
                                                                InstanceMethod("getTagMut", &SubtreeLogHeadJs::getTagMut),
                                                                InstanceMethod("isUnknown", &SubtreeLogHeadJs::isUnknown),
                                                                InstanceMethod("getUnknownConst", &SubtreeLogHeadJs::getUnknownConst),
                                                                InstanceMethod("getUnknownMut", &SubtreeLogHeadJs::getUnknownMut),
                                                                InstanceMethod("getLogKind", &SubtreeLogHeadJs::getLogKind),
                                                                InstanceMethod("sub_variant_get_name", &SubtreeLogHeadJs::sub_variant_get_name),
                                                                InstanceMethod("sub_variant_get_data", &SubtreeLogHeadJs::sub_variant_get_data),
                                                                InstanceMethod("sub_variant_get_kind", &SubtreeLogHeadJs::sub_variant_get_kind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SubtreeLogHeadJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::SubtreeLogHead> _stored;
  org::sem::SubtreeLogHead* getPtr() { return _stored.get(); }
};

struct SubtreeCompletionJs : public Napi::ObjectWrap<SubtreeCompletionJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeCompletion, bool>(info,
                                                              getPtr(),
                                                              static_cast<bool(org::sem::SubtreeCompletion::*)(org::sem::SubtreeCompletion const&) const>(&org::sem::SubtreeCompletion::operator==),
                                                              std::make_tuple(CxxArgSpec<org::sem::SubtreeCompletion>{"other"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreeCompletionJs", {InstanceMethod("operator==", &SubtreeCompletionJs::operator==)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SubtreeCompletionJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::SubtreeCompletion> _stored;
  org::sem::SubtreeCompletion* getPtr() { return _stored.get(); }
};

struct AttrListJs : public Napi::ObjectWrap<AttrListJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrList, bool>(info,
                                                     getPtr(),
                                                     static_cast<bool(org::sem::AttrList::*)(org::sem::AttrList const&) const>(&org::sem::AttrList::operator==),
                                                     std::make_tuple(CxxArgSpec<org::sem::AttrList>{"other"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AttrListJs", {InstanceMethod("operator==", &AttrListJs::operator==)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AttrListJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::AttrList> _stored;
  org::sem::AttrList* getPtr() { return _stored.get(); }
};

struct AttrGroupJs : public Napi::ObjectWrap<AttrGroupJs> {
  Napi::Value getFlatArgs(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, hstd::Vec<org::sem::AttrValue>>(info,
                                                                                getPtr(),
                                                                                static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getFlatArgs),
                                                                                std::make_tuple());
  }
  Napi::Value getAttrs(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, hstd::Vec<org::sem::AttrValue>>(info,
                                                                                getPtr(),
                                                                                static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::AttrGroup::getAttrs),
                                                                                std::make_tuple(CxxArgSpec<hstd::Opt<hstd::Str>>{"key", std::nullopt}));
  }
  Napi::Value setNamedAttr(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::AttrGroup, void>(info,
                                                 getPtr(),
                                                 static_cast<void(org::sem::AttrGroup::*)(hstd::Str const&, hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setNamedAttr),
                                                 std::make_tuple(CxxArgSpec<hstd::Str>{"key"},
                                                                 CxxArgSpec<hstd::Vec<org::sem::AttrValue>>{"attrs"}));
  }
  Napi::Value setPositionalAttr(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::AttrGroup, void>(info,
                                                 getPtr(),
                                                 static_cast<void(org::sem::AttrGroup::*)(hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setPositionalAttr),
                                                 std::make_tuple(CxxArgSpec<hstd::Vec<org::sem::AttrValue>>{"items"}));
  }
  Napi::Value getPositionalSize(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, int>(info,
                                                     getPtr(),
                                                     static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getPositionalSize),
                                                     std::make_tuple());
  }
  Napi::Value getNamedSize(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, int>(info,
                                                     getPtr(),
                                                     static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getNamedSize),
                                                     std::make_tuple());
  }
  Napi::Value isEmpty(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, bool>(info,
                                                      getPtr(),
                                                      static_cast<bool(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::isEmpty),
                                                      std::make_tuple());
  }
  Napi::Value getAll(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, org::sem::AttrList>(info,
                                                                    getPtr(),
                                                                    static_cast<org::sem::AttrList(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getAll),
                                                                    std::make_tuple());
  }
  Napi::Value atPositional(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, org::sem::AttrValue const&>(info,
                                                                            getPtr(),
                                                                            static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::atPositional),
                                                                            std::make_tuple(CxxArgSpec<int>{"index"}));
  }
  Napi::Value getPositional(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, hstd::Opt<org::sem::AttrValue>>(info,
                                                                                getPtr(),
                                                                                static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::getPositional),
                                                                                std::make_tuple(CxxArgSpec<int>{"index"}));
  }
  Napi::Value atNamed(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, org::sem::AttrList const&>(info,
                                                                           getPtr(),
                                                                           static_cast<org::sem::AttrList const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atNamed),
                                                                           std::make_tuple(CxxArgSpec<hstd::Str>{"index"}));
  }
  Napi::Value getNamed(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, hstd::Opt<org::sem::AttrList>>(info,
                                                                               getPtr(),
                                                                               static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getNamed),
                                                                               std::make_tuple(CxxArgSpec<hstd::Str>{"index"}));
  }
  Napi::Value atFirstNamed(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, org::sem::AttrValue const&>(info,
                                                                            getPtr(),
                                                                            static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstNamed),
                                                                            std::make_tuple(CxxArgSpec<hstd::Str>{"index"}));
  }
  Napi::Value getFirstNamed(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, hstd::Opt<org::sem::AttrValue>>(info,
                                                                                getPtr(),
                                                                                static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstNamed),
                                                                                std::make_tuple(CxxArgSpec<hstd::Str>{"index"}));
  }
  Napi::Value atVarNamed(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, org::sem::AttrList>(info,
                                                                    getPtr(),
                                                                    static_cast<org::sem::AttrList(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atVarNamed),
                                                                    std::make_tuple(CxxArgSpec<hstd::Str>{"index"}));
  }
  Napi::Value getVarNamed(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, hstd::Opt<org::sem::AttrList>>(info,
                                                                               getPtr(),
                                                                               static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getVarNamed),
                                                                               std::make_tuple(CxxArgSpec<hstd::Str>{"index"}));
  }
  Napi::Value atFirstVarNamed(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, org::sem::AttrValue>(info,
                                                                     getPtr(),
                                                                     static_cast<org::sem::AttrValue(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstVarNamed),
                                                                     std::make_tuple(CxxArgSpec<hstd::Str>{"index"}));
  }
  Napi::Value getFirstVarNamed(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, hstd::Opt<org::sem::AttrValue>>(info,
                                                                                getPtr(),
                                                                                static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstVarNamed),
                                                                                std::make_tuple(CxxArgSpec<hstd::Str>{"index"}));
  }
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AttrGroup, bool>(info,
                                                      getPtr(),
                                                      static_cast<bool(org::sem::AttrGroup::*)(org::sem::AttrGroup const&) const>(&org::sem::AttrGroup::operator==),
                                                      std::make_tuple(CxxArgSpec<org::sem::AttrGroup>{"other"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AttrGroupJs", {InstanceMethod("getFlatArgs", &AttrGroupJs::getFlatArgs),
                                                           InstanceMethod("getAttrs", &AttrGroupJs::getAttrs),
                                                           InstanceMethod("setNamedAttr", &AttrGroupJs::setNamedAttr),
                                                           InstanceMethod("setPositionalAttr", &AttrGroupJs::setPositionalAttr),
                                                           InstanceMethod("getPositionalSize", &AttrGroupJs::getPositionalSize),
                                                           InstanceMethod("getNamedSize", &AttrGroupJs::getNamedSize),
                                                           InstanceMethod("isEmpty", &AttrGroupJs::isEmpty),
                                                           InstanceMethod("getAll", &AttrGroupJs::getAll),
                                                           InstanceMethod("atPositional", &AttrGroupJs::atPositional),
                                                           InstanceMethod("getPositional", &AttrGroupJs::getPositional),
                                                           InstanceMethod("atNamed", &AttrGroupJs::atNamed),
                                                           InstanceMethod("getNamed", &AttrGroupJs::getNamed),
                                                           InstanceMethod("atFirstNamed", &AttrGroupJs::atFirstNamed),
                                                           InstanceMethod("getFirstNamed", &AttrGroupJs::getFirstNamed),
                                                           InstanceMethod("atVarNamed", &AttrGroupJs::atVarNamed),
                                                           InstanceMethod("getVarNamed", &AttrGroupJs::getVarNamed),
                                                           InstanceMethod("atFirstVarNamed", &AttrGroupJs::atFirstVarNamed),
                                                           InstanceMethod("getFirstVarNamed", &AttrGroupJs::getFirstVarNamed),
                                                           InstanceMethod("operator==", &AttrGroupJs::operator==)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AttrGroupJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::AttrGroup> _stored;
  org::sem::AttrGroup* getPtr() { return _stored.get(); }
};

struct OrgCodeEvalInputJs : public Napi::ObjectWrap<OrgCodeEvalInputJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::OrgCodeEvalInput, bool>(info,
                                                             getPtr(),
                                                             static_cast<bool(org::sem::OrgCodeEvalInput::*)(org::sem::OrgCodeEvalInput const&) const>(&org::sem::OrgCodeEvalInput::operator==),
                                                             std::make_tuple(CxxArgSpec<org::sem::OrgCodeEvalInput>{"other"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgCodeEvalInputJs", {InstanceMethod("operator==", &OrgCodeEvalInputJs::operator==)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OrgCodeEvalInputJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::OrgCodeEvalInput> _stored;
  org::sem::OrgCodeEvalInput* getPtr() { return _stored.get(); }
};

struct OrgCodeEvalOutputJs : public Napi::ObjectWrap<OrgCodeEvalOutputJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::OrgCodeEvalOutput, bool>(info,
                                                              getPtr(),
                                                              static_cast<bool(org::sem::OrgCodeEvalOutput::*)(org::sem::OrgCodeEvalOutput const&) const>(&org::sem::OrgCodeEvalOutput::operator==),
                                                              std::make_tuple(CxxArgSpec<org::sem::OrgCodeEvalOutput>{"other"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "OrgCodeEvalOutputJs", {InstanceMethod("operator==", &OrgCodeEvalOutputJs::operator==)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("OrgCodeEvalOutputJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::OrgCodeEvalOutput> _stored;
  org::sem::OrgCodeEvalOutput* getPtr() { return _stored.get(); }
};

struct ColumnViewJs : public Napi::ObjectWrap<ColumnViewJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::ColumnView, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::ColumnView::*)(org::sem::ColumnView const&) const>(&org::sem::ColumnView::operator==),
                                                       std::make_tuple(CxxArgSpec<org::sem::ColumnView>{"other"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ColumnViewJs", {InstanceMethod("operator==", &ColumnViewJs::operator==)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ColumnViewJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::ColumnView> _stored;
  org::sem::ColumnView* getPtr() { return _stored.get(); }
};

struct BlockCodeLineJs : public Napi::ObjectWrap<BlockCodeLineJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockCodeLine, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::BlockCodeLine::*)(org::sem::BlockCodeLine const&) const>(&org::sem::BlockCodeLine::operator==),
                                                          std::make_tuple(CxxArgSpec<org::sem::BlockCodeLine>{"other"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCodeLineJs", {InstanceMethod("operator==", &BlockCodeLineJs::operator==)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockCodeLineJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::BlockCodeLine> _stored;
  org::sem::BlockCodeLine* getPtr() { return _stored.get(); }
};

struct DocumentExportConfigJs : public Napi::ObjectWrap<DocumentExportConfigJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentExportConfig, bool>(info,
                                                                 getPtr(),
                                                                 static_cast<bool(org::sem::DocumentExportConfig::*)(org::sem::DocumentExportConfig const&) const>(&org::sem::DocumentExportConfig::operator==),
                                                                 std::make_tuple(CxxArgSpec<org::sem::DocumentExportConfig>{"other"}));
  }
  Napi::Value isDoExport(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentExportConfig, bool>(info,
                                                                 getPtr(),
                                                                 static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isDoExport),
                                                                 std::make_tuple());
  }
  Napi::Value getDoExportConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentExportConfig, org::sem::DocumentExportConfig::DoExport const&>(info,
                                                                                                            getPtr(),
                                                                                                            static_cast<org::sem::DocumentExportConfig::DoExport const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getDoExport),
                                                                                                            std::make_tuple());
  }
  Napi::Value getDoExportMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::DocumentExportConfig, org::sem::DocumentExportConfig::DoExport&>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::sem::DocumentExportConfig::DoExport&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getDoExport),
                                                                                                 std::make_tuple());
  }
  Napi::Value isExportFixed(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentExportConfig, bool>(info,
                                                                 getPtr(),
                                                                 static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isExportFixed),
                                                                 std::make_tuple());
  }
  Napi::Value getExportFixedConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentExportConfig, org::sem::DocumentExportConfig::ExportFixed const&>(info,
                                                                                                               getPtr(),
                                                                                                               static_cast<org::sem::DocumentExportConfig::ExportFixed const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getExportFixed),
                                                                                                               std::make_tuple());
  }
  Napi::Value getExportFixedMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::DocumentExportConfig, org::sem::DocumentExportConfig::ExportFixed&>(info,
                                                                                                    getPtr(),
                                                                                                    static_cast<org::sem::DocumentExportConfig::ExportFixed&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getExportFixed),
                                                                                                    std::make_tuple());
  }
  Napi::Value getTocExportKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentExportConfig, org::sem::DocumentExportConfig::TocExportKind>(info,
                                                                                                          getPtr(),
                                                                                                          static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getTocExportKind),
                                                                                                          std::make_tuple());
  }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentExportConfig, char const*>(info,
                                                                        getPtr(),
                                                                        static_cast<char const*(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::sub_variant_get_name),
                                                                        std::make_tuple());
  }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentExportConfig, org::sem::DocumentExportConfig::TocExport const&>(info,
                                                                                                             getPtr(),
                                                                                                             static_cast<org::sem::DocumentExportConfig::TocExport const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::sub_variant_get_data),
                                                                                                             std::make_tuple());
  }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentExportConfig, org::sem::DocumentExportConfig::TocExportKind>(info,
                                                                                                          getPtr(),
                                                                                                          static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::sub_variant_get_kind),
                                                                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentExportConfigJs", {InstanceMethod("operator==", &DocumentExportConfigJs::operator==),
                                                                      InstanceMethod("isDoExport", &DocumentExportConfigJs::isDoExport),
                                                                      InstanceMethod("getDoExportConst", &DocumentExportConfigJs::getDoExportConst),
                                                                      InstanceMethod("getDoExportMut", &DocumentExportConfigJs::getDoExportMut),
                                                                      InstanceMethod("isExportFixed", &DocumentExportConfigJs::isExportFixed),
                                                                      InstanceMethod("getExportFixedConst", &DocumentExportConfigJs::getExportFixedConst),
                                                                      InstanceMethod("getExportFixedMut", &DocumentExportConfigJs::getExportFixedMut),
                                                                      InstanceMethod("getTocExportKind", &DocumentExportConfigJs::getTocExportKind),
                                                                      InstanceMethod("sub_variant_get_name", &DocumentExportConfigJs::sub_variant_get_name),
                                                                      InstanceMethod("sub_variant_get_data", &DocumentExportConfigJs::sub_variant_get_data),
                                                                      InstanceMethod("sub_variant_get_kind", &DocumentExportConfigJs::sub_variant_get_kind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("DocumentExportConfigJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::DocumentExportConfig> _stored;
  org::sem::DocumentExportConfig* getPtr() { return _stored.get(); }
};

struct SubtreePeriodJs : public Napi::ObjectWrap<SubtreePeriodJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreePeriod, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::SubtreePeriod::*)(org::sem::SubtreePeriod const&) const>(&org::sem::SubtreePeriod::operator==),
                                                          std::make_tuple(CxxArgSpec<org::sem::SubtreePeriod>{"other"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreePeriodJs", {InstanceMethod("operator==", &SubtreePeriodJs::operator==)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SubtreePeriodJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::SubtreePeriod> _stored;
  org::sem::SubtreePeriod* getPtr() { return _stored.get(); }
};

struct NamedPropertyJs : public Napi::ObjectWrap<NamedPropertyJs> {
  Napi::Value isMatching(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::NamedProperty::isMatching),
                                                          std::make_tuple(CxxArgSpec<hstd::Str>{"kind"},
                                                                          CxxArgSpec<hstd::Opt<hstd::Str>>{"subKind", std::nullopt}));
  }
  Napi::Value getName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, hstd::Str>(info,
                                                               getPtr(),
                                                               static_cast<hstd::Str(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getName),
                                                               std::make_tuple());
  }
  Napi::Value getSubKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, hstd::Opt<hstd::Str>>(info,
                                                                          getPtr(),
                                                                          static_cast<hstd::Opt<hstd::Str>(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getSubKind),
                                                                          std::make_tuple());
  }
  Napi::Value operator==(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)(org::sem::NamedProperty const&) const>(&org::sem::NamedProperty::operator==),
                                                          std::make_tuple(CxxArgSpec<org::sem::NamedProperty>{"other"}));
  }
  Napi::Value isNonblocking(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isNonblocking),
                                                          std::make_tuple());
  }
  Napi::Value getNonblockingConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::Nonblocking const&>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::sem::NamedProperty::Nonblocking const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getNonblocking),
                                                                                                 std::make_tuple());
  }
  Napi::Value getNonblockingMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::Nonblocking&>(info,
                                                                                      getPtr(),
                                                                                      static_cast<org::sem::NamedProperty::Nonblocking&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getNonblocking),
                                                                                      std::make_tuple());
  }
  Napi::Value isArchiveTime(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTime),
                                                          std::make_tuple());
  }
  Napi::Value getArchiveTimeConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::ArchiveTime const&>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::sem::NamedProperty::ArchiveTime const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTime),
                                                                                                 std::make_tuple());
  }
  Napi::Value getArchiveTimeMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::ArchiveTime&>(info,
                                                                                      getPtr(),
                                                                                      static_cast<org::sem::NamedProperty::ArchiveTime&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTime),
                                                                                      std::make_tuple());
  }
  Napi::Value isArchiveFile(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveFile),
                                                          std::make_tuple());
  }
  Napi::Value getArchiveFileConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::ArchiveFile const&>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::sem::NamedProperty::ArchiveFile const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveFile),
                                                                                                 std::make_tuple());
  }
  Napi::Value getArchiveFileMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::ArchiveFile&>(info,
                                                                                      getPtr(),
                                                                                      static_cast<org::sem::NamedProperty::ArchiveFile&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveFile),
                                                                                      std::make_tuple());
  }
  Napi::Value isArchiveOlpath(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveOlpath),
                                                          std::make_tuple());
  }
  Napi::Value getArchiveOlpathConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::ArchiveOlpath const&>(info,
                                                                                                   getPtr(),
                                                                                                   static_cast<org::sem::NamedProperty::ArchiveOlpath const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveOlpath),
                                                                                                   std::make_tuple());
  }
  Napi::Value getArchiveOlpathMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::ArchiveOlpath&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<org::sem::NamedProperty::ArchiveOlpath&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveOlpath),
                                                                                        std::make_tuple());
  }
  Napi::Value isArchiveTarget(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTarget),
                                                          std::make_tuple());
  }
  Napi::Value getArchiveTargetConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::ArchiveTarget const&>(info,
                                                                                                   getPtr(),
                                                                                                   static_cast<org::sem::NamedProperty::ArchiveTarget const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTarget),
                                                                                                   std::make_tuple());
  }
  Napi::Value getArchiveTargetMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::ArchiveTarget&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<org::sem::NamedProperty::ArchiveTarget&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTarget),
                                                                                        std::make_tuple());
  }
  Napi::Value isArchiveCategory(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveCategory),
                                                          std::make_tuple());
  }
  Napi::Value getArchiveCategoryConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::ArchiveCategory const&>(info,
                                                                                                     getPtr(),
                                                                                                     static_cast<org::sem::NamedProperty::ArchiveCategory const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveCategory),
                                                                                                     std::make_tuple());
  }
  Napi::Value getArchiveCategoryMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::ArchiveCategory&>(info,
                                                                                          getPtr(),
                                                                                          static_cast<org::sem::NamedProperty::ArchiveCategory&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveCategory),
                                                                                          std::make_tuple());
  }
  Napi::Value isArchiveTodo(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTodo),
                                                          std::make_tuple());
  }
  Napi::Value getArchiveTodoConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::ArchiveTodo const&>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::sem::NamedProperty::ArchiveTodo const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTodo),
                                                                                                 std::make_tuple());
  }
  Napi::Value getArchiveTodoMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::ArchiveTodo&>(info,
                                                                                      getPtr(),
                                                                                      static_cast<org::sem::NamedProperty::ArchiveTodo&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTodo),
                                                                                      std::make_tuple());
  }
  Napi::Value isTrigger(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isTrigger),
                                                          std::make_tuple());
  }
  Napi::Value getTriggerConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::Trigger const&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<org::sem::NamedProperty::Trigger const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getTrigger),
                                                                                             std::make_tuple());
  }
  Napi::Value getTriggerMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::Trigger&>(info,
                                                                                  getPtr(),
                                                                                  static_cast<org::sem::NamedProperty::Trigger&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getTrigger),
                                                                                  std::make_tuple());
  }
  Napi::Value isExportLatexClass(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClass),
                                                          std::make_tuple());
  }
  Napi::Value getExportLatexClassConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::ExportLatexClass const&>(info,
                                                                                                      getPtr(),
                                                                                                      static_cast<org::sem::NamedProperty::ExportLatexClass const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexClass),
                                                                                                      std::make_tuple());
  }
  Napi::Value getExportLatexClassMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::ExportLatexClass&>(info,
                                                                                           getPtr(),
                                                                                           static_cast<org::sem::NamedProperty::ExportLatexClass&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClass),
                                                                                           std::make_tuple());
  }
  Napi::Value isCookieData(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCookieData),
                                                          std::make_tuple());
  }
  Napi::Value getCookieDataConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::CookieData const&>(info,
                                                                                                getPtr(),
                                                                                                static_cast<org::sem::NamedProperty::CookieData const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCookieData),
                                                                                                std::make_tuple());
  }
  Napi::Value getCookieDataMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::CookieData&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<org::sem::NamedProperty::CookieData&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCookieData),
                                                                                     std::make_tuple());
  }
  Napi::Value isExportLatexClassOptions(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClassOptions),
                                                          std::make_tuple());
  }
  Napi::Value getExportLatexClassOptionsConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::ExportLatexClassOptions const&>(info,
                                                                                                             getPtr(),
                                                                                                             static_cast<org::sem::NamedProperty::ExportLatexClassOptions const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexClassOptions),
                                                                                                             std::make_tuple());
  }
  Napi::Value getExportLatexClassOptionsMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::ExportLatexClassOptions&>(info,
                                                                                                  getPtr(),
                                                                                                  static_cast<org::sem::NamedProperty::ExportLatexClassOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClassOptions),
                                                                                                  std::make_tuple());
  }
  Napi::Value isExportLatexHeader(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexHeader),
                                                          std::make_tuple());
  }
  Napi::Value getExportLatexHeaderConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::ExportLatexHeader const&>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<org::sem::NamedProperty::ExportLatexHeader const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexHeader),
                                                                                                       std::make_tuple());
  }
  Napi::Value getExportLatexHeaderMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::ExportLatexHeader&>(info,
                                                                                            getPtr(),
                                                                                            static_cast<org::sem::NamedProperty::ExportLatexHeader&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexHeader),
                                                                                            std::make_tuple());
  }
  Napi::Value isExportLatexCompiler(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexCompiler),
                                                          std::make_tuple());
  }
  Napi::Value getExportLatexCompilerConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::ExportLatexCompiler const&>(info,
                                                                                                         getPtr(),
                                                                                                         static_cast<org::sem::NamedProperty::ExportLatexCompiler const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexCompiler),
                                                                                                         std::make_tuple());
  }
  Napi::Value getExportLatexCompilerMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::ExportLatexCompiler&>(info,
                                                                                              getPtr(),
                                                                                              static_cast<org::sem::NamedProperty::ExportLatexCompiler&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexCompiler),
                                                                                              std::make_tuple());
  }
  Napi::Value isOrdered(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isOrdered),
                                                          std::make_tuple());
  }
  Napi::Value getOrderedConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::Ordered const&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<org::sem::NamedProperty::Ordered const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getOrdered),
                                                                                             std::make_tuple());
  }
  Napi::Value getOrderedMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::Ordered&>(info,
                                                                                  getPtr(),
                                                                                  static_cast<org::sem::NamedProperty::Ordered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getOrdered),
                                                                                  std::make_tuple());
  }
  Napi::Value isEffort(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isEffort),
                                                          std::make_tuple());
  }
  Napi::Value getEffortConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::Effort const&>(info,
                                                                                            getPtr(),
                                                                                            static_cast<org::sem::NamedProperty::Effort const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getEffort),
                                                                                            std::make_tuple());
  }
  Napi::Value getEffortMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::Effort&>(info,
                                                                                 getPtr(),
                                                                                 static_cast<org::sem::NamedProperty::Effort&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getEffort),
                                                                                 std::make_tuple());
  }
  Napi::Value isVisibility(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isVisibility),
                                                          std::make_tuple());
  }
  Napi::Value getVisibilityConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::Visibility const&>(info,
                                                                                                getPtr(),
                                                                                                static_cast<org::sem::NamedProperty::Visibility const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getVisibility),
                                                                                                std::make_tuple());
  }
  Napi::Value getVisibilityMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::Visibility&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<org::sem::NamedProperty::Visibility&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getVisibility),
                                                                                     std::make_tuple());
  }
  Napi::Value isExportOptions(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportOptions),
                                                          std::make_tuple());
  }
  Napi::Value getExportOptionsConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::ExportOptions const&>(info,
                                                                                                   getPtr(),
                                                                                                   static_cast<org::sem::NamedProperty::ExportOptions const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportOptions),
                                                                                                   std::make_tuple());
  }
  Napi::Value getExportOptionsMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::ExportOptions&>(info,
                                                                                        getPtr(),
                                                                                        static_cast<org::sem::NamedProperty::ExportOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportOptions),
                                                                                        std::make_tuple());
  }
  Napi::Value isBlocker(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isBlocker),
                                                          std::make_tuple());
  }
  Napi::Value getBlockerConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::Blocker const&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<org::sem::NamedProperty::Blocker const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getBlocker),
                                                                                             std::make_tuple());
  }
  Napi::Value getBlockerMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::Blocker&>(info,
                                                                                  getPtr(),
                                                                                  static_cast<org::sem::NamedProperty::Blocker&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getBlocker),
                                                                                  std::make_tuple());
  }
  Napi::Value isUnnumbered(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isUnnumbered),
                                                          std::make_tuple());
  }
  Napi::Value getUnnumberedConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::Unnumbered const&>(info,
                                                                                                getPtr(),
                                                                                                static_cast<org::sem::NamedProperty::Unnumbered const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getUnnumbered),
                                                                                                std::make_tuple());
  }
  Napi::Value getUnnumberedMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::Unnumbered&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<org::sem::NamedProperty::Unnumbered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getUnnumbered),
                                                                                     std::make_tuple());
  }
  Napi::Value isCreated(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCreated),
                                                          std::make_tuple());
  }
  Napi::Value getCreatedConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::Created const&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<org::sem::NamedProperty::Created const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCreated),
                                                                                             std::make_tuple());
  }
  Napi::Value getCreatedMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::Created&>(info,
                                                                                  getPtr(),
                                                                                  static_cast<org::sem::NamedProperty::Created&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCreated),
                                                                                  std::make_tuple());
  }
  Napi::Value isRadioId(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isRadioId),
                                                          std::make_tuple());
  }
  Napi::Value getRadioIdConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::RadioId const&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<org::sem::NamedProperty::RadioId const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getRadioId),
                                                                                             std::make_tuple());
  }
  Napi::Value getRadioIdMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::RadioId&>(info,
                                                                                  getPtr(),
                                                                                  static_cast<org::sem::NamedProperty::RadioId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getRadioId),
                                                                                  std::make_tuple());
  }
  Napi::Value isHashtagDef(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isHashtagDef),
                                                          std::make_tuple());
  }
  Napi::Value getHashtagDefConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::HashtagDef const&>(info,
                                                                                                getPtr(),
                                                                                                static_cast<org::sem::NamedProperty::HashtagDef const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getHashtagDef),
                                                                                                std::make_tuple());
  }
  Napi::Value getHashtagDefMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::HashtagDef&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<org::sem::NamedProperty::HashtagDef&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getHashtagDef),
                                                                                     std::make_tuple());
  }
  Napi::Value isCustomArgs(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomArgs),
                                                          std::make_tuple());
  }
  Napi::Value getCustomArgsConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::CustomArgs const&>(info,
                                                                                                getPtr(),
                                                                                                static_cast<org::sem::NamedProperty::CustomArgs const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomArgs),
                                                                                                std::make_tuple());
  }
  Napi::Value getCustomArgsMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::CustomArgs&>(info,
                                                                                     getPtr(),
                                                                                     static_cast<org::sem::NamedProperty::CustomArgs&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomArgs),
                                                                                     std::make_tuple());
  }
  Napi::Value isCustomRaw(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomRaw),
                                                          std::make_tuple());
  }
  Napi::Value getCustomRawConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::CustomRaw const&>(info,
                                                                                               getPtr(),
                                                                                               static_cast<org::sem::NamedProperty::CustomRaw const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomRaw),
                                                                                               std::make_tuple());
  }
  Napi::Value getCustomRawMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::CustomRaw&>(info,
                                                                                    getPtr(),
                                                                                    static_cast<org::sem::NamedProperty::CustomRaw&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomRaw),
                                                                                    std::make_tuple());
  }
  Napi::Value isCustomSubtreeJson(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeJson),
                                                          std::make_tuple());
  }
  Napi::Value getCustomSubtreeJsonConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::CustomSubtreeJson const&>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<org::sem::NamedProperty::CustomSubtreeJson const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomSubtreeJson),
                                                                                                       std::make_tuple());
  }
  Napi::Value getCustomSubtreeJsonMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::CustomSubtreeJson&>(info,
                                                                                            getPtr(),
                                                                                            static_cast<org::sem::NamedProperty::CustomSubtreeJson&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeJson),
                                                                                            std::make_tuple());
  }
  Napi::Value isCustomSubtreeFlags(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, bool>(info,
                                                          getPtr(),
                                                          static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeFlags),
                                                          std::make_tuple());
  }
  Napi::Value getCustomSubtreeFlagsConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::CustomSubtreeFlags const&>(info,
                                                                                                        getPtr(),
                                                                                                        static_cast<org::sem::NamedProperty::CustomSubtreeFlags const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomSubtreeFlags),
                                                                                                        std::make_tuple());
  }
  Napi::Value getCustomSubtreeFlagsMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::NamedProperty, org::sem::NamedProperty::CustomSubtreeFlags&>(info,
                                                                                             getPtr(),
                                                                                             static_cast<org::sem::NamedProperty::CustomSubtreeFlags&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeFlags),
                                                                                             std::make_tuple());
  }
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::Kind>(info,
                                                                                   getPtr(),
                                                                                   static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getKind),
                                                                                   std::make_tuple());
  }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, char const*>(info,
                                                                 getPtr(),
                                                                 static_cast<char const*(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::sub_variant_get_name),
                                                                 std::make_tuple());
  }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::Data const&>(info,
                                                                                          getPtr(),
                                                                                          static_cast<org::sem::NamedProperty::Data const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::sub_variant_get_data),
                                                                                          std::make_tuple());
  }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::NamedProperty, org::sem::NamedProperty::Kind>(info,
                                                                                   getPtr(),
                                                                                   static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::sub_variant_get_kind),
                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "NamedPropertyJs", {InstanceMethod("isMatching", &NamedPropertyJs::isMatching),
                                                               InstanceMethod("getName", &NamedPropertyJs::getName),
                                                               InstanceMethod("getSubKind", &NamedPropertyJs::getSubKind),
                                                               InstanceMethod("operator==", &NamedPropertyJs::operator==),
                                                               InstanceMethod("isNonblocking", &NamedPropertyJs::isNonblocking),
                                                               InstanceMethod("getNonblockingConst", &NamedPropertyJs::getNonblockingConst),
                                                               InstanceMethod("getNonblockingMut", &NamedPropertyJs::getNonblockingMut),
                                                               InstanceMethod("isArchiveTime", &NamedPropertyJs::isArchiveTime),
                                                               InstanceMethod("getArchiveTimeConst", &NamedPropertyJs::getArchiveTimeConst),
                                                               InstanceMethod("getArchiveTimeMut", &NamedPropertyJs::getArchiveTimeMut),
                                                               InstanceMethod("isArchiveFile", &NamedPropertyJs::isArchiveFile),
                                                               InstanceMethod("getArchiveFileConst", &NamedPropertyJs::getArchiveFileConst),
                                                               InstanceMethod("getArchiveFileMut", &NamedPropertyJs::getArchiveFileMut),
                                                               InstanceMethod("isArchiveOlpath", &NamedPropertyJs::isArchiveOlpath),
                                                               InstanceMethod("getArchiveOlpathConst", &NamedPropertyJs::getArchiveOlpathConst),
                                                               InstanceMethod("getArchiveOlpathMut", &NamedPropertyJs::getArchiveOlpathMut),
                                                               InstanceMethod("isArchiveTarget", &NamedPropertyJs::isArchiveTarget),
                                                               InstanceMethod("getArchiveTargetConst", &NamedPropertyJs::getArchiveTargetConst),
                                                               InstanceMethod("getArchiveTargetMut", &NamedPropertyJs::getArchiveTargetMut),
                                                               InstanceMethod("isArchiveCategory", &NamedPropertyJs::isArchiveCategory),
                                                               InstanceMethod("getArchiveCategoryConst", &NamedPropertyJs::getArchiveCategoryConst),
                                                               InstanceMethod("getArchiveCategoryMut", &NamedPropertyJs::getArchiveCategoryMut),
                                                               InstanceMethod("isArchiveTodo", &NamedPropertyJs::isArchiveTodo),
                                                               InstanceMethod("getArchiveTodoConst", &NamedPropertyJs::getArchiveTodoConst),
                                                               InstanceMethod("getArchiveTodoMut", &NamedPropertyJs::getArchiveTodoMut),
                                                               InstanceMethod("isTrigger", &NamedPropertyJs::isTrigger),
                                                               InstanceMethod("getTriggerConst", &NamedPropertyJs::getTriggerConst),
                                                               InstanceMethod("getTriggerMut", &NamedPropertyJs::getTriggerMut),
                                                               InstanceMethod("isExportLatexClass", &NamedPropertyJs::isExportLatexClass),
                                                               InstanceMethod("getExportLatexClassConst", &NamedPropertyJs::getExportLatexClassConst),
                                                               InstanceMethod("getExportLatexClassMut", &NamedPropertyJs::getExportLatexClassMut),
                                                               InstanceMethod("isCookieData", &NamedPropertyJs::isCookieData),
                                                               InstanceMethod("getCookieDataConst", &NamedPropertyJs::getCookieDataConst),
                                                               InstanceMethod("getCookieDataMut", &NamedPropertyJs::getCookieDataMut),
                                                               InstanceMethod("isExportLatexClassOptions", &NamedPropertyJs::isExportLatexClassOptions),
                                                               InstanceMethod("getExportLatexClassOptionsConst", &NamedPropertyJs::getExportLatexClassOptionsConst),
                                                               InstanceMethod("getExportLatexClassOptionsMut", &NamedPropertyJs::getExportLatexClassOptionsMut),
                                                               InstanceMethod("isExportLatexHeader", &NamedPropertyJs::isExportLatexHeader),
                                                               InstanceMethod("getExportLatexHeaderConst", &NamedPropertyJs::getExportLatexHeaderConst),
                                                               InstanceMethod("getExportLatexHeaderMut", &NamedPropertyJs::getExportLatexHeaderMut),
                                                               InstanceMethod("isExportLatexCompiler", &NamedPropertyJs::isExportLatexCompiler),
                                                               InstanceMethod("getExportLatexCompilerConst", &NamedPropertyJs::getExportLatexCompilerConst),
                                                               InstanceMethod("getExportLatexCompilerMut", &NamedPropertyJs::getExportLatexCompilerMut),
                                                               InstanceMethod("isOrdered", &NamedPropertyJs::isOrdered),
                                                               InstanceMethod("getOrderedConst", &NamedPropertyJs::getOrderedConst),
                                                               InstanceMethod("getOrderedMut", &NamedPropertyJs::getOrderedMut),
                                                               InstanceMethod("isEffort", &NamedPropertyJs::isEffort),
                                                               InstanceMethod("getEffortConst", &NamedPropertyJs::getEffortConst),
                                                               InstanceMethod("getEffortMut", &NamedPropertyJs::getEffortMut),
                                                               InstanceMethod("isVisibility", &NamedPropertyJs::isVisibility),
                                                               InstanceMethod("getVisibilityConst", &NamedPropertyJs::getVisibilityConst),
                                                               InstanceMethod("getVisibilityMut", &NamedPropertyJs::getVisibilityMut),
                                                               InstanceMethod("isExportOptions", &NamedPropertyJs::isExportOptions),
                                                               InstanceMethod("getExportOptionsConst", &NamedPropertyJs::getExportOptionsConst),
                                                               InstanceMethod("getExportOptionsMut", &NamedPropertyJs::getExportOptionsMut),
                                                               InstanceMethod("isBlocker", &NamedPropertyJs::isBlocker),
                                                               InstanceMethod("getBlockerConst", &NamedPropertyJs::getBlockerConst),
                                                               InstanceMethod("getBlockerMut", &NamedPropertyJs::getBlockerMut),
                                                               InstanceMethod("isUnnumbered", &NamedPropertyJs::isUnnumbered),
                                                               InstanceMethod("getUnnumberedConst", &NamedPropertyJs::getUnnumberedConst),
                                                               InstanceMethod("getUnnumberedMut", &NamedPropertyJs::getUnnumberedMut),
                                                               InstanceMethod("isCreated", &NamedPropertyJs::isCreated),
                                                               InstanceMethod("getCreatedConst", &NamedPropertyJs::getCreatedConst),
                                                               InstanceMethod("getCreatedMut", &NamedPropertyJs::getCreatedMut),
                                                               InstanceMethod("isRadioId", &NamedPropertyJs::isRadioId),
                                                               InstanceMethod("getRadioIdConst", &NamedPropertyJs::getRadioIdConst),
                                                               InstanceMethod("getRadioIdMut", &NamedPropertyJs::getRadioIdMut),
                                                               InstanceMethod("isHashtagDef", &NamedPropertyJs::isHashtagDef),
                                                               InstanceMethod("getHashtagDefConst", &NamedPropertyJs::getHashtagDefConst),
                                                               InstanceMethod("getHashtagDefMut", &NamedPropertyJs::getHashtagDefMut),
                                                               InstanceMethod("isCustomArgs", &NamedPropertyJs::isCustomArgs),
                                                               InstanceMethod("getCustomArgsConst", &NamedPropertyJs::getCustomArgsConst),
                                                               InstanceMethod("getCustomArgsMut", &NamedPropertyJs::getCustomArgsMut),
                                                               InstanceMethod("isCustomRaw", &NamedPropertyJs::isCustomRaw),
                                                               InstanceMethod("getCustomRawConst", &NamedPropertyJs::getCustomRawConst),
                                                               InstanceMethod("getCustomRawMut", &NamedPropertyJs::getCustomRawMut),
                                                               InstanceMethod("isCustomSubtreeJson", &NamedPropertyJs::isCustomSubtreeJson),
                                                               InstanceMethod("getCustomSubtreeJsonConst", &NamedPropertyJs::getCustomSubtreeJsonConst),
                                                               InstanceMethod("getCustomSubtreeJsonMut", &NamedPropertyJs::getCustomSubtreeJsonMut),
                                                               InstanceMethod("isCustomSubtreeFlags", &NamedPropertyJs::isCustomSubtreeFlags),
                                                               InstanceMethod("getCustomSubtreeFlagsConst", &NamedPropertyJs::getCustomSubtreeFlagsConst),
                                                               InstanceMethod("getCustomSubtreeFlagsMut", &NamedPropertyJs::getCustomSubtreeFlagsMut),
                                                               InstanceMethod("getKind", &NamedPropertyJs::getKind),
                                                               InstanceMethod("sub_variant_get_name", &NamedPropertyJs::sub_variant_get_name),
                                                               InstanceMethod("sub_variant_get_data", &NamedPropertyJs::sub_variant_get_data),
                                                               InstanceMethod("sub_variant_get_kind", &NamedPropertyJs::sub_variant_get_kind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("NamedPropertyJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::NamedProperty> _stored;
  org::sem::NamedProperty* getPtr() { return _stored.get(); }
};

struct NoneJs : public Napi::ObjectWrap<NoneJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::None, OrgSemKind>(info,
                                                       getPtr(),
                                                       static_cast<OrgSemKind(org::sem::None::*)() const>(&org::sem::None::getKind),
                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "NoneJs", {InstanceMethod("getKind", &NoneJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("NoneJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::None> _stored;
  org::sem::None* getPtr() { return _stored.get(); }
};

struct ErrorItemJs : public Napi::ObjectWrap<ErrorItemJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::ErrorItem, OrgSemKind>(info,
                                                            getPtr(),
                                                            static_cast<OrgSemKind(org::sem::ErrorItem::*)() const>(&org::sem::ErrorItem::getKind),
                                                            std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ErrorItemJs", {InstanceMethod("getKind", &ErrorItemJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ErrorItemJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::ErrorItem> _stored;
  org::sem::ErrorItem* getPtr() { return _stored.get(); }
};

struct ErrorGroupJs : public Napi::ObjectWrap<ErrorGroupJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::ErrorGroup, OrgSemKind>(info,
                                                             getPtr(),
                                                             static_cast<OrgSemKind(org::sem::ErrorGroup::*)() const>(&org::sem::ErrorGroup::getKind),
                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ErrorGroupJs", {InstanceMethod("getKind", &ErrorGroupJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ErrorGroupJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::ErrorGroup> _stored;
  org::sem::ErrorGroup* getPtr() { return _stored.get(); }
};

struct StmtJs : public Napi::ObjectWrap<StmtJs> {
  Napi::Value getAttached(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Stmt, hstd::Vec<org::sem::SemId<org::sem::Org>>>(info,
                                                                                      getPtr(),
                                                                                      static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttached),
                                                                                      std::make_tuple(CxxArgSpec<hstd::Opt<hstd::Str>>{"kind", std::nullopt}));
  }
  Napi::Value getCaption(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Stmt, hstd::Vec<org::sem::SemId<org::sem::Org>>>(info,
                                                                                      getPtr(),
                                                                                      static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getCaption),
                                                                                      std::make_tuple());
  }
  Napi::Value getName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Stmt, hstd::Vec<hstd::Str>>(info,
                                                                 getPtr(),
                                                                 static_cast<hstd::Vec<hstd::Str>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getName),
                                                                 std::make_tuple());
  }
  Napi::Value getAttrs(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Stmt, hstd::Vec<org::sem::AttrValue>>(info,
                                                                           getPtr(),
                                                                           static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttrs),
                                                                           std::make_tuple(CxxArgSpec<hstd::Opt<hstd::Str>>{"kind", std::nullopt}));
  }
  Napi::Value getFirstAttr(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Stmt, hstd::Opt<org::sem::AttrValue>>(info,
                                                                           getPtr(),
                                                                           static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttr),
                                                                           std::make_tuple(CxxArgSpec<hstd::Str>{"kind"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "StmtJs", {InstanceMethod("getAttached", &StmtJs::getAttached),
                                                      InstanceMethod("getCaption", &StmtJs::getCaption),
                                                      InstanceMethod("getName", &StmtJs::getName),
                                                      InstanceMethod("getAttrs", &StmtJs::getAttrs),
                                                      InstanceMethod("getFirstAttr", &StmtJs::getFirstAttr)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("StmtJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Stmt> _stored;
  org::sem::Stmt* getPtr() { return _stored.get(); }
};

struct InlineJs : public Napi::ObjectWrap<InlineJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "InlineJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("InlineJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Inline> _stored;
  org::sem::Inline* getPtr() { return _stored.get(); }
};

struct StmtListJs : public Napi::ObjectWrap<StmtListJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::StmtList, OrgSemKind>(info,
                                                           getPtr(),
                                                           static_cast<OrgSemKind(org::sem::StmtList::*)() const>(&org::sem::StmtList::getKind),
                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "StmtListJs", {InstanceMethod("getKind", &StmtListJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("StmtListJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::StmtList> _stored;
  org::sem::StmtList* getPtr() { return _stored.get(); }
};

struct EmptyJs : public Napi::ObjectWrap<EmptyJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Empty, OrgSemKind>(info,
                                                        getPtr(),
                                                        static_cast<OrgSemKind(org::sem::Empty::*)() const>(&org::sem::Empty::getKind),
                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "EmptyJs", {InstanceMethod("getKind", &EmptyJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("EmptyJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Empty> _stored;
  org::sem::Empty* getPtr() { return _stored.get(); }
};

struct LeafJs : public Napi::ObjectWrap<LeafJs> {
  Napi::Value getText(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Leaf, hstd::Str>(info,
                                                      getPtr(),
                                                      static_cast<hstd::Str(org::sem::Leaf::*)() const>(&org::sem::Leaf::getText),
                                                      std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LeafJs", {InstanceMethod("getText", &LeafJs::getText)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("LeafJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Leaf> _stored;
  org::sem::Leaf* getPtr() { return _stored.get(); }
};

struct TimeJs : public Napi::ObjectWrap<TimeJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, OrgSemKind>(info,
                                                       getPtr(),
                                                       static_cast<OrgSemKind(org::sem::Time::*)() const>(&org::sem::Time::getKind),
                                                       std::make_tuple());
  }
  Napi::Value getYear(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, hstd::Opt<int>>(info,
                                                           getPtr(),
                                                           static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getYear),
                                                           std::make_tuple());
  }
  Napi::Value getMonth(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, hstd::Opt<int>>(info,
                                                           getPtr(),
                                                           static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getMonth),
                                                           std::make_tuple());
  }
  Napi::Value getDay(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, hstd::Opt<int>>(info,
                                                           getPtr(),
                                                           static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getDay),
                                                           std::make_tuple());
  }
  Napi::Value getHour(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, hstd::Opt<int>>(info,
                                                           getPtr(),
                                                           static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getHour),
                                                           std::make_tuple());
  }
  Napi::Value getMinute(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, hstd::Opt<int>>(info,
                                                           getPtr(),
                                                           static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getMinute),
                                                           std::make_tuple());
  }
  Napi::Value getSecond(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, hstd::Opt<int>>(info,
                                                           getPtr(),
                                                           static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getSecond),
                                                           std::make_tuple());
  }
  Napi::Value getStaticTime(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, hstd::UserTime>(info,
                                                           getPtr(),
                                                           static_cast<hstd::UserTime(org::sem::Time::*)() const>(&org::sem::Time::getStaticTime),
                                                           std::make_tuple());
  }
  Napi::Value isStatic(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, bool>(info,
                                                 getPtr(),
                                                 static_cast<bool(org::sem::Time::*)() const>(&org::sem::Time::isStatic),
                                                 std::make_tuple());
  }
  Napi::Value getStaticConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, org::sem::Time::Static const&>(info,
                                                                          getPtr(),
                                                                          static_cast<org::sem::Time::Static const&(org::sem::Time::*)() const>(&org::sem::Time::getStatic),
                                                                          std::make_tuple());
  }
  Napi::Value getStaticMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::Time, org::sem::Time::Static&>(info,
                                                               getPtr(),
                                                               static_cast<org::sem::Time::Static&(org::sem::Time::*)()>(&org::sem::Time::getStatic),
                                                               std::make_tuple());
  }
  Napi::Value isDynamic(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, bool>(info,
                                                 getPtr(),
                                                 static_cast<bool(org::sem::Time::*)() const>(&org::sem::Time::isDynamic),
                                                 std::make_tuple());
  }
  Napi::Value getDynamicConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, org::sem::Time::Dynamic const&>(info,
                                                                           getPtr(),
                                                                           static_cast<org::sem::Time::Dynamic const&(org::sem::Time::*)() const>(&org::sem::Time::getDynamic),
                                                                           std::make_tuple());
  }
  Napi::Value getDynamicMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::Time, org::sem::Time::Dynamic&>(info,
                                                                getPtr(),
                                                                static_cast<org::sem::Time::Dynamic&(org::sem::Time::*)()>(&org::sem::Time::getDynamic),
                                                                std::make_tuple());
  }
  Napi::Value getTimeKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, org::sem::Time::TimeKind>(info,
                                                                     getPtr(),
                                                                     static_cast<org::sem::Time::TimeKind(org::sem::Time::*)() const>(&org::sem::Time::getTimeKind),
                                                                     std::make_tuple());
  }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, char const*>(info,
                                                        getPtr(),
                                                        static_cast<char const*(org::sem::Time::*)() const>(&org::sem::Time::sub_variant_get_name),
                                                        std::make_tuple());
  }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, org::sem::Time::TimeVariant const&>(info,
                                                                               getPtr(),
                                                                               static_cast<org::sem::Time::TimeVariant const&(org::sem::Time::*)() const>(&org::sem::Time::sub_variant_get_data),
                                                                               std::make_tuple());
  }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Time, org::sem::Time::TimeKind>(info,
                                                                     getPtr(),
                                                                     static_cast<org::sem::Time::TimeKind(org::sem::Time::*)() const>(&org::sem::Time::sub_variant_get_kind),
                                                                     std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TimeJs", {InstanceMethod("getKind", &TimeJs::getKind),
                                                      InstanceMethod("getYear", &TimeJs::getYear),
                                                      InstanceMethod("getMonth", &TimeJs::getMonth),
                                                      InstanceMethod("getDay", &TimeJs::getDay),
                                                      InstanceMethod("getHour", &TimeJs::getHour),
                                                      InstanceMethod("getMinute", &TimeJs::getMinute),
                                                      InstanceMethod("getSecond", &TimeJs::getSecond),
                                                      InstanceMethod("getStaticTime", &TimeJs::getStaticTime),
                                                      InstanceMethod("isStatic", &TimeJs::isStatic),
                                                      InstanceMethod("getStaticConst", &TimeJs::getStaticConst),
                                                      InstanceMethod("getStaticMut", &TimeJs::getStaticMut),
                                                      InstanceMethod("isDynamic", &TimeJs::isDynamic),
                                                      InstanceMethod("getDynamicConst", &TimeJs::getDynamicConst),
                                                      InstanceMethod("getDynamicMut", &TimeJs::getDynamicMut),
                                                      InstanceMethod("getTimeKind", &TimeJs::getTimeKind),
                                                      InstanceMethod("sub_variant_get_name", &TimeJs::sub_variant_get_name),
                                                      InstanceMethod("sub_variant_get_data", &TimeJs::sub_variant_get_data),
                                                      InstanceMethod("sub_variant_get_kind", &TimeJs::sub_variant_get_kind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("TimeJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Time> _stored;
  org::sem::Time* getPtr() { return _stored.get(); }
};

struct TimeRangeJs : public Napi::ObjectWrap<TimeRangeJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::TimeRange, OrgSemKind>(info,
                                                            getPtr(),
                                                            static_cast<OrgSemKind(org::sem::TimeRange::*)() const>(&org::sem::TimeRange::getKind),
                                                            std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TimeRangeJs", {InstanceMethod("getKind", &TimeRangeJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("TimeRangeJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::TimeRange> _stored;
  org::sem::TimeRange* getPtr() { return _stored.get(); }
};

struct MacroJs : public Napi::ObjectWrap<MacroJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Macro, OrgSemKind>(info,
                                                        getPtr(),
                                                        static_cast<OrgSemKind(org::sem::Macro::*)() const>(&org::sem::Macro::getKind),
                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MacroJs", {InstanceMethod("getKind", &MacroJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MacroJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Macro> _stored;
  org::sem::Macro* getPtr() { return _stored.get(); }
};

struct SymbolJs : public Napi::ObjectWrap<SymbolJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Symbol, OrgSemKind>(info,
                                                         getPtr(),
                                                         static_cast<OrgSemKind(org::sem::Symbol::*)() const>(&org::sem::Symbol::getKind),
                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SymbolJs", {InstanceMethod("getKind", &SymbolJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SymbolJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Symbol> _stored;
  org::sem::Symbol* getPtr() { return _stored.get(); }
};

struct MarkupJs : public Napi::ObjectWrap<MarkupJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MarkupJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MarkupJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Markup> _stored;
  org::sem::Markup* getPtr() { return _stored.get(); }
};

struct RadioTargetJs : public Napi::ObjectWrap<RadioTargetJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::RadioTarget, OrgSemKind>(info,
                                                              getPtr(),
                                                              static_cast<OrgSemKind(org::sem::RadioTarget::*)() const>(&org::sem::RadioTarget::getKind),
                                                              std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "RadioTargetJs", {InstanceMethod("getKind", &RadioTargetJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("RadioTargetJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::RadioTarget> _stored;
  org::sem::RadioTarget* getPtr() { return _stored.get(); }
};

struct LatexJs : public Napi::ObjectWrap<LatexJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Latex, OrgSemKind>(info,
                                                        getPtr(),
                                                        static_cast<OrgSemKind(org::sem::Latex::*)() const>(&org::sem::Latex::getKind),
                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LatexJs", {InstanceMethod("getKind", &LatexJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("LatexJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Latex> _stored;
  org::sem::Latex* getPtr() { return _stored.get(); }
};

struct SubtreeLogJs : public Napi::ObjectWrap<SubtreeLogJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::SubtreeLog, OrgSemKind>(info,
                                                             getPtr(),
                                                             static_cast<OrgSemKind(org::sem::SubtreeLog::*)() const>(&org::sem::SubtreeLog::getKind),
                                                             std::make_tuple());
  }
  Napi::Value setDescription(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::SubtreeLog, void>(info,
                                                  getPtr(),
                                                  static_cast<void(org::sem::SubtreeLog::*)(org::sem::SemId<org::sem::StmtList>)>(&org::sem::SubtreeLog::setDescription),
                                                  std::make_tuple(CxxArgSpec<org::sem::SemId<org::sem::StmtList>>{"desc"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreeLogJs", {InstanceMethod("getKind", &SubtreeLogJs::getKind),
                                                            InstanceMethod("setDescription", &SubtreeLogJs::setDescription)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SubtreeLogJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::SubtreeLog> _stored;
  org::sem::SubtreeLog* getPtr() { return _stored.get(); }
};

struct SubtreeJs : public Napi::ObjectWrap<SubtreeJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Subtree, OrgSemKind>(info,
                                                          getPtr(),
                                                          static_cast<OrgSemKind(org::sem::Subtree::*)() const>(&org::sem::Subtree::getKind),
                                                          std::make_tuple());
  }
  Napi::Value getTimePeriods(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Subtree, hstd::Vec<org::sem::SubtreePeriod>>(info,
                                                                                  getPtr(),
                                                                                  static_cast<hstd::Vec<org::sem::SubtreePeriod>(org::sem::Subtree::*)(hstd::IntSet<org::sem::SubtreePeriod::Kind>) const>(&org::sem::Subtree::getTimePeriods),
                                                                                  std::make_tuple(CxxArgSpec<hstd::IntSet<org::sem::SubtreePeriod::Kind>>{"kinds"}));
  }
  Napi::Value getProperties(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Subtree, hstd::Vec<org::sem::NamedProperty>>(info,
                                                                                  getPtr(),
                                                                                  static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperties),
                                                                                  std::make_tuple(CxxArgSpec<hstd::Str>{"kind"},
                                                                                                  CxxArgSpec<hstd::Opt<hstd::Str>>{"subkind", std::nullopt}));
  }
  Napi::Value getProperty(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Subtree, hstd::Opt<org::sem::NamedProperty>>(info,
                                                                                  getPtr(),
                                                                                  static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperty),
                                                                                  std::make_tuple(CxxArgSpec<hstd::Str>{"kind"},
                                                                                                  CxxArgSpec<hstd::Opt<hstd::Str>>{"subkind", std::nullopt}));
  }
  Napi::Value removeProperty(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::Subtree, void>(info,
                                               getPtr(),
                                               static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::removeProperty),
                                               std::make_tuple(CxxArgSpec<hstd::Str>{"kind"},
                                                               CxxArgSpec<hstd::Opt<hstd::Str>>{"subkind", std::nullopt}));
  }
  Napi::Value setProperty(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::Subtree, void>(info,
                                               getPtr(),
                                               static_cast<void(org::sem::Subtree::*)(org::sem::NamedProperty const&)>(&org::sem::Subtree::setProperty),
                                               std::make_tuple(CxxArgSpec<org::sem::NamedProperty>{"value"}));
  }
  Napi::Value setPropertyStrValue(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::Subtree, void>(info,
                                               getPtr(),
                                               static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::setPropertyStrValue),
                                               std::make_tuple(CxxArgSpec<hstd::Str>{"value"},
                                                               CxxArgSpec<hstd::Str>{"kind"},
                                                               CxxArgSpec<hstd::Opt<hstd::Str>>{"subkind", std::nullopt}));
  }
  Napi::Value getCleanTitle(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Subtree, hstd::Str>(info,
                                                         getPtr(),
                                                         static_cast<hstd::Str(org::sem::Subtree::*)() const>(&org::sem::Subtree::getCleanTitle),
                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SubtreeJs", {InstanceMethod("getKind", &SubtreeJs::getKind),
                                                         InstanceMethod("getTimePeriods", &SubtreeJs::getTimePeriods),
                                                         InstanceMethod("getProperties", &SubtreeJs::getProperties),
                                                         InstanceMethod("getProperty", &SubtreeJs::getProperty),
                                                         InstanceMethod("removeProperty", &SubtreeJs::removeProperty),
                                                         InstanceMethod("setProperty", &SubtreeJs::setProperty),
                                                         InstanceMethod("setPropertyStrValue", &SubtreeJs::setPropertyStrValue),
                                                         InstanceMethod("getCleanTitle", &SubtreeJs::getCleanTitle)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SubtreeJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Subtree> _stored;
  org::sem::Subtree* getPtr() { return _stored.get(); }
};

struct ColonExampleJs : public Napi::ObjectWrap<ColonExampleJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::ColonExample, OrgSemKind>(info,
                                                               getPtr(),
                                                               static_cast<OrgSemKind(org::sem::ColonExample::*)() const>(&org::sem::ColonExample::getKind),
                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ColonExampleJs", {InstanceMethod("getKind", &ColonExampleJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ColonExampleJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::ColonExample> _stored;
  org::sem::ColonExample* getPtr() { return _stored.get(); }
};

struct CallJs : public Napi::ObjectWrap<CallJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Call, OrgSemKind>(info,
                                                       getPtr(),
                                                       static_cast<OrgSemKind(org::sem::Call::*)() const>(&org::sem::Call::getKind),
                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CallJs", {InstanceMethod("getKind", &CallJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CallJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Call> _stored;
  org::sem::Call* getPtr() { return _stored.get(); }
};

struct ListItemJs : public Napi::ObjectWrap<ListItemJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::ListItem, OrgSemKind>(info,
                                                           getPtr(),
                                                           static_cast<OrgSemKind(org::sem::ListItem::*)() const>(&org::sem::ListItem::getKind),
                                                           std::make_tuple());
  }
  Napi::Value isDescriptionItem(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::ListItem, bool>(info,
                                                     getPtr(),
                                                     static_cast<bool(org::sem::ListItem::*)() const>(&org::sem::ListItem::isDescriptionItem),
                                                     std::make_tuple());
  }
  Napi::Value getCleanHeader(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::ListItem, hstd::Opt<hstd::Str>>(info,
                                                                     getPtr(),
                                                                     static_cast<hstd::Opt<hstd::Str>(org::sem::ListItem::*)() const>(&org::sem::ListItem::getCleanHeader),
                                                                     std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ListItemJs", {InstanceMethod("getKind", &ListItemJs::getKind),
                                                          InstanceMethod("isDescriptionItem", &ListItemJs::isDescriptionItem),
                                                          InstanceMethod("getCleanHeader", &ListItemJs::getCleanHeader)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ListItemJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::ListItem> _stored;
  org::sem::ListItem* getPtr() { return _stored.get(); }
};

struct DocumentOptionsJs : public Napi::ObjectWrap<DocumentOptionsJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentOptions, OrgSemKind>(info,
                                                                  getPtr(),
                                                                  static_cast<OrgSemKind(org::sem::DocumentOptions::*)() const>(&org::sem::DocumentOptions::getKind),
                                                                  std::make_tuple());
  }
  Napi::Value getProperties(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentOptions, hstd::Vec<org::sem::NamedProperty>>(info,
                                                                                          getPtr(),
                                                                                          static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperties),
                                                                                          std::make_tuple(CxxArgSpec<hstd::Str>{"kind"},
                                                                                                          CxxArgSpec<hstd::Opt<hstd::Str>>{"subKind", std::nullopt}));
  }
  Napi::Value getProperty(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentOptions, hstd::Opt<org::sem::NamedProperty>>(info,
                                                                                          getPtr(),
                                                                                          static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperty),
                                                                                          std::make_tuple(CxxArgSpec<hstd::Str>{"kind"},
                                                                                                          CxxArgSpec<hstd::Opt<hstd::Str>>{"subKind", std::nullopt}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentOptionsJs", {InstanceMethod("getKind", &DocumentOptionsJs::getKind),
                                                                 InstanceMethod("getProperties", &DocumentOptionsJs::getProperties),
                                                                 InstanceMethod("getProperty", &DocumentOptionsJs::getProperty)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("DocumentOptionsJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::DocumentOptions> _stored;
  org::sem::DocumentOptions* getPtr() { return _stored.get(); }
};

struct DocumentFragmentJs : public Napi::ObjectWrap<DocumentFragmentJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentFragment, OrgSemKind>(info,
                                                                   getPtr(),
                                                                   static_cast<OrgSemKind(org::sem::DocumentFragment::*)() const>(&org::sem::DocumentFragment::getKind),
                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentFragmentJs", {InstanceMethod("getKind", &DocumentFragmentJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("DocumentFragmentJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::DocumentFragment> _stored;
  org::sem::DocumentFragment* getPtr() { return _stored.get(); }
};

struct CriticMarkupJs : public Napi::ObjectWrap<CriticMarkupJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CriticMarkup, OrgSemKind>(info,
                                                               getPtr(),
                                                               static_cast<OrgSemKind(org::sem::CriticMarkup::*)() const>(&org::sem::CriticMarkup::getKind),
                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CriticMarkupJs", {InstanceMethod("getKind", &CriticMarkupJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CriticMarkupJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::CriticMarkup> _stored;
  org::sem::CriticMarkup* getPtr() { return _stored.get(); }
};

struct DocumentJs : public Napi::ObjectWrap<DocumentJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Document, OrgSemKind>(info,
                                                           getPtr(),
                                                           static_cast<OrgSemKind(org::sem::Document::*)() const>(&org::sem::Document::getKind),
                                                           std::make_tuple());
  }
  Napi::Value getProperties(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Document, hstd::Vec<org::sem::NamedProperty>>(info,
                                                                                   getPtr(),
                                                                                   static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperties),
                                                                                   std::make_tuple(CxxArgSpec<hstd::Str>{"kind"},
                                                                                                   CxxArgSpec<hstd::Opt<hstd::Str>>{"subKind", std::nullopt}));
  }
  Napi::Value getProperty(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Document, hstd::Opt<org::sem::NamedProperty>>(info,
                                                                                   getPtr(),
                                                                                   static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperty),
                                                                                   std::make_tuple(CxxArgSpec<hstd::Str>{"kind"},
                                                                                                   CxxArgSpec<hstd::Opt<hstd::Str>>{"subKind", std::nullopt}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentJs", {InstanceMethod("getKind", &DocumentJs::getKind),
                                                          InstanceMethod("getProperties", &DocumentJs::getProperties),
                                                          InstanceMethod("getProperty", &DocumentJs::getProperty)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("DocumentJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Document> _stored;
  org::sem::Document* getPtr() { return _stored.get(); }
};

struct FileTargetJs : public Napi::ObjectWrap<FileTargetJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::FileTarget, OrgSemKind>(info,
                                                             getPtr(),
                                                             static_cast<OrgSemKind(org::sem::FileTarget::*)() const>(&org::sem::FileTarget::getKind),
                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "FileTargetJs", {InstanceMethod("getKind", &FileTargetJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("FileTargetJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::FileTarget> _stored;
  org::sem::FileTarget* getPtr() { return _stored.get(); }
};

struct TextSeparatorJs : public Napi::ObjectWrap<TextSeparatorJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::TextSeparator, OrgSemKind>(info,
                                                                getPtr(),
                                                                static_cast<OrgSemKind(org::sem::TextSeparator::*)() const>(&org::sem::TextSeparator::getKind),
                                                                std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TextSeparatorJs", {InstanceMethod("getKind", &TextSeparatorJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("TextSeparatorJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::TextSeparator> _stored;
  org::sem::TextSeparator* getPtr() { return _stored.get(); }
};

struct DocumentGroupJs : public Napi::ObjectWrap<DocumentGroupJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::DocumentGroup, OrgSemKind>(info,
                                                                getPtr(),
                                                                static_cast<OrgSemKind(org::sem::DocumentGroup::*)() const>(&org::sem::DocumentGroup::getKind),
                                                                std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DocumentGroupJs", {InstanceMethod("getKind", &DocumentGroupJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("DocumentGroupJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::DocumentGroup> _stored;
  org::sem::DocumentGroup* getPtr() { return _stored.get(); }
};

struct FileJs : public Napi::ObjectWrap<FileJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::File, OrgSemKind>(info,
                                                       getPtr(),
                                                       static_cast<OrgSemKind(org::sem::File::*)() const>(&org::sem::File::getKind),
                                                       std::make_tuple());
  }
  Napi::Value isDocument(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::File, bool>(info,
                                                 getPtr(),
                                                 static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isDocument),
                                                 std::make_tuple());
  }
  Napi::Value getDocumentConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::File, org::sem::File::Document const&>(info,
                                                                            getPtr(),
                                                                            static_cast<org::sem::File::Document const&(org::sem::File::*)() const>(&org::sem::File::getDocument),
                                                                            std::make_tuple());
  }
  Napi::Value getDocumentMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::File, org::sem::File::Document&>(info,
                                                                 getPtr(),
                                                                 static_cast<org::sem::File::Document&(org::sem::File::*)()>(&org::sem::File::getDocument),
                                                                 std::make_tuple());
  }
  Napi::Value isAttachment(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::File, bool>(info,
                                                 getPtr(),
                                                 static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isAttachment),
                                                 std::make_tuple());
  }
  Napi::Value getAttachmentConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::File, org::sem::File::Attachment const&>(info,
                                                                              getPtr(),
                                                                              static_cast<org::sem::File::Attachment const&(org::sem::File::*)() const>(&org::sem::File::getAttachment),
                                                                              std::make_tuple());
  }
  Napi::Value getAttachmentMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::File, org::sem::File::Attachment&>(info,
                                                                   getPtr(),
                                                                   static_cast<org::sem::File::Attachment&(org::sem::File::*)()>(&org::sem::File::getAttachment),
                                                                   std::make_tuple());
  }
  Napi::Value isSource(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::File, bool>(info,
                                                 getPtr(),
                                                 static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isSource),
                                                 std::make_tuple());
  }
  Napi::Value getSourceConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::File, org::sem::File::Source const&>(info,
                                                                          getPtr(),
                                                                          static_cast<org::sem::File::Source const&(org::sem::File::*)() const>(&org::sem::File::getSource),
                                                                          std::make_tuple());
  }
  Napi::Value getSourceMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::File, org::sem::File::Source&>(info,
                                                               getPtr(),
                                                               static_cast<org::sem::File::Source&(org::sem::File::*)()>(&org::sem::File::getSource),
                                                               std::make_tuple());
  }
  Napi::Value getFileKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::File, org::sem::File::Kind>(info,
                                                                 getPtr(),
                                                                 static_cast<org::sem::File::Kind(org::sem::File::*)() const>(&org::sem::File::getFileKind),
                                                                 std::make_tuple());
  }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::File, char const*>(info,
                                                        getPtr(),
                                                        static_cast<char const*(org::sem::File::*)() const>(&org::sem::File::sub_variant_get_name),
                                                        std::make_tuple());
  }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::File, org::sem::File::Data const&>(info,
                                                                        getPtr(),
                                                                        static_cast<org::sem::File::Data const&(org::sem::File::*)() const>(&org::sem::File::sub_variant_get_data),
                                                                        std::make_tuple());
  }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::File, org::sem::File::Kind>(info,
                                                                 getPtr(),
                                                                 static_cast<org::sem::File::Kind(org::sem::File::*)() const>(&org::sem::File::sub_variant_get_kind),
                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "FileJs", {InstanceMethod("getKind", &FileJs::getKind),
                                                      InstanceMethod("isDocument", &FileJs::isDocument),
                                                      InstanceMethod("getDocumentConst", &FileJs::getDocumentConst),
                                                      InstanceMethod("getDocumentMut", &FileJs::getDocumentMut),
                                                      InstanceMethod("isAttachment", &FileJs::isAttachment),
                                                      InstanceMethod("getAttachmentConst", &FileJs::getAttachmentConst),
                                                      InstanceMethod("getAttachmentMut", &FileJs::getAttachmentMut),
                                                      InstanceMethod("isSource", &FileJs::isSource),
                                                      InstanceMethod("getSourceConst", &FileJs::getSourceConst),
                                                      InstanceMethod("getSourceMut", &FileJs::getSourceMut),
                                                      InstanceMethod("getFileKind", &FileJs::getFileKind),
                                                      InstanceMethod("sub_variant_get_name", &FileJs::sub_variant_get_name),
                                                      InstanceMethod("sub_variant_get_data", &FileJs::sub_variant_get_data),
                                                      InstanceMethod("sub_variant_get_kind", &FileJs::sub_variant_get_kind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("FileJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::File> _stored;
  org::sem::File* getPtr() { return _stored.get(); }
};

struct DirectoryJs : public Napi::ObjectWrap<DirectoryJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Directory, OrgSemKind>(info,
                                                            getPtr(),
                                                            static_cast<OrgSemKind(org::sem::Directory::*)() const>(&org::sem::Directory::getKind),
                                                            std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DirectoryJs", {InstanceMethod("getKind", &DirectoryJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("DirectoryJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Directory> _stored;
  org::sem::Directory* getPtr() { return _stored.get(); }
};

struct SymlinkJs : public Napi::ObjectWrap<SymlinkJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Symlink, OrgSemKind>(info,
                                                          getPtr(),
                                                          static_cast<OrgSemKind(org::sem::Symlink::*)() const>(&org::sem::Symlink::getKind),
                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SymlinkJs", {InstanceMethod("getKind", &SymlinkJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SymlinkJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Symlink> _stored;
  org::sem::Symlink* getPtr() { return _stored.get(); }
};

struct CmdIncludeJs : public Napi::ObjectWrap<CmdIncludeJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, OrgSemKind>(info,
                                                             getPtr(),
                                                             static_cast<OrgSemKind(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getKind),
                                                             std::make_tuple());
  }
  Napi::Value isExample(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isExample),
                                                       std::make_tuple());
  }
  Napi::Value getExampleConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, org::sem::CmdInclude::Example const&>(info,
                                                                                       getPtr(),
                                                                                       static_cast<org::sem::CmdInclude::Example const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getExample),
                                                                                       std::make_tuple());
  }
  Napi::Value getExampleMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::CmdInclude, org::sem::CmdInclude::Example&>(info,
                                                                            getPtr(),
                                                                            static_cast<org::sem::CmdInclude::Example&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getExample),
                                                                            std::make_tuple());
  }
  Napi::Value isExport(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isExport),
                                                       std::make_tuple());
  }
  Napi::Value getExportConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, org::sem::CmdInclude::Export const&>(info,
                                                                                      getPtr(),
                                                                                      static_cast<org::sem::CmdInclude::Export const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getExport),
                                                                                      std::make_tuple());
  }
  Napi::Value getExportMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::CmdInclude, org::sem::CmdInclude::Export&>(info,
                                                                           getPtr(),
                                                                           static_cast<org::sem::CmdInclude::Export&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getExport),
                                                                           std::make_tuple());
  }
  Napi::Value isCustom(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isCustom),
                                                       std::make_tuple());
  }
  Napi::Value getCustomConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, org::sem::CmdInclude::Custom const&>(info,
                                                                                      getPtr(),
                                                                                      static_cast<org::sem::CmdInclude::Custom const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getCustom),
                                                                                      std::make_tuple());
  }
  Napi::Value getCustomMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::CmdInclude, org::sem::CmdInclude::Custom&>(info,
                                                                           getPtr(),
                                                                           static_cast<org::sem::CmdInclude::Custom&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getCustom),
                                                                           std::make_tuple());
  }
  Napi::Value isSrc(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isSrc),
                                                       std::make_tuple());
  }
  Napi::Value getSrcConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, org::sem::CmdInclude::Src const&>(info,
                                                                                   getPtr(),
                                                                                   static_cast<org::sem::CmdInclude::Src const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getSrc),
                                                                                   std::make_tuple());
  }
  Napi::Value getSrcMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::CmdInclude, org::sem::CmdInclude::Src&>(info,
                                                                        getPtr(),
                                                                        static_cast<org::sem::CmdInclude::Src&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getSrc),
                                                                        std::make_tuple());
  }
  Napi::Value isOrgDocument(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, bool>(info,
                                                       getPtr(),
                                                       static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isOrgDocument),
                                                       std::make_tuple());
  }
  Napi::Value getOrgDocumentConst(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, org::sem::CmdInclude::OrgDocument const&>(info,
                                                                                           getPtr(),
                                                                                           static_cast<org::sem::CmdInclude::OrgDocument const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getOrgDocument),
                                                                                           std::make_tuple());
  }
  Napi::Value getOrgDocumentMut(Napi::CallbackInfo const& info) {
    return WrapMethod<org::sem::CmdInclude, org::sem::CmdInclude::OrgDocument&>(info,
                                                                                getPtr(),
                                                                                static_cast<org::sem::CmdInclude::OrgDocument&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getOrgDocument),
                                                                                std::make_tuple());
  }
  Napi::Value getIncludeKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, org::sem::CmdInclude::Kind>(info,
                                                                             getPtr(),
                                                                             static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getIncludeKind),
                                                                             std::make_tuple());
  }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, char const*>(info,
                                                              getPtr(),
                                                              static_cast<char const*(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::sub_variant_get_name),
                                                              std::make_tuple());
  }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, org::sem::CmdInclude::Data const&>(info,
                                                                                    getPtr(),
                                                                                    static_cast<org::sem::CmdInclude::Data const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::sub_variant_get_data),
                                                                                    std::make_tuple());
  }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdInclude, org::sem::CmdInclude::Kind>(info,
                                                                             getPtr(),
                                                                             static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::sub_variant_get_kind),
                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdIncludeJs", {InstanceMethod("getKind", &CmdIncludeJs::getKind),
                                                            InstanceMethod("isExample", &CmdIncludeJs::isExample),
                                                            InstanceMethod("getExampleConst", &CmdIncludeJs::getExampleConst),
                                                            InstanceMethod("getExampleMut", &CmdIncludeJs::getExampleMut),
                                                            InstanceMethod("isExport", &CmdIncludeJs::isExport),
                                                            InstanceMethod("getExportConst", &CmdIncludeJs::getExportConst),
                                                            InstanceMethod("getExportMut", &CmdIncludeJs::getExportMut),
                                                            InstanceMethod("isCustom", &CmdIncludeJs::isCustom),
                                                            InstanceMethod("getCustomConst", &CmdIncludeJs::getCustomConst),
                                                            InstanceMethod("getCustomMut", &CmdIncludeJs::getCustomMut),
                                                            InstanceMethod("isSrc", &CmdIncludeJs::isSrc),
                                                            InstanceMethod("getSrcConst", &CmdIncludeJs::getSrcConst),
                                                            InstanceMethod("getSrcMut", &CmdIncludeJs::getSrcMut),
                                                            InstanceMethod("isOrgDocument", &CmdIncludeJs::isOrgDocument),
                                                            InstanceMethod("getOrgDocumentConst", &CmdIncludeJs::getOrgDocumentConst),
                                                            InstanceMethod("getOrgDocumentMut", &CmdIncludeJs::getOrgDocumentMut),
                                                            InstanceMethod("getIncludeKind", &CmdIncludeJs::getIncludeKind),
                                                            InstanceMethod("sub_variant_get_name", &CmdIncludeJs::sub_variant_get_name),
                                                            InstanceMethod("sub_variant_get_data", &CmdIncludeJs::sub_variant_get_data),
                                                            InstanceMethod("sub_variant_get_kind", &CmdIncludeJs::sub_variant_get_kind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdIncludeJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmNoneValue> _stored;
  org::imm::ImmNoneValue* getPtr() { return _stored.get(); }
};

struct ImmErrorItemValueJs : public Napi::ObjectWrap<ImmErrorItemValueJs> {
  Napi::Value setMessage(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmErrorItemValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmErrorItemValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmErrorItemValue::setMessage),
                                                         std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setFunction(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmErrorItemValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmErrorItemValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmErrorItemValue::setFunction),
                                                         std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  Napi::Value setLine(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmErrorItemValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmErrorItemValue::*)(immer::box<std::optional<int>> const&)>(&org::imm::ImmErrorItemValue::setLine),
                                                         std::make_tuple(CxxArgSpec<immer::box<std::optional<int>>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorItemValueJs", {InstanceMethod("setMessage", &ImmErrorItemValueJs::setMessage),
                                                                   InstanceMethod("setFunction", &ImmErrorItemValueJs::setFunction),
                                                                   InstanceMethod("setLine", &ImmErrorItemValueJs::setLine)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorItemValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmErrorItemValue> _stored;
  org::imm::ImmErrorItemValue* getPtr() { return _stored.get(); }
};

struct ImmErrorGroupValueJs : public Napi::ObjectWrap<ImmErrorGroupValueJs> {
  Napi::Value setDiagnostics(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmErrorGroupValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmErrorGroupValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmErrorItem>> const&)>(&org::imm::ImmErrorGroupValue::setDiagnostics),
                                                          std::make_tuple(CxxArgSpec<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmErrorItem>>>{"value"}));
  }
  Napi::Value setFunction(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmErrorGroupValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmErrorGroupValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmErrorGroupValue::setFunction),
                                                          std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  Napi::Value setLine(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmErrorGroupValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmErrorGroupValue::*)(immer::box<std::optional<int>> const&)>(&org::imm::ImmErrorGroupValue::setLine),
                                                          std::make_tuple(CxxArgSpec<immer::box<std::optional<int>>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorGroupValueJs", {InstanceMethod("setDiagnostics", &ImmErrorGroupValueJs::setDiagnostics),
                                                                    InstanceMethod("setFunction", &ImmErrorGroupValueJs::setFunction),
                                                                    InstanceMethod("setLine", &ImmErrorGroupValueJs::setLine)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorGroupValueJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmEmptyValue> _stored;
  org::imm::ImmEmptyValue* getPtr() { return _stored.get(); }
};

struct ImmCmdCaptionValueJs : public Napi::ObjectWrap<ImmCmdCaptionValueJs> {
  Napi::Value setText(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCaptionValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmCmdCaptionValue::*)(org::imm::ImmIdT<org::imm::ImmParagraph> const&)>(&org::imm::ImmCmdCaptionValue::setText),
                                                          std::make_tuple(CxxArgSpec<org::imm::ImmIdT<org::imm::ImmParagraph>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCaptionValueJs", {InstanceMethod("setText", &ImmCmdCaptionValueJs::setText)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCaptionValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdCaptionValue> _stored;
  org::imm::ImmCmdCaptionValue* getPtr() { return _stored.get(); }
};

struct ImmCmdColumnsValueJs : public Napi::ObjectWrap<ImmCmdColumnsValueJs> {
  Napi::Value setView(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdColumnsValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmCmdColumnsValue::*)(org::sem::ColumnView const&)>(&org::imm::ImmCmdColumnsValue::setView),
                                                          std::make_tuple(CxxArgSpec<org::sem::ColumnView>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdColumnsValueJs", {InstanceMethod("setView", &ImmCmdColumnsValueJs::setView)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdColumnsValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdColumnsValue> _stored;
  org::imm::ImmCmdColumnsValue* getPtr() { return _stored.get(); }
};

struct ImmCmdNameValueJs : public Napi::ObjectWrap<ImmCmdNameValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdNameValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmCmdNameValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdNameValue::setName),
                                                       std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdNameValueJs", {InstanceMethod("setName", &ImmCmdNameValueJs::setName)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdNameValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdNameValue> _stored;
  org::imm::ImmCmdNameValue* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomArgsValueJs : public Napi::ObjectWrap<ImmCmdCustomArgsValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCustomArgsValue, void>(info,
                                                             getPtr(),
                                                             static_cast<void(org::imm::ImmCmdCustomArgsValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdCustomArgsValue::setName),
                                                             std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setIsattached(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCustomArgsValue, void>(info,
                                                             getPtr(),
                                                             static_cast<void(org::imm::ImmCmdCustomArgsValue::*)(bool const&)>(&org::imm::ImmCmdCustomArgsValue::setIsattached),
                                                             std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomArgsValueJs", {InstanceMethod("setName", &ImmCmdCustomArgsValueJs::setName),
                                                                       InstanceMethod("setIsattached", &ImmCmdCustomArgsValueJs::setIsattached)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomArgsValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdCustomArgsValue> _stored;
  org::imm::ImmCmdCustomArgsValue* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomRawValueJs : public Napi::ObjectWrap<ImmCmdCustomRawValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCustomRawValue, void>(info,
                                                            getPtr(),
                                                            static_cast<void(org::imm::ImmCmdCustomRawValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdCustomRawValue::setName),
                                                            std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setIsattached(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCustomRawValue, void>(info,
                                                            getPtr(),
                                                            static_cast<void(org::imm::ImmCmdCustomRawValue::*)(bool const&)>(&org::imm::ImmCmdCustomRawValue::setIsattached),
                                                            std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  Napi::Value setText(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCustomRawValue, void>(info,
                                                            getPtr(),
                                                            static_cast<void(org::imm::ImmCmdCustomRawValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdCustomRawValue::setText),
                                                            std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomRawValueJs", {InstanceMethod("setName", &ImmCmdCustomRawValueJs::setName),
                                                                      InstanceMethod("setIsattached", &ImmCmdCustomRawValueJs::setIsattached),
                                                                      InstanceMethod("setText", &ImmCmdCustomRawValueJs::setText)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomRawValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdCustomRawValue> _stored;
  org::imm::ImmCmdCustomRawValue* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomTextValueJs : public Napi::ObjectWrap<ImmCmdCustomTextValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCustomTextValue, void>(info,
                                                             getPtr(),
                                                             static_cast<void(org::imm::ImmCmdCustomTextValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdCustomTextValue::setName),
                                                             std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setIsattached(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCustomTextValue, void>(info,
                                                             getPtr(),
                                                             static_cast<void(org::imm::ImmCmdCustomTextValue::*)(bool const&)>(&org::imm::ImmCmdCustomTextValue::setIsattached),
                                                             std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  Napi::Value setText(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCustomTextValue, void>(info,
                                                             getPtr(),
                                                             static_cast<void(org::imm::ImmCmdCustomTextValue::*)(org::imm::ImmIdT<org::imm::ImmParagraph> const&)>(&org::imm::ImmCmdCustomTextValue::setText),
                                                             std::make_tuple(CxxArgSpec<org::imm::ImmIdT<org::imm::ImmParagraph>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomTextValueJs", {InstanceMethod("setName", &ImmCmdCustomTextValueJs::setName),
                                                                       InstanceMethod("setIsattached", &ImmCmdCustomTextValueJs::setIsattached),
                                                                       InstanceMethod("setText", &ImmCmdCustomTextValueJs::setText)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomTextValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdCustomTextValue> _stored;
  org::imm::ImmCmdCustomTextValue* getPtr() { return _stored.get(); }
};

struct ImmCmdCallValueJs : public Napi::ObjectWrap<ImmCmdCallValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCallValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmCmdCallValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdCallValue::setName),
                                                       std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setFilename(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCallValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmCmdCallValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmCmdCallValue::setFilename),
                                                       std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  Napi::Value setInsideheaderattrs(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCallValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmCmdCallValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmCmdCallValue::setInsideheaderattrs),
                                                       std::make_tuple(CxxArgSpec<org::sem::AttrGroup>{"value"}));
  }
  Napi::Value setCallattrs(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCallValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmCmdCallValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmCmdCallValue::setCallattrs),
                                                       std::make_tuple(CxxArgSpec<org::sem::AttrGroup>{"value"}));
  }
  Napi::Value setEndheaderattrs(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCallValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmCmdCallValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmCmdCallValue::setEndheaderattrs),
                                                       std::make_tuple(CxxArgSpec<org::sem::AttrGroup>{"value"}));
  }
  Napi::Value setResult(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdCallValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmCmdCallValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&)>(&org::imm::ImmCmdCallValue::setResult),
                                                       std::make_tuple(CxxArgSpec<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCallValueJs", {InstanceMethod("setName", &ImmCmdCallValueJs::setName),
                                                                 InstanceMethod("setFilename", &ImmCmdCallValueJs::setFilename),
                                                                 InstanceMethod("setInsideheaderattrs", &ImmCmdCallValueJs::setInsideheaderattrs),
                                                                 InstanceMethod("setCallattrs", &ImmCmdCallValueJs::setCallattrs),
                                                                 InstanceMethod("setEndheaderattrs", &ImmCmdCallValueJs::setEndheaderattrs),
                                                                 InstanceMethod("setResult", &ImmCmdCallValueJs::setResult)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCallValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdCallValue> _stored;
  org::imm::ImmCmdCallValue* getPtr() { return _stored.get(); }
};

struct ImmCmdTblfmValueJs : public Napi::ObjectWrap<ImmCmdTblfmValueJs> {
  Napi::Value setExpr(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdTblfmValue, void>(info,
                                                        getPtr(),
                                                        static_cast<void(org::imm::ImmCmdTblfmValue::*)(org::sem::Tblfm const&)>(&org::imm::ImmCmdTblfmValue::setExpr),
                                                        std::make_tuple(CxxArgSpec<org::sem::Tblfm>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdTblfmValueJs", {InstanceMethod("setExpr", &ImmCmdTblfmValueJs::setExpr)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdTblfmValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdTblfmValue> _stored;
  org::imm::ImmCmdTblfmValue* getPtr() { return _stored.get(); }
};

struct ImmHashTagValueJs : public Napi::ObjectWrap<ImmHashTagValueJs> {
  Napi::Value setText(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmHashTagValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmHashTagValue::*)(org::sem::HashTagText const&)>(&org::imm::ImmHashTagValue::setText),
                                                       std::make_tuple(CxxArgSpec<org::sem::HashTagText>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmHashTagValueJs", {InstanceMethod("setText", &ImmHashTagValueJs::setText)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmHashTagValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmHashTagValue> _stored;
  org::imm::ImmHashTagValue* getPtr() { return _stored.get(); }
};

struct ImmInlineFootnoteValueJs : public Napi::ObjectWrap<ImmInlineFootnoteValueJs> {
  Napi::Value setTag(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmInlineFootnoteValue, void>(info,
                                                              getPtr(),
                                                              static_cast<void(org::imm::ImmInlineFootnoteValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmInlineFootnoteValue::setTag),
                                                              std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setDefinition(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmInlineFootnoteValue, void>(info,
                                                              getPtr(),
                                                              static_cast<void(org::imm::ImmInlineFootnoteValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>> const&)>(&org::imm::ImmInlineFootnoteValue::setDefinition),
                                                              std::make_tuple(CxxArgSpec<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineFootnoteValueJs", {InstanceMethod("setTag", &ImmInlineFootnoteValueJs::setTag),
                                                                        InstanceMethod("setDefinition", &ImmInlineFootnoteValueJs::setDefinition)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineFootnoteValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmInlineFootnoteValue> _stored;
  org::imm::ImmInlineFootnoteValue* getPtr() { return _stored.get(); }
};

struct ImmInlineExportValueJs : public Napi::ObjectWrap<ImmInlineExportValueJs> {
  Napi::Value setExporter(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmInlineExportValue, void>(info,
                                                            getPtr(),
                                                            static_cast<void(org::imm::ImmInlineExportValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmInlineExportValue::setExporter),
                                                            std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setContent(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmInlineExportValue, void>(info,
                                                            getPtr(),
                                                            static_cast<void(org::imm::ImmInlineExportValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmInlineExportValue::setContent),
                                                            std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineExportValueJs", {InstanceMethod("setExporter", &ImmInlineExportValueJs::setExporter),
                                                                      InstanceMethod("setContent", &ImmInlineExportValueJs::setContent)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineExportValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmInlineExportValue> _stored;
  org::imm::ImmInlineExportValue* getPtr() { return _stored.get(); }
};

struct ImmTimeValueJs : public Napi::ObjectWrap<ImmTimeValueJs> {
  Napi::Value setIsactive(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmTimeValue, void>(info,
                                                    getPtr(),
                                                    static_cast<void(org::imm::ImmTimeValue::*)(bool const&)>(&org::imm::ImmTimeValue::setIsactive),
                                                    std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  Napi::Value setTime(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmTimeValue, void>(info,
                                                    getPtr(),
                                                    static_cast<void(org::imm::ImmTimeValue::*)(org::imm::ImmTime::TimeVariant const&)>(&org::imm::ImmTimeValue::setTime),
                                                    std::make_tuple(CxxArgSpec<org::imm::ImmTime::TimeVariant>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeValueJs", {InstanceMethod("setIsactive", &ImmTimeValueJs::setIsactive),
                                                              InstanceMethod("setTime", &ImmTimeValueJs::setTime)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmTimeValue> _stored;
  org::imm::ImmTimeValue* getPtr() { return _stored.get(); }
};

struct ImmTimeRangeValueJs : public Napi::ObjectWrap<ImmTimeRangeValueJs> {
  Napi::Value setFrom(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmTimeRangeValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmTimeRangeValue::*)(org::imm::ImmIdT<org::imm::ImmTime> const&)>(&org::imm::ImmTimeRangeValue::setFrom),
                                                         std::make_tuple(CxxArgSpec<org::imm::ImmIdT<org::imm::ImmTime>>{"value"}));
  }
  Napi::Value setTo(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmTimeRangeValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmTimeRangeValue::*)(org::imm::ImmIdT<org::imm::ImmTime> const&)>(&org::imm::ImmTimeRangeValue::setTo),
                                                         std::make_tuple(CxxArgSpec<org::imm::ImmIdT<org::imm::ImmTime>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeRangeValueJs", {InstanceMethod("setFrom", &ImmTimeRangeValueJs::setFrom),
                                                                   InstanceMethod("setTo", &ImmTimeRangeValueJs::setTo)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeRangeValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmTimeRangeValue> _stored;
  org::imm::ImmTimeRangeValue* getPtr() { return _stored.get(); }
};

struct ImmMacroValueJs : public Napi::ObjectWrap<ImmMacroValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmMacroValue, void>(info,
                                                     getPtr(),
                                                     static_cast<void(org::imm::ImmMacroValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmMacroValue::setName),
                                                     std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setAttrs(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmMacroValue, void>(info,
                                                     getPtr(),
                                                     static_cast<void(org::imm::ImmMacroValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmMacroValue::setAttrs),
                                                     std::make_tuple(CxxArgSpec<org::sem::AttrGroup>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMacroValueJs", {InstanceMethod("setName", &ImmMacroValueJs::setName),
                                                               InstanceMethod("setAttrs", &ImmMacroValueJs::setAttrs)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMacroValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmMacroValue> _stored;
  org::imm::ImmMacroValue* getPtr() { return _stored.get(); }
};

struct ImmSymbolValueJs : public Napi::ObjectWrap<ImmSymbolValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSymbolValue, void>(info,
                                                      getPtr(),
                                                      static_cast<void(org::imm::ImmSymbolValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmSymbolValue::setName),
                                                      std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setParameters(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSymbolValue, void>(info,
                                                      getPtr(),
                                                      static_cast<void(org::imm::ImmSymbolValue::*)(immer::flex_vector<org::imm::ImmSymbol::Param> const&)>(&org::imm::ImmSymbolValue::setParameters),
                                                      std::make_tuple(CxxArgSpec<immer::flex_vector<org::imm::ImmSymbol::Param>>{"value"}));
  }
  Napi::Value setPositional(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSymbolValue, void>(info,
                                                      getPtr(),
                                                      static_cast<void(org::imm::ImmSymbolValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmOrg>> const&)>(&org::imm::ImmSymbolValue::setPositional),
                                                      std::make_tuple(CxxArgSpec<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmOrg>>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymbolValueJs", {InstanceMethod("setName", &ImmSymbolValueJs::setName),
                                                                InstanceMethod("setParameters", &ImmSymbolValueJs::setParameters),
                                                                InstanceMethod("setPositional", &ImmSymbolValueJs::setPositional)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymbolValueJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmParValue> _stored;
  org::imm::ImmParValue* getPtr() { return _stored.get(); }
};

struct ImmRadioTargetValueJs : public Napi::ObjectWrap<ImmRadioTargetValueJs> {
  Napi::Value setWords(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmRadioTargetValue, void>(info,
                                                           getPtr(),
                                                           static_cast<void(org::imm::ImmRadioTargetValue::*)(immer::flex_vector<hstd::Str> const&)>(&org::imm::ImmRadioTargetValue::setWords),
                                                           std::make_tuple(CxxArgSpec<immer::flex_vector<hstd::Str>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRadioTargetValueJs", {InstanceMethod("setWords", &ImmRadioTargetValueJs::setWords)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRadioTargetValueJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmLatexValue> _stored;
  org::imm::ImmLatexValue* getPtr() { return _stored.get(); }
};

struct ImmLinkValueJs : public Napi::ObjectWrap<ImmLinkValueJs> {
  Napi::Value setDescription(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmLinkValue, void>(info,
                                                    getPtr(),
                                                    static_cast<void(org::imm::ImmLinkValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmLinkValue::setDescription),
                                                    std::make_tuple(CxxArgSpec<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>>>{"value"}));
  }
  Napi::Value setTarget(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmLinkValue, void>(info,
                                                    getPtr(),
                                                    static_cast<void(org::imm::ImmLinkValue::*)(org::sem::LinkTarget const&)>(&org::imm::ImmLinkValue::setTarget),
                                                    std::make_tuple(CxxArgSpec<org::sem::LinkTarget>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLinkValueJs", {InstanceMethod("setDescription", &ImmLinkValueJs::setDescription),
                                                              InstanceMethod("setTarget", &ImmLinkValueJs::setTarget)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLinkValueJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmBlockVerseValue> _stored;
  org::imm::ImmBlockVerseValue* getPtr() { return _stored.get(); }
};

struct ImmBlockDynamicFallbackValueJs : public Napi::ObjectWrap<ImmBlockDynamicFallbackValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockDynamicFallbackValue, void>(info,
                                                                    getPtr(),
                                                                    static_cast<void(org::imm::ImmBlockDynamicFallbackValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmBlockDynamicFallbackValue::setName),
                                                                    std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockDynamicFallbackValueJs", {InstanceMethod("setName", &ImmBlockDynamicFallbackValueJs::setName)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockDynamicFallbackValueJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmBlockExampleValue> _stored;
  org::imm::ImmBlockExampleValue* getPtr() { return _stored.get(); }
};

struct ImmBlockExportValueJs : public Napi::ObjectWrap<ImmBlockExportValueJs> {
  Napi::Value setExporter(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockExportValue, void>(info,
                                                           getPtr(),
                                                           static_cast<void(org::imm::ImmBlockExportValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmBlockExportValue::setExporter),
                                                           std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setContent(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockExportValue, void>(info,
                                                           getPtr(),
                                                           static_cast<void(org::imm::ImmBlockExportValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmBlockExportValue::setContent),
                                                           std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExportValueJs", {InstanceMethod("setExporter", &ImmBlockExportValueJs::setExporter),
                                                                     InstanceMethod("setContent", &ImmBlockExportValueJs::setContent)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExportValueJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmBlockAdmonitionValue> _stored;
  org::imm::ImmBlockAdmonitionValue* getPtr() { return _stored.get(); }
};

struct ImmBlockCodeEvalResultValueJs : public Napi::ObjectWrap<ImmBlockCodeEvalResultValueJs> {
  Napi::Value setRaw(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockCodeEvalResultValue, void>(info,
                                                                   getPtr(),
                                                                   static_cast<void(org::imm::ImmBlockCodeEvalResultValue::*)(immer::flex_vector<org::sem::OrgCodeEvalOutput> const&)>(&org::imm::ImmBlockCodeEvalResultValue::setRaw),
                                                                   std::make_tuple(CxxArgSpec<immer::flex_vector<org::sem::OrgCodeEvalOutput>>{"value"}));
  }
  Napi::Value setNode(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockCodeEvalResultValue, void>(info,
                                                                   getPtr(),
                                                                   static_cast<void(org::imm::ImmBlockCodeEvalResultValue::*)(org::imm::ImmIdT<org::imm::ImmOrg> const&)>(&org::imm::ImmBlockCodeEvalResultValue::setNode),
                                                                   std::make_tuple(CxxArgSpec<org::imm::ImmIdT<org::imm::ImmOrg>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeEvalResultValueJs", {InstanceMethod("setRaw", &ImmBlockCodeEvalResultValueJs::setRaw),
                                                                             InstanceMethod("setNode", &ImmBlockCodeEvalResultValueJs::setNode)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeEvalResultValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmBlockCodeEvalResultValue> _stored;
  org::imm::ImmBlockCodeEvalResultValue* getPtr() { return _stored.get(); }
};

struct ImmBlockCodeValueJs : public Napi::ObjectWrap<ImmBlockCodeValueJs> {
  Napi::Value setLang(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockCodeValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmBlockCodeValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmBlockCodeValue::setLang),
                                                         std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  Napi::Value setExports(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockCodeValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmBlockCodeValue::*)(BlockCodeExports const&)>(&org::imm::ImmBlockCodeValue::setExports),
                                                         std::make_tuple(CxxArgSpec<BlockCodeExports>{"value"}));
  }
  Napi::Value setResult(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockCodeValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmBlockCodeValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&)>(&org::imm::ImmBlockCodeValue::setResult),
                                                         std::make_tuple(CxxArgSpec<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>>{"value"}));
  }
  Napi::Value setLines(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockCodeValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmBlockCodeValue::*)(immer::flex_vector<org::sem::BlockCodeLine> const&)>(&org::imm::ImmBlockCodeValue::setLines),
                                                         std::make_tuple(CxxArgSpec<immer::flex_vector<org::sem::BlockCodeLine>>{"value"}));
  }
  Napi::Value setCache(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockCodeValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setCache),
                                                         std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  Napi::Value setEval(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockCodeValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setEval),
                                                         std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  Napi::Value setNoweb(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockCodeValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setNoweb),
                                                         std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  Napi::Value setHlines(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockCodeValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setHlines),
                                                         std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  Napi::Value setTangle(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockCodeValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setTangle),
                                                         std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  Napi::Value setSwitches(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmBlockCodeValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmBlockCodeValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmBlockCodeValue::setSwitches),
                                                         std::make_tuple(CxxArgSpec<org::sem::AttrGroup>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeValueJs", {InstanceMethod("setLang", &ImmBlockCodeValueJs::setLang),
                                                                   InstanceMethod("setExports", &ImmBlockCodeValueJs::setExports),
                                                                   InstanceMethod("setResult", &ImmBlockCodeValueJs::setResult),
                                                                   InstanceMethod("setLines", &ImmBlockCodeValueJs::setLines),
                                                                   InstanceMethod("setCache", &ImmBlockCodeValueJs::setCache),
                                                                   InstanceMethod("setEval", &ImmBlockCodeValueJs::setEval),
                                                                   InstanceMethod("setNoweb", &ImmBlockCodeValueJs::setNoweb),
                                                                   InstanceMethod("setHlines", &ImmBlockCodeValueJs::setHlines),
                                                                   InstanceMethod("setTangle", &ImmBlockCodeValueJs::setTangle),
                                                                   InstanceMethod("setSwitches", &ImmBlockCodeValueJs::setSwitches)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmBlockCodeValue> _stored;
  org::imm::ImmBlockCodeValue* getPtr() { return _stored.get(); }
};

struct ImmSubtreeLogValueJs : public Napi::ObjectWrap<ImmSubtreeLogValueJs> {
  Napi::Value setHead(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeLogValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmSubtreeLogValue::*)(org::sem::SubtreeLogHead const&)>(&org::imm::ImmSubtreeLogValue::setHead),
                                                          std::make_tuple(CxxArgSpec<org::sem::SubtreeLogHead>{"value"}));
  }
  Napi::Value setDesc(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeLogValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmSubtreeLogValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>> const&)>(&org::imm::ImmSubtreeLogValue::setDesc),
                                                          std::make_tuple(CxxArgSpec<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeLogValueJs", {InstanceMethod("setHead", &ImmSubtreeLogValueJs::setHead),
                                                                    InstanceMethod("setDesc", &ImmSubtreeLogValueJs::setDesc)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeLogValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmSubtreeLogValue> _stored;
  org::imm::ImmSubtreeLogValue* getPtr() { return _stored.get(); }
};

struct ImmSubtreeValueJs : public Napi::ObjectWrap<ImmSubtreeValueJs> {
  Napi::Value setLevel(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(int const&)>(&org::imm::ImmSubtreeValue::setLevel),
                                                       std::make_tuple(CxxArgSpec<int>{"value"}));
  }
  Napi::Value setTreeid(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmSubtreeValue::setTreeid),
                                                       std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  Napi::Value setTodo(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmSubtreeValue::setTodo),
                                                       std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  Napi::Value setCompletion(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<org::sem::SubtreeCompletion>> const&)>(&org::imm::ImmSubtreeValue::setCompletion),
                                                       std::make_tuple(CxxArgSpec<immer::box<std::optional<org::sem::SubtreeCompletion>>>{"value"}));
  }
  Napi::Value setDescription(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmSubtreeValue::setDescription),
                                                       std::make_tuple(CxxArgSpec<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>>>{"value"}));
  }
  Napi::Value setTags(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&)>(&org::imm::ImmSubtreeValue::setTags),
                                                       std::make_tuple(CxxArgSpec<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>>>{"value"}));
  }
  Napi::Value setTitle(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(org::imm::ImmIdT<org::imm::ImmParagraph> const&)>(&org::imm::ImmSubtreeValue::setTitle),
                                                       std::make_tuple(CxxArgSpec<org::imm::ImmIdT<org::imm::ImmParagraph>>{"value"}));
  }
  Napi::Value setLogbook(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> const&)>(&org::imm::ImmSubtreeValue::setLogbook),
                                                       std::make_tuple(CxxArgSpec<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmSubtreeLog>>>{"value"}));
  }
  Napi::Value setProperties(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(immer::flex_vector<org::sem::NamedProperty> const&)>(&org::imm::ImmSubtreeValue::setProperties),
                                                       std::make_tuple(CxxArgSpec<immer::flex_vector<org::sem::NamedProperty>>{"value"}));
  }
  Napi::Value setClosed(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<hstd::UserTime>> const&)>(&org::imm::ImmSubtreeValue::setClosed),
                                                       std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::UserTime>>>{"value"}));
  }
  Napi::Value setDeadline(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<hstd::UserTime>> const&)>(&org::imm::ImmSubtreeValue::setDeadline),
                                                       std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::UserTime>>>{"value"}));
  }
  Napi::Value setScheduled(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<hstd::UserTime>> const&)>(&org::imm::ImmSubtreeValue::setScheduled),
                                                       std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::UserTime>>>{"value"}));
  }
  Napi::Value setIscomment(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(bool const&)>(&org::imm::ImmSubtreeValue::setIscomment),
                                                       std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  Napi::Value setIsarchived(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(bool const&)>(&org::imm::ImmSubtreeValue::setIsarchived),
                                                       std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  Napi::Value setPriority(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSubtreeValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmSubtreeValue::setPriority),
                                                       std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeValueJs", {InstanceMethod("setLevel", &ImmSubtreeValueJs::setLevel),
                                                                 InstanceMethod("setTreeid", &ImmSubtreeValueJs::setTreeid),
                                                                 InstanceMethod("setTodo", &ImmSubtreeValueJs::setTodo),
                                                                 InstanceMethod("setCompletion", &ImmSubtreeValueJs::setCompletion),
                                                                 InstanceMethod("setDescription", &ImmSubtreeValueJs::setDescription),
                                                                 InstanceMethod("setTags", &ImmSubtreeValueJs::setTags),
                                                                 InstanceMethod("setTitle", &ImmSubtreeValueJs::setTitle),
                                                                 InstanceMethod("setLogbook", &ImmSubtreeValueJs::setLogbook),
                                                                 InstanceMethod("setProperties", &ImmSubtreeValueJs::setProperties),
                                                                 InstanceMethod("setClosed", &ImmSubtreeValueJs::setClosed),
                                                                 InstanceMethod("setDeadline", &ImmSubtreeValueJs::setDeadline),
                                                                 InstanceMethod("setScheduled", &ImmSubtreeValueJs::setScheduled),
                                                                 InstanceMethod("setIscomment", &ImmSubtreeValueJs::setIscomment),
                                                                 InstanceMethod("setIsarchived", &ImmSubtreeValueJs::setIsarchived),
                                                                 InstanceMethod("setPriority", &ImmSubtreeValueJs::setPriority)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmSubtreeValue> _stored;
  org::imm::ImmSubtreeValue* getPtr() { return _stored.get(); }
};

struct ImmCellValueJs : public Napi::ObjectWrap<ImmCellValueJs> {
  Napi::Value setIsblock(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCellValue, void>(info,
                                                    getPtr(),
                                                    static_cast<void(org::imm::ImmCellValue::*)(bool const&)>(&org::imm::ImmCellValue::setIsblock),
                                                    std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCellValueJs", {InstanceMethod("setIsblock", &ImmCellValueJs::setIsblock)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCellValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCellValue> _stored;
  org::imm::ImmCellValue* getPtr() { return _stored.get(); }
};

struct ImmRowValueJs : public Napi::ObjectWrap<ImmRowValueJs> {
  Napi::Value setCells(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmRowValue, void>(info,
                                                   getPtr(),
                                                   static_cast<void(org::imm::ImmRowValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmCell>> const&)>(&org::imm::ImmRowValue::setCells),
                                                   std::make_tuple(CxxArgSpec<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmCell>>>{"value"}));
  }
  Napi::Value setIsblock(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmRowValue, void>(info,
                                                   getPtr(),
                                                   static_cast<void(org::imm::ImmRowValue::*)(bool const&)>(&org::imm::ImmRowValue::setIsblock),
                                                   std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRowValueJs", {InstanceMethod("setCells", &ImmRowValueJs::setCells),
                                                             InstanceMethod("setIsblock", &ImmRowValueJs::setIsblock)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRowValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmRowValue> _stored;
  org::imm::ImmRowValue* getPtr() { return _stored.get(); }
};

struct ImmTableValueJs : public Napi::ObjectWrap<ImmTableValueJs> {
  Napi::Value setRows(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmTableValue, void>(info,
                                                     getPtr(),
                                                     static_cast<void(org::imm::ImmTableValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmRow>> const&)>(&org::imm::ImmTableValue::setRows),
                                                     std::make_tuple(CxxArgSpec<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmRow>>>{"value"}));
  }
  Napi::Value setIsblock(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmTableValue, void>(info,
                                                     getPtr(),
                                                     static_cast<void(org::imm::ImmTableValue::*)(bool const&)>(&org::imm::ImmTableValue::setIsblock),
                                                     std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTableValueJs", {InstanceMethod("setRows", &ImmTableValueJs::setRows),
                                                               InstanceMethod("setIsblock", &ImmTableValueJs::setIsblock)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTableValueJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmColonExampleValue> _stored;
  org::imm::ImmColonExampleValue* getPtr() { return _stored.get(); }
};

struct ImmCmdAttrValueJs : public Napi::ObjectWrap<ImmCmdAttrValueJs> {
  Napi::Value setTarget(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdAttrValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmCmdAttrValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdAttrValue::setTarget),
                                                       std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdAttrValueJs", {InstanceMethod("setTarget", &ImmCmdAttrValueJs::setTarget)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdAttrValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdAttrValue> _stored;
  org::imm::ImmCmdAttrValue* getPtr() { return _stored.get(); }
};

struct ImmCmdExportValueJs : public Napi::ObjectWrap<ImmCmdExportValueJs> {
  Napi::Value setExporter(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdExportValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmCmdExportValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdExportValue::setExporter),
                                                         std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setContent(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdExportValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmCmdExportValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdExportValue::setContent),
                                                         std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdExportValueJs", {InstanceMethod("setExporter", &ImmCmdExportValueJs::setExporter),
                                                                   InstanceMethod("setContent", &ImmCmdExportValueJs::setContent)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdExportValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdExportValue> _stored;
  org::imm::ImmCmdExportValue* getPtr() { return _stored.get(); }
};

struct ImmCallValueJs : public Napi::ObjectWrap<ImmCallValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCallValue, void>(info,
                                                    getPtr(),
                                                    static_cast<void(org::imm::ImmCallValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCallValue::setName),
                                                    std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setAttrs(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCallValue, void>(info,
                                                    getPtr(),
                                                    static_cast<void(org::imm::ImmCallValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmCallValue::setAttrs),
                                                    std::make_tuple(CxxArgSpec<org::sem::AttrGroup>{"value"}));
  }
  Napi::Value setIscommand(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCallValue, void>(info,
                                                    getPtr(),
                                                    static_cast<void(org::imm::ImmCallValue::*)(bool const&)>(&org::imm::ImmCallValue::setIscommand),
                                                    std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCallValueJs", {InstanceMethod("setName", &ImmCallValueJs::setName),
                                                              InstanceMethod("setAttrs", &ImmCallValueJs::setAttrs),
                                                              InstanceMethod("setIscommand", &ImmCallValueJs::setIscommand)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCallValueJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmListValue> _stored;
  org::imm::ImmListValue* getPtr() { return _stored.get(); }
};

struct ImmListItemValueJs : public Napi::ObjectWrap<ImmListItemValueJs> {
  Napi::Value setCheckbox(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmListItemValue, void>(info,
                                                        getPtr(),
                                                        static_cast<void(org::imm::ImmListItemValue::*)(org::imm::ImmListItem::Checkbox const&)>(&org::imm::ImmListItemValue::setCheckbox),
                                                        std::make_tuple(CxxArgSpec<org::imm::ImmListItem::Checkbox>{"value"}));
  }
  Napi::Value setHeader(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmListItemValue, void>(info,
                                                        getPtr(),
                                                        static_cast<void(org::imm::ImmListItemValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmListItemValue::setHeader),
                                                        std::make_tuple(CxxArgSpec<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>>>{"value"}));
  }
  Napi::Value setBullet(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmListItemValue, void>(info,
                                                        getPtr(),
                                                        static_cast<void(org::imm::ImmListItemValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmListItemValue::setBullet),
                                                        std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListItemValueJs", {InstanceMethod("setCheckbox", &ImmListItemValueJs::setCheckbox),
                                                                  InstanceMethod("setHeader", &ImmListItemValueJs::setHeader),
                                                                  InstanceMethod("setBullet", &ImmListItemValueJs::setBullet)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListItemValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmListItemValue> _stored;
  org::imm::ImmListItemValue* getPtr() { return _stored.get(); }
};

struct ImmDocumentOptionsValueJs : public Napi::ObjectWrap<ImmDocumentOptionsValueJs> {
  Napi::Value setInitialvisibility(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentOptionsValue, void>(info,
                                                               getPtr(),
                                                               static_cast<void(org::imm::ImmDocumentOptionsValue::*)(InitialSubtreeVisibility const&)>(&org::imm::ImmDocumentOptionsValue::setInitialvisibility),
                                                               std::make_tuple(CxxArgSpec<InitialSubtreeVisibility>{"value"}));
  }
  Napi::Value setProperties(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentOptionsValue, void>(info,
                                                               getPtr(),
                                                               static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::flex_vector<org::sem::NamedProperty> const&)>(&org::imm::ImmDocumentOptionsValue::setProperties),
                                                               std::make_tuple(CxxArgSpec<immer::flex_vector<org::sem::NamedProperty>>{"value"}));
  }
  Napi::Value setExportconfig(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentOptionsValue, void>(info,
                                                               getPtr(),
                                                               static_cast<void(org::imm::ImmDocumentOptionsValue::*)(org::sem::DocumentExportConfig const&)>(&org::imm::ImmDocumentOptionsValue::setExportconfig),
                                                               std::make_tuple(CxxArgSpec<org::sem::DocumentExportConfig>{"value"}));
  }
  Napi::Value setFixedwidthsections(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentOptionsValue, void>(info,
                                                               getPtr(),
                                                               static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::box<std::optional<bool>> const&)>(&org::imm::ImmDocumentOptionsValue::setFixedwidthsections),
                                                               std::make_tuple(CxxArgSpec<immer::box<std::optional<bool>>>{"value"}));
  }
  Napi::Value setStartupindented(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentOptionsValue, void>(info,
                                                               getPtr(),
                                                               static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::box<std::optional<bool>> const&)>(&org::imm::ImmDocumentOptionsValue::setStartupindented),
                                                               std::make_tuple(CxxArgSpec<immer::box<std::optional<bool>>>{"value"}));
  }
  Napi::Value setCategory(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentOptionsValue, void>(info,
                                                               getPtr(),
                                                               static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmDocumentOptionsValue::setCategory),
                                                               std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  Napi::Value setSetupfile(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentOptionsValue, void>(info,
                                                               getPtr(),
                                                               static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmDocumentOptionsValue::setSetupfile),
                                                               std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  Napi::Value setMaxsubtreelevelexport(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentOptionsValue, void>(info,
                                                               getPtr(),
                                                               static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::box<std::optional<int>> const&)>(&org::imm::ImmDocumentOptionsValue::setMaxsubtreelevelexport),
                                                               std::make_tuple(CxxArgSpec<immer::box<std::optional<int>>>{"value"}));
  }
  Napi::Value setColumns(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentOptionsValue, void>(info,
                                                               getPtr(),
                                                               static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::box<std::optional<org::sem::ColumnView>> const&)>(&org::imm::ImmDocumentOptionsValue::setColumns),
                                                               std::make_tuple(CxxArgSpec<immer::box<std::optional<org::sem::ColumnView>>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentOptionsValueJs", {InstanceMethod("setInitialvisibility", &ImmDocumentOptionsValueJs::setInitialvisibility),
                                                                         InstanceMethod("setProperties", &ImmDocumentOptionsValueJs::setProperties),
                                                                         InstanceMethod("setExportconfig", &ImmDocumentOptionsValueJs::setExportconfig),
                                                                         InstanceMethod("setFixedwidthsections", &ImmDocumentOptionsValueJs::setFixedwidthsections),
                                                                         InstanceMethod("setStartupindented", &ImmDocumentOptionsValueJs::setStartupindented),
                                                                         InstanceMethod("setCategory", &ImmDocumentOptionsValueJs::setCategory),
                                                                         InstanceMethod("setSetupfile", &ImmDocumentOptionsValueJs::setSetupfile),
                                                                         InstanceMethod("setMaxsubtreelevelexport", &ImmDocumentOptionsValueJs::setMaxsubtreelevelexport),
                                                                         InstanceMethod("setColumns", &ImmDocumentOptionsValueJs::setColumns)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentOptionsValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmDocumentOptionsValue> _stored;
  org::imm::ImmDocumentOptionsValue* getPtr() { return _stored.get(); }
};

struct ImmDocumentFragmentValueJs : public Napi::ObjectWrap<ImmDocumentFragmentValueJs> {
  Napi::Value setBaseline(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentFragmentValue, void>(info,
                                                                getPtr(),
                                                                static_cast<void(org::imm::ImmDocumentFragmentValue::*)(int const&)>(&org::imm::ImmDocumentFragmentValue::setBaseline),
                                                                std::make_tuple(CxxArgSpec<int>{"value"}));
  }
  Napi::Value setBasecol(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentFragmentValue, void>(info,
                                                                getPtr(),
                                                                static_cast<void(org::imm::ImmDocumentFragmentValue::*)(int const&)>(&org::imm::ImmDocumentFragmentValue::setBasecol),
                                                                std::make_tuple(CxxArgSpec<int>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentFragmentValueJs", {InstanceMethod("setBaseline", &ImmDocumentFragmentValueJs::setBaseline),
                                                                          InstanceMethod("setBasecol", &ImmDocumentFragmentValueJs::setBasecol)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentFragmentValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmDocumentFragmentValue> _stored;
  org::imm::ImmDocumentFragmentValue* getPtr() { return _stored.get(); }
};

struct ImmCriticMarkupValueJs : public Napi::ObjectWrap<ImmCriticMarkupValueJs> {
  Napi::Value setKind(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCriticMarkupValue, void>(info,
                                                            getPtr(),
                                                            static_cast<void(org::imm::ImmCriticMarkupValue::*)(org::imm::ImmCriticMarkup::Kind const&)>(&org::imm::ImmCriticMarkupValue::setKind),
                                                            std::make_tuple(CxxArgSpec<org::imm::ImmCriticMarkup::Kind>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCriticMarkupValueJs", {InstanceMethod("setKind", &ImmCriticMarkupValueJs::setKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCriticMarkupValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCriticMarkupValue> _stored;
  org::imm::ImmCriticMarkupValue* getPtr() { return _stored.get(); }
};

struct ImmDocumentValueJs : public Napi::ObjectWrap<ImmDocumentValueJs> {
  Napi::Value setTitle(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentValue, void>(info,
                                                        getPtr(),
                                                        static_cast<void(org::imm::ImmDocumentValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmDocumentValue::setTitle),
                                                        std::make_tuple(CxxArgSpec<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>>>{"value"}));
  }
  Napi::Value setAuthor(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentValue, void>(info,
                                                        getPtr(),
                                                        static_cast<void(org::imm::ImmDocumentValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmDocumentValue::setAuthor),
                                                        std::make_tuple(CxxArgSpec<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>>>{"value"}));
  }
  Napi::Value setCreator(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentValue, void>(info,
                                                        getPtr(),
                                                        static_cast<void(org::imm::ImmDocumentValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmDocumentValue::setCreator),
                                                        std::make_tuple(CxxArgSpec<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>>>{"value"}));
  }
  Napi::Value setFiletags(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentValue, void>(info,
                                                        getPtr(),
                                                        static_cast<void(org::imm::ImmDocumentValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&)>(&org::imm::ImmDocumentValue::setFiletags),
                                                        std::make_tuple(CxxArgSpec<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>>>{"value"}));
  }
  Napi::Value setEmail(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentValue, void>(info,
                                                        getPtr(),
                                                        static_cast<void(org::imm::ImmDocumentValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>> const&)>(&org::imm::ImmDocumentValue::setEmail),
                                                        std::make_tuple(CxxArgSpec<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>>>{"value"}));
  }
  Napi::Value setLanguage(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentValue, void>(info,
                                                        getPtr(),
                                                        static_cast<void(org::imm::ImmDocumentValue::*)(immer::flex_vector<hstd::Str> const&)>(&org::imm::ImmDocumentValue::setLanguage),
                                                        std::make_tuple(CxxArgSpec<immer::flex_vector<hstd::Str>>{"value"}));
  }
  Napi::Value setOptions(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentValue, void>(info,
                                                        getPtr(),
                                                        static_cast<void(org::imm::ImmDocumentValue::*)(org::imm::ImmIdT<org::imm::ImmDocumentOptions> const&)>(&org::imm::ImmDocumentValue::setOptions),
                                                        std::make_tuple(CxxArgSpec<org::imm::ImmIdT<org::imm::ImmDocumentOptions>>{"value"}));
  }
  Napi::Value setExportfilename(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDocumentValue, void>(info,
                                                        getPtr(),
                                                        static_cast<void(org::imm::ImmDocumentValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmDocumentValue::setExportfilename),
                                                        std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentValueJs", {InstanceMethod("setTitle", &ImmDocumentValueJs::setTitle),
                                                                  InstanceMethod("setAuthor", &ImmDocumentValueJs::setAuthor),
                                                                  InstanceMethod("setCreator", &ImmDocumentValueJs::setCreator),
                                                                  InstanceMethod("setFiletags", &ImmDocumentValueJs::setFiletags),
                                                                  InstanceMethod("setEmail", &ImmDocumentValueJs::setEmail),
                                                                  InstanceMethod("setLanguage", &ImmDocumentValueJs::setLanguage),
                                                                  InstanceMethod("setOptions", &ImmDocumentValueJs::setOptions),
                                                                  InstanceMethod("setExportfilename", &ImmDocumentValueJs::setExportfilename)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmDocumentValue> _stored;
  org::imm::ImmDocumentValue* getPtr() { return _stored.get(); }
};

struct ImmFileTargetValueJs : public Napi::ObjectWrap<ImmFileTargetValueJs> {
  Napi::Value setPath(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmFileTargetValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmFileTargetValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmFileTargetValue::setPath),
                                                          std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setLine(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmFileTargetValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmFileTargetValue::*)(immer::box<std::optional<int>> const&)>(&org::imm::ImmFileTargetValue::setLine),
                                                          std::make_tuple(CxxArgSpec<immer::box<std::optional<int>>>{"value"}));
  }
  Napi::Value setSearchtarget(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmFileTargetValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmFileTargetValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmFileTargetValue::setSearchtarget),
                                                          std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  Napi::Value setRestricttoheadlines(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmFileTargetValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmFileTargetValue::*)(bool const&)>(&org::imm::ImmFileTargetValue::setRestricttoheadlines),
                                                          std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  Napi::Value setTargetid(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmFileTargetValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmFileTargetValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmFileTargetValue::setTargetid),
                                                          std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  Napi::Value setRegexp(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmFileTargetValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmFileTargetValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmFileTargetValue::setRegexp),
                                                          std::make_tuple(CxxArgSpec<immer::box<std::optional<hstd::Str>>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileTargetValueJs", {InstanceMethod("setPath", &ImmFileTargetValueJs::setPath),
                                                                    InstanceMethod("setLine", &ImmFileTargetValueJs::setLine),
                                                                    InstanceMethod("setSearchtarget", &ImmFileTargetValueJs::setSearchtarget),
                                                                    InstanceMethod("setRestricttoheadlines", &ImmFileTargetValueJs::setRestricttoheadlines),
                                                                    InstanceMethod("setTargetid", &ImmFileTargetValueJs::setTargetid),
                                                                    InstanceMethod("setRegexp", &ImmFileTargetValueJs::setRegexp)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileTargetValueJs", func);
    return exports;
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
  std::shared_ptr<org::imm::ImmDocumentGroupValue> _stored;
  org::imm::ImmDocumentGroupValue* getPtr() { return _stored.get(); }
};

struct ImmFileValueJs : public Napi::ObjectWrap<ImmFileValueJs> {
  Napi::Value setRelpath(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmFileValue, void>(info,
                                                    getPtr(),
                                                    static_cast<void(org::imm::ImmFileValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmFileValue::setRelpath),
                                                    std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setAbspath(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmFileValue, void>(info,
                                                    getPtr(),
                                                    static_cast<void(org::imm::ImmFileValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmFileValue::setAbspath),
                                                    std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setData(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmFileValue, void>(info,
                                                    getPtr(),
                                                    static_cast<void(org::imm::ImmFileValue::*)(org::imm::ImmFile::Data const&)>(&org::imm::ImmFileValue::setData),
                                                    std::make_tuple(CxxArgSpec<org::imm::ImmFile::Data>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileValueJs", {InstanceMethod("setRelpath", &ImmFileValueJs::setRelpath),
                                                              InstanceMethod("setAbspath", &ImmFileValueJs::setAbspath),
                                                              InstanceMethod("setData", &ImmFileValueJs::setData)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmFileValue> _stored;
  org::imm::ImmFileValue* getPtr() { return _stored.get(); }
};

struct ImmDirectoryValueJs : public Napi::ObjectWrap<ImmDirectoryValueJs> {
  Napi::Value setRelpath(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDirectoryValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmDirectoryValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmDirectoryValue::setRelpath),
                                                         std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setAbspath(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmDirectoryValue, void>(info,
                                                         getPtr(),
                                                         static_cast<void(org::imm::ImmDirectoryValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmDirectoryValue::setAbspath),
                                                         std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDirectoryValueJs", {InstanceMethod("setRelpath", &ImmDirectoryValueJs::setRelpath),
                                                                   InstanceMethod("setAbspath", &ImmDirectoryValueJs::setAbspath)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDirectoryValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmDirectoryValue> _stored;
  org::imm::ImmDirectoryValue* getPtr() { return _stored.get(); }
};

struct ImmSymlinkValueJs : public Napi::ObjectWrap<ImmSymlinkValueJs> {
  Napi::Value setIsdirectory(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSymlinkValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSymlinkValue::*)(bool const&)>(&org::imm::ImmSymlinkValue::setIsdirectory),
                                                       std::make_tuple(CxxArgSpec<bool>{"value"}));
  }
  Napi::Value setAbspath(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmSymlinkValue, void>(info,
                                                       getPtr(),
                                                       static_cast<void(org::imm::ImmSymlinkValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmSymlinkValue::setAbspath),
                                                       std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymlinkValueJs", {InstanceMethod("setIsdirectory", &ImmSymlinkValueJs::setIsdirectory),
                                                                 InstanceMethod("setAbspath", &ImmSymlinkValueJs::setAbspath)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymlinkValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmSymlinkValue> _stored;
  org::imm::ImmSymlinkValue* getPtr() { return _stored.get(); }
};

struct ImmCmdIncludeValueJs : public Napi::ObjectWrap<ImmCmdIncludeValueJs> {
  Napi::Value setPath(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdIncludeValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmCmdIncludeValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdIncludeValue::setPath),
                                                          std::make_tuple(CxxArgSpec<immer::box<hstd::Str>>{"value"}));
  }
  Napi::Value setFirstline(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdIncludeValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmCmdIncludeValue::*)(immer::box<std::optional<int>> const&)>(&org::imm::ImmCmdIncludeValue::setFirstline),
                                                          std::make_tuple(CxxArgSpec<immer::box<std::optional<int>>>{"value"}));
  }
  Napi::Value setLastline(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdIncludeValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmCmdIncludeValue::*)(immer::box<std::optional<int>> const&)>(&org::imm::ImmCmdIncludeValue::setLastline),
                                                          std::make_tuple(CxxArgSpec<immer::box<std::optional<int>>>{"value"}));
  }
  Napi::Value setData(Napi::CallbackInfo const& info) {
    return WrapMethod<org::imm::ImmCmdIncludeValue, void>(info,
                                                          getPtr(),
                                                          static_cast<void(org::imm::ImmCmdIncludeValue::*)(org::imm::ImmCmdInclude::Data const&)>(&org::imm::ImmCmdIncludeValue::setData),
                                                          std::make_tuple(CxxArgSpec<org::imm::ImmCmdInclude::Data>{"value"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdIncludeValueJs", {InstanceMethod("setPath", &ImmCmdIncludeValueJs::setPath),
                                                                    InstanceMethod("setFirstline", &ImmCmdIncludeValueJs::setFirstline),
                                                                    InstanceMethod("setLastline", &ImmCmdIncludeValueJs::setLastline),
                                                                    InstanceMethod("setData", &ImmCmdIncludeValueJs::setData)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdIncludeValueJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmCmdIncludeValue> _stored;
  org::imm::ImmCmdIncludeValue* getPtr() { return _stored.get(); }
};

struct ImmAdapterOrgAPIJs : public Napi::ObjectWrap<ImmAdapterOrgAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterOrgAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterOrgAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterOrgAPI> _stored;
  org::imm::ImmAdapterOrgAPI* getPtr() { return _stored.get(); }
};

struct CmdJs : public Napi::ObjectWrap<CmdJs> {
  Napi::Value getAttrs(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Cmd, hstd::Vec<org::sem::AttrValue>>(info,
                                                                          getPtr(),
                                                                          static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cmd::getAttrs),
                                                                          std::make_tuple(CxxArgSpec<hstd::Opt<hstd::Str>>{"key", std::nullopt}));
  }
  Napi::Value getFirstAttr(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Cmd, hstd::Opt<org::sem::AttrValue>>(info,
                                                                          getPtr(),
                                                                          static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Str const&) const>(&org::sem::Cmd::getFirstAttr),
                                                                          std::make_tuple(CxxArgSpec<hstd::Str>{"kind"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdJs", {InstanceMethod("getAttrs", &CmdJs::getAttrs),
                                                     InstanceMethod("getFirstAttr", &CmdJs::getFirstAttr)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Cmd> _stored;
  org::sem::Cmd* getPtr() { return _stored.get(); }
};

struct CmdCustomRawJs : public Napi::ObjectWrap<CmdCustomRawJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdCustomRaw, OrgSemKind>(info,
                                                               getPtr(),
                                                               static_cast<OrgSemKind(org::sem::CmdCustomRaw::*)() const>(&org::sem::CmdCustomRaw::getKind),
                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCustomRawJs", {InstanceMethod("getKind", &CmdCustomRawJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdCustomRawJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::CmdCustomRaw> _stored;
  org::sem::CmdCustomRaw* getPtr() { return _stored.get(); }
};

struct CmdCustomTextJs : public Napi::ObjectWrap<CmdCustomTextJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdCustomText, OrgSemKind>(info,
                                                                getPtr(),
                                                                static_cast<OrgSemKind(org::sem::CmdCustomText::*)() const>(&org::sem::CmdCustomText::getKind),
                                                                std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCustomTextJs", {InstanceMethod("getKind", &CmdCustomTextJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdCustomTextJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::CmdCustomText> _stored;
  org::sem::CmdCustomText* getPtr() { return _stored.get(); }
};

struct LinkJs : public Napi::ObjectWrap<LinkJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Link, OrgSemKind>(info,
                                                       getPtr(),
                                                       static_cast<OrgSemKind(org::sem::Link::*)() const>(&org::sem::Link::getKind),
                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LinkJs", {InstanceMethod("getKind", &LinkJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("LinkJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Link> _stored;
  org::sem::Link* getPtr() { return _stored.get(); }
};

struct BlockCommentJs : public Napi::ObjectWrap<BlockCommentJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockComment, OrgSemKind>(info,
                                                               getPtr(),
                                                               static_cast<OrgSemKind(org::sem::BlockComment::*)() const>(&org::sem::BlockComment::getKind),
                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCommentJs", {InstanceMethod("getKind", &BlockCommentJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockCommentJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::BlockComment> _stored;
  org::sem::BlockComment* getPtr() { return _stored.get(); }
};

struct ParagraphJs : public Napi::ObjectWrap<ParagraphJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Paragraph, OrgSemKind>(info,
                                                            getPtr(),
                                                            static_cast<OrgSemKind(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getKind),
                                                            std::make_tuple());
  }
  Napi::Value isFootnoteDefinition(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Paragraph, bool>(info,
                                                      getPtr(),
                                                      static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::isFootnoteDefinition),
                                                      std::make_tuple());
  }
  Napi::Value getFootnoteName(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Paragraph, hstd::Opt<hstd::Str>>(info,
                                                                      getPtr(),
                                                                      static_cast<hstd::Opt<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getFootnoteName),
                                                                      std::make_tuple());
  }
  Napi::Value hasAdmonition(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Paragraph, bool>(info,
                                                      getPtr(),
                                                      static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasAdmonition),
                                                      std::make_tuple());
  }
  Napi::Value getAdmonitions(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Paragraph, hstd::Vec<hstd::Str>>(info,
                                                                      getPtr(),
                                                                      static_cast<hstd::Vec<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getAdmonitions),
                                                                      std::make_tuple());
  }
  Napi::Value getAdmonitionNodes(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Paragraph, hstd::Vec<org::sem::SemId<org::sem::BigIdent>>>(info,
                                                                                                getPtr(),
                                                                                                static_cast<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getAdmonitionNodes),
                                                                                                std::make_tuple());
  }
  Napi::Value hasTimestamp(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Paragraph, bool>(info,
                                                      getPtr(),
                                                      static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasTimestamp),
                                                      std::make_tuple());
  }
  Napi::Value getTimestamps(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Paragraph, hstd::Vec<hstd::UserTime>>(info,
                                                                           getPtr(),
                                                                           static_cast<hstd::Vec<hstd::UserTime>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getTimestamps),
                                                                           std::make_tuple());
  }
  Napi::Value getTimestampNodes(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Paragraph, hstd::Vec<org::sem::SemId<org::sem::Time>>>(info,
                                                                                            getPtr(),
                                                                                            static_cast<hstd::Vec<org::sem::SemId<org::sem::Time>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getTimestampNodes),
                                                                                            std::make_tuple());
  }
  Napi::Value hasLeadHashtags(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Paragraph, bool>(info,
                                                      getPtr(),
                                                      static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasLeadHashtags),
                                                      std::make_tuple());
  }
  Napi::Value getLeadHashtags(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Paragraph, hstd::Vec<org::sem::SemId<org::sem::HashTag>>>(info,
                                                                                               getPtr(),
                                                                                               static_cast<hstd::Vec<org::sem::SemId<org::sem::HashTag>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getLeadHashtags),
                                                                                               std::make_tuple());
  }
  Napi::Value getBody(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Paragraph, hstd::Vec<org::sem::SemId<org::sem::Org>>>(info,
                                                                                           getPtr(),
                                                                                           static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getBody),
                                                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ParagraphJs", {InstanceMethod("getKind", &ParagraphJs::getKind),
                                                           InstanceMethod("isFootnoteDefinition", &ParagraphJs::isFootnoteDefinition),
                                                           InstanceMethod("getFootnoteName", &ParagraphJs::getFootnoteName),
                                                           InstanceMethod("hasAdmonition", &ParagraphJs::hasAdmonition),
                                                           InstanceMethod("getAdmonitions", &ParagraphJs::getAdmonitions),
                                                           InstanceMethod("getAdmonitionNodes", &ParagraphJs::getAdmonitionNodes),
                                                           InstanceMethod("hasTimestamp", &ParagraphJs::hasTimestamp),
                                                           InstanceMethod("getTimestamps", &ParagraphJs::getTimestamps),
                                                           InstanceMethod("getTimestampNodes", &ParagraphJs::getTimestampNodes),
                                                           InstanceMethod("hasLeadHashtags", &ParagraphJs::hasLeadHashtags),
                                                           InstanceMethod("getLeadHashtags", &ParagraphJs::getLeadHashtags),
                                                           InstanceMethod("getBody", &ParagraphJs::getBody)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ParagraphJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Paragraph> _stored;
  org::sem::Paragraph* getPtr() { return _stored.get(); }
};

struct ListJs : public Napi::ObjectWrap<ListJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::List, OrgSemKind>(info,
                                                       getPtr(),
                                                       static_cast<OrgSemKind(org::sem::List::*)() const>(&org::sem::List::getKind),
                                                       std::make_tuple());
  }
  Napi::Value getListAttrs(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::List, hstd::Vec<org::sem::AttrValue>>(info,
                                                                           getPtr(),
                                                                           static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::List::*)(hstd::Str const&) const>(&org::sem::List::getListAttrs),
                                                                           std::make_tuple(CxxArgSpec<hstd::Str>{"key"}));
  }
  Napi::Value getListFormattingMode(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::List, ListFormattingMode>(info,
                                                               getPtr(),
                                                               static_cast<ListFormattingMode(org::sem::List::*)() const>(&org::sem::List::getListFormattingMode),
                                                               std::make_tuple());
  }
  Napi::Value isDescriptionList(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::List, bool>(info,
                                                 getPtr(),
                                                 static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isDescriptionList),
                                                 std::make_tuple());
  }
  Napi::Value isNumberedList(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::List, bool>(info,
                                                 getPtr(),
                                                 static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isNumberedList),
                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ListJs", {InstanceMethod("getKind", &ListJs::getKind),
                                                      InstanceMethod("getListAttrs", &ListJs::getListAttrs),
                                                      InstanceMethod("getListFormattingMode", &ListJs::getListFormattingMode),
                                                      InstanceMethod("isDescriptionList", &ListJs::isDescriptionList),
                                                      InstanceMethod("isNumberedList", &ListJs::isNumberedList)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ListJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::List> _stored;
  org::sem::List* getPtr() { return _stored.get(); }
};

struct HashTagJs : public Napi::ObjectWrap<HashTagJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::HashTag, OrgSemKind>(info,
                                                          getPtr(),
                                                          static_cast<OrgSemKind(org::sem::HashTag::*)() const>(&org::sem::HashTag::getKind),
                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "HashTagJs", {InstanceMethod("getKind", &HashTagJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("HashTagJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::HashTag> _stored;
  org::sem::HashTag* getPtr() { return _stored.get(); }
};

struct InlineFootnoteJs : public Napi::ObjectWrap<InlineFootnoteJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::InlineFootnote, OrgSemKind>(info,
                                                                 getPtr(),
                                                                 static_cast<OrgSemKind(org::sem::InlineFootnote::*)() const>(&org::sem::InlineFootnote::getKind),
                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "InlineFootnoteJs", {InstanceMethod("getKind", &InlineFootnoteJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("InlineFootnoteJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::InlineFootnote> _stored;
  org::sem::InlineFootnote* getPtr() { return _stored.get(); }
};

struct InlineExportJs : public Napi::ObjectWrap<InlineExportJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::InlineExport, OrgSemKind>(info,
                                                               getPtr(),
                                                               static_cast<OrgSemKind(org::sem::InlineExport::*)() const>(&org::sem::InlineExport::getKind),
                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "InlineExportJs", {InstanceMethod("getKind", &InlineExportJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("InlineExportJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::InlineExport> _stored;
  org::sem::InlineExport* getPtr() { return _stored.get(); }
};

struct EscapedJs : public Napi::ObjectWrap<EscapedJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Escaped, OrgSemKind>(info,
                                                          getPtr(),
                                                          static_cast<OrgSemKind(org::sem::Escaped::*)() const>(&org::sem::Escaped::getKind),
                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "EscapedJs", {InstanceMethod("getKind", &EscapedJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("EscapedJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Escaped> _stored;
  org::sem::Escaped* getPtr() { return _stored.get(); }
};

struct NewlineJs : public Napi::ObjectWrap<NewlineJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Newline, OrgSemKind>(info,
                                                          getPtr(),
                                                          static_cast<OrgSemKind(org::sem::Newline::*)() const>(&org::sem::Newline::getKind),
                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "NewlineJs", {InstanceMethod("getKind", &NewlineJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("NewlineJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Newline> _stored;
  org::sem::Newline* getPtr() { return _stored.get(); }
};

struct SpaceJs : public Napi::ObjectWrap<SpaceJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Space, OrgSemKind>(info,
                                                        getPtr(),
                                                        static_cast<OrgSemKind(org::sem::Space::*)() const>(&org::sem::Space::getKind),
                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SpaceJs", {InstanceMethod("getKind", &SpaceJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("SpaceJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Space> _stored;
  org::sem::Space* getPtr() { return _stored.get(); }
};

struct WordJs : public Napi::ObjectWrap<WordJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Word, OrgSemKind>(info,
                                                       getPtr(),
                                                       static_cast<OrgSemKind(org::sem::Word::*)() const>(&org::sem::Word::getKind),
                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "WordJs", {InstanceMethod("getKind", &WordJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("WordJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Word> _stored;
  org::sem::Word* getPtr() { return _stored.get(); }
};

struct AtMentionJs : public Napi::ObjectWrap<AtMentionJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::AtMention, OrgSemKind>(info,
                                                            getPtr(),
                                                            static_cast<OrgSemKind(org::sem::AtMention::*)() const>(&org::sem::AtMention::getKind),
                                                            std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AtMentionJs", {InstanceMethod("getKind", &AtMentionJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AtMentionJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::AtMention> _stored;
  org::sem::AtMention* getPtr() { return _stored.get(); }
};

struct RawTextJs : public Napi::ObjectWrap<RawTextJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::RawText, OrgSemKind>(info,
                                                          getPtr(),
                                                          static_cast<OrgSemKind(org::sem::RawText::*)() const>(&org::sem::RawText::getKind),
                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "RawTextJs", {InstanceMethod("getKind", &RawTextJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("RawTextJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::RawText> _stored;
  org::sem::RawText* getPtr() { return _stored.get(); }
};

struct PunctuationJs : public Napi::ObjectWrap<PunctuationJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Punctuation, OrgSemKind>(info,
                                                              getPtr(),
                                                              static_cast<OrgSemKind(org::sem::Punctuation::*)() const>(&org::sem::Punctuation::getKind),
                                                              std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "PunctuationJs", {InstanceMethod("getKind", &PunctuationJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("PunctuationJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Punctuation> _stored;
  org::sem::Punctuation* getPtr() { return _stored.get(); }
};

struct PlaceholderJs : public Napi::ObjectWrap<PlaceholderJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Placeholder, OrgSemKind>(info,
                                                              getPtr(),
                                                              static_cast<OrgSemKind(org::sem::Placeholder::*)() const>(&org::sem::Placeholder::getKind),
                                                              std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "PlaceholderJs", {InstanceMethod("getKind", &PlaceholderJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("PlaceholderJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Placeholder> _stored;
  org::sem::Placeholder* getPtr() { return _stored.get(); }
};

struct BigIdentJs : public Napi::ObjectWrap<BigIdentJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BigIdent, OrgSemKind>(info,
                                                           getPtr(),
                                                           static_cast<OrgSemKind(org::sem::BigIdent::*)() const>(&org::sem::BigIdent::getKind),
                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BigIdentJs", {InstanceMethod("getKind", &BigIdentJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BigIdentJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::BigIdent> _stored;
  org::sem::BigIdent* getPtr() { return _stored.get(); }
};

struct TextTargetJs : public Napi::ObjectWrap<TextTargetJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::TextTarget, OrgSemKind>(info,
                                                             getPtr(),
                                                             static_cast<OrgSemKind(org::sem::TextTarget::*)() const>(&org::sem::TextTarget::getKind),
                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TextTargetJs", {InstanceMethod("getKind", &TextTargetJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("TextTargetJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::TextTarget> _stored;
  org::sem::TextTarget* getPtr() { return _stored.get(); }
};

struct BoldJs : public Napi::ObjectWrap<BoldJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Bold, OrgSemKind>(info,
                                                       getPtr(),
                                                       static_cast<OrgSemKind(org::sem::Bold::*)() const>(&org::sem::Bold::getKind),
                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BoldJs", {InstanceMethod("getKind", &BoldJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BoldJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Bold> _stored;
  org::sem::Bold* getPtr() { return _stored.get(); }
};

struct UnderlineJs : public Napi::ObjectWrap<UnderlineJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Underline, OrgSemKind>(info,
                                                            getPtr(),
                                                            static_cast<OrgSemKind(org::sem::Underline::*)() const>(&org::sem::Underline::getKind),
                                                            std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "UnderlineJs", {InstanceMethod("getKind", &UnderlineJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("UnderlineJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Underline> _stored;
  org::sem::Underline* getPtr() { return _stored.get(); }
};

struct MonospaceJs : public Napi::ObjectWrap<MonospaceJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Monospace, OrgSemKind>(info,
                                                            getPtr(),
                                                            static_cast<OrgSemKind(org::sem::Monospace::*)() const>(&org::sem::Monospace::getKind),
                                                            std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MonospaceJs", {InstanceMethod("getKind", &MonospaceJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MonospaceJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Monospace> _stored;
  org::sem::Monospace* getPtr() { return _stored.get(); }
};

struct MarkQuoteJs : public Napi::ObjectWrap<MarkQuoteJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::MarkQuote, OrgSemKind>(info,
                                                            getPtr(),
                                                            static_cast<OrgSemKind(org::sem::MarkQuote::*)() const>(&org::sem::MarkQuote::getKind),
                                                            std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "MarkQuoteJs", {InstanceMethod("getKind", &MarkQuoteJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("MarkQuoteJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::MarkQuote> _stored;
  org::sem::MarkQuote* getPtr() { return _stored.get(); }
};

struct VerbatimJs : public Napi::ObjectWrap<VerbatimJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Verbatim, OrgSemKind>(info,
                                                           getPtr(),
                                                           static_cast<OrgSemKind(org::sem::Verbatim::*)() const>(&org::sem::Verbatim::getKind),
                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "VerbatimJs", {InstanceMethod("getKind", &VerbatimJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("VerbatimJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Verbatim> _stored;
  org::sem::Verbatim* getPtr() { return _stored.get(); }
};

struct ItalicJs : public Napi::ObjectWrap<ItalicJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Italic, OrgSemKind>(info,
                                                         getPtr(),
                                                         static_cast<OrgSemKind(org::sem::Italic::*)() const>(&org::sem::Italic::getKind),
                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ItalicJs", {InstanceMethod("getKind", &ItalicJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ItalicJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Italic> _stored;
  org::sem::Italic* getPtr() { return _stored.get(); }
};

struct StrikeJs : public Napi::ObjectWrap<StrikeJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Strike, OrgSemKind>(info,
                                                         getPtr(),
                                                         static_cast<OrgSemKind(org::sem::Strike::*)() const>(&org::sem::Strike::getKind),
                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "StrikeJs", {InstanceMethod("getKind", &StrikeJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("StrikeJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Strike> _stored;
  org::sem::Strike* getPtr() { return _stored.get(); }
};

struct ParJs : public Napi::ObjectWrap<ParJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Par, OrgSemKind>(info,
                                                      getPtr(),
                                                      static_cast<OrgSemKind(org::sem::Par::*)() const>(&org::sem::Par::getKind),
                                                      std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ParJs", {InstanceMethod("getKind", &ParJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ParJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Par> _stored;
  org::sem::Par* getPtr() { return _stored.get(); }
};

struct ImmAdapterStmtAPIJs : public Napi::ObjectWrap<ImmAdapterStmtAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterStmtAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterStmtAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterStmtAPI> _stored;
  org::imm::ImmAdapterStmtAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterSubtreeAPIJs : public Napi::ObjectWrap<ImmAdapterSubtreeAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterSubtreeAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterSubtreeAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterSubtreeAPI> _stored;
  org::imm::ImmAdapterSubtreeAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterNoneAPIJs : public Napi::ObjectWrap<ImmAdapterNoneAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterNoneAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterNoneAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterNoneAPI> _stored;
  org::imm::ImmAdapterNoneAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterAttrAPIJs : public Napi::ObjectWrap<ImmAdapterAttrAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterAttrAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterAttrAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterAttrAPI> _stored;
  org::imm::ImmAdapterAttrAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterAttrListAPIJs : public Napi::ObjectWrap<ImmAdapterAttrListAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterAttrListAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterAttrListAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterAttrListAPI> _stored;
  org::imm::ImmAdapterAttrListAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterAttrsAPIJs : public Napi::ObjectWrap<ImmAdapterAttrsAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterAttrsAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterAttrsAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterAttrsAPI> _stored;
  org::imm::ImmAdapterAttrsAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterErrorItemAPIJs : public Napi::ObjectWrap<ImmAdapterErrorItemAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterErrorItemAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterErrorItemAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterErrorItemAPI> _stored;
  org::imm::ImmAdapterErrorItemAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterErrorGroupAPIJs : public Napi::ObjectWrap<ImmAdapterErrorGroupAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterErrorGroupAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterErrorGroupAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterErrorGroupAPI> _stored;
  org::imm::ImmAdapterErrorGroupAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterStmtListAPIJs : public Napi::ObjectWrap<ImmAdapterStmtListAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterStmtListAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterStmtListAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterStmtListAPI> _stored;
  org::imm::ImmAdapterStmtListAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterEmptyAPIJs : public Napi::ObjectWrap<ImmAdapterEmptyAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterEmptyAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterEmptyAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterEmptyAPI> _stored;
  org::imm::ImmAdapterEmptyAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterInlineAPIJs : public Napi::ObjectWrap<ImmAdapterInlineAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterInlineAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterInlineAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterInlineAPI> _stored;
  org::imm::ImmAdapterInlineAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterTimeAPIJs : public Napi::ObjectWrap<ImmAdapterTimeAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterTimeAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterTimeAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterTimeAPI> _stored;
  org::imm::ImmAdapterTimeAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterTimeRangeAPIJs : public Napi::ObjectWrap<ImmAdapterTimeRangeAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterTimeRangeAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterTimeRangeAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterTimeRangeAPI> _stored;
  org::imm::ImmAdapterTimeRangeAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterMacroAPIJs : public Napi::ObjectWrap<ImmAdapterMacroAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterMacroAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterMacroAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterMacroAPI> _stored;
  org::imm::ImmAdapterMacroAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterSymbolAPIJs : public Napi::ObjectWrap<ImmAdapterSymbolAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterSymbolAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterSymbolAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterSymbolAPI> _stored;
  org::imm::ImmAdapterSymbolAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterLeafAPIJs : public Napi::ObjectWrap<ImmAdapterLeafAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterLeafAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterLeafAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterLeafAPI> _stored;
  org::imm::ImmAdapterLeafAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterMarkupAPIJs : public Napi::ObjectWrap<ImmAdapterMarkupAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterMarkupAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterMarkupAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterMarkupAPI> _stored;
  org::imm::ImmAdapterMarkupAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterLatexAPIJs : public Napi::ObjectWrap<ImmAdapterLatexAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterLatexAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterLatexAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterLatexAPI> _stored;
  org::imm::ImmAdapterLatexAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterSubtreeLogAPIJs : public Napi::ObjectWrap<ImmAdapterSubtreeLogAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterSubtreeLogAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterSubtreeLogAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterSubtreeLogAPI> _stored;
  org::imm::ImmAdapterSubtreeLogAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterColonExampleAPIJs : public Napi::ObjectWrap<ImmAdapterColonExampleAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterColonExampleAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterColonExampleAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterColonExampleAPI> _stored;
  org::imm::ImmAdapterColonExampleAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCallAPIJs : public Napi::ObjectWrap<ImmAdapterCallAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCallAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCallAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCallAPI> _stored;
  org::imm::ImmAdapterCallAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterFileAPIJs : public Napi::ObjectWrap<ImmAdapterFileAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterFileAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterFileAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterFileAPI> _stored;
  org::imm::ImmAdapterFileAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterDirectoryAPIJs : public Napi::ObjectWrap<ImmAdapterDirectoryAPIJs> {
  Napi::Value getFsSubnode(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterDirectoryAPI, std::optional<org::imm::ImmAdapter>>(info,
                                                                                                  getPtr(),
                                                                                                  static_cast<std::optional<org::imm::ImmAdapter>(org::imm::ImmAdapterDirectoryAPI::*)(hstd::Str const&, bool) const>(&org::imm::ImmAdapterDirectoryAPI::getFsSubnode),
                                                                                                  std::make_tuple(CxxArgSpec<hstd::Str>{"name"},
                                                                                                                  CxxArgSpec<bool>{"withPath", 1}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterDirectoryAPIJs", {InstanceMethod("getFsSubnode", &ImmAdapterDirectoryAPIJs::getFsSubnode)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterDirectoryAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterDirectoryAPI> _stored;
  org::imm::ImmAdapterDirectoryAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterSymlinkAPIJs : public Napi::ObjectWrap<ImmAdapterSymlinkAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterSymlinkAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterSymlinkAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterSymlinkAPI> _stored;
  org::imm::ImmAdapterSymlinkAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterDocumentFragmentAPIJs : public Napi::ObjectWrap<ImmAdapterDocumentFragmentAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterDocumentFragmentAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterDocumentFragmentAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterDocumentFragmentAPI> _stored;
  org::imm::ImmAdapterDocumentFragmentAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCriticMarkupAPIJs : public Napi::ObjectWrap<ImmAdapterCriticMarkupAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCriticMarkupAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCriticMarkupAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCriticMarkupAPI> _stored;
  org::imm::ImmAdapterCriticMarkupAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterListItemAPIJs : public Napi::ObjectWrap<ImmAdapterListItemAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterListItemAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterListItemAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterListItemAPI> _stored;
  org::imm::ImmAdapterListItemAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterDocumentOptionsAPIJs : public Napi::ObjectWrap<ImmAdapterDocumentOptionsAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterDocumentOptionsAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterDocumentOptionsAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterDocumentOptionsAPI> _stored;
  org::imm::ImmAdapterDocumentOptionsAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterDocumentAPIJs : public Napi::ObjectWrap<ImmAdapterDocumentAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterDocumentAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterDocumentAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterDocumentAPI> _stored;
  org::imm::ImmAdapterDocumentAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterFileTargetAPIJs : public Napi::ObjectWrap<ImmAdapterFileTargetAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterFileTargetAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterFileTargetAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterFileTargetAPI> _stored;
  org::imm::ImmAdapterFileTargetAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterTextSeparatorAPIJs : public Napi::ObjectWrap<ImmAdapterTextSeparatorAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterTextSeparatorAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterTextSeparatorAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterTextSeparatorAPI> _stored;
  org::imm::ImmAdapterTextSeparatorAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdIncludeAPIJs : public Napi::ObjectWrap<ImmAdapterCmdIncludeAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdIncludeAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdIncludeAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdIncludeAPI> _stored;
  org::imm::ImmAdapterCmdIncludeAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterDocumentGroupAPIJs : public Napi::ObjectWrap<ImmAdapterDocumentGroupAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterDocumentGroupAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterDocumentGroupAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterDocumentGroupAPI> _stored;
  org::imm::ImmAdapterDocumentGroupAPI* getPtr() { return _stored.get(); }
};

struct BlockJs : public Napi::ObjectWrap<BlockJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Block> _stored;
  org::sem::Block* getPtr() { return _stored.get(); }
};

struct LineCommandJs : public Napi::ObjectWrap<LineCommandJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "LineCommandJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("LineCommandJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::LineCommand> _stored;
  org::sem::LineCommand* getPtr() { return _stored.get(); }
};

struct CmdCustomArgsJs : public Napi::ObjectWrap<CmdCustomArgsJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdCustomArgs, OrgSemKind>(info,
                                                                getPtr(),
                                                                static_cast<OrgSemKind(org::sem::CmdCustomArgs::*)() const>(&org::sem::CmdCustomArgs::getKind),
                                                                std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCustomArgsJs", {InstanceMethod("getKind", &CmdCustomArgsJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdCustomArgsJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::CmdCustomArgs> _stored;
  org::sem::CmdCustomArgs* getPtr() { return _stored.get(); }
};

struct CmdTblfmJs : public Napi::ObjectWrap<CmdTblfmJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdTblfm, OrgSemKind>(info,
                                                           getPtr(),
                                                           static_cast<OrgSemKind(org::sem::CmdTblfm::*)() const>(&org::sem::CmdTblfm::getKind),
                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdTblfmJs", {InstanceMethod("getKind", &CmdTblfmJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdTblfmJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::CmdTblfm> _stored;
  org::sem::CmdTblfm* getPtr() { return _stored.get(); }
};

struct CellJs : public Napi::ObjectWrap<CellJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Cell, OrgSemKind>(info,
                                                       getPtr(),
                                                       static_cast<OrgSemKind(org::sem::Cell::*)() const>(&org::sem::Cell::getKind),
                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CellJs", {InstanceMethod("getKind", &CellJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CellJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Cell> _stored;
  org::sem::Cell* getPtr() { return _stored.get(); }
};

struct RowJs : public Napi::ObjectWrap<RowJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Row, OrgSemKind>(info,
                                                      getPtr(),
                                                      static_cast<OrgSemKind(org::sem::Row::*)() const>(&org::sem::Row::getKind),
                                                      std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "RowJs", {InstanceMethod("getKind", &RowJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("RowJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Row> _stored;
  org::sem::Row* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdAPIJs : public Napi::ObjectWrap<ImmAdapterCmdAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdAPI> _stored;
  org::imm::ImmAdapterCmdAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdCustomRawAPIJs : public Napi::ObjectWrap<ImmAdapterCmdCustomRawAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdCustomRawAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdCustomRawAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdCustomRawAPI> _stored;
  org::imm::ImmAdapterCmdCustomRawAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdCustomTextAPIJs : public Napi::ObjectWrap<ImmAdapterCmdCustomTextAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdCustomTextAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdCustomTextAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdCustomTextAPI> _stored;
  org::imm::ImmAdapterCmdCustomTextAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterLinkAPIJs : public Napi::ObjectWrap<ImmAdapterLinkAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterLinkAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterLinkAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterLinkAPI> _stored;
  org::imm::ImmAdapterLinkAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterBlockCommentAPIJs : public Napi::ObjectWrap<ImmAdapterBlockCommentAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBlockCommentAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBlockCommentAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBlockCommentAPI> _stored;
  org::imm::ImmAdapterBlockCommentAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterParagraphAPIJs : public Napi::ObjectWrap<ImmAdapterParagraphAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterParagraphAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterParagraphAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterParagraphAPI> _stored;
  org::imm::ImmAdapterParagraphAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterListAPIJs : public Napi::ObjectWrap<ImmAdapterListAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterListAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterListAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterListAPI> _stored;
  org::imm::ImmAdapterListAPI* getPtr() { return _stored.get(); }
};

struct ImmSubtreeAdapter : public Napi::ObjectWrap<ImmSubtreeAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmSubtree>, org::imm::ImmSubtreeValueRead>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<org::imm::ImmSubtreeValueRead(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getValue),
                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeAdapter", {InstanceMethod("getValue", &ImmSubtreeAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSubtree>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSubtree>* getPtr() { return _stored.get(); }
};

struct ImmNoneAdapter : public Napi::ObjectWrap<ImmNoneAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmNone>, org::imm::ImmNoneValueRead>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::imm::ImmNoneValueRead(org::imm::ImmAdapterT<org::imm::ImmNone>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmNone>::getValue),
                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNoneAdapter", {InstanceMethod("getValue", &ImmNoneAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNoneAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmNone>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmNone>* getPtr() { return _stored.get(); }
};

struct ImmErrorItemAdapter : public Napi::ObjectWrap<ImmErrorItemAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmErrorItem>, org::imm::ImmErrorItemValueRead>(info,
                                                                                                           getPtr(),
                                                                                                           static_cast<org::imm::ImmErrorItemValueRead(org::imm::ImmAdapterT<org::imm::ImmErrorItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorItem>::getValue),
                                                                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorItemAdapter", {InstanceMethod("getValue", &ImmErrorItemAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorItemAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmErrorItem>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmErrorItem>* getPtr() { return _stored.get(); }
};

struct ImmErrorGroupAdapter : public Napi::ObjectWrap<ImmErrorGroupAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>, org::imm::ImmErrorGroupValueRead>(info,
                                                                                                             getPtr(),
                                                                                                             static_cast<org::imm::ImmErrorGroupValueRead(org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::getValue),
                                                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmErrorGroupAdapter", {InstanceMethod("getValue", &ImmErrorGroupAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmErrorGroupAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmErrorGroup>* getPtr() { return _stored.get(); }
};

struct ImmStmtListAdapter : public Napi::ObjectWrap<ImmStmtListAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmStmtList>, org::imm::ImmStmtListValueRead>(info,
                                                                                                         getPtr(),
                                                                                                         static_cast<org::imm::ImmStmtListValueRead(org::imm::ImmAdapterT<org::imm::ImmStmtList>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmStmtList>::getValue),
                                                                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStmtListAdapter", {InstanceMethod("getValue", &ImmStmtListAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStmtListAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmStmtList>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmStmtList>* getPtr() { return _stored.get(); }
};

struct ImmEmptyAdapter : public Napi::ObjectWrap<ImmEmptyAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmEmpty>, org::imm::ImmEmptyValueRead>(info,
                                                                                                   getPtr(),
                                                                                                   static_cast<org::imm::ImmEmptyValueRead(org::imm::ImmAdapterT<org::imm::ImmEmpty>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmEmpty>::getValue),
                                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEmptyAdapter", {InstanceMethod("getValue", &ImmEmptyAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEmptyAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmEmpty>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmEmpty>* getPtr() { return _stored.get(); }
};

struct ImmAdapterHashTagAPIJs : public Napi::ObjectWrap<ImmAdapterHashTagAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterHashTagAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterHashTagAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterHashTagAPI> _stored;
  org::imm::ImmAdapterHashTagAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterInlineFootnoteAPIJs : public Napi::ObjectWrap<ImmAdapterInlineFootnoteAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterInlineFootnoteAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterInlineFootnoteAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterInlineFootnoteAPI> _stored;
  org::imm::ImmAdapterInlineFootnoteAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterSubtreeCompletionAPIJs : public Napi::ObjectWrap<ImmAdapterSubtreeCompletionAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterSubtreeCompletionAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterSubtreeCompletionAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterSubtreeCompletionAPI> _stored;
  org::imm::ImmAdapterSubtreeCompletionAPI* getPtr() { return _stored.get(); }
};

struct ImmTimeAdapter : public Napi::ObjectWrap<ImmTimeAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmTime>, org::imm::ImmTimeValueRead>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::imm::ImmTimeValueRead(org::imm::ImmAdapterT<org::imm::ImmTime>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTime>::getValue),
                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeAdapter", {InstanceMethod("getValue", &ImmTimeAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTime>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTime>* getPtr() { return _stored.get(); }
};

struct ImmTimeRangeAdapter : public Napi::ObjectWrap<ImmTimeRangeAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmTimeRange>, org::imm::ImmTimeRangeValueRead>(info,
                                                                                                           getPtr(),
                                                                                                           static_cast<org::imm::ImmTimeRangeValueRead(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getValue),
                                                                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTimeRangeAdapter", {InstanceMethod("getValue", &ImmTimeRangeAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTimeRangeAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTimeRange>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTimeRange>* getPtr() { return _stored.get(); }
};

struct ImmMacroAdapter : public Napi::ObjectWrap<ImmMacroAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmMacro>, org::imm::ImmMacroValueRead>(info,
                                                                                                   getPtr(),
                                                                                                   static_cast<org::imm::ImmMacroValueRead(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getValue),
                                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMacroAdapter", {InstanceMethod("getValue", &ImmMacroAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMacroAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmMacro>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmMacro>* getPtr() { return _stored.get(); }
};

struct ImmSymbolAdapter : public Napi::ObjectWrap<ImmSymbolAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmSymbol>, org::imm::ImmSymbolValueRead>(info,
                                                                                                     getPtr(),
                                                                                                     static_cast<org::imm::ImmSymbolValueRead(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getValue),
                                                                                                     std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymbolAdapter", {InstanceMethod("getValue", &ImmSymbolAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymbolAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSymbol>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSymbol>* getPtr() { return _stored.get(); }
};

struct ImmAdapterEscapedAPIJs : public Napi::ObjectWrap<ImmAdapterEscapedAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterEscapedAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterEscapedAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterEscapedAPI> _stored;
  org::imm::ImmAdapterEscapedAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterNewlineAPIJs : public Napi::ObjectWrap<ImmAdapterNewlineAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterNewlineAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterNewlineAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterNewlineAPI> _stored;
  org::imm::ImmAdapterNewlineAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterSpaceAPIJs : public Napi::ObjectWrap<ImmAdapterSpaceAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterSpaceAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterSpaceAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterSpaceAPI> _stored;
  org::imm::ImmAdapterSpaceAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterWordAPIJs : public Napi::ObjectWrap<ImmAdapterWordAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterWordAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterWordAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterWordAPI> _stored;
  org::imm::ImmAdapterWordAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterAtMentionAPIJs : public Napi::ObjectWrap<ImmAdapterAtMentionAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterAtMentionAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterAtMentionAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterAtMentionAPI> _stored;
  org::imm::ImmAdapterAtMentionAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterRawTextAPIJs : public Napi::ObjectWrap<ImmAdapterRawTextAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterRawTextAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterRawTextAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterRawTextAPI> _stored;
  org::imm::ImmAdapterRawTextAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterPunctuationAPIJs : public Napi::ObjectWrap<ImmAdapterPunctuationAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterPunctuationAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterPunctuationAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterPunctuationAPI> _stored;
  org::imm::ImmAdapterPunctuationAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterPlaceholderAPIJs : public Napi::ObjectWrap<ImmAdapterPlaceholderAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterPlaceholderAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterPlaceholderAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterPlaceholderAPI> _stored;
  org::imm::ImmAdapterPlaceholderAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterBigIdentAPIJs : public Napi::ObjectWrap<ImmAdapterBigIdentAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBigIdentAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBigIdentAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBigIdentAPI> _stored;
  org::imm::ImmAdapterBigIdentAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterTextTargetAPIJs : public Napi::ObjectWrap<ImmAdapterTextTargetAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterTextTargetAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterTextTargetAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterTextTargetAPI> _stored;
  org::imm::ImmAdapterTextTargetAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterBoldAPIJs : public Napi::ObjectWrap<ImmAdapterBoldAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBoldAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBoldAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBoldAPI> _stored;
  org::imm::ImmAdapterBoldAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterUnderlineAPIJs : public Napi::ObjectWrap<ImmAdapterUnderlineAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterUnderlineAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterUnderlineAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterUnderlineAPI> _stored;
  org::imm::ImmAdapterUnderlineAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterMonospaceAPIJs : public Napi::ObjectWrap<ImmAdapterMonospaceAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterMonospaceAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterMonospaceAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterMonospaceAPI> _stored;
  org::imm::ImmAdapterMonospaceAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterMarkQuoteAPIJs : public Napi::ObjectWrap<ImmAdapterMarkQuoteAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterMarkQuoteAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterMarkQuoteAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterMarkQuoteAPI> _stored;
  org::imm::ImmAdapterMarkQuoteAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterRadioTargetAPIJs : public Napi::ObjectWrap<ImmAdapterRadioTargetAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterRadioTargetAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterRadioTargetAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterRadioTargetAPI> _stored;
  org::imm::ImmAdapterRadioTargetAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterVerbatimAPIJs : public Napi::ObjectWrap<ImmAdapterVerbatimAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterVerbatimAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterVerbatimAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterVerbatimAPI> _stored;
  org::imm::ImmAdapterVerbatimAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterItalicAPIJs : public Napi::ObjectWrap<ImmAdapterItalicAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterItalicAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterItalicAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterItalicAPI> _stored;
  org::imm::ImmAdapterItalicAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterStrikeAPIJs : public Napi::ObjectWrap<ImmAdapterStrikeAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterStrikeAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterStrikeAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterStrikeAPI> _stored;
  org::imm::ImmAdapterStrikeAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterParAPIJs : public Napi::ObjectWrap<ImmAdapterParAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterParAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterParAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterParAPI> _stored;
  org::imm::ImmAdapterParAPI* getPtr() { return _stored.get(); }
};

struct ImmLatexAdapter : public Napi::ObjectWrap<ImmLatexAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmLatex>, org::imm::ImmLatexValueRead>(info,
                                                                                                   getPtr(),
                                                                                                   static_cast<org::imm::ImmLatexValueRead(org::imm::ImmAdapterT<org::imm::ImmLatex>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLatex>::getValue),
                                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLatexAdapter", {InstanceMethod("getValue", &ImmLatexAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLatexAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmLatex>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmLatex>* getPtr() { return _stored.get(); }
};

struct ImmSubtreeLogAdapter : public Napi::ObjectWrap<ImmSubtreeLogAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>, org::imm::ImmSubtreeLogValueRead>(info,
                                                                                                             getPtr(),
                                                                                                             static_cast<org::imm::ImmSubtreeLogValueRead(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getValue),
                                                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSubtreeLogAdapter", {InstanceMethod("getValue", &ImmSubtreeLogAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSubtreeLogAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>* getPtr() { return _stored.get(); }
};

struct ImmColonExampleAdapter : public Napi::ObjectWrap<ImmColonExampleAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmColonExample>, org::imm::ImmColonExampleValueRead>(info,
                                                                                                                 getPtr(),
                                                                                                                 static_cast<org::imm::ImmColonExampleValueRead(org::imm::ImmAdapterT<org::imm::ImmColonExample>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmColonExample>::getValue),
                                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmColonExampleAdapter", {InstanceMethod("getValue", &ImmColonExampleAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmColonExampleAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmColonExample>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmColonExample>* getPtr() { return _stored.get(); }
};

struct ImmCallAdapter : public Napi::ObjectWrap<ImmCallAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCall>, org::imm::ImmCallValueRead>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::imm::ImmCallValueRead(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getValue),
                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCallAdapter", {InstanceMethod("getValue", &ImmCallAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCallAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCall>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCall>* getPtr() { return _stored.get(); }
};

struct ImmFileAdapter : public Napi::ObjectWrap<ImmFileAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmFile>, org::imm::ImmFileValueRead>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::imm::ImmFileValueRead(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getValue),
                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileAdapter", {InstanceMethod("getValue", &ImmFileAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmFile>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmFile>* getPtr() { return _stored.get(); }
};

struct ImmDirectoryAdapter : public Napi::ObjectWrap<ImmDirectoryAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmDirectory>, org::imm::ImmDirectoryValueRead>(info,
                                                                                                           getPtr(),
                                                                                                           static_cast<org::imm::ImmDirectoryValueRead(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getValue),
                                                                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDirectoryAdapter", {InstanceMethod("getValue", &ImmDirectoryAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDirectoryAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDirectory>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDirectory>* getPtr() { return _stored.get(); }
};

struct ImmSymlinkAdapter : public Napi::ObjectWrap<ImmSymlinkAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmSymlink>, org::imm::ImmSymlinkValueRead>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<org::imm::ImmSymlinkValueRead(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getValue),
                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSymlinkAdapter", {InstanceMethod("getValue", &ImmSymlinkAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSymlinkAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSymlink>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSymlink>* getPtr() { return _stored.get(); }
};

struct ImmDocumentFragmentAdapter : public Napi::ObjectWrap<ImmDocumentFragmentAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>, org::imm::ImmDocumentFragmentValueRead>(info,
                                                                                                                         getPtr(),
                                                                                                                         static_cast<org::imm::ImmDocumentFragmentValueRead(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getValue),
                                                                                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentFragmentAdapter", {InstanceMethod("getValue", &ImmDocumentFragmentAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentFragmentAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>* getPtr() { return _stored.get(); }
};

struct ImmCriticMarkupAdapter : public Napi::ObjectWrap<ImmCriticMarkupAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>, org::imm::ImmCriticMarkupValueRead>(info,
                                                                                                                 getPtr(),
                                                                                                                 static_cast<org::imm::ImmCriticMarkupValueRead(org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::getValue),
                                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCriticMarkupAdapter", {InstanceMethod("getValue", &ImmCriticMarkupAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCriticMarkupAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>* getPtr() { return _stored.get(); }
};

struct ImmListItemAdapter : public Napi::ObjectWrap<ImmListItemAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmListItem>, org::imm::ImmListItemValueRead>(info,
                                                                                                         getPtr(),
                                                                                                         static_cast<org::imm::ImmListItemValueRead(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getValue),
                                                                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListItemAdapter", {InstanceMethod("getValue", &ImmListItemAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListItemAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmListItem>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmListItem>* getPtr() { return _stored.get(); }
};

struct ImmDocumentOptionsAdapter : public Napi::ObjectWrap<ImmDocumentOptionsAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>, org::imm::ImmDocumentOptionsValueRead>(info,
                                                                                                                       getPtr(),
                                                                                                                       static_cast<org::imm::ImmDocumentOptionsValueRead(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getValue),
                                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentOptionsAdapter", {InstanceMethod("getValue", &ImmDocumentOptionsAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentOptionsAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>* getPtr() { return _stored.get(); }
};

struct ImmDocumentAdapter : public Napi::ObjectWrap<ImmDocumentAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmDocument>, org::imm::ImmDocumentValueRead>(info,
                                                                                                         getPtr(),
                                                                                                         static_cast<org::imm::ImmDocumentValueRead(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getValue),
                                                                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentAdapter", {InstanceMethod("getValue", &ImmDocumentAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocument>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDocument>* getPtr() { return _stored.get(); }
};

struct ImmFileTargetAdapter : public Napi::ObjectWrap<ImmFileTargetAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmFileTarget>, org::imm::ImmFileTargetValueRead>(info,
                                                                                                             getPtr(),
                                                                                                             static_cast<org::imm::ImmFileTargetValueRead(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getValue),
                                                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmFileTargetAdapter", {InstanceMethod("getValue", &ImmFileTargetAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmFileTargetAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmFileTarget>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmFileTarget>* getPtr() { return _stored.get(); }
};

struct ImmTextSeparatorAdapter : public Napi::ObjectWrap<ImmTextSeparatorAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>, org::imm::ImmTextSeparatorValueRead>(info,
                                                                                                                   getPtr(),
                                                                                                                   static_cast<org::imm::ImmTextSeparatorValueRead(org::imm::ImmAdapterT<org::imm::ImmTextSeparator>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTextSeparator>::getValue),
                                                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextSeparatorAdapter", {InstanceMethod("getValue", &ImmTextSeparatorAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextSeparatorAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTextSeparator>* getPtr() { return _stored.get(); }
};

struct ImmCmdIncludeAdapter : public Napi::ObjectWrap<ImmCmdIncludeAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>, org::imm::ImmCmdIncludeValueRead>(info,
                                                                                                             getPtr(),
                                                                                                             static_cast<org::imm::ImmCmdIncludeValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getValue),
                                                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdIncludeAdapter", {InstanceMethod("getValue", &ImmCmdIncludeAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdIncludeAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdInclude>* getPtr() { return _stored.get(); }
};

struct ImmDocumentGroupAdapter : public Napi::ObjectWrap<ImmDocumentGroupAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>, org::imm::ImmDocumentGroupValueRead>(info,
                                                                                                                   getPtr(),
                                                                                                                   static_cast<org::imm::ImmDocumentGroupValueRead(org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>::getValue),
                                                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmDocumentGroupAdapter", {InstanceMethod("getValue", &ImmDocumentGroupAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmDocumentGroupAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>* getPtr() { return _stored.get(); }
};

struct BlockCenterJs : public Napi::ObjectWrap<BlockCenterJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockCenter, OrgSemKind>(info,
                                                              getPtr(),
                                                              static_cast<OrgSemKind(org::sem::BlockCenter::*)() const>(&org::sem::BlockCenter::getKind),
                                                              std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCenterJs", {InstanceMethod("getKind", &BlockCenterJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockCenterJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::BlockCenter> _stored;
  org::sem::BlockCenter* getPtr() { return _stored.get(); }
};

struct BlockQuoteJs : public Napi::ObjectWrap<BlockQuoteJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockQuote, OrgSemKind>(info,
                                                             getPtr(),
                                                             static_cast<OrgSemKind(org::sem::BlockQuote::*)() const>(&org::sem::BlockQuote::getKind),
                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockQuoteJs", {InstanceMethod("getKind", &BlockQuoteJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockQuoteJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::BlockQuote> _stored;
  org::sem::BlockQuote* getPtr() { return _stored.get(); }
};

struct BlockVerseJs : public Napi::ObjectWrap<BlockVerseJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockVerse, OrgSemKind>(info,
                                                             getPtr(),
                                                             static_cast<OrgSemKind(org::sem::BlockVerse::*)() const>(&org::sem::BlockVerse::getKind),
                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockVerseJs", {InstanceMethod("getKind", &BlockVerseJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockVerseJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::BlockVerse> _stored;
  org::sem::BlockVerse* getPtr() { return _stored.get(); }
};

struct BlockDynamicFallbackJs : public Napi::ObjectWrap<BlockDynamicFallbackJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockDynamicFallback, OrgSemKind>(info,
                                                                       getPtr(),
                                                                       static_cast<OrgSemKind(org::sem::BlockDynamicFallback::*)() const>(&org::sem::BlockDynamicFallback::getKind),
                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockDynamicFallbackJs", {InstanceMethod("getKind", &BlockDynamicFallbackJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockDynamicFallbackJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::BlockDynamicFallback> _stored;
  org::sem::BlockDynamicFallback* getPtr() { return _stored.get(); }
};

struct BlockExampleJs : public Napi::ObjectWrap<BlockExampleJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockExample, OrgSemKind>(info,
                                                               getPtr(),
                                                               static_cast<OrgSemKind(org::sem::BlockExample::*)() const>(&org::sem::BlockExample::getKind),
                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockExampleJs", {InstanceMethod("getKind", &BlockExampleJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockExampleJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::BlockExample> _stored;
  org::sem::BlockExample* getPtr() { return _stored.get(); }
};

struct BlockExportJs : public Napi::ObjectWrap<BlockExportJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockExport, OrgSemKind>(info,
                                                              getPtr(),
                                                              static_cast<OrgSemKind(org::sem::BlockExport::*)() const>(&org::sem::BlockExport::getKind),
                                                              std::make_tuple());
  }
  Napi::Value getPlacement(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockExport, hstd::Opt<hstd::Str>>(info,
                                                                        getPtr(),
                                                                        static_cast<hstd::Opt<hstd::Str>(org::sem::BlockExport::*)() const>(&org::sem::BlockExport::getPlacement),
                                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockExportJs", {InstanceMethod("getKind", &BlockExportJs::getKind),
                                                             InstanceMethod("getPlacement", &BlockExportJs::getPlacement)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockExportJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::BlockExport> _stored;
  org::sem::BlockExport* getPtr() { return _stored.get(); }
};

struct BlockAdmonitionJs : public Napi::ObjectWrap<BlockAdmonitionJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockAdmonition, OrgSemKind>(info,
                                                                  getPtr(),
                                                                  static_cast<OrgSemKind(org::sem::BlockAdmonition::*)() const>(&org::sem::BlockAdmonition::getKind),
                                                                  std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockAdmonitionJs", {InstanceMethod("getKind", &BlockAdmonitionJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockAdmonitionJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::BlockAdmonition> _stored;
  org::sem::BlockAdmonition* getPtr() { return _stored.get(); }
};

struct BlockCodeEvalResultJs : public Napi::ObjectWrap<BlockCodeEvalResultJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockCodeEvalResult, OrgSemKind>(info,
                                                                      getPtr(),
                                                                      static_cast<OrgSemKind(org::sem::BlockCodeEvalResult::*)() const>(&org::sem::BlockCodeEvalResult::getKind),
                                                                      std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCodeEvalResultJs", {InstanceMethod("getKind", &BlockCodeEvalResultJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockCodeEvalResultJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::BlockCodeEvalResult> _stored;
  org::sem::BlockCodeEvalResult* getPtr() { return _stored.get(); }
};

struct BlockCodeJs : public Napi::ObjectWrap<BlockCodeJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockCode, OrgSemKind>(info,
                                                            getPtr(),
                                                            static_cast<OrgSemKind(org::sem::BlockCode::*)() const>(&org::sem::BlockCode::getKind),
                                                            std::make_tuple());
  }
  Napi::Value getVariable(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::BlockCode, hstd::Opt<org::sem::AttrValue>>(info,
                                                                                getPtr(),
                                                                                static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCode::*)(hstd::Str const&) const>(&org::sem::BlockCode::getVariable),
                                                                                std::make_tuple(CxxArgSpec<hstd::Str>{"varname"}));
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "BlockCodeJs", {InstanceMethod("getKind", &BlockCodeJs::getKind),
                                                           InstanceMethod("getVariable", &BlockCodeJs::getVariable)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("BlockCodeJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::BlockCode> _stored;
  org::sem::BlockCode* getPtr() { return _stored.get(); }
};

struct TableJs : public Napi::ObjectWrap<TableJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::Table, OrgSemKind>(info,
                                                        getPtr(),
                                                        static_cast<OrgSemKind(org::sem::Table::*)() const>(&org::sem::Table::getKind),
                                                        std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "TableJs", {InstanceMethod("getKind", &TableJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("TableJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Table> _stored;
  org::sem::Table* getPtr() { return _stored.get(); }
};

struct AttachedJs : public Napi::ObjectWrap<AttachedJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "AttachedJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("AttachedJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::Attached> _stored;
  org::sem::Attached* getPtr() { return _stored.get(); }
};

struct ImmAdapterLineCommandAPIJs : public Napi::ObjectWrap<ImmAdapterLineCommandAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterLineCommandAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterLineCommandAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterLineCommandAPI> _stored;
  org::imm::ImmAdapterLineCommandAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdCustomArgsAPIJs : public Napi::ObjectWrap<ImmAdapterCmdCustomArgsAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdCustomArgsAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdCustomArgsAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdCustomArgsAPI> _stored;
  org::imm::ImmAdapterCmdCustomArgsAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdTblfmAPIJs : public Napi::ObjectWrap<ImmAdapterCmdTblfmAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdTblfmAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdTblfmAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdTblfmAPI> _stored;
  org::imm::ImmAdapterCmdTblfmAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterBlockAPIJs : public Napi::ObjectWrap<ImmAdapterBlockAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBlockAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBlockAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBlockAPI> _stored;
  org::imm::ImmAdapterBlockAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCellAPIJs : public Napi::ObjectWrap<ImmAdapterCellAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCellAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCellAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCellAPI> _stored;
  org::imm::ImmAdapterCellAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterRowAPIJs : public Napi::ObjectWrap<ImmAdapterRowAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterRowAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterRowAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterRowAPI> _stored;
  org::imm::ImmAdapterRowAPI* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomRawAdapter : public Napi::ObjectWrap<ImmCmdCustomRawAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>, org::imm::ImmCmdCustomRawValueRead>(info,
                                                                                                                 getPtr(),
                                                                                                                 static_cast<org::imm::ImmCmdCustomRawValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getValue),
                                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomRawAdapter", {InstanceMethod("getValue", &ImmCmdCustomRawAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomRawAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomTextAdapter : public Napi::ObjectWrap<ImmCmdCustomTextAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>, org::imm::ImmCmdCustomTextValueRead>(info,
                                                                                                                   getPtr(),
                                                                                                                   static_cast<org::imm::ImmCmdCustomTextValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getValue),
                                                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomTextAdapter", {InstanceMethod("getValue", &ImmCmdCustomTextAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomTextAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>* getPtr() { return _stored.get(); }
};

struct ImmLinkAdapter : public Napi::ObjectWrap<ImmLinkAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmLink>, org::imm::ImmLinkValueRead>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::imm::ImmLinkValueRead(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getValue),
                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmLinkAdapter", {InstanceMethod("getValue", &ImmLinkAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmLinkAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmLink>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmLink>* getPtr() { return _stored.get(); }
};

struct ImmBlockCommentAdapter : public Napi::ObjectWrap<ImmBlockCommentAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmBlockComment>, org::imm::ImmBlockCommentValueRead>(info,
                                                                                                                 getPtr(),
                                                                                                                 static_cast<org::imm::ImmBlockCommentValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockComment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockComment>::getValue),
                                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCommentAdapter", {InstanceMethod("getValue", &ImmBlockCommentAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCommentAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockComment>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockComment>* getPtr() { return _stored.get(); }
};

struct ImmParagraphAdapter : public Napi::ObjectWrap<ImmParagraphAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmParagraph>, org::imm::ImmParagraphValueRead>(info,
                                                                                                           getPtr(),
                                                                                                           static_cast<org::imm::ImmParagraphValueRead(org::imm::ImmAdapterT<org::imm::ImmParagraph>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmParagraph>::getValue),
                                                                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParagraphAdapter", {InstanceMethod("getValue", &ImmParagraphAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParagraphAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmParagraph>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmParagraph>* getPtr() { return _stored.get(); }
};

struct ImmListAdapter : public Napi::ObjectWrap<ImmListAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmList>, org::imm::ImmListValueRead>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::imm::ImmListValueRead(org::imm::ImmAdapterT<org::imm::ImmList>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmList>::getValue),
                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmListAdapter", {InstanceMethod("getValue", &ImmListAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmListAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmList>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmList>* getPtr() { return _stored.get(); }
};

struct ImmHashTagAdapter : public Napi::ObjectWrap<ImmHashTagAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmHashTag>, org::imm::ImmHashTagValueRead>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<org::imm::ImmHashTagValueRead(org::imm::ImmAdapterT<org::imm::ImmHashTag>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmHashTag>::getValue),
                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmHashTagAdapter", {InstanceMethod("getValue", &ImmHashTagAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmHashTagAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmHashTag>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmHashTag>* getPtr() { return _stored.get(); }
};

struct ImmInlineFootnoteAdapter : public Napi::ObjectWrap<ImmInlineFootnoteAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>, org::imm::ImmInlineFootnoteValueRead>(info,
                                                                                                                     getPtr(),
                                                                                                                     static_cast<org::imm::ImmInlineFootnoteValueRead(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getValue),
                                                                                                                     std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineFootnoteAdapter", {InstanceMethod("getValue", &ImmInlineFootnoteAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineFootnoteAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>* getPtr() { return _stored.get(); }
};

struct ImmEscapedAdapter : public Napi::ObjectWrap<ImmEscapedAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmEscaped>, org::imm::ImmEscapedValueRead>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<org::imm::ImmEscapedValueRead(org::imm::ImmAdapterT<org::imm::ImmEscaped>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmEscaped>::getValue),
                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmEscapedAdapter", {InstanceMethod("getValue", &ImmEscapedAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmEscapedAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmEscaped>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmEscaped>* getPtr() { return _stored.get(); }
};

struct ImmNewlineAdapter : public Napi::ObjectWrap<ImmNewlineAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmNewline>, org::imm::ImmNewlineValueRead>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<org::imm::ImmNewlineValueRead(org::imm::ImmAdapterT<org::imm::ImmNewline>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmNewline>::getValue),
                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmNewlineAdapter", {InstanceMethod("getValue", &ImmNewlineAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmNewlineAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmNewline>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmNewline>* getPtr() { return _stored.get(); }
};

struct ImmSpaceAdapter : public Napi::ObjectWrap<ImmSpaceAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmSpace>, org::imm::ImmSpaceValueRead>(info,
                                                                                                   getPtr(),
                                                                                                   static_cast<org::imm::ImmSpaceValueRead(org::imm::ImmAdapterT<org::imm::ImmSpace>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSpace>::getValue),
                                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmSpaceAdapter", {InstanceMethod("getValue", &ImmSpaceAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmSpaceAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmSpace>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmSpace>* getPtr() { return _stored.get(); }
};

struct ImmWordAdapter : public Napi::ObjectWrap<ImmWordAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmWord>, org::imm::ImmWordValueRead>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::imm::ImmWordValueRead(org::imm::ImmAdapterT<org::imm::ImmWord>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmWord>::getValue),
                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmWordAdapter", {InstanceMethod("getValue", &ImmWordAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmWordAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmWord>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmWord>* getPtr() { return _stored.get(); }
};

struct ImmAtMentionAdapter : public Napi::ObjectWrap<ImmAtMentionAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmAtMention>, org::imm::ImmAtMentionValueRead>(info,
                                                                                                           getPtr(),
                                                                                                           static_cast<org::imm::ImmAtMentionValueRead(org::imm::ImmAdapterT<org::imm::ImmAtMention>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmAtMention>::getValue),
                                                                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAtMentionAdapter", {InstanceMethod("getValue", &ImmAtMentionAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAtMentionAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmAtMention>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmAtMention>* getPtr() { return _stored.get(); }
};

struct ImmRawTextAdapter : public Napi::ObjectWrap<ImmRawTextAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmRawText>, org::imm::ImmRawTextValueRead>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<org::imm::ImmRawTextValueRead(org::imm::ImmAdapterT<org::imm::ImmRawText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRawText>::getValue),
                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRawTextAdapter", {InstanceMethod("getValue", &ImmRawTextAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRawTextAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmRawText>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmRawText>* getPtr() { return _stored.get(); }
};

struct ImmPunctuationAdapter : public Napi::ObjectWrap<ImmPunctuationAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmPunctuation>, org::imm::ImmPunctuationValueRead>(info,
                                                                                                               getPtr(),
                                                                                                               static_cast<org::imm::ImmPunctuationValueRead(org::imm::ImmAdapterT<org::imm::ImmPunctuation>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmPunctuation>::getValue),
                                                                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPunctuationAdapter", {InstanceMethod("getValue", &ImmPunctuationAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPunctuationAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmPunctuation>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmPunctuation>* getPtr() { return _stored.get(); }
};

struct ImmPlaceholderAdapter : public Napi::ObjectWrap<ImmPlaceholderAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>, org::imm::ImmPlaceholderValueRead>(info,
                                                                                                               getPtr(),
                                                                                                               static_cast<org::imm::ImmPlaceholderValueRead(org::imm::ImmAdapterT<org::imm::ImmPlaceholder>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmPlaceholder>::getValue),
                                                                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmPlaceholderAdapter", {InstanceMethod("getValue", &ImmPlaceholderAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmPlaceholderAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmPlaceholder>* getPtr() { return _stored.get(); }
};

struct ImmBigIdentAdapter : public Napi::ObjectWrap<ImmBigIdentAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmBigIdent>, org::imm::ImmBigIdentValueRead>(info,
                                                                                                         getPtr(),
                                                                                                         static_cast<org::imm::ImmBigIdentValueRead(org::imm::ImmAdapterT<org::imm::ImmBigIdent>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBigIdent>::getValue),
                                                                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBigIdentAdapter", {InstanceMethod("getValue", &ImmBigIdentAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBigIdentAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBigIdent>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBigIdent>* getPtr() { return _stored.get(); }
};

struct ImmTextTargetAdapter : public Napi::ObjectWrap<ImmTextTargetAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmTextTarget>, org::imm::ImmTextTargetValueRead>(info,
                                                                                                             getPtr(),
                                                                                                             static_cast<org::imm::ImmTextTargetValueRead(org::imm::ImmAdapterT<org::imm::ImmTextTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTextTarget>::getValue),
                                                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTextTargetAdapter", {InstanceMethod("getValue", &ImmTextTargetAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTextTargetAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTextTarget>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTextTarget>* getPtr() { return _stored.get(); }
};

struct ImmBoldAdapter : public Napi::ObjectWrap<ImmBoldAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmBold>, org::imm::ImmBoldValueRead>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::imm::ImmBoldValueRead(org::imm::ImmAdapterT<org::imm::ImmBold>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBold>::getValue),
                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBoldAdapter", {InstanceMethod("getValue", &ImmBoldAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBoldAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBold>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBold>* getPtr() { return _stored.get(); }
};

struct ImmUnderlineAdapter : public Napi::ObjectWrap<ImmUnderlineAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmUnderline>, org::imm::ImmUnderlineValueRead>(info,
                                                                                                           getPtr(),
                                                                                                           static_cast<org::imm::ImmUnderlineValueRead(org::imm::ImmAdapterT<org::imm::ImmUnderline>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmUnderline>::getValue),
                                                                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmUnderlineAdapter", {InstanceMethod("getValue", &ImmUnderlineAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmUnderlineAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmUnderline>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmUnderline>* getPtr() { return _stored.get(); }
};

struct ImmMonospaceAdapter : public Napi::ObjectWrap<ImmMonospaceAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmMonospace>, org::imm::ImmMonospaceValueRead>(info,
                                                                                                           getPtr(),
                                                                                                           static_cast<org::imm::ImmMonospaceValueRead(org::imm::ImmAdapterT<org::imm::ImmMonospace>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMonospace>::getValue),
                                                                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMonospaceAdapter", {InstanceMethod("getValue", &ImmMonospaceAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMonospaceAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmMonospace>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmMonospace>* getPtr() { return _stored.get(); }
};

struct ImmMarkQuoteAdapter : public Napi::ObjectWrap<ImmMarkQuoteAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>, org::imm::ImmMarkQuoteValueRead>(info,
                                                                                                           getPtr(),
                                                                                                           static_cast<org::imm::ImmMarkQuoteValueRead(org::imm::ImmAdapterT<org::imm::ImmMarkQuote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMarkQuote>::getValue),
                                                                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmMarkQuoteAdapter", {InstanceMethod("getValue", &ImmMarkQuoteAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmMarkQuoteAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmMarkQuote>* getPtr() { return _stored.get(); }
};

struct ImmRadioTargetAdapter : public Napi::ObjectWrap<ImmRadioTargetAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>, org::imm::ImmRadioTargetValueRead>(info,
                                                                                                               getPtr(),
                                                                                                               static_cast<org::imm::ImmRadioTargetValueRead(org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::getValue),
                                                                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRadioTargetAdapter", {InstanceMethod("getValue", &ImmRadioTargetAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRadioTargetAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmRadioTarget>* getPtr() { return _stored.get(); }
};

struct ImmVerbatimAdapter : public Napi::ObjectWrap<ImmVerbatimAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmVerbatim>, org::imm::ImmVerbatimValueRead>(info,
                                                                                                         getPtr(),
                                                                                                         static_cast<org::imm::ImmVerbatimValueRead(org::imm::ImmAdapterT<org::imm::ImmVerbatim>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmVerbatim>::getValue),
                                                                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmVerbatimAdapter", {InstanceMethod("getValue", &ImmVerbatimAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmVerbatimAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmVerbatim>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmVerbatim>* getPtr() { return _stored.get(); }
};

struct ImmItalicAdapter : public Napi::ObjectWrap<ImmItalicAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmItalic>, org::imm::ImmItalicValueRead>(info,
                                                                                                     getPtr(),
                                                                                                     static_cast<org::imm::ImmItalicValueRead(org::imm::ImmAdapterT<org::imm::ImmItalic>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmItalic>::getValue),
                                                                                                     std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmItalicAdapter", {InstanceMethod("getValue", &ImmItalicAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmItalicAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmItalic>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmItalic>* getPtr() { return _stored.get(); }
};

struct ImmStrikeAdapter : public Napi::ObjectWrap<ImmStrikeAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmStrike>, org::imm::ImmStrikeValueRead>(info,
                                                                                                     getPtr(),
                                                                                                     static_cast<org::imm::ImmStrikeValueRead(org::imm::ImmAdapterT<org::imm::ImmStrike>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmStrike>::getValue),
                                                                                                     std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmStrikeAdapter", {InstanceMethod("getValue", &ImmStrikeAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmStrikeAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmStrike>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmStrike>* getPtr() { return _stored.get(); }
};

struct ImmParAdapter : public Napi::ObjectWrap<ImmParAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmPar>, org::imm::ImmParValueRead>(info,
                                                                                               getPtr(),
                                                                                               static_cast<org::imm::ImmParValueRead(org::imm::ImmAdapterT<org::imm::ImmPar>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmPar>::getValue),
                                                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmParAdapter", {InstanceMethod("getValue", &ImmParAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmParAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmPar>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmPar>* getPtr() { return _stored.get(); }
};

struct CmdCaptionJs : public Napi::ObjectWrap<CmdCaptionJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdCaption, OrgSemKind>(info,
                                                             getPtr(),
                                                             static_cast<OrgSemKind(org::sem::CmdCaption::*)() const>(&org::sem::CmdCaption::getKind),
                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCaptionJs", {InstanceMethod("getKind", &CmdCaptionJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdCaptionJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::CmdCaption> _stored;
  org::sem::CmdCaption* getPtr() { return _stored.get(); }
};

struct CmdColumnsJs : public Napi::ObjectWrap<CmdColumnsJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdColumns, OrgSemKind>(info,
                                                             getPtr(),
                                                             static_cast<OrgSemKind(org::sem::CmdColumns::*)() const>(&org::sem::CmdColumns::getKind),
                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdColumnsJs", {InstanceMethod("getKind", &CmdColumnsJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdColumnsJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::CmdColumns> _stored;
  org::sem::CmdColumns* getPtr() { return _stored.get(); }
};

struct CmdNameJs : public Napi::ObjectWrap<CmdNameJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdName, OrgSemKind>(info,
                                                          getPtr(),
                                                          static_cast<OrgSemKind(org::sem::CmdName::*)() const>(&org::sem::CmdName::getKind),
                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdNameJs", {InstanceMethod("getKind", &CmdNameJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdNameJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::CmdName> _stored;
  org::sem::CmdName* getPtr() { return _stored.get(); }
};

struct CmdCallJs : public Napi::ObjectWrap<CmdCallJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdCall, OrgSemKind>(info,
                                                          getPtr(),
                                                          static_cast<OrgSemKind(org::sem::CmdCall::*)() const>(&org::sem::CmdCall::getKind),
                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdCallJs", {InstanceMethod("getKind", &CmdCallJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdCallJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::CmdCall> _stored;
  org::sem::CmdCall* getPtr() { return _stored.get(); }
};

struct CmdAttrJs : public Napi::ObjectWrap<CmdAttrJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdAttr, OrgSemKind>(info,
                                                          getPtr(),
                                                          static_cast<OrgSemKind(org::sem::CmdAttr::*)() const>(&org::sem::CmdAttr::getKind),
                                                          std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdAttrJs", {InstanceMethod("getKind", &CmdAttrJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdAttrJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::CmdAttr> _stored;
  org::sem::CmdAttr* getPtr() { return _stored.get(); }
};

struct CmdExportJs : public Napi::ObjectWrap<CmdExportJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::sem::CmdExport, OrgSemKind>(info,
                                                            getPtr(),
                                                            static_cast<OrgSemKind(org::sem::CmdExport::*)() const>(&org::sem::CmdExport::getKind),
                                                            std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "CmdExportJs", {InstanceMethod("getKind", &CmdExportJs::getKind)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("CmdExportJs", func);
    return exports;
  }
  std::shared_ptr<org::sem::CmdExport> _stored;
  org::sem::CmdExport* getPtr() { return _stored.get(); }
};

struct ImmAdapterAttachedAPIJs : public Napi::ObjectWrap<ImmAdapterAttachedAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterAttachedAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterAttachedAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterAttachedAPI> _stored;
  org::imm::ImmAdapterAttachedAPI* getPtr() { return _stored.get(); }
};

struct ImmCmdCustomArgsAdapter : public Napi::ObjectWrap<ImmCmdCustomArgsAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>, org::imm::ImmCmdCustomArgsValueRead>(info,
                                                                                                                   getPtr(),
                                                                                                                   static_cast<org::imm::ImmCmdCustomArgsValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getValue),
                                                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCustomArgsAdapter", {InstanceMethod("getValue", &ImmCmdCustomArgsAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCustomArgsAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>* getPtr() { return _stored.get(); }
};

struct ImmCmdTblfmAdapter : public Napi::ObjectWrap<ImmCmdTblfmAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>, org::imm::ImmCmdTblfmValueRead>(info,
                                                                                                         getPtr(),
                                                                                                         static_cast<org::imm::ImmCmdTblfmValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::getValue),
                                                                                                         std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdTblfmAdapter", {InstanceMethod("getValue", &ImmCmdTblfmAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdTblfmAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>* getPtr() { return _stored.get(); }
};

struct ImmAdapterBlockCenterAPIJs : public Napi::ObjectWrap<ImmAdapterBlockCenterAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBlockCenterAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBlockCenterAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBlockCenterAPI> _stored;
  org::imm::ImmAdapterBlockCenterAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterBlockQuoteAPIJs : public Napi::ObjectWrap<ImmAdapterBlockQuoteAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBlockQuoteAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBlockQuoteAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBlockQuoteAPI> _stored;
  org::imm::ImmAdapterBlockQuoteAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterBlockVerseAPIJs : public Napi::ObjectWrap<ImmAdapterBlockVerseAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBlockVerseAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBlockVerseAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBlockVerseAPI> _stored;
  org::imm::ImmAdapterBlockVerseAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterBlockExampleAPIJs : public Napi::ObjectWrap<ImmAdapterBlockExampleAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBlockExampleAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBlockExampleAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBlockExampleAPI> _stored;
  org::imm::ImmAdapterBlockExampleAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterInlineExportAPIJs : public Napi::ObjectWrap<ImmAdapterInlineExportAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterInlineExportAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterInlineExportAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterInlineExportAPI> _stored;
  org::imm::ImmAdapterInlineExportAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdExportAPIJs : public Napi::ObjectWrap<ImmAdapterCmdExportAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdExportAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdExportAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdExportAPI> _stored;
  org::imm::ImmAdapterCmdExportAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterBlockExportAPIJs : public Napi::ObjectWrap<ImmAdapterBlockExportAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBlockExportAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBlockExportAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBlockExportAPI> _stored;
  org::imm::ImmAdapterBlockExportAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterBlockDynamicFallbackAPIJs : public Napi::ObjectWrap<ImmAdapterBlockDynamicFallbackAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBlockDynamicFallbackAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBlockDynamicFallbackAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBlockDynamicFallbackAPI> _stored;
  org::imm::ImmAdapterBlockDynamicFallbackAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterBlockAdmonitionAPIJs : public Napi::ObjectWrap<ImmAdapterBlockAdmonitionAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBlockAdmonitionAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBlockAdmonitionAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBlockAdmonitionAPI> _stored;
  org::imm::ImmAdapterBlockAdmonitionAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterBlockCodeEvalResultAPIJs : public Napi::ObjectWrap<ImmAdapterBlockCodeEvalResultAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBlockCodeEvalResultAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBlockCodeEvalResultAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBlockCodeEvalResultAPI> _stored;
  org::imm::ImmAdapterBlockCodeEvalResultAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterBlockCodeAPIJs : public Napi::ObjectWrap<ImmAdapterBlockCodeAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterBlockCodeAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterBlockCodeAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterBlockCodeAPI> _stored;
  org::imm::ImmAdapterBlockCodeAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterTableAPIJs : public Napi::ObjectWrap<ImmAdapterTableAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterTableAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterTableAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterTableAPI> _stored;
  org::imm::ImmAdapterTableAPI* getPtr() { return _stored.get(); }
};

struct ImmCellAdapter : public Napi::ObjectWrap<ImmCellAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCell>, org::imm::ImmCellValueRead>(info,
                                                                                                 getPtr(),
                                                                                                 static_cast<org::imm::ImmCellValueRead(org::imm::ImmAdapterT<org::imm::ImmCell>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCell>::getValue),
                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCellAdapter", {InstanceMethod("getValue", &ImmCellAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCellAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCell>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCell>* getPtr() { return _stored.get(); }
};

struct ImmRowAdapter : public Napi::ObjectWrap<ImmRowAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmRow>, org::imm::ImmRowValueRead>(info,
                                                                                               getPtr(),
                                                                                               static_cast<org::imm::ImmRowValueRead(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getValue),
                                                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmRowAdapter", {InstanceMethod("getValue", &ImmRowAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmRowAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmRow>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmRow>* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdCaptionAPIJs : public Napi::ObjectWrap<ImmAdapterCmdCaptionAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdCaptionAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdCaptionAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdCaptionAPI> _stored;
  org::imm::ImmAdapterCmdCaptionAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdColumnsAPIJs : public Napi::ObjectWrap<ImmAdapterCmdColumnsAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdColumnsAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdColumnsAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdColumnsAPI> _stored;
  org::imm::ImmAdapterCmdColumnsAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdNameAPIJs : public Napi::ObjectWrap<ImmAdapterCmdNameAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdNameAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdNameAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdNameAPI> _stored;
  org::imm::ImmAdapterCmdNameAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdCallAPIJs : public Napi::ObjectWrap<ImmAdapterCmdCallAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdCallAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdCallAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdCallAPI> _stored;
  org::imm::ImmAdapterCmdCallAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdResultsAPIJs : public Napi::ObjectWrap<ImmAdapterCmdResultsAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdResultsAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdResultsAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdResultsAPI> _stored;
  org::imm::ImmAdapterCmdResultsAPI* getPtr() { return _stored.get(); }
};

struct ImmAdapterCmdAttrAPIJs : public Napi::ObjectWrap<ImmAdapterCmdAttrAPIJs> {
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmAdapterCmdAttrAPIJs", {});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmAdapterCmdAttrAPIJs", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterCmdAttrAPI> _stored;
  org::imm::ImmAdapterCmdAttrAPI* getPtr() { return _stored.get(); }
};

struct ImmBlockCenterAdapter : public Napi::ObjectWrap<ImmBlockCenterAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>, org::imm::ImmBlockCenterValueRead>(info,
                                                                                                               getPtr(),
                                                                                                               static_cast<org::imm::ImmBlockCenterValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockCenter>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCenter>::getValue),
                                                                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCenterAdapter", {InstanceMethod("getValue", &ImmBlockCenterAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCenterAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockCenter>* getPtr() { return _stored.get(); }
};

struct ImmBlockQuoteAdapter : public Napi::ObjectWrap<ImmBlockQuoteAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>, org::imm::ImmBlockQuoteValueRead>(info,
                                                                                                             getPtr(),
                                                                                                             static_cast<org::imm::ImmBlockQuoteValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockQuote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockQuote>::getValue),
                                                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockQuoteAdapter", {InstanceMethod("getValue", &ImmBlockQuoteAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockQuoteAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockQuote>* getPtr() { return _stored.get(); }
};

struct ImmBlockVerseAdapter : public Napi::ObjectWrap<ImmBlockVerseAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>, org::imm::ImmBlockVerseValueRead>(info,
                                                                                                             getPtr(),
                                                                                                             static_cast<org::imm::ImmBlockVerseValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockVerse>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockVerse>::getValue),
                                                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockVerseAdapter", {InstanceMethod("getValue", &ImmBlockVerseAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockVerseAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockVerse>* getPtr() { return _stored.get(); }
};

struct ImmBlockExampleAdapter : public Napi::ObjectWrap<ImmBlockExampleAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmBlockExample>, org::imm::ImmBlockExampleValueRead>(info,
                                                                                                                 getPtr(),
                                                                                                                 static_cast<org::imm::ImmBlockExampleValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockExample>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExample>::getValue),
                                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExampleAdapter", {InstanceMethod("getValue", &ImmBlockExampleAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExampleAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockExample>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockExample>* getPtr() { return _stored.get(); }
};

struct ImmInlineExportAdapter : public Napi::ObjectWrap<ImmInlineExportAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmInlineExport>, org::imm::ImmInlineExportValueRead>(info,
                                                                                                                 getPtr(),
                                                                                                                 static_cast<org::imm::ImmInlineExportValueRead(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getValue),
                                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmInlineExportAdapter", {InstanceMethod("getValue", &ImmInlineExportAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmInlineExportAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmInlineExport>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmInlineExport>* getPtr() { return _stored.get(); }
};

struct ImmCmdExportAdapter : public Napi::ObjectWrap<ImmCmdExportAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCmdExport>, org::imm::ImmCmdExportValueRead>(info,
                                                                                                           getPtr(),
                                                                                                           static_cast<org::imm::ImmCmdExportValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getValue),
                                                                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdExportAdapter", {InstanceMethod("getValue", &ImmCmdExportAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdExportAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdExport>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdExport>* getPtr() { return _stored.get(); }
};

struct ImmBlockExportAdapter : public Napi::ObjectWrap<ImmBlockExportAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmBlockExport>, org::imm::ImmBlockExportValueRead>(info,
                                                                                                               getPtr(),
                                                                                                               static_cast<org::imm::ImmBlockExportValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getValue),
                                                                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockExportAdapter", {InstanceMethod("getValue", &ImmBlockExportAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockExportAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockExport>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockExport>* getPtr() { return _stored.get(); }
};

struct ImmBlockDynamicFallbackAdapter : public Napi::ObjectWrap<ImmBlockDynamicFallbackAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>, org::imm::ImmBlockDynamicFallbackValueRead>(info,
                                                                                                                                 getPtr(),
                                                                                                                                 static_cast<org::imm::ImmBlockDynamicFallbackValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::getValue),
                                                                                                                                 std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockDynamicFallbackAdapter", {InstanceMethod("getValue", &ImmBlockDynamicFallbackAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockDynamicFallbackAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>* getPtr() { return _stored.get(); }
};

struct ImmBlockAdmonitionAdapter : public Napi::ObjectWrap<ImmBlockAdmonitionAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>, org::imm::ImmBlockAdmonitionValueRead>(info,
                                                                                                                       getPtr(),
                                                                                                                       static_cast<org::imm::ImmBlockAdmonitionValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>::getValue),
                                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockAdmonitionAdapter", {InstanceMethod("getValue", &ImmBlockAdmonitionAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockAdmonitionAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>* getPtr() { return _stored.get(); }
};

struct ImmBlockCodeEvalResultAdapter : public Napi::ObjectWrap<ImmBlockCodeEvalResultAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>, org::imm::ImmBlockCodeEvalResultValueRead>(info,
                                                                                                                               getPtr(),
                                                                                                                               static_cast<org::imm::ImmBlockCodeEvalResultValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getValue),
                                                                                                                               std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeEvalResultAdapter", {InstanceMethod("getValue", &ImmBlockCodeEvalResultAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeEvalResultAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>* getPtr() { return _stored.get(); }
};

struct ImmBlockCodeAdapter : public Napi::ObjectWrap<ImmBlockCodeAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmBlockCode>, org::imm::ImmBlockCodeValueRead>(info,
                                                                                                           getPtr(),
                                                                                                           static_cast<org::imm::ImmBlockCodeValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getValue),
                                                                                                           std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmBlockCodeAdapter", {InstanceMethod("getValue", &ImmBlockCodeAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmBlockCodeAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmBlockCode>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmBlockCode>* getPtr() { return _stored.get(); }
};

struct ImmTableAdapter : public Napi::ObjectWrap<ImmTableAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmTable>, org::imm::ImmTableValueRead>(info,
                                                                                                   getPtr(),
                                                                                                   static_cast<org::imm::ImmTableValueRead(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getValue),
                                                                                                   std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmTableAdapter", {InstanceMethod("getValue", &ImmTableAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmTableAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmTable>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmTable>* getPtr() { return _stored.get(); }
};

struct ImmCmdCaptionAdapter : public Napi::ObjectWrap<ImmCmdCaptionAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>, org::imm::ImmCmdCaptionValueRead>(info,
                                                                                                             getPtr(),
                                                                                                             static_cast<org::imm::ImmCmdCaptionValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::getValue),
                                                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCaptionAdapter", {InstanceMethod("getValue", &ImmCmdCaptionAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCaptionAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCaption>* getPtr() { return _stored.get(); }
};

struct ImmCmdColumnsAdapter : public Napi::ObjectWrap<ImmCmdColumnsAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>, org::imm::ImmCmdColumnsValueRead>(info,
                                                                                                             getPtr(),
                                                                                                             static_cast<org::imm::ImmCmdColumnsValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::getValue),
                                                                                                             std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdColumnsAdapter", {InstanceMethod("getValue", &ImmCmdColumnsAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdColumnsAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdColumns>* getPtr() { return _stored.get(); }
};

struct ImmCmdNameAdapter : public Napi::ObjectWrap<ImmCmdNameAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCmdName>, org::imm::ImmCmdNameValueRead>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<org::imm::ImmCmdNameValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdName>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdName>::getValue),
                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdNameAdapter", {InstanceMethod("getValue", &ImmCmdNameAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdNameAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdName>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdName>* getPtr() { return _stored.get(); }
};

struct ImmCmdCallAdapter : public Napi::ObjectWrap<ImmCmdCallAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCmdCall>, org::imm::ImmCmdCallValueRead>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<org::imm::ImmCmdCallValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getValue),
                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdCallAdapter", {InstanceMethod("getValue", &ImmCmdCallAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdCallAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdCall>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdCall>* getPtr() { return _stored.get(); }
};

struct ImmCmdAttrAdapter : public Napi::ObjectWrap<ImmCmdAttrAdapter> {
  Napi::Value getValue(Napi::CallbackInfo const& info) {
    return WrapConstMethod<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>, org::imm::ImmCmdAttrValueRead>(info,
                                                                                                       getPtr(),
                                                                                                       static_cast<org::imm::ImmCmdAttrValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::getValue),
                                                                                                       std::make_tuple());
  }
  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ImmCmdAttrAdapter", {InstanceMethod("getValue", &ImmCmdAttrAdapter::getValue)});
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("ImmCmdAttrAdapter", func);
    return exports;
  }
  std::shared_ptr<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>> _stored;
  org::imm::ImmAdapterT<org::imm::ImmCmdAttr>* getPtr() { return _stored.get(); }
};

Napi::Object InitModule(Napi::Env env, Napi::Object exports) {
  UserTimeBreakdownJs::Init(env, exports);
  UserTimeJs::Init(env, exports);
  LineColJs::Init(env, exports);
  OrgJsonJs::Init(env, exports);
  OrgJs::Init(env, exports);
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
  ImmAdapterVirtualBaseJs::Init(env, exports);
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
  StmtJs::Init(env, exports);
  InlineJs::Init(env, exports);
  StmtListJs::Init(env, exports);
  EmptyJs::Init(env, exports);
  LeafJs::Init(env, exports);
  TimeJs::Init(env, exports);
  TimeRangeJs::Init(env, exports);
  MacroJs::Init(env, exports);
  SymbolJs::Init(env, exports);
  MarkupJs::Init(env, exports);
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
  ImmAdapterOrgAPIJs::Init(env, exports);
  CmdJs::Init(env, exports);
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
  ImmAdapterStmtAPIJs::Init(env, exports);
  ImmAdapterSubtreeAPIJs::Init(env, exports);
  ImmAdapterNoneAPIJs::Init(env, exports);
  ImmAdapterAttrAPIJs::Init(env, exports);
  ImmAdapterAttrListAPIJs::Init(env, exports);
  ImmAdapterAttrsAPIJs::Init(env, exports);
  ImmAdapterErrorItemAPIJs::Init(env, exports);
  ImmAdapterErrorGroupAPIJs::Init(env, exports);
  ImmAdapterStmtListAPIJs::Init(env, exports);
  ImmAdapterEmptyAPIJs::Init(env, exports);
  ImmAdapterInlineAPIJs::Init(env, exports);
  ImmAdapterTimeAPIJs::Init(env, exports);
  ImmAdapterTimeRangeAPIJs::Init(env, exports);
  ImmAdapterMacroAPIJs::Init(env, exports);
  ImmAdapterSymbolAPIJs::Init(env, exports);
  ImmAdapterLeafAPIJs::Init(env, exports);
  ImmAdapterMarkupAPIJs::Init(env, exports);
  ImmAdapterLatexAPIJs::Init(env, exports);
  ImmAdapterSubtreeLogAPIJs::Init(env, exports);
  ImmAdapterColonExampleAPIJs::Init(env, exports);
  ImmAdapterCallAPIJs::Init(env, exports);
  ImmAdapterFileAPIJs::Init(env, exports);
  ImmAdapterDirectoryAPIJs::Init(env, exports);
  ImmAdapterSymlinkAPIJs::Init(env, exports);
  ImmAdapterDocumentFragmentAPIJs::Init(env, exports);
  ImmAdapterCriticMarkupAPIJs::Init(env, exports);
  ImmAdapterListItemAPIJs::Init(env, exports);
  ImmAdapterDocumentOptionsAPIJs::Init(env, exports);
  ImmAdapterDocumentAPIJs::Init(env, exports);
  ImmAdapterFileTargetAPIJs::Init(env, exports);
  ImmAdapterTextSeparatorAPIJs::Init(env, exports);
  ImmAdapterCmdIncludeAPIJs::Init(env, exports);
  ImmAdapterDocumentGroupAPIJs::Init(env, exports);
  BlockJs::Init(env, exports);
  LineCommandJs::Init(env, exports);
  CmdCustomArgsJs::Init(env, exports);
  CmdTblfmJs::Init(env, exports);
  CellJs::Init(env, exports);
  RowJs::Init(env, exports);
  ImmAdapterCmdAPIJs::Init(env, exports);
  ImmAdapterCmdCustomRawAPIJs::Init(env, exports);
  ImmAdapterCmdCustomTextAPIJs::Init(env, exports);
  ImmAdapterLinkAPIJs::Init(env, exports);
  ImmAdapterBlockCommentAPIJs::Init(env, exports);
  ImmAdapterParagraphAPIJs::Init(env, exports);
  ImmAdapterListAPIJs::Init(env, exports);
  ImmSubtreeAdapter::Init(env, exports);
  ImmNoneAdapter::Init(env, exports);
  ImmErrorItemAdapter::Init(env, exports);
  ImmErrorGroupAdapter::Init(env, exports);
  ImmStmtListAdapter::Init(env, exports);
  ImmEmptyAdapter::Init(env, exports);
  ImmAdapterHashTagAPIJs::Init(env, exports);
  ImmAdapterInlineFootnoteAPIJs::Init(env, exports);
  ImmAdapterSubtreeCompletionAPIJs::Init(env, exports);
  ImmTimeAdapter::Init(env, exports);
  ImmTimeRangeAdapter::Init(env, exports);
  ImmMacroAdapter::Init(env, exports);
  ImmSymbolAdapter::Init(env, exports);
  ImmAdapterEscapedAPIJs::Init(env, exports);
  ImmAdapterNewlineAPIJs::Init(env, exports);
  ImmAdapterSpaceAPIJs::Init(env, exports);
  ImmAdapterWordAPIJs::Init(env, exports);
  ImmAdapterAtMentionAPIJs::Init(env, exports);
  ImmAdapterRawTextAPIJs::Init(env, exports);
  ImmAdapterPunctuationAPIJs::Init(env, exports);
  ImmAdapterPlaceholderAPIJs::Init(env, exports);
  ImmAdapterBigIdentAPIJs::Init(env, exports);
  ImmAdapterTextTargetAPIJs::Init(env, exports);
  ImmAdapterBoldAPIJs::Init(env, exports);
  ImmAdapterUnderlineAPIJs::Init(env, exports);
  ImmAdapterMonospaceAPIJs::Init(env, exports);
  ImmAdapterMarkQuoteAPIJs::Init(env, exports);
  ImmAdapterRadioTargetAPIJs::Init(env, exports);
  ImmAdapterVerbatimAPIJs::Init(env, exports);
  ImmAdapterItalicAPIJs::Init(env, exports);
  ImmAdapterStrikeAPIJs::Init(env, exports);
  ImmAdapterParAPIJs::Init(env, exports);
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
  AttachedJs::Init(env, exports);
  ImmAdapterLineCommandAPIJs::Init(env, exports);
  ImmAdapterCmdCustomArgsAPIJs::Init(env, exports);
  ImmAdapterCmdTblfmAPIJs::Init(env, exports);
  ImmAdapterBlockAPIJs::Init(env, exports);
  ImmAdapterCellAPIJs::Init(env, exports);
  ImmAdapterRowAPIJs::Init(env, exports);
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
  ImmAdapterAttachedAPIJs::Init(env, exports);
  ImmCmdCustomArgsAdapter::Init(env, exports);
  ImmCmdTblfmAdapter::Init(env, exports);
  ImmAdapterBlockCenterAPIJs::Init(env, exports);
  ImmAdapterBlockQuoteAPIJs::Init(env, exports);
  ImmAdapterBlockVerseAPIJs::Init(env, exports);
  ImmAdapterBlockExampleAPIJs::Init(env, exports);
  ImmAdapterInlineExportAPIJs::Init(env, exports);
  ImmAdapterCmdExportAPIJs::Init(env, exports);
  ImmAdapterBlockExportAPIJs::Init(env, exports);
  ImmAdapterBlockDynamicFallbackAPIJs::Init(env, exports);
  ImmAdapterBlockAdmonitionAPIJs::Init(env, exports);
  ImmAdapterBlockCodeEvalResultAPIJs::Init(env, exports);
  ImmAdapterBlockCodeAPIJs::Init(env, exports);
  ImmAdapterTableAPIJs::Init(env, exports);
  ImmCellAdapter::Init(env, exports);
  ImmRowAdapter::Init(env, exports);
  ImmAdapterCmdCaptionAPIJs::Init(env, exports);
  ImmAdapterCmdColumnsAPIJs::Init(env, exports);
  ImmAdapterCmdNameAPIJs::Init(env, exports);
  ImmAdapterCmdCallAPIJs::Init(env, exports);
  ImmAdapterCmdResultsAPIJs::Init(env, exports);
  ImmAdapterCmdAttrAPIJs::Init(env, exports);
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