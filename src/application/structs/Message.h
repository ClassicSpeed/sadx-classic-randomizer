#pragma once

#include <ctime>

struct Message
{
    Message()
        : message(""), _start(0)
    {
    }

    explicit Message(std::string message)
        : message(std::move(message)), _start(std::clock())
    {
    }

    bool IsExpired(const float displayDuration) const
    {
        const double timePassed = (std::clock() - this->_start) / static_cast<double>(CLOCKS_PER_SEC);
        return timePassed > displayDuration;
    }


    std::string message;

private:
    std::clock_t _start;
};
