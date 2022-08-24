OUTDIR = $(shell cd ../build && pwd)
UNAME = $(shell uname -s)
CC = gcc -Wall -Werror -Wextra -std=c11 -g
SOURCES_LIB = bits_forverter.o other_forverter.o arithmetic_forverter.o another_forverter.o comparison_forverter.o convertion_parsing_forverter.o
SOURCES_TEST = bits.o other.o arithmetic.o another.o comparison.o convertion_parsing.o
OUTNAME = "tests"


ifeq ($(UNAME),Darwin)
	FLAGSS = -lcheck -lm -lpthread -fprofile-arcs
endif
ifeq ($(UNAME),Linux)
	FLAGSS = -lcheck -lsubunit -lrt -lm -lpthread -fprofile-arcs
endif


all: cleanall build clean

build: style s21_decimal.a test gcov_report

rebuild: all

gcov_report:
	gcov -b -l -p -c *.gcno
	gcovr -g -k -r . --html --html-details -o coverage_report.html

test: s21_tests.c $(SOURCES_TEST)
	$(CC) s21_tests.c $(SOURCES_TEST) $(FLAGSS) -o $(OUTNAME)
	./$(OUTNAME)

s21_decimal.a: $(SOURCES_LIB) s21_decimal.h
	ar -rcs s21_decimal.a $(SOURCES_LIB) s21_decimal.h
	ranlib s21_decimal.a



### OBJECT FILES

bits.o: helpers/bits.c
	$(CC) -c --coverage helpers/bits.c -o bits.o

other.o: helpers/other.c
	$(CC) -c --coverage helpers/other.c -o other.o

arithmetic.o: main/arithmetic.c
	$(CC) -c --coverage main/arithmetic.c -o arithmetic.o

comparison.o: main/comparison.c
	$(CC) -c --coverage main/comparison.c -o comparison.o

convertion_parsing.o: main/convertion_parsing.c
	$(CC) -c --coverage main/convertion_parsing.c -o convertion_parsing.o

another.o: main/another.c
	$(CC) -c --coverage main/another.c -o another.o


bits_forverter.o: helpers/bits.c
	$(CC) -c helpers/bits.c -o bits_forverter.o

other_forverter.o: helpers/other.c
	$(CC) -c helpers/other.c -o other_forverter.o

arithmetic_forverter.o: main/arithmetic.c
	$(CC) -c main/arithmetic.c -o arithmetic_forverter.o

comparison_forverter.o: main/comparison.c
	$(CC) -c main/comparison.c -o comparison_forverter.o

convertion_parsing_forverter.o: main/convertion_parsing.c
	$(CC) -c main/convertion_parsing.c -o convertion_parsing_forverter.o

another_forverter.o: main/another.c
	$(CC) -c main/another.c -o another_forverter.o

###



style:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	cp ../materials/linters/cpplint.py cpplint.py
	python3 cpplint.py --extension=c *.c *.h
	python3 cpplint.py --extension=c main/*.c
	python3 cpplint.py --extension=c helpers/*.c

valgrind:
	valgrind ./tests

clean:
	/bin/rm -rf *.o

cleanall:
	/bin/rm -rf *.o *.a *.so $(OUTNAME) coverage* *.gcno *.gcda *.gcov *.dSYM *.cfg *.py a.out
