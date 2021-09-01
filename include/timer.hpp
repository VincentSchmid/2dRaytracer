#ifndef timer_h
#define timer_h

#include <chrono>

struct Timer
{
    typedef std::chrono::high_resolution_clock clock ;

    void reset() { start = clock::now() ; }

    double seconds_elapsed() const
    { return std::chrono::duration<double>( clock::now() - start ).count(); }

    private: clock::time_point start = clock::now() ;
};

#endif