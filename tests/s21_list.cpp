#include <gtest/gtest.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_containers.h"

using namespace std;

TEST(list_tests, subtest_1) {
    S21::List<double> dlist;
    dlist.push_back(7);
    dlist.push_back(8);
    dlist.push_back(9);
    dlist.push_front(1);
    dlist.push_front(2);
    dlist.push_front(3);
    ASSERT_TRUE(dlist.size() == 6);
    ASSERT_TRUE(dlist.front() == 9);
    ASSERT_TRUE(dlist.back() == 3);

    dlist.pop_front();
    dlist.pop_front();
    dlist.pop_front();
    dlist.pop_back();
    dlist.pop_back();
    dlist.pop_back();
    ASSERT_TRUE(dlist.size() == 0);
    ASSERT_TRUE(dlist.empty());

    dlist.push_back(1000);
    dlist.push_back(2000);
    dlist.push_back(3000);
    dlist.push_back(4000);
    dlist.push_back(5000);
    auto it = dlist.begin();
    it++;
    it++;
    it = dlist.insert(it, 10);
    it++;
    it++;
    it = dlist.insert(it, 100);
    it = dlist.insert(it, 200);
    it = dlist.insert(it, 300);
    ASSERT_TRUE(dlist.size() == 9);
    ASSERT_TRUE(dlist.front() == 300);
    ASSERT_TRUE(dlist.back() == 1000);

    dlist.erase(dlist.begin());
    dlist.erase(dlist.begin());
    dlist.erase(dlist.begin());
    auto it2 = dlist.begin();
    it2++;
    it2++;
    it2++;
    dlist.erase(it2);
    ASSERT_TRUE(dlist.size() == 5);
    ASSERT_TRUE(dlist.front() == 300);
    ASSERT_TRUE(dlist.back() == 10);
}

TEST(list_tests, subtest_2) {
    S21::List<int> ilist = {1, 2, 3, 4, 5};
    ASSERT_TRUE(ilist.size() == 5);
    ASSERT_TRUE(ilist.front() == 5);
    ASSERT_TRUE(ilist.back() == 1);

    S21::List<string> slist = {"aaa", "bbb", "ccc", "ddd", "eee", "fff"};
    ASSERT_TRUE(slist.size() == 6);
    ASSERT_TRUE(slist.front() == "fff");
    ASSERT_TRUE(slist.back() == "aaa");
}

TEST(list_tests, subtest_3) {
    S21::List<int> ilist_src = {1, 2, 3, 4, 5};
    S21::List<int> ilist(ilist_src);

    ASSERT_TRUE(ilist.size() == ilist_src.size());
    ASSERT_EQ(ilist.front(), ilist_src.front());
    ASSERT_EQ(ilist.back(), ilist_src.back());

    ilist_src.push_back(6);
    ASSERT_TRUE(ilist_src.size() == 6);
    ASSERT_TRUE(ilist.size() == 5);

    S21::List<int> empty;
    S21::List<int> empty_copy(empty);
    ASSERT_TRUE(empty_copy.empty());
    ASSERT_TRUE(empty_copy.size() == 0);

    S21::List<int> single = {42};
    S21::List<int> single_copy(single);
    ASSERT_TRUE(single_copy.size() == 1);
    ASSERT_TRUE(single_copy.front() == 42);
    ASSERT_TRUE(single_copy.back() == 42);
}

TEST(list_tests, subtest_4) {
    S21::List<int> list1 = {1, 2, 3, 4, 5};
    S21::List<int> list2 = {6, 7, 8};
    ASSERT_TRUE(list2.size() == 3);
    ASSERT_TRUE(list2.front() == 8);
    ASSERT_TRUE(list2.back() == 6);
    ASSERT_TRUE(!list1.empty());

    list2 = std::move(list1);
    ASSERT_TRUE(list2.size() == 5);
    ASSERT_TRUE(list2.front() == 5);
    ASSERT_TRUE(list2.back() == 1);
    ASSERT_TRUE(list1.empty());
}

// swap
TEST(list_tests, subtest_5) {
    S21::List<int> list1 = {1, 2, 3, 4, 5};
    S21::List<int> list2 = {6, 7, 8};
    ASSERT_TRUE(list1.size() == 5);
    ASSERT_TRUE(list1.front() == 5);
    ASSERT_TRUE(list1.back() == 1);
    ASSERT_TRUE(list2.size() == 3);
    ASSERT_TRUE(list2.front() == 8);
    ASSERT_TRUE(list2.back() == 6);

    list1.swap(list2);
    ASSERT_TRUE(list1.size() == 3);
    ASSERT_TRUE(list1.front() == 8);
    ASSERT_TRUE(list1.back() == 6);
    ASSERT_TRUE(list2.size() == 5);
    ASSERT_TRUE(list2.front() == 5);
    ASSERT_TRUE(list2.back() == 1);
}

// merge
TEST(list_tests, subtest_6) {
    S21::List<double> list1 = {1, 2, 3, 4, 5};
    S21::List<double> list2 = {8, 7, 6};
    ASSERT_TRUE(list1.size() == 5);
    ASSERT_TRUE(list1.front() == 5);
    ASSERT_TRUE(list1.back() == 1);

    list1.merge(list2);
    ASSERT_TRUE(list1.size() == 8);
    ASSERT_TRUE(list1.front() == 6);
    ASSERT_TRUE(list1.back() == 1);
    ASSERT_TRUE(list2.empty());

    S21::List<double> list3 = {1, 2, 3, 4, 5};
    S21::List<double> list4 = {};
    list3.merge(list4);
    ASSERT_TRUE(list3.size() == 5);
    ASSERT_TRUE(list3.front() == 5);
    ASSERT_TRUE(list3.back() == 1);
    ASSERT_TRUE(list4.empty());

    S21::List<double> list5 = {};
    S21::List<double> list6 = {7, 8, 9, 0};
    list5.merge(list6);
    ASSERT_TRUE(list5.size() == 4);
    ASSERT_TRUE(list5.front() == 0);
    ASSERT_TRUE(list5.back() == 7);
    ASSERT_TRUE(list6.empty());
}

