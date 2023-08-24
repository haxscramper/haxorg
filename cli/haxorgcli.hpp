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
#include "config.hpp"

struct HaxorgCli {
    // TODO support processing multiple files, token groups
    OrgTokenGroup              tokens;
    SPtr<OrgTokenizer>         tokenizer;
    OrgNodeGroup               nodes;
    SPtr<OrgParser>            parser;
    QString                    source;
    sem::OrgConverter          converter;
    LineColInfo                info;
    Lexer<OrgTokenKind>        lex;
    sem::SemIdT<sem::Document> node = sem::SemIdT<sem::Document>::Nil();
    SPtr<PosStr>               str;
    StrCache                   sources;
    Func<LineCol(CR<PosStr>)>  locationResolver;
    sem::ContextStore          store;

    UnorderedMap<OrgTokenId, OrgTokenizer::Report> pushedOn;

    struct NodeOperations {
        UnorderedMap<OrgId, OrgParser::Report> started, ended, pushed;
    };

    NodeOperations ops;

    void initLocationResolvers();
    void initTracers();


    bool runTokenizer(bool catchExceptions);
    void writeYamlLex(QTextStream& stream);

    HaxorgCli(cli::Main const& params);
    cli::Main config;
    void      exec();
};

#endif // HAXORGCLI_HPP
