#include "StdAfx.h"
#include "Point.h"

Point::Point() : m_time(0)
{
}

Point::~Point()
{
}

uint64_t& Point::Time()
{
    return m_time;
}

FrameKey& Point::FrameKey()
{
    return m_key_frame;
}

ChannelID& Point::ChannelKey()
{
    return m_key_channel;
}

Value& Point::Value()
{
    return m_value;
}
