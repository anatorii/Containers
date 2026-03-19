CXX := gcc
CXXFLAGS := -Wall -Wextra -Werror -std=c++20
LDLIBS := -lgtest -lgtest_main -pthread
CPP_FLAGS = -lstdc++ -lm
TEST_SRCS := $(wildcard tests/*.cpp)
TEST_OBJS := $(TEST_SRCS:.cpp=.o)
TARGET := main_test.out
GCOVFLAGS := -O0 -fprofile-arcs -ftest-coverage -std=c++20
SANITIZE_FLAG = -fsanitize=address

tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDLIBS) $(CPP_FLAGS)

test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o $(TARGET) $(LDLIBS) $(CPP_FLAGS)

sanitize: clean $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(SANITIZE_FLAG) tests/main_test.cpp -o ./sanitize.out $(LDLIBS) $(CPP_FLAGS)
	./sanitize.out

valgrind: clean test
	valgrind --leak-check=yes --tool=memcheck -q ./$(TARGET)

gcov_report: clean
	$(CXX) $(GCOVFLAGS) $(TEST_SRCS) -o ./gcov_report $(LDLIBS) $(CPP_FLAGS)
	./gcov_report
	lcov --ignore-errors mismatch,unsupported,inconsistent,format --rc geninfo_unexecuted_blocks=1 -c -d . -o ./coverage.info
	lcov -r coverage.info '/usr/*' '**/tests/*' -o coverage.info
	genhtml --ignore-errors category -o ./report ./coverage.info
	xdg-open ./report/index.html

all: clean test
	./$(TARGET)

cf-check:
	@find . -type f -name "*.[ch]" -exec clang-format -i {} \;
	@find . -type f -name "*.cpp" -exec clang-format -i {} \;
	@find . -type f -name "*.hpp" -exec clang-format -i {} \;
	
clean:
	rm -f ../src/**/*.[ao] ./*.[ao] ./*.out ./*.gch
	rm -f ./gcov_report* ./coverage.info
	rm -rf report
