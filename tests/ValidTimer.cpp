#include <gmock/gmock.h>

#include "timer.hpp"

using namespace ::testing;

TEST(ValidTimer, Valid) {
    Timer timer;
    ASSERT_THAT(timer.isValid(), IsTrue());
    timer.stop();
    ASSERT_THAT(timer.isValid(), IsTrue());
}

TEST(ValidTimer, Invalid) {
    Timer timer;
    Timer timer2{std::move(timer)};
    ASSERT_THAT(timer.isValid(), IsFalse());
}
