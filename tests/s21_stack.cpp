#include <gtest/gtest.h>

#include "../s21_containers.h"

using namespace std;

class Stack_Test : public testing::Test {};

// test #1
TEST_F(Stack_Test, init1) {
    S21::stack<int> a;
    ASSERT_THROW(a.top(), std::runtime_error);
}

// test #2
TEST_F(Stack_Test, init2) {
    S21::stack<int> b({1, 2, 3});
    size_t size = 3;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.top(), 3);
}

TEST_F(Stack_Test, init3) {
    S21::stack<int> a({1, 2, 3});
    size_t size = 3;
    S21::stack<int> b = a;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.top(), 3);
}

TEST_F(Stack_Test, init4) {
    S21::stack<int> a({1, 2, 3});
    size_t size = 3;
    S21::stack<int> c = S21::stack<int>({1, 2, 3});
    ASSERT_EQ(c.size(), size);
    ASSERT_EQ(c.top(), 3);
}

TEST_F(Stack_Test, push) {
    S21::stack<string> a({"a", "b", "c"});
    a.push("d");
    size_t size = 4;
    ASSERT_EQ(a.size(), size);
}

TEST_F(Stack_Test, pop) {
    S21::stack<string> a({"a", "b"});
    a.pop();
    a.pop();
    a.pop();
}

TEST_F(Stack_Test, swap) {
    S21::stack<string> a({"a", "b"});
    S21::stack<string> b({"c", "d"});
    a.swap(b);
    ASSERT_EQ(a.top(), "d");
    ASSERT_EQ(b.top(), "b");
}