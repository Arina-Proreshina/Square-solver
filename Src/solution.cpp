#include <stdio.h>
#include <stdlib.h>
#include ".../Lib/solution.h"

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
