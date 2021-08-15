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


#define SAMPLE sampler_checkpoint(__FILE__, __LINE__, __func__)
#define CHECKPOINT SAMPLE

void sampler_checkpoint(const char *file, int line, const char *func);


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
