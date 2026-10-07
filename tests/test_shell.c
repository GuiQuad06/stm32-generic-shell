#include <stdio.h>
#include <stdlib.h>

#include "handlers.h"
#include "shell.h"

#include "unity/unity.h"

#ifdef __ARM_EABI__
    void initialise_monitor_handles();
#endif

void setUp(void) {}

void tearDown(void) {}

static void test_bad_command(void) {
    char command[] = "unicorn\n";
    int result = shell_process(command);
    TEST_ASSERT_EQUAL(CMDLINE_BAD_CMD, result);
}

static void test_too_many_args(void) {
    char command[] = "cmd arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9 arg10 arg11\n";
    int result = shell_process(command);
    TEST_ASSERT_EQUAL(CMDLINE_TOO_MANY_ARGS, result);
}

static void test_shell_success(void) {
    char command[] = "help\n";
    int result = shell_process(command);
    TEST_ASSERT_EQUAL(0, result);
}

int main(void) {
#ifdef __ARM_EABI__
    initialise_monitor_handles();
#endif
    printf("Running tests for %s\n", __FILE__);
    UnityBegin(__FILE__);
    RUN_TEST(test_bad_command);
    RUN_TEST(test_too_many_args);
    RUN_TEST(test_shell_success);
    exit(UnityEnd());
}