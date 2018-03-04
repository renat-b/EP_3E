#include "StdAfx.h"
#include "FrameEmPulse3E.h"

FrameKey::FrameKey() : m_type(FrameTypeID::SampleTypeADC), m_param(0)
{
}

void FrameKey::operator=(const FrameKey &other)
{
    m_type = other.m_type;
    m_param = other.m_param;
}

void FrameKey::operator=(FrameTypeID type)
{
    m_type = type;
    m_param = 0;
}

bool FrameKey::operator==(const FrameKey &other) const
{
    bool r = (other.m_type == m_type) && (other.m_param == m_param);
    return r;
}

FrameTypeID FrameKey::TypeGet() const
{
    return m_type;
}

void FrameKey::TypeSet(const FrameTypeID type)
{
    m_type = type;
}

FrameEmPulse3E::FrameEmPulse3E() : m_key(), m_time(0)
{
}

FrameEmPulse3E::FrameEmPulse3E(const FrameKey& key, const uint64_t& frame_time) : m_key(key), m_time(frame_time)
{
}

FrameEmPulse3E::FrameEmPulse3E(const FrameEmPulse3E& other)
{
    *this = other;
}

FrameEmPulse3E::~FrameEmPulse3E()
{
}

FrameKey& FrameEmPulse3E::Key()
{
    return m_key;
}

void FrameEmPulse3E::operator = (const FrameEmPulse3E &other)
{
    Clear();
    m_interval = other.m_interval;
    m_flags    = other.m_flags;
    m_time     = other.m_time;
    
    for (uint32_t i = 0; i < other.m_data.size(); i++)
    {
        const ChannelFrame &channel_frame_other = other.m_data[i];
        ChannelFrame channel_frame = { channel_frame_other.channel->Copy(), channel_frame_other.value };
        
        if (!channel_frame.channel)
            return;
        m_data.push_back(channel_frame);
    }
}

uint64_t& FrameEmPulse3E::Time()
{
    return m_time;
}

uint64_t FrameEmPulse3E::TimeGet() const
{
    return m_time;
}

void FrameEmPulse3E::TimeSet(const uint64_t &val)
{
    m_time = val;
}

uint32_t FrameEmPulse3E::IntervalGet() const
{
    return m_interval;
}

void FrameEmPulse3E::IntervalSet(uint32_t val)
{
    m_interval = val;
}

uint32_t FrameEmPulse3E::FlagsGet() const
{
    return m_flags;
}

void FrameEmPulse3E::FlagsSet(uint32_t flags)
{
    m_flags = flags;
}

FrameTypeID FrameEmPulse3E::TypeGet() const
{
    return m_type;
}

void FrameEmPulse3E::TypeSet(const FrameTypeID &type)
{
    m_type = type;
}

const Value& FrameEmPulse3E::GetValue(uint32_t channel_pos) const
{
    const Value &value = m_data[channel_pos].value;
    return value;
}

uint32_t FrameEmPulse3E::Count() const
{
    uint32_t count = m_data.size();
    return count;
}

const Channel3E& FrameEmPulse3E::GetChannel(uint32_t channel_pos) const
{
    const Channel3E &channel = *(m_data[channel_pos].channel);
    return channel;
}

Value* FrameEmPulse3E::Find(const ChannelID &channel_key)
{
    Value *val = nullptr;   

    for (uint32_t i = 0; i < m_data.size(); i++)
    {
        ChannelFrame &info = m_data[i];
        if (info.channel->IDGet() == channel_key.IDGet())
        {
            val = &info.value;
            break;
        }
    }
    return val;
}

bool FrameEmPulse3E::Add(const Channel3E &channel, const Value &value)
{
    ChannelFrame info = { channel.Copy(), value };
    if (!info.channel)
        return false;

    m_data.push_back(info);
    return true;
}

bool FrameEmPulse3E::Remove(uint32_t channel_pos)
{
    if (channel_pos >= m_data.size())
        return false;

    delete m_data[channel_pos].channel;
    m_data[channel_pos].channel = nullptr;

    m_data.erase(m_data.begin() + channel_pos, m_data.begin() + channel_pos + 1);
    return true;
}

void FrameEmPulse3E::Clear()
{
    m_key  = FrameTypeID::SampleTypeADC;
    m_time = 0;
    Shutdown();
}

void FrameEmPulse3E::Shutdown()
{
    for (uint32_t i = 0; i < m_data.size(); i++)
    {
        ChannelFrame &frame_channel = m_data[i];

        if (frame_channel.channel)
        {
            delete frame_channel.channel;
            frame_channel.channel = nullptr;
        }
    }
    m_data.clear();
}