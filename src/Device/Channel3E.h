#pragma once

#include "..\CommonDevice.h"
#include "..\Common.h"
#include "Channel.h"
#include "MetaInfo.h"

class ChannelMetaInfo3E;


class Channel3E
{
private:
    const Channel  *m_channel = nullptr;

public:
    Channel3E(const Channel &channel);
    ~Channel3E();

    const Channel    &ChannelGet() const;

    uint32_t          IDGet() const;
    ScVar             ScaleTypeGet() const;
    uint32_t          PointStart() const;
    uint32_t          PointCount() const;
	uint32_t          AmountOfSavingsGet() const;

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
    ScVar      m_scale_type  = ScVarType0;
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

    ScVar             ScaleTypeGet() const;
    uint32_t          PointStart()   const;
    uint32_t          PointCount()   const;
    uint32_t          AmountOfSavingsGet() const;
    bool              ChannelIsPositive() const;
    bool              ChannelIsNegative() const;

    void              Create(const Channel &channel, const OperationMeasure &measure);
    void              PolarFlagAssign(const Channel &channel, const OperationImpulse &impulse);
};