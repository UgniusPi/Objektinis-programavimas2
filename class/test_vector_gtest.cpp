#include <gtest/gtest.h>
#include <string>
#include "../my_vector/Vector.h"

using mystl::Vector;
using mystl::Item;

TEST(VectorGTest, PushBackAndSize) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorGTest, InitializerListAndAt) {
    Vector<std::string> v = {"a","b","c"};
    EXPECT_EQ(v[1], "b");
    EXPECT_EQ(v.at(2), "c");
}

TEST(VectorGTest, InsertErase) {
    Vector<int> v = {1,3,4};
    v.insert(v.begin() + 1, 2);
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v[1], 2);
    v.erase(v.begin() + 2);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[2], 4);
}

TEST(VectorGTest, ReserveCapacity) {
    Vector<int> v;
    v.reserve(16);
    EXPECT_EQ(v.capacity(), 16u);
}

TEST(VectorGTest, Resize) {
    Vector<int> v = {1,2,3,4,5};
    v.resize(3);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[2], 3);
    v.resize(6, 9);
    EXPECT_EQ(v.size(), 6u);
    EXPECT_EQ(v[3], 9);
}

TEST(VectorGTest, EmplaceBack) {
    Vector<Item> v;
    v.emplace_back(std::string("Apple"), 10);
    v.emplace_back(std::string("Banana"), 5);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0].title, "Apple");
    EXPECT_EQ(v[0].quantity, 10);
}

TEST(VectorGTest, CopyMove) {
    Vector<int> v = {1,2,3};
    Vector<int> copy = v;
    EXPECT_EQ(copy, v);
    Vector<int> moved = std::move(v);
    EXPECT_EQ(moved.size(), 3u);
}

TEST(VectorGTest, AtThrows) {
    Vector<int> v = {1,2};
    EXPECT_THROW(v.at(10), std::out_of_range);
}

TEST(VectorGTest, AssignSwap) {
    Vector<int> v;
    v.assign(4, 7);
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v[0], 7);
    Vector<int> a = {1,2,3};
    v.swap(a);
    EXPECT_EQ(v[0], 1);
}
