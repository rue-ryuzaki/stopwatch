#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <chrono>
#include <cstdint>
#include <string>

// -----------------------------------------------------------------------------
// -- Stopwatch ----------------------------------------------------------------
// -----------------------------------------------------------------------------
class Stopwatch
{
public:
    // -- static ---------------------------------------------------------------
    static std::string time_to_string(double seconds);
    static std::string time_to_string(uint64_t seconds);

    // -- constructor ----------------------------------------------------------
    Stopwatch();

    // -- methods --------------------------------------------------------------
    void start();
    void stop();

    std::string remain_to_string(double percent)    const;
    uint64_t    remain(double percent)              const;
    bool        is_elapsed(uint64_t sec)            const;

    template <class T, class U = std::ratio<1, 1> >
    T elapsed() const
    {
        return std::chrono::duration<T, std::nano>(m_last - m_start).count() *
                std::nano::num * U::den / (std::nano::den * U::num);
    }

    inline std::chrono::time_point<std::chrono::system_clock> current() const;

private:
    std::chrono::time_point<std::chrono::system_clock> m_start;
    std::chrono::time_point<std::chrono::system_clock> m_last;
};

#endif // STOPWATCH_H_
