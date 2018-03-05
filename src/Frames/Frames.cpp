#include "StdAfx.h"
#include "Frames.h"

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

    uint32_t count = m_frames[pos_interval].size();
    return count;
}

Frame &Frames::Get(uint32_t pos_interval, uint32_t pos_script)
{
    Frame &frame = m_frames[pos_interval][pos_script];
    return frame;
}

bool Frames::Add(uint32_t pos_interval, const Frame &frame)
{
    if (pos_interval >= m_frames.size())
    {
        m_frames.push_back(std::vector<Frame>());
    }
    
    if (pos_interval >= m_frames.size())
        return false;

    m_frames[pos_interval].push_back(frame);
    return true;
}

bool Frames::Remove(uint32_t pos_interval, uint32_t pos_script)
{
    if (pos_interval >= m_frames.size())
        return false;

    FramesOfInterval &frames_of_interval = m_frames[pos_interval]; 
    if (pos_script >= frames_of_interval.size())
        return false;

    frames_of_interval.erase(frames_of_interval.begin() + pos_script, frames_of_interval.begin() + pos_script + 1);
    return true;
}