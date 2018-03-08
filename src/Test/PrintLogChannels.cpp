#include "StdAfx.h"
#include "PrintLogChannels.h"

PrintLogChannels::PrintLogChannels()
{

}

PrintLogChannels::~PrintLogChannels()
{
    m_file.Close();
}

bool PrintLogChannels::Open(const char *file_name)
{
    if (!file_name)
        return false;

    bool r = m_file.OpenWrite(file_name);
    return r;
}

bool PrintLogChannels::AddCaptions(const char *caption)
{
    if (!m_buffer.AddString(caption, strlen(caption)))
        return false;
    return true;
}

bool PrintLogChannels::AddDouble(const double &val)
{
    if (m_buffer.GetSize())
    {
        if (!m_buffer.AddStringFormat("\t%.4f", val))
            return false;
    }
    else
    {
        if (!m_buffer.AddStringFormat("%.4f", val))
            return false;
    }
    return true;

}

bool PrintLogChannels::AddInt(uint32_t val)
{
    if (m_buffer.GetSize())
    {
        if (!m_buffer.AddStringFormat("\t%d", val))
            return false;
    }
    else
    {
        if (!m_buffer.AddStringFormat("%d", val))
            return false;
    }
    return true;


}

bool PrintLogChannels::AddEndLine()
{
    if (!m_buffer.AddString("\r\n", 2))
        return false;

    if (!m_file.Write(m_buffer.GetData(), m_buffer.GetSize()))
        return false;

    m_buffer.Clear();
    return true;
}
