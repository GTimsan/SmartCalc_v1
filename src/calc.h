#ifndef SRC_CALC_H_
#define SRC_CALC_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    double var;
    double val;
    int opr;
    int type;
    void* next;
} stack_t;

/**
 * @brief Основная функция вычисляет выражение, парсит строку, переводит в обратную польскую нотацию и производит вычисления
 * 
 * @param str строка для вычисления
 * @param result на входе хранится значение "X", на выходе результат вычисления
 * @return int возвращает код ошибки
 */
int smart_calc_v_1(char* str, double* result);

/**
 * @brief Проверяет знак на унарность
 * 
 * @param top_f стек
 * @return stack_t* 
 */
stack_t* unary_sign(stack_t* top_f);

/**
 * @brief Производит вычисления с участием математических операций
 * 
 * @param first 
 * @param second 
 * @param opr номер операции
 * @return double 
 */
double calculate(double first, double second, int opr);

/**
 * @brief Вычисляет выражение с участием функции
 * 
 * @param first 
 * @param opr каждому номеру соответствует своя функция
 * @return double 
 */
double func_calculate(double first, int opr);

/**
 * @brief Достает из стека значения и определяет вычислять как функцию или операцию
 * 
 * @param top_f 
 * @return double 
 */
double prepare_for_calc(stack_t* top_f);

/**
 * @brief Переводит в польскую нотацию
 * 
 * @param top_f 
 * @return stack_t* 
 */
stack_t* r_p_n(stack_t* top_f);

/**
 * @brief Очищает стек
 * 
 * @param top 
 */
void destroy(stack_t* top);

/**
 * @brief Получает приоритет для значений
 * 
 * @param i 
 * @param j 
 * @return int 
 */
int get_weight(int i, int j);

/**
 * @brief Парсит число и переводит в тип double
 * 
 * @param str 
 * @param pos_i 
 * @return double 
 */
double find_value(char* str, int* pos_i);

/**
 * @brief Парсит строку и заполняет стек
 * 
 * @param str 
 * @param result 
 * @return stack_t* 
 */
stack_t* pars(char* str, double* result);

/**
 * @brief Инициализирует значение в структуре в стеке
 * 
 * @param type 
 * @param value 
 * @param tmp 
 * @return stack_t* 
 */
stack_t* init_val(int type, double value, stack_t* tmp);

/**
 * @brief Инициализирует структуру в стеке
 * 
 * @param new_stack 
 * @return stack_t* 
 */
stack_t* init(stack_t* new_stack);

/**
 * @brief Добавляет структуру в стек
 * 
 * @param data 
 * @param top 
 * @return stack_t* 
 */
stack_t* push(stack_t* data, stack_t* top);

/**
 * @brief Удаляет структуру из стека
 * 
 * @param top 
 * @return stack_t* 
 */
stack_t* pop(stack_t* top);

/**
 * @brief Меняет местами структуры в стеке
 * 
 * @param top 
 * @return stack_t* 
 */
stack_t* revers(stack_t* top);

/**
 * @brief Проверяет на валидность строку
 * 
 * @param str 
 * @return int код 9 - ошибка скобок, 7000 - ошибка функции, 8000 - ошибка знака
 */
int validator(char* str);

/**
 * @brief Проверяет знаки при валидации
 * 
 * @param str 
 * @param i_f 
 * @param i_s 
 * @return int 
 */
int check_operation(char* str, int i_f, int i_s);

/**
 * @brief Проверяет функции при валидации
 * 
 * @param str 
 * @param i 
 * @return int 
 */
int check_func(char* str, int* i);
// -----------------------------------------------------------
// char conv(int operation);
// void output(stack_t* top);

#endif  // SRC_CALC_H_
