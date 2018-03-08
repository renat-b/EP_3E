#include "StdAfx.h"
#include "Frame.h"

Frame::Frame()
{

}

Frame::Frame(const Frame &other)
{
    *this = other;
}

Frame::~Frame()
{
}

void Frame::operator=(const Frame &other)
{
    m_id        = other.m_id;
    m_interval  = other.m_interval;
    m_frame_num = other.m_frame_num;
    m_time      = other.m_time;
    m_type      = other.m_type;
    m_channels  = other.m_channels;
    m_storage   = other.m_storage;
}

void Frame::Clear()
{
    m_id = 0;
    m_interval = 0;
    m_frame_num = 0;
    m_time = 0;
    m_type = 0;
    m_channels.clear();
    m_storage.Shutdown();
}

uint32_t Frame::IDGet() const
{
    return m_id;
}

void Frame::IDSet(uint32_t id)
{
    m_id = id;
}

uint32_t Frame::IntervalGet() const
{
    return m_interval;
}

void Frame::IntervalSet(uint32_t interval)
{
    m_interval = interval;
}

uint32_t Frame::FrameNumGet() const
{
    return m_frame_num;
}

void Frame::FrameNumSet(uint32_t frame_num)
{
    m_frame_num = frame_num;
}

FrameTime Frame::TimeGet() const
{
    return m_time;
}

void Frame::TimeSet(FrameTime time)
{
    m_time = time;
}

uint32_t Frame::TypeGet() const
{
    return m_type;
}

void Frame::TypeSet(uint32_t type)
{
    m_type = type;
}

uint32_t Frame::ChannelsCount() const
{
    uint32_t count = m_channels.size();
    return count;
}

const Channel &Frame::ChannelGet(uint32_t pos) const
{
    const Channel &channel = m_channels[pos].channel;
    return channel;
}

const Value &Frame::ValueGet(uint32_t pos) const
{
    const Value &value = m_channels[pos].value;
    return value;
}

Value &Frame::ValueGet(uint32_t pos)
{
    Value &value = m_channels[pos].value;
    return value;
}

bool Frame::ChannelAdd(const Channel &channel, const Value &value)
{
    m_channels.emplace_back(ChannelInfo( { channel, value } ));
    return true;
}

bool Frame::MetaInfoGet(IMetaInfo **object, uint32_t id_meta_info) const
{
    bool r = m_storage.MetaInfoGet(object, id_meta_info);
    return r;
}

bool Frame::MetaInfoAdd(IMetaInfo *object)
{
    bool r = m_storage.MetaInfoAdd(object);
    return r;
}