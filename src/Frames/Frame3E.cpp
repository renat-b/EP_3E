#include "StdAfx.h"
#include "Frame3E.h"
#include "..\Device\Channel3E.h"
#include "..\DR7\TimeScale.h"


FrameMetaInfo3E::FrameMetaInfo3E() : m_offset_time(0)
{
}

FrameMetaInfo3E::FrameMetaInfo3E(const FrameMetaInfo3E &other)
{
    *this = other;
}

FrameMetaInfo3E::~FrameMetaInfo3E()
{
    m_offset_time = 0;
}

uint32_t FrameMetaInfo3E::ID() const
{
    return ID_EmPulse3E;
}

IMetaInfo *FrameMetaInfo3E::Copy() const
{
    FrameMetaInfo3E *meta = new(std::nothrow) FrameMetaInfo3E;
    if (!meta)
        return nullptr;

    *meta = *this;
    return meta;
}

void FrameMetaInfo3E::operator=(const FrameMetaInfo3E &other)
{
    m_offset_time      = other.m_offset_time;
    m_num_points       = other.m_num_points;
}

uint32_t FrameMetaInfo3E::OffsetTimeGet() const
{
    return m_offset_time;
}

void FrameMetaInfo3E::Create(const OperationMeasure &measure)
{
    m_offset_time = measure.ofs.Get();

    if (measure.sc_var == ScVarType0)
    {
        m_num_points = 1;
    }
    else
    {
        m_num_points = measure.n_point.Get();
    }
}

uint32_t FrameMetaInfo3E::NumPoints() const
{
    return m_num_points;
}

Frame3E::Frame3E(const Frame &frame)
{
    m_frame = &frame;
}

Frame3E::~Frame3E()
{

}

uint32_t Frame3E::OffsetTimeGet() const
{
    FrameMetaInfo3E *meta = nullptr;
    if (!m_frame->MetaInfoGet((IMetaInfo **)&meta, FrameMetaInfo3E::ID_EmPulse3E))
        return 0;

    uint32_t offset_time = meta->OffsetTimeGet();
    return offset_time;
}

uint32_t Frame3E::NumPoints() const
{
    FrameMetaInfo3E *meta = nullptr;
    if (!m_frame->MetaInfoGet((IMetaInfo **)&meta, FrameMetaInfo3E::ID_EmPulse3E))
        return 1;

    uint32_t num_points = meta->NumPoints();
    return num_points;
}

uint32_t Frame3E::ChannelsCount() const
{
    return m_frame->ChannelsCount();
}

const Channel &Frame3E::ChannelGet(uint32_t pos) const
{
    return m_frame->ChannelGet(pos);
}

const Value &Frame3E::ValueGet(uint32_t pos) const
{
    return m_frame->ValueGet(pos);
}

Value &Frame3E::ValueGet(uint32_t pos)
{
    Frame *frame = (Frame *)m_frame;
    return frame->ValueGet(pos);
}
