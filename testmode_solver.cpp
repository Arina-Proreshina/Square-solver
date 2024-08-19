#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "testmode_solver.h"
#include "solver.h"
#include "input_output_solver.h"

static const double EPSILON = 1e-6;

/**
 * @brief Функция для парсинга строки с коэффициентами.
 *
 * @param[in] line Строка с коэффициентами.
 * @param[out] coeffts Указатель на структуру, в которую будут записаны коэффициенты.
 */
static void parse_coefficients(const char *line, SquareEquationCoefficient *coeffts) {
    sscanf(line, "%lf %lf %lf", &coeffts->a, &coeffts->b, &coeffts->c);
}

/**
 * @brief Сравнивает фактический результат с ожидаемым.
 *
 * @param[in] expected Ожидаемый результат.
 * @param[in] actual Фактический результат.
 * @return Возвращает SUCCESS, если результаты совпадают, иначе ERROR_CODE.
 */
static int compare_results(const char *expected, const SquareEquationResult *actual) {
    char expected_result[50];
    double x1, x2;

    if (sscanf(expected, "%s %lf %lf", expected_result, &x1, &x2) < 1) {
        return ERROR_CODE;
    }

    if (strcmp(expected_result, "InfRoots") == 0 && actual->result_type == InfRoots) {
        return SUCCESS;
    } else if (strcmp(expected_result, "NoRoots") == 0 && actual->result_type == NoRoots) {
        return SUCCESS;
    } else if (strcmp(expected_result, "OneRoot") == 0 && actual->result_type == OneRoot &&
               fabs(actual->x1 - x1) < EPSILON) {
        return SUCCESS;
    } else if (strcmp(expected_result, "TwoRoots") == 0 && actual->result_type == TwoRoots &&
               fabs(actual->x1 - x1) < EPSILON && fabs(actual->x2 - x2) < EPSILON) {
        return SUCCESS;
    }

    return ERROR_CODE;
}

/**
 * @brief Запускает тесты из файла.
 *
 * @param[in] test_file Путь к файлу с тестами.
 */
void run_tests(const char *test_file) {
    FILE *file = fopen(test_file, "r");
    if (file == NULL) {
        perror("Не удалось открыть файл с тестами");
        return;
    }

    char line[100];
    SquareEquationCoefficient coeffts;
    SquareEquationResult result;

    while (fgets(line, sizeof(line), file)) {
        parse_coefficients(line, &coeffts);

        if (fgets(line, sizeof(line), file)) {
            SquareEquationResult expected_result;
            if (compare_results(line, &result)) {
                printf("Тест пройден успешно!\n");
            } else {
                printf("Тест не пройден. Ожидалось: %s, Получено: ", line);
                print_solution(result);
            }
        }
    }

    fclose(file);
}

