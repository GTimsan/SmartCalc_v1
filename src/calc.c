#include "calc.h"


int smart_calc_v_1(char* str, double* result) {
    int error = validator(str);
    if (!error) {
        stack_t* top = NULL;
        top = revers(pars(str, result));
        top = r_p_n(top);
        *result = prepare_for_calc(top);
    }
    return error;
}

int check_operation(char* str, int i_f, int i_s) {
    int error = 0;
    int flag = 0;
    for (; str[i_f] != -1; i_f--) {
        if ((strchr("-+/*^d", str[i_f])) && i_f == 0) {
            error = 8 * 1000 + i_f;
            break;
        } else if (str[i_f - 1] == ' ') { continue;
        } else if ((strchr("nsgt)(0123456789x", str[i_f - 1]))) { break;
        } else {
            error = 8 * 1000 + i_f;
            break;
        }
    }
    flag = 0;
    for (; str[i_s] != '\0'; i_s++) {
        if (str[i_s + 1] == ' ') {
        } else if (strchr("sctla0123456789x", str[i_s + 1])) { break;
        } else if (str[i_s + 1] == '(') {
            flag = 1;
            continue;
        } else if (strchr("-+/*^m", str[i_s + 1]) && flag) { continue;
        } else {
            error = 8 * 1000 + i_s;
            break;
        }
    }
    return error;
}

stack_t* unary_sign(stack_t* top_f) {
    stack_t tmp;
    tmp.val = 0, tmp.opr = 0, tmp.type = 3;
    if (top_f->opr == 16) {
        top_f = push(&tmp, top_f);
    }

    return top_f;
}

int check_func(char* str, int* i) {
    int error = 0;
    if (!strncmp(str + *i, "sin(", 4)) {*i += 2;
    } else if (!strncmp(str + *i, "sqrt(", 5)) { *i += 3;
    } else if (!strncmp(str + *i, "cos(", 4)) { *i += 2;
    } else if (!strncmp(str + *i, "tan(", 4)) { *i += 2;
    } else if (!strncmp(str + *i, "ln(", 3)) { *i += 1;
    } else if (!strncmp(str + *i, "log(", 4)) { *i += 2;
    } else if (!strncmp(str + *i, "asin(", 5)) { *i += 3;
    } else if (!strncmp(str + *i, "acos(", 5)) { *i += 3;
    } else if (!strncmp(str + *i, "atan(", 5)) { *i += 3;
    } else if (!strncmp(str + *i, "mod", 3)) {
        error = check_operation(str, *i, *i + 2);
        *i += 2;
    } else { error = 7 * 1000 + *i; }

    return error;
}

int validator(char* str) {
    int error = 0;
    int bracket = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') { bracket += 1;
        } else if (str[i] == ')') { bracket -= 1;
        } else if (strchr("+-*/^", str[i])) {
            error = check_operation(str, i, i);
            if (error) break;
        } else if (strchr("sctlma", str[i])) {
            error = check_func(str, &i);
            if (error) break;
        }
    }
    if (!error) {
        if (bracket != 0) error = 9;
    }
    return error;
}

double prepare_for_calc(stack_t* top_f) {
    stack_t* top_s = NULL;
    stack_t tmp;
    double result = 0;
    for (; top_f != NULL;) {
        if (top_f->type == 3) {
            top_s = push(top_f, top_s);
            top_f = pop(top_f);
        } else if (top_f->type == 2) {
            if (strchr("123456", top_f->opr + '0')) {
                double second = top_s->val;
                top_s = pop(top_s);
                double first = top_s->val;
                top_s = pop(top_s);
                result = calculate(first, second, top_f->opr);
                top_f = pop(top_f);
                top_s = push(init_val(3, result, &tmp), top_s);
            } else if (top_f->opr >= 7 && top_f->opr <= 15) {
                double first = top_s->val;
                top_s = pop(top_s);
                result = func_calculate(first, top_f->opr);
                top_f = pop(top_f);
                top_s = push(init_val(3, result, &tmp), top_s);
            }
        }
    }
    destroy(top_s);
    return result;
}

double calculate(double first, double second, int opr) {
    double result = 0;
    if (opr == 1) result = first + second;
    if (opr == 2) result = first - second;
    if (opr == 3) result = first * second;
    if (opr == 4) result = first / second;
    if (opr == 5) result = fmod(first, second);
    if (opr == 6) result = pow(first, second);
    return result;
}

double func_calculate(double first, int opr) {
    double result = 0;
    if (opr == 7) result = sin(first);
    if (opr == 8) result = cos(first);
    if (opr == 9) result = tan(first);
    if (opr == 10) result = asin(first);
    if (opr == 11) result = acos(first);
    if (opr == 12) result = atan(first);
    if (opr == 13) result = sqrt(first);
    if (opr == 14) result = log(first);
    if (opr == 15) result = log10(first);
    return result;
}

stack_t* r_p_n(stack_t* top_f) {
    stack_t* top_s = NULL;
    stack_t* top_th = NULL;
    stack_t tmp;
    tmp.val = 0, tmp.opr = 0, tmp.type = 2;
    top_s = push(&tmp, top_s);
    int i = 0;
    for (; ;) {
        i++;
        if (top_f->type == 3) {
            top_th = push(top_f, top_th);
            top_f = pop(top_f);
            continue;
        } else if (top_f->type == 1) {
            top_th = push(top_f, top_th);
            top_f = pop(top_f);

        } else if (top_f->type == 2) {
            int x = get_weight(top_s->opr, top_f->opr);
            if (x == 1) {
                top_s = push(top_f, top_s);
                top_f = pop(top_f);
            } else if (x == 2) {
                top_th = push(top_s, top_th);
                top_s = pop(top_s);
            } else if (x == 3) {
                if (top_f) top_f = pop(top_f);
                if (top_s) top_s = pop(top_s);
            } else if (x == 4) {break;}
        }
    }

    top_th = revers(top_th);
    destroy(top_f);
    destroy(top_s);
    return top_th;
}

