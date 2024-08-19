#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "solver.h"

static const double EPSILON = 1e-6;

static bool is_zero(double value) {
    return fabs(value) < EPSILON;
}

static SquareEquationResult solve_linear_equation(SquareEquationCoefficient coeffts) {
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

    if (is_zero(coeffts.a)) {
        result = solve_linear_equation(coeffts);
    } else {
        double dscr = coeffts.b * coeffts.b - 4 * coeffts.a * coeffts.c;
        double dscr_sqrt = sqrt(dscr);

        if (dscr > 0) {
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
