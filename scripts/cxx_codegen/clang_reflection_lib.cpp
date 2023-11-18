#include "clang_reflection_lib.hpp"

#include <llvm/Support/TimeProfiler.h>
#include <format>

std::string getAbsoluteDeclLocation(clang::Decl* Decl) {
    clang::SourceLocation       loc           = Decl->getLocation();
    const clang::ASTContext&    astContext    = Decl->getASTContext();
    clang::SourceManager const& sourceManager = astContext
                                                    .getSourceManager();

    std::string filePath;
    if (loc.isValid()) {
        clang::SourceLocation fullLoc = sourceManager.getExpansionLoc(loc);
        if (fullLoc.isValid()) {
            filePath = sourceManager.getFilename(fullLoc).str();
        } else {
            filePath = sourceManager.getFilename(loc).str();
        }
    }

    return filePath;
}

std::vector<QualType> ReflASTVisitor::getNamespaces(
    clang::NamespaceDecl const*                 Namespace,
    std::optional<clang::SourceLocation> const& Loc) {
    std::vector<QualType> result;
    if (!Namespace->isAnonymousNamespace()
        && !Namespace->isInlineNamespace()) {
        auto space = &result.emplace_back();
        space->set_name(Namespace->getNameAsString());
        space->set_dbgorigin(std::format(
            "Namespace visitation of '{}'", Namespace->getNameAsString()));
        space->set_isnamespace(true);
        assert(!space->name().empty());
    }

    if (Namespace->getDeclContext()->isNamespace()) {
        auto spaces = getNamespaces(
            clang::dyn_cast<clang::NamespaceDecl>(
                Namespace->getDeclContext()),
            Loc);
        result.insert(result.end(), spaces.begin(), spaces.end());
    }

    return result;
}


void ReflASTVisitor::applyNamespaces(
    QualType*                    Out,
    const std::vector<QualType>& Namespaces) {
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
            QualType const* _old = oldNamespaces.at(i);
            QualType const* _new = newNamespaces.at(i);
            if (_old->name() != _new->name()) {
                llvm::outs() << std::format(
                    "Mismatching namespace types at index {} '{}' (from "
                    "{}) != '{}' (from {})\n",
                    i,
                    _old->name(),
                    _old->dbgorigin(),
                    _new->name(),
                    _new->dbgorigin());
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
            space->set_dbgorigin(newSpace.dbgorigin());
            space->set_name(newSpace.name());
            // TODO Fill namespace parameters
        }
    }
}

