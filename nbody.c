#include "nbody.h"

#include <math.h>
#include <stddef.h>

#define DIM   3
#define Gf    1.0e-1f
#define EPSf  1.0e-2f
#define BOUNDSf 1.00f

static inline float 
nbody_getr2f(const float* const dx) {

        const float r = dx[0] * dx[0] + dx[1] * dx[1] + dx[2] * dx[2];

        return r;

}

#define USE_EULER 0
static  void 
nbody_integratef(float* const restrict x,
                 float* const restrict v,
                 float* const restrict a,
                 const size_t i,
                 const float dt) {

#if USE_EULER
        v[DIM * i + 0] += a[0] * dt;
        v[DIM * i + 1] += a[1] * dt;
        v[DIM * i + 2] += a[2] * dt;

        x[DIM * i + 0] += v[DIM * i + 0] * dt;
        x[DIM * i + 1] += v[DIM * i + 1] * dt;
        x[DIM * i + 2] += v[DIM * i + 2] * dt;
#else
        v[DIM * i + 0] += 0.5f * a[0] * dt;
        v[DIM * i + 1] += 0.5f * a[1] * dt;
        v[DIM * i + 2] += 0.5f * a[2] * dt;

        x[DIM * i + 0] += v[DIM * i + 0] * dt;
        x[DIM * i + 1] += v[DIM * i + 1] * dt;
        x[DIM * i + 2] += v[DIM * i + 2] * dt;

        v[DIM * i + 0] += 0.5f * a[0] * dt;
        v[DIM * i + 1] += 0.5f * a[1] * dt;
        v[DIM * i + 2] += 0.5f * a[2] * dt;
#endif

}

#include <omp.h>
void 
nbody_stepf(float* const restrict x, 
            float* const restrict v,
            const float* const restrict m, 
            const size_t N, const float dt) {
        
        #pragma omp parallel for
        for (size_t i = 0; i < N; i++) {

                float dx[DIM];
                float a[DIM] = {0};
                
                for (size_t j = 0; j < N; j++) {

                        if (i == j) {
                                continue;
                        }

                        dx[0] = x[DIM * j + 0] - x[DIM * i + 0];
                        dx[1] = x[DIM * j + 1] - x[DIM * i + 1];
                        dx[2] = x[DIM * j + 2] - x[DIM * i + 2];

                        const float r2 = nbody_getr2f(dx) + EPSf * EPSf;
                        const float r3_inv = 1.0f / (sqrtf(r2) * r2);
                        const float c = Gf * m[j] * r3_inv;

                        a[0] += dx[0] * c;
                        a[1] += dx[1] * c;
                        a[2] += dx[2] * c;
                
                }

                nbody_integratef(x, v, a, i, dt);

        }

}
