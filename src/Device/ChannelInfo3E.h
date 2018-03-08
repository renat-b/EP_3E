#pragma once

#include "..\CommonDevice3E.h"
#include "..\Common3E.h"
#include "Channel.h"
#include "MetaInfo.h"

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
    ScVar             ScaleGet() const;
    uint32_t          PointStart() const;
    uint32_t          PointCount() const;
    uint32_t          AmountOfSavingsGet() const;
    double            MsNumPoint(uint32_t num_point) const;

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
    ScVar      m_scale  = ScVarType0;
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
    double            MsGet(uint32_t num_point) const;


    void              Create(const Channel &channel, const OperationMeasure &measure);
    void              PolarFlagAssign(const Channel &channel, const OperationImpulse &impulse);
};