// Google Test unit tests for Studentas

#include <gtest/gtest.h>
#include <sstream>
#include "studentas.h"

using std::istringstream;

TEST(StudentasTest, DefaultConstructor) {
    Studentas s;
    EXPECT_EQ(s.getEgz(), 0);
    EXPECT_TRUE(s.getTarp().empty());
    EXPECT_EQ(s.getVard(), "Nenurodyta");
    EXPECT_EQ(s.getPav(), "Nenurodyta");
}

TEST(StudentasTest, ReadFromStreamAndGalBal) {
    istringstream iss("Petras Petraitis 6 7 8 9");
    Studentas s;
    iss >> s;
    EXPECT_EQ(s.getVard(), "Petras");
    EXPECT_EQ(s.getPav(), "Petraitis");
    EXPECT_EQ(s.getEgz(), 9);
    ASSERT_EQ(s.getTarp().size(), 3u);

    // average and median should both be 8.2 for {6,7,8} with egz=9
    EXPECT_DOUBLE_EQ(s.galBalas(1), 8.2);
    EXPECT_DOUBLE_EQ(s.galBalas(2), 8.2);
}

TEST(StudentasTest, MedianEvenAndEmptyTarp) {
    // even number of interim grades: 6 7 8 9 with egz=10
    istringstream iss("Ana Anaitite 6 7 8 9 10");
    Studentas s;
    iss >> s;
    ASSERT_EQ(s.getTarp().size(), 4u);
    double expected_med = ((7.0 + 8.0) / 2.0) * 0.4 + 10.0 * 0.6; // (7.5*0.4 + 10*0.6) = 9.0
    EXPECT_DOUBLE_EQ(s.galBalas(2), expected_med);

    // empty interim grades -> final should be 0.6 * egz
    Studentas e;
    e.setEgz(5);
    EXPECT_DOUBLE_EQ(e.galBalas(1), 3.0);
}

TEST(StudentasTest, CopyAndMoveSemantics_RuleOfFive) {
    istringstream iss("Jonas Jonaitis 6 7 8 9");
    Studentas orig;
    iss >> orig;

    // Copy constructor
    Studentas copyCt(orig);
    EXPECT_EQ(copyCt.getEgz(), orig.getEgz());
    // modifying copy should not change original (deep copy)
    size_t origSize = copyCt.getTarp().size();
    copyCt.addTarp(100);
    EXPECT_NE(copyCt.getTarp().size(), orig.getTarp().size());

    // Copy assignment
    Studentas copyAsg;
    copyAsg = orig;
    EXPECT_EQ(copyAsg.getEgz(), orig.getEgz());
    copyAsg.addTarp(101);
    EXPECT_NE(copyAsg.getTarp().size(), orig.getTarp().size());

    // Move constructor
    istringstream iss2("Kestas Kestaitis 2 3 4 5");
    Studentas a;
    iss2 >> a;
    Studentas moved(std::move(a));
    EXPECT_EQ(moved.getEgz(), 5);
    // moved-from object should be left in a valid but unspecified state per implementation: egz set to 0
    EXPECT_EQ(a.getEgz(), 0);
    EXPECT_TRUE(a.getTarp().empty());

    // Move assignment
    istringstream iss3("Lina Linute 1 2 3 4");
    Studentas b;
    iss3 >> b;
    Studentas target;
    target = std::move(b);
    EXPECT_EQ(target.getEgz(), 4);
    EXPECT_EQ(b.getEgz(), 0);
    EXPECT_TRUE(b.getTarp().empty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
