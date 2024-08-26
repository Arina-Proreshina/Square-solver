/**
 * @file input_output_solver.c
 * @brief ���� � ����� ������ ��� ������� ���������� ���������.
 *
 * @details
 * ���� ���� �������� ������� ��� ��������� ������������� ����������� ��������� �� ������������,
 * � ����� ��� ������ ������� ���������. �������������� ������ �����, � ��������������� ��������������� ���������.
 *
 * @author ����� ���������
 * @date 20.08.2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <cctype>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "input_output_solver.h"
#include "error_code.h"

/**
 * @brief ���������, ������������ ���������� ������������� ���������.
 */
const int NUM_COEFFS = 3;

/**
 * @brief ������� ����� �����.
 *
 * @details
 * ��� ������� ������� ����� �����, ����� ������������� ������������ ������������� ���������� ��������,
 * ������� ����� ���������� ����� ������ �����.
 */
static void clear_input_buffer() {
    int ch = getchar();
    while (ch != '\n' && ch != EOF)
        ch = getchar();
}

/**
 * @brief �������� �������� ���� �� ������������.
 *
 * @details
 * ��� ������� ����������� � ������������ ���� ����� � ��������� ��� �� ������������. ���� ���� �����������,
 * ������������ ������������ ������ �������� ��������.
 *
 * @param[out] value ��������� �� ����������, � ������� ����� ��������� ��������� ��������.
 * @param[in] message ���������, ������� ����� ���������� ������������ ����� ������.
 * @return true, ���� ���� ���������, ����� false.
 */
static bool get_number_input(double* value, const char* message) {
    assert(value != NULL);
    assert(message != NULL);

    if (isatty(fileno(stdin))) {
        printf("%s", message);
    }

    int ch = 0;

    if (scanf("%lf", value) == 1) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
            if (!isspace(ch)) {
                printf("������ �����! ������� �������� ��������.\n");
                clear_input_buffer();
                return false;
            }
        }
        return true;
    } else if (feof(stdin)) {
        printf("������ �����! ��������� EOF.\n");
        return false;
    } else {
        printf("������ �����! ������� �������� ��������.\n");
        clear_input_buffer();
        return false;
    }
}

/**
 * @brief �������� ������������ ����������� ��������� �� ������������.
 *
 * @details
 * ��� ������� ����������� � ������������ ���� ������������� a, b � c ��� ����������� ���������
 * � ��������� �� � ��������� SquareEquationCoefficient. ���� ���� �������� �������� (EOF),
 * ������������ ��� ������.
 *
 * @param[out] coeffts ��������� �� ��������� SquareEquationCoefficient, � ������� ����� ��������� ������������.
 * @return ��� ����������: SUCCESS (0) ��� �������� �����, ERROR_CODE (-1) ��� ������.
 */
int get_coefficients(SquareEquationCoefficient* coeffts) {
    const char* messages[] = {
        "������� ����������� a: ",
        "������� ����������� b: ",
        "������� ����������� c: "
    };

    double* coeffs[NUM_COEFFS] = { &coeffts->a, &coeffts->b, &coeffts->c };

    for (size_t i = 0; i < NUM_COEFFS; i++) {
        while (!get_number_input(coeffs[i], messages[i])) {
            if (feof(stdin)) {
                return ERROR_CODE;
            }
        }
    }
    return SUCCESS;
}

/**
 * @brief ������� ������� ����������� ���������.
 *
 * @details
 * ��� ������� ������� ������� ����������� ��������� �� �����, ������ �� ���� ����������,
 * ������� ������������ ��������� ���������� result.result_type.
 *
 * @param[in] result ��������� SquareEquationResult, ���������� ���������� ������� ���������.
 */
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
