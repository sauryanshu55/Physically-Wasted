#include "test.h"

#include <nbody.h>
#include <global.h>
#include <math.h>

static const float tol = 0.05;

void setUp(void) {}
void tearDown(void) {}

void 
test_case_1(void) {
        // Test case 1: Zero vector
        float dx[3];
        dx[0] = 0.0f;
        dx[1] = 0.0f;
        dx[2] = 0.0f;
        TEST_ASSERT_FLOAT_WITHIN(tol, 0.0f, nbody_getr2f(dx));

}

void 
test_case_2(void) {
        // Test case 2: Unit vector along x-axis
        float dx[3];
        dx[0] = 1.0f;
        dx[1] = 0.0f;
        dx[2] = 0.0f;
        TEST_ASSERT_FLOAT_WITHIN(tol, 1.0f, nbody_getr2f(dx));
}

void 
test_case_3(void) {
        // Test case 3: Unit vector along y-axis
        float dx[3];
        dx[0] = 0.0f;
        dx[1] = 1.0f;
        dx[2] = 0.0f;
        TEST_ASSERT_FLOAT_WITHIN(tol, 1.0f, nbody_getr2f(dx));
}

void 
test_case_4(void) {
        // Test case 4: Vector with mixed components
        float dx[3];
        dx[0] = 1.0f;
        dx[1] = 1.0f;
        dx[2] = 1.0f;
        float expected_r2 = 1.0f + 1.0f + 1.0f; // 3.0
        TEST_ASSERT_FLOAT_WITHIN(tol, expected_r2, nbody_getr2f(dx));
}

void 
test_case_5(void) {
        // Test case 5: Larger magnitude vector
        float dx[3];
        dx[0] = 3.0f;
        dx[1] = 4.0f;
        dx[2] = 0.0f;
        float expected_r2 = 3.0f * 3.0f + 4.0f * 4.0f; // 9 + 16 = 25
        TEST_ASSERT_FLOAT_WITHIN(tol, expected_r2, nbody_getr2f(dx));
}

int 
main(void) {

        UNITY_BEGIN();
        RUN_TEST(test_case_1);
        RUN_TEST(test_case_2);
        RUN_TEST(test_case_3);
        RUN_TEST(test_case_4);
        RUN_TEST(test_case_5);
        return UNITY_END();

}

