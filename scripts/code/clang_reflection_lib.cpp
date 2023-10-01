#include "clang_reflection_lib.hpp"

#include <llvm/Support/TimeProfiler.h>

void ReflASTVisitor::fillNamespaces(
    QualType*                                   Out,
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
        for (auto const* nns : spaces) {
            clang::NestedNameSpecifier::SpecifierKind kind = nns->getKind();
            QualType* Space = Out->add_spaces();
            switch (kind) {
                case clang::NestedNameSpecifier::Identifier: {
                    Space->set_name(nns->getAsIdentifier()->getName());
                    break;
                }

                case clang::NestedNameSpecifier::Namespace: {
                    Space->set_name(
                        nns->getAsNamespace()->getNameAsString());
                    break;
                }

                case clang::NestedNameSpecifier::NamespaceAlias: {
                    // Namespace aliases must be resolved as protobuf
                    // QualType definition is designed to map
                    // non-aliased type
                    Diag(
                        DiagKind::Warning,
                        "TODO Implement namespace alias expansion",
                        Loc);
                    Space->set_name(
                        nns->getAsNamespaceAlias()->getNameAsString());
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
    }
}

void ReflASTVisitor::fillType(
    QualType*                                   Out,
    const clang::QualType&                      In,
    const std::optional<clang::SourceLocation>& Loc) {

    Out->set_isconst(In.isConstQualified());
    Out->set_isref(In->isReferenceType());
    if (In->isReferenceType()) {
        fillType(Out, In->getPointeeType(), Loc);
    } else if (In->isBuiltinType()) {
        Out->set_name(In.getAsString());
    } else if (
        clang::ElaboratedType const* elab = In->getAs<
                                            clang::ElaboratedType>()) {
        // 'fill' operations are additive for namespaces
        fillNamespaces(Out, elab, Loc);
        fillType(Out, elab->getNamedType(), Loc);
    } else if (In->isRecordType()) {
        Out->set_name(
            In->getAs<clang::RecordType>()->getDecl()->getNameAsString());
    } else if (In->isEnumeralType()) {
        Out->set_name(
            In->getAs<clang::EnumType>()->getDecl()->getNameAsString());
    } else {
        Diag(
            DiagKind::Warning,
            "Unhandled serialization for a type %0 (%1)",
            Loc)
            << In << dump(In);
    }

    // TODO unwrap all typedefs
    // TODO get declaration location scope with all namespaces
    if (const auto* TST = llvm::dyn_cast<
            clang::TemplateSpecializationType>(In.getTypePtr())) {
        for (clang::TemplateArgument const& Arg :
             TST->template_arguments()) {
            fillType(Out->add_parameters(), Arg, Loc);
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
    fillType(arg->mutable_type(), parm->getType(), parm->getLocation());
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

bool ReflASTVisitor::VisitCXXRecordDecl(
    clang::CXXRecordDecl* Declaration) {
    if (isRefl(Declaration)) {
        llvm::TimeTraceScope timeScope{
            "reflection-visit-record" + Declaration->getNameAsString()};

        Diag(
            DiagKind::Note,
            "Adding serialization information for %0",
            Declaration->getLocation())
            << Declaration;

        Record* rec = out->add_records();
        rec->set_name(Declaration->getNameAsString());

        for (clang::FieldDecl* field : Declaration->fields()) {
            if (isRefl(field)) {
                fillFieldDecl(rec->add_fields(), field);
            }
        }

        for (clang::CXXMethodDecl* method : Declaration->methods()) {
            if (isRefl(method)) {
                fillMethodDecl(rec->add_methods(), method);
            }
        }
    }


    return true;
}

bool ReflASTVisitor::VisitEnumDecl(clang::EnumDecl* Decl) {
    if (isRefl(Decl)) {
        Diag(
            DiagKind::Note,
            "Adding serialization information for %0",
            Decl->getLocation())
            << Decl;
        Enum* rec = out->add_enums();
        rec->set_name(Decl->getNameAsString());

        for (clang::EnumConstantDecl* field : Decl->enumerators()) {
            Enum_Field* sub = rec->add_fields();
            sub->set_name(field->getNameAsString());
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
        Diags.Report(Diags.getCustomDiagID(
            clang::DiagnosticsEngine::Remark,
            "Wrote compiler reflection to file: "
            "'%0'"))
            << path;
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
