#include <iostream>

#include "timer.hpp"

Timer::Timer () : id{++id_count} {
    start_time = std::chrono::system_clock::now ();
}

Timer::~Timer () {
    if (stopped)
        return;
    
    stop ();
    printDuration ();
}

void Timer::stop () {
    end_time = std::chrono::system_clock::now ();
}

template<typename duration_unit>
double Timer::elipsedTime () const {
    return std::chrono::duration_cast<duration_unit> (end_time - start_time).count ();
}

void Timer::printDuration () const {
    std::cout << "Timer " << id << ":" << elipsedTime<std::chrono::milliseconds> ();
}

uint64_t Timer::getId () const {
    return static_cast<uint64_t> (id);
}

std::atomic<uint64_t> Timer::id_count = 0;