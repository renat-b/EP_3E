#pragma once

#include "Frames.h"
#include "MetaInfo.h"

class CyclogramBase
{
private:
    typedef std::vector<uint32_t> CyclosOfInterval;

private:
    enum constants
    {
        MAX_INTERVAL   = 12,
        UNKNOWN_CYCLOS = -1,
    };

private:
    uint32_t  m_tool_id;
    char      m_ser_num[32];
    
    CyclosOfInterval  m_cycles_must_be; 
    CyclosOfInterval  m_cycles_real;

    Frames    m_frames;
    MetaInfoStorage  m_storage;


public:
    CyclogramBase();
    ~CyclogramBase();
    
    void        Clear();

    uint32_t    ToolIdGet() const;
    void        ToolIdSet(uint32_t id);

    const char* SerNumGet() const;
    void        SerNumSet(const char *ser_num);
    
    uint32_t    Cycles(uint32_t pos_interval) const;
    void        CyclesSet(uint32_t pos_interval, uint32_t cyclos);

    uint32_t    CyclesReal(uint32_t pos_interval) const;
    void        CyclesRealSet(uint32_t pos_interval, uint32_t cyclos);

    Frames&     FramesGet();
    void        FramesAssign(const Frames &frames);

    uint32_t     CountIntervals() const;
    uint32_t     CountFrames(uint32_t pos_interval) const;
    FramesOfInterval&       Get(uint32_t pos_interval);
    const FramesOfInterval& Get(uint32_t pos_interval) const;

    bool        Add(uint32_t pos_interval, const Frame &frame);
    bool        Remove(uint32_t pos_interval, uint32_t pos_script);

    bool        MetaInfoGet(IMetaInfo **obj, uint32_t id_meta_info) const;
    bool        MetaInfoAdd(IMetaInfo *obj);
};
