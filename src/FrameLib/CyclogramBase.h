#pragma once

#include "Frames.h"

class CyclogramBase
{
private:
    uint32_t  m_tool_id;
    char      m_ser_num[32];
    Frames    m_frames;

public:
    CyclogramBase();
    ~CyclogramBase();
    
    void        Clear();

    uint32_t    ToolIdGet() const;
    void        ToolIdSet(uint32_t id);

    const char *SerNumGet() const;
    void        SerNumSet(const char *ser_num);

    Frames     &FramesGet();
    void        FramesAssign(const Frames &frames);

    uint32_t    CountIntervals() const;
    uint32_t    CountFrames(uint32_t pos_interval) const;
    Frame      &Get(uint32_t pos_interval, uint32_t pos_script);
    const Frame  &Get(uint32_t pos_interval, uint32_t pos_script) const;

    bool        Add(uint32_t pos_interval, const Frame &frame);
    bool        Remove(uint32_t pos_interval, uint32_t pos_script);

};
