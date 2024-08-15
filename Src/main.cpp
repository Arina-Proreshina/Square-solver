/**
 * @file
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include ".../Lib/input.h"
#include ".../Lib/equation.h"

/**
 * @brief �������� ������� ���������.
 *
 * ������� ������������� ������ ��� ������ ���������, �������� �������
 * ��� ��������� ������������� ����������� ��������� �� ������������, �����
 * ��������� ����� ��������� � ������� ���������. ��� ������������� ������
 * �� ����� ����� �������������, ������� ��������� ���������� � ����� ������.
 *
 * @return ���������� 0 ��� �������� ���������� ���������, ����� ���������� ERROR_CODE.
 */
int main() {
    setlocale(LC_ALL, "Rus");
    SquareEquationCoefficient coeffts;

    if (get_coefficients(&coeffts) != 0) {
        return ERROR_CODE;
    }

    SquareEquationResult result = solve_square_equation(coeffts);
    print_solution(result);

    return 0;
}
