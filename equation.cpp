#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "equation.h"

bool is_zero(double value) {
    return fabs(value) < EPSILON;
}

SquareEquationResult solve_linear_equation(SquareEquationCoefficient coeffts) {
    SquareEquationResult result;

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

SquareEquationResult solve_square_equation(SquareEquationCoefficient coeffts) {
    SquareEquationResult result;
    result.result_type = NoRoots;

    double dscr = coeffts.b * coeffts.b - 4 * coeffts.a * coeffts.c;

    if (is_zero(coeffts.a)) {
        result = solve_linear_equation(coeffts);
    } else if (dscr > 0) {
        result.x1 = (-coeffts.b + sqrt(dscr)) / (2 * coeffts.a);
        result.x2 = (-coeffts.b - sqrt(dscr)) / (2 * coeffts.a);
        result.result_type = TwoRoots;
    } else if (dscr == 0) {
        result.x1 = -coeffts.b / (2 * coeffts.a);
        result.result_type = OneRoot;
    }
    return result;
}

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
