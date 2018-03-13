#pragma once

#include "CommonLibEmPulse/StreamBuffer.h"
#include "EmPulse3E/Device/CommonDevice3E.h"
#include "EmPulse3E/Device/Cyclogram3E.h"
#include "EmPulse3E/Device/Calibration3E.h"
#include "FrameInfo3E.h"
#include "FrameLib/Frames.h"
#include "FrameLib/NotifierParserBase.h"

class DV7Sample
{
public:
    enum LastErrorCodes
    {
        ErrorCodeSuccess = 0,
        ErrorCodeUnknown,
        ErrorCodeEOF,
    };

private:
    const double    m_measure_unit_offset = 0.01;

private:
    IStreamBuffer      *m_stream = nullptr;
    DR7SampleHeader     m_header;
    Calibration3E       m_calibration;

    FrameTime           m_cur_time = { 0, 0 };
    FrameTime           m_start_cyclo_time = { 0, 0 };

    NotifierParserBase  *m_notifier  = nullptr;
    Frames              m_frames;
    
    uint32_t            m_last_error = LastErrorCodes::ErrorCodeSuccess;
    

public:
    DV7Sample();
    ~DV7Sample();

    void     Clear();
    void     SetNotifier(NotifierParserBase *notifier);

    void     SetStream(IStreamBuffer *stream);

    void     SetParams(const Calibration3E &calibration, const uint64_t &unix_time);

    bool     Parse();
    uint32_t LastError() const;

    void     FramesAssign(const Frames &frames);


private:
    bool     ParseHeader();
    bool     ParseFrames();
    bool     ParseChannels(Frame &frame);
    bool     ParseChannel(Value &value, const ChannelInfo3E &channel, uint32_t pos_point);

    bool     OnCyclo();

    void     FrameAssign(Frame &frame);
};
