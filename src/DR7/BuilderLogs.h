#pragma once

#include "..\Common\OutLogger.h"
#include "..\Device\Cyclogram3E.h"
#include "..\Tools\itool_classes.h"
#include "DR7Sample.h"

class BuilderLogs : public LoggerPrint, public DR7Notifier
{
protected:
    struct LogInfo
    {
        ChannelID        channel;
        IndigoSuite::LogHeader log;
    };
    typedef std::vector<LogInfo>             LogHeaders;
    typedef std::vector<IndigoSuite::Sensor>    Sensors;


protected:
    uint32_t       m_type_measure;
    uint32_t       m_tool_type;
    Cyclogram3E*   m_cyclo; 

    LogHeaders     m_headers;
    Sensors        m_sensors;

    bool           m_ewl_mode;

public:
    BuilderLogs();
    ~BuilderLogs();

    void    Shutdown();

protected:
    // DR7 Notifier
    virtual bool   OnParse(uint32_t flags);
    virtual bool   OnCyclogram(Cyclogram3E& cyclo, uint32_t flags);

    virtual bool   OnCyclo(uint32_t flags);
    virtual bool   OnFrame(const FrameEmPulse3E& frame);
    virtual void   OnError(const char* msg);

protected:
};