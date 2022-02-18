#include <gmock/gmock.h>

#include <future>
#include <thread>

#include "timer.hpp"

using namespace ::testing;

struct TimerId : public ::testing::Test {
#ifdef DEBUG
    virtual void SetUp() override { Timer::resetIdCount(); }
#else
    virtual void SetUp() override { }
#endif
};

TEST_F(TimerId, SameThread) {
    Timer timer;
    Timer timer2;
    {
        Timer timer3;
        ASSERT_THAT(timer3.getId(), Eq(3));
    }

    Timer timer4;
    ASSERT_THAT(timer.getId(), Eq(1));
    ASSERT_THAT(timer2.getId(), Eq(2));
    ASSERT_THAT(timer4.getId(), Eq(4));
}

TEST_F(TimerId, DifferentThread) {
    const auto threadGetTimerId = [&](const int count) {
        Timer t;
        ASSERT_THAT(t.getId(), Eq(count));
    };

    const auto createAndGetTimerID = []() { return Timer().getId(); };
    std::future<uint64_t> timerId1 = std::async(std::launch::async, createAndGetTimerID);
    timerId1.wait();
    std::future<uint64_t> timerId2 = std::async(std::launch::async, createAndGetTimerID);
    timerId2.wait();

    ASSERT_THAT(timerId1.get(), Eq(1));
    ASSERT_THAT(timerId2.get(), Eq(2));

    std::thread thr1(threadGetTimerId, 3);
    thr1.join();
    std::thread thr2(threadGetTimerId, 4);
    thr2.join();

    Timer main;
    ASSERT_THAT(main.getId(), Eq(5));
}
