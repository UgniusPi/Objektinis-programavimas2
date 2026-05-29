#include <gtest/gtest.h>
#include "Vector.h"
#include <string>

using mystl::Vector;
using mystl::Item;

TEST(VectorTest, PushBackAndSize) {
    Vector<int> mv;
    mv.push_back(1);
    mv.push_back(2);
    mv.push_back(3);
    EXPECT_EQ(mv.size(), 3u);
    EXPECT_EQ(mv[0], 1);
    EXPECT_EQ(mv[1], 2);
    EXPECT_EQ(mv[2], 3);
}

TEST(VectorTest, InitializerListAndAt) {
    Vector<std::string> mv = {"a","b","c"};
    EXPECT_EQ(mv.size(), 3u);
    EXPECT_EQ(mv[1], "b");
    EXPECT_EQ(mv.at(2), "c");
}

TEST(VectorTest, InsertErase) {
    Vector<int> mv = {1,3,4};
    mv.insert(mv.begin() + 1, 2);
    EXPECT_EQ(mv.size(), 4u);
    EXPECT_EQ(mv[1], 2);
    mv.erase(mv.begin() + 2);
    EXPECT_EQ(mv.size(), 3u);
}

TEST(VectorTest, ReserveCapacity) {
    Vector<int> mv;
    mv.reserve(16);
    EXPECT_GE(mv.capacity(), 16u);
}

TEST(VectorTest, ResizeAndValues) {
    Vector<int> mv = {1,2,3,4,5};
    mv.resize(3);
    EXPECT_EQ(mv.size(), 3u);
    mv.resize(6, 9);
    EXPECT_EQ(mv.size(), 6u);
    EXPECT_EQ(mv[3], 9);
}

TEST(VectorTest, EmplaceBackWithItem) {
    Vector<Item> mv;
    mv.emplace_back(std::string("Apple"), 10);
    mv.emplace_back(std::string("Banana"), 5);
    EXPECT_EQ(mv.size(), 2u);
    EXPECT_EQ(mv[0].title, "Apple");
    EXPECT_EQ(mv[0].quantity, 10);
}

TEST(VectorTest, CopyAndMove) {
    Vector<int> a = {1,2,3};
    Vector<int> b(a); // copy
    EXPECT_EQ(b.size(), 3u);
    Vector<int> c(std::move(a)); // move
    EXPECT_EQ(c.size(), 3u);
    EXPECT_EQ(a.size(), 0u);
}

TEST(VectorTest, AssignAndSwap) {
    Vector<int> a;
    a.assign(4, 7);
    EXPECT_EQ(a.size(), 4u);
    Vector<int> b = {1,2,3,4};
    a.swap(b);
    EXPECT_EQ(a[0], 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
