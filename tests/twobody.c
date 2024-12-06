#include "test.h"

#include <nbody.h>
#include <global.h>
#include <math.h>

static const float tol = 0.05;
static const float dt = 0.1;
static const size_t t_N = 100000;

void setUp(void) {}
void tearDown(void) {}

static float
getv(const float v0, const float v1, const float v2) {
        return v0 * v0 + v1 * v1 + v2 * v2;
}

static void
test_case_1(void) {
        
        const size_t N = 2;              
        float x[3 * N];
        float v[3 * N];
        float M = 1e2;
        float m[N];
        float r = 1.0f;
        float errmax = 0.0f;
        
        const float v_analytic = sqrtf(Gf * M / r);

        m[0] = M;
        m[1] = 0.0f;

        x[0] = 0.0f;
        x[1] = 0.0f;
        x[2] = 0.0f;
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = 0.0f;

        x[3] = r;
        x[4] = 0.0f;
        x[5] = 0.0f;
        v[3] = 0.0f;
        v[4] = v_analytic;
        v[5] = 0.0f;

        for (size_t i = 0; i < t_N; i++) {

                nbody_stepf(x, v, m, N, dt);

                const double v_err = fabs((double)(v_analytic * v_analytic) - 
                                          (double)(getv(v[3], v[4], v[5]))) /
                                          (double)(v_analytic * v_analytic); 

                errmax = errmax < v_err ? v_err : errmax;

                printf("%lu : %f > %f : %f\n", i, tol, v_err, errmax);


        }

        printf("%f < %f\n", tol, errmax);
        TEST_ASSERT_LESS_THAN_FLOAT(tol, errmax);       

}

int
main(void) {

        UNITY_BEGIN();
        RUN_TEST(test_case_1);
        return UNITY_END();

}
