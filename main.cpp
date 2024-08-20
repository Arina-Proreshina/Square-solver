/**
 * @file main.cpp
 * @brief Программа для решения квадратного уравнения.
 *
 * Эта программа позволяет пользователю ввести коэффициенты квадратного уравнения
 * и вычислить его корни. Она включает в себя функции для получения ввода, решения
 * квадратного уравнения и печати результатов.
 *
 * @details
 * Программа предоставляет следующие функции:
 * - @ref is_zero "is_zero" для проверки, близко ли значение к нулю в пределах EPSILON.
 * - @ref get_number_input "get_number_input" для получения числового ввода от пользователя.
 * - @ref get_coefficients "get_coefficients" для ввода коэффициентов квадратного уравнения.
 * - @ref solve_linear_equation "solve_linear_equation" для вычисления корней линейного уравнения.
 * - @ref solve_square_equation "solve_square_equation" для вычисления корней квадратного уравнения.
 * - @ref print_solution "print_solution" для печати результатов.
 * - @ref main "main" для выполнения основной логики программы.
 *
 * @note Внимание: Функция @ref get_number_input "get_number_input" проверяет ввод чисел и ожидает, что ввод будет числовым значением.
 *
 * @see SquareEquationCoefficient
 * @see SquareEquationResult
 *
 * @author Арина Прорешина
 * @date 20.08.2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "solver.h"
#include "input_output_solver.h"
#include "testmode_solver.h"
#include "error_code.h"

enum ChoiceMode {
    TestMode = 1,
    SolverMode,
};

/**
 * @brief Основная функция программы.
 *
 * @details
 * Функция устанавливает локаль для корректного отображения текста, выводит меню
 * для выбора режима работы программы, и в зависимости от выбора пользователя
 * запускает либо режим тестов, либо режим решения квадратного уравнения.
 *
 * @return Возвращает 0 при успешном выполнении программы, иначе возвращает
 *         код ошибки, определённый как ERROR_CODE.
 */
int main() {
    setlocale(LC_ALL, "Rus");

    int choice = 0;
    puts("Выберите режим работы программы:\n"
         "1. Режим тестов\n"
         "2. Решение квадратного уравнения\n"
         "Введите номер режима: ");
    if (scanf("%d", &choice) != 1) {
        printf("Ошибка ввода.\n");
        return ERROR_CODE;
    }

    switch (choice) {
        case TestMode:
            run_tests();
            break;

        case SolverMode: {
            SquareEquationCoefficient coeffts;

            if (get_coefficients(&coeffts) != SUCCESS) {
                return ERROR_CODE;
            }

            SquareEquationResult result = solve_square_equation(coeffts);
            print_solution(result);
            break;
        }

        default:
            fprintf(stderr, "Ошибка выбора режима. Пожалуйста, выберите 1 или 2.\n");
            return ERROR_CODE;
    }

    return 0;
}
