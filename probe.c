/******************************************************************************
 * Copyright (c) 2024 Ivan Solodilov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/

#include "probe.h"

/****************************************************************************
 * Version
 ****************************************************************************/

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0

/****************************************************************************
 * Private Data
 ****************************************************************************/

static probe_test_case_t test_cases[PROBE_MAX_TEST_CASES];
static int test_cases_num = 0;
static int test_cases_passed = 0;
static int test_cases_error = 0;

/******************************************************************************
 * Private Functions
 *****************************************************************************/

void register_test(probe_test_case_handler_t test, const char *name) {
    if (test_cases_num < PROBE_MAX_TEST_CASES) {
        test_cases[test_cases_num].handler = test;
        test_cases[test_cases_num].name = name;
        ++test_cases_num;
    } else {
        printf("Too many tests registered\n");
    }
}

void set_local_error() {
    test_cases_error = 1;
}

void reset_local_error() {
    test_cases_error = 0;
}

int check_local_error() {
    return test_cases_error;
}

/******************************************************************************
 * Test Runner
 *****************************************************************************/

int main(void) {
    printf("Probe %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    printf("Running tests...\n");
    for (int i = 0; i < test_cases_num; ++i) {
        reset_local_error();
        printf("  %s: ", test_cases[i].name);
        test_cases[i].handler();
        if (!check_local_error()) {
            printf("Passed\n");
            ++test_cases_passed;
        }
    }
    printf("\nPassed: %d/%d\n", test_cases_passed, test_cases_num);
    return 0;
}