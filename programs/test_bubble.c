#include <stdio.h>
#include <stdlib.h>

#include "sampler.h"

void bubble_1(float arr[], size_t n)
{
    float tmp;
    size_t i, j;
    for (i = 0; i<n-1; i++)
        for (j = i+1; j<n; j++)
            if (arr[i] > arr[j]) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
}

void swap(float *a, float *b)
{
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_2(float arr[], size_t n)
{
    int no_change;
    size_t j;
    do {
        no_change = 0;
        for (j = 0; j<n-1; j++)
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
                no_change = 1;
            }
    } while (no_change != 0);
}

int main(int argc, char **argv)
{
    size_t max = 100;
    unsigned int seed = 123654;
    if (argc >= 2) {
        sscanf(argv[1], "%zu", &max);
    }
    if (argc >= 3) {
        sscanf(argv[2], "%u", &seed);
    }

    float arr1[max], arr2[max];
    SAMPLE;
    srand(seed);
    SAMPLE;
    for(size_t i=0; i<max; i++) {
        arr1[i] = rand()/1000.0;
        arr2[i] = arr1[i];
    }
    SAMPLE;
    bubble_1(arr1, max);
    SAMPLE;
    bubble_2(arr2, max);
    SAMPLE;
}
