#include "StdAfx.h"
#include "DV7Measure.h"
#include "TimeScale.h"

DV7Channel3E::DV7Channel3E(const Channel3E& channel) : m_parent(nullptr), m_point_pos(0)
{
    m_amount_of_savings = channel.AmountOfSavingsGet();
    m_scale_type        = channel.ScaleTypeGet();
    m_point_count       = channel.PointCount();    

    ValueCreate();
}

DV7Channel3E::DV7Channel3E(const DV7Channel3E& other)
{
    Assign(other);
}

DV7Channel3E::~DV7Channel3E()
{
}

void DV7Channel3E::operator=(const DV7Channel3E& other)
{
    Assign(other);
}

uint32_t DV7Channel3E::PointPos() const
{
    return m_point_pos;
}

bool DV7Channel3E::ValueCreate()
{
    if (m_scale_type == ScVarType0)
    {
        if (!m_value.Create(sizeof(double)))
            return false;
    }
    else
    {
        if (m_point_count == 0)
            return false;
        if (!m_value.Create1d(sizeof(double), m_point_count))
            return false;
    }
    return true;
}

DV7ResultCode DV7Channel3E::Parse(StreamFile& convertor)
{
    uint32_t val = 0;

    if (!convertor.GetInt32(&val))
        return DV7ResultCode::RESULT_END_OF_DATA;  
    
    uint32_t amount = AmountOfSavingCalc();
    if (amount == 0)
        return DV7ResultCode::RESULT_FAILED;

    double ret = ((double)val) / amount;
    if (!ValueAssign(ret))
        return DV7ResultCode::RESULT_FAILED;

    m_point_pos++;
    if (IsEndOfPoints())
        m_parent->ChannelRemove(this);
    else
        m_parent->ChannelNext();

    return DV7ResultCode::RESULT_SUCCESS;
}

void DV7Channel3E::InitSample(DV7Measure *measure)
{
    m_parent = measure;
    if (m_parent)
        m_parent->ChannelAdd(this);

    m_point_pos = 0;
}

void DV7Channel3E::Assign(const DV7Channel3E& other)
{
    m_id = other.m_id;

    m_amount_of_savings = other.m_amount_of_savings;
    m_scale_type        = other.m_scale_type;
    m_point_start       = other.m_point_start;
    m_point_count       = other.m_point_count;

    m_point_pos         = other.m_point_pos;
    m_value             = other.m_value;
    m_parent            = other.m_parent;
}

bool DV7Channel3E::IsEndOfPoints()
{
    if (m_scale_type == ScVarType0)
    {
        if (m_point_pos >= 1)
            return true;
    }
    else
    {
        if (m_point_pos >= m_point_count)
            return true;
    }
    return false;
}

uint32_t DV7Channel3E::AmountOfSavingCalc()
{
    uint32_t  amount = 0;
    TimeScale time_scale;

    if (!time_scale.AmountOfSavingGet(*this, amount))
        return 0;
    return amount;
}

bool DV7Channel3E::ValueAssign(const double& val)
{
    if (m_scale_type == ScVarType0)
    {
        m_value = val;
    } 
    else
    {
        if (!m_value.Assign(val, m_point_pos))
            return false;
    } 
    return true;
}

DV7Measure::DV7Measure() : m_channel_pos(0)
{
}

DV7Measure::~DV7Measure()
{
}

void DV7Measure::Clear()
{
    m_channels_stack.clear();
}

bool DV7Measure::ChannelAdd(Channel3E& channel)
{
    m_channels.emplace_back(DV7Channel3E(channel));
    return true;
}

bool DV7Measure::ChannelAdd(DV7Channel3E* channel)
{
    m_channels_stack.push_back(channel);
    return true;
}

void DV7Measure::ChannelRemove(const DV7Channel3E* channel)
{
    for (uint32_t i = 0; i < m_channels_stack.size(); i++)
    {
        if (channel == m_channels_stack[i])
        {
            m_channels_stack.erase(m_channels_stack.begin() + i);
            break;
        }
    }
}

