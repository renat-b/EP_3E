#pragma once

#include "..\Common\Value.h"
#include "..\Device\ChannelInfo3E.h"
#include "..\CommonEmPulse\ChannelID.h"

struct FrameKeyParam
{
    uint16_t  base_type   : 6;
    uint16_t  device_type : 6;
    uint16_t  interval    : 4;
    uint8_t   measure_mode: 4;

    uint8_t   reserved1 : 4;
    uint8_t   reserved2 : 8;
    uint8_t   reserved3 : 8;
    uint8_t   reserved4 : 8;
    uint8_t   reserved5 : 8;
    uint8_t   reserved6 : 8;
};

class FrameKey
{
private:
    FrameTypeID  m_type; 
    uint64_t     m_param;

public:
    FrameKey();
    void operator=(const FrameKey &other);
    void operator=(FrameTypeID type);

    bool operator==(const FrameKey &other) const;
    FrameTypeID TypeGet() const;
    void     TypeSet(FrameTypeID type);

    template<typename T>
    T&  Param()
    {
        return (*((T*)&m_param));
    }
};


class FrameEmPulse3E
{
private:
    struct ChannelFrame
    {
        Channel3E *channel;
        Value      value;
    };
    typedef std::vector<ChannelFrame> DataArray;

private:
    uint32_t     m_interval = 0;
    uint32_t     m_flags    = 0;
    DataArray    m_data;
    uint64_t     m_time     = 0;
    FrameTypeID  m_type     = FrameTypeID::SampleTypeCalib;

    FrameKey     m_key;


public:
    FrameEmPulse3E();
    FrameEmPulse3E(const FrameKey &key, const uint64_t &frame_time);
    FrameEmPulse3E(const FrameEmPulse3E &other);
    ~FrameEmPulse3E();
    void  operator = (const FrameEmPulse3E &value);
    
    // get interval, and etc    
    FrameKey&     Key();
    uint64_t&     Time();

    uint64_t      TimeGet() const;
    void          TimeSet(const uint64_t &val);

    uint32_t      IntervalGet() const;
    void          IntervalSet(uint32_t val);
    
    uint32_t      FlagsGet() const;
    void          FlagsSet(uint32_t flags);
    
    FrameTypeID   TypeGet() const;
    void          TypeSet(const FrameTypeID &type);

    // get data
    uint32_t      Count() const;
    const Channel3E&  GetChannel(uint32_t channel_pos) const;
    const Value&      GetValue(uint32_t channel_pos) const;

    Value*        Find(const ChannelID &channel_key);

    // add, remove data
    bool          Add(const Channel3E &channel, const Value &value);
    bool          Remove(uint32_t channel_pos);
    void          Clear();

private:
    void          Shutdown();
};