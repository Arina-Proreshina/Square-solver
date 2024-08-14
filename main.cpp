/**
 * @file
 * @brief Программа для решения квадратного уравнения.
 *
 * Эта программа позволяет пользователю ввести коэффициенты квадратного уравнения
 * и вычислить его корни. Она включает в себя функции для проверки ввода, решения
 * квадратного уравнения и печати результатов.
 *
 * @details
 * Программа использует следующие функции:
 * - @ref my_isdigit "my_isdigit" для проверки, является ли символ цифрой.
 * - @ref solve_square_equation "solve_square_equation" для вычисления корней квадратного уравнения.
 * - @ref print_solution "print_solution" для печати результатов.
 * - @ref is_number "is_number" для проверки, является ли строка числом.
 * - @ref get_number_input "get_number_input" для получения числового ввода от пользователя.
 * - @ref main "main" является главной функцией программы.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>
#include <assert.h>

/**
 * @brief Размер буфера для ввода данных.
 *
 * Эта константа используется для определения размера массива, в который
 * сохраняется ввод пользователя. Размер установлен на 100 символов.
 *
 * @note Размер буфера может быть изменен в зависимости от требований
 * программы или ограничений системы.
 */
const int INPUT_SIZE = 100;

/**
 * @struct SquareEquationCoefficient
 * @brief Структура для хранения коэффициентов квадратного уравнения.
 *
 * Эта структура содержит коэффициенты уравнения ax^2 + bx + c = 0.
 */
typedef struct {
    double a; /**< Коэффициент a */
    double b; /**< Коэффициент b */
    double c; /**< Коэффициент c */
} SquareEquationCoefficient;

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
 * @brief Проверяет, является ли символ цифрой (0-9).
 *
 * @param[in] c Символ для проверки.
 * @return true Если символ является цифрой.
 * @return false Если символ не является цифрой.
 */
bool my_isdigit(int c) {
    return c >= '0' && c <= '9';
}

/**
 * @brief Решает квадратное уравнение ax^2 + bx + c = 0.
 *
 * Эта функция вычисляет дискриминант и на основе его значения определяет
 * корни квадратного уравнения. Результаты хранятся в структуре SquareEquationResult.
 *
 * @param[in] coeffts Указатель на структуру SquareEquationCoefficient, содержащую коэффициенты уравнения.
 * @return SquareEquationResult Структура, содержащая корни уравнения и тип результата.
 */
SquareEquationResult solve_square_equation(const SquareEquationCoefficient* coeffts) {
    assert(coeffts != NULL);

    SquareEquationResult result;
    result.result_type = 0;

    double dscr = pow(coeffts->b, 2) - 4 * coeffts->a * coeffts->c;

    if (coeffts->a == 0) {
        result.x1 = -coeffts->c / coeffts->b;
        result.result_type = 1;
    } else if (dscr > 0) {
        result.x1 = (-coeffts->b + sqrt(dscr)) / (2 * coeffts->a);
        result.x2 = (-coeffts->b - sqrt(dscr)) / (2 * coeffts->a);
        result.result_type = 2;
    } else if (dscr == 0) {
            result.x1 = -coeffts->b / (2*coeffts->a);
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
 * @param[in] result Указатель на структуру SquareEquationResult, содержащую результаты.
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
        default:
            printf("Ошибка: Неизвестный тип результата.\n");
            break;
    }
}

/**
 * @brief Проверяет, является ли строка числом.
 *
 * Эта функция проверяет, содержит ли строка корректное числовое значение (включая вещественные числа).
 *
 * @param[in] str Указатель на строку, которую нужно проверить.
 * @return true Если строка является числом.
 * @return false Если строка не является числом.
 */
bool is_number(const char* str) {
    assert(str != NULL);

    if (*str == '\0') return false;
    bool has_digit = false;
    bool has_point = false;

    if (*str == '-' || *str == '+') {
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
 * @param[in] value Указатель на переменную, в которую будет записано значение.
 * @param[out] message Сообщение, которое будет отображено пользователю.
 * @return true Если ввод был корректным числом.
 * @return false Если ввод не был числом.
 */
bool get_number_input(double* value, const char* message) {
    assert(value != NULL);
    assert(message != NULL);

    printf("%s", message);

    while (1) {
        int result = scanf("%lf", value);

        if (result == 1) {
            while (getchar() != '\n');
            return true;
        } else {
            printf("Ошибка ввода! Введите числовое значение.\n");
            return false;
        }
        printf("%s", message);
    }
}

/**
 * @brief Главная функция программы.
 *
 * Эта функция устанавливает локаль, получает коэффициенты уравнения от пользователя,
 * решает квадратное уравнение и выводит результат.
 *
 * @return int Код завершения программы. Возвращает 0 при успешном завершении, -1 при ошибке ввода.
 */
int main() {
    setlocale(LC_ALL, "Rus");
    SquareEquationCoefficient coeffts;

    if (!get_number_input(&coeffts.a, "Введите коэффициент a: ")) return -1;
    if (!get_number_input(&coeffts.b, "Введите коэффициент b: ")) return -1;
    if (!get_number_input(&coeffts.c, "Введите коэффициент c: ")) return -1;

    SquareEquationResult result = solve_square_equation(&coeffts);
    print_solution(&result);

    return 0;
}
