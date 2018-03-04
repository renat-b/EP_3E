#pragma once

#include "..\Common\StreamBuffer.h"
#include "..\CommonDevice.h"
#include "..\Common\StreamBuffer.h"
#include "..\Device\Cyclogram3E.h"
#include "..\Frames\Frames.h"
#include "EmPulse3ENotifier.h"


class DR7Sample
{
private:
    const double    m_measure_unit_offset = 0.01;

private:
    IStreamBuffer      *m_stream = nullptr;
    DR7SampleHeader     m_header;

    uint64_t            m_cur_time;
    uint64_t            m_start_cyclo_time;

    EmPulse3ENotifier  *m_notifier  = nullptr;
    Frames              m_frames;


public:
    DR7Sample();
    ~DR7Sample();

    void     Clear();
    void     SetNotifier(EmPulse3ENotifier *notifier);

    void     SetStream(IStreamBuffer *stream);

    void     SetCurTime(const uint64_t &cur_time);

    bool     Parse();
    uint32_t LastError();

    void     FrameAdd(uint32_t pos_interval, const Frame &frame);


private:
    bool     ParseHeader();
    bool     ParseFrames();
    bool     ParseChannels(Frame &frame);
    bool     ParseChannel(const Channel &channel, Value& value);

    bool     OnCyclo();
    bool     OnFrame(const Frame &frame);

    void     FrameAssign(Frame &frame);
};