// unique
TEST(list_tests, subtest_7) {
    S21::List<double> list;
    ASSERT_EQ(list.size(), 0);
    list.unique();
    ASSERT_EQ(list.size(), 0);

    S21::List<double> list1 = {1.1, 1.2, 1.2, 2, 2, 3, 4, 5};
    ASSERT_EQ(list1.size(), 8);
    list1.unique();
    ASSERT_EQ(list1.size(), 6);

    S21::List<double> list2 = {1.1};
    ASSERT_EQ(list2.size(), 1);
    list2.unique();
    ASSERT_EQ(list2.size(), 1);

    S21::List<double> list3 = {3, 3, 3, 3, 4, 4, 4, 4, 4, 5,
                               5, 5, 5, 6, 6, 6, 2, 2, 2, 0};
    ASSERT_EQ(list3.size(), 20);
    list3.unique();
    ASSERT_EQ(list3.size(), 6);
}

// reverse
TEST(list_tests, subtest_8) {
    S21::List<double> list1 = {1, 2, 3, 4, 5};
    ASSERT_TRUE(list1.size() == 5);
    ASSERT_TRUE(list1.front() == 5);
    ASSERT_TRUE(list1.back() == 1);

    list1.reverse();
    ASSERT_TRUE(list1.size() == 5);
    ASSERT_TRUE(list1.front() == 1);
    ASSERT_TRUE(list1.back() == 5);

    S21::List<double> list2;
    ASSERT_EQ(list2.size(), 0);
    list2.reverse();
    ASSERT_EQ(list2.size(), 0);
}

// splice
TEST(list_tests, subtest_9) {
    S21::List<int> l1 = {1, 5, 8};
    S21::List<int> l2 = {4, 6};
    ASSERT_EQ(l1.size(), 3);
    ASSERT_EQ(l1.back(), 1);
    l1.splice(l1.begin(), l2);
    ASSERT_EQ(l1.size(), 5);
    ASSERT_EQ(l1.back(), 4);

    S21::List<int> l3 = {1, 5, 8};
    S21::List<int> l4 = {4, 6};
    auto it = l3.begin();
    it++;
    l3.splice(it, l4);
    ASSERT_EQ(l3.size(), 5);
    ASSERT_EQ(l3.back(), 1);

    S21::List<int> l5 = {1, 5, 8};
    S21::List<int> l6 = {};
    l5.splice(l5.begin(), l6);
    ASSERT_EQ(l5.size(), 3);
    ASSERT_EQ(l5.back(), 1);

    S21::List<int> l7 = {};
    S21::List<int> l8 = {11, 22, 33, 44, 88};
    l7.splice(l7.begin(), l8);
    ASSERT_EQ(l7.size(), 0);
    ASSERT_EQ(l8.size(), 5);
    ASSERT_EQ(l8.back(), 11);
}

// sort
TEST(list_tests, subtest_10) {
    S21::List<int> l1 = {2, 1, 5, 4, 3, 2, 4, 5, 7, 7, 3, 9};
    ASSERT_EQ(l1.size(), 12);
    ASSERT_TRUE(l1.front() == 9);
    ASSERT_TRUE(l1.back() == 2);
    l1.sort();
    ASSERT_EQ(l1.size(), 12);
    ASSERT_TRUE(l1.front() == 9);
    ASSERT_TRUE(l1.back() == 1);

    S21::List<int> l2 = {77, 66, 88, 33, 11, 22};
    ASSERT_EQ(l2.size(), 6);
    ASSERT_TRUE(l2.front() == 22);
    ASSERT_TRUE(l2.back() == 77);
    l2.sort();
    ASSERT_EQ(l2.size(), 6);
    ASSERT_TRUE(l2.front() == 88);
    ASSERT_TRUE(l2.back() == 11);

    S21::List<int> l3 = {77};
    ASSERT_EQ(l3.size(), 1);
    ASSERT_TRUE(l3.front() == 77);
    ASSERT_TRUE(l3.back() == 77);
    l3.sort();
    ASSERT_EQ(l3.size(), 1);
    ASSERT_TRUE(l3.front() == 77);
    ASSERT_TRUE(l3.back() == 77);

    S21::List<int> l4 = {};
    ASSERT_EQ(l4.size(), 0);
    l4.sort();
    ASSERT_EQ(l4.size(), 0);
}

class ape {
   private:
    int id;
    int age;

   public:
    ape() : id(0), age(0) {}
    ape(int id, int age) : id(id), age(age) {}
    ~ape() {}

    int getID() const { return id; }
    int getAge() const { return age; }

    auto operator<=>(const ape& other) const { return id <=> other.id; }

    bool operator==(const ape& other) const { return id == other.id; }
};

TEST(list_tests, subtest_11) {
    S21::List<ape> l;
    l.push_front(ape(5, 10));
    l.push_front(ape(1, 11));
    l.push_front(ape(2, 9));

    l.sort();
}