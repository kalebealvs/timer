#include <gmock/gmock.h>

#include <chrono>
#include <thread>

#include "timer.hpp"

using namespace ::testing;
using namespace std::this_thread;
using namespace std::chrono;
TEST(TimerDuration, Elapsed1) {
    Timer t;
    sleep_for(seconds(2));
    t.stop();

    ASSERT_THAT(t.elapsedInSeconds(), Gt(2.));
    ASSERT_THAT(t.elapsedInSeconds(), Lt(2.1));
    ASSERT_THAT(t.elapsedInMilliseconds(), Gt(2000.));
    ASSERT_THAT(t.elapsedInMilliseconds(), Lt(2010.));
    ASSERT_THAT(t.elapsedInMicroseconds(), Gt(2000000.));
    ASSERT_THAT(t.elapsedInMicroseconds(), Lt(2010000.));
    ASSERT_THAT(t.elapsedInNanoseconds(), Gt(2000000000.));
    ASSERT_THAT(t.elapsedInNanoseconds(), Lt(2010000000.));
}

TEST(TimerDuration, Elapsed2) {
    Timer t;
    sleep_for(milliseconds(100));
    t.stop();

    ASSERT_THAT(t.elapsedInSeconds(), Gt(0.));
    ASSERT_THAT(t.elapsedInSeconds(), Lt(0.01));
    ASSERT_THAT(t.elapsedInMilliseconds(), Gt(100.));
    ASSERT_THAT(t.elapsedInMilliseconds(), Lt(101.));
    ASSERT_THAT(t.elapsedInMicroseconds(), Gt(100000.));
    ASSERT_THAT(t.elapsedInMicroseconds(), Lt(101000.));
    ASSERT_THAT(t.elapsedInNanoseconds(), Gt(100000000.));
    ASSERT_THAT(t.elapsedInNanoseconds(), Lt(101000000.));
}
