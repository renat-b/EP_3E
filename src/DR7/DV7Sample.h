#pragma once

#include "..\Common\StreamBuffer.h"
#include "..\CommonDevice.h"
#include "..\Common\StreamBuffer.h"
#include "..\Device\Cyclogram3E.h"
#include "..\Device\Calibration3E.h"
#include "..\Frames\Frame3E.h"
#include "..\Frames\Frames.h"
#include "EmPulse3ENotifier.h"


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

    uint64_t            m_cur_time;
    uint64_t            m_start_cyclo_time;

    EmPulse3ENotifier  *m_notifier  = nullptr;
    Frames              m_frames;
    
    uint32_t            m_last_error = LastErrorCodes::ErrorCodeSuccess;


public:
    DV7Sample();
    ~DV7Sample();

    void     Clear();
    void     SetNotifier(EmPulse3ENotifier *notifier);

    void     SetStream(IStreamBuffer *stream);

    void     SetParams(const Calibration3E &calibration, const uint64_t &cur_time);

    bool     Parse();
    uint32_t LastError() const;

    void     FramesAssign(const Frames &frames);


private:
    bool     ParseHeader();
    bool     ParseFrames();
    bool     ParseChannels(Frame &frame);
    bool     ParseChannel(Value &value, const Frame3E &frame, const Channel &channel, uint32_t num_point);

    bool     OnCyclo();
    bool     OnFrame(const Frame &frame);

    void     FrameAssign(Frame &frame);
};
