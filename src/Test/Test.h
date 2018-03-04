#pragma once

#include "..\DR7\EmPulse3ENotifier.h"

class TestDR7Parser : public EmPulse3ENotifier
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


public:
    TestDR7Parser();
    ~TestDR7Parser();

    virtual bool   OnParse(uint32_t flags) override;
    virtual bool   OnCyclogram(Cyclogram3E &cyclo, uint32_t flags) override;

    virtual bool   OnCyclo(uint32_t flags) override;
    virtual bool   OnFrame(const Frame &frame) override;

private:
    void           AssignValue(const uint64_t &time, const Channel &channel, const Value &value);
};