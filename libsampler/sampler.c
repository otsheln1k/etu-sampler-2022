#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include <sys/time.h>

#include "sampler.h"

static struct vertex *
get_vertex(struct graph *g,
           const char *file, int line)
{
    for (size_t i = 0; i < g->svs; i++) {
        struct vertex *v = &g->vs[i];
        if (v->file == file     /* both string literals, so just == */
            && v->line == line) {
            return v;
        }
    }

    if (g->svs == g->cvs) {
        g->cvs = (g->cvs + 1) * 2;
        g->vs = realloc(g->vs, sizeof(*g->vs) * g->cvs);
    }
    struct vertex *v = &g->vs[g->svs++];
    *v = (struct vertex) {
        .file = file,
        .line = line,
        .edges = NULL,
        .sedges = 0,
        .cedges = 0,
    };
    return v;
}

static struct edge *
get_edge(struct graph *g, size_t src,
         const char *file, int line)
{
    struct vertex *v = &g->vs[src];

    for (size_t i = 0; i < v->sedges; i++) {
        struct edge *e = &v->edges[i];
        struct vertex *d = &g->vs[e->dest];
        if (d->file == file     /* see get_vertex */
            && d->line == line) {
            return e;
        }
    }

    size_t dest = get_vertex(g, file, line) - g->vs;

    v = &g->vs[src];            /* repeat in case of realloc */

    if (v->sedges == v->cedges) {
        v->cedges = (v->cedges + 1) * 2;
        v->edges = realloc(v->edges, sizeof(*v->edges) * v->cedges);
    }
    struct edge *e = &v->edges[v->sedges++];
    *e = (struct edge) {
        .dest = dest,
        .total_usec = 0,
        .count = 0,
    };
    return e;
}

struct graph sample_graph = {
    .vs = NULL,
    .svs = 0,
    .cvs = 0,
};

static size_t sample_last;

static struct timeval sample_tv_last;

void
do_sample(const char *file, int line, const char *func)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) < 0) {
        perror("do_sample: gettimeofday");
        exit(1);
    }

    if (sample_graph.vs == NULL) {
        struct vertex *v = get_vertex(&sample_graph, file, line);
        sample_last = v - sample_graph.vs;

    } else {
        struct edge *e = get_edge(&sample_graph,
                                  sample_last, file, line);
        uint64_t dusec = (tv.tv_sec - sample_tv_last.tv_sec) * 1000000
            + (tv.tv_usec - sample_tv_last.tv_usec);
        e->total_usec += dusec;
        e->count++;

        sample_last = e->dest;
    }

    sample_graph.vs[sample_last].func = func;

    if (gettimeofday(&sample_tv_last, NULL) < 0) {
        perror("do_sample: gettimeofday");
        exit(1);
    }
}

static char
json_ctl_char(char c)
{
    switch (c) {
    case '\b': return 'b';
    case '\n': return 'n';
    case '\r': return 'r';
    case '\t': return 't';
    case '\f': return 'f';
    default: return -1;
    }
}

static void
print_json_char(FILE *f, char c)
{
    if (c == '"' || c == '\\') {
        fputc('\\', f);
        fputc(c, f);
        return;
    }

    if (c >= 0x20) {            /* should be ok for UTF-8 */
        fputc(c, f);
        return;
    }

    char cc = json_ctl_char(c);
    if (cc >= 0) {
        fputc('\\', f);
        fputc(cc, f);
        return;
    }
    fprintf(f, "\\u%04x", c);
}

static void
print_json_string(FILE *f, const char *s)
{
    fputc('"', f);
    for (const char *i = s; *i; i++) {
        print_json_char(f, *i);
    }
    fputc('"', f);
}

void
print_graph_json(FILE *f, const struct graph *graph)
{
    fprintf(f, "[\n");
    for (size_t i = 0; i < graph->svs; i++) {
        struct vertex *v = &graph->vs[i];

        fprintf(f, " {\n  \"file\": ");
        print_json_string(f, v->file);
        fprintf(f, ",\n  \"line\": %d,\n", v->line);
        fprintf(f, "  \"func\": ");
        print_json_string(f, v->func);
        fprintf(f, ",\n  \"edges\": [\n");
        for (size_t j = 0; j < v->sedges; j++) {
            struct edge *e = &v->edges[j];

            fprintf(f, "   {\n    \"dest\": %zu,\n", e->dest);
            fprintf(f, "    \"total-usec\": %" PRIu64 ",\n", e->total_usec);
            fprintf(f, "    \"count\": %" PRIu64 "\n   }%s\n",
                   e->count, (j == v->sedges - 1) ? "" : ",");
        }
        fprintf(f, "  ]\n }%s\n", (i == graph->svs - 1) ? "" : ",");
    }
    fprintf(f, "]\n");

    /*
     * [
     *  {
     *   ‘file’: (string),
     *   ‘line’: (integer),
     *   ‘func’: (string),
     *   ‘edges’: [
     *    {
     *     ‘dest’: (integer index),
     *     ‘total-usec’: (large integer),
     *     ‘count’: (large integer)
     *    }, ...
     *   ]
     *  }, ...
     * ]
     */
}

__attribute__ ((destructor)) void
print_graph()
{
    print_graph_json(stdout, &sample_graph);
}
