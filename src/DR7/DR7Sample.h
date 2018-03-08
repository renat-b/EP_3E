#pragma once

#include "..\Common\StreamBuffer.h"
#include "..\CommonDevice3E.h"
#include "..\Common\StreamBuffer.h"
#include "..\Device\Cyclogram3E.h"
#include "..\Device\Calibration3E.h"
#include "..\Frames\Frames.h"
#include "EmPulse3ENotifier.h"


class DR7Sample
{
private:
    const double    m_measure_unit_offset = 0.01;

private:
    IStreamBuffer      *m_stream = nullptr;
    DR7SampleHeader     m_header;
    Calibration3E       m_calibration;

    FrameTime           m_cur_time = { 0, 0 };
    FrameTime           m_start_cyclo_time = { 0, 0 };

    EmPulse3ENotifier  *m_notifier  = nullptr;
    Frames              m_frames;


public:
    DR7Sample();
    ~DR7Sample();

    void     Clear();
    void     SetNotifier(EmPulse3ENotifier *notifier);

    void     SetStream(IStreamBuffer *stream);

    void     SetParams(const Calibration3E &calibration, const uint64_t &unix_time);

    bool     Parse();
    uint32_t LastError();

    void     FramesAssign(const Frames &frames);


private:
    bool     ParseHeader();
    bool     ParseFrames();
    bool     ParseChannels(Frame &frame);
    bool     ParseChannel(const Channel &channel, Value& value);

    bool     OnCyclo();
    bool     OnFrame(const Frame &frame);

    void     FrameAssign(Frame &frame);
};
