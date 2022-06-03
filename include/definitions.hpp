#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <chrono>
#include <concepts>

#ifdef __cpp_lib_atomic_ref
#include <atomic>
#include <utility>
constexpr auto makeAtomic(auto&& x) {
    return std::atomic_ref(std::forward<decltype(x)>(x));
}
#else
constexpr auto&& makeAtomic(auto&& x) {
    return x;
}
#endif

using Clock = std::chrono::high_resolution_clock;
using Time = Clock::time_point;
using sc = std::chrono::seconds;
using ms = std::chrono::milliseconds;
using mc = std::chrono::microseconds;
using ns = std::chrono::nanoseconds;

template <typename T> concept Number = std::integral<T> || std::floating_point<T>;

template <typename T>
    requires Number<T>
using limit = std::numeric_limits<T>;

template <typename Duration>
using TimePoint = std::chrono::time_point<Clock, Duration>;

#endif
