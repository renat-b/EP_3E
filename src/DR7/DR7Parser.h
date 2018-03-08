#pragma once

#include "..\CommonDevice.h"
#include "..\Common\StreamBuffer.h"
#include "..\Device\Cyclogram3E.h"
#include "..\Device\CyclogramBase.h"
#include "..\Device\Calibration3E.h"
#include "DR7Sample.h"
#include "DV7Sample.h"
#include "EmPulse3ENotifier.h"


class DR7Parser
{
private:
    enum constants
    {
        MODE_DR7 = 1,
        MODE_DV7,
    };

private:
    DR7Header          m_header;
    DR7Sample          m_dr7_sample;
    DV7Sample          m_dv7_sample;

    Cyclogram3E        m_cyclogram3E;
    CyclogramBase      m_cyclogram; 
    Calibration3E      m_calibration;

    IStreamBuffer     *m_stream   = nullptr;
    EmPulse3ENotifier *m_notifier = nullptr;

    uint32_t           m_mode = MODE_DR7;

public:
    DR7Parser();
    ~DR7Parser();

    bool   Initialize(EmPulse3ENotifier *notifier);
    bool   Parse(IStreamBuffer &stream, bool is_dr7 = true);

private:
    bool   ParseHeader();
    bool   ParseCyclogram();
    bool   ParseCalibration();
    bool   ParseResource();
    bool   ParseSamples();

    bool   ParseDR7Samples();
    bool   ParseDR7Sample();
    
    bool   ParseDV7Samples();
    bool   ParseDV7Sample();

    void   DR7SampleInit();
    void   DV7SampleInit();

    void   OnCyclogram();
    bool   CyclogramBaseCreate();
    void   FrameAssign(Frame &frame, const OperationMeasure &measure, uint32_t pos_interval, uint32_t pos_measure);
};