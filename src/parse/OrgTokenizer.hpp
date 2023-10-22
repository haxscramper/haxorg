#pragma once

#include <string>
#include <fstream>

#include <hstd/stdlib/Array.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/ColText.hpp>

#include <parse/OrgTypes.hpp>

#include <lexbase/TraceBase.hpp>

struct ImplementError : public std::runtime_error {
    explicit inline ImplementError(const std::string& message = "")
        : std::runtime_error(message) {}
};

/// \brief Base implementation of the tokenizer.
///
/// There are two intended implementations of the tokenizer -- with and
/// without tracing. They differ only in the presence of the tracing calls
/// and implemented as explicitly specialized templates with static bool
/// argument.
struct OrgTokenizer : public OperationsTracer {
    // TODO at the moment the assumption is that adding conditional checks
    // all over the place in each lexer function would hinder the
    // performance quite a bit. Since indent/dedent relies on the RAII
    // triggers they would be executed no matter what -- but now without
    // any purpose. It is not exactly checked whether the performance drop
    // is large enough to justify all the hacks with explicit
    // initialization, but for the time being I don't want to get into this
    // and try and check what is really going on.
    using Base = Tokenizer<OrgTokenKind, BaseToken>;

  public:
    /// \brief Create tokenizer implementation object
    static SPtr<OrgTokenizer> initImpl(OrgTokenGroup* out, bool doTrace);

    /// \brief Definition of the error types for the lexer
    struct Errors {
        /// \brief Base error, not thrown anywhere
        struct Base : std::runtime_error {
            // TODO add extent information about the error
            int          pos = 0;
            Opt<LineCol> loc;
            std::string  getLocMsg() const;
            Base() : std::runtime_error("") {}
        };

        /// \brief Empty placeholder
        struct None : Base {
            None() {}
        };


        struct MissingElement : Base {
            std::string missing;
            std::string where;
            const char* what() const noexcept override;
            MissingElement() {}
        };

        struct UnexpectedConstruct : Base {
            const char* what() const noexcept override;
            std::string desc;
            UnexpectedConstruct() {}
        };

        struct UnknownConstruct : Base {
            const char* what() const noexcept override;
            UnknownConstruct() {}
        };
    };

    using Error = Variant<
        Errors::UnexpectedConstruct,
        Errors::UnknownConstruct,
        Errors::MissingElement,
        Errors::None>;


    struct TokenizerError : std::runtime_error {
        Error err;
        TokenizerError() : std::runtime_error(""), err(Errors::None()) {}
        explicit TokenizerError(CR<Error> err)
            : std::runtime_error(""), err(err) {}
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
        fs::path       location;
        int            line;
        Opt<Str>       subname;
        TokenizerError error;
    };


  public:
    Vec<OrgTokenId> groupStack;
    void            startGroup(BaseLexer& str);
    void            endGroup(BaseLexer& str);

  public:
    using ReportHookCb      = Func<void(CR<Report>)>;
    using TraceUpdateHookCb = Func<void(CR<Report>, bool&, bool)>;

    virtual void         setReportHook(ReportHookCb)           = 0;
    virtual void         setTraceUpdateHook(TraceUpdateHookCb) = 0;
    virtual void         reserve(int size)                     = 0;
    virtual Opt<LineCol> getLoc(CR<BaseLexer> str)             = 0;


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
    __IMPL(DynamicTimeStamp);                                             \
    __IMPL(StaticTimeStamp);                                              \
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

#define _def(Kind) virtual bool lex##Kind(BaseLexer& str) = 0;
    EACH_SIMPLE_TOKENIZER_METHOD(_def);
#undef _def
};
