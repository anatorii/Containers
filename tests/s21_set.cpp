#include <gtest/gtest.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_containers.h"

using namespace std;

// def constructor
TEST(set_tests, subtest_0) {
    S21::Set<double> set;
    ASSERT_TRUE(set.size() == 0);
    ASSERT_TRUE(set.empty());
}

// copy constructor
TEST(set_tests, subtest_1) {
    S21::Set<double> set = {5.2, 5.1, 5.3, 5.7, 5.4, 5.6};
    S21::Set<double> set_copy(set);
    ASSERT_TRUE(set_copy.size() == set.size());
    ASSERT_TRUE(set_copy.contains(5.1));

    S21::Set<double> set2 = {};
    S21::Set<double> set2_copy(set2);
    ASSERT_TRUE(set2_copy.size() == set2.size());
    ASSERT_TRUE(!set2_copy.contains(5.1));

    S21::Set<int> set3 = {2, 1, 3, 7, 4, 6};
    S21::Set<int> set3_copy = set3;
    ASSERT_TRUE(set3_copy.size() == set3.size());
    ASSERT_TRUE(set3_copy.contains(1));
}

// move constructor
TEST(set_tests, subtest_2) {
    S21::Set<double> set1 = {5.2, 5.1, 5.3, 5.7, 5.4, 5.6};
    S21::Set<double> set2 = {6, 7, 8};
    ASSERT_TRUE(set2.size() == 3);
    ASSERT_TRUE(set1.size() == 6);
    ASSERT_TRUE(set2.contains(7));
    ASSERT_TRUE(set1.contains(5.7));

    set2 = std::move(set1);
    ASSERT_TRUE(set2.size() == 6);
    ASSERT_TRUE(set1.size() == 0);
    ASSERT_TRUE(set2.contains(5.1));
    ASSERT_TRUE(!set1.contains(5.1));
}

// swap
TEST(set_tests, subtest_3) {
    S21::Set<double> set1 = {5.2, 5.1, 5.3, 5.7, 5.4, 5.6};
    S21::Set<double> set2 = {11, 12, 13, 14, 15};
    ASSERT_EQ(set1.size(), 6);
    ASSERT_EQ(set2.size(), 5);
    ASSERT_TRUE(set1.contains(5.7));
    ASSERT_TRUE(set2.contains(13));
    set1.swap(set2);
    ASSERT_EQ(set1.size(), 5);
    ASSERT_EQ(set2.size(), 6);
    ASSERT_TRUE(set1.contains(13));
    ASSERT_TRUE(set2.contains(5.7));
}

// erase
TEST(set_tests, subtest_4) {
    S21::Set<double> set1 = {11, 12, 13, 14, 15, 1};
    ASSERT_EQ(set1.size(), 6);
    ASSERT_TRUE(set1.contains(1));
    set1.erase(set1.begin());
    ASSERT_EQ(set1.size(), 5);
    ASSERT_TRUE(!set1.contains(1));
    ASSERT_TRUE(set1.contains(15));

    auto b = set1.begin();
    b++;
    b++;
    b++;
    b++;
    set1.erase(b);
    ASSERT_EQ(set1.size(), 4);
    ASSERT_TRUE(!set1.contains(15));

    S21::Set<double> set2 = {};
    ASSERT_EQ(set2.size(), 0);
    set2.erase(set2.begin());
    ASSERT_EQ(set2.size(), 0);
}

// merge
TEST(set_tests, subtest_5) {
    S21::Set<double> set1 = {11, 12, 13, 14, 15};
    S21::Set<double> set2 = {1, 2, 3, 4, 5};
    ASSERT_EQ(set1.size(), 5);
    ASSERT_TRUE(!set1.contains(1));
    set1.merge(set2);
    ASSERT_EQ(set1.size(), 10);
    ASSERT_TRUE(set1.contains(1));

    S21::Set<double> set3 = {11, 12, 13, 1, 2, 3, 4, 5};
    S21::Set<double> set4 = {3, 4, 11, 12, 13, 14, 15};
    ASSERT_EQ(set3.size(), 8);
    ASSERT_TRUE(!set3.contains(14));
    set3.merge(set4);
    ASSERT_EQ(set3.size(), 10);
    ASSERT_TRUE(set3.contains(14));

    S21::Set<double> set5 = {11, 12, 13, 1, 2, 3, 4, 5};
    S21::Set<double> set6 = {};
    ASSERT_EQ(set5.size(), 8);
    ASSERT_TRUE(set5.contains(11));
    set5.merge(set6);
    ASSERT_EQ(set5.size(), 8);
    ASSERT_TRUE(set5.contains(11));

    S21::Set<double> set7 = {};
    S21::Set<double> set8 = {17, 12, 13, 1, 2, 3, 4, 5};
    ASSERT_EQ(set7.size(), 0);
    ASSERT_EQ(set8.size(), 8);

    auto it7 = set7.find(1);
    auto it8 = set8.find(1);
    ASSERT_TRUE(it7 == nullptr);
    ASSERT_TRUE(it8 != nullptr);
    ASSERT_TRUE(!set7.contains(1));
    ASSERT_TRUE(set8.contains(1));

    set7.merge(set8);
    it7 = set7.find(1);
    ASSERT_TRUE(it7 != nullptr);
    ASSERT_TRUE(set7.contains(1));
    ASSERT_EQ(set7.size(), set8.size());

    S21::Set<double> set9 = {};
    S21::Set<double> set10 = {};
    ASSERT_EQ(set9.size(), 0);
    ASSERT_EQ(set10.size(), 0);

    set9.merge(set10);
    ASSERT_EQ(set9.size(), 0);
    ASSERT_EQ(set10.size(), 0);
    ASSERT_TRUE(!set9.contains(1));
    ASSERT_TRUE(!set10.contains(1));
}

// iterator
TEST(set_tests, subtest_6) {
    S21::Set<short> set1 = {11, 12, 13, 14, 15};

    auto it1 = set1.begin();
    it1++;
    it1++;
    it1++;
    it1++;
    ASSERT_EQ(*it1, 15);
    it1--;
    it1--;
    it1--;
    it1--;
    ASSERT_EQ(*it1, 11);
}

// insert
TEST(set_tests, subtest_7) {
    S21::Set<short> set1;
    ASSERT_TRUE(set1.size() == 0);
    ASSERT_TRUE(set1.empty());
    set1.insert(23);
    ASSERT_TRUE(set1.size() == 1);
    ASSERT_TRUE(!set1.empty());

    auto [it1, inserted1] = set1.insert(55);
    ASSERT_TRUE(set1.size() == 2);
    ASSERT_TRUE(!set1.empty());
    it1--;
    ASSERT_EQ(*it1, 23);

    ASSERT_THROW(set1.insert(55), std::runtime_error);
    ASSERT_NO_THROW(set1.insert(56));
}
