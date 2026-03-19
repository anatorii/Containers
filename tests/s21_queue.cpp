#include <gtest/gtest.h>

#include "../s21_containers.h"

class Queue_Test : public testing::Test {};

// test #1
TEST_F(Queue_Test, init1) {
    S21::queue<int> a;
    ASSERT_THROW(a.front(), std::runtime_error);
}

// test #2
TEST_F(Queue_Test, init2) {
    S21::queue<int> b({1, 2, 3});
    size_t size = 3;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.front(), 1);
    ASSERT_EQ(b.back(), 3);
}

TEST_F(Queue_Test, init3) {
    S21::queue<int> a({1, 2, 3});
    size_t size = 3;
    S21::queue<int> b = a;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.front(), 1);
    ASSERT_EQ(b.back(), 3);
}

TEST_F(Queue_Test, init4) {
    S21::queue<int> a({1, 2, 3});
    size_t size = 3;
    S21::queue<int> c = S21::queue<int>({1, 2, 3});
    ASSERT_EQ(c.size(), size);
    ASSERT_EQ(c.front(), 1);
    ASSERT_EQ(c.back(), 3);
}

TEST_F(Queue_Test, push) {
    S21::queue<char> a({'a', 'b', 'c'});
    a.push('d');
    size_t size = 4;
    ASSERT_EQ(a.size(), size);
}

TEST_F(Queue_Test, pop) {
    S21::queue<char> a({'a', 'b'});
    a.pop();
    a.pop();
    a.pop();
}

TEST_F(Queue_Test, swap) {
    S21::queue<char> a({'a', 'b'});
    S21::queue<char> b({'c', 'd'});
    a.swap(b);
    ASSERT_EQ(a.front(), 'c');
    ASSERT_EQ(b.front(), 'a');
}
