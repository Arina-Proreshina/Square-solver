#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <assert.h>

#define INPUT_SIZE 100

/**
 * @brief Проверяет, является ли символ цифрой (0-9).
 *
 * @param c Символ для проверки.
 * @return true Если символ является цифрой.
 * @return false Если символ не является цифрой.
 */
bool my_isdigit(int c) {
    return c >= '0' && c <= '9';
}

/**
 * @struct SquareEquationResult
 * @brief Структура для хранения результатов решения квадратного уравнения.
 *
 * Эта структура содержит результаты решения квадратного уравнения,
 * а также тип результата, который указывает на количество корней.
 */
typedef struct {
    double x1;      /**< Первый корень уравнения */
    double x2;      /**< Второй корень уравнения */
    int result_type;/**< Тип результата: 0 - нет вещественных корней, 1 - один корень, 2 - два корня */
} SquareEquationResult;

/**
 * @brief Решает квадратное уравнение ax^2 + bx + c = 0.
 *
 * Эта функция вычисляет дискриминант и на основе его значения определяет
 * корни квадратного уравнения. Результаты хранятся в структуре SquareEquationResult.
 *
 * @param a Коэффициент a уравнения
 * @param b Коэффициент b уравнения
 * @param c Коэффициент c уравнения
 * @return SquareEquationResult Структура, содержащая корни уравнения и тип результата
 */
SquareEquationResult solve_square_equation(double a, double b, double c) {
    SquareEquationResult result;
    result.result_type = 0;

    double dscr = pow(b, 2) - 4 * a * c;

    if (a == 0) {
        printf("Коэффициент a не может быть равен нулю для квадратного уравнения.\n");
        exit(1);
    }

    if (dscr > 0) {
        result.x1 = (-b + sqrt(dscr)) / (2 * a);
        result.x2 = (-b - sqrt(dscr)) / (2 * a);
        result.result_type = 2;
    } else if (dscr == 0) {
            result.x1 = -b / (2*a);
            result.result_type = 1;

    }

    return result;
}

/**
 * @brief Печатает решение квадратного уравнения.
 *
 * Эта функция принимает структуру SquareEquationResult и печатает соответствующее
 * сообщение в зависимости от типа результата.
 *
 * @param result Указатель на структуру SquareEquationResult, содержащую результаты
 */
void print_solution(const SquareEquationResult* result) {
    assert(result != NULL);

    switch (result->result_type) {
        case 2:
            printf("Корни уравнения: x1 = %.2f, x2 = %.2f\n", result->x1, result->x2);
            break;
        case 1:
            printf("Один корень уравнения: x = %.2f\n", result->x1);
            break;
        case 0:
            printf("Уравнение не имеет вещественных корней.\n");
            break;
    }
}

/**
 * @brief Проверяет, является ли строка числом.
 *
 * Эта функция проверяет, содержит ли строка корректное числовое значение (включая вещественные числа).
 *
 * @param str Указатель на строку, которую нужно проверить
 * @return true Если строка является числом
 * @return false Если строка не является числом
 */
bool is_number(const char* str) {
    assert(str != NULL);

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
        } else if (my_isdigit(*str)) {
            has_digit = true;
        } else {
            return false;
        }
        str++;
    }

    return has_digit;
}

/**
 * @brief Получает числовой ввод от пользователя.
 *
 * Эта функция запрашивает у пользователя ввод числового значения и проверяет его корректность.
 *
 * @param value Указатель на переменную, в которую будет записано значение
 * @param message Сообщение, которое будет отображено пользователю
 * @return true Если ввод был корректным числом
 * @return false Если ввод не был числом (функция будет продолжать запрашивать ввод)
 */
bool get_number_input(double* value, const char* message) {
    assert(value != NULL);
    assert(message != NULL);

    char input[INPUT_SIZE];

    while (1) {
        printf("%s", message);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            char* newline = strchr(input, '\n');
            if (newline != NULL) {
                *newline = '\0';
            }

            if (is_number(input)) {
                sscanf(input, "%lf", value);
                return true;
            }
        }
        printf("Ошибка ввода! Введите числовое значение.\n");
    }
}

/**
 * @brief Главная функция программы.
 *
 * Эта функция устанавливает локаль, получает коэффициенты уравнения от пользователя,
 * решает квадратное уравнение и выводит результат.
 *
 * @return int Код завершения программы (0 - успешно, -1 - ошибка ввода)
 */
int main() {
    setlocale(LC_ALL, "Rus");
    double a, b, c;

    if (!get_number_input(&a, "Введите коэффициент a: ")) return -1;
    if (!get_number_input(&b, "Введите коэффициент b: ")) return -1;
    if (!get_number_input(&c, "Введите коэффициент c: ")) return -1;

    SquareEquationResult result = solve_square_equation(a, b, c);
    print_solution(&result);

    return 0;
}
