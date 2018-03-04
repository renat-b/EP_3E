#include "StdAfx.h"
#include "RuleAverage.h"

void RuleAverage::ValueInfo::operator=(const ValueInfo& other)
{
    time  = other.time;
    value = other.value;
}

RuleAverage::RuleAverage() : m_load(false)
{
}

RuleAverage::~RuleAverage()
{
}

bool RuleAverage::Execute(Sample& sample)
{
    Frames* frames_plus    = sample.Find(m_frame_key_plus);
    Frames* frames_minus   = sample.Find(m_frame_key_minus);
    Frames* frames_average = FramesGet(sample, m_frame_key_average);
    if (!frames_plus || !frames_minus || !frames_average)
        return false;
    
    if (frames_plus->Count() != frames_minus->Count())
        return false;
    

    for (uint32_t i = 0; i < frames_plus->Count(); i++)
    {
        FrameEmPulse3E& frame_plus = frames_plus->Get(i);
        m_value_plus.time = frame_plus.Time();

        Value* value = frame_plus.Find(m_channel_key_plus);  
        if (!value)
            return false;
        m_value_plus.value = *value;


        FrameEmPulse3E& frame_minus = frames_minus->Get(i);
        m_value_plus.time = frame_minus.Time();          

        value = frame_minus.Find(m_channel_key_plus);  
        if (!value)
            return false;
        m_value_minus.value = *value;

        if (!FrameAverageCreate(*frames_average))
            return false;
    }
    return true;
}

bool RuleAverage::FrameAverageCreate(Frames& frames_average)
{
    if (!m_load)
    {
        m_value_plus_prev  = m_value_plus;
        m_value_minus_prev = m_value_minus;
        m_load = true;
        return true;
    }


    double   first_val,    second_val;
    double   average_plus, average_minus, average;
    uint64_t first_time,   second_time,   average_time;

    first_time   = m_value_plus_prev.time;
    second_time  = m_value_plus.time;
    average_time = m_value_minus_prev.time;

    m_value_plus_prev.value.CopyTo(first_val);
    m_value_plus.value.CopyTo(second_val);

    average_plus = CalcInterpolation(first_time, second_time, average_time, first_val, second_val);
    average = (average_plus - (double)(m_value_minus_prev.value)) / 2;


    m_value_minus_prev.value.CopyTo(first_time);
    m_value_minus.value.CopyTo(second_time);
    m_value_plus.value.CopyTo(average_time);

    m_value_minus_prev.value.CopyTo(first_val);
    m_value_minus.value.CopyTo(second_val);

    average_minus = CalcInterpolation(first_time, second_time, average_time, first_val, second_val);

    average = ((double)(m_value_plus.value) - average_minus) / 2;
    return true;
}

double RuleAverage::CalcInterpolation(const uint64_t& first_time,const uint64_t& second_time,const uint64_t& average_time,const double& first_val, const double& second_val)
{
    double average = first_val + ((double)(average_time - first_time) / (second_time - first_time)) * (second_val - first_val);
    return average;
}

bool RuleAverage::FrameAverageAddValue(Frames& frames_average, const uint64_t& frame_time, const Value& value)
{
    FrameEmPulse3E* frame = FrameGet(frames_average, frame_time);
    if (!frame)
        return false;

    //!!!if (!frame->Add(m_channel_key_average, value))
    //    return false;
    return true;
}

Frames* RuleAverage::FramesGet(Sample& sample, const FrameKey& key)
{
    Frames* found = sample.Find(key); 
    if (found)
        return found;
    
    if (!sample.Add(Frames(key)))
        return nullptr;

    found = sample.Find(key);
    return found;
}

FrameEmPulse3E* RuleAverage::FrameGet(Frames& frames, const uint64_t& frame_time)
{
    FrameEmPulse3E* found = frames.Find(frame_time);
    if (found)
        return found;

    FrameEmPulse3E frame(frames.Key(), frame_time);
    if (!frames.Add(frame))
        return nullptr;

    found = frames.Find(frame_time);
    return found;
}