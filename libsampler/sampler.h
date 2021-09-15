#ifndef SAMPLER_H
#define SAMPLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/* New sampler:
 * 1. Measure end time, calculate time delta
 * 2. Write prev pt, this pt, time delta
 * 3. Measure start time, record this pt as prev pt
 */


struct sampler_times {
    struct timespec tse1, tse2, tss1, tss2;
};

extern struct sampler_times sampler_times;

#include <time.h>

#ifndef CLOCK
#define CLOCK CLOCK_THREAD_CPUTIME_ID
#endif


#ifndef SAMPLER_MACRO
#define SAMPLE sampler_checkpoint(__FILE__, __LINE__, __func__)
#else

#define SAMPLER_CHECKPOINT()                                    \
    do {                                                        \
        clock_gettime(CLOCK, &sampler_times.tse1);              \
        clock_gettime(CLOCK, &sampler_times.tse2);              \
        sampler_do_checkpoint(__FILE__, __LINE__, __func__);    \
        clock_gettime(CLOCK, &sampler_times.tss1);              \
        clock_gettime(CLOCK, &sampler_times.tss2);              \
    } while (0)

#define SAMPLE SAMPLER_CHECKPOINT()
#endif


#define CHECKPOINT SAMPLE

void sampler_checkpoint(
    const char *file, int line, const char *func);

void sampler_do_checkpoint(
    const char *file, int line, const char *func);

/* Cmdline interface:
 * - ‘-o file’
 * - ‘-O fd’
 * - ‘-- rest...’
 */


void sampler_init(int *pargc, char **argv);

#ifdef __cplusplus
}
#endif

#endif
