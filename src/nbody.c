#include <nbody.h>
#include <global.h>

#include <math.h>
#include <stddef.h>

float 
nbody_getr2f(const float* const dx) {

        const float r = dx[0] * dx[0] + dx[1] * dx[1] + dx[2] * dx[2];

        return r;

}

static void 
nbody_geta(float* const restrict x,
           float* const restrict a,
           const float* const restrict m, 
           const size_t N, const size_t i) {

        float dx[DIM];

        a[0] = 0;
        a[1] = 0;
        a[2] = 0;

        for (size_t j = 0; j < N; j++) {

                if (i == j) {
                        continue;
                }

                dx[0] = x[DIM * j + 0] - x[DIM * i + 0];
                dx[1] = x[DIM * j + 1] - x[DIM * i + 1];
                dx[2] = x[DIM * j + 2] - x[DIM * i + 2];

                const float r2 = nbody_getr2f(dx) + EPSf * EPSf;
                const float c = Gf * m[j] / (r2 * sqrtf(r2));

                a[0] += dx[0] * c;
                a[1] += dx[1] * c;
                a[2] += dx[2] * c;
        
        }

}

#define USE_2ND_ORDER 0
static  void 
nbody_integratef(float* const restrict x,
                 float* const restrict v,
                 float* const restrict a,
                 const float* const restrict m,
                 const size_t N,
                 const size_t i,
                 const float dt) {

#if USE_2ND_ORDER
        (void)a;
        (void)m;
        (void)N;
        v[DIM * i + 0] += 0.5f * a[0] * dt;
        v[DIM * i + 1] += 0.5f * a[1] * dt;
        v[DIM * i + 2] += 0.5f * a[2] * dt;

        x[DIM * i + 0] += v[DIM * i + 0] * dt;
        x[DIM * i + 1] += v[DIM * i + 1] * dt;
        x[DIM * i + 2] += v[DIM * i + 2] * dt;

        v[DIM * i + 0] += 0.5f * a[0] * dt;
        v[DIM * i + 1] += 0.5f * a[1] * dt;
        v[DIM * i + 2] += 0.5f * a[2] * dt;

#else

        const float w0 = -1.7024143839193153;
        const float w1 =  1.3512071919596578;

        const float c1 = w1 / 2;
        const float c2 = (w0 + w1) / 2;
        const float c3 = (w0 + w1) / 2;
        const float c4 = w1 / 2;
        const float d1 = w1;
        const float d2 = w0;
        const float d3 = w1;

        x[DIM * i + 0] += c1 * v[DIM * i + 0] * dt;
        x[DIM * i + 1] += c1 * v[DIM * i + 1] * dt;
        x[DIM * i + 2] += c1 * v[DIM * i + 2] * dt;
        
        nbody_geta(x, a, m, N, i);
        v[DIM * i + 0] += d1 * a[0] * dt;
        v[DIM * i + 1] += d1 * a[1] * dt;
        v[DIM * i + 2] += d1 * a[2] * dt;

        x[DIM * i + 0] += c2 * v[DIM * i + 0] * dt;
        x[DIM * i + 1] += c2 * v[DIM * i + 1] * dt;
        x[DIM * i + 2] += c2 * v[DIM * i + 2] * dt;

        nbody_geta(x, a, m, N, i);
        v[DIM * i + 0] += d2 * a[0] * dt;
        v[DIM * i + 1] += d2 * a[1] * dt;
        v[DIM * i + 2] += d2 * a[2] * dt;

        x[DIM * i + 0] += c3 * v[DIM * i + 0] * dt;
        x[DIM * i + 1] += c3 * v[DIM * i + 1] * dt;
        x[DIM * i + 2] += c3 * v[DIM * i + 2] * dt;

        nbody_geta(x, a, m, N, i);
        v[DIM * i + 0] += d3 * a[0] * dt;
        v[DIM * i + 1] += d3 * a[1] * dt;
        v[DIM * i + 2] += d3 * a[2] * dt;

        x[DIM * i + 0] += c4 * v[DIM * i + 0] * dt;
        x[DIM * i + 1] += c4 * v[DIM * i + 1] * dt;
        x[DIM * i + 2] += c4 * v[DIM * i + 2] * dt;
        
#endif

}

#define USE_OMP 0
#if USE_OMP
#include <omp.h>
#endif

void 
nbody_stepf(float* const restrict x, 
            float* const restrict v,
            const float* const restrict m, 
            const size_t N, const float dt) {
        
#if USE_OMP
        #pragma omp parallel for
#endif
        for (size_t i = 0; i < N; i++) {

                float a[DIM];
                nbody_geta(x, a, m, N, i);
                nbody_integratef(x, v, a, m, N, i, dt);

        }

}
