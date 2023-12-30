.PHONY: all dist install uninstall dist dvi gcov_report clean check rebuild
CXX = g++ -std=c++17
CXXFLAGS = -Wall -Werror -Wextra -g
OS = $(shell uname -s)
TEST_FLAGS = -o test.out -lgtest

GCOV := $(shell which gcov)
LCOV := $(shell which lcov)
GENHTML := $(shell which genhtml)

CLANG_FORMAT := $(shell which clang-format)
CPPCHECK := $(shell which cppcheck)
VALGRIND := $(shell which valgrind)

ifeq ($(OS), Linux)
	TEST_FLAGS += -lpthread
endif

all: dvi install dist test gcov_report memory_tests_check style_check

test: ./tests/tests.cc ./controllers/maze_controllers.cc ./model/*.cc ./model/*/*.cc
	$(CXX) $(CXXFLAGS) ./tests/tests.cc ./controllers/maze_controllers.cc ./model/*.cc ./model/*/*.cc $(TEST_FLAGS)
	./test.out

# dvi:
# 	touch readme.dvi
# 	@(echo "1. В умном калькуляторе можно нажимать кнопки с клавиатуры(числа, операторы, скобки, вычисление(Enter), AC(del)), кроме функций, графиков и открытия других калькуляторов. Чтобы можно было вводить с клавиатуры, нужно ЛКМ нажать в область графика.\n2. Кредитный и Депозитный калькуляторы могут производить расчет при нажатии клавиши Enter и имеют привязку к клавишам(кнопки подписаны) кредитный -F1, депозитный - F1/F2.\n3. Чтобы установить калькулятор - make install, для удаления - make uninstall, создать архив с дистрибьютором - make dist, для удаления ненужных файлом - make clean." > readme.dvi)

dist:
	rm -rf archive_maze/
	mkdir archive_maze/
	mkdir archive_maze/src/
ifeq ($(OS), Darwin)
	cp -r ./build/Maze.app archive_maze/src/
else
	cp -r ./build/Maze archive_maze/src/
endif
	tar cvzf archive_maze.tgz archive_maze/
	rm -rf archive_maze/

install:
	cd view && qmake && make && make clean && rm Makefile && cd ../ && mkdir build
ifeq ($(OS), Darwin)
	mv view/Maze.app build
	chmod +x ./build/Maze.app
else
	mv view/Maze build
	chmod +x ./build/Maze
endif

uninstall:
	rm -rf build*

gcov_report: ./tests/tests.cc ./controllers/maze_controllers.cc ./model/*.cc ./model/*/*.cc
ifdef GCOV
ifdef LCOV
ifdef GENHTML
	$(CXX) $(CXXFLAGS) -fprofile-arcs -ftest-coverage ./tests/tests.cc ./controllers/maze_controllers.cc ./model/*.cc ./model/*/*.cc $(TEST_FLAGS) 
	./test.out
	lcov --rc lcov_branch_coverage=1 --ignore-errors mismatch -t "test" -o test.info --no-external -c -d .
	genhtml -o report test.info --ignore-errors mismatch
ifeq ($(OS), Darwin)
	open ./report/index.html
else
	xdg-open ./report/index.html
endif
endif
endif
endif

clean:
	rm -rf ./view/.qmake.stash ./view/*.user ./*/*/.DS_Store ./*/.DS_Store .DS_Store *.tgz *.out *.dSYM
	rm -rf *.out *.gcda *.gcno *.a *.info *.o report *.dSYM .DS_Store *.dvi

style_check:
ifdef CLANG_FORMAT
	clang-format -style=google -n *.cc
	clang-format -style=google -n ./*/*.cc ./*/*.h
	clang-format -style=google -n ./*/*/*.cc ./*/*/*.h
endif
ifdef CPPCHECK
	cppcheck --library=qt *.cc
	cppcheck --library=qt ./*/*.cc
	cppcheck --library=qt ./*/*/*.cc
endif

memory_tests_check:
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
ifdef VALGRIND
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test.out
endif
endif

rebuild: clean all