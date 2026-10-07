#include <stdio.h>
#include <stdlib.h>
#include "unity/unity.h"
#ifdef __ARM_EABI__
    void initialise_monitor_handles();
#endif


void setUp(void) {}
void tearDown(void) {}

static void test_3x3_still_eq_9(void) {
    int val = 3*3;
    TEST_ASSERT_EQUAL_INT(9, val);
}

int main(void) {
#ifdef __ARM_EABI__
    initialise_monitor_handles();
#endif
    printf("Running tests for %s\n", __FILE__);
    UnityBegin(__FILE__);
    RUN_TEST(test_3x3_still_eq_9);
    exit(UnityEnd());
}