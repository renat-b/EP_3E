#pragma once

#include "..\CommonDevice.h"
#include "..\Common\StreamBuffer.h"
#include "..\Device\Cyclogram3E.h"
#include "DR7Sample.h"
#include "EmPulse3ENotifier.h"


class DR7Parser
{
private:
    uint8_t           *m_data = nullptr;
    uint32_t           m_size = 0;

    DR7Header          m_header;
    DR7Sample          m_dr7_sample;

    Cyclogram3E        m_cyclogram;

    IStreamBuffer     *m_stream = nullptr;
    EmPulse3ENotifier *m_notifier = nullptr;


public:
    DR7Parser();
    ~DR7Parser();

    bool   Initialize(EmPulse3ENotifier *notifier);
    
    bool   Parse(IStreamBuffer &stream);
    //!!!bool   BigFile(const char *path, uint32_t count);

private:
    bool   ParseHeader();
    bool   ParseCyclogram();
    bool   ParseCalibration();
    bool   ParseResource();
    bool   ParseSamples();
    bool   ParseSample();

    void   DR7SampleInit();

    void   OnCyclogram();
    bool   FramesCreate();
    void   FrameAssign(Frame &frame, const OperationMeasure &measure, uint32_t pos_measure);
};