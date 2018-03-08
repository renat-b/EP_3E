#pragma once

#include "..\DR7\NotifierParserBase.h"
#include "PrintLogChannels.h"

class Notifier3E : public NotifierParserBase
{
private:
    struct ChannelData
    {
        uint64_t time;
        double   val;
    };
    typedef std::vector<ChannelData> ChannelDataArray;

private:
    ChannelDataArray  m_vals;

    uint32_t    m_num_interval = 0;
    uint32_t    m_num_frame = 0;

    uint32_t    m_num_line  = 0;
    PrintLogChannels  m_log_file;


public:
    Notifier3E();
    ~Notifier3E();

    bool           Initialize(const char *file_name, uint32_t num_interval, uint32_t num_frame);

    virtual bool   OnParse(uint32_t flags) override;
    virtual bool OnCyclogram(const CyclogramBase &cyclo) override;

    virtual bool   OnCyclo(uint32_t flags) override;
    virtual bool   OnFrame(const Frame &frame) override;

private:
    void           AssignValue(const uint64_t &time, const Channel &channel, const Value &value);
    bool           PrintLogValue(const Value &val);
    void           PrintLogCaption(const Frame &frame);
    char          *PrintLogCaptionParams(const Frame &frame, char *buf, uint32_t len);
};