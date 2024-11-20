#include "nbody.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int 
main(void) {

        const size_t N = 5000;
        const float dt = 0.0001f;
        const float t_max = 0.01f;

        float* x = (float*)malloc(3 * N * sizeof(float));
        float* v = (float*)calloc(3 * N, sizeof(float));
        float* m = (float*)malloc(N * sizeof(float));

        if (!x || !v || !m) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
        }

        for (size_t i = 0; i < 3 * N; ++i) {
                x[i] = (float)rand() / RAND_MAX;
        }
        for (size_t i = 0; i < N; ++i) {
                m[i] = 1.0f;
        }


        struct timespec tbeg, tend;

        clock_gettime(CLOCK_MONOTONIC, &tbeg);

        for (float t = 0; t < t_max; t += dt) {
                nbody_stepf(x, v, m, N, dt);
        }

        clock_gettime(CLOCK_MONOTONIC, &tend);

        double t_tot = (tend.tv_sec - tbeg.tv_sec) +
                       (tend.tv_nsec - tbeg.tv_nsec) / 1e9;

        double t_avg = t_tot / ((int)((t_max + dt - 1e-6f) / dt));

        printf("Total time: %f seconds\n", t_tot);
        printf("Average time per step: %e seconds\n", t_avg);

        free(x);
        free(v);
        free(m);

        return 0;
}
