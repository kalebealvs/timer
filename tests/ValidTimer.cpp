#include <gtest/gtest.h>

#include "timer.hpp"

TEST(ValidTimer, Valid) {
    Timer timer;
    EXPECT_EQ(timer.isValid(), true);
    timer.stop();
    EXPECT_EQ(timer.isValid(), true);
}

TEST(ValidTimer, Invalid) {
    Timer timer;
    Timer timer2{std::move(timer)};
    EXPECT_EQ(timer.isValid(), false);
}
