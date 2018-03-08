#include "StdAfx.h"
#include "Channel3E.h"
#include "..\DR7\TimeScale.h"

Channel3E::Channel3E(const Channel &channel) 
{
    m_channel = &channel;
}

Channel3E::~Channel3E()
{
    m_channel = nullptr;
}

const Channel &Channel3E::ChannelGet() const
{
    return *m_channel;
}

uint32_t Channel3E::IDGet() const
{
    return m_channel->IDGet();
}

ScVar Channel3E::ScaleGet() const
{
    ChannelMetaInfo3E *meta = MetaInfoGet();
    if (!meta)
        return ScVarType0;
    return meta->ScaleTypeGet();
}

uint32_t Channel3E::PointStart() const
{
    ChannelMetaInfo3E *meta = MetaInfoGet();
    if (!meta)
        return 0;
    return meta->PointStart();
}

uint32_t Channel3E::PointCount() const
{
    ChannelMetaInfo3E *meta = MetaInfoGet();
    if (!meta)
        return 0;
    return meta->PointCount();
}

uint32_t Channel3E::AmountOfSavingsGet() const
{
    ChannelMetaInfo3E *meta = MetaInfoGet();
    if (!meta)
        return 0;
    return meta->AmountOfSavingsGet();
}

double Channel3E::MsNumPoint(uint32_t num_point) const
{
    ChannelMetaInfo3E *meta = MetaInfoGet();
    if (!meta)
        return 0.0;
    return meta->MsGet(num_point);   
}

bool Channel3E::IsPositive() const
{
    ChannelMetaInfo3E *meta = MetaInfoGet();
    if (!meta)
        return false;
    return meta->ChannelIsPositive();
}


bool Channel3E::IsNegative() const
{
    ChannelMetaInfo3E *meta = MetaInfoGet();
    if (!meta)
        return false;
    return meta->ChannelIsNegative();
}

ChannelMetaInfo3E *Channel3E::MetaInfoGet() const
{
    ChannelMetaInfo3E *meta = nullptr;
    if (!m_channel->MetaInfoGet((IMetaInfo **)&meta, ChannelMetaInfo3E::ID_EmPulse3E))
        return nullptr;

    return meta;
}

ChannelMetaInfo3E::ChannelMetaInfo3E()
{
}

ChannelMetaInfo3E::ChannelMetaInfo3E(const ChannelMetaInfo3E &other)
{
}

ChannelMetaInfo3E::~ChannelMetaInfo3E()
{

}

uint32_t ChannelMetaInfo3E::ID() const
{
    return ID_EmPulse3E;
}

IMetaInfo *ChannelMetaInfo3E::Copy() const
{
    ChannelMetaInfo3E *meta = new(std::nothrow) ChannelMetaInfo3E;
    if (meta)
        *meta = *this;

    return meta;
}

void ChannelMetaInfo3E::operator=(const ChannelMetaInfo3E& other)
{
    m_amount_of_savings = other.m_amount_of_savings;

    m_scale  = other.m_scale;
    m_point_start = other.m_point_start;
    m_point_count = other.m_point_count;

    m_positive_channel = other.m_positive_channel;
    m_negative_channel = other.m_negative_channel;
}

ScVar ChannelMetaInfo3E::ScaleTypeGet() const
{
    return m_scale;
}

uint32_t ChannelMetaInfo3E::PointStart() const
{
    return m_point_start;
}

uint32_t ChannelMetaInfo3E::PointCount() const
{
    return m_point_count;
}

uint32_t ChannelMetaInfo3E::AmountOfSavingsGet() const
{
    return m_amount_of_savings;
}

bool ChannelMetaInfo3E::ChannelIsPositive() const
{
    return m_positive_channel;
}

bool ChannelMetaInfo3E::ChannelIsNegative() const
{
    return m_negative_channel;
}

double ChannelMetaInfo3E::MsGet(uint32_t num_point) const
{
    TimeScale time_scale;

    double ms = time_scale.MsGet(m_scale, num_point);
    return ms;
}

void ChannelMetaInfo3E::Create(const Channel &channel, const OperationMeasure &measure)
{
    m_positive_channel = false;
    m_negative_channel = false;

    if (channel.SinglePointIs()) // ��� ��������� �����
    {
        // �������� ���������, ����� � ���-�� ����������
        m_scale = ScVarType0;
        m_amount_of_savings = measure.n_point.data;

        // not used field, assign zero values
        m_point_start = 0;
        m_point_count = 0;
    }
    else // ��� ����
    {
        // �������� ���������, �����, ��������� �����, ���-�� ����� � �����        
        m_scale  = measure.sc_var;
        m_point_start = measure.b_point.data;
        m_point_count = measure.n_point.data;

        // not used field, assign zero values
        m_amount_of_savings = 0;
    }
}

void ChannelMetaInfo3E::PolarFlagAssign(const Channel &channel, const OperationImpulse &impulse)
{
    if (channel.IDGet() == ChannelBase_VSL) // ������� ������
    {
        // ������� ������� ���������� �� ������� ������ 
        if (impulse.ctrl.Pol0)
            m_negative_channel = true;
        else
            m_positive_channel = true;
    }
    else if (channel.IDGet() == ChannelBase_SSL) // �������� ������
    {
        // ������� ������� ���������� �� ������� ������
        if (impulse.ctrl.Pol1)
            m_negative_channel = true;
        else
            m_positive_channel = true;
    }
}
