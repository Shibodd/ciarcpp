#include "ciarcpp/types.hpp"
#include <gtest/gtest.h>
#include <ciarcpp/json_parse/parse.hpp>

using namespace ciarcpp;

TEST (JsonParseTests, ParseTimestamp) {
  constexpr std::chrono::nanoseconds t(1731763409123456789);
  constexpr const char* json_ok = "\"2024-11-16T13:23:29.123456789Z\"";
  ASSERT_EQ(parse::for_testing::parse_timestamp(json_ok).time_since_epoch(), t);
}

TEST (JsonParseTests, ThrowsOnBadTimestamp) {
  constexpr const char* json = "\"2024-11-16T13:23:29.123456789\"";
  ASSERT_THROW(parse::for_testing::parse_timestamp(json), parse::JsonParseException);
}

TEST (JsonParseTests, ParseZone) {
  constexpr const char* json = "[1,2,3,4]";
  constexpr Zone z {
    .top_left_x = 1,
    .top_left_y = 2,
    .width = 3,
    .height = 4
  };

  auto ans = parse::for_testing::parse_zone(json);
  ASSERT_TRUE(ans.has_value());
  ASSERT_EQ(ans.value(), z);
}

TEST (JsonParseTests, ParseUnknownZone) {
  auto ans = parse::for_testing::parse_zone("\"unknown\"");
  ASSERT_FALSE(ans.has_value());
}

TEST (JsonParseTests, ThrowsOnBadZone) {
  EXPECT_THROW(parse::for_testing::parse_zone("\"hello\""), parse::JsonParseException);
  EXPECT_THROW(parse::for_testing::parse_zone("[1,2,3]"), parse::JsonParseException);
  EXPECT_THROW(parse::for_testing::parse_zone("[1,2,3,4,5]"), parse::JsonParseException);
  EXPECT_THROW(parse::for_testing::parse_zone("2"), parse::JsonParseException);
}

TEST (JsonParseTests, ParseMelvinState) {
  EXPECT_EQ(parse::for_testing::parse_melvin_state("\"none\""), MelvinState::None);
  EXPECT_EQ(parse::for_testing::parse_melvin_state("\"charge\""), MelvinState::Charge);
}

TEST (JsonParseTests, ThrowsOnBadMelvinState) {
  ASSERT_THROW(parse::for_testing::parse_melvin_state("\"non\""), parse::JsonParseException);
}