#include <stdio.h>
#include <stdlib.h>
#include ".../Lib/solution.h"

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
