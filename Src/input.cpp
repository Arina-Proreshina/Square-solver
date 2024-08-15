#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include ".../Lib/input.h"

bool get_number_input(double* value, const char* message) {
    assert(value != NULL);
    assert(message != NULL);

    printf("%s", message);

    while (true) {
        int result = scanf("%lf", value);

        if (result == 1) {
            while (getchar() != '\n');
            return true;
        } else {
            printf("Ошибка ввода! Введите числовое значение.\n");
            return false;
        }
        printf("%s", message);
    }
}

int get_coefficients(SquareEquationCoefficient* coeffts) {
    const char* messages[] = {
        "Введите коэффициент a: ",
        "Введите коэффициент b: ",
        "Введите коэффициент c: "
    };

    double* coeffs[] = { &coeffts->a, &coeffts->b, &coeffts->c };

    for (size_t i = 0; i < 3; i++) {
        if (!get_number_input(coeffs[i], messages[i])) {
            return ERROR_CODE;
        }
    }
    return 0;
}
