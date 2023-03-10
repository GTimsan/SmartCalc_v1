# SmartCalc_v1

### Реализация калькулятора на языке С и GUI с помощью QT.

#### Installation:
Сборка проекта с помощью [Makefile](https://github.com/GTimsan/SmartCalc_v1/blob/main/src/Makefile) и нужной цели.

#### Navigation
Тесты и вычислительная часть написанная на языке Си:
- [Тесты](https://github.com/GTimsan/SmartCalc_v1/blob/main/src/tests.c)
- [Header](https://github.com/GTimsan/SmartCalc_v1/blob/main/src/calc.h)
- [Реализация](https://github.com/GTimsan/SmartCalc_v1/blob/main/src/calc.c)

#### Description:
Выражение проходит валидацию, разбивается на лексемы и вычисляется(используется Алгоритм Дейкстры):  
![Пример вычислений](./images/1.png)

Реализована отрисовка графиков:  
![Пример графика](./images/2.png)

Дополнительно кредитный калькулятор(аннуитетный, дифференцированный):  
![Пример кредитного калькулятор](./images/3.png)

Документация сгенерирована с помощью doxygen:
![Документация](./images/4.png)
