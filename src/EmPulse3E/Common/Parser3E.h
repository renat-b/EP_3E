#pragma once

#include "CommonLibEmPulse/StreamBuffer.h"
#include "FrameLib\CyclogramBase.h"
#include "FrameLib\NotifierParserBase.h"
#include "EmPulse3E/Device/CommonDevice3E.h"
#include "EmPulse3E/Device/Cyclogram3E.h"
#include "EmPulse3E/Device/Calibration3E.h"
#include "DR7Sample.h"
#include "DV7Sample.h"


class Parser3E
{
private:
    enum constants
    {
        MODE_DR7 = 1,
        MODE_DV7,
    };

private:
    DR7BaseHeader          m_header;
    DR7Sample          m_dr7_sample;
    DV7Sample          m_dv7_sample;

    Cyclogram3E        m_cyclogram3E;
    CyclogramBase      m_cyclogram; 
    Calibration3E      m_calibration;

    IStreamBuffer     *m_stream   = nullptr;
    NotifierParserBase *m_notifier = nullptr;

    uint32_t           m_mode = MODE_DR7;

public:
    Parser3E();
    ~Parser3E();

    bool   Initialize(NotifierParserBase *notifier);
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
    void   FrameAssign(Frame &frame, const OperationMeasure3E &measure, uint32_t pos_interval, uint32_t pos_frame);
};
