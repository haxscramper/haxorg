#pragma once

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/ASTConsumers.h>

#include <hstd/stdlib/Set.hpp>

#include "reflection_config.hpp"
#include "reflection_defs.pb.h"


struct BranchingIncludeCollectorCallback : public clang::PPCallbacks {
    clang::SourceManager* SM;
    clang::Preprocessor*  PP;
    TU*                   Out;

    IncludeVisit* Root = nullptr;

    static std::string getMainFileAbsolutePath(clang::CompilerInstance& CI) {
        clang::SourceManager&       SM     = CI.getSourceManager();
        clang::FileID               mainId = SM.getMainFileID();
        clang::OptionalFileEntryRef file   = SM.getFileEntryRefForID(mainId);
        if (file) {
            return file->getName().str();
        } else {
            return SM.getFileEntryRefForID(mainId)->getName().str();
        }
    }

    static std::string getRealPathForLoc(
        clang::SourceManager const& SM,
        clang::SourceLocation       Loc) {
        clang::SourceLocation spelling = SM.getSpellingLoc(Loc);
        if (spelling.isInvalid()) { return {}; }

        clang::FileID               fid  = SM.getFileID(spelling);
        clang::OptionalFileEntryRef file = SM.getFileEntryRefForID(fid);
        if (file) { return file->getName().str(); }

        if (auto oldFile = SM.getFileEntryRefForID(fid)) {
            return oldFile->getName().str();
        }

        return {};
    }

    static unsigned countPhysicalLines(
        clang::SourceManager const& SM,
        clang::FileID               fid) {
        llvm::StringRef data = SM.getBufferData(fid);
        if (data.empty()) { return 0; }

        unsigned lines = 1;
        for (char c : data) {
            if (c == '\n') { ++lines; }
        }
        return lines;
    }

    struct PendingInclude {
        std::string IncludingFilePath;
        std::string RelativePath;
        std::string AbsolutePath;
    };

    struct VisitFrame {
        IncludeVisit*                Node;
        clang::FileID                File;
        std::string                  AbsolutePath;
        std::unordered_set<unsigned> ProcessedLines;
    };


    std::vector<VisitFrame>    ActiveStack;
    std::deque<PendingInclude> PendingIncludes;

    BranchingIncludeCollectorCallback(
        TU*                   tu,
        clang::SourceManager* sourceManager,
        clang::Preprocessor*  preprocessor)
        : SM(sourceManager), PP(preprocessor), Out(tu) {}

    void ensureRoot() {
        if (Root) { return; }

        Root = Out->mutable_mainfileincludetree();
        Root->set_absolutepath(getMainFileAbsolutePathFromSM());
        Root->set_relativepath("");

        clang::FileID mainId = SM->getMainFileID();

        ActiveStack.push_back(
            VisitFrame{
                .Node           = Root,
                .File           = mainId,
                .AbsolutePath   = Root->absolutepath(),
                .ProcessedLines = {},
            });

        Root->set_directlinecount(countPhysicalLines(*SM, mainId));
    }

    std::string getMainFileAbsolutePathFromSM() {
        clang::FileID               mainId = SM->getMainFileID();
        clang::OptionalFileEntryRef file   = SM->getFileEntryRefForID(mainId);
        if (file) {
            return file->getName().str();
        } else if (auto oldFile = SM->getFileEntryRefForID(mainId)) {
            return oldFile->getName().str();
        } else {
            return {};
        }
    }

    void markLine(clang::SourceLocation Loc) {
        if (ActiveStack.empty()) { return; }

        clang::SourceLocation spelling = SM->getSpellingLoc(Loc);
        if (spelling.isInvalid()) { return; }

        clang::FileID fid = SM->getFileID(spelling);
        VisitFrame&   top = ActiveStack.back();
        if (fid != top.File) { return; }

        unsigned line = SM->getSpellingLineNumber(spelling);
        if (line != 0) { top.ProcessedLines.insert(line); }
    }


    std::optional<PendingInclude> popPendingForParent(std::string const& parentPath) {
        for (auto it = PendingIncludes.begin(); it != PendingIncludes.end(); ++it) {
            if (it->IncludingFilePath == parentPath) {
                PendingInclude result = *it;
                PendingIncludes.erase(it);
                return result;
            }
        }
        return std::nullopt;
    }

