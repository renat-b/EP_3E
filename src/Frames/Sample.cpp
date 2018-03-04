#include "StdAfx.h"
#include "Sample.h"

Sample::Sample()
{
}

Sample::~Sample()
{
}

uint32_t Sample::Count() const
{
    uint32_t count = m_frames.size();
    return count;
}

Frames& Sample::Get(uint32_t pos)
{
    Frames& frame = m_frames[pos];
    return frame;
}

Frames* Sample::Find(const FrameKey& key)
{
    Frames *res = nullptr;
    for (uint32_t i = 0; i < m_frames.size(); i++)
    {
        Frames& frame = m_frames[i];
        if (frame.Key() == key)
        {
            res = &frame;
            break;
        }
    }
    return res;
}

bool Sample::Add(const Frames& frame)
{
    m_frames.push_back(frame);
    return true;
}

bool Sample::Remove(uint32_t pos)
{
    if (pos >= m_frames.size())
        return false;
    
    m_frames.erase(m_frames.begin() + pos, m_frames.begin() + pos + 1);
    return true;
}