#include "StdAfx.h"
#include "DR7Parser.h"
#include "..\Frames\Frame3E.h"

DR7Parser::DR7Parser() : m_data(nullptr), m_size(0), m_notifier(nullptr), m_stream(nullptr)
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

bool DR7Parser::Parse(IStreamBuffer &stream)
{
    m_stream = &stream;

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

    // dr7 samples
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
    bool r = m_cyclogram.Load(data, len_cyclo);
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
    
    if (!m_stream->GetRawDataPtr(len_calib))
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
    bool r = true;

    DR7SampleInit();
    while (m_stream->GetRemaind())
    {
        r = ParseSample();
        if (!r)
            break;
    }
    return r;
}

bool DR7Parser::ParseSample()
{
    bool r = m_dr7_sample.Parse();
    return r;
}

void DR7Parser::DR7SampleInit()
{
    m_dr7_sample.SetNotifier(m_notifier);
    m_dr7_sample.SetStream(m_stream);
    m_dr7_sample.SetCurTime(m_header.StartTime);
}

void DR7Parser::OnCyclogram()
{
    if (!FramesCreate())
        return;

    if (!m_notifier)
        return;

    m_notifier->OnCyclogram(m_cyclogram, EmPulse3ENotifier::FLAG_NOTIFY_END);
}

bool DR7Parser::FramesCreate()
{
    for (uint32_t pos_interval = 0; pos_interval < m_cyclogram.IntervalCount(); pos_interval++)
    {
        Script3E &script = m_cyclogram.IntervalGet(pos_interval).ScriptGet();
        for (uint32_t pos_measure = 0; pos_measure < script.MeasureCount(); pos_measure++)
        {
            Frame frame;
            FrameAssign(frame, script.MeasureGet(pos_measure), pos_measure);

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
            m_dr7_sample.FrameAdd(pos_interval, frame);
        }
    }
    return true;
}

void DR7Parser::FrameAssign(Frame &frame, const OperationMeasure &measure, uint32_t pos_measure)
{
    frame.FrameNumSet(pos_measure);

    FrameMetaInfo3E *meta = nullptr;
    if (frame.MetaInfoGet((IMetaInfo **)&meta, FrameMetaInfo3E::ID_EmPulse3E))
        return;

    meta = new (std::nothrow)FrameMetaInfo3E;
    if (!meta)
        return;

    meta->Create(measure);
    frame.MetaInfoAdd(meta);
}
