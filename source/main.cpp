/**
 * @file main.cpp
 * @brief ��������� ��� ������� ����������� ���������.
 *
 * ��� ��������� ��������� ������������ ������ ������������ ����������� ���������
 * � ��������� ��� �����. ��� �������� � ���� ������� ��� ��������� �����, �������
 * ����������� ��������� � ������ �����������.
 *
 * @details
 * ��������� ������������� ��������� �������:
 * - @ref is_zero "is_zero" ��� ��������, ������ �� �������� � ���� � �������� EPSILON.
 * - @ref get_number_input "get_number_input" ��� ��������� ��������� ����� �� ������������.
 * - @ref get_coefficients "get_coefficients" ��� ����� ������������� ����������� ���������.
 * - @ref solve_linear_equation "solve_linear_equation" ��� ���������� ������ ��������� ���������.
 * - @ref solve_square_equation "solve_square_equation" ��� ���������� ������ ����������� ���������.
 * - @ref print_solution "print_solution" ��� ������ �����������.
 * - @ref main "main" ��� ���������� �������� ������ ���������.
 *
 * @note ��������: ������� @ref get_number_input "get_number_input" ��������� ���� ����� � �������, ��� ���� ����� �������� ���������.
 *
 * @see SquareEquationCoefficient
 * @see SquareEquationResult
 *
 * @author ����� ���������
 * @date 20.08.2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "solver.h"
#include "input_output_solver.h"
#include "testmode_solver.h"
#include "error_code.h"

enum ChoiceMode {
    TestMode = 1,
    SolverMode,
};

/**
 * @brief �������� ������� ���������.
 *
 * @details
 * ������� ������������� ������ ��� ����������� ����������� ������, ������� ����
 * ��� ������ ������ ������ ���������, � � ����������� �� ������ ������������
 * ��������� ���� ����� ������, ���� ����� ������� ����������� ���������.
 *
 * @return ���������� 0 ��� �������� ���������� ���������, ����� ����������
 *         ��� ������, ����������� ��� ERROR_CODE.
 */
int main() {
    setlocale(LC_ALL, "Rus");

    int choice = 0;
    puts("�������� ����� ������ ���������:\n"
         "1. ����� ������\n"
         "2. ������� ����������� ���������\n"
         "������� ����� ������: ");
    if (scanf("%d", &choice) != 1) {
        printf("������ �����.\n");
        return ERROR_CODE;
    }

    switch (choice) {
        case TestMode:
            run_tests();
            break;

        case SolverMode: {
            SquareEquationCoefficient coeffts;

            if (get_coefficients(&coeffts) != SUCCESS) {
                return ERROR_CODE;
            }

            SquareEquationResult result = solve_square_equation(coeffts);
            print_solution(result);
            break;
        }

        default:
            fprintf(stderr, "������ ������ ������. ����������, �������� 1 ��� 2.\n");
            return ERROR_CODE;
    }

    return 0;
}
