#pragma once

#include "CommonDevice.h"
#include "StreamFile.h"
#include ".\Device\Cyclogram3E.h"
#include ".\DR7\DV7Sample.h"
#include ".\DR7\DR7Sample.h"

class EmPulse3EParser
{
private:
    uint8_t   *m_data;
    uint32_t   m_size;

    Cyclogram3E    m_cyclogram;
    StreamFile  m_convertor;    
    DV7Sample      m_dv7_sample;
    DR7Sample      m_dr7_sample;


public:
    EmPulse3EParser();
    ~EmPulse3EParser();

    void   Shutdown();
    bool   Parse(const uint8_t *data, uint32_t size);
    bool   ParseFile(const char *path);


private:
    bool   ParseSample();
};
