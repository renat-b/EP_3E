#pragma once

#include "..\CommonDevice.h"
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
    uint32_t   m_offset_time = 0;

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
    void       Create(const OperationMeasure& measure);
};

class Frame3E
{
private:
    const Frame *m_frame = nullptr;

public:
    Frame3E(const Frame &frame);
    ~Frame3E();

    uint32_t   OffsetTimeGet() const;
};