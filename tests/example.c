#include "test.h" 

static int 
add(const int a, const int b) {
        return a + b;
}

static int 
subtract(const int a, const int b) {

        return a - b;
        
}

static float 
divide(const int a, const int b) {

        if (b == 0) {
                return -1.0;
        }

        return (float)a / b;
}

void setUp(void) {}
void tearDown(void) {}

static void 
test_add(void) {
        TEST_ASSERT_EQUAL(5, add(2, 3));
        TEST_ASSERT_EQUAL(0, add(-1, 1));
        TEST_ASSERT_EQUAL(-3, add(-1, -2));
}

static void 
test_subtract(void) {
        TEST_ASSERT_EQUAL(-1, subtract(2, 3));
        TEST_ASSERT_EQUAL(-2, subtract(-1, 1));
        TEST_ASSERT_EQUAL(1, subtract(-1, -2));
}

static void 
test_divide(void) {
        TEST_ASSERT_FLOAT_WITHIN(0.01, 2.5, divide(5, 2));
        TEST_ASSERT_EQUAL(-1.0, divide(5, 0));
}

int 
main(void) {
        UNITY_BEGIN();
        RUN_TEST(test_add);
        RUN_TEST(test_subtract);
        RUN_TEST(test_divide);
        return UNITY_END();
}
