#ifndef KTIMER_H
#define KTIMER_H
#include <atomic>
#include <chrono>

class Timer {
public:
    Timer();
    Timer(const Timer& t) = delete;
    Timer(Timer&& oldTimer) noexcept;
    ~Timer();
    auto operator=(const Timer&) -> Timer& = delete;
    auto operator=(Timer&& oldTimer) noexcept -> Timer&;

    auto stop() -> void;
    auto elapsedInSeconds() const -> long double;
    auto elapsedInMilliseconds() const -> long double;
    auto elapsedInMicroseconds() const -> long double;
    auto elapsedInNanoseconds() const -> long double;
    auto printDuration() const -> void;

    auto getId() const -> uint64_t;

    auto isValid() const -> bool;

#ifdef DEBUG
    static auto resetIdCount() -> void;
#endif

private:
    template <typename unit>
    inline auto elapsedTime() const -> long double;
    inline auto invalidate() -> void;

    std::chrono::high_resolution_clock::time_point _start_time;
    std::chrono::high_resolution_clock::time_point _end_time;
    bool _stopped = false;
    uint64_t _id;
    static std::atomic<uint64_t> _id_count;
};

#endif
