#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "solver.h"

const double EPSILON = 1e-6;

static bool is_zero(double value) {
    return fabs(value) < EPSILON;
}

static inline double calculate_dscr(double a, double b, double c){
    return b * b - 4 * a * c;
}

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
