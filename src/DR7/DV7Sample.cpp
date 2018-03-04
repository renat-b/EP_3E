#include "stdafx.h"
#include "DV7Sample.h"

DV7Sample::DV7Sample() : m_cur_time(0), m_start_cyclo_time(0), m_cyclogram(nullptr), m_notifier(nullptr), m_convertor(nullptr)
{
}

DV7Sample::~DV7Sample()
{
}

void DV7Sample::Clear()
{
    m_cur_time     = 0;
    m_start_cyclo_time = 0;
}

void DV7Sample::SetNotifier(DR7Notifier *notifier)
{
    m_notifier = notifier;
}

void DV7Sample::SetCyclogram(Cyclogram3E *cyclogram)
{
    if (!cyclogram)
        return;

    m_cyclogram = cyclogram;
    m_containter.Create(*cyclogram);
}

void DV7Sample::SetDataConvertor(StreamFile* convertor)
{
    m_convertor = convertor;
}

void DV7Sample::SetCurTime(const uint64_t& cur_time)
{
    m_cur_time = cur_time;
}

bool DV7Sample::Parse()
{    
    if (!m_cyclogram || !m_convertor)
        return false;

    Clear();
    if (!ParseHeader())
        return false;

    if (!ParseSample())
        return false;

    return true;
}

uint32_t DV7Sample::LastError()
{
    return 0;
}

bool DV7Sample::ParseSample()
{
    bool r = m_containter.Parse(m_header.interval_pos, *m_convertor);
    return r;
}

bool DV7Sample::ParseHeader()
{
    // parsing dr7 sample header
    if (!m_convertor->GetRawData(&m_header, sizeof(m_header)))
        return false;

    // calculate start cyclo time
    m_start_cyclo_time = m_cur_time + m_header.time;
    return true;
}