
/******************************************************************************
 * Copyright (2024) Ivan Solodilov
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

#ifndef PROBE_H
#define PROBE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef PROBE_USE_STDIO
#include <stdio.h>
#else
extern int printf(const char *restrict format, ...);
#endif

#ifndef PROBE_MAX_TEST_CASES
#define PROBE_MAX_TEST_CASES 1024
#endif

/******************************************************************************
 * Private Data Types
 *****************************************************************************/
typedef void (*probe_test_case_handler_t)(void);

struct probe_test_case {
    const char *name;
    probe_test_case_handler_t handler;
};

typedef struct probe_test_case probe_test_case_t;

/******************************************************************************
 * Private Functions
 *****************************************************************************/

/**
 * @brief Registers test with the given name
 *
 * @param test pointer to a test case function
 * @param name name of a test case
 */
void register_test(probe_test_case_handler_t test, const char *name);

/**
 * @brief Functions to set/reset/check errors
 */
int check_local_error();
void set_local_error();
void reset_local_error();

/******************************************************************************
 * Public Functions
 *****************************************************************************/

/**
 * @brief Creates a test case
 * @param name name of a test case
 */
#define TEST(name)                                                   \
    void name##_test(void);                                          \
    __attribute__((constructor)) void register_##name##_test(void) { \
        register_test(name##_test, #name);                           \
    }                                                                \
    void name##_test(void)

/**
 * @brief Prints an error
 * @param expression expression to print
 * Prints a message and sets an error
 */
#define LOG_ERROR(expression)             \
    if (!check_local_error()) {           \
        printf("Failed \n");              \
    }                                     \
    printf(                               \
        "    %s, line %d: "               \
        "%s\n",                           \
        __FILE__, __LINE__, #expression); \
    set_local_error()

/**
 * @brief Checks whether an expression is true
 * @param expression boolean expression to check
 * Prints a message and sets an error if
 * expressions is not true
 */
#define CHECK_TRUE(expression)       \
    do {                             \
        if (!(expression)) {         \
            LOG_ERROR((expression)); \
        }                            \
    } while (0)

/**
 * @brief Checks whether an expression is false
 * @param expression boolean expression to check
 * Prints a message and sets an error if
 * expressions is not false
 */
#define CHECK_FALSE(expression)       \
    do {                              \
        if ((expression)) {           \
            LOG_ERROR(!(expression)); \
        }                             \
    } while (0)

/**
 * @brief Compare whether two variables are equal
 * @param var1 variable for comparison
 * @param var2 variable for comparison
 * Prints a message and sets an error if
 * two variable are not equal
 */
#define CHECK_EQ(var1, var2)         \
    do {                             \
        if ((var1) != (var2)) {      \
            LOG_ERROR(var1 == var2); \
        }                            \
    } while (0)

/**
 * @brief Checks whether two variables are not equal
 * @param var1 variable for comparison
 * @param var2 variable for comparison
 * Prints a message and sets an error if
 * two variables are queal
 */
#define CHECK_NOT_EQ(var1, var2)     \
    do {                             \
        if ((var1) == (var2)) {      \
            LOG_ERROR(var1 != var2); \
        }                            \
    } while (0)

/**
 * @brief Checks whether a variable is equal to zero
 * @param var variable for comparison
 * Prints a message and sets an error if
 * a variable is not equal to zero
 */
#define CHECK_ZERO(var)          \
    do {                         \
        if ((var) != 0) {        \
            LOG_ERROR(var == 0); \
        }                        \
    } while (0)

/**
 * @brief Checks whether a variable is equal to zero
 * @param var variable for comparison
 * Prints a message and sets an error if
 * a variable is not equal to zero
 */
#define CHECK_NOT_ZERO(var)      \
    do {                         \
        if ((var) == 0) {        \
            LOG_ERROR(var != 0); \
        }                        \
    } while (0)

/**
 * @brief Checks whether a variable is not equal to NULL
 * @param var variable for comparison
 * Prints a message and sets an error if
 * a variable is not equal to NULL
 */
#define CHECK_NOT_NULL(var)         \
    do {                            \
        if ((var) == NULL) {        \
            LOG_ERROR(var != NULL); \
        }                           \
    } while (0)

/**
 * @brief Checks whether a variable is equal to NULL
 * @param var variable for comparison
 * Prints a message and sets an error if
 * a variable is equal to NULL
 */
#define CHECK_NULL(var)             \
    do {                            \
        if ((var) != NULL) {        \
            LOG_ERROR(var == NULL); \
        }                           \
    } while (0)

/**
 * @brief Checks whether strings are equal
 * @param str1 string for comparison
 * @param str2 string for comparison
 * Prints a message and sets an error if
 * strings are not equal
 */
#define CHECK_STR(str1, str2)                                      \
    do {                                                           \
        int __s1_i__ = 0, __s2_i__ = 0;                            \
        int __error__ = 0;                                         \
        while (str1[__s1_i__] != '\0' && str2[__s2_i__] != '\0') { \
            if (str1[__s1_i__] != str2[__s2_i__]) {                \
                __error__ = 1;                                     \
                LOG_ERROR(str1 == str2);                           \
                break;                                             \
            }                                                      \
            ++__s1_i__;                                            \
            ++__s2_i__;                                            \
        }                                                          \
        if (str1[__s1_i__] != str2[__s2_i__] && !__error__) {      \
            LOG_ERROR(str1 == str2);                               \
        }                                                          \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif  // PROBE_H
