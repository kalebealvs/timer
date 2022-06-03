#include <gmock/gmock.h>

#include <chrono>
#include <thread>

#include "timer.hpp"

using namespace ::testing;
using namespace std::this_thread;
using namespace std::chrono;

using Clock = high_resolution_clock;
using Time = Clock::time_point;
using sc = seconds;
using ms = milliseconds;
using mc = microseconds;
using ns = nanoseconds;

TEST(TimerDuration, Elapsed) {
    Timer t;
    sleep_for(milliseconds(2001));
    t.stop();

    ASSERT_THAT(t.elapsedInSeconds(), Gt(1.9));
    ASSERT_THAT(t.elapsedInSeconds(), Lt(2.1));
    ASSERT_THAT(t.elapsedInMilliseconds(), Gt(2000.));
    ASSERT_THAT(t.elapsedInMilliseconds(), Lt(2010.));
    ASSERT_THAT(t.elapsedInMicroseconds(), Gt(2000000.));
    ASSERT_THAT(t.elapsedInMicroseconds(), Lt(2010000.));
    ASSERT_THAT(t.elapsedInNanoseconds(), Gt(2000000000.));
    ASSERT_THAT(t.elapsedInNanoseconds(), Lt(2010000000.));
}

TEST(TimerDuration, ShowsCurrentDurationWhileRunning) {
    Timer t;
    const auto time = 200;
    std::this_thread::sleep_for(milliseconds(time));
    ASSERT_THAT(t.elapsedInMilliseconds(), Gt(time));
}
