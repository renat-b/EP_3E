#pragma once

#include "Rule.h"

class RuleAverage : public Rule
{
private:
    struct ValueInfo
    {
        uint64_t    time;
        Value       value;
        //
        void operator=(const ValueInfo& other);
    };

private:
    bool          m_load;
    ValueInfo     m_value_plus_prev;
    ValueInfo     m_value_plus;
    ValueInfo     m_value_minus_prev;
    ValueInfo     m_value_minus;

    FrameKey      m_frame_key_plus;
    FrameKey      m_frame_key_minus;
    ChannelID     m_channel_key_plus;
    ChannelID     m_channel_key_minus;
    
    FrameKey      m_frame_key_average;    
    ChannelID     m_channel_key_average;


public:
    RuleAverage();
    ~RuleAverage();

    virtual bool Execute(Sample& sample) override;

private:
    bool         FrameAverageCreate(Frames& frames_average);
    double       CalcInterpolation(const uint64_t& first_time,const uint64_t& second_time,const uint64_t& average_time, const double& first_val, const double& second_val);

    bool         FrameAverageAddValue(Frames& frames_average, const uint64_t& frame_time, const Value& value);
    Frames*      FramesGet(Sample& sample, const FrameKey& key);
    FrameEmPulse3E*       FrameGet(Frames& frames, const uint64_t& frame_time);
};