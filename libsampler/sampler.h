#ifndef SAMPLER_H
#define SAMPLER_H

#ifdef __cplusplus
extern "C" {
#endif

#define SAMPLE do_sample(__FILE__, __LINE__)

void do_sample(const char *file, int line);

#ifdef __cplusplus
}
#endif

#endif
