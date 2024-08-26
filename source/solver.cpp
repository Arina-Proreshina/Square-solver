/**
 * @file solver.c
 * @brief Файл для решения квадратных и линейных уравнений.
 *
 * @details
 * Этот файл содержит функции для решения как линейных, так и квадратных уравнений.
 * В случае квадратного уравнения, программа вычисляет дискриминант для определения
 * количества корней, а затем находит сами корни. Для линейного уравнения программа
 * проверяет коэффициенты и решает уравнение либо возвращает информацию о бесконечном
 * числе решений или отсутствии решений.
 *
 * Программа предоставляет следующие функции:
 * - @ref calculate_dscr "calculate_dscr" для вычисления дискриминанта квадратного уравнения.
 * - @ref solve_linear_equation "solve_linear_equation" для решения линейного уравнения.
 * - @ref solve_square_equation "solve_square_equation" для решения квадратного уравнения.
 *
 * @author Арина Прорешина
 * @date 20.08.2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "solver.h"
#include "error_code.h"
#include "comparison_with_zero.h"

/**
 * @brief Вычисляет дискриминант квадратного уравнения.
 *
 * @details
 * Функция принимает коэффициенты квадратного уравнения и вычисляет дискриминант,
 * который затем используется для определения количества корней уравнения.
 *
 * @param[in] a Коэффициент при x^2.
 * @param[in] b Коэффициент при x.
 * @param[in] c Свободный член.
 * @return Значение дискриминанта.
 */
static inline double calculate_dscr(double a, double b, double c) {
    return b * b - 4 * a * c;
}

/**
 * @brief Решает линейное уравнение вида bx + c = 0.
 *
 * @details
 * Функция решает линейное уравнение в зависимости от значений коэффициентов b и c.
 * Если b равно нулю, программа проверяет значение c, чтобы определить, является ли
 * уравнение противоречивым (нет решений) или имеет бесконечно много решений.
 *
 * @param[in] coeffts Структура, содержащая коэффициенты линейного уравнения.
 * @return Структура SquareEquationResult, содержащая количество корней и их значения.
 */
static SquareEquationResult solve_linear_equation(SquareEquationCoefficient coeffts) {
    SquareEquationResult result = {0,0};

    if (is_zero(coeffts.b)) {
        if (is_zero(coeffts.c)) {
            result.result_type = InfRoots;
        } else {
            result.result_type = NoRoots;
        }
    } else {
        result.x1 = -coeffts.c / coeffts.b;
        result.result_type = OneRoot;
    }
    return result;
}

/**
 * @brief Решает квадратное уравнение вида ax^2 + bx + c = 0.
 *
 * @details
 * Функция решает квадратное уравнение в зависимости от значений коэффициентов a, b и c.
 * Если a равно нулю, функция решает уравнение как линейное. В противном случае вычисляется
 * дискриминант, и на основе его значения определяется количество корней (два, один или ни одного).
 *
 * @param[in] coeffts Структура, содержащая коэффициенты квадратного уравнения.
 * @return Структура SquareEquationResult, содержащая количество корней и их значения.
 */
SquareEquationResult solve_square_equation(SquareEquationCoefficient coeffts) {
    SquareEquationResult result;
    result.result_type = NoRoots;

    if (is_zero(coeffts.a)) {
        result = solve_linear_equation(coeffts);
    } else {
        double dscr = calculate_dscr(coeffts.a, coeffts.b, coeffts.c);

        if (dscr > 0) {
            double dscr_sqrt = sqrt(dscr);
            result.x1 = (-coeffts.b + dscr_sqrt) / (2 * coeffts.a);
            result.x2 = (-coeffts.b - dscr_sqrt) / (2 * coeffts.a);
            result.result_type = TwoRoots;
        } else if (dscr == 0) {
            result.x1 = -coeffts.b / (2 * coeffts.a);
            result.result_type = OneRoot;
        }
    }
    return result;
}
