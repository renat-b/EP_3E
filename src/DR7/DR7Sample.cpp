#include "StdAfx.h"
#include "DR7Sample.h"
#include "..\Frames\Frame3E.h"

DR7Sample::DR7Sample() : m_notifier(nullptr), m_stream(nullptr)
{
}

DR7Sample::~DR7Sample()
{
}

void DR7Sample::Clear()
{
    m_start_cyclo_time = m_cur_time;
}

void DR7Sample::SetNotifier(EmPulse3ENotifier *notifier)
{
    m_notifier = notifier;
}

void DR7Sample::SetStream(IStreamBuffer* stream)
{
    m_stream = stream;
}

void DR7Sample::SetParams(const Calibration3E &calibration, const uint64_t &unix_time)
{
    m_cur_time.AddSec(unix_time);
    m_calibration = calibration;
}

bool DR7Sample::Parse()
{    
    Clear();
    if (!ParseHeader())
        return false;

    if (!ParseFrames())
        return false;

    return true;
}

uint32_t DR7Sample::LastError()
{
    return 0;
}

void DR7Sample::FramesAssign(const Frames &frames)
{
    m_frames.Clear();
    m_frames = frames;
}

bool DR7Sample::ParseHeader()
{
    // parsing dr7 sample header
    if (!m_stream->GetRawData(&m_header, sizeof(m_header)))
        return false;

    // calculate start cyclo time
    m_start_cyclo_time.AddMs(m_header.time);
    return true;
}

bool DR7Sample::ParseFrames()
{
    uint32_t pos_interval = m_header.interval_pos;
    // check bound intervals
    if (pos_interval >= m_frames.CountIntervals())
        return false;
    
    // parsing sample
    for (uint32_t pos_frame = 0; pos_frame < m_frames.CountFrames(pos_interval); pos_frame++)
    {
        Frame &frame = m_frames.Get(pos_interval, pos_frame);

        FrameAssign(frame);

        if (!ParseChannels(frame))
            return false;

        if (!OnFrame(frame))
            return false;
    }

    if (!OnCyclo())
        return false;
    return true;
}

bool DR7Sample::ParseChannels(Frame &frame)
{
    uint32_t channel_count = frame.ChannelsCount();
    for (uint32_t channel_pos = 0; channel_pos < channel_count; channel_pos++)
    {
        const Channel &channel = frame.ChannelGet(channel_pos);
        Value   &value   = frame.ValueGet(channel_pos);

        if (!ParseChannel(channel, value))
            return false;
    }
    return true;
}

bool DR7Sample::ParseChannel(const Channel &channel, Value& value)
{
    float    d_adc = 0;
    double   d_calib;

    Channel3E channel3E(channel);

    if (channel3E.ScaleGet() == ScVarType0)
    {
        if (!m_stream->GetRawData(&d_adc, sizeof(d_adc)))
            return false;

        if (!m_calibration.Calibrate(d_calib, channel.IDGet(), d_adc))
            return false;;

        value = d_calib;
    }
    else
    {
        assert(channel3E.PointCount() != 0);
        for (uint32_t i = 0; i < channel3E.PointCount(); i++)
        {
            if (!m_stream->GetRawData(&d_adc, sizeof(d_adc)))
                return false;

            if (!m_calibration.Calibrate(d_calib, channel.IDGet(), d_adc))
                return false;;

            if (!value.Assign(d_calib, i))
                return false;
        }
    }
    return true; 
}

bool DR7Sample::OnCyclo()
{
    if (!m_notifier)
        return true;

    if (!m_notifier->OnCyclo(EmPulse3ENotifier::FLAG_NOTIFY_END))
        return false;
    return true;
}

bool DR7Sample::OnFrame(const Frame &frame)
{
    if (!m_notifier)
        return true;

    if (!m_notifier->OnFrame(frame))
        return false;
    return true;
}

void DR7Sample::FrameAssign(Frame &frame)
{
    Frame3E frame3E(frame);

    FrameTime measure_time = m_start_cyclo_time; 
    measure_time.AddMs((uint64_t)(frame3E.OffsetTimeGet() * m_measure_unit_offset));

    frame.TimeSet(measure_time);
    frame.TypeSet(FrameTypeID::SampleTypeCalib);
}
