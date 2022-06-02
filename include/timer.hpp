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
    using epoch_type
        = decltype(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    std::atomic<epoch_type> _start_time;
    std::atomic<epoch_type> _end_time;
    std::atomic<bool> _stopped;
    uint64_t _id;
    static std::atomic<uint64_t> _id_count;
};

#endif
