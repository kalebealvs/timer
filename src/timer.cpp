#include "timer.hpp"
#include "definitions.hpp"

#include <iostream>
#include <ratio>

using namespace std;
using namespace chrono;

static constexpr int64_t InvalidTime = TimePoint<ms>(ms(0)).time_since_epoch().count();

template <typename unit>
static auto timeFromEpoch(const int64_t epoch) -> Time {
    return Time{unit(epoch)};
}

template <typename unit>
static constexpr auto getRatio() {
    return duration_cast<unit>(sc(1)).count();
}

static auto now() {
    return Clock::now().time_since_epoch().count();
}

Timer::Timer() : _start_time{now()}, _end_time{InvalidTime}, _stopped{false} {
    auto&& id_ref = makeAtomic(_id_count);
    _id = ++id_ref;
}

Timer::Timer(Timer&& oldTimer) noexcept
    : _start_time{makeAtomic(oldTimer._start_time)}, _end_time{makeAtomic(
                                                         oldTimer._end_time)},
      _stopped{makeAtomic(oldTimer._stopped)}, _id{makeAtomic(oldTimer._id)} {
    oldTimer.invalidate();
}

auto Timer::operator=(Timer&& oldTimer) noexcept -> Timer& {
    _start_time = makeAtomic(oldTimer._start_time);
    _end_time = makeAtomic(oldTimer._end_time);
    _stopped = makeAtomic(oldTimer._stopped);
    _id = makeAtomic(oldTimer._id);
    oldTimer.invalidate();
    return *this;
}

Timer::~Timer() = default;

auto Timer::stop() -> void {
    auto&& stop_ref = makeAtomic(_stopped);
    if(stop_ref)
        return;

    auto&& end_ref = makeAtomic(_end_time);
    end_ref = now();
    stop_ref = true;
}

auto Timer::elapsedInSeconds() const -> double {
    return elapsedTime<sc>();
}

auto Timer::elapsedInMilliseconds() const -> double {
    return elapsedTime<ms>();
}

auto Timer::elapsedInMicroseconds() const -> double {
    return elapsedTime<mc>();
}

auto Timer::elapsedInNanoseconds() const -> double {
    return elapsedTime<ns>();
}

template <typename unit>
auto Timer::elapsedTime() const -> double {
    auto&& start_ref = makeAtomic(_start_time);
    auto&& end_ref = makeAtomic(_stopped) ? makeAtomic(_end_time) : now();
    return duration<double, std::ratio<1, getRatio<unit>()>>(
               timeFromEpoch<ns>(end_ref) - timeFromEpoch<ns>(start_ref))
        .count();
}

auto Timer::invalidate() -> void {
    auto&& stop_ref = makeAtomic(_stopped);
    stop_ref = true;
    auto&& start_ref = makeAtomic(_start_time);
    auto&& end_ref = makeAtomic(_end_time);
    start_ref = end_ref = InvalidTime;
    auto&& id_ref = makeAtomic(_id);
    id_ref = UINT64_MAX;
}

auto Timer::printDuration() const -> void {
    std::cout << "Timer " << _id << ": " << elapsedTime<mc>() << " μs \n";
}

auto Timer::getId() const -> uint64_t {
    return static_cast<uint64_t>(_id);
}

auto Timer::isValid() const -> bool {
    return makeAtomic(_id) != UINT64_MAX && makeAtomic(_start_time) != InvalidTime;
}

#ifdef DEBUG
void Timer::resetIdCount() {
    auto&& id_c_ref = makeAtomic(_id_count);
    id_c_ref = 0;
}
#endif

uint64_t Timer::_id_count = 0;
