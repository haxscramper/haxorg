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


struct OrgTokenizer
    : public Tokenizer<OrgTokenKind>
    , public OperationsTracer {
    using Base = Tokenizer<OrgTokenKind>;

  private:
    enum class ReportKind
    {
        Enter,
        Leave,
        Push,
        SetBuffer,
        ClearBuffer,
        PushResolved
    };

    struct Report {
        ReportKind kind;
        Str        name;
        OrgToken   tok;
        OrgTokenId id = OrgTokenId::Nil();
        fs::path   location;
        int        line;
        Opt<Str>   subname;
        PosStr*    str = nullptr;
    };

    int  depth = 0;
    void report(CR<Report> in);


  public:
    OrgTokenizer(OrgTokenGroup* out) : Tokenizer<OrgTokenKind>(out) {}

    /// Push complex token into recursive processing pipeline. Used for
    /// table content (which might contain more blocks of texts, some
    /// paragraph elements, more content etc), regular `Text` token
    /// (contained in a lot of places, first picked out from the
    /// 'surrounding' and then re-lexed again (the best example where this
    /// might be needed is `#+title:` followed by regular paragraph, but
    /// things like link descriptions might contain nested paragraphs as
    /// well))
    void pushResolved(CR<OrgToken> token);

    Vec<OrgToken> lexDelimited(
        PosStr&                          str,
        const Pair<QChar, OrgTokenKind>& start,
        const Pair<QChar, OrgTokenKind>& finish,
        const OrgTokenKind&              middle);


    /*!Check if the string is positioned at the start of a logbook
    `CLOCK:` entry.
    */
    bool atLogClock(CR<PosStr> str);

    /*!Check if string is positioned at the start of toplevel language
    construct.
    */
    bool atConstructStart(CR<PosStr> str);

    // Store common types of the lexer state
    template <typename Flag>
    struct LexerState {
        Vec<Flag> flagStack = Vec<Flag>();
        Vec<int>  indent = Vec<int>(); /// Indentation steps encountered by
                                       /// the lexer state
        /*!Check if state has any indentation levels stored
         */
        bool hasIndent() { return 0 < indent.size(); }

        Flag toFlag(Flag flag) {
            auto old         = flagStack.back();
            flagStack.back() = flag;
        }
        void lift(Flag flag) { flagStack.push_back(flag); }
        void drop(Flag flag) { flagStack.pop_back_v(); }

        Flag topFlag() const { return flagStack.at(1_B); }

        bool hasFlag(Flag flag) const {
            return flagStack.find(flag) != -1;
        }

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


    using LexerStateSimple = LexerState<char>;

    void skipIndents(LexerStateSimple& state, PosStr& str);


    /*!Attempt to parse list start dash */
    bool atListStart(CR<PosStr> str);
    bool lexListStart(PosStr& str);


    bool atListAhead(CR<PosStr> str);


    /*!Lex head starting from current position onwards. `indent` is the
indentation of the original list prefix -- dash, number or letter.
*/
    void lexListItem(
        PosStr&           str,
        const int&        indent,
        LexerStateSimple& state);

    void lexListBullet(PosStr& str, int indent, LexerStateSimple& state);
    void lexListDescription(
        PosStr&           str,
        int               indent,
        LexerStateSimple& state);

    PosStr popListBody(PosStr& str, int indent, LexerStateSimple& state);

    void lexComment(PosStr& str) {
        push(str.tok(OrgTokenKind::Comment, skipToEOL));
    }


    void setBuffer(Vec<OrgToken>* buffer) {
        report(Report{.kind = ReportKind::SetBuffer});
        Base::setBuffer(buffer);
    }

    void clearBuffer() {
        report(Report{.kind = ReportKind::ClearBuffer});
        Base::clearBuffer();
    }

    void       push(CR<std::span<OrgToken>> tok) { Base::push(tok); }
    void       push(CR<Vec<OrgToken>> tok) { Base::push(tok); }
    OrgTokenId push(CR<OrgToken> tok) { return Base::push(tok); }

    void lexListItems(PosStr& str, LexerStateSimple& state);
    void lexList(PosStr& str);
    void lexParagraph(PosStr& str);
    void lexParagraphExpand(PosStr& str);
    void lexLogbookExpand(PosStr& str);
    void lexContentExpand(PosStr& str);
    void lexStmtListExpand(PosStr& str);
    void lexTableState(PosStr& str, LexerState<OrgBlockLexerState>& state);
    void lexTable(PosStr& str);
    void lexStructure(PosStr& str);
    void lexGlobal(PosStr& str);
    void lexAngle(PosStr& str);
    void lexTime(PosStr& str);
    void lexLinkTarget(PosStr& str);
    void lexBracket(PosStr& str);
    void lexTextChars(PosStr& str);
    void lexParenArguments(PosStr& str);
    void lexText(PosStr& str);
    void lexProperties(PosStr& str);
    void lexDescription(PosStr& str);
    void lexLogbook(PosStr& str);
    void lexDrawer(PosStr& str);
    void lexSubtreeTodo(PosStr& str);
    void lexSubtreeUrgency(PosStr& str);
    void lexSubtreeTitle(PosStr& str);
    void lexSubtreeTimes(PosStr& str);
    void lexSubtree(PosStr& str);
    void lexSourceBlockContent(PosStr& str);
    void lexCommandContent(PosStr& str, const OrgCommandKind& kind);
    void lexCommandArguments(PosStr& str, const OrgCommandKind& kind);
    void lexCommandBlock(PosStr& str);
    bool isFirstOnLine(CR<PosStr> str);
};
