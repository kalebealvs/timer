#include <iostream>

#include "timer.hpp"

Timer::Timer () : start_time{std::chrono::high_resolution_clock::now ()}, id{++id_count} {}

Timer::~Timer () {
    if (stopped)
        return;
    
    stop ();
    printDuration ();
}

void Timer::stop () {
    end_time = std::chrono::high_resolution_clock::now ();
}

long double Timer::elapsedInSeconds () const {
    return elapsedTime<std::chrono::seconds> ();
}

long double Timer::elapsedInMilliseconds () const {
    return elapsedTime<std::chrono::milliseconds> ();
}

long double Timer::elapsedInMicroseconds () const {
    return elapsedTime<std::chrono::microseconds> ();
}

long double Timer::elapsedInNanoseconds () const {
    return elapsedTime<std::chrono::nanoseconds> ();
}

template<typename duration_unit>
long double Timer::elapsedTime () const {
    return std::chrono::duration_cast<duration_unit> (end_time - start_time).count ();
}

void Timer::printDuration () const {
    std::cout << "Timer " << id << ":" << elapsedTime<std::chrono::microseconds>() << '\n';
}

uint64_t Timer::getId () const {
    return static_cast<uint64_t> (id);
}

#ifdef DEBUG
void Timer::resetIdCount () {
    id_count = 0;
}
#endif

std::atomic<uint64_t> Timer::id_count = 0;