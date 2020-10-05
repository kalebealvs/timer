#ifndef KTIMER_H
#define KTIMER_H
#include <chrono>
#include <atomic>

class Timer {
public:
    Timer ();
    ~Timer ();

    void stop ();

    template<typename duration_unit>
    double elapsedTime () const;
    
    void printDuration () const;

    uint64_t getId () const;

private:
    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> end_time;
    bool stopped = false;
    uint64_t id;
    static std::atomic<uint64_t> id_count;
};

#endif