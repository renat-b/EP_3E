#pragma once

#include "EmPulse3E/Device/CommonDevice3E.h"
#include "EmPulse3E/Common3E.h"
#include "FrameLib/Channel.h"
#include "FrameLib/MetaInfo.h"

class ChannelMetaInfo3E;


class ChannelInfo3E
{
private:
    const Channel  *m_channel = nullptr;

public:
    ChannelInfo3E(const Channel &channel);
    ~ChannelInfo3E();

    const Channel    &ChannelGet() const;

    uint32_t          IDGet() const;
    ScaleVariantInner3E             ScaleGet() const;
    uint32_t          PointStart() const;
    uint32_t          PointCount() const;
    uint32_t          AmountOfSavingsGet() const;
    double            PointMs(uint32_t num_point) const;

    bool              IsPositive() const;
    bool              IsNegative() const;
private:
    ChannelMetaInfo3E *MetaInfoGet() const;
};

class ChannelMetaInfo3E : public IMetaInfo
{
public:
    enum ID_Constants
    {
        ID_EmPulse3E = 1,
    };

protected:
    ScaleVariantInner3E      m_scale  = ScVarType0;
    uint32_t   m_point_start = 0;
    uint32_t   m_point_count = 0;
    uint32_t   m_amount_of_savings = 0;
    bool       m_positive_channel = false;
    bool       m_negative_channel = false;

public:
    ChannelMetaInfo3E();
    ChannelMetaInfo3E(const ChannelMetaInfo3E &other);

public:
    virtual ~ChannelMetaInfo3E();
    virtual  uint32_t   ID()   const override;
    virtual  IMetaInfo *Copy() const override;

public:
    void operator = (const ChannelMetaInfo3E& other);

    ScaleVariantInner3E             ScaleTypeGet() const;
    uint32_t          PointStart()   const;
    uint32_t          PointCount()   const;
    uint32_t          AmountOfSavingsGet() const;
    bool              ChannelIsPositive() const;
    bool              ChannelIsNegative() const;
    double            PointMs(uint32_t num_point) const;


    void              Create(const Channel &channel, const OperationMeasure3E &measure);
    void              PolarFlagAssign(const Channel &channel, const OperationImpulse3E &impulse);
};