stack_t* pars(char* str, double* result) {
    stack_t* top = NULL;
    stack_t tmp;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] == ' ') || (str[i] == '\n')) {continue;
        } else if (str[i] == '+') {
            top = unary_sign(top);
            top = push(init_val(2, 1, &tmp), top);
        } else if (str[i] == '-') {
            top = unary_sign(top);
            top = push(init_val(2, 2, &tmp), top);
        } else if (str[i] == '*') {top = push(init_val(2, 3, &tmp), top);
        } else if (str[i] == '/') {top = push(init_val(2, 4, &tmp), top);
        } else if (!strncmp(str + i, "mod", 3)) {
            top = push(init_val(2, 5, &tmp), top);
            i += 2;
        } else if (str[i] == '^') {top = push(init_val(2, 6, &tmp), top);
        } else if ((str[i] >= 48) && (str[i] <= 57)) {
            double x = find_value(str, &i);
            top = push(init_val(3, x, &tmp), top);
        } else if (!strncmp(str + i, "sin", 3)) {
            i += 2;
            top = push(init_val(2, 7, &tmp), top);
        } else if (!strncmp(str + i, "cos", 3)) {
            top = push(init_val(2, 8, &tmp), top);
            i += 2;
        } else if (!strncmp(str + i, "tan", 3)) {
            top = push(init_val(2, 9, &tmp), top);
            i += 2;
        } else if (!strncmp(str + i, "asin", 4)) {
            top = push(init_val(2, 10, &tmp), top);
            i += 3;
        } else if (!strncmp(str + i, "acos", 4)) {
            top = push(init_val(2, 11, &tmp), top);
            i += 3;
        } else if (!strncmp(str + i, "atan", 4)) {
            top = push(init_val(2, 12, &tmp), top);
            i += 3;
        } else if (!strncmp(str + i, "sqrt", 4)) {
            top = push(init_val(2, 13, &tmp), top);
            i += 3;
        } else if (!strncmp(str + i, "ln", 2)) {
            top = push(init_val(2, 14, &tmp), top);
            i += 1;
        } else if (!strncmp(str + i, "log", 3)) {
            top = push(init_val(2, 15, &tmp), top);
            i += 2;
        } else if (str[i] == '(') { top = push(init_val(2, 16, &tmp), top);
        } else if (str[i] == ')') { top = push(init_val(2, 17, &tmp), top);
        } else if (str[i] == 'x') { top = push(init_val(3, *result, &tmp), top); }
    }
    tmp.val = 0, tmp.opr = 0, tmp.type = 2;
    top = push(&tmp, top);
    return top;
}

double find_value(char* str, int* pos_i) {
    char arr[50] = {0};
    int j = 0;
    for (int i = *pos_i; ;) {
        if (((str[i] >= 48) && (str[i] <= 57)) || str[i] == '.') {
            arr[j] = str[i];
            j++, i++;
        } else { break; }
    }
    double tmp = atof(arr);
    *pos_i += j - 1;
    return tmp;
}


stack_t* init_val(int type, double value, stack_t* tmp) {
    tmp->type = type;
    tmp->var = (type == 1) ? value : 0;
    tmp->opr = (type == 2) ? value : 0;
    tmp->val = (type == 3) ? value : 0;
    return tmp;
}

stack_t* init(stack_t* new_stack) {
    stack_t* tmp = (stack_t*) malloc(sizeof(stack_t));
    tmp->val = new_stack->val;
    tmp->opr = new_stack->opr;
    tmp->type = new_stack->type;
    tmp->next = NULL;
    return tmp;
}

stack_t* push(stack_t* data, stack_t* top) {
    stack_t* tmp = init(data);
    if (top) {
        tmp->val = data->val;
        tmp->opr = data->opr;
        tmp->type = data->type;
        tmp->next = top;
    }
    return tmp;
}

stack_t* pop(stack_t* top) {
    stack_t* tmp = top->next;
    free(top);
    return tmp;
}

stack_t* revers(stack_t* top) {
    stack_t* tmp = NULL;
    do {
        tmp = push(top, tmp);
        top = pop(top);
    } while (top);
    free(top);
    return tmp;
}


int get_weight(int i, int j) {
    int matrix[17][18] = {
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5},
        {2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2},
        {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    };
    return matrix[i][j];
}

void destroy(stack_t* top) {
        while (top->next != NULL) top = pop(top);
        free(top);
}
// -----------------------------------------------------------------
// char conv(int operation) {
//     char opr;
//     switch (operation) {
//         case 1 : opr = '+';
//             break;
//         case 2 : opr = '-';
//             break;
//         case 3 : opr = '*';
//             break;
//         case 4 : opr = '/';
//             break;
//         case 5 : opr = '^';
//             break;
//         case 6 : opr = 's';
//             break;
//         case 7 : opr = 's';
//             break;
//         case 8 : opr = 't';
//             break;
//         case 9 : opr = 'g';
//             break;
//         case 10 : opr = 'r';
//             break;
//         case 11 : opr = 'l';
//             break;
//         case 12 : opr = '(';
//             break;
//         case 13 : opr = ')';
//             break;
//     }
//     return opr;
// }

// void output(stack_t* top) {
//     stack_t* tmp = top;
//     for (; tmp != NULL; ) {
//         if (tmp->type == 1) printf("x");
//         else if (tmp->type == 2) printf("%c", conv(tmp->opr));
//         else if (tmp->type == 3) printf("%.0f", tmp->val);
//             tmp = tmp->next;
//         }
//         printf("\n");
// }
