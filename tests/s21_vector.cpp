#include <gtest/gtest.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_containers.h"

using namespace std;

TEST(vector_tests, subtest_1) {
    S21::Vector<int> v;
    ASSERT_TRUE(v.empty());
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 0);

    v.push_tail(10);
    ASSERT_TRUE(!v.empty());
    ASSERT_EQ(v.at(0), 10);
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(v.capacity(), 10);

    v.pop_tail();
    ASSERT_TRUE(v.empty());
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 10);

    for (size_t i = 0; i < 10; i++) {
        v.push_tail(i);
    }
    ASSERT_TRUE(!v.empty());
    ASSERT_EQ(v.at(0), 0);
    ASSERT_EQ(v.at(v.size() - 1), 9);
    ASSERT_EQ(v.size(), 10);
    ASSERT_EQ(v[v.size() - 1], 9);
}

TEST(vector_tests, subtest_2) {
    S21::Vector<int> v;

    for (size_t i = 0; i < 10; i++) {
        v.push_tail(i);
    }

    ASSERT_TRUE(!v.empty());
    ASSERT_EQ(v.at(0), 0);
    ASSERT_EQ(v.at(v.size() - 1), 9);
    ASSERT_EQ(v.size(), 10);
    ASSERT_EQ(v.back(), 9);
    ASSERT_EQ(v.front(), 0);
    ASSERT_EQ(v.capacity(), 10);

    v.erase(v.data());
    ASSERT_EQ(v.at(0), 1);
    ASSERT_EQ(v.size(), 9);
    ASSERT_EQ(v.capacity(), 10);

    v.erase(v.data() + v.size() - 1);
    ASSERT_EQ(v.at(v.size() - 1), 8);
    ASSERT_EQ(v.size(), 8);

    v.erase(v.data() + 1);
    ASSERT_EQ(v.at(0), 1);
    ASSERT_EQ(v.at(1), 3);
    ASSERT_EQ(v.size(), 7);
}

TEST(vector_tests, subtest_3) {
    S21::Vector<int> v;

    for (size_t i = 0; i < 10; i++) {
        v.push_tail(i);
    }

    v.insert(v.data(), 1000);
    ASSERT_EQ(v.at(0), 0);
    ASSERT_EQ(v.at(1), 1000);
    ASSERT_EQ(v.size(), 11);

    v.insert(v.data() + v.size() - 1, 2000);
    ASSERT_EQ(v.at(v.size() - 1), 2000);
    ASSERT_EQ(v.size(), 12);

    v.insert(v.data() + 1, 3000);
    ASSERT_EQ(v.at(0), 0);
    ASSERT_EQ(v.at(1), 1000);
    ASSERT_EQ(v.at(2), 3000);
    ASSERT_EQ(v.size(), 13);
}

TEST(vector_tests, subtest_4) {
    S21::Vector<int> v = {1, 2, 3, 4, 5};
    ASSERT_TRUE(v.capacity() == 5);
    ASSERT_TRUE(v.size() == 5);
    ASSERT_EQ(v.front(), 1);
    ASSERT_EQ(v.back(), 5);
}

TEST(vector_tests, subtest_5) {
    S21::Vector<int> v_src = {1, 2, 3, 4, 5};
    S21::Vector<int> v(v_src);

    ASSERT_TRUE(v.size() == v_src.size());
    ASSERT_EQ(v.front(), v_src.front());
    ASSERT_EQ(v.back(), v_src.back());

    v_src.push_tail(6);
    ASSERT_TRUE(v_src.size() == 6);
    ASSERT_TRUE(v.size() == 5);

    S21::Vector<int> empty;
    S21::Vector<int> empty_copy(empty);
    ASSERT_TRUE(empty_copy.empty());
    ASSERT_TRUE(empty_copy.size() == 0);

    S21::Vector<int> single = {42};
    S21::Vector<int> single_copy(single);
    ASSERT_TRUE(single_copy.size() == 1);
    ASSERT_TRUE(single_copy.front() == 42);
    ASSERT_TRUE(single_copy.back() == 42);
}

TEST(vector_tests, subtest_6) {
    S21::Vector<int> v1 = {1, 2, 3, 4, 5};
    S21::Vector<int> v2 = {6, 7, 8};
    ASSERT_TRUE(v2.size() == 3);
    ASSERT_TRUE(v2.front() == 6);
    ASSERT_TRUE(v2.back() == 8);
    ASSERT_TRUE(!v1.empty());

    v2 = std::move(v1);
    ASSERT_TRUE(v2.size() == 5);
    ASSERT_TRUE(v2.front() == 1);
    ASSERT_TRUE(v2.back() == 5);
    ASSERT_TRUE(v1.empty());
}

