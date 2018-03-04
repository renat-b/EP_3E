#include "StdAfx.h"
#include "CommonDevice.h"
#include "EmPulse3EParser.h"

EmPulse3EParser::EmPulse3EParser() : m_data(nullptr), m_size(0)
{
}

EmPulse3EParser::~EmPulse3EParser()
{
    Shutdown();
}

void EmPulse3EParser::Shutdown()
{
    m_cyclogram.Shutdown();
}

bool EmPulse3EParser::Parse(const uint8_t *data, uint32_t size)
{
    // DR7 header
    data += sizeof(DR7Header);
    size -= sizeof(DR7Header);
    
    // cyclogram
    uint16_t len_cyclo = *(uint16_t *)data;
    if (len_cyclo > size)
        return false;

    data += sizeof(len_cyclo);
    size -= sizeof(len_cyclo);

    bool r = m_cyclogram.Load(data, len_cyclo); 
    if (!r)
        return false;

    data += len_cyclo;
    size -= len_cyclo;    

    // calibration table
    uint16_t len_calib = *(uint16_t *)data;
    if (len_calib > size)
        return false;
    
    data += sizeof(len_calib);
    size -= sizeof(len_calib);
    data += len_calib;
    size -= len_calib;
    
    // res
    uint16_t len_res = *(uint16_t *)data;
    if (len_res > size)
        return false;
    
    data += sizeof(len_res);
    size -= sizeof(len_res);
    data += len_res;
    size -= len_res;

    // parsing samples
    if (!m_convertor.Initialize(data, size))
        return false;
    
    m_dv7_sample.SetCyclogram(&m_cyclogram);
    m_dv7_sample.SetDataConvertor(&m_convertor);
    m_dv7_sample.SetCurTime(0);

    // m_dr7_sample.SetCyclogram(&m_cyclogram);
    // m_dr7_sample.SetDataConvertor(&m_convertor);
    // m_dr7_sample.SetCurTime(0);

    r = true;    
    while (m_convertor.GetRemaind())
    {
        r = ParseSample();
        if (!r)
            break;
    }
    return r;
}

bool EmPulse3EParser::ParseFile(const char *path)
{
    HANDLE handle = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (handle == INVALID_HANDLE_VALUE)
        return false;

    DWORD size = GetFileSize(handle, NULL);
    if (INVALID_FILE_SIZE == size)
    {
        CloseHandle(handle);
        return false;
    }

    Shutdown(); 
    m_size = size;
    m_data = new(std::nothrow) uint8_t[m_size];
    if (!m_data)
    {
        CloseHandle(handle);
        return false;
    }
     
    if (!ReadFile(handle, m_data, m_size, &size, NULL) || m_size != size)
    {
        CloseHandle(handle);
        return false;
    }

    CloseHandle(handle);

    bool r = Parse(m_data, m_size);
    return r; 
}

bool EmPulse3EParser::ParseSample()
{
    bool r = m_dv7_sample.Parse();
    //bool r = m_dr7_sample.Parse();

    return r;
}