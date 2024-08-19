#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "input_output_solver.h"

static const int NUM_COEFFS = 3;

static bool get_number_input(double* value, const char* message) {
    assert(value != NULL);
    assert(message != NULL);

    printf("%s", message);

    while (true) {
        int result = scanf("%lf", value);

        if (result == 1) {
            while (getchar() != '\n');
            return true;
        } else {
            printf("������ �����! ������� �������� ��������.\n");
            return false;
        }
        printf("%s", message);
    }
}

int get_coefficients(SquareEquationCoefficient* coeffts) {
    const char* messages[] = {
        "������� ����������� a: ",
        "������� ����������� b: ",
        "������� ����������� c: "
    };

    double* coeffs[] = { &coeffts->a, &coeffts->b, &coeffts->c };

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
            printf("��������� ����� ���������� ����� ������.\n");
            break;
        case TwoRoots:
            printf("����� ���������: x1 = %.2f, x2 = %.2f\n", result.x1, result.x2);
            break;
        case OneRoot:
            printf("���� ������ ���������: x = %.2f\n", result.x1);
            break;
        case NoRoots:
            printf("��������� �� ����� ������������ ������.\n");
            break;
        default:
            printf("������: ����������� ��� ����������.\n");
            break;
    }
}
