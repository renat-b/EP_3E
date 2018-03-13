#pragma once

class FrameTime
{
private:
    enum constants
    {
        DIGIT_SEC = 10000,
        DIGIT_MS  = 10,
    };

private:
    uint64_t    m_time;

public:
    inline FrameTime(uint32_t sec = 0, uint16_t ms = 0);
    inline FrameTime(const FrameTime &other);

    inline FrameTime &operator = (const FrameTime &other);

    inline void     AddSec(uint64_t sec);
    inline void     AddMs(uint64_t ms);

    inline uint64_t GetTimeUnix() const;
    inline uint16_t GetTimeMs() const;
    inline double   GetTimeIndigo() const;
};

FrameTime::FrameTime(uint32_t sec /*= 0*/, uint16_t ms /*= 0*/)
{
    m_time  = (uint64_t)sec * DIGIT_SEC;
    m_time += (uint64_t)ms * DIGIT_MS;
}

FrameTime::FrameTime(const FrameTime &other)
{
    m_time = other.m_time;
}

FrameTime & FrameTime::operator=(const FrameTime &other)
{
    m_time = other.m_time;
    return *this;
}

void FrameTime::AddSec(uint64_t sec)
{
    m_time += sec * DIGIT_SEC;
}

void FrameTime::AddMs(uint64_t ms)
{
    m_time += ms * DIGIT_MS;
}

uint64_t FrameTime::GetTimeUnix() const
{
    uint64_t ret = m_time / DIGIT_SEC;
    return ret;
}

uint16_t FrameTime::GetTimeMs() const
{
    uint64_t ret = m_time % DIGIT_SEC;
    ret /= DIGIT_MS;
    return (uint16_t)ret;
}

double FrameTime::GetTimeIndigo() const
{
    double ret = (double)(m_time / DIGIT_SEC);
    double ms  = ((double)(m_time % DIGIT_SEC)) / DIGIT_SEC;  
    ret += ms;
    return ret;
}
