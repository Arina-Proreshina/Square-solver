/**
 * @file input_output_solver.c
 * @brief Ввод и вывод данных для решения квадратных уравнений.
 *
 * @details
 * Этот файл содержит функции для получения коэффициентов квадратного уравнения от пользователя,
 * а также для вывода решения уравнения. Обрабатываются ошибки ввода, и предоставляются соответствующие сообщения.
 *
 * @author Арина Прорешина
 * @date 20.08.2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <cctype>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "input_output_solver.h"
#include "error_code.h"

/**
 * @brief Константа, определяющая количество коэффициентов уравнения.
 */
const int NUM_COEFFS = 3;

/**
 * @brief Очищает буфер ввода.
 *
 * @details
 * Эта функция очищает буфер ввода, чтобы предотвратить неправильную интерпретацию остаточных символов,
 * которые могут возникнуть после ошибки ввода.
 */
static void clear_input_buffer() {
    int ch = getchar();
    while (ch != '\n' && ch != EOF)
        ch = getchar();
}

/**
 * @brief Получает числовой ввод от пользователя.
 *
 * @details
 * Эта функция запрашивает у пользователя ввод числа и проверяет его на корректность. Если ввод некорректен,
 * пользователю предлагается ввести значение повторно.
 *
 * @param[out] value Указатель на переменную, в которую будет сохранено введенное значение.
 * @param[in] message Сообщение, которое будет отображено пользователю перед вводом.
 * @return true, если ввод корректен, иначе false.
 */
static bool get_number_input(double* value, const char* message) {
    assert(value != NULL);
    assert(message != NULL);

    if (isatty(fileno(stdin))) {
        printf("%s", message);
    }

    int ch = 0;

    if (scanf("%lf", value) == 1) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
            if (!isspace(ch)) {
                printf("Ошибка ввода! Введите числовое значение.\n");
                clear_input_buffer();
                return false;
            }
        }
        return true;
    } else if (feof(stdin)) {
        printf("Ошибка ввода! Обнаружен EOF.\n");
        return false;
    } else {
        printf("Ошибка ввода! Введите числовое значение.\n");
        clear_input_buffer();
        return false;
    }
}

/**
 * @brief Получает коэффициенты квадратного уравнения от пользователя.
 *
 * @details
 * Эта функция запрашивает у пользователя ввод коэффициентов a, b и c для квадратного уравнения
 * и сохраняет их в структуре SquareEquationCoefficient. Если ввод завершен досрочно (EOF),
 * возвращается код ошибки.
 *
 * @param[out] coeffts Указатель на структуру SquareEquationCoefficient, в которую будут сохранены коэффициенты.
 * @return Код завершения: SUCCESS (0) при успешном вводе, ERROR_CODE (-1) при ошибке.
 */
int get_coefficients(SquareEquationCoefficient* coeffts) {
    const char* messages[] = {
        "Введите коэффициент a: ",
        "Введите коэффициент b: ",
        "Введите коэффициент c: "
    };

    double* coeffs[NUM_COEFFS] = { &coeffts->a, &coeffts->b, &coeffts->c };

    for (size_t i = 0; i < NUM_COEFFS; i++) {
        while (!get_number_input(coeffs[i], messages[i])) {
            if (feof(stdin)) {
                return ERROR_CODE;
            }
        }
    }
    return SUCCESS;
}

/**
 * @brief Выводит решение квадратного уравнения.
 *
 * @details
 * Эта функция выводит решение квадратного уравнения на экран, исходя из типа результата,
 * который определяется значением переменной result.result_type.
 *
 * @param[in] result Структура SquareEquationResult, содержащая результаты решения уравнения.
 */
void print_solution(SquareEquationResult result) {
    switch (result.result_type) {
        case InfRoots:
            printf("Уравнение имеет бесконечно много корней.\n");
            break;
        case TwoRoots:
            printf("Корни уравнения: x1 = %.2f, x2 = %.2f\n", result.x1, result.x2);
            break;
        case OneRoot:
            printf("Один корень уравнения: x = %.2f\n", result.x1);
            break;
        case NoRoots:
            printf("Уравнение не имеет вещественных корней.\n");
            break;
        default:
            printf("Ошибка: Неизвестный тип результата.\n");
            break;
    }
}