void DV7Measure::ChannelNext()
{
    if ((m_channel_pos + 1) >= m_channels_stack.size())
        m_channel_pos = 0;
    else 
        m_channel_pos++;
}

DV7ResultCode DV7Measure::Parse(StreamFile& convertor)
{
    DV7Channel3E* channel;
    DV7ResultCode code = DV7ResultCode::RESULT_SUCCESS;

    while ((channel = Next()) != nullptr)
    {
        code = channel->Parse(convertor); 
        if (code != DV7ResultCode::RESULT_SUCCESS)
            break;
    }

    return code;
}

DV7Channel3E* DV7Measure::Next()
{
    if (m_channel_pos >= m_channels_stack.size())
        return nullptr;

    DV7Channel3E* ret = m_channels_stack[m_channel_pos];
    return ret;
}

void DV7Measure::InitSample()
{
    Clear();

    for (uint32_t i = 0; i < m_channels.size(); i++)
        m_channels[i].InitSample(this);

    m_channel_pos = 0;
}

DV7ContrainterMeasure::DV7ContrainterMeasure()
{
}

DV7ContrainterMeasure::~DV7ContrainterMeasure()
{
}

bool DV7ContrainterMeasure::Create(Cyclogram3E& cyclo)
{
    Clear();
    // обходим все интервалы в циклограмме
    for (uint32_t interval_pos = 0; interval_pos < cyclo.IntervalCount(); interval_pos++)
    {
        // создаем dv7 интервал
        m_intervals.emplace_back(DV7Interval(interval_pos));
        DV7Interval& interval = m_intervals[m_intervals.size() - 1];

        // обходим операции измерения в интервале по циклограмме
        Script3E&  script = cyclo.IntervalGet(interval_pos).ScriptGet();
        for (uint32_t measure_pos = 0; measure_pos < script.MeasureCount(); measure_pos++)
        {
            // создаем dv7 операцию измерения
            interval.measures.emplace_back(DV7Measure());
            DV7Measure& measure = interval.measures[interval.measures.size() - 1];

            for (uint32_t channel_pos = 0; channel_pos < script.ChannelCount(measure_pos); channel_pos++)
            {
                // добавляем dv7 канал в измерение
                Channel3E& channel = script.ChannelGet(measure_pos, channel_pos);
                if (!measure.ChannelAdd(channel))
                    return false;
            }
        }
    }
    return true;
}

void DV7ContrainterMeasure::Clear()
{
    m_intervals.clear();
}

bool DV7ContrainterMeasure::Parse(uint32_t interval_pos, StreamFile& convertor)
{
    // ищем dv7 интервал по его номеру
    uint32_t pos = MeasureFind(interval_pos);
    if (pos >= m_intervals.size())
        return false;


    DV7Interval& interval = m_intervals[pos];

    InitSample(interval);
    if (!ParseInterval(interval, convertor))
        return false;

    return true;
}

uint32_t DV7ContrainterMeasure::MeasureFind(uint32_t interval_pos)
{
    if (interval_pos < m_intervals.size())
        return interval_pos;
    
    return m_intervals.size();
}

bool DV7ContrainterMeasure::ParseInterval(DV7Interval& interval, StreamFile& convertor)
{
    // последовательно обходим измерения и парсим данные
    for (uint32_t i = 0; i < interval.measures.size(); i++)
    {
        DV7ResultCode code = interval.measures[i].Parse(convertor);
        // данные закончились, такое может быть, возвращаем, что все хорошо
        if (code == DV7ResultCode::RESULT_END_OF_DATA)
            return true;
        // произошла ошибка парсинга, выходим с ошибкой
        if (code == DV7ResultCode::RESULT_FAILED)
            return false;
    }
    return true;
}

void DV7ContrainterMeasure::InitSample(DV7Interval& interval)
{
    for (uint32_t i = 0; i < interval.measures.size(); i++)
        interval.measures[i].InitSample();
}