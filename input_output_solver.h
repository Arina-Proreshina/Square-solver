/**
 * @file input_output_solver.h
 * @brief ������������ ���� ��� ����� � ������ ������ � ��������� ������� ���������� ���������.
 *
 * @details
 * ���� ���� �������� ���������� ������� ��� ����� ������������� ����������� ���������
 * �� ������������ � ������ ����������� ������� ���������. ����� ������������ ����
 * ������, ������������ � ���������.
 *
 * �������� �������:
 * - @ref get_coefficients: ����������� ���� ������������� � ������������.
 * - @ref print_solution: �������� ���������� ������� ���������.
 *
 * @author ����� ���������
 * @date 20.08.2024
 */
#ifndef INPUT_OUTPUT_SOLVER_H
#define INPUT_OUTPUT_SOLVER_H
#include "solver.h"

/**
 * @enum ErrorCode
 * @brief ���� ������ ��� ���������.
 *
 * ��� ������������ �������� ����, ������� ������������ ��� �����������
 * ��������� ���������� ��������� ��� ������.
 */
enum {
    SUCCESS = 0,    /**< �������� ���������� ��������. */
    ERROR_CODE = -1 /**< ������ ���������� ��������. */
} ErrorCode;

/**
 * @brief ����������� ���� ������������� ����������� ��������� �� ������������.
 *
 * @details
 * ������� ������� ��������� ��� ����� ������������� a, b � c, � ���������
 * �� �������� �� ������������ �����. ��� �������� ����� ���������� 0,
 * ����� ���������� ��� ������ (����������� ��� ERROR_CODE).
 *
 * @param[out] coeffts ��������� �� ���������, � ������� ����� ��������� ��������� ������������.
 *
 * @return ���������� 0 ��� �������� ����� ���� �������������, ����� ���������� ERROR_CODE.
 */
int get_coefficients(SquareEquationCoefficient* coeffts);

/**
 * @brief �������� ������� ����������� ���������.
 *
 * @details
 * ��� ������� ��������� ��������� SquareEquationResult � �������� ���������������
 * ��������� � ����������� �� ���� ����������.
 *
 * @param[in] result ��������� �� ��������� SquareEquationResult, ���������� ����������.
 */
void print_solution(SquareEquationResult result);

#endif // INPUT_OUTPUT_SOLVER_H
