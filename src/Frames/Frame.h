#pragma once

#include "..\Device\MetaInfoStorage.h"
#include "..\Device\Channel.h"
#include "..\Common\Value.h"

enum FrameTypeID
{
    SampleTypeADC   = 1,
    SampleTypeCalib = 2,
    SampleTypeQualityControl = 3,
};


class Frame
{
private:
    struct ChannelInfo
    {
        Channel   channel;
        Value     value;
    };
    typedef std::vector<ChannelInfo> Channels;


private:
    uint32_t   m_id        = 0;
    uint32_t   m_interval  = 0;
    uint32_t   m_frame_num = 0;
    uint64_t   m_time      = 0;
    uint32_t   m_type      = 0;
    Channels   m_channels;
    MetaInfoStorage  m_storage;

public:
    Frame();
    Frame(const Frame &other);
    ~Frame();
    void operator = (const Frame &other);

    void     Clear();

    uint32_t IDGet()       const;
    void     IDSet(uint32_t id);

    uint32_t IntervalGet() const;
    void     IntervalSet(uint32_t interval);

    uint32_t FrameNumGet() const;
    void     FrameNumSet(uint32_t frame_num);

    uint64_t TimeGet()  const;
    void     TimeSet(uint64_t time);

    uint32_t TypeGet() const;
    void     TypeSet(uint32_t type);

    uint32_t ChannelsCount() const;
    const Channel &ChannelGet(uint32_t pos) const;
    const Value &ValueGet(uint32_t pos) const;
    Value &ValueGet(uint32_t pos);

    bool  ChannelAdd(const Channel &channel, const Value &value);

    bool  MetaInfoGet(IMetaInfo **obj, uint32_t id_meta_info) const;
    bool  MetaInfoAdd(IMetaInfo *obj);
};
