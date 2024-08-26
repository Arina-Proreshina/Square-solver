/**
 * @file test_solver.c
 * @brief ������������ ������� ����������� ���������.
 *
 * @details
 * ���� ���� �������� ������� ��� ������������ ��������� ������� ����������� ���������.
 * �������� ������� ��� ������� ������, �������� ����������� � ������ ���������� � ���������� ������.
 *
 * @author ����� ���������
 * @date 20.08.2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "solver.h"
#include "input_output_solver.h"
#include "error_code.h"
#include "comparison_with_zero.h"

/**
 * @enum TestResult
 * @brief ������������ ��� ����������� ���������� �����.
 */
enum TestResult {
    TEST_PASSED,  /**< ���� ������� �������. */
    TEST_FAILED   /**< ���� �� �������. */
};

/**
 * @struct Test
 * @brief ��������� ��� �������� ������ �����.
 *
 * ��� ��������� �������� ������������ ����������� ���������, ��������� ���������� ������ � ��������� �������� ������.
 */
struct Test {
    enum RootNumber expected_roots_num;  /**< ��������� ���������� ������. */
    double a;                            /**< ����������� a ����������� ���������. */
    double b;                            /**< ����������� b ����������� ���������. */
    double c;                            /**< ����������� c ����������� ���������. */
    double expected_x1;                  /**< ��������� �������� ������� �����. */
    double expected_x2;                  /**< ��������� �������� ������� �����. */
};

/**
 * @brief ������� ��������� ����� �� �����.
 *
 * @details
 * ��� ������� ������� ���������� � ����������� �����, ������� ������ ������, ������������, ��������� � ������������ �����.
 *
 * @param[in] test_num ����� �����.
 * @param[in] test ��������� �� ��������� � ������� �����.
 * @param[in] result ��������� �� ��������� � ����������� ������� ���������.
 * @param[in] test_result ��������� ����� (������� ��� ���).
 */
void print_test_result(int test_num, const struct Test* test, const SquareEquationResult* result, enum TestResult test_result) {
    switch (test_result) {
        case TEST_PASSED:
            printf("���� � %d �������\n", test_num);
            break;

        case TEST_FAILED:
            printf("���� � %d �� �������\n\t������������: a = %lg, b = %lg, c = %lg\n",
                test_num, test->a, test->b, test->c);
            printf("\t��������� ���������� ������: %d\n", test->expected_roots_num);

            switch (test->expected_roots_num) {
                case OneRoot:
                    printf("\t��������� ������: x = %lg\n", test->expected_x1);
                    break;

                case TwoRoots:
                    printf("\t��������� �����: x1 = %lg, x2 = %lg\n", test->expected_x1, test->expected_x2);
                    break;

                default:
                    printf("\t��������� ���������� ������: %d\n", test->expected_roots_num);
                    break;
            }
            printf("\t������������ ���������� ������: %d\n", result->result_type);

            switch (result->result_type) {
                case OneRoot:
                    printf("\t������������ ������: x = %lg\n", result->x1);
                    break;

                case TwoRoots:
                    printf("\t������������ �����: x1 = %lg, x2 = %lg\n", result->x1, result->x2);
                    break;

                default:
                    printf("\t������������ ���������� ������: %d\n", result->result_type);
                    break;
            }
            break;
    }
}

/**
 * @brief ��������� ������������ ������� ����������� ���������.
 *
 * @details
 * ��� ������� ���������� ������������ ����� � ���������� ����������, ����� ����������, ������� �� ����.
 *
 * @param[in] test ��������� �� ��������� � ������� �����.
 * @param[in] result ��������� �� ��������� � ����������� ������� ���������.
 * @return enum TestResult ��������� ����� (TEST_PASSED ��� TEST_FAILED).
 */
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

/**
 * @brief ��������� ���� ���� ������� ����������� ���������.
 *
 * @details
 * ��� ������� ������ ���������� ��������� � ��������� �������������� � ��������� ��������� �� ������������ ����������.
 *
 * @param[in] test ��������� � ������� �����.
 * @param[in] test_num ����� �����.
 * @return enum TestResult ��������� ����� (TEST_PASSED ��� TEST_FAILED).
 */
enum TestResult run_test(struct Test test, int test_num) {
    SquareEquationCoefficient coeffs = { test.a, test.b, test.c };
    SquareEquationResult result = solve_square_equation(coeffs);

    enum TestResult test_result = check_roots(&test, &result);

    print_test_result(test_num, &test, &result, test_result);
    return test_result;
}

/**
 * @brief ��������� ��� ����� ��� ������� ����������� ���������.
 *
 * @details
 * ��� ������� ��������������� ��������� ��� �����, ������������ � ������� test_data, � ������� ����������.
 * �� ���������� ������ ������� ���������� ��������� ������.
 */
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

    printf("\n������������ ���������. ���������� ��������� ������: %d\n", failed_tests_counter);
}
