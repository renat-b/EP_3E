#pragma once

#include "Frame.h"

class FramesOfInterval
{
private:
    typedef std::vector<Frame> Frames;

private:
    Frames  m_frames;

public:
     FramesOfInterval();
    ~FramesOfInterval();
    
    void     operator = (const FramesOfInterval &other);
    void     Clear();

    uint32_t     Count() const;
    Frame&       Get(uint32_t num_frame);
    const Frame& Get(uint32_t num_frame) const;

    bool     Add(const Frame &frame);
    bool     Remove(uint32_t num_frame);   
};



class Frames
{
private:
    typedef std::vector<FramesOfInterval> FramesOfAllIntervals;

private:
    FramesOfAllIntervals m_frames;

public:
    Frames();
    ~Frames();
    
    void     operator = (const Frames &other);
    void     Clear();

    uint32_t     CountIntervals() const;
    uint32_t     CountFrames(uint32_t pos_interval) const;

    FramesOfInterval&       Get(uint32_t pos_interval);
    const FramesOfInterval& Get(uint32_t pos_interval) const;
    Frame&       GetFrame(uint32_t pos_interval, uint32_t num_frame);
    const Frame& GetFrame(uint32_t pos_interval, uint32_t num_frame) const;

    bool     Add(uint32_t pos_interval, const Frame &frame);
    bool     Remove(uint32_t pos_interval, uint32_t num_frame);
};