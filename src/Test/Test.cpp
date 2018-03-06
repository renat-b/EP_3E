#include "StdAfx.h"
#include "Test.h"

TestDR7Parser::TestDR7Parser()
{
}

TestDR7Parser::~TestDR7Parser()
{
    uint32_t break_point = 0;
}

bool TestDR7Parser::Initialize(const char *file_name, uint32_t num_interval, uint32_t num_frame)
{
    if (num_interval == INT_MAX || num_frame == INT_MAX)
        return true;

    char *ptr;
    char  buf[MAX_PATH];
    char  name[32];

    strcpy_s(buf, file_name);
    ptr = strrchr(buf, '\\');
    if (!ptr)
        return false;
    ptr += 1;

    strcpy_s(name, ptr);
   *ptr = 0;

    strcat_s(name, ".log");
    strcat_s(buf, name);

    bool r = m_log_file.Open(buf);
    if (r)
    {
        m_num_interval = num_interval;
        m_num_frame    = num_frame;
    }
    return r;
}

bool TestDR7Parser::OnParse(uint32_t flags)
{
    return true;
}

bool TestDR7Parser::OnCyclogram(Cyclogram3E &cyclo, uint32_t flags)
{
    m_vals.clear();

    if (m_num_interval >= cyclo.IntervalCount())
        return true;
    
    Script3E &script = cyclo.IntervalGet(m_num_interval).ScriptGet();
    if (m_num_frame >= script.MeasureCount())
        return false;
    
    PrintLogCaption(script.MeasureGet(m_num_frame)); 
    return true;
}

bool TestDR7Parser::OnCyclo(uint32_t flags)
{
    return true;
}

bool TestDR7Parser::OnFrame(const Frame &frame)
{
    if ( !(frame.FrameNumGet() == m_num_frame && frame.IntervalGet() == m_num_interval))
        return true;

    if (!m_log_file.AddInt(m_num_line))
        return false;
    m_num_line++;

    if (!m_log_file.AddDouble((double)frame.TimeGet()))
        return false;
    for (uint32_t pos = 0; pos < frame.ChannelsCount(); pos++)
    {
        if (!PrintLogValue(frame.ValueGet(pos)))
            return false;
    }
    if (!m_log_file.AddEndLine())
        return false;
    return true;
}

void TestDR7Parser::AssignValue(const uint64_t &time, const Channel &channel, const Value &value)
{
    Channel3E   channel3E(channel);

    ChannelData data = { time, 0.0 };
    if (channel3E.ScaleTypeGet() == ScVarType0)
        value.CopyTo(data.val);
    else
        value.CopyTo(data.val, 0);

    m_vals.push_back(data);
}

bool TestDR7Parser::PrintLogValue(const Value &val)
{
    double dd = 0.0;
    if (val.Dims() == 0)
        val.CopyTo(dd);
    else
        val.CopyTo(dd, 0);

    return m_log_file.AddDouble(dd);    
}

void TestDR7Parser::PrintLogCaption(OperationMeasure &measure)
{
    std::string caption = "Num\tTime\t";
    char buf[64];

    if (measure.mask.Rn0)
    {
        if (caption.size())
            caption += "\t";
        caption += "SLA";
        caption += PrintLogCaptionParams(measure, buf, _countof(buf));
    }
    if (measure.mask.Rn1)
    {
        if (caption.size())
            caption += "\t";
        caption += "VLA";
        caption += PrintLogCaptionParams(measure, buf, _countof(buf));
    }
    if (measure.mask.Rn2)
    {
        if (caption.size())
            caption += "\t";
        caption += "SHA";
        caption += PrintLogCaptionParams(measure, buf, _countof(buf));
    }
    if (measure.mask.Rn3)
    {
        if (caption.size())
            caption += "\t";
        caption += "VHA";
        caption += PrintLogCaptionParams(measure, buf, _countof(buf));
    }
    if (measure.mask.Rn4)
    {
        if (caption.size())
            caption += "\t";
        sprintf_s(buf, "1st multi, id: %d", (uint32_t)measure.scom.Cn1);
        caption += buf;
        caption += PrintLogCaptionParams(measure, buf, _countof(buf));
    }
    if (measure.mask.Rn5)
    {
        if (caption.size())
            caption += "\t";
        sprintf_s(buf, "2st multi, id: %d", (uint32_t)measure.scom.Cn1);
        caption += buf;
        caption += PrintLogCaptionParams(measure, buf, _countof(buf));
    }

    m_log_file.AddCaptions(caption.c_str());
    m_log_file.AddEndLine();
}

char *TestDR7Parser::PrintLogCaptionParams(OperationMeasure &measure, char *buf, uint32_t len)
{
    if (measure.sc_var == ScVarType0)
        sprintf_s(buf, len, " (%d)", measure.n_point);
    else
        sprintf_s(buf, len, " (%d, %d, %d)", (uint32_t)measure.sc_var, (uint32_t)measure.b_point.data, (uint32_t)measure.n_point.data);

    return buf;
}
