#include "StdAfx.h"
#include "Parser3E.h"
#include "FrameInfo3E.h"
#include "CyclogramInfo3E.h"

Parser3E::Parser3E() : m_notifier(nullptr), m_stream(nullptr)
{

}

Parser3E::~Parser3E()
{

}

bool Parser3E::Initialize(NotifierParserBase *notifier)
{
    m_notifier = notifier;
    return true;
}

bool Parser3E::Parse(IStreamBuffer &stream, bool is_dr7/* = true */)
{
    m_stream = &stream;
    if (is_dr7)
        m_mode = MODE_DR7;
    else
        m_mode = MODE_DV7;

    // DR7 header
    if (!ParseHeader())
        return false;

    // cyclogram
    if (!ParseCyclogram())
        return false;

    // calibration table
    if (!ParseCalibration())
        return false;

    // res
    if (!ParseResource())
        return false;

    // samples
    if (!ParseSamples())
        return false;

    return true;
}

bool Parser3E::ParseHeader()
{
    if (!m_stream->GetRawData(&m_header, sizeof(DR7BaseHeader)))
        return false;
    return true;
}

bool Parser3E::ParseCyclogram()
{
    // cyclogram
    uint16_t len_cyclo = 0;
    if (!m_stream->GetInt16(&len_cyclo))
        return false;

    uint8_t *data = m_stream->GetRawDataPtr(len_cyclo); 
    if (!data)
        return false;
    bool r = m_cyclogram3E.Load(data, len_cyclo);
    if (!r)
        return false;

    OnCyclogram();
    return true;
}

bool Parser3E::ParseCalibration()
{
    // calibration table
    uint16_t len_calib = 0;
    if (!m_stream->GetInt16(&len_calib))
        return false;
    
    uint8_t *ptr; 
    if (!(ptr = m_stream->GetRawDataPtr(len_calib)))
        return false;
    
    if (!m_calibration.Load(ptr, len_calib))
        return false;

    return true;
}

bool Parser3E::ParseResource()
{
    // res
    uint16_t len_res = 0;
    if (!m_stream->GetInt16(&len_res))
        return false;

    if (!m_stream->GetRawDataPtr(len_res))
        return false;

    return true;
}

bool Parser3E::ParseSamples()
{
    bool r;
    if (m_mode == MODE_DR7)
        r = ParseDR7Samples(); 
    else
        r = ParseDV7Samples();

    return r;
}

bool Parser3E::ParseDR7Samples()
{
    bool r = true;

    DR7SampleInit();
    while (m_stream->GetRemaind())
    {
        r = ParseDR7Sample();
        if (!r)
            break;
    }
    return r;
}

bool Parser3E::ParseDR7Sample()
{
    bool r = m_dr7_sample.Parse();
    return r;
}

bool Parser3E::ParseDV7Samples()
{
    bool r = true;

    DV7SampleInit();
    while (m_stream->GetRemaind())
    {
        r = ParseDV7Sample();
        if (!r)
            break;
    }
    return r;
}

bool Parser3E::ParseDV7Sample()
{
    bool r = m_dv7_sample.Parse();
    if (!r)
    {
        if (m_dv7_sample.LastError() == DV7Sample::ErrorCodeEOF)
            r = true;
    }
    return r;
}

void Parser3E::DR7SampleInit()
{
    m_dr7_sample.SetNotifier(m_notifier);
    m_dr7_sample.SetStream(m_stream);
    m_dr7_sample.SetParams(m_calibration, m_header.StartTime);
    m_dr7_sample.FramesAssign(m_cyclogram.FramesGet());
}

void Parser3E::DV7SampleInit()
{
    m_dv7_sample.SetNotifier(m_notifier);
    m_dv7_sample.SetStream(m_stream);
    m_dv7_sample.SetParams(m_calibration, m_header.StartTime);
    m_dv7_sample.FramesAssign(m_cyclogram.FramesGet());
}

void Parser3E::OnCyclogram()
{
    if (!CyclogramBaseCreate())
        return;

    if (!m_notifier)
        return;

    m_notifier->OnCyclogram(m_cyclogram);
}

bool Parser3E::CyclogramBaseCreate()
{
    m_cyclogram.Clear();

    m_cyclogram.ToolIdSet(0);
    m_cyclogram.SerNumSet("");
    
    if (!FramesAssign())
        return false;
   
    if (!CyclesAssign())
        return false;

    return true;
}

bool Parser3E::FramesAssign()
{
    for (uint32_t pos_interval = 0; pos_interval < m_cyclogram3E.IntervalCount(); pos_interval++)
    {
        Script3E &script = m_cyclogram3E.IntervalGet(pos_interval).ScriptGet();
        for (uint32_t pos_measure = 0; pos_measure < script.MeasureCount(); pos_measure++)
        {
            Frame frame;
            FrameAssign(frame, script.MeasureGet(pos_measure), pos_interval, pos_measure);

            for (uint32_t pos_channel = 0; pos_channel < script.ChannelCount(pos_measure); pos_channel++)
            {
                if (!ChannelAdd(frame, script.ChannelGet(pos_measure, pos_channel)))
                    return false;
            }

            if (!m_cyclogram.Add(pos_interval, frame))
                return false;
        }
    }
    return true; 
}

void Parser3E::FrameAssign(Frame &frame, const OperationMeasure3E &measure, uint32_t pos_interval, uint32_t pos_frame)
{
    frame.FrameNumSet(pos_frame);
    frame.IntervalSet(pos_interval);

    FrameMetaInfo3E *meta = nullptr;
    if (frame.MetaInfoGet((IMetaInfo **)&meta, FrameMetaInfo3E::ID_EmPulse3E))
        return;

    meta = new (std::nothrow)FrameMetaInfo3E;
    if (!meta)
        return;

    meta->Create(measure);
    frame.MetaInfoAdd(meta);
}


bool  Parser3E::ChannelAdd(Frame &frame, const Channel &channel)
{
    Value     val;
    ChannelInfo3E channel3E(channel);

    if (channel3E.ScaleGet() == ScVarType0)
    {
        if (!val.Create(sizeof(double)))
            return false;
    }
    else
    {
        if (!val.Create1d(sizeof(double), channel3E.PointCount()))
            return false;
    }

    if (!frame.ChannelAdd(channel, val))
        return false;

    return true;
}

bool Parser3E::CyclesAssign()
{
    CyclogramMetaInfo3E *meta = new(std::nothrow) CyclogramMetaInfo3E;
    if (!meta)
        return false;

    if (!m_cyclogram.MetaInfoAdd(meta))
    {
        delete meta;
        return false;
    }

    for (uint32_t i = 0; i < m_cyclogram3E.IntervalCount(); i++)
    {
        Interval3E &interval = m_cyclogram3E.IntervalGet(i);

        m_cyclogram.CyclesSet(i, interval.Cycles());
        m_cyclogram.CyclesRealSet(i, interval.CyclesReal());
    }

    return true;
}