#include "StdAfx.h"
#include "CyclogramBase.h"

CyclogramBase::CyclogramBase() : m_tool_id(0)
{
    memset(m_ser_num, 0, sizeof(m_ser_num));
}

CyclogramBase::~CyclogramBase()
{

}

void CyclogramBase::Clear()
{
    m_tool_id    = 0;
    m_ser_num[0] = 0;
    m_frames.Clear();
}

uint32_t CyclogramBase::ToolIdGet() const
{
    return m_tool_id;
}

void CyclogramBase::ToolIdSet(uint32_t id)
{
    m_tool_id = id;
}

const char *CyclogramBase::SerNumGet() const
{
    return m_ser_num;
}

void CyclogramBase::SerNumSet(const char *ser_num)
{
    strcpy_s(m_ser_num, ser_num);
}

Frames &CyclogramBase::FramesGet()
{
    return m_frames;
}

void CyclogramBase::FramesAssign(const Frames &frames)
{
    m_frames = frames;
}

uint32_t CyclogramBase::CountIntervals() const
{
    uint32_t count = m_frames.CountIntervals();
    return count;
}

uint32_t CyclogramBase::CountFrames(uint32_t pos_interval) const
{
    uint32_t count = m_frames.CountFrames(pos_interval);
    return count;
}

Frame &CyclogramBase::Get(uint32_t pos_interval, uint32_t pos_script)
{
    Frame &frame = m_frames.Get(pos_interval, pos_script);
    return frame;
}

bool CyclogramBase::Add(uint32_t pos_interval, const Frame &frame)
{
    bool r = m_frames.Add(pos_interval, frame);
    return r;
}

bool CyclogramBase::Remove(uint32_t pos_interval, uint32_t pos_script)
{
    bool r = m_frames.Remove(pos_interval, pos_script);
    return r;
}
