#pragma once

#include "CommonLibEmPulse/StreamBuffer.h"
#include "Interval3E.h"

class Cyclogram3E
{
private:
    typedef std::vector<Interval3E> IntervalArray;

private:
    uint16_t         m_version;    
    IntervalArray    m_intervals;

    StreamBuffer     m_convertor;

public:
    Cyclogram3E();
    ~Cyclogram3E();
    
    void   Shutdown();
    bool   Load(const uint8_t *data, uint32_t size);

    uint32_t    IntervalCount() const;
    Interval3E &IntervalGet(uint32_t interval_pos);


private:
    bool   ParseInterval();
    bool   ParseScript(Interval3E &interval);

    void   PrintMeasure(OperationMeasure3E &measure, uint32_t measure_pos);
};
