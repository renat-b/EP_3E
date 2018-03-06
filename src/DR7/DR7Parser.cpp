#include "StdAfx.h"
#include "DR7Parser.h"
#include "..\Frames\Frame3E.h"

DR7Parser::DR7Parser() : m_notifier(nullptr), m_stream(nullptr)
{

}

DR7Parser::~DR7Parser()
{

}

bool DR7Parser::Initialize(EmPulse3ENotifier *notifier)
{
    m_notifier = notifier;
    return true;
}

bool DR7Parser::Parse(IStreamBuffer &stream, bool is_dr7/* = true */)
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

/*!!!
bool DR7Parser::BigFile(const char *path, uint32_t count)
{
    HANDLE handle = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (handle == INVALID_HANDLE_VALUE)
        return false;

    DWORD size = GetFileSize(handle, NULL);
    if (INVALID_FILE_SIZE == size)
    {
        CloseHandle(handle);
        return false;
    }

    SetFilePointer(handle, 644, NULL, FILE_BEGIN); 
    DWORD readed = 0;

    uint8_t *buf = new uint8_t[357568];
    BOOL r = ReadFile(handle, buf, 357568, &readed, NULL);
    
    SetFilePointer(handle, 0, NULL, FILE_END);
    for (uint32_t i = 0; i < count; i++)
    {
        r = WriteFile(handle, buf, 357568, &readed, NULL);
        r = r;
    }
    CloseHandle(handle);

    delete [] buf;
    return true;
}
*/

bool DR7Parser::ParseHeader()
{
    if (!m_stream->GetRawData(&m_header, sizeof(DR7Header)))
        return false;
    return true;
}

bool DR7Parser::ParseCyclogram()
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

bool DR7Parser::ParseCalibration()
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

bool DR7Parser::ParseResource()
{
    // res
    uint16_t len_res = 0;
    if (!m_stream->GetInt16(&len_res))
        return false;

    if (!m_stream->GetRawDataPtr(len_res))
        return false;

    return true;
}

bool DR7Parser::ParseSamples()
{
    bool r;
    if (m_mode == MODE_DR7)
        r = ParseDR7Samples(); 
    else
        r = ParseDV7Samples();

    return r;
}

bool DR7Parser::ParseDR7Samples()
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

bool DR7Parser::ParseDR7Sample()
{
    bool r = m_dr7_sample.Parse();
    return r;
}

bool DR7Parser::ParseDV7Samples()
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

bool DR7Parser::ParseDV7Sample()
{
    bool r = m_dv7_sample.Parse();
    if (!r)
    {
        if (m_dv7_sample.LastError() == DV7Sample::ErrorCodeEOF)
            r = true;
    }
    return r;
}

void DR7Parser::DR7SampleInit()
{
    m_dr7_sample.SetNotifier(m_notifier);
    m_dr7_sample.SetStream(m_stream);
    m_dr7_sample.SetCurTime(m_header.StartTime);
    m_dr7_sample.FramesAssign(m_cyclogram.FramesGet());
}

void DR7Parser::DV7SampleInit()
{
    m_dv7_sample.SetNotifier(m_notifier);
    m_dv7_sample.SetStream(m_stream);
    m_dv7_sample.SetParams(m_calibration, m_header.StartTime);
    m_dv7_sample.FramesAssign(m_cyclogram.FramesGet());
}

void DR7Parser::OnCyclogram()
{
    if (!CyclogramBaseCreate())
        return;

    if (!m_notifier)
        return;

    m_notifier->OnCyclogram(m_cyclogram3E, EmPulse3ENotifier::FLAG_NOTIFY_END);
}

bool DR7Parser::CyclogramBaseCreate()
{
    m_cyclogram.Clear();


    m_cyclogram.ToolIdSet(0);
    m_cyclogram.SerNumSet("");
    
    for (uint32_t pos_interval = 0; pos_interval < m_cyclogram3E.IntervalCount(); pos_interval++)
    {
        Script3E &script = m_cyclogram3E.IntervalGet(pos_interval).ScriptGet();
        for (uint32_t pos_measure = 0; pos_measure < script.MeasureCount(); pos_measure++)
        {
            Frame frame;
            FrameAssign(frame, script.MeasureGet(pos_measure), pos_interval, pos_measure);

            for (uint32_t pos_channel = 0; pos_channel < script.ChannelCount(pos_measure); pos_channel++)
            {

                Value     val;
                Channel3E channel3E(script.ChannelGet(pos_measure, pos_channel));

                if (channel3E.ScaleTypeGet() == ScVarType0)
                {
                    if (!val.Create(sizeof(double)))
                        return false;
                }
                else
                {
                    if (!val.Create1d(sizeof(double), channel3E.PointCount()))
                        return false;
                }

                if (!frame.ChannelAdd(channel3E.ChannelGet(), val))
                    return false;
            }

            if (!m_cyclogram.Add(pos_interval, frame))
                return false;
        }
    }
    
    return true;
}

void DR7Parser::FrameAssign(Frame &frame, const OperationMeasure &measure, uint32_t pos_interval, uint32_t pos_measure)
{
    frame.FrameNumSet(pos_measure);
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
