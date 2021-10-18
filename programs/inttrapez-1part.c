#include <stdio.h>
#include <math.h>
#include "sampler.h"

const double tol = 1.0E-6;
double sum, upper, lower;

double fx(double x) {
    return 1.0 / x;
}

void trapez(double lower, double upper, double tol) {
    SAMPLE;
    int pieces = 1;
    double x, delta_x, end_sum, mid_sum = 0.0, sum1;
    delta_x = (upper - lower) / pieces;
    end_sum = fx(lower) + fx(upper);
    sum = end_sum * delta_x / 2.0;
    SAMPLE;
    do {
        SAMPLE;
        pieces = pieces * 2;
        sum1 = sum;
        delta_x = (upper - lower) / pieces;
        SAMPLE;
        for (int i = 1; i <= pieces / 2; i++) {
            SAMPLE;
            x = lower + delta_x * (2.0 * i - 1.0);
            mid_sum = mid_sum + fx(x);
            SAMPLE;
        }
        SAMPLE;
        sum = (end_sum + 2.0 * mid_sum) * delta_x * 0.5;
        SAMPLE;
    } while (fabs(sum - sum1) > fabs(tol * sum));
    SAMPLE;
}

int main(int argc, char **argv) {
    sampler_init(&argc, argv);

    lower = 1.0;
    upper = 9.0;
    trapez(lower, upper, tol);

    /* if (tmp_i != TMP_VALS_SIZE) { */
    /*     fprintf(stderr, "not enough vals!\n"); */
    /*     return 43; */
    /* } */
    /* for (size_t i = 0; i < tmp_i; i++) { */
    /*     printf("%ld\n", tmp_vals[i]); */
    /* } */
    /* printf("total = %lu\n", tmp_total); */
    return 0;
}
