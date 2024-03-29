#ifndef KTIMER_H
#define KTIMER_H
#include <chrono>

using epoch_type
    = decltype(std::chrono::high_resolution_clock::now().time_since_epoch().count());

class Timer {
public:
    Timer();
    Timer(const Timer& t) = delete;
    Timer(Timer&& oldTimer) noexcept;
    ~Timer();
    auto operator=(const Timer&) -> Timer& = delete;
    auto operator=(Timer&& oldTimer) noexcept -> Timer&;

    auto stop() -> void;
    auto elapsedInSeconds() const -> double;
    auto elapsedInMilliseconds() const -> double;
    auto elapsedInMicroseconds() const -> double;
    auto elapsedInNanoseconds() const -> double;
    auto printDuration() const -> void;

    auto getId() const -> uint64_t;

    auto isValid() const -> bool;

#ifdef DEBUG
    static auto resetIdCount() -> void;
#endif

private:
    template <typename unit>
    inline auto elapsedTime() const -> double;
    inline auto invalidate() -> void;

    epoch_type _start_time;
    epoch_type _end_time;
    bool _stopped;
    uint64_t _id;
    static uint64_t _id_count;
};

#endif
