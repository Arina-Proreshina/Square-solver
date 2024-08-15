/**
 * @file
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "input.h"
#include "equation.h"

/**
 * @brief Основная функция программы.
 *
 * Функция устанавливает локаль для вывода сообщений, вызывает функцию
 * для получения коэффициентов квадратного уравнения от пользователя, затем
 * вычисляет корни уравнения и выводит результат. При возникновении ошибки
 * во время ввода коэффициентов, функция завершает выполнение с кодом ошибки.
 *
 * @return Возвращает 0 при успешном выполнении программы, иначе возвращает ERROR_CODE.
 */
int main() {
    setlocale(LC_ALL, "Rus");
    SquareEquationCoefficient coeffts;

    if (get_coefficients(&coeffts) != 0) {
        return ERROR_CODE;
    }

    SquareEquationResult result = solve_square_equation(coeffts);
    print_solution(result);

    return 0;
}
