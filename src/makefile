FLAGS = -Wall -Werror -Wextra -std=c++17

OS=$(shell uname)
ifeq ($(OS), Linux)
system =@echo "linux"
LIBS = -lpthread
LEAKS = @valgrind ./report_test
OPEN_REPORT = @xdg-open report/index.html 
endif
ifeq ($(OS), Darwin)
system = @echo "MacOs"
LEAKS = @leaks -atExit -- ./report_test
OPEN_REPORT = @open report/index.html 
endif

all: s21_matrix_oop.a
	$(system)

clean:
	@rm -rf test
	@rm -rf report_test
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf *.out
	@rm -rf *.info
	@rm -rf *.o
	@rm -rf *.a
	@rm -rf .clang-format
	@rm -rf report
	@echo "CLEAN"

test:
	@clear
	@g++ $(FLAGS) *.cc -o report_test -lgtest -lgtest_main $(LIBS)
	@./report_test
	@echo "TEST"

s21_matrix_oop.a:
	@g++ $(FLAGS) -c s21_matrix_oop.cc
	@ar -cr s21_matrix_oop.a s21_matrix_oop.o


clang:
	@cp ../materials/linters/.clang-format .
	clang-format -i *.cc *.h
	clang-format -n *.cc *.h


gcov_report:
	@g++ --coverage *.cc -o report_test -lgtest -lgtest_main $(LIBS)
	@./report_test
	@lcov -t "test" -o test.info --no-external -c -d .
	@genhtml -o report test.info
	$(OPEN_REPORT)
	@echo "GCOV_REPORT"

leaks: test
	$(LEAKS)
