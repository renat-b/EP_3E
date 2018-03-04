#include "StdAfx.h"
#include "Test.h"

TestDR7Parser::TestDR7Parser()
{

}

TestDR7Parser::~TestDR7Parser()
{
    uint32_t break_point = 0;
}

bool TestDR7Parser::OnParse(uint32_t flags)
{
    return true;
}

bool TestDR7Parser::OnCyclogram(Cyclogram3E &cyclo, uint32_t flags)
{
    m_vals.clear();
    return true;
}

bool TestDR7Parser::OnCyclo(uint32_t flags)
{
    return true;
}

bool TestDR7Parser::OnFrame(const Frame &frame)
{
    if (frame.FrameNumGet() != 15 && frame.FrameNumGet() != 17)
        return true;

    for (uint32_t i = 0; i < frame.ChannelsCount(); i++)
    {
        const Channel &channel = frame.ChannelGet(i);
        AssignValue(frame.TimeGet(), channel, frame.ValueGet(i));
    }
    return true;
}

void TestDR7Parser::AssignValue(const uint64_t &time, const Channel &channel, const Value &value)
{
    Channel3E   channel3E(channel);

    ChannelData data = { time, 0.0 };
    if (channel3E.ScaleTypeGet() == ScVarType0)
        value.CopyTo(data.val);
    else
        value.CopyTo(data.val, 0);

    m_vals.push_back(data);
}
