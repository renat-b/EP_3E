#pragma once

#include "CommonLibEmPulse/BinFile.h"
#include "CommonLibEmPulse/MemPack.h"

class PrintLogChannels
{
private:
    BinFile   m_file;
    MemPack   m_buffer;

public:
    PrintLogChannels();
    ~PrintLogChannels();
    
    bool   Open(const char *file_name);
    bool   AddCaptions(const char *caption);
    bool   AddDouble(const double &val);
    bool   AddInt(uint32_t val);
    bool   AddEndLine();
};
