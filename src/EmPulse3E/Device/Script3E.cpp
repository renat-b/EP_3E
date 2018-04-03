#include "StdAfx.h"
#include "Script3E.h"
#include "EmPulse3E/Common3E.h"

Script3E::Measure::Measure()
{
    memset(&operation, 0, sizeof(operation));
}

Script3E::Measure::Measure(const Measure &other)
{
    *this = other;
}

void Script3E::Measure::operator=(const Measure &other)
{
    operation = other.operation;
    channels  = other.channels;
}



Script3E::Script3E()
{
}

Script3E::Script3E(const Script3E &other)
{
    *this = other;
}

Script3E::~Script3E()
{
}

void Script3E::Shutdown()
{
    m_measures.clear();
    m_impulses.clear();
}

void Script3E::ChannelsCreate()
{
    for (uint32_t pos = 0; pos < m_measures.size(); pos++)
    {
        Measure            &measure   = m_measures[pos];
        OperationMeasure3E &operation = measure.operation;

        if (operation.sc_var == ScVarType0)
        {
            if (operation.mask.Rn0)
                ChannelAdd(ChannelBase_SSL, ChannelFlagSingleMeasure, measure);
            if (operation.mask.Rn1)
                ChannelAdd(ChannelBase_VSL, ChannelFlagSingleMeasure, measure);
            if (operation.mask.Rn2)
                ChannelAdd(ChannelBase_SSH, ChannelFlagSingleMeasure, measure);
            if (operation.mask.Rn3)
                ChannelAdd(ChannelBase_VSH, ChannelFlagSingleMeasure, measure);
            if (operation.mask.Rn4)
                ChannelAdd(operation.scom.Cn1, (ChannelFlagSingleMeasure | ChannelFlag1stMulti), measure);
            if (operation.mask.Rn5)
                ChannelAdd(operation.scom.Cn2, (ChannelFlagSingleMeasure | ChannelFlag2ndMulti), measure);
        }
        else
        {
            if (operation.mask.Rn0)
                ChannelAdd(ChannelBase_SSL, ChannelFlagDecayMeasure, measure);
            if (operation.mask.Rn1)
                ChannelAdd(ChannelBase_VSL, ChannelFlagDecayMeasure, measure);
            if (operation.mask.Rn2)
                ChannelAdd(ChannelBase_SSH, ChannelFlagDecayMeasure, measure);
            if (operation.mask.Rn3)
                ChannelAdd(ChannelBase_VSH, ChannelFlagDecayMeasure, measure);
            if (operation.mask.Rn4)
                ChannelAdd(operation.scom.Cn1, (ChannelFlagDecayMeasure | ChannelFlag1stMulti), measure);
            if (operation.mask.Rn5)
                ChannelAdd(operation.scom.Cn2, (ChannelFlagDecayMeasure | ChannelFlag2ndMulti), measure);
        }
    }
}

void Script3E::operator = (const Script3E &other)
{
    m_measures.clear();
    m_impulses.clear();
    
    m_measures = other.m_measures;
    m_impulses = other.m_impulses;
}

uint32_t Script3E::MeasureCount() const
{
    uint32_t count = m_measures.size();
    return count;
}

OperationMeasure3E &Script3E::MeasureGet(uint32_t pos)
{
    Measure &val = m_measures[pos];
    return val.operation;
}

uint32_t Script3E::ChannelCount(uint32_t pos_measure) const
{
    uint32_t count = m_measures[pos_measure].channels.size();
    return count;
}

Channel &Script3E::ChannelGet(uint32_t pos_measure, uint32_t pos_channel)
{
    Channel &channel = m_measures[pos_measure].channels[pos_channel];
    return channel;
}

uint32_t Script3E::ImpulseCount() const
{
    uint32_t count = m_impulses.size();
    return count;
}

OperationImpulse3E Script3E::ImpulseGet(uint32_t pos)
{
    OperationImpulse3E &val = m_impulses[pos];
    return val;
}

bool Script3E::MeasureAdd(const OperationMeasure3E &measure)
{
    Measure info;

    info.operation = measure;
    m_measures.push_back(info);
    return true;
}

void Script3E::ChannelAdd(uint32_t id, uint32_t flags, Measure &measure)
{
    Channel channel;

    ChannelAssign(channel, id, flags, measure.operation);
    MetaCreate(channel, measure.operation);

    measure.channels.push_back(channel);
}

void Script3E::ChannelAssign(Channel &channel, uint32_t id, uint32_t flags, const OperationMeasure3E &measure)
{
    if (flags & ChannelFlag1stMulti)
        id = ChannelBaseLast + id + 1;
    else if (flags & ChannelFlag2ndMulti)
        id = Channel1stMultiLast + id + 1;
    else
        id = id;

    channel.IDSet(id);
    // выставим колво точек в канале
    if (measure.sc_var == ScVarType0) // это одинарная точка
    {
        channel.PointsSet(1);
    }
    else // это спад
    {
        channel.PointsSet(measure.n_point.data);
    }
}

void Script3E::MetaCreate(Channel &channel, const OperationMeasure3E &operation)
{
    ChannelMetaInfo3E *meta = new(std::nothrow) ChannelMetaInfo3E;
    if (!meta)
        return;

    MetaAssign(meta, channel, operation);
    if (!channel.MetaInfoAdd(meta))
    {
        delete meta;
        return;
    }
}

void Script3E::MetaAssign(ChannelMetaInfo3E *meta, const Channel &channel, const OperationMeasure3E &operation)
{
    // создаем информацю по текущему каналу
    meta->Create(channel, operation);

    // это базовый канал, определимся, положительный или отрицательный импульс у него
    if (channel.IDGet() <= ChannelBaseLast)
    {
        // ищем операцию возбуждения со временем равным операции измерения
        uint32_t i = m_impulses.size();
        for (i = 0; i < m_impulses.size(); i++)
        {
            OperationImpulse3E &impulses = m_impulses[i];
            if (impulses.ofs.Get() == operation.ofs.Get())
                break;
        }
        // не нашли, выходим
        if (i >= m_impulses.size())
            return;
        // выставим - положительный или отрицательный импульс у канала
        meta->PolarFlagAssign(channel, m_impulses[i]);
    }
}
