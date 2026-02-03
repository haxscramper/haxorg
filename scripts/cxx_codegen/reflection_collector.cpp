#include "reflection_collector.hpp"

#include <llvm/Support/TimeProfiler.h>
#include <format>
#include <absl/log/log.h>
#include <absl/log/check.h>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/message.h>

#include <llvm/Object/ObjectFile.h>
#include <llvm/Object/ELFObjectFile.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Demangle/Demangle.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/raw_ostream.h>
#include <fstream>
#include <hstd/ext/logger.hpp>

namespace c = clang;
using llvm::dyn_cast;


bool ReflASTVisitor::isDescribedRecord(
    const clang::RecordDecl* recordDecl) {
    if (!recordDecl) { return false; }

    // Try to downcast to CXXRecordDecl for C++ classes
    const clang::CXXRecordDecl* cxxRecordDecl = llvm::dyn_cast<
        clang::CXXRecordDecl>(recordDecl);

    // Get the qualified name of the record
    std::string recordName = recordDecl->getQualifiedNameAsString();

    // First check: Look for friend functions inside the class (only for
    // C++ classes)
    bool hasBaseFn   = false;
    bool hasMemberFn = false;

    // Check friend declarations inside the class (only for C++ classes)
    if (cxxRecordDecl) {
        if (!cxxRecordDecl->hasDefinition()) { return false; }

        for (const clang::FriendDecl* friendDecl :
             cxxRecordDecl->friends()) {
            if (const clang::FunctionDecl* fnDecl = llvm::dyn_cast<
                    clang::FunctionDecl>(friendDecl->getFriendDecl())) {
                std::string fnName = fnDecl->getNameAsString();

                if (fnName == "boost_base_descriptor_fn") {
                    hasBaseFn = true;
                } else if (
                    fnName == "boost_public_member_descriptor_fn"
                    || fnName == "boost_protected_member_descriptor_fn"
                    || fnName == "boost_private_member_descriptor_fn") {
                    hasMemberFn = true;
                }

                if (hasBaseFn && hasMemberFn) { return true; }
            }
        }
    }

    // Second check: Look for standalone functions that take this type as a
    // parameter Get the translation unit
    clang::TranslationUnitDecl* TU = Ctx->getTranslationUnitDecl();

    for (clang::Decl* decl : TU->decls()) {
        if (const clang::FunctionDecl* fnDecl = llvm::dyn_cast<
                clang::FunctionDecl>(decl)) {
            std::string fnName = fnDecl->getNameAsString();

            // Check if it's one of the Boost.Describe functions
            if (fnName == "boost_base_descriptor_fn"
                || fnName == "boost_public_member_descriptor_fn"
                || fnName == "boost_protected_member_descriptor_fn"
                || fnName == "boost_private_member_descriptor_fn") {

                // Check if the function takes a pointer-to-pointer of our
                // type
                if (fnDecl->getNumParams() >= 1) {
                    const clang::ParmVarDecl* param = fnDecl->getParamDecl(
                        0);
                    clang::QualType paramType = param->getType();

                    // The parameter should be T**
                    if (paramType->isPointerType()) {
                        clang::QualType pointeeType = paramType
                                                          ->getPointeeType();
                        if (pointeeType->isPointerType()) {
                            clang::QualType targetType = pointeeType
                                                             ->getPointeeType();

                            // Get the record declaration from the type
                            if (const clang::RecordType* recordType = targetType
                                                                          ->getAs<
                                                                              clang::
                                                                                  RecordType>()) {
                                if (recordType->getDecl() == recordDecl) {
                                    if (fnName
                                        == "boost_base_descriptor_fn") {
                                        hasBaseFn = true;
                                    } else {
                                        hasMemberFn = true;
                                    }

                                    if (hasBaseFn && hasMemberFn) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return hasBaseFn && hasMemberFn;
}

bool ReflASTVisitor::isDescribedEnum(const clang::EnumDecl* enumDecl) {
    if (!enumDecl) { return false; }

    // For enums, look for boost_enum_descriptor_fn
    clang::TranslationUnitDecl* TU = Ctx->getTranslationUnitDecl();

    for (clang::Decl* decl : TU->decls()) {
        if (const clang::FunctionDecl* fnDecl = llvm::dyn_cast<
                clang::FunctionDecl>(decl)) {
            std::string fnName = fnDecl->getNameAsString();

            if (fnName == "boost_enum_descriptor_fn") {
                // Check if the function takes a pointer-to-pointer of our
                // enum
                if (fnDecl->getNumParams() >= 1) {
                    const clang::ParmVarDecl* param = fnDecl->getParamDecl(
                        0);
                    clang::QualType paramType = param->getType();

                    // The parameter should be T**
                    if (paramType->isPointerType()) {
                        clang::QualType pointeeType = paramType
                                                          ->getPointeeType();
                        if (pointeeType->isPointerType()) {
                            clang::QualType targetType = pointeeType
                                                             ->getPointeeType();

                            if (const clang::EnumType* enumType = targetType
                                                                      ->getAs<
                                                                          clang::
                                                                              EnumType>()) {
                                if (enumType->getDecl() == enumDecl) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

std::optional<std::string> ReflASTVisitor::get_refl_params(
    c::Decl const* decl) {
    auto fmt = decl->getLocation().printToString(Ctx->getSourceManager());


    for (const clang::Attr* attr : decl->attrs()) {
        if (attr->getKind() == clang::attr::Kind::Annotate) {
            const auto* annotateAttr = llvm::cast<clang::AnnotateAttr>(
                attr);

            // Get the attribute arguments
            if (const auto* strLiteral = annotateAttr->args_begin();
                strLiteral != nullptr && *strLiteral != nullptr) {
                if (const auto* stringLiteral = llvm::dyn_cast<
                        clang::StringLiteral>(*strLiteral)) {
                    return stringLiteral->getString().str();
                }
            }

            // Fallback to annotation string if needed
            llvm::StringRef annotation = annotateAttr->getAnnotation();
            if (annotation.starts_with("refl")) {
                auto text = annotation.substr(4).trim().str();
                if (!text.empty()) { return text; }
            }
        }
    }

    return std::nullopt;
}

std::string ReflASTVisitor::dump(const clang::Decl* Decl, int head) {
    std::string              tree;
    llvm::raw_string_ostream rso(tree);
    Decl->dump(rso);
    rso.flush();

    if (head == -1) { return tree; }

    std::istringstream iss{tree};
    std::string        line;
    std::string        result;
    int                count{0};

    while (std::getline(iss, line) && count < head) {
        if (count > 0) { result += "\n"; }
        result += line;
        count++;
    }

    return result;
}

c::TypedefDecl* findTypedefForDecl(c::Decl* Decl, c::ASTContext* Ctx) {
    c::DeclContext* Context = Decl->getDeclContext();
    for (auto D : Context->decls()) {
        if (auto* TD = dyn_cast<c::TypedefDecl>(D)) {
            if (TD->getUnderlyingType()->getAsRecordDecl() == Decl) {
                return TD;
            } else if (const c::EnumType* ET = TD->getUnderlyingType()
                                                   ->getAs<c::EnumType>();
                       ET && ET->getDecl() == Decl) {
                return TD;

            } else if (TD->getUnderlyingDecl() == Decl) {
                return TD;
            }
        }
    }


    return nullptr;
}

c::FieldDecl* findFieldForDecl(c::Decl const* Decl, c::ASTContext* Ctx) {
    c::DeclContext const* Context = Decl->getDeclContext();
    for (auto D : Context->decls()) {
        if (auto* FD = dyn_cast<c::FieldDecl>(D)) {
            c::Type const* FieldType = FD->getType().getTypePtr();
            if (FD->getType()->getAsRecordDecl() == Decl) {
                return FD;
            } else if (const c::EnumType* ET = FD->getType()
                                                   ->getAs<c::EnumType>();
                       ET && ET->getDecl() == Decl) {
                return FD;

            } else if (
                FieldType && FieldType->getAs<c::RecordType>()
                && FieldType->getAs<c::RecordType>()->getDecl() == Decl) {
                return FD;
            }
        }
    }


    return nullptr;
}

std::string getAbsoluteDeclLocation(c::Decl const* Decl) {
    c::SourceLocation       loc           = Decl->getLocation();
    const c::ASTContext&    astContext    = Decl->getASTContext();
    c::SourceManager const& sourceManager = astContext.getSourceManager();

    std::string filePath;
    if (loc.isValid()) {
        c::SourceLocation fullLoc = sourceManager.getExpansionLoc(loc);
        if (fullLoc.isValid()) {
            filePath = sourceManager.getFilename(fullLoc).str();
        } else {
            filePath = sourceManager.getFilename(loc).str();
        }
    }

    return filePath;
}


template <typename T>
void add_debug(
    T*                 it,
    std::string const& msg,
    int                line = __builtin_LINE()) {
    it->mutable_dbgorigin()->append(std::format(" [{}]{}", line, msg));
}

template <typename T>
void append_debug(T* it, std::string const& msg) {
    it->mutable_dbgorigin()->append(msg);
}

template <typename Func>
struct finally {
    Func action;

    explicit finally(Func _action) : action(_action) {}

    template <typename T, typename Func1>
    static finally init(Func1 _action, T const& value) {
        return finally([value, _action]() { _action(value); });
    }

    static finally nop() { return finally{finally::nop_impl}; }

    ~finally() { action(); }

  private:
    static void nop_impl() {}
};

using finally_std = finally<std::function<void(void)>>;

template <typename T>
finally_std scope_debug(
    T*                 it,
    std::string const& pre,
    std::string const& post) {
    it->mutable_dbgorigin()->append(pre);
    return finally_std{
        [it, post]() { it->mutable_dbgorigin()->append(post); }};
}

std::ostream& errs(
    int         line     = __builtin_LINE(),
    char const* function = __builtin_FUNCTION()) {
    return std::cerr << std::format("[refl-lib] [{}:{}] ", function, line);
}


std::string formatSourceLocation(
    const c::SourceLocation& loc,
    c::SourceManager&        srcMgr) {
    if (loc.isValid()) {
        c::PresumedLoc presumedLoc = srcMgr.getPresumedLoc(loc);

        if (presumedLoc.isValid()) {
            std::string filePath = presumedLoc.getFilename();
            unsigned    line     = presumedLoc.getLine();
            unsigned    column   = presumedLoc.getColumn();

            // Split the filePath and get the last three parts
            std::vector<std::string> pathParts;
            std::istringstream       f(filePath);
            std::string              s;
            while (getline(f, s, '/')) { pathParts.push_back(s); }

            const int paths = 2;

            std::string shortPath;
            int         pathSize = pathParts.size();
            for (int i = std::max(0, pathSize - paths); i < pathSize;
                 ++i) {
                if (i > std::max(0, pathSize - paths)) {
                    shortPath += "/";
                }
                shortPath += pathParts[i];
            }

            // Format with line and column
            std::ostringstream formattedLoc;
            formattedLoc << shortPath << ":" << line << ":" << column;
            return formattedLoc.str();
        }
    }
    return "Invalid SourceLocation";
}


std::string formatSourceLocation(clang::Decl const* Decl) {
    return formatSourceLocation(
        Decl->getLocation(), Decl->getASTContext().getSourceManager());
}

std::string formatDeclLocation(clang::Decl const* Decl) {
    std::string name;
    if (const auto* namedDecl = llvm::dyn_cast<clang::NamedDecl>(Decl)) {
        name = namedDecl->getNameAsString();
    } else {
        name = "(not named decl)";
    }

    return std::format(
        "Decl '{}' of kind {} at '{}'",
        name,
        Decl->getDeclKindName(),
        formatSourceLocation(
            Decl->getLocation(),
            Decl->getASTContext().getSourceManager()));
}


std::vector<QualType> ReflASTVisitor::getNamespaces(
    c::NamespaceDecl const*                 Namespace,
    std::optional<c::SourceLocation> const& Loc) {
    std::vector<QualType> result;
    if (!Namespace->isAnonymousNamespace()
        && !Namespace->isInlineNamespace()) {
        auto space = &result.emplace_back();
        space->set_name(Namespace->getNameAsString());
        add_debug(
            space,
            std::format(
                "Namespace visitation of '{}'",
                Namespace->getNameAsString()));
        space->set_isnamespace(true);
        assert(!space->name().empty());
    }

    if (Namespace->getDeclContext()->isNamespace()) {
        auto spaces = getNamespaces(
            c::dyn_cast<c::NamespaceDecl>(Namespace->getDeclContext()),
            Loc);
        result.insert(result.end(), spaces.begin(), spaces.end());
    }

    return result;
}


void ReflASTVisitor::applyNamespaces(
    QualType*                    Out,
    const std::vector<QualType>& Namespaces,
    int                          line,
    const char*                  function) {
    std::vector<QualType const*> newNamespaces;
    std::vector<QualType*>       oldNamespaces;
    for (auto& Namespace : Namespaces) {
        newNamespaces.push_back(&Namespace);
    }

    {
        auto spaces = Out->mutable_spaces();
        for (int i = 0; i < spaces->size(); ++i) {
            oldNamespaces.push_back(&spaces->at(i));
        }
    }

    for (int i = 0;
         i < std::max(newNamespaces.size(), oldNamespaces.size());
         ++i) {
        if (i < newNamespaces.size() && i < oldNamespaces.size()) {
            QualType*       _old = oldNamespaces.at(i);
            QualType const* _new = newNamespaces.at(i);
            if (_old->name() != _new->name()) {
                if (false) {
                    HSLOG_WARNING(
                        "Mismatching namespace types at index {} '{}' "
                        "(from {}) != '{}' (from {})",
                        i,
                        _old->name(),
                        _old->dbgorigin(),
                        _new->name(),
                        _new->dbgorigin());
                }
                _old->set_name(_new->name());
            }


        } else {
            QualType newSpace = (i < newNamespaces.size())
                                  ? *newNamespaces.at(i)
                                  : *oldNamespaces.at(i);

            //            if (newSpace.name().empty()) {
            //                llvm::outs() << std::format(
            //                    "Empty namespace formatted from {}\n",
            //                    newSpace.dbgorigin());
            //            }

            auto space = Out->add_spaces();
            space->set_isnamespace(true);
            add_debug(
                space,
                std::format(
                    "Apply namespace @[{}] from {}:{} '{}'",
                    i,
                    line,
                    function,
                    newSpace.dbgorigin()));
            space->set_name(newSpace.name());
            // TODO Fill namespace parameters
        }
    }
}

std::vector<QualType> ReflASTVisitor::getNamespaces(
    c::QualType const&                      In,
    std::optional<c::SourceLocation> const& Loc) {

    c::Decl* decl = nullptr;
    if (const c::TypedefType* tdType = In->getAs<c::TypedefType>()) {
        decl = tdType->getDecl();
    } else if (
        const c::RecordType* recordType = In->getAs<c::RecordType>()) {
        decl = recordType->getDecl();
    } else if (const c::EnumType* enumType = In->getAs<c::EnumType>()) {
        decl = enumType->getDecl();
    } else {
        Diag(
            DiagKind::Warning,
            "Unhandled namespace expansion for %0 (%1 %2)",
            Loc)
            << In << dump(In);
    }

    if (decl) {
        return getNamespaces(decl, Loc);
    } else {
        return {};
    }
}

std::vector<QualType> ReflASTVisitor::getNamespaces(
    c::Decl*                                Decl,
    const std::optional<c::SourceLocation>& Loc) {
    c::DeclContext*       dc = Decl->getDeclContext();
    std::vector<QualType> result;

    int namespaceIndex = 0;

    while (dc) {
        if (c::NamespaceDecl* nns = dyn_cast<c::NamespaceDecl>(dc)) {
            if (!nns->isAnonymousNamespace()
                && !nns->isInlineNamespace()) {
                auto space = &result.emplace_back();
                add_debug(
                    space,
                    std::format(
                        "regular type namespaces @[{}]", namespaceIndex));
                space->set_name(nns->getNameAsString());
                space->set_isnamespace(true);
                ++namespaceIndex;
            }
        } else if (
            c::CXXRecordDecl* rec = dyn_cast<c::CXXRecordDecl>(dc)) {
            auto space = &result.emplace_back();
            add_debug(
                space,
                std::format("type namespace @[{}]", namespaceIndex));
            space->set_name(rec->getNameAsString());
            space->set_isnamespace(false);
            ++namespaceIndex;
        } else if (dyn_cast<c::TranslationUnitDecl>(dc)) {
        } else {
            errs() << dc->getDeclKindName() << "\n";
        }
        dc = dc->getParent();
    }

    std::reverse(result.begin(), result.end());
    return result;
}


void ReflASTVisitor::log_visit(
    c::Decl const*     Decl,
    std::string const& msg,
    int                line,
    char const*        function) {
    if (cli.verbose_log) {
        if (Decl) {
            HSLOG_TRACE(
                "line:{} function:{} msg:{} {}",
                line,
                function,
                msg,
                formatDeclLocation(Decl));

            if (false) {
                HSLOG_TRACE(
                    "{}",
                    std::format(
                        "\n-----------------------------------------------"
                        "---\n{}\n---\n{}\n"
                        "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                        "^",
                        std::format(
                            "line:{} function:{} msg:{}",
                            line,
                            function,
                            msg),
                        (Decl ? "\n" + dump(Decl, 5) : "")));
            }
        } else {
            HSLOG_TRACE("line:{} function:{} msg:{}", line, function, msg);
        }
    }
}


std::vector<QualType> ReflASTVisitor::getNamespaces(
    const c::ElaboratedType*                elab,
    const std::optional<c::SourceLocation>& Loc) {
    if (const c::NestedNameSpecifier* nns = elab->getQualifier()) {
        // Iterate through the Nested Name Specifier, collect them and
        // reverse order
        llvm::SmallVector<c::NestedNameSpecifier const*> spaces;
        while (nns) {
            spaces.push_back(nns);
            nns = nns->getPrefix();
        }

        std::reverse(spaces.begin(), spaces.end());
        std::vector<QualType> result;
        for (auto const* nns : spaces) {
            c::NestedNameSpecifier::SpecifierKind kind = nns->getKind();
            switch (kind) {
                case c::NestedNameSpecifier::Identifier: {
                    auto space = &result.emplace_back();
                    auto name  = nns->getAsIdentifier()->getName().str();
                    add_debug(
                        space,
                        std::format(
                            "Elaborated name identifier '{}'", name));
                    space->set_name(name);
                    assert(!space->name().empty());
                    break;
                }

                case c::NestedNameSpecifier::Namespace: {
                    auto space = &result.emplace_back();
                    auto name  = nns->getAsNamespace()->getNameAsString();
                    add_debug(
                        space,
                        std::format("Elaborated type namespace {}", name));
                    space->set_isnamespace(true);
                    space->set_name(name);
                    assert(!space->name().empty());
                    break;
                }

                case c::NestedNameSpecifier::NamespaceAlias: {
                    auto spaces = getNamespaces(
                        nns->getAsNamespaceAlias()->getNamespace(), Loc);
                    result.insert(
                        result.end(), spaces.begin(), spaces.end());
                    break;
                }

                case c::NestedNameSpecifier::TypeSpec: {
                    auto space  = &result.emplace_back();
                    auto record = nns->getAsType()->getAsRecordDecl();
                    auto name   = record->getNameAsString();
                    add_debug(space, std::format("type spec '{}'", name));
                    space->set_isnamespace(true);
                    space->set_name(name);
                    auto spaces = getNamespaces(record, Loc);
                    result.insert(
                        result.begin(), spaces.begin(), spaces.end());
                    break;
                }

                default: {
                    Diag(
                        DiagKind::Warning,
                        "Unhadled namespace filler %0 kind '%1'",
                        Loc)
                        << kind;
                }
            }
        }
        return result;
    } else {
        return {};
    }
}

bool isTypedefOrUsingType(
    clang::ASTContext*     Ctx,
    clang::QualType const& qualType) {
    // First, get the underlying type by removing qualifiers
    clang::QualType canonicalType = qualType.getCanonicalType();

    // Get the type without sugar (typedefs, using declarations, etc.)
    clang::QualType desugaredType = qualType.getSingleStepDesugaredType(
        *Ctx);

    // If the desugared type is different from the original type,
    // it might be a typedef or using declaration
    if (desugaredType != qualType) {
        // To confirm it's a typedef/using and not another form of sugar,
        // check if we can get the TypedefNameDecl
        if (const auto* typedefType = qualType
                                          ->getAs<clang::TypedefType>()) {
            return true;
        }

        // For 'using' declarations, they also result in TypedefType in the
        // AST So the above check covers both typedef and using
    }

    return false;
}

void ReflASTVisitor::fillTypeTemplates(
    QualType*                               Out,
    c::QualType const&                      In,
    std::optional<c::SourceLocation> const& Loc) {
    auto __scope = scope_debug(Out, "<", ">");

    auto fillArgs = [&](llvm::ArrayRef<c::TemplateArgument> Args) -> void {
        for (c::TemplateArgument const& Arg : Args) {
            auto param = Out->add_parameters();
            add_debug(param, "Type parameter");
            fillTypeRec(param, Arg, Loc);
        }
    };

    c::Type const* type = In.getTypePtr();

    if (auto const* inj = dyn_cast<c::InjectedClassNameType>(type)) {
        auto const* TST = inj->getInjectedTST();
        if (TST != nullptr) {
            add_debug(Out, " templates: injected-class-name");
            fillArgs(TST->template_arguments());
        }
        return;
    }

    if (auto const* TST = dyn_cast<c::TemplateSpecializationType>(type)) {
        add_debug(Out, " templates: template-specialization-type");
        fillArgs(TST->template_arguments());
        return;
    }

    if (auto const* DTST = dyn_cast<
            c::DependentTemplateSpecializationType>(type)) {
        add_debug(
            Out, " templates: dependent-template-specialization-type");
        fillArgs(DTST->template_arguments());
        return;
    }

    if (auto const* RT = dyn_cast<c::RecordType>(type)) {
        if (auto const* spec = dyn_cast<
                c::ClassTemplateSpecializationDecl>(RT->getDecl())) {
            add_debug(
                Out, " templates: class-template-specialization-decl");
            fillArgs(spec->getTemplateArgs().asArray());
        }
        return;
    }

    if (auto const* ET = dyn_cast<c::EnumType>(type)) {
        if (auto const* spec = dyn_cast<
                c::ClassTemplateSpecializationDecl>(
                ET->getDecl()->getDeclContext())) {
            add_debug(
                Out,
                " templates: enum-in-template-specialization-context");
            fillArgs(spec->getTemplateArgs().asArray());
        }
        return;
    }
}

void ReflASTVisitor::fillTypeRec(
    QualType*                               Out,
    c::QualType const&                      In,
    std::optional<c::SourceLocation> const& Loc) {
    auto __scope = scope_debug(Out, "(", ")");

    if (isTypedefOrUsingType(Ctx, In)) { Out->set_istypedef(true); }

    if (In.isConstQualified() || In->isPointerType()) {
        auto cvq = Out->add_qualifiers();
        if (In.isConstQualified()) {
            cvq->set_isconst(true);
            add_debug(Out, " T-const");
        }

        if (In->isPointerType()) {
            cvq->set_ispointer(true);
            add_debug(Out, " T-pointer");
        }

        if (In.isVolatileQualified()) {
            cvq->set_isvolatile(true);
            add_debug(Out, " T-volatile");
        }
    }

    if (const c::UsingType* usType = In->getAs<c::UsingType>()) {
        c::UsingShadowDecl* usDecl = usType->getFoundDecl();
        Out->set_name(usDecl->getNameAsString());
        add_debug(
            Out,
            " using type "
                + formatSourceLocation(
                    usDecl->getLocation(), Ctx->getSourceManager()));

        applyNamespaces(Out, getNamespaces(usDecl, Loc));
    } else if (
        const c::TypedefType* tdType = In->getAs<c::TypedefType>()) {
        c::TypedefNameDecl* tdDecl = tdType->getDecl();
        Out->set_name(tdDecl->getNameAsString());
        add_debug(
            Out,
            " typedef type "
                + formatSourceLocation(
                    tdDecl->getLocation(), Ctx->getSourceManager()));

        applyNamespaces(Out, getNamespaces(tdDecl, Loc));
    } else {
        if (In->isReferenceType()) {
            Out->set_refkind(ReferenceKind::LValue);
            add_debug(Out, " T-reference");
        }

        Out->set_name(In->getTypeClassName());
        Out->set_isbuiltin(In->isBuiltinType());

        if (In->isReferenceType() || In->isPointerType()) {
            add_debug(Out, " >ref/ptr");
            fillTypeRec(Out, In->getPointeeType(), Loc);
        } else if (In->isBooleanType()) {
            add_debug(Out, " >bool");
            Out->set_name("bool");

        } else if (In->isVoidType() || In->isVoidPointerType()) {
            Out->set_name("void");

        } else if (In->isCharType()) {
            add_debug(Out, " >char");
            Out->set_name("char");

        } else if (In->isBuiltinType()) {
            add_debug(Out, " >builtin/unqual");
            auto unqual = In.getUnqualifiedType().getAsString();
            if (unqual.starts_with("const ")) {
                unqual = unqual.substr(strlen("const "));
            }


            Out->set_name(unqual);

        } else if (
            c::ElaboratedType const* elab = In->getAs<
                                            c::ElaboratedType>()) {
            add_debug(Out, " >elaborated");
            fillTypeRec(Out, elab->getNamedType(), Loc);
        } else if (In->isRecordType()) {
            applyNamespaces(Out, getNamespaces(In, Loc));
            auto const name //
                = In->getAs<c::RecordType>()->getDecl()->getNameAsString();

            add_debug(Out, std::format(" >record '{}'", name));
            Out->set_name(name);
        } else if (In->isEnumeralType()) {
            auto const name //
                = In->getAs<c::EnumType>()->getDecl()->getNameAsString();
            applyNamespaces(Out, getNamespaces(In, Loc));
            add_debug(Out, std::format(" >enum '{}'", name));
            Out->set_name(name);

        } else if (In->isFunctionProtoType()) {
            add_debug(Out, " >func");
            Out->set_kind(TypeKind::FunctionPtr);
            const c::FunctionProtoType* FPT = In->getAs<
                c::FunctionProtoType>();
            fillTypeRec(Out->add_parameters(), FPT->getReturnType(), Loc);
            for (c::QualType const& param : FPT->param_types()) {
                fillTypeRec(Out->add_parameters(), param, Loc);
            }
        } else if (In->isConstantArrayType()) {
            add_debug(Out, " >constarray");
            c::ArrayType const* ARRT = dyn_cast<c::ArrayType>(
                In.getTypePtr());
            c::ConstantArrayType const* C_ARRT = dyn_cast<
                c::ConstantArrayType>(ARRT);

            Out->set_kind(TypeKind::Array);
            fillTypeRec(
                Out->add_parameters(), C_ARRT->getElementType(), Loc);
            auto expr_param = Out->add_parameters();
            expr_param->set_kind(TypeKind::TypeExpr);
            if (auto size = C_ARRT->getSizeExpr()) {
                fillExpr(expr_param->mutable_typevalue(), size, Loc);
            } else {
                expr_param->mutable_typevalue()->set_value(
                    std::format("{}", C_ARRT->getSize().getSExtValue()));
                add_debug(expr_param, " >int value");
            }
        } else if (In->isArrayType()) {
            add_debug(Out, " >array");
            c::ArrayType const* ARRT = dyn_cast<c::ArrayType>(
                In.getTypePtr());
            Out->set_kind(TypeKind::Array);
            fillTypeRec(
                Out->add_parameters(), ARRT->getElementType(), Loc);
        } else if (
            auto const* parm = dyn_cast<c::TemplateTypeParmType>(
                In.getTypePtr())) {
            add_debug(Out, " >templatetypeparmtype");
            Out->set_kind(TypeKind::RegularType);
            const c::TemplateTypeParmDecl* D = parm->getDecl();
            if (D != nullptr) {
                Out->set_name(D->getNameAsString());
            } else if (parm->getIdentifier()) {
                Out->set_name(parm->getIdentifier()->getName());
            } else {
                unsigned Depth = parm->getDepth();
                unsigned Index = parm->getIndex();
                Out->set_name(std::format("unnamed_{}_{}", Depth, Index));
            }

        } else if (
            auto const* inj = dyn_cast<c::InjectedClassNameType>(
                In.getTypePtr())) {
            add_debug(Out, " >injectedclassname");
            c::CXXRecordDecl* injDecl = inj->getDecl();
            applyNamespaces(Out, getNamespaces(injDecl, Loc));
            Out->set_kind(TypeKind::RegularType);
            if (inj->getDecl()) {
                Out->set_name(inj->getDecl()->getNameAsString());
            } else {
                Out->set_name("INJ_NO_IDENT");
            }

        } else if (
            auto const* at = dyn_cast<c::AutoType>(In.getTypePtr())) {
            add_debug(Out, " >autotype");
            Out->set_kind(TypeKind::RegularType);
            Out->set_name("auto");
        } else if (
            auto const* PET = dyn_cast<c::PackExpansionType>(
                In.getTypePtr())) {
            add_debug(Out, " >pack-expansion");
            fillTypeRec(Out, PET->getPattern(), Loc);
        } else if (
            const auto* TST = dyn_cast<c::TemplateSpecializationType>(
                In.getTypePtr())) {
            add_debug(Out, " >template-spec-type");
            Out->set_kind(TypeKind::RegularType);

            c::TemplateName TN = TST->getTemplateName();

            if (c::TemplateDecl* TD = TN.getAsTemplateDecl()) {
                Out->set_name(TD->getNameAsString());
                applyNamespaces(Out, getNamespaces(TD, Loc));
            } else {
                Out->set_name("TST_NON_TEMPLATE_DECL");
            }


        } else if (
            const auto* STTP = dyn_cast<c::SubstTemplateTypeParmType>(
                In.getTypePtr())) {
            auto param = Out->add_parameters();
            add_debug(param, "SubstTemplateTypeParmType");
            fillTypeRec(param, STTP->getReplacementType(), Loc);
        } else {
            add_debug(
                Out, std::format("typeclass={}", In->getTypeClassName()));
            Diag(
                DiagKind::Warning,
                "Unhandled serialization for a type '%0' (%1 %2)",
                Loc)
                << In << dump(In);
        }

        fillTypeTemplates(Out, In, Loc);
    }
}

void ReflASTVisitor::fillType(
    QualType*                               Out,
    const c::QualType&                      In,
    const std::optional<c::SourceLocation>& Loc) {
    if (Loc) {
        add_debug(
            Out,
            formatSourceLocation(Loc.value(), Ctx->getSourceManager()));
    }

    fillTypeRec(Out, In, Loc);
}

void ReflASTVisitor::fillTypeRec(
    QualType*                               Out,
    const c::TemplateArgument&              Arg,
    const std::optional<c::SourceLocation>& Loc) {

    switch (Arg.getKind()) {
        case c::TemplateArgument::Type: {
            fillType(Out, Arg.getAsType(), Loc);

            break;
        }
        case c::TemplateArgument::Integral:
        case c::TemplateArgument::Template:
        case c::TemplateArgument::Expression:
        case c::TemplateArgument::Declaration:
        case c::TemplateArgument::TemplateExpansion:
        case c::TemplateArgument::NullPtr:
        case c::TemplateArgument::Null:
        case c::TemplateArgument::StructuralValue:
        case c::TemplateArgument::Pack: {
            Diag(
                DiagKind::Warning,
                "Unhandled template argument %0 type '%1'",
                Loc)
                << Arg.getKind();
        }
    }
}


std::optional<std::string> getExprAsString(
    clang::Expr const*          expr,
    clang::SourceManager const& srcMgr,
    clang::LangOptions const&   langOpts) {
    clang::SourceRange range = expr->getSourceRange();
    // range.setEnd(clang::Lexer::getLocForEndOfToken(
    //     range.getEnd(), 0, srcMgr, langOpts));

    bool invalid = false;

    std::string text = clang::Lexer::getSourceText(
                           clang::CharSourceRange::getTokenRange(range),
                           srcMgr,
                           langOpts,
                           &invalid)
                           .str();

    if (invalid) {
        return std::nullopt;
    } else {
        return text;
    }
}

void ReflASTVisitor::fillExpr(
    Expr*                                   Out,
    const c::Expr*                          In,
    const std::optional<c::SourceLocation>& Loc) {
    if (const auto* boolLiteral = llvm::dyn_cast<
            clang::CXXBoolLiteralExpr>(In)) {
        bool outValue = boolLiteral->getValue();
        Out->set_kind(ExprKind::Lit);
        Out->set_value(outValue ? "true" : "false");
    }
    if (auto val = In->getIntegerConstantExpr(*Ctx)) {
        Out->set_kind(ExprKind::Lit);
        llvm::SmallString<32> Str;
        val->toString(Str);
        Out->set_value(Str.str().str());
    } else {
        auto value = getExprAsString(
            In, Ctx->getSourceManager(), Ctx->getLangOpts());
        if (value) {
            Out->set_kind(ExprKind::Lit);
            Out->set_value(*value);
        } else {
            Diag(
                DiagKind::Warning,
                "Unhandled expression with failed 'get expr as string' "
                "serialization %0",
                Loc);
        }
    }
}

void ReflASTVisitor::fillFieldDecl(
    Record::Field*      sub,
    c::FieldDecl const* field) {
    c::QualType const&   Type    = field->getType();
    c::RecordType const* RecType = Type.getTypePtr()
                                       ->getAs<c::RecordType>();

    HSLOG_DEPTH_SCOPE_ANON();

    log_visit(
        field,
        std::format(
            "field_visit has_rec_type: {} name: {}",
            RecType != nullptr,
            field->getNameAsString()));

    sub->set_name(field->getNameAsString());
    auto doc = getDoc(field);
    if (doc) { sub->set_doc(*doc); }

    if (RecType && RecType->getDecl()) {
        log_visit(
            RecType->getDecl(),
            std::format(
                "Anon:{}", RecType->getDecl()->getNameAsString().empty()));
    }

    if (RecType != nullptr && RecType->getDecl()
        && RecType->getDecl()->getNameAsString().empty()) {
        c::RecordDecl const* RecDecl = RecType->getDecl();
        log_visit(RecDecl);
        fillRecordDecl(sub->mutable_typedecl(), RecType->getDecl());
        sub->set_istypedecl(true);
    } else {
        fillType(
            sub->mutable_type(), field->getType(), field->getLocation());
        sub->set_istypedecl(false);
    }
}

void ReflASTVisitor::fillParmVarDecl(
    Arg*                  arg,
    const c::ParmVarDecl* parm) {
    arg->set_name(parm->getNameAsString());
    auto doc = getDoc(parm);
    if (doc) { arg->set_doc(*doc); }
    QualType* ArgType = arg->mutable_type();
    fillType(ArgType, parm->getType(), parm->getLocation());

    if (parm->hasDefaultArg()) {
        fillExpr(
            arg->mutable_default_(),
            parm->getDefaultArg(),
            parm->getLocation());
    }
}

void ReflASTVisitor::fillMethodDecl(
    Record::Method*         sub,
    c::CXXMethodDecl const* method) {

    if (auto args = get_refl_params(method)) {
        sub->set_reflectionparams(args.value());
    }

    sub->set_name(method->getNameAsString());
    sub->set_isconst(method->isConst());
    sub->set_isstatic(method->isStatic());
    sub->set_isvirtual(method->isVirtual());
    sub->set_isimplicit(method->isImplicit());
    sub->set_isoperator(method->getNameAsString().starts_with("operator"));
    if (sub->isoperator()) {
        sub->set_operatorname(
            method->getNameAsString().substr(strlen("operator")));
    }

    auto doc = getDoc(method);
    if (doc) { sub->set_doc(*doc); }

    if (method->isCopyAssignmentOperator()) {
        sub->set_kind(Record_MethodKind_CopyAssignmentOperator);
    } else if (method->isMoveAssignmentOperator()) {
        sub->set_kind(Record_MethodKind_MoveAssignmentOperator);
    } else if (dyn_cast<c::CXXDestructorDecl>(method)) {
        sub->set_kind(Record_MethodKind_Destructor);
    } else if (auto constr = dyn_cast<c::CXXConstructorDecl>(method)) {
        if (constr->isCopyConstructor()) {
            sub->set_kind(Record_MethodKind_CopyConstructor);
        } else if (constr->isConvertingConstructor(true)) {
            sub->set_kind(Record_MethodKind_ConvertingConstructor);
        } else if (constr->isMoveConstructor()) {
            sub->set_kind(Record_MethodKind_MoveConstructor);
        } else if (constr->isDefaultConstructor()) {
            sub->set_kind(Record_MethodKind_DefaultConstructor);
        } else {
            sub->set_kind(Record_MethodKind_Constructor);
        }
    } else {
        sub->set_kind(Record_MethodKind_Base);
    }

    if (!llvm::isa<c::CXXConstructorDecl>(method)) {
        fillType(
            sub->mutable_returnty(),
            method->getReturnType(),
            method->getLocation());
    }

    for (c::ParmVarDecl const* parm : method->parameters()) {
        fillParmVarDecl(sub->add_args(), parm);
    }
}

void ReflASTVisitor::fillRecordDecl(Record* rec, c::RecordDecl* Decl) {
    rec->set_isforwarddecl(!Decl->isThisDeclarationADefinition());
    rec->set_isunion(Decl->isUnion());


    if (auto args = get_refl_params(Decl)) {
        rec->set_reflectionparams(args.value());
    }

    fillSharedRecordData(rec, Decl);

    auto&           Diags   = Ctx->getDiagnostics();
    c::TypedefDecl* Typedef = findTypedefForDecl(Decl, Ctx);
    if (Decl->getNameAsString().empty() && Typedef == nullptr) {
        Diags.Report(Diags.getCustomDiagID(
            c::DiagnosticsEngine::Warning, "No name provided for '%0'"))
            << Decl;
        rec->set_hasname(false);
    } else {
        auto name = rec->mutable_name();
        rec->set_hasname(true);
        if (Typedef != nullptr) {
            // typedef struct abomination handling -- need to conjure
            // up a name from the scattered bits of brain tissue that
            // was left by the developers of this frankenstein feature.
            fillType(
                rec->mutable_name(),
                Typedef->getASTContext().getTypedefType(Typedef),
                Decl->getLocation());

            name->set_name(Typedef->getNameAsString());

            if (!Decl->getNameAsString().empty()) {
                auto ed = rec->mutable_recorddefname();
                fillType(
                    rec->mutable_name(),
                    Typedef->getASTContext().getTypedefType(Typedef),
                    Decl->getLocation());
                ed->set_name(Decl->getNameAsString());
                ed->set_tag(TypeTag::TypeTagStruct);
            }
            add_debug(name, " > typedef!=nullptr");

        } else {
            fillType(
                name,
                Decl->getASTContext().getRecordType(Decl),
                Decl->getLocation());
            add_debug(name, " > typedef==nullptr");
        }

        add_debug(name, " > " + Decl->getKindName().str());

        if (name->mutable_name()->empty()) {
            Diags.Report(Diags.getCustomDiagID(
                c::DiagnosticsEngine::Warning, "Empty name '%0'"))
                << Decl;
        }

        if (false) {
            std::string              str;
            llvm::raw_string_ostream buf{str};
            Decl->dump(buf);
            buf.flush();
            add_debug(name, str);
        }
    }

    for (c::FieldDecl* field : Decl->fields()) {
        if (shouldVisit(field) && !field->isImplicit()) {
            fillFieldDecl(rec->add_fields(), field);
        }
    }
}


bool ReflASTVisitor::isRefl(c::Decl const* Decl) {
    for (c::AnnotateAttr* Attr : Decl->specific_attrs<c::AnnotateAttr>()) {
        if (Attr->getAnnotation() == REFL_NAME) { return true; }
    }
    return false;
}

std::optional<std::string> ReflASTVisitor::getDoc(c::Decl const* Decl) {
    const c::ASTContext& astContext = Decl->getASTContext();
    const c::RawComment* rawComment = astContext
                                          .getRawCommentForDeclNoCache(
                                              Decl);
    if (rawComment) {
        llvm::StringRef commentText = rawComment->getRawText(
            astContext.getSourceManager());
        return commentText.str();
    } else {
        return std::nullopt;
    }
}

bool ReflASTVisitor::shouldVisit(c::Decl const* Decl) {
    switch (visitMode) {
        case VisitMode::AllAnnotated: {
            return isRefl(Decl);
        }
        case VisitMode::AllTargeted: {
            std::string DeclLoc = getAbsoluteDeclLocation(Decl);
            return !DeclLoc.empty()
                && target_files.find(DeclLoc) != target_files.end();
        }
        case VisitMode::AllMainTranslationUnit: {
            const c::ASTContext& astContext = Decl->getASTContext();
            return astContext.getSourceManager().isInMainFile(
                Decl->getLocation());
        }
    }
}

void ReflASTVisitor::fillCxxRecordDecl(
    Record*                 rec,
    c::CXXRecordDecl const* Decl) {
    rec->set_isforwarddecl(!Decl->isThisDeclarationADefinition());
    fillType(
        rec->mutable_name(),
        Decl->getASTContext().getRecordType(Decl),
        Decl->getLocation());

    if (auto args = get_refl_params(Decl)) {
        rec->set_reflectionparams(args.value());
    }

    if (Decl->hasDefinition()) {
        for (const auto& base : Decl->bases()) {
            auto b = rec->add_bases();
            b->set_isvirtual(base.isVirtual());
            fillType(
                b->mutable_name(), base.getType(), Decl->getLocation());
            switch (base.getAccessSpecifier()) {
                case clang::AccessSpecifier::AS_none:
                    b->set_access(AccessSpecifier::AsNone);
                    break;
                case clang::AccessSpecifier::AS_public:
                    b->set_access(AccessSpecifier::AsPublic);
                    break;
                case clang::AccessSpecifier::AS_private:
                    b->set_access(AccessSpecifier::AsPrivate);
                    break;
                case clang::AccessSpecifier::AS_protected:
                    b->set_access(AccessSpecifier::AsProtected);
                    break;
            }
        }
    }

    fillSharedRecordData(rec, Decl);

    for (c::Decl const* SubDecl : Decl->decls()) {
        if (!shouldVisit(SubDecl)) { continue; }

        if (c::CXXRecordDecl const* SubRecord = dyn_cast<c::CXXRecordDecl>(
                SubDecl);
            SubRecord != nullptr) {
            // Filter out implicit structure records added to the ast of
            // the cxx records
            if (!SubRecord->isImplicit()) {
                c::FieldDecl* FieldDecl = findFieldForDecl(SubRecord, Ctx);

                if (
                    // `struct something { int a; };`
                    // -- not field-bound
                    FieldDecl == nullptr
                    // `struct { int field; }`
                    // -- not an implicit anon field
                    || FieldDecl->isImplicit()
                           && SubRecord->getNameAsString().empty()
                    // `struct Named { int a; } field;`
                    // -- not a joined field+name
                    || (!FieldDecl->isImplicit()
                        && !SubRecord->getNameAsString().empty())) {
                    log_visit(SubRecord);
                    Record* sub_rec = rec->add_nestedrec();
                    fillCxxRecordDecl(sub_rec, SubRecord);
                } else {
                    if (cli.verbose_log) {
                        HSLOG_WARNING(
                            "Dropping decl field decl: {}, implicit: {}, "
                            "is anon "
                            "subrec: {}",
                            FieldDecl != nullptr,
                            (FieldDecl ? (FieldDecl->isImplicit()
                                              ? "implicit"
                                              : "not implicit")
                                       : "no field"),
                            SubRecord->getNameAsString().empty());
                    }
                }
            }

        } else if (c::CXXMethodDecl const* sub = dyn_cast<
                       c::CXXMethodDecl>(SubDecl);
                   sub != nullptr) {

            fillMethodDecl(rec->add_methods(), sub);

        } else if (c::CXXConstructorDecl const* sub = dyn_cast<
                       c::CXXConstructorDecl>(SubDecl);
                   sub != nullptr) {

            fillMethodDecl(rec->add_methods(), sub);

        } else if (c::CXXDestructorDecl const* sub = dyn_cast<
                       c::CXXDestructorDecl>(SubDecl);
                   sub != nullptr) {

            fillMethodDecl(rec->add_methods(), sub);

        } else if (c::FieldDecl const* sub = dyn_cast<c::FieldDecl>(
                       SubDecl);
                   sub != nullptr) {

            if (!sub->isImplicit()) {
                fillFieldDecl(rec->add_fields(), sub);
            }

        } else if (c::FunctionTemplateDecl const* templ = dyn_cast<
                       c::FunctionTemplateDecl>(SubDecl);
                   templ != nullptr) {

            auto* sub = rec->add_methods();

            if (auto args = get_refl_params(templ)) {
                sub->set_reflectionparams(args.value());
            }

            clang::Decl const* templatedDecl = templ->getTemplatedDecl();
            auto const*        method = llvm::cast<clang::CXXMethodDecl>(
                templatedDecl);
            fillMethodDecl(sub, method);

            if (auto doc = getDoc(templ)) { sub->set_doc(*doc); }

        } else if (c::CXXMethodDecl const* sub = dyn_cast<
                       c::CXXMethodDecl>(SubDecl);
                   sub != nullptr) {

            fillMethodDecl(rec->add_methods(), sub);

        } else if (
            llvm::isa<c::IndirectFieldDecl>(SubDecl)
            || llvm::isa<c::UsingDecl>(SubDecl)
            || llvm::isa<c::EnumDecl>(SubDecl)
            || llvm::isa<c::AccessSpecDecl>(SubDecl)
            || llvm::isa<c::FriendDecl>(SubDecl)
            || llvm::isa<c::UsingShadowDecl>(SubDecl)) {
            // pass
        } else {
            Diag(
                DiagKind::Warning,
                "Unknown nested serialization content for %0 %1",
                SubDecl->getLocation())
                << dump(SubDecl);
        }
    }
}

void ReflASTVisitor::fillSharedRecordData(
    Record*                  rec,
    clang::RecordDecl const* Decl) {

    rec->set_isdescribedrecord(isDescribedRecord(Decl));

    if (const auto* specialization = llvm::dyn_cast<
            clang::ClassTemplateSpecializationDecl>(Decl)) {
        rec->set_isexplicitinstantiation(true);
        const clang::TemplateArgumentList& args //
            = specialization->getTemplateArgs();

        for (unsigned i = 0; i < args.size(); ++i) {
            auto param = rec->add_explicittemplateparams();
            fillTypeRec(param, args[i], std::nullopt);
        }
    }
}

bool ReflASTVisitor::VisitCXXRecordDecl(c::CXXRecordDecl* Decl) {
    bool isToplevelDecl = Decl->getDeclContext()->isTranslationUnit()
                       || Decl->getDeclContext()->isNamespace();

    if ((visitMode == VisitMode::AllAnnotated //
         && isRefl(Decl)                      //
         && isToplevelDecl)                   //
        ||                                    //
        ((visitMode == VisitMode::AllTargeted
          || visitMode == VisitMode::AllMainTranslationUnit) //
         && shouldVisit(Decl)                                //
         && isToplevelDecl)) {
        log_visit(Decl);

        llvm::TimeTraceScope timeScope{
            "reflection-visit-record" + Decl->getNameAsString()};

        Record* rec = out->add_records();
        assert(Decl != nullptr);
        fillCxxRecordDecl(rec, Decl);
        if (Decl->hasDefinition()) {
            rec->set_isabstract(Decl->isAbstract());
        }
    } else {
        log_visit(
            nullptr,
            std::format(
                "declaration context is not translation unit '{}' at {}, "
                "isRefl:{}",
                Decl->getNameAsString(),
                formatSourceLocation(Decl),
                isRefl(Decl)));
    }

    return true;
}

bool ReflASTVisitor::VisitFunctionDecl(c::FunctionDecl* Decl) {
    if (shouldVisit(Decl) && !llvm::isa<c::CXXMethodDecl>(Decl)) {
        log_visit(Decl);
        Function* func = out->add_functions();

        if (auto args = get_refl_params(Decl)) {
            func->set_reflectionparams(args.value());
        }

        func->set_name(Decl->getNameAsString());
        for (c::ParmVarDecl* Parm : Decl->parameters()) {
            fillParmVarDecl(func->add_arguments(), Parm);
        }

        add_debug(func, "visit function");

        fillType(
            func->mutable_resultty(),
            Decl->getReturnType(),
            Decl->getLocation());

        for (auto const& space :
             getNamespaces(Decl, Decl->getLocation())) {
            auto added = func->add_spaces();
            *added     = space;
        }
    }
    return true;
}


bool ReflASTVisitor::VisitEnumDecl(c::EnumDecl* Decl) {
    c::TypedefDecl* Typedef = findTypedefForDecl(Decl, Ctx);

    if (Typedef == nullptr && Decl->getNameAsString().empty()) {
        return true;
    }

    if (shouldVisit(Decl)) {
        log_visit(Decl);
        Enum* rec = out->add_enums();
        rec->set_isdescribedenum(isDescribedEnum(Decl));
        rec->set_isforwarddecl(!Decl->isThisDeclarationADefinition());

        if (auto args = get_refl_params(Decl)) {
            rec->set_reflectionparams(args.value());
        }

        std::string origin = (Typedef
                                  ? "typedef:" + Typedef->getNameAsString()
                                  : "")
                           + (Typedef ? "name:" + Decl->getNameAsString()
                                      : "")
                           + formatSourceLocation(
                                 Decl->getLocation(),
                                 Ctx->getSourceManager());

        auto name   = rec->mutable_name();
        auto spaces = getNamespaces(Decl, Decl->getLocation());

        if (Typedef != nullptr) {
            name->set_name(Typedef->getNameAsString());
            add_debug(name, "enum typedef " + origin);
            if (!Decl->getNameAsString().empty()) {
                auto ed = rec->mutable_enumdefname();
                ed->set_name(Decl->getNameAsString());
                add_debug(ed, "enum direct " + origin);
                ed->set_tag(TypeTag::TypeTagEnum);
                applyNamespaces(ed, spaces);
            }
        } else {
            name->set_name(Decl->getNameAsString());
            add_debug(name, "enum direct " + origin);
        }


        applyNamespaces(name, spaces);

        for (c::EnumConstantDecl* field : Decl->enumerators()) {
            Enum_Field* sub = rec->add_fields();
            sub->set_name(field->getNameAsString());
            sub->set_value(field->getInitVal().getExtValue());
        }
    }

    return true;
}

bool ReflASTVisitor::VisitTypedefDecl(c::TypedefDecl* Decl) {
    // bool isStandaloneTypedef = false;
    // if (c::RecordDecl* RecordDecl = Decl->getUnderlyingType()
    //                                     ->getAsRecordDecl()) {

    //     if (shouldVisit(Decl)) { isStandaloneTypedef = true; }

    // } else if (
    //     const auto* enumType = Decl->getUnderlyingType()
    //                                ->getAs<c::EnumType>()) {

    // } else {
    //     if (shouldVisit(Decl)) { isStandaloneTypedef = true; }
    // }

    if (shouldVisit(Decl)) {
        log_visit(Decl);
        Typedef* def = out->add_typedefs();
        def->mutable_name()->set_name(Decl->getNameAsString());
        add_debug(
            def->mutable_name(),
            formatSourceLocation(
                Decl->getLocation(), Ctx->getSourceManager()));
        applyNamespaces(
            def->mutable_name(), getNamespaces(Decl, Decl->getLocation()));

        add_debug(def->mutable_basetype(), " Typedef Decl Visit");

        fillType(
            def->mutable_basetype(),
            Decl->getUnderlyingType(),
            Decl->getLocation());
    }

    return true;
}

bool ReflASTVisitor::VisitRecordDecl(c::RecordDecl* Decl) {
    c::TypedefDecl* Typedef   = findTypedefForDecl(Decl, Ctx);
    c::FieldDecl*   FieldDecl = findFieldForDecl(Decl, Ctx);
    HSLOG_TRACE("VisitRecordDecl {}", formatDeclLocation(Decl));
    HSLOG_DEPTH_SCOPE_ANON();
    if (Decl->getNameAsString().empty() && Typedef == nullptr) {
        log_visit(
            nullptr,
            "empty name and no typedef " + Decl->getNameAsString());
        return true;
    } else if (Decl->getNameAsString().empty() && FieldDecl != nullptr) {
        log_visit(
            nullptr,
            "empty name and has field " + Decl->getNameAsString());
        return true;
    } else if (shouldVisit(Decl)) {
        if (!llvm::isa<c::CXXRecordDecl>(Decl)) {
            log_visit(Decl);
            llvm::TimeTraceScope timeScope{
                "reflection-visit-record" + Decl->getNameAsString()};

            Record* rec = out->add_records();
            fillRecordDecl(rec, Decl);
        } else {
            log_visit(
                nullptr,
                "not a cxx record decl " + Decl->getNameAsString());
        }
    } else {
        log_visit(Decl, "not visiting record");
    }

    return true;
}

bool ReflASTVisitor::IndirectFieldDecl(c::IndirectFieldDecl* Decl) {
    return false;
}

bool SaveProtobufToJsonFile(
    const google::protobuf::Message& message,
    const std::string&               filename,
    bool                             pretty_print = true) {
    // Configure JSON options
    google::protobuf::util::JsonPrintOptions options;
    options.add_whitespace = pretty_print; // For formatted/pretty JSON
    // Include fields with default values
    options.always_print_fields_with_no_presence = true;
    options.preserve_proto_field_names = true; // Use original field names
                                               // (not camelCase)

    // Convert protobuf to JSON string
    std::string  json_string;
    absl::Status status = google::protobuf::util::MessageToJsonString(
        message, &json_string, options);

    if (!status.ok()) {
        std::cerr << "Error converting protobuf to JSON: "
                  << status.message() << std::endl;
        return false;
    }

    // Write JSON to file
    std::ofstream out_file(filename);
    if (!out_file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename
                  << std::endl;
        return false;
    }

    out_file << json_string;
    out_file.close();

    std::cout << "Saved protobuf JSON to " << filename << std::endl;
    return true;
}

std::string getMainFileAbsolutePath(
    const clang::CompilerInstance& compilerInstance) {
    const clang::SourceManager& sourceManager = compilerInstance
                                                    .getSourceManager();
    clang::FileID mainFileID = sourceManager.getMainFileID();

    auto fileEntryRef = sourceManager.getFileEntryRefForID(mainFileID);
    if (fileEntryRef) {
        return std::string{fileEntryRef->getName()};
    } else {
        return "";
    }
}

ReflASTConsumer::ReflASTConsumer(
    clang::CompilerInstance& CI,
    const ReflectionCLI&     cli)
    : out(std::make_unique<TU>())
    , Visitor(&CI.getASTContext(), out.get(), cli)
    , CI(CI)
    , cli(cli) {
    auto callback = std::make_unique<IncludeCollectorCallback>(
        out.get(), &CI.getSourceManager());
    out->set_absolutepath(getMainFileAbsolutePath(CI));
    CI.getPreprocessor().addPPCallbacks(std::move(callback));
}

void ReflASTConsumer::HandleTranslationUnit(c::ASTContext& Context) {
    HSLOG_INFO(
        "Handling translation unit in refl ast consumer with visit mode "
        "{}",
        Visitor.visitMode);

    HSLOG_DEPTH_SCOPE_ANON();
    // When executed with -ftime-trace plugin execution time will be
    // reported in the constructed flame graph.
    llvm::TimeTraceScope timeScope{"reflection-visit-tu"};

    LOGIC_ASSERTION_CHECK(!cli.output.empty(), "CLI output is empty");

    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    // I could not figure out how to properly execute code at the end
    // of the pugin invocation, so :
    // translation unit *visitor* instead, but for now this will do.
    c::DiagnosticsEngine& Diags = CI.getDiagnostics();
    std::ofstream         file{
        cli.output,
        std::ios::out |
            // Overwrite the file if anything is there
            std::ios::trunc | std::ios::binary};

    SaveProtobufToJsonFile(*out, cli.output + ".json");

    if (file.is_open()) {
        out->SerializePartialToOstream(&file);
        file.close();
    } else {
        Diags.Report(Diags.getCustomDiagID(
            c::DiagnosticsEngine::Warning,
            "Could not write compiler reflection data from a file: "
            "'%0'"))
            << cli.output;
    }
}

/// Helper wrapper for clang diagnostic printer
template <unsigned N>
c::DiagnosticBuilder Diag(
    c::Sema&                    S,
    c::DiagnosticsEngine::Level L,
    const char (&FormatString)[N],
    std::optional<c::SourceLocation> const& Loc = std::nullopt) {
    auto& D = S.getASTContext().getDiagnostics();
    if (Loc) {
        return D.Report(*Loc, D.getCustomDiagID(L, FormatString));
    } else {
        return D.Report(D.getCustomDiagID(L, FormatString));
    }
}

c::ParsedAttrInfo::AttrHandling ReflAttrInfo::handleDeclAttribute(
    c::Sema&             S,
    c::Decl*             D,
    const c::ParsedAttr& Attr) const {
    c::AnnotateAttr* created = c::AnnotateAttr::Create(
        S.Context,
        Attr.getAttrName()->deuglifiedName(),
        nullptr,
        0,
        Attr.getRange());


    HSLOG_TRACE("Handle declared attribute on {}", formatDeclLocation(D));
    if (Attr.getNumArgs() == 1) {
        // Process argument if provided
        clang::StringRef jsonStr;
        if (!S.checkStringLiteralArgumentAttr(Attr, 0, jsonStr)) {
            HSLOG_TRACE("Attribute not applied");
            return AttributeNotApplied;
        }

        std::vector<c::Expr*> exprs{Attr.getArgAsExpr(0)};

        // Create attribute with the string argument
        D->addAttr(
            c::AnnotateAttr::Create(
                S.Context,
                Attr.getAttrName()->deuglifiedName(),
                &(*exprs.begin()),
                exprs.size(),
                Attr.getRange()));
    } else {
        // Create attribute with no arguments
        D->addAttr(
            c::AnnotateAttr::Create(
                S.Context,
                Attr.getAttrName()->deuglifiedName(),
                nullptr,
                0,
                Attr.getRange()));
    }

    D->addAttr(created);
    return AttributeApplied;
}

void IncludeCollectorCallback::InclusionDirective(
    clang::SourceLocation             HashLoc,
    clang::Token const&               IncludeTok,
    llvm::StringRef                   FileName,
    bool                              IsAngled,
    clang::CharSourceRange            FilenameRange,
    clang::OptionalFileEntryRef       File,
    llvm::StringRef                   SearchPath,
    llvm::StringRef                   RelativePath,
    clang::Module const*              SuggestedModule,
    bool                              ModuleImported,
    clang::SrcMgr::CharacteristicKind FileType) {

    if (File && sourceManager->isInMainFile(HashLoc)) {
        auto incl = out->add_includes();
        incl->set_absolutepath(File->getName().str());
        incl->set_relativepath(FileName.str());
    }
}
