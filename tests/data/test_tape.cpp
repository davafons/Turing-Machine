#include "gtest/gtest.h"

#include "data/tape.hpp"

namespace turing {

class SimpleTapeTest : public ::testing::Test {
protected:
  void SetUp() override {
    tape_.alphabet().addSymbols("A B C");
    tape_.setInputString("A B Z");
  }

  Tape<1> tape_;
};

TEST_F(SimpleTapeTest, InputStringConstructor) {
  tape_ = Tape<1>("a b c");

  ASSERT_EQ(tape_.alphabet().size(), 3);
  ASSERT_EQ(tape_.size(), 3);
}

TEST_F(SimpleTapeTest, AlphabetConstructor) {
  tape_ = Tape<1>("a b c", "a b");

  ASSERT_EQ(tape_.alphabet().size(), 2);
  ASSERT_EQ(tape_.size(), 2);
}

TEST_F(SimpleTapeTest, Size) { ASSERT_EQ(tape_.size(), 2); }

TEST_F(SimpleTapeTest, Peek) { ASSERT_EQ(tape_.peek(), "A"); }

TEST_F(SimpleTapeTest, Move) {
  ASSERT_EQ(tape_.peek(), "A");

  tape_.moveRight();
  ASSERT_EQ(tape_.peek(), "B");

  tape_.moveRight();
  ASSERT_EQ(tape_.peek(), tape_.alphabet().blank());

  tape_.moveLeft();
  ASSERT_EQ(tape_.peek(), "B");

  tape_.moveLeft();
  ASSERT_EQ(tape_.peek(), "A");

  tape_.moveLeft();
  ASSERT_EQ(tape_.peek(), tape_.alphabet().blank());
}

TEST_F(SimpleTapeTest, Reset) {
  tape_.reset();

  ASSERT_EQ(tape_.size(), 0);
}

TEST_F(SimpleTapeTest, SetInputString) {
  tape_.alphabet().reset();
  tape_.alphabet().addSymbols("X Y Z");

  tape_.setInputString("XYZ");

  ASSERT_EQ(tape_.size(), 3);
}

TEST_F(SimpleTapeTest, SetBiggerInputString) {
  tape_.alphabet().reset();
  tape_.alphabet().addSymbols("X Y Z");

  // Tape should ignore the second string of characters
  tape_.setInputString("XYZ\nXYZ");

  ASSERT_EQ(tape_.size(), 3);
}

class MultipleTapeTest : public ::testing::Test {
protected:
  void SetUp() override {
    tape_.alphabet().addSymbols("A B C");
    tape_.setInputString("ABC\nCBA");
  }

  Tape<2> tape_;
};

TEST_F(MultipleTapeTest, InputStringConstructor) {
  tape_ = Tape<2>("a b c\na b c");

  ASSERT_EQ(tape_.alphabet().size(), 3);
  ASSERT_EQ(tape_.size(), 3);
}

TEST_F(MultipleTapeTest, SetInputString) {
  tape_.alphabet().reset();
  tape_.alphabet().addSymbols("X Y Z");

  tape_.setInputString("XYZ\nZYX");
  ASSERT_EQ(tape_.size(), 3);

  // Check first column
  auto column = tape_.peek();

  ASSERT_EQ(column.size(), 2);
  ASSERT_EQ(column[0], "X");
  ASSERT_EQ(column[1], "Z");

  // Check second column
  tape_.moveRight();
  column = tape_.peek();

  ASSERT_EQ(column.size(), 2);
  ASSERT_EQ(column[0], "Y");
  ASSERT_EQ(column[1], "Y");

  // Check third column
  tape_.moveRight();
  column = tape_.peek();

  ASSERT_EQ(column.size(), 2);
  ASSERT_EQ(column[0], "Z");
  ASSERT_EQ(column[1], "X");

  // Check fourth column (out of bounds)
  tape_.moveRight();
  column = tape_.peek();

  ASSERT_EQ(column.size(), 2);
  ASSERT_EQ(column[0], tape_.alphabet().blank());
  ASSERT_EQ(column[1], tape_.alphabet().blank());
}

TEST_F(MultipleTapeTest, SetInputStringMissingValues) {
  tape_.alphabet().reset();
  tape_.alphabet().addSymbols("X Y Z");

  tape_.setInputString("X---\nZYX-");
  ASSERT_EQ(tape_.size(), 3);

  // Check first column
  auto column = tape_.peek();

  ASSERT_EQ(column.size(), 2);
  ASSERT_EQ(column[0], "X");
  ASSERT_EQ(column[1], "Z");

  // Check second column
  tape_.moveRight();
  column = tape_.peek();

  ASSERT_EQ(column.size(), 2);
  ASSERT_EQ(column[0], tape_.alphabet().blank());
  ASSERT_EQ(column[1], "Y");

  // Check third column
  tape_.moveRight();
  column = tape_.peek();

  ASSERT_EQ(column.size(), 2);
  ASSERT_EQ(column[0], tape_.alphabet().blank());
  ASSERT_EQ(column[1], "X");

  // Check fourth column (out of bounds)
  tape_.moveRight();
  column = tape_.peek();

  ASSERT_EQ(column.size(), 2);
  ASSERT_EQ(column[0], tape_.alphabet().blank());
  ASSERT_EQ(column[1], tape_.alphabet().blank());
}

} // namespace turing
