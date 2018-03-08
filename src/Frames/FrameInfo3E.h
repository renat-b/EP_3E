#pragma once

#include "..\CommonDevice3E.h"
#include "..\Device\MetaInfo.h"
#include "Frame.h"

class FrameMetaInfo3E : public IMetaInfo
{
public:
    enum ID_Constants
    {
        ID_EmPulse3E = 2,
    };

protected:
    uint32_t   m_offset_time      = 0;
    uint32_t   m_num_points       = 1;

public:
    FrameMetaInfo3E();
    FrameMetaInfo3E(const FrameMetaInfo3E &other);

public:
    virtual ~FrameMetaInfo3E();
    virtual  uint32_t   ID()   const override;
    virtual  IMetaInfo *Copy() const override;

public:
    void operator = (const FrameMetaInfo3E& other);

    uint32_t   OffsetTimeGet() const;
    uint32_t   NumPoints() const;

    void       Create(const OperationMeasure3E &measure);
};

class FrameInfo3E
{
private:
    const Frame *m_frame = nullptr;

public:
    FrameInfo3E(const Frame &frame);
    ~FrameInfo3E();

    uint32_t   OffsetTimeGet() const;
    uint32_t   NumPoints() const;

    uint32_t       ChannelsCount() const;
    const Channel &ChannelGet(uint32_t pos) const;
    const Value   &ValueGet(uint32_t pos) const;
    Value         &ValueGet(uint32_t pos);
};