std::vector<QualType> ReflASTVisitor::getNamespaces(
    clang::QualType const&                      In,
    std::optional<clang::SourceLocation> const& Loc) {

    clang::Decl* decl = nullptr;
    if (const clang::TypedefType* tdType = In->getAs<
                                           clang::TypedefType>()) {
        decl = tdType->getDecl();
    } else if (
        const clang::RecordType* recordType = In->getAs<
                                              clang::RecordType>()) {
        decl = recordType->getDecl();
    } else {
        Diag(
            DiagKind::Warning,
            "Unhandled namespace expansion for %0 (%1)",
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
    clang::Decl*                                Decl,
    const std::optional<clang::SourceLocation>& Loc) {
    llvm::SmallVector<clang::NamespaceDecl*> spaces;
    clang::DeclContext*                      dc = Decl->getDeclContext();
    while (dc) {
        if (clang::NamespaceDecl* ns = llvm::dyn_cast<
                clang::NamespaceDecl>(dc)) {
            spaces.push_back(ns);
        }
        dc = dc->getParent();
    }
    std::reverse(spaces.begin(), spaces.end());

    std::vector<QualType> result;

    for (auto const* nns : spaces) {
        if (!nns->isAnonymousNamespace() && !nns->isInlineNamespace()) {
            auto space = &result.emplace_back();
            space->set_dbgorigin("regular type namespaces");
            space->set_name(nns->getNameAsString());
            space->set_isnamespace(true);
        }
    }

    return result;
}


std::vector<QualType> ReflASTVisitor::getNamespaces(
    const clang::ElaboratedType*                elab,
    const std::optional<clang::SourceLocation>& Loc) {
    if (const clang::NestedNameSpecifier* nns = elab->getQualifier()) {
        // Iterate through the Nested Name Specifier, collect them and
        // reverse order
        llvm::SmallVector<clang::NestedNameSpecifier const*> spaces;
        while (nns) {
            spaces.push_back(nns);
            nns = nns->getPrefix();
        }

        std::reverse(spaces.begin(), spaces.end());
        std::vector<QualType> result;
        for (auto const* nns : spaces) {
            clang::NestedNameSpecifier::SpecifierKind kind = nns->getKind();
            switch (kind) {
                case clang::NestedNameSpecifier::Identifier: {
                    auto space = &result.emplace_back();
                    space->set_dbgorigin("Elaborated name identifier");
                    space->set_name(nns->getAsIdentifier()->getName());
                    assert(!space->name().empty());
                    break;
                }

                case clang::NestedNameSpecifier::Namespace: {
                    auto space = &result.emplace_back();
                    space->set_dbgorigin("Elaborated type namespace");
                    space->set_isnamespace(true);
                    space->set_name(
                        nns->getAsNamespace()->getNameAsString());
                    assert(!space->name().empty());
                    break;
                }

                case clang::NestedNameSpecifier::NamespaceAlias: {
                    auto spaces = getNamespaces(
                        nns->getAsNamespaceAlias()->getNamespace(), Loc);
                    result.insert(
                        result.end(), spaces.begin(), spaces.end());
                    break;
                }

                default: {
                    Diag(
                        DiagKind::Warning,
                        "Unahdled namespace filler kind '%0'",
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

void ReflASTVisitor::fillType(
    QualType*                                   Out,
    const clang::QualType&                      In,
    const std::optional<clang::SourceLocation>& Loc) {

    if (const clang::TypedefType* tdType = In->getAs<
                                           clang::TypedefType>()) {
        clang::TypedefNameDecl* tdDecl = tdType->getDecl();
        Out->set_name(tdDecl->getNameAsString());
        Out->set_dbgorigin(
            "typedef type "
            + tdDecl->getLocation().printToString(
                Ctx->getSourceManager()));
        applyNamespaces(Out, getNamespaces(tdDecl, Loc));
    } else {
        if (In.isConstQualified()) {
            Out->set_isconst(true);
            Out->mutable_dbgorigin()->append(" T-const");
        }

        if (In->isReferenceType()) {
            Out->set_refkind(ReferenceKind::LValue);
            Out->mutable_dbgorigin()->append(" T-reference");
        }

        if (In->isPointerType()) {
            Out->set_ispointer(true);
            Out->mutable_dbgorigin()->append(" T-pointer");
        }

        if (In->isReferenceType() || In->isPointerType()) {
            Out->mutable_dbgorigin()->append(" >ref/ptr");
            fillType(Out, In->getPointeeType(), Loc);
        } else if (In->isBooleanType()) {
            Out->mutable_dbgorigin()->append(" >bool");
            Out->set_name("bool");

        } else if (In->isCharType()) {
            Out->mutable_dbgorigin()->append(" >char");
            Out->set_name("char");

        } else if (In->isBuiltinType()) {
            Out->mutable_dbgorigin()->append(" >builtin");
            Out->set_name(In.getAsString());

        } else if (
            clang::ElaboratedType const* elab = In->getAs<
                                                clang::ElaboratedType>()) {
            Out->mutable_dbgorigin()->append(" >elaborated");
            applyNamespaces(Out, getNamespaces(elab, Loc));
            fillType(Out, elab->getNamedType(), Loc);

        } else if (In->isRecordType()) {
            applyNamespaces(Out, getNamespaces(In, Loc));

            Out->set_dbgorigin(
                "record type filler "
                + Loc->printToString(Ctx->getSourceManager()));

            Out->set_name(In->getAs<clang::RecordType>()
                              ->getDecl()
                              ->getNameAsString());
        } else if (In->isEnumeralType()) {
            Out->mutable_dbgorigin()->append(" >enum");
            Out->set_name(In->getAs<clang::EnumType>()
                              ->getDecl()
                              ->getNameAsString());

        } else if (In->isFunctionProtoType()) {
            Out->mutable_dbgorigin()->append(" >func");
            Out->set_kind(TypeKind::FunctionPtr);
            const clang::FunctionProtoType* FPT = In->getAs<
                clang::FunctionProtoType>();
            fillType(Out->add_parameters(), FPT->getReturnType(), Loc);
            for (clang::QualType const& param : FPT->param_types()) {
                fillType(Out->add_parameters(), param, Loc);
            }


        } else if (In->isConstantArrayType()) {
            Out->mutable_dbgorigin()->append(" >constarray");
            clang::ArrayType const* ARRT = dyn_cast<clang::ArrayType>(
                In.getTypePtr());

            clang::ConstantArrayType const* C_ARRT = dyn_cast<
                clang::ConstantArrayType>(ARRT);

            Out->set_kind(TypeKind::Array);
            fillType(Out->add_parameters(), C_ARRT->getElementType(), Loc);
            Out->add_parameters()->set_kind(TypeKind::TypeExpr);
            if (auto size = C_ARRT->getSizeExpr()) {
                fillExpr(
                    Out->add_parameters()->mutable_typevalue(), size, Loc);
            }

        } else if (In->isArrayType()) {
            Out->mutable_dbgorigin()->append(" >array");
            clang::ArrayType const* ARRT = dyn_cast<clang::ArrayType>(
                In.getTypePtr());
            Out->set_kind(TypeKind::Array);
            fillType(Out->add_parameters(), ARRT->getElementType(), Loc);

        } else {
            Diag(
                DiagKind::Warning,
                "Unhandled serialization for a type %0 (%1)",
                Loc)
                << In << dump(In);
        }

        if (const auto* TST = llvm::dyn_cast<
                clang::TemplateSpecializationType>(In.getTypePtr())) {
            for (clang::TemplateArgument const& Arg :
                 TST->template_arguments()) {
                auto param = Out->add_parameters();
                param->set_dbgorigin("Type parameter");
                fillType(param, Arg, Loc);
            }
        }
    }
}

void ReflASTVisitor::fillType(
    QualType*                                   Out,
    const clang::TemplateArgument&              Arg,
    const std::optional<clang::SourceLocation>& Loc) {

    switch (Arg.getKind()) {
        case clang::TemplateArgument::Type: {
            fillType(Out, Arg.getAsType(), Loc);

            break;
        }
        case clang::TemplateArgument::Integral:
        case clang::TemplateArgument::Template:
        case clang::TemplateArgument::Expression:
        case clang::TemplateArgument::Declaration:
        case clang::TemplateArgument::TemplateExpansion:
        case clang::TemplateArgument::NullPtr:
        case clang::TemplateArgument::Null:
        case clang::TemplateArgument::Pack: {
            Diag(
                DiagKind::Warning,
                "Unhandled template argument type '%0'",
                Loc)
                << Arg.getKind();
        }
    }
}


void ReflASTVisitor::fillExpr(
    Expr*                                       Out,
    const clang::Expr*                          In,
    const std::optional<clang::SourceLocation>& Loc) {
    if (auto val = In->getIntegerConstantExpr(*Ctx)) {
        Out->set_kind(ExprKind::Lit);
        llvm::SmallString<32> Str;
        val->toString(Str);
        Out->set_value(Str.str().str());
    } else {
        Diag(DiagKind::Warning, "Unhandled expression filled.", Loc);
    }
}

void ReflASTVisitor::fillFieldDecl(
    Record::Field*    sub,
    clang::FieldDecl* field) {
    sub->set_name(field->getNameAsString());
    auto doc = getDoc(field);
    if (doc) {
        sub->set_doc(*doc);
    }
    fillType(sub->mutable_type(), field->getType(), field->getLocation());
}

void ReflASTVisitor::fillParmVarDecl(
    Arg*                      arg,
    const clang::ParmVarDecl* parm) {
    arg->set_name(parm->getNameAsString());
    auto doc = getDoc(parm);
    if (doc) {
        arg->set_doc(*doc);
    }
    QualType* ArgType = arg->mutable_type();
    fillType(ArgType, parm->getType(), parm->getLocation());

    //    if (parm->getNameAsString() == "path") {
    //        Diag(
    //            DiagKind::Warning,
    //            "Adding serialization information for %0 %1 %2\n",
    //            parm->getLocation())
    //            << parm
    //            << std::format(
    //                   "Ref {} Const {}\n",
    //                   parm->getType()->isReferenceType(),
    //                   parm->getType().isConstQualified())
    //            << dump(parm->getType());
    //    }

    if (parm->hasDefaultArg()) {
        fillExpr(
            arg->mutable_default_(),
            parm->getDefaultArg(),
            parm->getLocation());
    }
}

void ReflASTVisitor::fillMethodDecl(
    Record::Method*       sub,
    clang::CXXMethodDecl* method) {


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
    if (doc) {
        sub->set_doc(*doc);
    }

    if (method->isCopyAssignmentOperator()) {
        sub->set_kind(Record_MethodKind_CopyAssignmentOperator);
    } else if (method->isMoveAssignmentOperator()) {
        sub->set_kind(Record_MethodKind_MoveAssignmentOperator);
    } else if (llvm::dyn_cast<clang::CXXDestructorDecl>(method)) {
        sub->set_kind(Record_MethodKind_Destructor);
    } else if (
        auto constr = llvm::dyn_cast<clang::CXXConstructorDecl>(method)) {
        if (constr->isCopyConstructor()) {
            sub->set_kind(Record_MethodKind_CopyConstructor);
        } else if (constr->isConvertingConstructor(true)) {
            sub->set_kind(Record_MethodKind_DefaultConstructor);
        } else if (constr->isMoveConstructor()) {
            sub->set_kind(Record_MethodKind_MoveConstructor);
        } else if (constr->isDefaultConstructor()) {
            sub->set_kind(Record_MethodKind_DefaultConstructor);
        }
    } else {
        sub->set_kind(Record_MethodKind_Base);
    }

    fillType(
        sub->mutable_returnty(),
        method->getReturnType(),
        method->getLocation());

    for (clang::ParmVarDecl const* parm : method->parameters()) {
        fillParmVarDecl(sub->add_args(), parm);
    }
}

bool ReflASTVisitor::isRefl(clang::Decl* Decl) {
    for (clang::AnnotateAttr* Attr :
         Decl->specific_attrs<clang::AnnotateAttr>()) {
        if (Attr->getAnnotation() == REFL_NAME) {
            return true;
        }
    }
    return false;
}

std::optional<std::string> ReflASTVisitor::getDoc(
    clang::Decl const* Decl) {
    const clang::ASTContext& astContext = Decl->getASTContext();
    const clang::RawComment* rawComment = astContext
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

bool ReflASTVisitor::shouldVisit(clang::Decl* Decl) {
    switch (visitMode) {
        case VisitMode::AllAnnotated: {
            return isRefl(Decl);
        }
        case VisitMode::AllTargeted: {
            std::string DeclLoc = getAbsoluteDeclLocation(Decl);
            //            std::cerr << "Decl location " <<
            //            Decl->getDeclKindName() << " "
            //                      << DeclLoc << std::endl;
            return !DeclLoc.empty()
                && targetFiles.find(DeclLoc) != targetFiles.end();
        }
    }
}

bool ReflASTVisitor::VisitCXXRecordDecl(clang::CXXRecordDecl* Decl) {
    if (shouldVisit(Decl)) {
        llvm::TimeTraceScope timeScope{
            "reflection-visit-record" + Decl->getNameAsString()};

        Record* rec = out->add_records();
        rec->set_isforwarddecl(!Decl->isThisDeclarationADefinition());
        fillType(
            rec->mutable_name(),
            Decl->getASTContext().getRecordType(Decl),
            Decl->getLocation());

        for (clang::FieldDecl* field : Decl->fields()) {
            if (shouldVisit(field)) {
                fillFieldDecl(rec->add_fields(), field);
            }
        }

        for (clang::CXXMethodDecl* method : Decl->methods()) {
            if (shouldVisit(method)) {
                fillMethodDecl(rec->add_methods(), method);
            }
        }
    }


    return true;
}

bool ReflASTVisitor::VisitFunctionDecl(clang::FunctionDecl* Decl) {
    if (shouldVisit(Decl)) {
        Function* func = out->add_functions();
        func->set_name(Decl->getNameAsString());
        for (clang::ParmVarDecl* Parm : Decl->parameters()) {
            fillParmVarDecl(func->add_arguments(), Parm);
        }

        fillType(
            func->mutable_resultty(),
            Decl->getReturnType(),
            Decl->getLocation());
    }
    return true;
}

bool ReflASTVisitor::VisitEnumDecl(
    clang::EnumDecl*    Decl,
    clang::TypedefDecl* Typedef) {
    if (Typedef == nullptr && Decl->getNameAsString().empty()) {
        return true;
    }

    if (shouldVisit(Decl)) {
        Diag(
            DiagKind::Note,
            "Adding serialization information for %0",
            Decl->getLocation())
            << Decl;
        Enum* rec = out->add_enums();
        rec->set_isforwarddecl(!Decl->isThisDeclarationADefinition());
        std::string origin = (Typedef
                                  ? "typedef:" + Typedef->getNameAsString()
                                  : "")
                           + (Typedef ? "name:" + Decl->getNameAsString()
                                      : "")
                           + Typedef->getLocation().printToString(
                               Ctx->getSourceManager());

        auto name   = rec->mutable_name();
        auto spaces = getNamespaces(Decl, Decl->getLocation());

        if (Typedef != nullptr) {
            name->set_name(Typedef->getNameAsString());
            name->set_dbgorigin("enum typedef " + origin);
            if (!Decl->getNameAsString().empty()) {
                auto ed = rec->mutable_enumdefname();
                ed->set_name(Decl->getNameAsString());
                ed->set_dbgorigin("enum direct " + origin);
                ed->set_tag(TypeTag::TypeTagEnum);
                applyNamespaces(ed, spaces);
            }
        } else {
            name->set_name(Decl->getNameAsString());
            name->set_dbgorigin("enum direct " + origin);
        }


        applyNamespaces(name, spaces);

        for (clang::EnumConstantDecl* field : Decl->enumerators()) {
            Enum_Field* sub = rec->add_fields();
            sub->set_name(field->getNameAsString());
            sub->set_value(field->getInitVal().getExtValue());
        }
    }

    return true;
}

bool ReflASTVisitor::VisitTypedefDecl(clang::TypedefDecl* Decl) {
    if (clang::RecordDecl* RecordDecl = Decl->getUnderlyingType()
                                            ->getAsRecordDecl()) {

        return VisitRecordDecl(RecordDecl, Decl);
    } else if (
        const auto* enumType = Decl->getUnderlyingType()
                                   ->getAs<clang::EnumType>()) {
        if (enumType->getDecl()->getNameAsString().empty()) {
            return VisitEnumDecl(enumType->getDecl(), Decl);
        } else {
            goto is_regular_typedef;
        }

    } else {
    is_regular_typedef:
        if (shouldVisit(Decl)) {
            Typedef* def = out->add_typedefs();
            def->mutable_name()->set_name(Decl->getNameAsString());
            def->mutable_name()->set_dbgorigin(
                Decl->getLocation().printToString(
                    Ctx->getSourceManager()));
            applyNamespaces(
                def->mutable_name(),
                getNamespaces(Decl, Decl->getLocation()));

            fillType(
                def->mutable_basetype(),
                Decl->getUnderlyingType(),
                Decl->getLocation());
        }

        return true;
    }
}

bool ReflASTVisitor::VisitRecordDecl(
    clang::RecordDecl*  Decl,
    clang::TypedefDecl* Typedef) {
    if (Decl->getNameAsString().empty() && Typedef == nullptr) {
        return true;
    } else if (shouldVisit(Decl)) {
        llvm::TimeTraceScope timeScope{
            "reflection-visit-record" + Decl->getNameAsString()};

        Record* rec = out->add_records();
        rec->set_isforwarddecl(!Decl->isThisDeclarationADefinition());
        auto name = rec->mutable_name();
        if (Typedef != nullptr) {
            // typedef struct abomination handling -- need to conjure up a
            // name from the scattered bits of brain tissue that was left
            // by the developers of this frankenstein feature.
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

        } else {
            fillType(
                name,
                Decl->getASTContext().getRecordType(Decl),
                Decl->getLocation());
        }


        for (clang::FieldDecl* field : Decl->fields()) {
            if (shouldVisit(field)) {
                fillFieldDecl(rec->add_fields(), field);
            }
        }
    }

    return true;
}


void ReflASTConsumer::HandleTranslationUnit(clang::ASTContext& Context) {
    // When executed with -ftime-trace plugin execution time will be
    // reported in the constructed flame graph.
    llvm::TimeTraceScope timeScope{"reflection-visit-tu"};

    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    // I could not figure out how to properly execute code at the end
    // of the pugin invocation, so :
    // translation unit *visitor* instead, but for now this will do.
    clang::DiagnosticsEngine& Diags = CI.getDiagnostics();
    std::string               path  = outputPathOverride
                                        ? *outputPathOverride
                                        : CI.getFrontendOpts().OutputFile + ".pb";
    std::ofstream             file{
        path,
        std::ios::out |
            // Overwrite the file if anything is there
            std::ios::trunc | std::ios::binary};


    if (file.is_open()) {
        out->SerializePartialToOstream(&file);
        file.close();
    } else {
        Diags.Report(Diags.getCustomDiagID(
            clang::DiagnosticsEngine::Warning,
            "Could not write compiler reflection data from a file: "
            "'%0'"))
            << path;
    }
}

/// Helper wrapper for clang diagnostic printer
template <unsigned N>
clang::DiagnosticBuilder Diag(
    clang::Sema&                    S,
    clang::DiagnosticsEngine::Level L,
    const char (&FormatString)[N],
    std::optional<clang::SourceLocation> const& Loc = std::nullopt) {
    auto& D = S.getASTContext().getDiagnostics();
    if (Loc) {
        return D.Report(*Loc, D.getCustomDiagID(L, FormatString));
    } else {
        return D.Report(D.getCustomDiagID(L, FormatString));
    }
}

clang::ParsedAttrInfo::AttrHandling ExampleAttrInfo::handleDeclAttribute(
    clang::Sema&             S,
    clang::Decl*             D,
    const clang::ParsedAttr& Attr) const {
    clang::AnnotateAttr* created = clang::AnnotateAttr::Create(
        S.Context,
        Attr.getAttrName()->deuglifiedName(),
        nullptr,
        0,
        Attr.getRange());

    D->addAttr(created);
    return AttributeApplied;
}
