#include "StdAfx.h"
#include "Cyclogram3E.h"

Cyclogram3E::Cyclogram3E()
{
}

Cyclogram3E::~Cyclogram3E()
{
}

void Cyclogram3E::Shutdown()
{
    m_version = 0;
    m_intervals.erase(m_intervals.begin(), m_intervals.end());
    m_convertor.Clear();
}

bool Cyclogram3E::Load(const uint8_t *data, uint32_t size)
{
    Shutdown();

    if (!m_convertor.Initialize(data, size))
        return false;
    
    if (!m_convertor.GetInt16(&m_version))
        return false;

    bool r = false;
    while (m_convertor.GetRemaind())
    {
        r = ParseInterval();
        if (!r)
            break;
    }
    return r;
}

uint32_t Cyclogram3E::IntervalCount() const
{
    uint32_t count = m_intervals.size();
    return count;
}

Interval3E &Cyclogram3E::IntervalGet(uint32_t interval_pos)
{
    Interval3E &res = m_intervals[interval_pos];
    return res;
}

bool Cyclogram3E::ParseInterval()
{
    IntervalInner3E val = { 0 };
    if (!m_convertor.GetRawData(&val, sizeof(val)))
        return false;

    Interval3E interval;
    interval.m_interval = val;
    if (!ParseScript(interval))
        return false;

    m_intervals.push_back(interval);
    return true;
}

bool Cyclogram3E::ParseScript(Interval3E &interval)
{
    uint8_t count_measure;
    uint8_t count_impulse;

    if (!m_convertor.GetInt8(&count_measure))
        return false;
    if (!m_convertor.GetInt8(&count_impulse))
        return false;


    Script3E script;
    OperationMeasure3E measure;
    for (uint32_t pos = 0; pos < count_measure; pos++)
    {
        if (!m_convertor.GetRawData(&measure, sizeof(OperationMeasure3E)))
            return false;

        if (!script.MeasureAdd(measure))
            return false;;

        PrintMeasure(measure, pos);
    }

    OperationImpulse3E impulse;
    for (uint32_t pos = 0; pos < count_impulse; pos++)
    {
        if (!m_convertor.GetRawData(&impulse, sizeof(OperationImpulse3E)))
            return false;
        script.m_impulses.push_back(impulse);
    }

    interval.m_script = script;
    interval.m_script.ChannelsCreate();
    return true;
}

void Cyclogram3E::PrintMeasure(OperationMeasure3E &measure, uint32_t measure_pos)
{
    printf("measure operation #%d\n", measure_pos);
    if (measure.mask.Rn0)
    {
        printf("channel: SSL, ");
        if (measure.sc_var == ScVarType0)
            printf("amount points: %d", measure.n_point);
        else
            printf("scale type: %d, start point: %d, count points: %d", (uint32_t)measure.sc_var, (uint32_t)measure.b_point.data, (uint32_t)measure.n_point.data);
        printf("\n");
    }
    if (measure.mask.Rn1)
    {
        printf("channel: VSL, ");
        if (measure.sc_var == ScVarType0)
            printf("amount points: %d", measure.n_point);
        else
            printf("scale type: %d, start point: %d, count points: %d", (uint32_t)measure.sc_var, (uint32_t)measure.b_point.data, (uint32_t)measure.n_point.data);
        printf("\n");
    }
    if (measure.mask.Rn2)
    {
        printf("channel SSH, ");
        if (measure.sc_var == ScVarType0)
            printf("amount points: %d", measure.n_point);
        else
            printf("scale type: %d, start point: %d, count points: %d", (uint32_t)measure.sc_var, (uint32_t)measure.b_point.data, (uint32_t)measure.n_point.data);
        printf("\n");
    }
    if (measure.mask.Rn3)
    {
        printf("channel: VSH, ");
        if (measure.sc_var == ScVarType0)
            printf("amount points: %d", measure.n_point);
        else
            printf("scale type: %d, start point: %d, count points: %d", (uint32_t)measure.sc_var, (uint32_t)measure.b_point.data, (uint32_t)measure.n_point.data);
        printf("\n");
    }
    if (measure.mask.Rn4)
    {
        printf("channel: 1st multi, id: %d, ", (uint32_t)measure.scom.Cn1);
        if (measure.sc_var == ScVarType0)
            printf("amount points: %d", measure.n_point);
        else
            printf("scale type: %d, start point: %d, count points: %d", (uint32_t)measure.sc_var, (uint32_t)measure.b_point.data, (uint32_t)measure.n_point.data);
        printf("\n");
    }
    if (measure.mask.Rn5)
    {
        printf("channel: 2nd multi, id: %d, ", (uint32_t)measure.scom.Cn2);
        if (measure.sc_var == ScVarType0)
            printf("amount points: %d", measure.n_point);
        else
            printf("scale type: %d, start point: %d, count points: %d", (uint32_t)measure.sc_var, (uint32_t)measure.b_point.data, (uint32_t)measure.n_point.data);
        printf("\n");
    }
    printf("\n");
}