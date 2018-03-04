#include "StdAfx.h"
#include "BuilderLogs.h"

BuilderLogs::BuilderLogs() : m_ewl_mode(false), m_type_measure(0), m_tool_type(0), m_cyclo(nullptr)
{
}

BuilderLogs::~BuilderLogs()
{

}

void BuilderLogs::Shutdown()
{
    m_type_measure = 0;
    m_tool_type    = 0;

    m_headers.clear();
    m_sensors.clear();
}

bool BuilderLogs::OnParse(uint32_t flags)
{
    return true;
}

bool BuilderLogs::OnCyclogram(Cyclogram3E& cyclo, uint32_t flags)
{
    return true;
}

bool BuilderLogs::OnCyclo(uint32_t flags)
{
    return true;
}

bool BuilderLogs::OnFrame(const FrameEmPulse3E& frame)
{
    return true;
}

void BuilderLogs::OnError(const char* msg)
{
    return;
}