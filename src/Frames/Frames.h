#pragma once

#include "Frame.h"

class Frames
{
private:
    typedef std::vector<Frame> FramesOfInterval;
    typedef std::vector<FramesOfInterval> FramesOfAllIntervals;

private:
    FramesOfAllIntervals m_frames;

public:
    Frames();
    ~Frames();
    
    void     operator = (const Frames &other);
    void     Clear();

    uint32_t CountIntervals() const;
    uint32_t CountFrames(uint32_t pos_interval) const;
    Frame   &Get(uint32_t pos_interval, uint32_t pos_script);

    bool     Add(uint32_t pos_interval, const Frame &frame);
    bool     Remove(uint32_t pos_interval, uint32_t pos_script);
};