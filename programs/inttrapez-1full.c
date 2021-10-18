#include <stdio.h>
#include <math.h>
#include "sampler.h"

const double tol = 1.0E-6;
double sum, upper, lower;

double fx(double x) {
    return 1.0 / x;
}

void trapez(double lower, double upper, double tol) {
    int pieces = 1;
    double x, delta_x, end_sum, mid_sum = 0.0, sum1;
    delta_x = (upper - lower) / pieces;
    end_sum = fx(lower) + fx(upper);
    sum = end_sum * delta_x / 2.0;
    do {
        pieces = pieces * 2;
        sum1 = sum;
        delta_x = (upper - lower) / pieces;
        for (int i = 1; i <= pieces / 2; i++) {
            x = lower + delta_x * (2.0 * i - 1.0);
            mid_sum = mid_sum + fx(x);
        }
        sum = (end_sum + 2.0 * mid_sum) * delta_x * 0.5;
    } while (fabs(sum - sum1) > fabs(tol * sum));
}

int main(int argc, char **argv) {
    sampler_init(&argc, argv);

    lower = 1.0;
    upper = 9.0;
    SAMPLE;
    trapez(lower, upper, tol);
    SAMPLE;
    return 0;
}
