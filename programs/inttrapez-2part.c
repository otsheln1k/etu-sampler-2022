#include <stdio.h>
#include <math.h>
#include "sampler.h"

const double tol = 1.0E-6;
double sum, upper = 9.0, lower = 1.0;

void trapez(double lower, double upper, double tol) {
    SAMPLE;
    int pieces = 1;
    double delta_x, end_sum, mid_sum = 0.0, sum1;
    delta_x = (upper - lower) / pieces;
    end_sum = 1.0 / lower + 1.0 / upper;
    sum = end_sum * delta_x / 2.0;
    SAMPLE;
    do {
        SAMPLE;
        pieces *= 2;
        sum1 = sum;
        delta_x = (upper - lower) / pieces;
        SAMPLE;
        for (int i = 1; i <= pieces / 2; i++) {
            SAMPLE;
            mid_sum += 1.0 / (lower + delta_x * (2.0 * i - 1.0));
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

    trapez(lower, upper, tol);
    return 0;
}
