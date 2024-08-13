#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

void solve_square(double a, double b, double c) {
    double dscr, x1, x2;
    dscr = pow(b, 2) - 4 * a * c;

    if (dscr > 0) {
        x1 = (-b + sqrt(dscr)) / (2 * a);
        x2 = (-b - sqrt(dscr)) / (2 * a);
        printf("Корни уравнения: x1 = %.2f, x2 = %.2f\n", x1, x2);
    } else if (dscr == 0) {
            x1 = -b / (2*a);
            printf("Один корень уравнения: x = %.2f\n", x1);

    } else {
       printf("Уравнение не имеет вещественных корней.\n");
    }
}

bool is_number(const char* str) {
    if (*str == '\0') return false;
    bool has_digit = false;
    bool has_point = false;
    bool has_sign = false;

    if (*str == '-' || *str == '+') {
        has_sign = true;
        str++;
    }

    if (*str == '\0') return false;

    while (*str) {
        if (*str == '.') {
            if (has_point) return false;
            has_point = true;
        } else if (isdigit(*str)) {
            has_digit = true;
        } else {
            return false;
        }
        str++;
    }

    return has_digit;
}

bool get_int_input(double* value, const char* message) {
    char input[100];

    while (1) {
        printf("%s", message);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';
            if (is_number(input)) {
                sscanf(input, "%lf", value);
                return true;
            }
        }
        printf("Ошибка ввода! Введите числовое значение.\n");
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    double a, b, c;

    if (!get_int_input(&a, "Введите коэффициент a: ")) return 1;
    if (!get_int_input(&b, "Введите коэффициент b: ")) return 1;
    if (!get_int_input(&c, "Введите коэффициент c: ")) return 1;

    solve_square(a, b, c);

    return 0;
}
