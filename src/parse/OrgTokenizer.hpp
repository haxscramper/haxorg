#pragma once

#include <string>
#include <fstream>

#include <hstd/stdlib/Array.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/ColText.hpp>

#include <lexbase/PosStr.hpp>
#include <parse/OrgTypes.hpp>

#include <lexbase/TraceBase.hpp>

struct ImplementError : public std::runtime_error {
    explicit inline ImplementError(const QString& message = "")
        : std::runtime_error(message.toStdString()) {}
};

OrgCommandKind classifyCommand(QString const& command);

// Store common types of the lexer state
template <typename Flag>
struct LexerState {
    Vec<Flag> flagStack = Vec<Flag>();
    Vec<int>  indent    = Vec<int>(); /// Indentation steps encountered by
                                      /// the lexer state
    /// Check if state has any indentation levels stored
    bool hasIndent() { return 0 < indent.size(); }

    Flag toFlag(Flag flag) {
        auto old         = flagStack.back();
        flagStack.back() = flag;
    }
    void lift(Flag flag) { flagStack.push_back(flag); }
    void drop(Flag flag) { flagStack.pop_back_v(); }

    Flag topFlag() const { return flagStack.at(1_B); }

    bool hasFlag(Flag flag) const { return flagStack.find(flag) != -1; }

    enum LexerIndentKind
    {
        likIncIndent,  /// Indentation increased on current position
        likDecIndent,  /// Decreased on current position
        likSameIndent, /// No indentation change
        likEmptyLine,  /// Multiple whitespaces followed by newline -
                       /// special case for indented blocks.
        likNoIndent,   /// Not at position where indentation can be
                       /// determine (e.g. is inside of a identifier or
                       /// at the start of the line)
    };


    /// Get total indentation level from the state
    int getIndent() const {
        int result = 0;
        for (const auto& level : indent) {
            result += level;
        }
        return result;
    }

    void addIndent(int ind) { indent.push_back(ind); }

    int popIndent() { return indent.pop_back_v(); }

    /// Skip all indentation levels in the lexer - consume leading
    /// whitespaces and calculate list of the indentation level
    /// changes.
    ///
    /// NOTE: indentation calculations are independent from the actual
    /// column values and are only based on the actual spaces used in
    /// the input.
    Vec<LexerIndentKind> skipIndent(PosStr& str) {
        Vec<LexerIndentKind> result;
        if (str.at(charsets::Newline)) {
            str.next();
        }

        int skip = 0;
        while (str.at(charsets::HorizontalSpace, skip)) {
            ++skip;
        }

        str.next(skip);
        if (str.at(charsets::Newline)) {
            result.push_back(likEmptyLine);
        } else {
            const int now = getIndent();
            if (skip == now) {
                result.push_back(likSameIndent);
            } else if (now < skip) {
                result.push_back(likIncIndent);
                // add single indentation level;
                addIndent(skip - now);
            } else if (skip < now) { // indentation level decreased
                                     // from the current one - pop all
                // indentation levels until it will be the same.
                while (skip < getIndent()) {
                    popIndent();
                    result.push_back(likDecIndent);
                }
            }
        }

        return result;
    }
};


struct OrgTokenizer : public OperationsTracer {
    using Base = Tokenizer<OrgTokenKind>;

  public:
    static SPtr<OrgTokenizer> initImpl(OrgTokenGroup* out, bool doTrace);

    struct Errors {
        struct Base : std::runtime_error {
            // TODO add extent information about the error
            QStringView  view;
            int          pos = 0;
            Opt<LineCol> loc;
            QString      getLocMsg() const;

            Base(CR<PosStr> str)
                : std::runtime_error(""), view(str.view), pos(str.pos) {}
        };

        struct None : Base {
            None() : Base(PosStr("", 1)) {}
        };

        struct UnexpectedChar : Base {
            PosStr::CheckableSkip wanted;
            const char*           what() const noexcept override;
            UnexpectedChar(CR<PosStr> str, PosStr::CheckableSkip wanted)
                : Base(str), wanted(wanted) {}
        };

        struct MissingElement : Base {
            QString     missing;
            QString     where;
            const char* what() const noexcept override;

            MissingElement(
                CR<PosStr>  str,
                CR<QString> missing,
                CR<QString> where);
        };

        struct UnexpectedConstruct : Base {
            const char* what() const noexcept override;
            QString     desc;
            UnexpectedConstruct(CR<PosStr> str, CR<QString> desc)
                : Base(str), desc(desc) {}
        };

        struct UnknownConstruct : Base {
            const char* what() const noexcept override;
            UnknownConstruct(CR<PosStr> str) : Base(str) {}
        };
    };

    using Error = Variant<
        Errors::UnexpectedChar,
        Errors::UnexpectedConstruct,
        Errors::UnknownConstruct,
        Errors::MissingElement,
        Errors::None>;


    struct TokenizerError : std::runtime_error {
        Error err;
        TokenizerError() : std::runtime_error(""), err(Errors::None()) {}
        explicit TokenizerError(CR<Error> err)
            : std::runtime_error(""), err(err) {}
        QStringView  getView() const;
        int          getPos() const;
        void         setLoc(CR<LineCol> loc);
        Opt<LineCol> getLoc() const;
        const char*  what() const noexcept override;
    };


    Vec<TokenizerError> errors;


  public:
    enum class ReportKind
    {
        Enter,
        Leave,
        Push,
        SetBuffer,
        ClearBuffer,
        PushResolved,
        Print,
        Error
    };

