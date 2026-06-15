#pragma once

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/ASTConsumers.h>

#include <hstd/stdlib/Set.hpp>

#include "reflection_config.hpp"
#include "reflection_defs.pb.h"
#include <filesystem>


struct BranchingIncludeCollectorCallback : public clang::PPCallbacks {
    clang::SourceManager* SM;
    clang::Preprocessor*  PP;
    TU*                   Out;

    IncludeVisit* Root = nullptr;

    static std::string normalizeAbsolutePath(std::string const& rawPath) {
        if (rawPath.empty()) { return {}; }

        std::filesystem::path p(rawPath);
        if (p.is_relative()) { p = std::filesystem::absolute(p); }

        return std::filesystem::canonical(p).string();
    }

    static std::string getMainFileAbsolutePath(clang::CompilerInstance& CI) {
        clang::SourceManager&       SM     = CI.getSourceManager();
        clang::FileID               mainId = SM.getMainFileID();
        clang::OptionalFileEntryRef file   = SM.getFileEntryRefForID(mainId);
        if (file) {
            return normalizeAbsolutePath(file->getName().str());
        } else {
            return normalizeAbsolutePath(
                SM.getFileEntryRefForID(mainId)->getName().str());
        }
    }

    static std::string getRealPathForLoc(
        clang::SourceManager const& SM,
        clang::SourceLocation       Loc) {
        clang::SourceLocation spelling = SM.getSpellingLoc(Loc);
        if (spelling.isInvalid()) { return {}; }

        clang::FileID               fid  = SM.getFileID(spelling);
        clang::OptionalFileEntryRef file = SM.getFileEntryRefForID(fid);
        if (file) { return normalizeAbsolutePath(file->getName().str()); }

        if (auto oldFile = SM.getFileEntryRefForID(fid)) {
            return normalizeAbsolutePath(oldFile->getName().str());
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
        unsigned    PhysicalLine = 0;
    };

    struct VisitFrame {
        IncludeVisit*                Node;
        clang::FileID                File;
        std::string                  AbsolutePath;
        std::unordered_set<unsigned> SkippedLines;
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
        Root->set_includelocationline(0);

        clang::FileID mainId = SM->getMainFileID();

        ActiveStack.push_back(
            VisitFrame{
                .Node         = Root,
                .File         = mainId,
                .AbsolutePath = Root->absolutepath(),
            });

        Root->set_filelinecount(countPhysicalLines(*SM, mainId));
    }

    std::string getMainFileAbsolutePathFromSM() {
        clang::FileID               mainId = SM->getMainFileID();
        clang::OptionalFileEntryRef file   = SM->getFileEntryRefForID(mainId);
        if (file) {
            return normalizeAbsolutePath(file->getName().str());
        } else if (auto oldFile = SM->getFileEntryRefForID(mainId)) {
            return normalizeAbsolutePath(oldFile->getName().str());
        } else {
            return {};
        }
    }


    std::optional<PendingInclude> popPendingForParent(
        std::string const& parentPath,
        unsigned           includeLine,
        std::string const& enteredPath) {

        for (auto it = PendingIncludes.begin(); it != PendingIncludes.end(); ++it) {
            if (it->IncludingFilePath != parentPath) { continue; }
            if (includeLine == 0 || it->PhysicalLine != includeLine) { continue; }
            if (!enteredPath.empty() && !it->AbsolutePath.empty()
                && it->AbsolutePath != enteredPath) {
                continue;
            }

            PendingInclude result = *it;
            PendingIncludes.erase(it);
            return result;
        }

        return std::nullopt;
    }

    void enterFile(clang::FileID enteredFile) {
        if (!Root) { ensureRoot(); }

        auto fe = SM->getFileEntryRefForID(enteredFile);
        if (!fe) { return; }

        if (!ActiveStack.empty() && ActiveStack.back().File == enteredFile) { return; }
        if (ActiveStack.empty()) { return; }

        std::string enteredPath = normalizeAbsolutePath(fe->getName().str());

        clang::SourceLocation includeLoc = SM->getIncludeLoc(enteredFile);
        std::string           parentPath;
        unsigned              includeLine = 0;
        if (includeLoc.isValid()) {
            parentPath  = getRealPathForLoc(*SM, includeLoc);
            includeLine = SM->getSpellingLineNumber(SM->getSpellingLoc(includeLoc));
        } else {
            parentPath = ActiveStack.back().AbsolutePath;
        }

        auto pending = popPendingForParent(parentPath, includeLine, enteredPath);

        IncludeVisit* nested = ActiveStack.back().Node->add_nested();
        nested->set_absolutepath(enteredPath);
        nested->set_filelinecount(countPhysicalLines(*SM, enteredFile));

        if (pending) {
            nested->set_relativepath(pending->RelativePath);
            nested->set_includelocationline(pending->PhysicalLine);
        } else {
            nested->set_relativepath("");
            nested->set_includelocationline(0);
        }

        ActiveStack.push_back(
            VisitFrame{
                .Node         = nested,
                .File         = enteredFile,
                .AbsolutePath = nested->absolutepath(),
            });
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

        if (File && SM->isInMainFile(HashLoc)) {
            auto incl = Out->add_includes();
            incl->set_absolutepath(normalizeAbsolutePath(File->getName().str()));
            incl->set_relativepath(FileName.str());
        }

        PendingInclude pending;
        pending.IncludingFilePath = getRealPathForLoc(*SM, HashLoc);
        pending.RelativePath      = FileName.str();
        if (File) { pending.AbsolutePath = normalizeAbsolutePath(File->getName().str()); }

        clang::SourceLocation spelling = SM->getSpellingLoc(HashLoc);
        if (spelling.isValid()) {
            pending.PhysicalLine = SM->getSpellingLineNumber(spelling);
        }

        PendingIncludes.push_back(std::move(pending));
    }

    void FileSkipped(
        clang::FileEntryRef const& SkippedFile,
        clang::Token const&        FilenameTok,
        clang::SrcMgr::CharacteristicKind) override {

        std::string parentPath = getRealPathForLoc(*SM, FilenameTok.getLocation());
        unsigned    line       = SM->getSpellingLineNumber(
            SM->getSpellingLoc(FilenameTok.getLocation()));
        std::string skippedAbs = normalizeAbsolutePath(SkippedFile.getName().str());

        (void)popPendingForParent(parentPath, line, skippedAbs);
    }

    void FileChanged(
        clang::SourceLocation                Loc,
        clang::PPCallbacks::FileChangeReason Reason,
        clang::SrcMgr::CharacteristicKind,
        clang::FileID PrevFID) override {

        if (!Root) { ensureRoot(); }

        switch (Reason) {
            case clang::PPCallbacks::EnterFile: {
                clang::SourceLocation enterLoc = SM->getExpansionLoc(Loc);
                if (enterLoc.isValid()) {
                    clang::FileID entered = SM->getFileID(enterLoc);
                    enterFile(entered);
                }
                break;
            }

            case clang::PPCallbacks::ExitFile:
                if (!ActiveStack.empty() && ActiveStack.back().File == PrevFID) {
                    exitFile();
                } else if (ActiveStack.size() > 1) {
                    exitFile();
                }
                break;

            case clang::PPCallbacks::RenameFile:
            case clang::PPCallbacks::SystemHeaderPragma: break;
        }
    }

    void SourceRangeSkipped(clang::SourceRange Range, clang::SourceLocation) override {
        if (ActiveStack.empty()) { return; }

        clang::SourceLocation begin = SM->getSpellingLoc(Range.getBegin());
        clang::SourceLocation end   = SM->getSpellingLoc(Range.getEnd());
        if (begin.isInvalid() || end.isInvalid()) { return; }

        clang::FileID fidBegin = SM->getFileID(begin);
        clang::FileID fidEnd   = SM->getFileID(end);
        if (fidBegin != fidEnd) { return; }

        VisitFrame& top = ActiveStack.back();
        if (fidBegin != top.File) { return; }

        unsigned lineBegin = SM->getSpellingLineNumber(begin);
        unsigned lineEnd   = SM->getSpellingLineNumber(end);
        if (lineBegin == 0 || lineEnd == 0) { return; }
        if (lineEnd < lineBegin) { std::swap(lineBegin, lineEnd); }

        for (unsigned line = lineBegin; line <= lineEnd; ++line) {
            top.SkippedLines.insert(line);
        }
    }


    bool Finalized = false;

    void finalizeTop() {
        VisitFrame& top = ActiveStack.back();

        unsigned total   = top.Node->filelinecount();
        unsigned skipped = static_cast<unsigned>(top.SkippedLines.size());
        unsigned direct  = (total > skipped) ? (total - skipped) : 0;

        top.Node->set_usedlinecount(direct);
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
