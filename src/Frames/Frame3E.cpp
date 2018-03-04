#include "StdAfx.h"
#include "Frame3E.h"

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
    m_offset_time = other.m_offset_time;
}

uint32_t FrameMetaInfo3E::OffsetTimeGet() const
{
    return m_offset_time;
}

void FrameMetaInfo3E::Create(const OperationMeasure &measure)
{
    m_offset_time = measure.ofs.Get();
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
