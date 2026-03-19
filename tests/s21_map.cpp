#include <gtest/gtest.h>

#include <cstddef>

#include "../s21_containers.h"

class Map_Test : public testing::Test {};

TEST_F(Map_Test, init1) {
    S21::map<int, int> b;
    size_t size = 0;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.begin(), b.end());
    ASSERT_THROW(b.begin()->first, std::runtime_error);
}
TEST_F(Map_Test, init2) {
    S21::map<int, int> b({{1, 1}, {2, 2}, {3, 3}});
    size_t size = 3;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.begin()->first, 1);
    ASSERT_EQ(b.begin()->second, 1);
}

TEST_F(Map_Test, init3) {
    S21::map<int, int> a({{1, 1}, {2, 2}, {3, 3}});
    S21::map<int, int> b = a;
    size_t size = 3;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.begin()->first, 1);
    ASSERT_EQ(b.begin()->second, 1);
}

TEST_F(Map_Test, forloop) {
    S21::map<int, int> a({{1, 1}, {2, 2}, {3, 3}});
    for (auto it = a.begin(); it != a.end(); ++it) {
        std::cout << it->first << it->second << std::endl;
    }
}

TEST_F(Map_Test, copy) {
    S21::map<int, int> a({{1, 1}, {2, 2}, {3, 3}});
    S21::map<int, int> b(a);
    size_t size = 3;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.begin()->first, 1);
    ASSERT_EQ(b.begin()->second, 1);
}

TEST_F(Map_Test, move) {
    S21::map<int, int> b(S21::map<int, int>({{1, 1}, {2, 2}, {3, 3}}));
    size_t size = 3;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.begin()->first, 1);
    ASSERT_EQ(b.begin()->second, 1);
}

TEST_F(Map_Test, empty) {
    S21::map<int, int> a;
    S21::map<int, int> b(S21::map<int, int>({{1, 1}, {2, 2}, {3, 3}}));
    ASSERT_TRUE(a.empty());
    ASSERT_FALSE(b.empty());
}

TEST_F(Map_Test, max_size) {
    S21::map<int, int> a;
    ASSERT_TRUE(a.max_size() > 0);
}

TEST_F(Map_Test, clear) {
    S21::map<int, int> b(S21::map<int, int>({{1, 1}, {2, 2}, {3, 3}}));
    b.clear();
    size_t size = 0;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.begin(), b.end());
}

TEST_F(Map_Test, insert) {
    S21::map<int, int> b;
    b.insert(std::pair<int, int>(1, 1));
    b.insert(2, 2);
    b.insert(1, 10);
    size_t size = 2;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.begin()->second, 1);
}
TEST_F(Map_Test, insert_or_assign) {
    S21::map<int, int> b;
    b.insert(1, 1);
    b.insert_or_assign(2, 2);
    b.insert_or_assign(1, 10);
    size_t size = 2;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.begin()->second, 10);
}

TEST_F(Map_Test, erase) {
    S21::map<int, int> b;
    auto res = b.insert(1, 1);
    b.insert(2, 2);
    b.insert(3, 3);
    b.erase(res.first);
    size_t size = 2;
    ASSERT_EQ(b.size(), size);
    ASSERT_EQ(b.begin()->second, 2);
}

TEST_F(Map_Test, swap) {
    S21::map<int, int> a({{10, 10}});
    S21::map<int, int> b(S21::map<int, int>({{1, 1}, {2, 2}, {3, 3}}));
    size_t size = 1;
    a.swap(b);
    ASSERT_EQ(b.size(), size);
    size = 3;
    ASSERT_EQ(a.size(), size);
    ASSERT_EQ(b.begin()->second, 10);
}

TEST_F(Map_Test, merge) {
    S21::map<int, int> a({{1, 10}, {10, 10}});
    S21::map<int, int> b(S21::map<int, int>({{1, 1}, {2, 2}, {3, 3}}));
    size_t size = 4;
    b.merge(a);
    ASSERT_EQ(b.size(), size);
    size = 1;
    ASSERT_EQ(a.size(), size);
    ASSERT_EQ(a.begin()->second, 10);
}
