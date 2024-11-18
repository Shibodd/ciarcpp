#include "ciarcpp/types.hpp"
#include <gtest/gtest.h>
#include <ciarcpp/errors/ciarcpp_internal_error.hpp>
#include <ciarcpp/json_parse/parse.hpp>

using namespace ciarcpp;

TEST (JsonParseTests, ParseTimestamp) {
  constexpr std::chrono::nanoseconds t(1731763409123456789);
  constexpr const char* json_ok = "\"2024-11-16T13:23:29.123456789Z\"";
  ASSERT_EQ(json_parse::for_testing::parse_timestamp(json_ok).time_since_epoch(), t);
}

TEST (JsonParseTests, ThrowsOnBadTimestamp) {
  constexpr const char* json = "\"2024-11-16T13:23:29.123456789\"";
  ASSERT_THROW(json_parse::for_testing::parse_timestamp(json), CiarcppInternalException);
}

TEST (JsonParseTests, ParseZone) {
  constexpr const char* json = "[1,2,3,4]";
  constexpr Zone z {
    .top_left_x = 1,
    .top_left_y = 2,
    .width = 3,
    .height = 4
  };

  auto ans = json_parse::for_testing::parse_zone(json);
  ASSERT_TRUE(ans.has_value());
  ASSERT_EQ(ans.value(), z);
}

TEST (JsonParseTests, ParseUnknownZone) {
  auto ans = json_parse::for_testing::parse_zone("\"unknown\"");
  ASSERT_FALSE(ans.has_value());
}

TEST (JsonParseTests, ThrowsOnBadZone) {
  EXPECT_THROW(json_parse::for_testing::parse_zone("\"hello\""), CiarcppInternalException);
  EXPECT_THROW(json_parse::for_testing::parse_zone("[1,2,3]"), CiarcppInternalException);
  EXPECT_THROW(json_parse::for_testing::parse_zone("[1,2,3,4,5]"), CiarcppInternalException);
  EXPECT_THROW(json_parse::for_testing::parse_zone("2"), CiarcppInternalException);
}

TEST (JsonParseTests, ParseMelvinState) {
  EXPECT_EQ(json_parse::for_testing::parse_melvin_state("\"none\""), MelvinState::None);
  EXPECT_EQ(json_parse::for_testing::parse_melvin_state("\"charge\""), MelvinState::Charge);
}

TEST (JsonParseTests, ThrowsOnBadMelvinState) {
  ASSERT_THROW(json_parse::for_testing::parse_melvin_state("\"non\""), CiarcppInternalException);
}