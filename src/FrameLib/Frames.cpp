#include "StdAfx.h"
#include "Frames.h"

FramesOfInterval::FramesOfInterval()
{

}

FramesOfInterval::~FramesOfInterval()
{

}

void FramesOfInterval::operator=(const FramesOfInterval &other)
{
    m_frames = other.m_frames;
}

void FramesOfInterval::Clear()
{
    m_frames.clear();
}

uint32_t FramesOfInterval::Count() const
{
    uint32_t count = m_frames.size();
    return count;
}

Frame& FramesOfInterval::Get(uint32_t num_frame)
{
    Frame& frame = m_frames[num_frame];
    return frame;
}

const Frame& FramesOfInterval::Get(uint32_t num_frame) const
{
    const Frame& frame = m_frames[num_frame];
    return frame;
}

bool FramesOfInterval::Add(const Frame &frame)
{
    m_frames.push_back(frame);
    return true;
}

bool FramesOfInterval::Remove(uint32_t num_frame)
{
    if (num_frame >= m_frames.size())
        return false;

    m_frames.erase(m_frames.begin() + num_frame, m_frames.begin() + num_frame + 1);
    return true;
}




Frames::Frames()
{
}

Frames::~Frames()
{
}

void Frames::operator=(const Frames &other)
{
    Clear();
    m_frames = other.m_frames;
}

void Frames::Clear()
{
    m_frames.clear();
}

uint32_t Frames::CountIntervals() const
{
    uint32_t count = m_frames.size();
    return count;
}

uint32_t Frames::CountFrames(uint32_t pos_interval) const
{
    if (pos_interval >= m_frames.size())
        return 0;

    uint32_t count = m_frames[pos_interval].Count();
    return count;
}

FramesOfInterval& Frames::Get(uint32_t pos_interval)
{
    FramesOfInterval& frames_of_interval = m_frames[pos_interval];
    return frames_of_interval;
}

const FramesOfInterval& Frames::Get(uint32_t pos_interval) const
{
    const FramesOfInterval& frames_of_interval = m_frames[pos_interval];
    return frames_of_interval;
}

Frame& Frames::GetFrame(uint32_t pos_interval, uint32_t num_frame)
{
    Frame &frame = m_frames[pos_interval].Get(num_frame);
    return frame;
}

const Frame& Frames::GetFrame(uint32_t pos_interval, uint32_t num_frame) const
{
    const Frame &frame = m_frames[pos_interval].Get(num_frame);
    return frame;
}

bool Frames::Add(uint32_t pos_interval, const Frame &frame)
{
    if (pos_interval >= m_frames.size())
    {
        m_frames.push_back(FramesOfInterval());
    }
    
    if (pos_interval >= m_frames.size())
        return false;

    m_frames[pos_interval].Add(frame);
    return true;
}

bool Frames::Remove(uint32_t pos_interval, uint32_t num_frame)
{
    if (pos_interval >= m_frames.size())
        return false;
    
    bool r = m_frames[pos_interval].Remove(num_frame);
    return r;
}
