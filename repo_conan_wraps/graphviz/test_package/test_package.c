#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int failures = 0;

#define CHECK(cond)                                                                      \
    do {                                                                                 \
        if (cond) {                                                                      \
            printf("  ok   %s\n", #cond);                                                \
        } else {                                                                         \
            fprintf(stderr, "  FAIL %s (%s:%d)\n", #cond, __FILE__, __LINE__);           \
            ++failures;                                                                  \
        }                                                                                \
    } while (0)

/* ---- in-memory output channel for agwrite ---- */
typedef struct {
    char*  data;
    size_t len;
    size_t cap;
} strbuf_t;

static int buf_putstr(void* chan, const char* str) {
    strbuf_t* b = chan;
    size_t    n = strlen(str);
    if (b->len + n + 1 > b->cap) {
        size_t cap = b->cap ? b->cap : 256;
        while (b->len + n + 1 > cap) { cap *= 2; }
        char* p = realloc(b->data, cap);
        if (!p) { return EOF; }
        b->data = p;
        b->cap  = cap;
    }
    memcpy(b->data + b->len, str, n + 1);
    b->len += n;
    return (int)n;
}

static int buf_flush(void* chan) {
    (void)chan;
    return 0;
}

static int streq(const char* a, const char* b) { return a && b && strcmp(a, b) == 0; }

int main(void) {
    // validate gvc types are OK
    Agnodeinfo_t* type_declaration_test;

    strbuf_t out = {NULL, 0, 0};

    /* 1. build a graph programmatically */
    printf("[1] programmatic construction\n");
    Agiodisc_t io   = {AgIoDisc.afread, buf_putstr, buf_flush};
    Agdisc_t   disc = {&AgIdDisc, &io};

    Agraph_t* g = agopen("built", Agdirected, &disc);
    CHECK(g != NULL);
    CHECK(agisdirected(g));

    Agnode_t* a = agnode(g, "a", 1);
    Agnode_t* b = agnode(g, "b", 1);
    Agnode_t* c = agnode(g, "c", 1);
    agedge(g, a, b, NULL, 1);
    agedge(g, b, c, NULL, 1);
    agedge(g, a, c, NULL, 1);

    CHECK(agnnodes(g) == 3);
    CHECK(agnedges(g) == 3);
    CHECK(agdegree(g, a, 0, 1) == 2); /* out-degree of a */
    CHECK(agdegree(g, c, 1, 0) == 2); /* in-degree of c */
    CHECK(agnode(g, "a", 0) == a);
    CHECK(agnode(g, "missing", 0) == NULL);

    agattr_text(g, AGNODE, "shape", "ellipse");
    agset_text(b, "shape", "box");
    CHECK(streq(agget(a, "shape"), "ellipse"));
    CHECK(streq(agget(b, "shape"), "box"));

    Agraph_t* sg = agsubg(g, "cluster_0", 1);
    agsubnode(sg, a, 1);
    CHECK(agnsubg(g) == 1);
    CHECK(agnnodes(sg) == 1);

    /* 2. write to memory, then parse back (exercises writer + bison/flex parser) */
    printf("[2] write / re-read round trip\n");
    CHECK(agwrite(g, &out) != EOF);
    CHECK(out.data != NULL && out.len > 0);
    if (out.data) { printf("---- DOT output ----\n%s--------------------\n", out.data); }
    agclose(g);

    Agraph_t* g2 = out.data ? agmemread(out.data) : NULL;
    CHECK(g2 != NULL);
    if (g2) {
        CHECK(agisdirected(g2));
        CHECK(agnnodes(g2) == 3);
        CHECK(agnedges(g2) == 3);
        CHECK(agnsubg(g2) == 1);
        CHECK(streq(agget(agnode(g2, "b", 0), "shape"), "box"));
        agclose(g2);
    }

    /* 3. parse DOT text: strict graph, labels, HTML-like strings */
    printf("[3] parsing DOT text\n");
    const char* dot
        = "strict graph H {\n"
          "  x -- y [label=\"hello\"];\n"
          "  x -- y;\n" /* merged: strict graph */
          "  y -- z;\n"
          "  z [label=<<b>bold</b>>];\n"
          "}\n";
    Agraph_t* h = agmemread(dot);
    CHECK(h != NULL);
    if (h) {
        CHECK(agisstrict(h));
        CHECK(agisundirected(h));
        CHECK(agnnodes(h) == 3);
        CHECK(agnedges(h) == 2);
        Agnode_t* x  = agnode(h, "x", 0);
        Agnode_t* y  = agnode(h, "y", 0);
        Agnode_t* z  = agnode(h, "z", 0);
        Agedge_t* xy = (x && y) ? agedge(h, x, y, NULL, 0) : NULL;
        CHECK(xy != NULL);
        if (xy) { CHECK(streq(agget(xy, "label"), "hello")); }
        if (z) { CHECK(aghtmlstr(agget(z, "label"))); }
        agclose(h);
    }

    /* 4. syntax errors must be reported, not crash */
    printf("[4] error handling\n");
    agseterr(AGMAX); /* silence stderr output */
    Agraph_t* bad = agmemread("digraph { a -> ; }");
    CHECK(bad == NULL);
    CHECK(agerrors() != 0);
    if (bad) { agclose(bad); }
    agreseterrors();
    agseterr(AGWARN);

    free(out.data);

    if (failures) {
        fprintf(stderr, "%d check(s) failed\n", failures);
        return EXIT_FAILURE;
    }
    printf("all cgraph checks passed\n");
    return EXIT_SUCCESS;
}
