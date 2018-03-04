#pragma once

#include "DR7Sample.h"
#include "..\StreamFile.h"
#include "..\CommonDevice.h"
#include "..\StreamFile.h"
#include "..\Device\Cyclogram3E.h"
#include "..\Frames\FrameEmPulse3E.h"
#include "DV7Measure.h"


class DV7Sample
{
private:
    const double    m_measure_unit_offset = 0.01;

private:
    StreamFile*  m_convertor;
    DR7SampleHeader m_header;
    DV7ContrainterMeasure m_containter;

    FrameEmPulse3E           m_frame;

    uint64_t        m_cur_time;
    uint64_t        m_start_cyclo_time;

    Cyclogram3E*    m_cyclogram;
    DR7Notifier*    m_notifier;


public:
    DV7Sample();
    ~DV7Sample();

    void     Clear();
    void     SetNotifier(DR7Notifier* notifier);

    void     SetCyclogram(Cyclogram3E* cyclogram);
    void     SetDataConvertor(StreamFile* convertor);

    void     SetCurTime(const uint64_t& cur_time);

    bool     Parse();
    uint32_t LastError();
    

private:
    bool     ParseSample();
    bool     ParseHeader();
    bool     OnCyclo();
    bool     OnFrame();
};
