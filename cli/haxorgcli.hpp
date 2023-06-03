#ifndef HAXORGCLI_HPP
#define HAXORGCLI_HPP

#include <sem/SemConvert.hpp>
#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <parse/OrgTypes.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <QFileInfo>
#include <sem/ErrorWrite.hpp>

struct HaxorgCli {
    // TODO support processing multiple files, token groups
    OrgTokenGroup             tokens;
    SPtr<OrgTokenizer>        tokenizer;
    OrgNodeGroup              nodes;
    SPtr<OrgParser>           parser;
    QString                   source;
    sem::OrgConverter         converter;
    LineColInfo               info;
    Lexer<OrgTokenKind>       lex;
    sem::Document::Ptr        node;
    SPtr<PosStr>              str;
    StrCache                  sources;
    Func<LineCol(CR<PosStr>)> locationResolver;

    UnorderedMap<OrgTokenId, OrgTokenizer::Report> pushedOn;

    struct NodeOperations {
        UnorderedMap<OrgId, OrgParser::Report> started, ended, pushed;
    };

    NodeOperations ops;

    void initLocationResolvers();
    void initTracers();


    bool runTokenizer(bool catchExceptions);

    void writeYamlLex();
    void writeYamlParse();
    void writeTreeParse();

    void writeJsonParse();


    void writeJson();
    void writeYaml();
    void writeQDocument();
    void writeSimpleSExpr();
    void writeHtml();
    void writeGantt();

    struct Config {
        enum class Target
        {
            Json,      /// SemOrg JSON export
            JsonParse, /// Raw parsed tree
            JsonLex,   /// Token list in JSON format
            YamlParse, /// Parsed tree in linearized YAML format
            YamlLex,   /// Token list in YAML format
            HtmlLex,   /// HTML table for the processed document
            HtmlParse, /// Linearized DOD tree representation in HTML form
            AnnotatedLex,
            CsvLex,
            GanttPlantuml
        };

        BOOST_DESCRIBE_NESTED_ENUM(
            Target,
            Json,
            JsonParse,
            JsonLex,
            YamlParse,
            YamlLex,
            HtmlLex,
            HtmlParse,
            AnnotatedLex,
            CsvLex,
            GanttPlantuml);

        // TODO multiple writing targets and multiple output files
        Target target = Target::Json;

        /// Common tracing configuration for different file processing
        /// steps
        struct TraceConfig {
            /// Execute tracing at this stage
            bool doTrace = false;
            /// Write trace output to the specified file instead of the
            /// stdout
            Opt<QFileInfo> traceTo;
            /// Do tracing only on a fixed range of input code instead of
            /// the whole file
            Slice<int> traceExtent = slice(0, high<int>());
        };

        // TODO trace must be supported on the per-file basis, each file
        // having unique range of elements
        struct Trace {
            TraceConfig lex;   /// Do tracing during lex
            TraceConfig parse; /// Do tracing during parse
            TraceConfig sem;   /// Do tracing during sem
        } trace;

        QFileInfo sourceFile; /// Input org-mode file to parse
        QFileInfo outFile;    /// Output file to write parse result to
    } config;

    HaxorgCli();
    void exec();
};

#endif // HAXORGCLI_HPP
