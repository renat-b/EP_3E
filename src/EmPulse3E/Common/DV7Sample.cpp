#include "StdAfx.h"
#include "DV7Sample.h"
#include "FrameInfo3E.h"
#include "..\Device\TimeScale3E.h"

DV7Sample::DV7Sample()
{
}

DV7Sample::~DV7Sample()
{
}

void DV7Sample::Clear()
{
    m_last_error = LastErrorCodes::ErrorCodeUnknown;
    m_start_cyclo_time = m_cur_time;
}

void DV7Sample::SetNotifier(NotifierParserBase *notifier)
{
    m_notifier = notifier;
}

void DV7Sample::SetStream(IStreamBuffer* stream)
{
    m_stream = stream;
}

void DV7Sample::SetParams(const Calibration3E &calibration, const uint64_t &unix_time)
{
    m_cur_time.AddSec(unix_time);
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
    m_start_cyclo_time.AddMs(m_header.time);
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
    FrameInfo3E frame3E(frame);

    uint32_t count_channel = frame3E.ChannelsCount();
    uint32_t count_points  = frame3E.NumPoints(); 

    for (uint32_t pos_point = 0; pos_point < count_points; pos_point++)
    {
        for (uint32_t pos_channel = 0; pos_channel < count_channel; pos_channel++)
        {
            ChannelInfo3E channel(frame.ChannelGet(pos_channel));
            Value &value = frame.ValueGet(pos_channel);

            if (!ParseChannel(value, channel, pos_point))
                return false;
        }
    }
    return true;
}

bool DV7Sample::ParseChannel(Value &value, const ChannelInfo3E &channel, uint32_t pos_point)
{
    int32_t  adc_voltage = 0;
    float    d_adc; 
    double   d_calib; 

    if (channel.ScaleGet() == ScVarType0)
    {
        if (!m_stream->GetRawData(&adc_voltage, sizeof(adc_voltage)))
        {
            m_last_error = LastErrorCodes::ErrorCodeEOF;
            return false;
        }
        d_adc = ((float)adc_voltage) / channel.AmountOfSavingsGet();
        if (!m_calibration.Calibrate(d_calib, channel.IDGet(), d_adc))
            return false;;

        value = d_calib;
    }
    else
    {
        if (!m_stream->GetRawData(&adc_voltage, sizeof(adc_voltage)))
        {
            m_last_error = LastErrorCodes::ErrorCodeEOF;
            return false;
        }
        
        TimeScale3E scale;
        d_adc = ((float)adc_voltage) / scale.AmountOfPointsGet(channel.ScaleGet(), channel.PointStart() + pos_point);
        if (!m_calibration.Calibrate(d_calib, channel.IDGet(), d_adc))
            return false;

        if (!value.Assign(d_calib, pos_point))
            return false;
    }

    return true; 
}

bool DV7Sample::OnCyclo()
{
    if (!m_notifier)
        return true;

    if (!m_notifier->OnCyclo(NotifierParserBase::FLAG_NOTIFY_END))
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
    FrameInfo3E frame3E(frame);

    FrameTime measure_time = m_start_cyclo_time;
    measure_time.AddMs((uint64_t)(frame3E.OffsetTimeGet() * m_measure_unit_offset));   

    frame.TimeSet(measure_time);
    frame.TypeSet(FrameTypeID::SampleTypeCalib);
}
