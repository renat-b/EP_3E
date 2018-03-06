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
    m_amount_of_points = other.m_amount_of_points;
    m_scale            = other.m_scale;
}

uint32_t FrameMetaInfo3E::OffsetTimeGet() const
{
    return m_offset_time;
}

ScVar FrameMetaInfo3E::ScaleGet() const
{
    return m_scale;
}

void FrameMetaInfo3E::Create(const OperationMeasure &measure)
{
    m_offset_time = measure.ofs.Get();
    m_scale = measure.sc_var;

    if (measure.sc_var == ScVarType0)
    {
        m_num_points = 1;
        m_amount_of_points = measure.n_point.Get();
    }
    else
    {
        m_num_points = measure.n_point.Get();
        m_amount_of_points = 1;
    }
}

uint32_t FrameMetaInfo3E::AmountOfPoints(uint32_t num_point) const
{
    if (m_scale == ScVarType0)
        return m_amount_of_points;

    TimeScale time_scale;

    uint32_t amount_of_points = time_scale.AmountOfPointsGet(m_scale, num_point);
    return amount_of_points;
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

ScVar Frame3E::ScaleGet() const
{
    FrameMetaInfo3E *meta = nullptr;
    if (!m_frame->MetaInfoGet((IMetaInfo **)&meta, FrameMetaInfo3E::ID_EmPulse3E))
        return ScVarType0;

    ScVar scale = meta->ScaleGet();
    return scale;   
}

uint32_t Frame3E::AmountOfPoints(uint32_t num_point) const
{
    FrameMetaInfo3E *meta = nullptr;
    if (!m_frame->MetaInfoGet((IMetaInfo **)&meta, FrameMetaInfo3E::ID_EmPulse3E))
        return 1;

    uint32_t amount_of_points = meta->AmountOfPoints(num_point);
    return amount_of_points;
}

uint32_t Frame3E::NumPoints() const
{
    FrameMetaInfo3E *meta = nullptr;
    if (!m_frame->MetaInfoGet((IMetaInfo **)&meta, FrameMetaInfo3E::ID_EmPulse3E))
        return 0;

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
