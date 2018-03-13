#include "StdAfx.h"
#include "Notifier3E.h"
#include "EmPulse3E/Common/ChannelInfo3E.h"

Notifier3E::Notifier3E()
{
}

Notifier3E::~Notifier3E()
{
    uint32_t break_point = 0;
}

bool Notifier3E::Initialize(const char *file_name, uint32_t num_interval, uint32_t num_frame)
{
    m_num_interval = num_interval;
    m_num_frame    = num_frame;

    if (m_num_interval == INT_MAX || m_num_frame == INT_MAX)
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
    return r;
}

bool Notifier3E::OnParse(uint32_t flags)
{
    return true;
}

bool Notifier3E::OnCyclogram(const CyclogramBase &cyclo)
{
    m_vals.clear();

    if (m_num_interval >= cyclo.CountIntervals())
        return true;
    
    if (m_num_frame >= cyclo.CountFrames(m_num_interval))
        return false;
    
    PrintLogCaption(cyclo.Get(m_num_interval, m_num_frame)); 
    return true;
}

bool Notifier3E::OnCyclo(uint32_t flags)
{
    return true;
}

bool Notifier3E::OnFrame(const Frame &frame)
{
    if ( !(frame.FrameNumGet() == m_num_frame && frame.IntervalGet() == m_num_interval))
        return true;

    if (!m_log_file.AddInt(m_num_line))
        return false;
    m_num_line++;

    if (!m_log_file.AddDouble(frame.TimeGet().GetTimeIndigo()))
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

void Notifier3E::AssignValue(const uint64_t &time, const Channel &channel, const Value &value)
{
    ChannelInfo3E   channel3E(channel);

    ChannelData data = { time, 0.0 };
    if (channel3E.ScaleGet() == ScVarType0)
        value.CopyTo(data.val);
    else
        value.CopyTo(data.val, 0);

    m_vals.push_back(data);
}

bool Notifier3E::PrintLogValue(const Value &val)
{
    double dd = 0.0;
    if (val.Dims() == 0)
        val.CopyTo(dd);
    else
        val.CopyTo(dd, 0);

    return m_log_file.AddDouble(dd);    
}

void Notifier3E::PrintLogCaption(const Frame &frame)
{
    std::string caption = "Num\tTime\t";
    char buf[64];

    if (frame.IDGet() == ChannelBase_SSL)
    {
        if (caption.size())
            caption += "\t";
        caption += "SSL";
        caption += PrintLogCaptionParams(frame, buf, _countof(buf));
    }
    if (frame.IDGet() == ChannelBase_VSL)
    {
        if (caption.size())
            caption += "\t";
        caption += "VSL";
        caption += PrintLogCaptionParams(frame, buf, _countof(buf));
    }
    if (frame.IDGet() == ChannelBase_SSH)
    {
        if (caption.size())
            caption += "\t";
        caption += "SSH";
        caption += PrintLogCaptionParams(frame, buf, _countof(buf));
    }
    if (frame.IDGet() == ChannelBase_VSH)
    {
        if (caption.size())
            caption += "\t";
        caption += "VSH";
        caption += PrintLogCaptionParams(frame, buf, _countof(buf));
    }
    if (frame.IDGet() >= Channel1stMultiFXMinus && frame.IDGet() <= Channel1stMultiVHA)
    {
        if (caption.size())
            caption += "\t";
        sprintf_s(buf, "1st multi, id: %d", (uint32_t)frame.IDGet() - ChannelBaseLast);
        caption += buf;
        caption += PrintLogCaptionParams(frame, buf, _countof(buf));
    }
    if (frame.IDGet() >= Channel2stMultiFYMinus && frame.IDGet() <= Channel2stMultiSHA)
    {
        if (caption.size())
            caption += "\t";
        sprintf_s(buf, "2st multi, id: %d", (uint32_t)frame.IDGet() - Channel1stMultiLast);
        caption += buf;
        caption += PrintLogCaptionParams(frame, buf, _countof(buf));
    }

    m_log_file.AddCaptions(caption.c_str());
    m_log_file.AddEndLine();
}

char *Notifier3E::PrintLogCaptionParams(const Frame &frame, char *buf, uint32_t len)
{
    buf[0] = 0;

    ChannelInfo3E channel(frame.ChannelGet(0));
    if (channel.ScaleGet() == ScVarType0)
        sprintf_s(buf, len, " (%d)", channel.AmountOfSavingsGet());
    else
        sprintf_s(buf, len, " (%d, %d)", channel.PointStart(), channel.PointCount());

    return buf;
}
