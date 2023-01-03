CC=gcc
FLAGS=-std=c11 -Wall -Werror -Wextra -g
LIBS_MACOS= -L /usr/local/lib -lcheck
LIBS_LINUX= -lcheck -lm -lpthread -lrt -lsubunit -D_GNU_SOURCE
 
OS = $(shell uname)
ifeq ($(OS), Darwin)
APP = TestProject.app
APPF = Calc_release.app
OPEN=open
LIBS=$(LIBS_MACOS)
# LEAK_CHECK = leaks --atExit -- ./test
endif
 
ifeq ($(OS), Linux)
OPEN=xdg-open
LIBS=$(LIBS_LINUX)
APP = TestProject
APPF = Calc_release
# cppcheck --enable=all --suppress=missingIncludeSystem src/soursefile_name.c
# LEAK_CHECK = valgrind --leak-check=full --show-leak-kinds=all -s ./a.out
# python3 materials/linters/cpplint.py --extensions=c src/sourcefile_name.c
endif

all: install

build:
	mkdir build
	cp TestProject.pro main.cpp mainwindow.cpp mainwindow.h mainwindow.ui build
	cp creditwindow.cpp creditwindow.h creditwindow.ui build
	cp graphwindow.cpp graphwindow.h graphwindow.ui build
	cp qcustomplot.cpp qcustomplot.h calc.c calc.h build
	cd build; qmake TestProject.pro
	make -C build
	cd build; rm -rf *.c *.h *.cpp *.ui 

install: build
	@mkdir Smart_Calc_v1.0
	@cp -rf build/$(APP) Smart_Calc_v1.0/
	mv Smart_Calc_v1.0/$(APP) Smart_Calc_v1.0/$(APPF)
	make clean

uninstall:
	@rm -rf Smart_Calc_v1.0/

dist: 
	rm -rf archive_Smartcalc/
	mkdir archive_Smartcalc/
	mkdir archive_Smartcalc/src
	cp Makefile *.c *.h *.pro *.cpp Doxyfile *.ui *.user archive_Smartcalc/src/
	tar cvzf archive_Smartcalc.tgz archive_Smartcalc/
	rm -rf archive_Smartcalc/

dvi:
	doxygen

calc.o_with_gcov: calc.c
	@$(CC) $(FLAGS) -c calc.c --coverage

tests: clean calc.o_with_gcov
	@$(CC) tests.c calc.o -o s21_test $(LIBS) --coverage
	@./s21_test
	@rm -f s21_test.gcda s21_test.gcno s21_test.c

test_val: clean calc.o_with_gcov
	$(CC) tests.c calc.o -o s21_test $(LIBS) --coverage
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./s21_test
	rm -f s21_test.gcda s21_test.gcno s21_test.c


gcov_report: tests
	gcovr --html --html-details -o report.html
	$(OPEN) report.html

lcov: tests
	lcov -t “test” -o lcov_test.info -c -d .
	genhtml -o report lcov_test.info
	$(OPEN) ./report/index.html

clean:
	@rm -f *.out *.gcda *.gcno *.o *.a report.* s21_test test_with_gcov* *.gcov s21_test.c *.info
	@rm -rf ./lcov_report report/ log.txt ./build generated-docs/ *tgz
