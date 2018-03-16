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

    m_cycles_must_be.clear();
    m_cycles_real.clear();

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

uint32_t CyclogramBase::Cycles(uint32_t pos_interval) const
{
    if (pos_interval >= m_cycles_must_be.size())
        return UNKNOWN_CYCLOS;

    return m_cycles_must_be[pos_interval];
}

void CyclogramBase::CyclesSet(uint32_t pos_interval, uint32_t cyclos)
{
    if (pos_interval >= m_cycles_must_be.size() && pos_interval > MAX_INTERVAL)
        return; 
    
    for (uint32_t i = m_cycles_must_be.size(); i <= pos_interval; i++)
    {
        m_cycles_must_be.push_back(UNKNOWN_CYCLOS);
    }
    m_cycles_must_be[pos_interval] = cyclos;
}

uint32_t CyclogramBase::CyclesReal(uint32_t pos_interval) const
{
    if (pos_interval >= m_cycles_real.size())
        return UNKNOWN_CYCLOS;

    return m_cycles_real[pos_interval];
}

void CyclogramBase::CyclesRealSet(uint32_t pos_interval, uint32_t cyclos)
{
    if (pos_interval >= m_cycles_real.size() && pos_interval > MAX_INTERVAL)
        return; 
    
    for (uint32_t i = m_cycles_real.size(); i <= pos_interval; i++)
    {
        m_cycles_real.push_back(UNKNOWN_CYCLOS);
    }
    m_cycles_real[pos_interval] = cyclos;
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

FramesOfInterval& CyclogramBase::Get(uint32_t pos_interval)
{
    FramesOfInterval &frame = m_frames.Get(pos_interval);
    return frame;
}

const FramesOfInterval& CyclogramBase::Get(uint32_t pos_interval) const
{
    const FramesOfInterval &frame = m_frames.Get(pos_interval);
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

bool CyclogramBase::MetaInfoGet(IMetaInfo **object, uint32_t id_meta_info) const
{
    bool r = m_storage.MetaInfoGet(object, id_meta_info);
    return r;
}

bool CyclogramBase::MetaInfoAdd(IMetaInfo *object)
{
    bool r = m_storage.MetaInfoAdd(object);
    return r;
}