    struct Report {
        bool           addBuffered = false;
        ReportKind     kind;
        Str            name;
        OrgToken       tok;
        OrgTokenId     id = OrgTokenId::Nil();
        QFileInfo      location;
        int            line;
        Opt<Str>       subname;
        PosStr const*  str = nullptr;
        TokenizerError error;
    };


  public:
    Vec<OrgTokenId> groupStack;
    void            startGroup(PosStr& str);
    void            endGroup(PosStr& str);

  public:
    using LocationResolverCb = Func<LineCol(CR<PosStr>)>;
    using ReportHookCb       = Func<void(CR<Report>)>;
    using TraceUpdateHookCb  = Func<void(CR<Report>, bool&, bool)>;

    virtual void setReportHook(ReportHookCb)             = 0;
    virtual void setTraceUpdateHook(TraceUpdateHookCb)   = 0;
    virtual void setLocationResolver(LocationResolverCb) = 0;


    virtual Vec<OrgToken> lexDelimited(
        PosStr&                          str,
        const Pair<QChar, OrgTokenKind>& start,
        const Pair<QChar, OrgTokenKind>& finish,
        const OrgTokenKind&              middle)
        = 0;


    /// Check if the string is positioned at the start of a logbook
    /// `CLOCK:` entry.
    virtual bool atLogClock(CR<PosStr> str) = 0;

    /// Check if string is positioned at the start of toplevel language
    /// construct.
    virtual bool atConstructStart(CR<PosStr> str) = 0;
    virtual bool atSubtreeStart(CR<PosStr> str)   = 0;

    using LexerStateSimple = LexerState<char>;

    virtual void skipIndents(LexerStateSimple& state, PosStr& str) = 0;


    /// Attempt to parse list start dash
    virtual bool atListStart(CR<PosStr> str) = 0;
    virtual bool atListAhead(CR<PosStr> str) = 0;

    /// Lex head starting from current position onwards. `indent` is the
    /// indentation of the original list prefix -- dash, number or letter.
    virtual bool lexListItem(PosStr& str, const int& indent, LexerStateSimple& state) = 0;

    virtual bool lexListBullet(PosStr& str, int indent, LexerStateSimple& state) = 0;
    virtual bool lexListDescription(PosStr& str, int indent, LexerStateSimple& state) = 0;
    virtual void lexListBody(PosStr& str, int indent, LexerStateSimple& state) = 0;
    virtual bool lexListItems(PosStr& str, LexerStateSimple& state) = 0;
    virtual bool lexTableState(PosStr& str, LexerState<OrgBlockLexerState>& state) = 0;
    virtual bool lexCommandContent(PosStr& str, const OrgCommandKind& kind) = 0;
    virtual bool lexCommandArguments(PosStr& str, const OrgCommandKind& kind) = 0;

    virtual bool lexCommandBlockDelimited(PosStr& str, PosStr id, int column) = 0;


    virtual bool isFirstOnLine(CR<PosStr> str) = 0;

    virtual void         spaceSkip(PosStr& str, bool require = false) = 0;
    virtual void         newlineSkip(PosStr& str)                     = 0;
    virtual Opt<LineCol> getLoc(CR<PosStr> str)                       = 0;

#define EACH_SIMPLE_TOKENIZER_METHOD(__IMPL)                              \
    __IMPL(Comment);                                                      \
    __IMPL(List);                                                         \
    __IMPL(Paragraph);                                                    \
    __IMPL(Table);                                                        \
    __IMPL(Structure);                                                    \
    __IMPL(Global);                                                       \
    __IMPL(Angle);                                                        \
    __IMPL(TimeRange);                                                    \
    __IMPL(TimeStamp);                                                    \
                                                                          \
    __IMPL(Link);                                                         \
    __IMPL(Footnote);                                                     \
    __IMPL(LinkTarget);                                                   \
    __IMPL(Bracket);                                                      \
    __IMPL(TextChars);                                                    \
    __IMPL(ParenArguments);                                               \
    __IMPL(Text);                                                         \
    __IMPL(Properties);                                                   \
    __IMPL(Description);                                                  \
    __IMPL(Logbook);                                                      \
    __IMPL(Drawer);                                                       \
    __IMPL(SubtreeTodo);                                                  \
    __IMPL(SubtreeUrgency);                                               \
    __IMPL(SubtreeTitle);                                                 \
    __IMPL(SubtreeTimes);                                                 \
    __IMPL(Subtree);                                                      \
    __IMPL(SourceBlockContent);                                           \
                                                                          \
    __IMPL(CommandKeyValue);                                              \
    __IMPL(CommandInclude);                                               \
    __IMPL(CommandOptions);                                               \
    __IMPL(CommandCall);                                                  \
    __IMPL(CommandBlock);                                                 \
    __IMPL(CommandProperty);                                              \
                                                                          \
    __IMPL(HashTag);                                                      \
    __IMPL(TextDollar);                                                   \
    __IMPL(TextSlash);                                                    \
    __IMPL(SlashMath);                                                    \
    __IMPL(SlashEntity);                                                  \
    __IMPL(TextVerbatim);                                                 \
    __IMPL(TextCurly);                                                    \
    __IMPL(TextMarkup);                                                   \
    __IMPL(TextAtSign);                                                   \
    __IMPL(TextSrc);                                                      \
    __IMPL(TextCall);                                                     \
    __IMPL(TextWord);

#define _def(Kind) virtual bool lex##Kind(PosStr& str) = 0;
    EACH_SIMPLE_TOKENIZER_METHOD(_def);
#undef _def
};