TEST(vector_tests, subtest_7) {
    S21::Vector<int> v = {1, 2, 3, 4, 5};
    ASSERT_TRUE(v.size() == 5);
    ASSERT_TRUE(v.front() == 1);
    ASSERT_TRUE(v.back() == 5);
    ASSERT_TRUE(!v.empty());
    ASSERT_EQ(v.capacity(), 5);

    v.reserve(20);
    ASSERT_EQ(v.capacity(), 25);
    ASSERT_EQ(v.size(), 5);

    v.reserve(0);
    ASSERT_EQ(v.capacity(), 25);
    ASSERT_EQ(v.size(), 5);

    v.shrink_to_fit();
    ASSERT_EQ(v.capacity(), 5);
    ASSERT_EQ(v.size(), 5);
    ASSERT_TRUE(v.front() == 1);
    ASSERT_TRUE(v.back() == 5);
}

TEST(vector_tests, subtest_8) {
    S21::Vector<int> v1 = {1, 2, 3, 4, 5};
    S21::Vector<int> v2 = {6, 7, 8, 9};

    ASSERT_EQ(v1.size(), 5);
    ASSERT_EQ(v1.capacity(), 5);
    ASSERT_TRUE(v1.front() == 1);
    ASSERT_TRUE(v1.back() == 5);
    ASSERT_EQ(v2.size(), 4);
    ASSERT_EQ(v2.capacity(), 4);
    ASSERT_TRUE(v2.front() == 6);
    ASSERT_TRUE(v2.back() == 9);

    v1.swap(v2);

    ASSERT_EQ(v1.size(), 4);
    ASSERT_EQ(v1.capacity(), 4);
    ASSERT_TRUE(v1.front() == 6);
    ASSERT_TRUE(v1.back() == 9);
    ASSERT_EQ(v2.size(), 5);
    ASSERT_EQ(v2.capacity(), 5);
    ASSERT_TRUE(v2.front() == 1);
    ASSERT_TRUE(v2.back() == 5);
}

TEST(vector_tests, subtest_9) {
    S21::Vector<int> v1 = {1, 2, 3, 4, 5};
    S21::Vector<int> v2 = {};

    ASSERT_EQ(v1.size(), 5);
    ASSERT_EQ(v1.capacity(), 5);
    ASSERT_TRUE(v1.front() == 1);
    ASSERT_TRUE(v1.back() == 5);

    ASSERT_EQ(v2.size(), 0);
    ASSERT_EQ(v2.capacity(), 0);
    ASSERT_TRUE(v2.empty());

    v1.swap(v2);

    ASSERT_EQ(v1.size(), 0);
    ASSERT_EQ(v1.capacity(), 0);
    ASSERT_TRUE(v1.empty());

    ASSERT_EQ(v2.size(), 5);
    ASSERT_EQ(v2.capacity(), 5);
    ASSERT_TRUE(v2.front() == 1);
    ASSERT_TRUE(v2.back() == 5);
}

TEST(vector_tests, subtest_10) {
    S21::Vector<int> v1 = {};
    S21::Vector<int> v2 = {1, 2, 3, 4, 5};

    ASSERT_EQ(v1.size(), 0);
    ASSERT_EQ(v1.capacity(), 0);
    ASSERT_TRUE(v1.empty());

    ASSERT_EQ(v2.size(), 5);
    ASSERT_EQ(v2.capacity(), 5);
    ASSERT_TRUE(v2.front() == 1);
    ASSERT_TRUE(v2.back() == 5);

    v1.swap(v2);

    ASSERT_EQ(v1.size(), 5);
    ASSERT_EQ(v1.capacity(), 5);
    ASSERT_TRUE(v1.front() == 1);
    ASSERT_TRUE(v1.back() == 5);

    ASSERT_EQ(v2.size(), 0);
    ASSERT_EQ(v2.capacity(), 0);
    ASSERT_TRUE(v2.empty());
}

TEST(vector_tests, subtest_11) {
    S21::Vector<double> v1 = {};
    S21::Vector<double> v2 = {};

    v1.swap(v2);

    ASSERT_EQ(v1.size(), 0);
    ASSERT_EQ(v1.capacity(), 0);
    ASSERT_TRUE(v1.empty());
    ASSERT_EQ(v2.size(), 0);
    ASSERT_EQ(v2.capacity(), 0);
    ASSERT_TRUE(v2.empty());
}

TEST(vector_tests, subtest_12) {
    S21::Vector<string> v1 = {"aa", "ss", "dd"};
    S21::Vector<string> v2 = {"aaa", "sss", "ddd"};

    v1.swap(v2);

    ASSERT_TRUE(v1.front() == "aaa");
    ASSERT_TRUE(v1.back() == "ddd");
}
