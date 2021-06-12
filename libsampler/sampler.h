#ifndef SAMPLER_H
#define SAMPLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SAMPLE do_sample(__FILE__, __LINE__, __func__)

void do_sample(const char *file, int line, const char *func);


struct vertex;

struct edge {
    size_t dest;
    uint64_t total_usec;
    uint64_t count;
};

struct vertex {
    const char *file;
    int line;

    const char *func;

    struct edge *edges;
    size_t sedges;              /* size */
    size_t cedges;              /* capacity */
};

struct graph {
    struct vertex *vs;
    size_t svs;                 /* size */
    size_t cvs;                 /* capacity */
};

extern struct graph sample_graph;

void
print_graph_json(FILE *f, const struct graph *graph);


#ifdef __cplusplus
}
#endif

#endif
