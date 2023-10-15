#include <sem/SemOrg.hpp>
#include <sem/SemConvert.hpp>

#include <benchmark/benchmark.h>

static void impl() {
    qDebug() << "Running bench";
    OrgTokenGroup       tokens;
    SPtr<OrgTokenizer>  tokenizer = OrgTokenizer::initImpl(&tokens, false);
    OrgNodeGroup        nodes{nullptr};
    QString             base;
    Lexer<OrgTokenKind> lex{&tokens};
    SPtr<OrgParser>     parser = OrgParser::initImpl(&nodes, false);
    UPtr<OrgSpec>       spec;
    nodes.tokens = &tokens;

    base = readFile(QFileInfo("/home/haxscramper/tmp/doc.org"));

    Func<LineCol(CR<PosStr>)> locationResolver =
        [&](CR<PosStr> str) -> LineCol {
        return {0, 0, 0};
    };

    tokenizer->setLocationResolver(locationResolver);
    parser->setLocationResolver(locationResolver);

    tokens.base = base.data();
    PosStr str{base};
    tokenizer->lexGlobal(str);
    qDebug() << "Completed run to" << tokens.size() << "tokens";
}

static void BenchLexFile(benchmark::State& state) { impl(); }


QTextStream qcout;

int main() { impl(); }
// BENCHMARK(BenchLexFile);
// BENCHMARK_MAIN();
