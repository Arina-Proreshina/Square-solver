#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "solver.h"
#include "input_output_solver.h"
#include "error_code.h"
#include "comparison_with_zero.h"

enum TestResult {
    TEST_PASSED,
    TEST_FAILED
};

struct Test {
    enum RootNumber expected_roots_num;
    double a;
    double b;
    double c;
    double expected_x1;
    double expected_x2;
};

void print_test_result(int test_num, const struct Test* test, const SquareEquationResult* result, enum TestResult test_result) {
    if (test_result == TEST_PASSED) {
        printf("Тест № %d пройден\n", test_num);
    } else {
        printf("Тест № %d НЕ пройден\n\tКоэффициенты: a = %lg, b = %lg, c = %lg\n",
            test_num, test->a, test->b, test->c);
        printf("\tОжидаемое количество корней: %d\n", test->expected_roots_num);

        if (test->expected_roots_num == OneRoot) {
            printf("\tОжидаемый корень: x = %lg\n", test->expected_x1);
        } else if (test->expected_roots_num == TwoRoots) {
            printf("\tОжидаемые корни: x1 = %lg, x2 = %lg\n", test->expected_x1, test->expected_x2);
        }

        printf("\tРассчитанное количество корней: %d\n", result->result_type);
        if (result->result_type == OneRoot) {
            printf("\tРассчитанный корень: x = %lg\n", result->x1);
        } else if (result->result_type == TwoRoots) {
            printf("\tРассчитанные корни: x1 = %lg, x2 = %lg\n", result->x1, result->x2);
        }
    }
}

enum TestResult check_roots(const struct Test* test, const SquareEquationResult* result) {
    if (result->result_type == test->expected_roots_num) {
        switch (result->result_type) {
            case NoRoots:
            case InfRoots:
                return TEST_PASSED;

            case OneRoot:
                if (is_close(result->x1, test->expected_x1)) {
                    return TEST_PASSED;
                }
                break;

            case TwoRoots:
                if ((is_close(result->x1, test->expected_x1) &&
                     is_close(result->x2, test->expected_x2))    ||
                    (is_close(result->x1, test->expected_x2) &&
                     is_close(result->x2, test->expected_x1))) {
                    return TEST_PASSED;
                }
                break;
        }
    }

    return TEST_FAILED;
}

enum TestResult run_test(struct Test test, int test_num) {
    SquareEquationCoefficient coeffs = { test.a, test.b, test.c };
    SquareEquationResult result = solve_square_equation(coeffs);
    enum TestResult test_result = check_roots(&test, &result);
    print_test_result(test_num, &test, &result, test_result);
    return test_result;
}

void run_tests() {
    struct Test test_data[] = {
        {NoRoots,   0,    0,    5,    0,    0},
        {NoRoots,  10,    1,    7,    0,    0},
        {NoRoots,   2,    6,   14,    0,    0},
        {OneRoot,   0,    5,   20,   -4,    0},
        {OneRoot,   9,  -54,   81,    4,    0},  // Incorrect
        {OneRoot,   0,  -14,    7,  0.5,    0},
        {OneRoot,   5,   10,    5,   -1,    0},
        {OneRoot,   7,    0,    0,    0,    0},
        {TwoRoots,  8,    0,   -2,  0.5, -0.5},
        {TwoRoots,  5,  -20, -105,    7,   -3},
        {TwoRoots, 12,    6,    0,    0,  0.5},  // Incorrect
        {InfRoots,  0,    0,    0,    0,    0}
    };

    const size_t NUM_TESTS = sizeof(test_data) / sizeof(test_data[0]);
    size_t failed_tests_counter = 0;

    for (size_t i = 0; i < NUM_TESTS; ++i) {
        if (run_test(test_data[i], i) == TEST_FAILED) {
            ++failed_tests_counter;
        }
    }

    printf("\nТестирование завершено. Количество неудачных тестов: %d\n", failed_tests_counter);
}
