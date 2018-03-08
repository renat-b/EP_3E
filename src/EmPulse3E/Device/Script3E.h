#pragma once

#include "CommonDevice3E.h"
#include "..\Common\ChannelInfo3E.h"
#include "..\..\Frame\Channel.h"

class Script3E
{
    friend class Cyclogram3E;

private:
    typedef std::vector<Channel> Channels;

    struct Measure
    {
        OperationMeasure3E operation;
        Channels         channels;        

        Measure();
        Measure(const Measure &other);
        void operator = (const Measure &other);

    };
    typedef std::vector<Measure>           Measures; 
    typedef std::vector<OperationImpulse3E>  Impulses;


private:
    Measures     m_measures;
    Impulses     m_impulses;

public:
    Script3E();
    Script3E(const Script3E &other);
    ~Script3E();

    void operator = (const Script3E &other);
   
    void        Shutdown();
    void        ChannelsCreate();

    uint32_t    MeasureCount() const;
    OperationMeasure3E &MeasureGet(uint32_t pos);

    uint32_t    ChannelCount(uint32_t pos_measure) const;
    Channel    &ChannelGet(uint32_t pos_measure, uint32_t pos_channel);

    uint32_t    ImpulseCount() const;
    OperationImpulse3E  ImpulseGet(uint32_t pos);


private:
    bool        MeasureAdd(const OperationMeasure3E &measure);
    void        ChannelAdd(uint32_t id, uint32_t flags, Measure &measure);

    void        ChannelAssign(Channel &channel, uint32_t id, uint32_t flags);
    void        MetaCreate(Channel &channel, const OperationMeasure3E &operation);
    void        MetaAssign(ChannelMetaInfo3E *meta, const Channel &channel, const OperationMeasure3E &operation);
};
