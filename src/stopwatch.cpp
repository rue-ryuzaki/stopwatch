#include "stopwatch.h"

#include <algorithm>
#include <vector>

// -----------------------------------------------------------------------------
// -- Stopwatch ----------------------------------------------------------------
// -----------------------------------------------------------------------------
std::string Stopwatch::time_to_string(double seconds)
{
    std::string res = time_to_string(uint64_t(seconds));
    double fraction = seconds - double(uint64_t(seconds));
    std::string str = std::to_string(fraction);
    if (str.size() > 2) {
        res.insert(res.size() - 1, str.substr(1, std::min(size_t(4), str.size() - 1)));
    }
    return res;
}

// -----------------------------------------------------------------------------
std::string Stopwatch::time_to_string(uint64_t seconds)
{
    std::vector<std::pair<uint64_t, std::string> > const timestamps =
    {
        { 60, "s" },
        { 60, "m" },
        { 24, "h" },
        {  7, "d" }
    };
    std::string res;
    for (auto const& pair : timestamps) {
        uint64_t modulo = seconds % pair.first;
        seconds /= pair.first;
        if (seconds == 0) {
            res = std::to_string(modulo) + pair.second + res;
            break;
        } else {
            res = (modulo < 10 ? ("0" + std::to_string(modulo))
                               : std::to_string(modulo)) + pair.second + res;
        }
    }
    if (seconds > 0) {
        res = std::to_string(seconds) + "w" + res;
    }
    return res;
}

// -----------------------------------------------------------------------------
Stopwatch::Stopwatch()
    : m_start(),
      m_last()
{
    start();
}

// -----------------------------------------------------------------------------
void Stopwatch::start()
{
    m_start = m_last = current();
}

// -----------------------------------------------------------------------------
void Stopwatch::stop()
{
    m_last = current();
}

// -----------------------------------------------------------------------------
std::string Stopwatch::remain_to_string(double percent) const
{
    return time_to_string(remain(percent));
}

// -----------------------------------------------------------------------------
uint64_t Stopwatch::remain(double percent) const
{
    return uint64_t((1.0 - percent) * elapsed<double>() / percent);
}

// -----------------------------------------------------------------------------
bool Stopwatch::is_elapsed(uint64_t sec) const
{
    return std::chrono::duration<uint64_t, std::nano>(current() - m_last).count()
            / std::nano::den >= sec;
}

// -----------------------------------------------------------------------------
std::chrono::time_point<std::chrono::system_clock> Stopwatch::current() const
{
    return std::chrono::system_clock::now();
}
