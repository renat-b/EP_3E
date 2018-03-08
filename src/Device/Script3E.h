#pragma once

#include "..\CommonDevice3E.h"
#include "ChannelInfo3E.h"
#include "Channel.h"

class Script3E
{
    friend class Cyclogram3E;

private:
    typedef std::vector<Channel> Channels;

    struct Measure
    {
        OperationMeasure operation;
        Channels         channels;        

        Measure();
        Measure(const Measure &other);
        void operator = (const Measure &other);

    };
    typedef std::vector<Measure>           Measures; 
    typedef std::vector<OperationImpulse>  Impulses;


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
    OperationMeasure &MeasureGet(uint32_t pos);

    uint32_t    ChannelCount(uint32_t pos_measure) const;
    Channel    &ChannelGet(uint32_t pos_measure, uint32_t pos_channel);

    uint32_t    ImpulseCount() const;
    OperationImpulse  ImpulseGet(uint32_t pos);


private:
    bool        MeasureAdd(const OperationMeasure &measure);
    void        ChannelAdd(uint32_t id, uint32_t flags, Measure &measure);

    void        ChannelAssign(Channel &channel, uint32_t id, uint32_t flags);
    void        MetaCreate(Channel &channel, const OperationMeasure &operation);
    void        MetaAssign(ChannelMetaInfo3E *meta, const Channel &channel, const OperationMeasure &operation);
};
