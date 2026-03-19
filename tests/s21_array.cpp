#ifndef ARRAY_TEST_H
#define ARRAY_TEST_H

#include <gtest/gtest.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_containersplus.h"

using namespace std;

TEST(array_tests, subtest_1) {
    S21::Array<int, 0> ar1;
    ASSERT_EQ(ar1.size(), 0);
    ASSERT_EQ(ar1.empty(), true);
    ASSERT_THROW(ar1[0], std::runtime_error);

    S21::Array<int, 10> ar2;
    for (size_t i = 0; i < ar2.size(); i++) {
        ar2[i] = i + 1;
    }
    ASSERT_EQ(ar2.size(), 10);
    ASSERT_EQ(ar2.at(0), 1);
    ASSERT_EQ(ar2.at(9), 10);
    ASSERT_THROW(ar2.at(10), std::runtime_error);
}

TEST(array_tests, subtest_2) {
    S21::Array<int, 5> ar_src = {1, 2, 3};
    S21::Array<int, 5> ar(ar_src);
    ASSERT_TRUE(ar.size() == ar_src.size());
    ASSERT_EQ(ar.back(), ar_src.back());

    S21::Array<int, 5> a_src = {1, 2, 3, 4, 5, 6, 7, 8};
    S21::Array<int, 5> a(a_src);

    ASSERT_TRUE(a.size() == a_src.size());
    ASSERT_EQ(a.front(), a_src.front());
    ASSERT_EQ(a.back(), a_src.back());

    S21::Array<int, 0> empty;
    S21::Array<int, 0> empty_copy(empty);
    ASSERT_TRUE(empty_copy.empty());
    ASSERT_TRUE(empty_copy.size() == 0);

    S21::Array<int, 1> single = {42};
    S21::Array<int, 1> single_copy(single);
    ASSERT_TRUE(single_copy.size() == 1);
    ASSERT_TRUE(single_copy.front() == 42);
    ASSERT_TRUE(single_copy.back() == 42);
}

TEST(array_tests, subtest_3) {
    S21::Array<int, 5> a1 = {1, 2, 3, 4, 5};
    S21::Array<int, 5> a2 = {6, 7, 8};
    a2.at(4) = 9;
    ASSERT_TRUE(a2.size() == 5);
    ASSERT_TRUE(a2.front() == 6);
    ASSERT_TRUE(a2.back() == 9);
    ASSERT_TRUE(!a1.empty());
    ASSERT_TRUE(!a2.empty());

    a2 = std::move(a1);
    ASSERT_TRUE(a2.size() == 5);
    ASSERT_TRUE(a2.front() == 1);
    ASSERT_TRUE(a2.back() == 5);
    ASSERT_TRUE(a1.empty());
}

TEST(array_tests, subtest_4) {
    S21::Array<int, 5> a1;
    a1.fill(100);
    ASSERT_TRUE(a1.size() == 5);
    ASSERT_TRUE(a1.front() == 100);
    ASSERT_TRUE(a1.back() == 100);
    ASSERT_TRUE(!a1.empty());
}

TEST(array_tests, subtest_5) {
    S21::Array<int, 5> a1;
    a1.fill(100);
    int sum = 0;
    for (auto it = a1.begin(); it != a1.end(); ++it) {
        sum += *it;
    }
    ASSERT_EQ(sum, 500);
}

TEST(array_tests, subtest_6) {
    S21::Array<int, 5> a1 = {1, 2, 3, 4, 5};
    S21::Array<int, 5> a2 = {6, 7, 8};
    ASSERT_TRUE(a2.size() == 5);
    ASSERT_TRUE(a2.front() == 6);
    ASSERT_TRUE(a2.at(1) == 7);
    ASSERT_TRUE(a1.size() == 5);
    ASSERT_TRUE(a1.front() == 1);
    ASSERT_TRUE(a1.at(1) == 2);
    a1.swap(a2);
    ASSERT_TRUE(a2.size() == 5);
    ASSERT_TRUE(a2.front() == 1);
    ASSERT_TRUE(a2.at(1) == 2);
    ASSERT_TRUE(a1.size() == 5);
    ASSERT_TRUE(a1.front() == 6);
    ASSERT_TRUE(a1.at(1) == 7);
}

#endif
