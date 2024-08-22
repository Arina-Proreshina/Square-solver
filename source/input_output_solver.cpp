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

    int ch = 0;

    if (scanf("%lf", value) == 1) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
            if (ch != ' ' && ch != '\t' && ch != EOF) {
                printf("������ �����! ������� �������� ��������.\n");
                return false;
            }else if (ch == EOF) {
                printf("������ �����! ��������� EOF.\n");
                return false;
            }
        }
        return true;
    } else if ((ch = getchar()) != '\n' && ch != EOF && ch != ' ') {
        printf("������ �����! ������� �������� ��������.\n");
        return false;
    }
    return true;
}

int get_coefficients(SquareEquationCoefficient* coeffts) {
    const char* messages[] = {
        "������� ����������� a: ",
        "������� ����������� b: ",
        "������� ����������� c: "
    };

    double* coeffs[NUM_COEFFS] = { &coeffts->a, &coeffts->b, &coeffts->c };

    for (size_t i = 0; i < NUM_COEFFS; i++) {
        while (get_number_input(coeffs[i], messages[i]) == false) {
            get_number_input(coeffs[i], messages[i]);
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
