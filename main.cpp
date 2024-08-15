/**
 * @file
 * @brief Программа для решения квадратного уравнения.
 *
 * Эта программа позволяет пользователю ввести коэффициенты квадратного уравнения
 * и вычислить его корни. Она включает в себя функции для получения ввода, решения
 * квадратного уравнения и печати результатов.
 *
 * @details
 * Программа предоставляет следующие функции:
 * - @ref is_zero "is_zero" для проверки, близко ли значение к нулю в пределах EPSILON.
 * - @ref get_number_input "get_number_input" для получения числового ввода от пользователя.
 * - @ref get_coefficients "get_coefficients" для ввода коэффициентов квадратного уравнения.
 * - @ref solve_linear_equation "solve_linear_equation" для вычисления корней линейного уравнения.
 * - @ref solve_square_equation "solve_square_equation" для вычисления корней квадратного уравнения.
 * - @ref print_solution "print_solution" для печати результатов.
 * - @ref main "main" для выполнения основной логики программы.
 *
 * @note Внимание: Функция @ref get_number_input "get_number_input" проверяет ввод чисел и ожидает, что ввод будет числовым значением.
 *
 * @see SquareEquationCoefficient
 * @see SquareEquationResult
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>
#include <assert.h>

/**
 * @constant ERROR_CODE
 * @brief Код ошибки, указывающий на неудачное выполнение операции.
 *
 * Эта константа используется для обозначения ошибки в различных функциях и операциях,
 * где возвращаемое значение -1 сигнализирует о неудачном завершении.
 *
 * @note Константа используется для упрощения обработки ошибок в коде.
 */
const int ERROR_CODE = -1;

/**
 * @brief Константа, представляющая значение \(10^{-6}\).
 *
 * Эта константа используется в программе для представления значения,
 * близкого к нулю. Она может быть полезна при сравнении чисел с плавающей
 * запятой для учета погрешности вычислений и определения, когда число
 * считается практически равным нулю.
 *
 * @note Значение константы установлено как 1e-6, что эквивалентно \(10^{-6}\).
 * Оно может использоваться для проверки чисел на близость к нулю, чтобы избежать
 * проблем, связанных с точностью вычислений с плавающей запятой.
 */
const double EPSILON = 1e-6;

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
    double x1;       /**< Первый корень уравнения */
    double x2;       /**< Второй корень уравнения */
    int result_type; /**< Тип результата: 0 - нет вещественных корней, 1 - один корень, 2 - два корня, 3 - бесконечно много корней*/
} SquareEquationResult;

/**
 * @enum RootNumber
 * @brief Перечисление для представления количества корней квадратного уравнения.
 *
 * Это перечисление используется для обозначения количества вещественных корней
 * квадратного уравнения. Оно определяет возможные значения количества корней
 * уравнения в зависимости от дискриминанта и коэффициентов уравнения.
 *
 * @var RootNumber::NoRoots
 * Значение 0: Уравнение не имеет вещественных корней.
 *
 * @var RootNumber::OneRoot
 * Значение 1: Уравнение имеет один вещественный корень.
 *
 * @var RootNumber::TwoRoots
 * Значение 2: Уравнение имеет два вещественных корня.
 *
 * @var RootNumber::InfRoots
 * Значение 3: Уравнение имеет бесконечно много корней (применимо для случая, когда a = 0 и b = 0).
 */
enum RootNumber {
    NoRoots,  /**< Уравнение не имеет вещественных корней. */
    OneRoot,  /**< Уравнение имеет один вещественный корень. */
    TwoRoots, /**< Уравнение имеет два вещественных корня. */
    InfRoots  /**< Уравнение имеет бесконечно много корней. */
};

/**solve_linear_equation
 * @brief Проверяет, близко ли значение к нулю в пределах EPSILON.
 *
 * @param value Значение, которое нужно проверить.
 * @return true Если значение близко к нулю в пределах EPSILON.
 * @return false Если значение не близко к нулю.
 */
bool is_zero(double value) {
    return fabs(value) < EPSILON;
}

/**
 * @brief Решает линейное уравнение вида bx + c = 0.
 *
 * Эта функция вычисляет корень линейного уравнения на основе коэффициентов
 * b и c. Она обрабатывает специальные случаи, когда коэффициенты b и/или c равны нулю.
 *
 * @param[in] coeffts Структура, содержащая коэффициенты линейного уравнения.
 *                    - `coeffts.b` Коэффициент при x.
 *                    - `coeffts.c` Свободный член.
 * @return SquareEquationResult Структура, содержащая результат решения уравнения.
 *                              - `result.x1` Значение корня уравнения (действительное число).
 *                              - `result.result_type` Тип результата:
 *                                - `InfRoots`  Если уравнение имеет бесконечно много решений (когда b = 0 и c = 0).
 *                                - `NoRoots`   Если уравнение не имеет решений (когда b = 0 и c != 0).
 *                                - `OneRoot`   Если уравнение имеет один корень (когда b != 0).
 */
