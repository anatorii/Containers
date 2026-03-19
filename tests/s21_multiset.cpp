#include <gtest/gtest.h>

#include <cstddef>

#include "../s21_containers.h"

class Multiset_Test : public testing::Test {};

TEST_F(Multiset_Test, init1) {
    S21::multiset<int> b;
    size_t size = 0;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.begin(), b.end());
    ASSERT_THROW(*b.begin(), std::runtime_error);
}

TEST_F(Multiset_Test, init2) {
    S21::multiset<int> b({1, 2, 3, 3, 2, 1});
    size_t size = 6;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(*b.begin(), 1);
}

TEST_F(Multiset_Test, init3) {
    S21::multiset<int> a({1, 2, 3, 3, 2, 1});
    S21::multiset<int> b = a;
    size_t size = 6;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(*b.begin(), 1);
}

TEST_F(Multiset_Test, forloop) {
    S21::multiset<int> a({1, 2, 3, 3, 2, 1});
    int sum = 0;
    for (auto it = a.begin(); it != a.end(); ++it) {
        sum += *it;
    }
    ASSERT_EQ(sum, 12);  // 1+1+2+2+3+3 = 12
}

TEST_F(Multiset_Test, copy) {
    S21::multiset<int> a({1, 2, 3, 3, 2, 1});
    S21::multiset<int> b(a);
    size_t size = 6;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(*b.begin(), 1);
}

TEST_F(Multiset_Test, move) {
    S21::multiset<int> b(S21::multiset<int>({1, 2, 3, 3, 2, 1}));
    size_t size = 6;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(*b.begin(), 1);
}

TEST_F(Multiset_Test, empty) {
    S21::multiset<int> a;
    S21::multiset<int> b({1, 2, 3});
    ASSERT_TRUE(a.empty());
    ASSERT_FALSE(b.empty());
}

TEST_F(Multiset_Test, max_size) {
    S21::multiset<int> a;
    ASSERT_TRUE(a.max_size() > 0);
}

TEST_F(Multiset_Test, clear) {
    S21::multiset<int> b({1, 2, 3, 3, 2, 1});
    b.clear();
    size_t size = 0;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.begin(), b.end());
}

TEST_F(Multiset_Test, insert) {
    S21::multiset<int> b;
    b.insert(1);
    b.insert(2);
    b.insert(1);  // Дубликат
    b.insert(3);
    size_t size = 4;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(*b.begin(), 1);

    // Проверяем количество дубликатов
    int count_1 = 0;
    for (auto it = b.begin(); it != b.end(); ++it) {
        if (*it == 1) count_1++;
    }
    ASSERT_EQ(count_1, 2);
}

TEST_F(Multiset_Test, erase) {
    S21::multiset<int> b;
    auto res = b.insert(1);
    b.insert(2);
    b.insert(3);
    b.insert(1);  // Второй дубликат 1
    b.erase(res);
    size_t size = 3;
    ASSERT_EQ(b.size(), size);
    // Проверяем, что один элемент 1 остался
    int count_1 = 0;
    for (auto it = b.begin(); it != b.end(); ++it) {
        if (*it == 1) count_1++;
    }
    ASSERT_EQ(count_1, 1);
}

TEST_F(Multiset_Test, swap) {
    S21::multiset<int> a({10, 10, 10});
    S21::multiset<int> b({1, 2, 3, 3, 2, 1});
    size_t size = 3;
    a.swap(b);
    ASSERT_EQ(b.size(), size);
    size = 6;
    ASSERT_EQ(a.size(), size);
    ASSERT_EQ(*b.begin(), 10);

    // Проверяем количество дубликатов в b
    int count_10 = 0;
    for (auto it = b.begin(); it != b.end(); ++it) {
        if (*it == 10) count_10++;
    }
    ASSERT_EQ(count_10, 3);
}

TEST_F(Multiset_Test, merge) {
    S21::multiset<int> a({1, 10, 10});
    S21::multiset<int> b({1, 2, 3, 3, 2, 1});
    size_t size = 9;  // 3 + 6
    b.merge(a);
    ASSERT_EQ(b.size(), size);
    size = 0;
    ASSERT_EQ(a.size(), size);

    // Проверяем количество элементов после merge
    int count_1 = 0, count_10 = 0;
    for (auto it = b.begin(); it != b.end(); ++it) {
        if (*it == 1) count_1++;
        if (*it == 10) count_10++;
    }
    ASSERT_EQ(count_1, 3);   // 2 из b + 1 из a
    ASSERT_EQ(count_10, 2);  // 2 из a
}

TEST_F(Multiset_Test, count) {
    S21::multiset<int> b({1, 2, 3, 3, 2, 1, 1});
    ASSERT_EQ(b.count(1), 3);
    ASSERT_EQ(b.count(2), 2);
    ASSERT_EQ(b.count(3), 2);
    ASSERT_EQ(b.count(4), 0);
}

TEST_F(Multiset_Test, find) {
    S21::multiset<int> b({1, 2, 3, 3, 2, 1});
    auto it1 = b.find(1);
    auto it3 = b.find(3);
    auto it4 = b.find(4);

    ASSERT_NE(it1, b.end());
    ASSERT_EQ(*it1, 1);

    ASSERT_NE(it3, b.end());
    ASSERT_EQ(*it3, 3);

    ASSERT_EQ(it4, b.end());
}

TEST_F(Multiset_Test, contains) {
    S21::multiset<int> b({1, 2, 3, 3, 2, 1});
    ASSERT_TRUE(b.contains(1));
    ASSERT_TRUE(b.contains(2));
    ASSERT_TRUE(b.contains(3));
    ASSERT_FALSE(b.contains(4));
}

TEST_F(Multiset_Test, equal_range) {
    S21::multiset<int> b({1, 2, 3, 3, 3, 4});
    auto range = b.equal_range(3);

    int count = 0;
    for (auto it = range.first; it != range.second; ++it) {
        ASSERT_EQ(*it, 3);
        count++;
    }
    std::cout << count << std::endl;
    ASSERT_EQ(count, 3);

    auto range_nonexistent = b.equal_range(5);
    ASSERT_EQ(range_nonexistent.first, range_nonexistent.second);
}

TEST_F(Multiset_Test, lower_upper_bound) {
    S21::multiset<int> b({1, 2, 3, 3, 3, 4});

    auto lower = b.lower_bound(3);
    auto upper = b.upper_bound(3);

    ASSERT_EQ(*lower, 3);
    ASSERT_EQ(*upper, 4);

    int count = 0;
    for (auto it = lower; it != upper; ++it) {
        ASSERT_EQ(*it, 3);
        count++;
    }
    ASSERT_EQ(count, 3);
}