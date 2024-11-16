#include <gtest/gtest.h>
#include <ciarcpp/json_parse/parse.hpp>

TEST(HelloTest, BasicAssertions) {
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7*6,42);
}