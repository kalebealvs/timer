#include "timer.hpp"

#include <concepts>
#include <iostream>
#include <ratio>

using namespace std::chrono;
using Clock = high_resolution_clock;
using Time = Clock::time_point;
using sc = seconds;
using ms = milliseconds;
using mc = microseconds;
using ns = nanoseconds;

template <typename T> concept Number = std::integral<T> || std::floating_point<T>;

template <typename T>
    requires Number<T>
using limit = std::numeric_limits<T>;

template <class Duration>
using TimePoint = time_point<Clock, Duration>;

static constexpr int64_t InvalidTime = TimePoint<ms>(ms(0)).time_since_epoch().count();

template <typename unit>
static auto timeFromEpoch(const int64_t epoch) -> Time {
    return Time{unit(epoch)};
}

template <typename unit>
static constexpr auto getRatio() {
    return duration_cast<unit>(sc(1)).count();
}

Timer::Timer() : _start_time{Clock::now().time_since_epoch().count()}, _id{++_id_count} {
}

Timer::Timer(Timer&& oldTimer) noexcept
    : _start_time{oldTimer._start_time.load()}, _end_time{oldTimer._end_time.load()},
      _stopped{oldTimer._stopped.load()}, _id{oldTimer._id} {
    oldTimer.invalidate();
}

auto Timer::operator=(Timer&& oldTimer) noexcept -> Timer& {
    _start_time = oldTimer._start_time.load();
    _end_time = oldTimer._end_time.load();
    _stopped = oldTimer._stopped.load();
    _id = oldTimer._id;
    oldTimer.invalidate();
    return *this;
}

Timer::~Timer() {
    if(_stopped)
        return;

    stop();
    printDuration();
}

auto Timer::stop() -> void {
    if(_stopped)
        return;

    _end_time = Clock::now().time_since_epoch().count();
    _stopped = true;
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
    return duration<double, std::ratio<1, getRatio<unit>()>>(
               timeFromEpoch<ns>(_end_time) - timeFromEpoch<ns>(_start_time))
        .count();
}

auto Timer::invalidate() -> void {
    _stopped = true;
    _start_time = _end_time = InvalidTime;
    _id = limit<uint64_t>::max();
}

auto Timer::printDuration() const -> void {
    std::cout << "Timer " << _id << ": " << elapsedTime<mc>() << " μs \n";
}

auto Timer::getId() const -> uint64_t {
    return static_cast<uint64_t>(_id);
}

auto Timer::isValid() const -> bool {
    return _id_count != limit<uint64_t>::max() && _start_time != InvalidTime;
}

#ifdef DEBUG
void Timer::resetIdCount() {
    _id_count = 0;
}
#endif

std::atomic<uint64_t> Timer::_id_count = 0;
