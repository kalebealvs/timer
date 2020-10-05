#include <gtest/gtest.h>
#include <future>
#include <thread>
#include "timer.hpp"

struct TimerId : public ::testing::Test {
    virtual void SetUp () override {
        Timer::resetIdCount ();
    }
};

TEST_F (TimerId, SameThread) {
    Timer timer;
    Timer timer2;
    {
        Timer timer3;
        EXPECT_EQ (timer3.getId (), 3);
    }

    Timer timer4;
    EXPECT_EQ (timer.getId (), 1);
    EXPECT_EQ (timer2.getId (), 2);
    EXPECT_EQ (timer4.getId (), 4);
}

TEST_F (TimerId, DifferentThread) {
    const auto threadGetTimerId = [&](const int count) {
        Timer t;
        EXPECT_EQ (t.getId (), count);
    };

    const auto createAndGetTimerID = []() { return Timer ().getId (); };
    std::future<uint64_t> timerId1 = std::async (std::launch::async, createAndGetTimerID);
    timerId1.wait ();
    std::future<uint64_t> timerId2 = std::async (std::launch::async, createAndGetTimerID);
    timerId2.wait ();

    EXPECT_EQ (timerId1.get (), 1);
    EXPECT_EQ (timerId2.get (), 2);

    std::thread thr1 (threadGetTimerId, 3);
    thr1.join ();
    std::thread thr2 (threadGetTimerId, 4);
    thr2.join ();

    Timer main;
    EXPECT_EQ (main.getId (), 5);
}