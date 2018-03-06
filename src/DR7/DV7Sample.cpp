#include "StdAfx.h"
#include "DV7Sample.h"
#include "..\Frames\Frame3E.h"

DV7Sample::DV7Sample() : m_cur_time(0), m_start_cyclo_time(0), m_notifier(nullptr), m_stream(nullptr)
{
}

DV7Sample::~DV7Sample()
{
}

void DV7Sample::Clear()
{
    m_last_error = LastErrorCodes::ErrorCodeUnknown;
    m_start_cyclo_time = 0;
}

void DV7Sample::SetNotifier(EmPulse3ENotifier *notifier)
{
    m_notifier = notifier;
}

void DV7Sample::SetStream(IStreamBuffer* stream)
{
    m_stream = stream;
}

void DV7Sample::SetParams(const Calibration3E &calibration, const uint64_t &cur_time)
{
    m_cur_time    = cur_time;
    m_calibration = calibration;
}

bool DV7Sample::Parse()
{    
    Clear();
    if (!ParseHeader())
        return false;

    if (!ParseFrames())
        return false;
    
    return true;
}

uint32_t DV7Sample::LastError() const
{
    return m_last_error;
}

void DV7Sample::FramesAssign(const Frames &frames)
{
    m_frames.Clear();
    m_frames = frames;
}

bool DV7Sample::ParseHeader()
{
    // parsing dr7 sample header
    if (!m_stream->GetRawData(&m_header, sizeof(m_header)))
        return false;

    // calculate start cyclo time
    m_start_cyclo_time = m_cur_time + m_header.time;
    return true;
}

bool DV7Sample::ParseFrames()
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

bool DV7Sample::ParseChannels(Frame &frame)
{
    Frame3E frame3E(frame);

    uint32_t count_channel = frame3E.ChannelsCount();
    uint32_t count_points  = frame3E.NumPoints(); 

    for (uint32_t pos_point = 0; pos_point < count_points; pos_point++)
    {
        for (uint32_t pos_channel = 0; pos_channel < count_channel; pos_channel++)
        {
            const Channel &channel = frame3E.ChannelGet(pos_channel);
            Value &value = frame3E.ValueGet(pos_channel);

            if (!ParseChannel(value, frame3E, channel, pos_point))
                return false;


        }
    }
    return true;
}

bool DV7Sample::ParseChannel(Value &value, const Frame3E &frame, const Channel &channel, uint32_t pos_point)
{
    uint32_t val = 0;
    double   d; 
    if (frame.ScaleGet() == ScVarType0)
    {
        if (!m_stream->GetRawData(&val, sizeof(val)))
        {
            m_last_error = LastErrorCodes::ErrorCodeEOF;
            return false;
        }

        d = (double)val / frame.AmountOfPoints(0);
        if (!m_calibration.Calibrate(d, channel.IDGet(), d))
            return false;;

        value = d;
    }
    else
    {
        if (!m_stream->GetRawData(&val, sizeof(val)))
        {
            m_last_error = LastErrorCodes::ErrorCodeEOF;
            return false;
        }

        d = (double)val / frame.AmountOfPoints(pos_point);
        if (!m_calibration.Calibrate(d, channel.IDGet(), d))
            return false;

        if (!value.Assign(d, pos_point))
            return false;
    }

    return true; 
}

bool DV7Sample::OnCyclo()
{
    if (!m_notifier)
        return true;

    if (!m_notifier->OnCyclo(EmPulse3ENotifier::FLAG_NOTIFY_END))
        return false;
    return true;
}

bool DV7Sample::OnFrame(const Frame &frame)
{
    if (!m_notifier)
        return true;

    if (!m_notifier->OnFrame(frame))
        return false;
    return true;
}

void DV7Sample::FrameAssign(Frame &frame)
{
    Frame3E frame3E(frame);

    uint64_t measure_time = m_start_cyclo_time + uint64_t(frame3E.OffsetTimeGet() * m_measure_unit_offset);   

    frame.TimeSet(measure_time);
    frame.TypeSet(FrameTypeID::SampleTypeCalib);
}