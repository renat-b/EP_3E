#pragma once

#include  "FrameEmPulse3E.h"
#include "..\CommonEmPulse\ChannelID.h"

class Point
{
private:
    FrameKey    m_key_frame;
    ChannelID   m_key_channel;
    uint64_t    m_time;
    Value       m_value;

public:
    Point();
    ~Point();

    uint64_t&   Time();
    FrameKey&   FrameKey();
    ChannelID&  ChannelKey();
    Value&      Value();
};
