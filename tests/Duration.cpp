#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include "timer.hpp"

using namespace std::this_thread;
using namespace std::chrono;
TEST(TimerDuration, Elapsed1) {
    Timer t;
    sleep_for(seconds(2));
    t.stop();

    EXPECT_GE(t.elapsedInSeconds(), 2.);
    EXPECT_LT(t.elapsedInSeconds(), 2.1);
    EXPECT_GE(t.elapsedInMilliseconds(), 2000.);
    EXPECT_LT(t.elapsedInMilliseconds(), 2010.);
    EXPECT_GE(t.elapsedInMicroseconds(), 2000000.);
    EXPECT_LT(t.elapsedInMicroseconds(), 2010000.);
    EXPECT_GE(t.elapsedInNanoseconds(), 2000000000.);
    EXPECT_LT(t.elapsedInNanoseconds(), 2010000000.);
}

TEST(TimerDuration, Elapsed2) {
    Timer t;
    sleep_for(milliseconds(100));
    t.stop();

    EXPECT_GE(t.elapsedInSeconds(), 0.);
    EXPECT_LT(t.elapsedInSeconds(), 0.01);
    EXPECT_GE(t.elapsedInMilliseconds(), 100.);
    EXPECT_LT(t.elapsedInMilliseconds(), 101.);
    EXPECT_GE(t.elapsedInMicroseconds(), 100000.);
    EXPECT_LT(t.elapsedInMicroseconds(), 101000.);
    EXPECT_GE(t.elapsedInNanoseconds(), 100000000.);
    EXPECT_LT(t.elapsedInNanoseconds(), 101000000.);
}
