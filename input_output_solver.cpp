#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "input_output_solver.h"
#include "error_code.h"

const int NUM_COEFFS = 3;

static bool get_number_input(double* value, const char* message) {
    assert(value != NULL);
    assert(message != NULL);

    printf("%s", message);

    while (true) {
        int result = scanf("%lf", value);

        if (result == 1) {
            int ch = 0;
            while ((ch = getchar()) != '\n' && (ch = getchar()) != EOF) {
                if (ch != ' ' && ch != '\t' && ch != EOF) {
                    printf("Ошибка ввода! Введите числовое значение.\n");
                    return false;
                }else if (ch == EOF) {
                    printf("Ошибка ввода! Обнаружен EOF.\n");
                    return false;
                }
            }
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

    double* coeffs[NUM_COEFFS] = { &coeffts->a, &coeffts->b, &coeffts->c };

    for (size_t i = 0; i < NUM_COEFFS; i++) {
        if (!get_number_input(coeffs[i], messages[i])) {
            return ERROR_CODE;
        }
    }
    return SUCCESS;
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