SquareEquationResult solve_linear_equation(SquareEquationCoefficient coeffts) {
    SquareEquationResult result;

    if (is_zero(coeffts.b)) {
        if (is_zero(coeffts.c)) {
            result.result_type = InfRoots;
        } else {
            result.result_type = NoRoots;
        }
    } else {
        result.x1 = -coeffts.c / coeffts.b;
        result.result_type = OneRoot;
    }
    return result;
}


/**
 * @brief Решает квадратное уравнение вида ax^2 + bx + c = 0.
 *
 * Эта функция вычисляет корни квадратного уравнения на основе коэффициентов
 * a, b и c. Она также учитывает случай, когда коэффициент a равен нулю, и
 * переходит к решению линейного уравнения вида bx + c = 0.
 *
 * @param[in] coeffts Структура, содержащая коэффициенты квадратного уравнения.
 *                    - `coeffts.a` Коэффициент при x^2.
 *                    - `coeffts.b` Коэффициент при x.
 *                    - `coeffts.c` Свободный член.
 * @return SquareEquationResult Структура, содержащая результат решения уравнения.
 *                              - `result.x1` Первый корень уравнения (действительное число).
 *                              - `result.x2` Второй корень уравнения (действительное число, если существует).
 *                              - `result.result_type` Тип результата:
 *                                - `InfRoots`  Если уравнение имеет бесконечно много решений (когда a = 0, b = 0 и c = 0).
 *                                - `NoRoots`   Если уравнение не имеет решений (когда a = 0, b = 0 и c != 0).
 *                                - `OneRoot`   Если уравнение имеет один корень (когда a = 0, b != 0 или дискриминант равен нулю).
 *                                - `TwoRoots`  Если уравнение имеет два корня (когда дискриминант больше нуля).
 */
SquareEquationResult solve_square_equation(SquareEquationCoefficient coeffts) {
    SquareEquationResult result;
    result.result_type = NoRoots;

    double dscr = coeffts.b * coeffts.b - 4 * coeffts.a * coeffts.c;

    if (is_zero(coeffts.a)) {
        result = solve_linear_equation(coeffts);
    } else if (dscr > 0) {
        result.x1 = (-coeffts.b + sqrt(dscr)) / (2 * coeffts.a);
        result.x2 = (-coeffts.b - sqrt(dscr)) / (2 * coeffts.a);
        result.result_type = TwoRoots;
    } else if (is_zero(dscr)) {
        result.x1 = -coeffts.b / (2 * coeffts.a);
        result.result_type = OneRoot;
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

    while (true) {
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
 * @brief Запрашивает ввод коэффициентов квадратного уравнения от пользователя.
 *
 * Функция выводит сообщения для ввода коэффициентов a, b и c, и считывает
 * их значения из стандартного ввода. При успешном вводе возвращает 0,
 * иначе возвращает код ошибки (определённый как ERROR_CODE).
 *
 * @param[out] coeffts Указатель на структуру, в которую будут сохранены введенные коэффициенты.
 *
 * @return Возвращает 0 при успешном вводе всех коэффициентов, иначе возвращает ERROR_CODE.
 */
int get_coefficients(SquareEquationCoefficient* coeffts) {
    const char* messages[] = {
        "Введите коэффициент a: ",
        "Введите коэффициент b: ",
        "Введите коэффициент c: "
    };

    double* coeffs[] = { &coeffts->a, &coeffts->b, &coeffts->c };

    for (size_t i = 0; i < 3; i++) {
        if (!get_number_input(coeffs[i], messages[i])) {
            return ERROR_CODE;
        }
    }
    return 0;
}

/**
 * @brief Основная функция программы.
 *
 * Функция устанавливает локаль для вывода сообщений, вызывает функцию
 * для получения коэффициентов квадратного уравнения от пользователя, затем
 * вычисляет корни уравнения и выводит результат. При возникновении ошибки
 * во время ввода коэффициентов, функция завершает выполнение с кодом ошибки.
 *
 * @return Возвращает 0 при успешном выполнении программы, иначе возвращает ERROR_CODE.
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
