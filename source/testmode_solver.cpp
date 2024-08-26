/**
 * @file test_solver.c
 * @brief Тестирование решения квадратного уравнения.
 *
 * @details
 * Этот файл содержит функции для тестирования алгоритма решения квадратного уравнения.
 * Включены функции для запуска тестов, проверки результатов и вывода информации о пройденных тестах.
 *
 * @author Арина Прорешина
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
 * @brief Перечисление для обозначения результата теста.
 */
enum TestResult {
    TEST_PASSED,  /**< Тест пройден успешно. */
    TEST_FAILED   /**< Тест не пройден. */
};

/**
 * @struct Test
 * @brief Структура для хранения данных теста.
 *
 * Эта структура содержит коэффициенты квадратного уравнения, ожидаемое количество корней и ожидаемые значения корней.
 */
struct Test {
    enum RootNumber expected_roots_num;  /**< Ожидаемое количество корней. */
    double a;                            /**< Коэффициент a квадратного уравнения. */
    double b;                            /**< Коэффициент b квадратного уравнения. */
    double c;                            /**< Коэффициент c квадратного уравнения. */
    double expected_x1;                  /**< Ожидаемое значение первого корня. */
    double expected_x2;                  /**< Ожидаемое значение второго корня. */
};

/**
 * @brief Выводит результат теста на экран.
 *
 * @details
 * Эта функция выводит информацию о результатах теста, включая номера тестов, коэффициенты, ожидаемые и рассчитанные корни.
 *
 * @param[in] test_num Номер теста.
 * @param[in] test Указатель на структуру с данными теста.
 * @param[in] result Указатель на структуру с результатом решения уравнения.
 * @param[in] test_result Результат теста (пройден или нет).
 */
void print_test_result(int test_num, const struct Test* test, const SquareEquationResult* result, enum TestResult test_result) {
    switch (test_result) {
        case TEST_PASSED:
            printf("Тест № %d пройден\n", test_num);
            break;

        case TEST_FAILED:
            printf("Тест № %d НЕ пройден\n\tКоэффициенты: a = %lg, b = %lg, c = %lg\n",
                test_num, test->a, test->b, test->c);
            printf("\tОжидаемое количество корней: %d\n", test->expected_roots_num);

            switch (test->expected_roots_num) {
                case OneRoot:
                    printf("\tОжидаемый корень: x = %lg\n", test->expected_x1);
                    break;

                case TwoRoots:
                    printf("\tОжидаемые корни: x1 = %lg, x2 = %lg\n", test->expected_x1, test->expected_x2);
                    break;

                default:
                    printf("\tОжидается количество корней: %d\n", test->expected_roots_num);
                    break;
            }
            printf("\tРассчитанное количество корней: %d\n", result->result_type);

            switch (result->result_type) {
                case OneRoot:
                    printf("\tРассчитанный корень: x = %lg\n", result->x1);
                    break;

                case TwoRoots:
                    printf("\tРассчитанные корни: x1 = %lg, x2 = %lg\n", result->x1, result->x2);
                    break;

                default:
                    printf("\tРассчитанное количество корней: %d\n", result->result_type);
                    break;
            }
            break;
    }
}

/**
 * @brief Проверяет правильность решения квадратного уравнения.
 *
 * @details
 * Эта функция сравнивает рассчитанные корни с ожидаемыми значениями, чтобы определить, пройден ли тест.
 *
 * @param[in] test Указатель на структуру с данными теста.
 * @param[in] result Указатель на структуру с результатом решения уравнения.
 * @return enum TestResult Результат теста (TEST_PASSED или TEST_FAILED).
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
 * @brief Выполняет один тест решения квадратного уравнения.
 *
 * @details
 * Эта функция решает квадратное уравнение с заданными коэффициентами и проверяет результат на соответствие ожидаемому.
 *
 * @param[in] test Структура с данными теста.
 * @param[in] test_num Номер теста.
 * @return enum TestResult Результат теста (TEST_PASSED или TEST_FAILED).
 */
enum TestResult run_test(struct Test test, int test_num) {
    SquareEquationCoefficient coeffs = { test.a, test.b, test.c };
    SquareEquationResult result = solve_square_equation(coeffs);

    enum TestResult test_result = check_roots(&test, &result);

    print_test_result(test_num, &test, &result, test_result);
    return test_result;
}

/**
 * @brief Запускает все тесты для решения квадратного уравнения.
 *
 * @details
 * Эта функция последовательно запускает все тесты, определенные в массиве test_data, и выводит результаты.
 * По завершении работы выводит количество неудачных тестов.
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

    printf("\nТестирование завершено. Количество неудачных тестов: %d\n", failed_tests_counter);
}