    void enterFile(clang::SourceLocation Loc) {
        if (!Root) { ensureRoot(); }

        clang::SourceLocation spelling = SM->getSpellingLoc(Loc);
        if (spelling.isInvalid()) { return; }

        clang::FileID enteredFile = SM->getFileID(spelling);

        auto fe = SM->getFileEntryRefForID(enteredFile);
        if (!fe) { return; } // skip non-physical files

        if (!ActiveStack.empty() && ActiveStack.back().File == enteredFile) { return; }

        if (ActiveStack.empty()) { return; }

        std::string enteredPath = getRealPathForLoc(*SM, spelling);
        std::string parentPath  = ActiveStack.back().AbsolutePath;

        auto pending = popPendingForParent(parentPath);

        IncludeVisit* nested = ActiveStack.back().Node->add_nested();
        nested->set_absolutepath(enteredPath);
        nested->set_directlinecount(countPhysicalLines(*SM, enteredFile));

        if (pending) {
            nested->set_relativepath(pending->RelativePath);
            if (nested->absolutepath().empty()) {
                nested->set_absolutepath(pending->AbsolutePath);
            }
        } else {
            nested->set_relativepath("");
        }

        ActiveStack.push_back(
            VisitFrame{
                .Node           = nested,
                .File           = enteredFile,
                .AbsolutePath   = nested->absolutepath(),
                .ProcessedLines = {},
            });

        markLine(Loc);
    }


    void InclusionDirective(
        clang::SourceLocation HashLoc,
        clang::Token const&,
        llvm::StringRef FileName,
        bool,
        clang::CharSourceRange,
        clang::OptionalFileEntryRef File,
        llvm::StringRef,
        llvm::StringRef,
        clang::Module const*,
        bool,
        clang::SrcMgr::CharacteristicKind) override {

        ensureRoot();
        markLine(HashLoc);

        if (File && SM->isInMainFile(HashLoc)) {
            auto incl = Out->add_includes();
            incl->set_absolutepath(File->getName().str());
            incl->set_relativepath(FileName.str());
        }

        PendingInclude pending;
        pending.IncludingFilePath = getRealPathForLoc(*SM, HashLoc);
        pending.RelativePath      = FileName.str();
        if (File) { pending.AbsolutePath = File->getName().str(); }

        PendingIncludes.push_back(std::move(pending));
    }

    void FileChanged(
        clang::SourceLocation                Loc,
        clang::PPCallbacks::FileChangeReason Reason,
        clang::SrcMgr::CharacteristicKind,
        clang::FileID PrevFID) override {

        if (!Root) { ensureRoot(); }

        switch (Reason) {
            case clang::PPCallbacks::EnterFile: enterFile(Loc); break;

            case clang::PPCallbacks::ExitFile:
                if (!ActiveStack.empty() && ActiveStack.back().File == PrevFID) {
                    markLine(Loc);
                    exitFile();
                } else if (ActiveStack.size() > 1) {
                    exitFile();
                }
                break;

            case clang::PPCallbacks::RenameFile:
            case clang::PPCallbacks::SystemHeaderPragma: break;
        }
    }

    void If(clang::SourceLocation Loc, clang::SourceRange, ConditionValueKind) override {
        markLine(Loc);
    }

    void Elif(
        clang::SourceLocation Loc,
        clang::SourceRange,
        ConditionValueKind,
        clang::SourceLocation) override {
        markLine(Loc);
    }

    void Ifdef(
        clang::SourceLocation Loc,
        clang::Token const&,
        clang::MacroDefinition const&) override {
        markLine(Loc);
    }

    void Ifndef(
        clang::SourceLocation Loc,
        clang::Token const&,
        clang::MacroDefinition const&) override {
        markLine(Loc);
    }

    void Else(clang::SourceLocation Loc, clang::SourceLocation) override {
        markLine(Loc);
    }

    void Endif(clang::SourceLocation Loc, clang::SourceLocation) override {
        markLine(Loc);
    }

    void MacroDefined(clang::Token const& Tok, clang::MacroDirective const*) override {
        markLine(Tok.getLocation());
    }

    void MacroUndefined(
        clang::Token const& Tok,
        clang::MacroDefinition const&,
        clang::MacroDirective const*) override {
        markLine(Tok.getLocation());
    }

    void MacroExpands(
        clang::Token const&,
        clang::MacroDefinition const&,
        clang::SourceRange Range,
        clang::MacroArgs const*) override {
        markLine(Range.getBegin());
    }

    void PragmaDirective(clang::SourceLocation Loc, clang::PragmaIntroducerKind)
        override {
        markLine(Loc);
    }


    bool Finalized = false;

    void finalizeTop() {
        VisitFrame& top = ActiveStack.back();

        unsigned selfLines = static_cast<unsigned>(top.ProcessedLines.size());
        top.Node->set_expandedlinecountwithoutnested(selfLines);

        unsigned withnested = selfLines;
        for (int i = 0; i < top.Node->nested_size(); ++i) {
            withnested += top.Node->nested(i).expandedlinecountwithnested();
        }

        top.Node->set_expandedlinecountwithnested(withnested);
    }

    void exitFile() {
        if (ActiveStack.empty()) { return; }

        finalizeTop();
        ActiveStack.pop_back();
    }


    void finalizeAll() {
        if (Finalized) { return; }
        while (!ActiveStack.empty()) {
            finalizeTop();
            ActiveStack.pop_back();
        }
        Finalized = true;
    }

    void EndOfMainFile() override {
        if (!Root) { ensureRoot(); }
        finalizeAll();
    }

    ~BranchingIncludeCollectorCallback() override { finalizeAll(); }
};
