#ifndef KTIMER_H
#define KTIMER_H
#include <chrono>
#include <atomic>

class Timer {
public:
    Timer ();
    Timer (Timer &&oldTimer);
    ~Timer ();
    Timer (const Timer &t) = delete;
    Timer operator= (const Timer&) = delete;

    void stop ();
    long double elapsedInSeconds () const;
    long double elapsedInMilliseconds () const;
    long double elapsedInMicroseconds () const;
    long double elapsedInNanoseconds () const;
    void printDuration () const;

    uint64_t getId () const;

    bool isValid () const;

#ifdef DEBUG
    static void resetIdCount ();
#endif

private:
    template<typename duration_unit>
    long double elapsedTime () const;

    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
    bool stopped = false;
    uint64_t id;
    static std::atomic<uint64_t> id_count;
};

#endif
