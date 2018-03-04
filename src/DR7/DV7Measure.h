#pragma once

#include "..\Device\Channel3E.h"
#include "..\Device\Cyclogram3E.h"
#include "..\Common\Value.h"

class DV7Measure;

enum class DV7ResultCode
{
    RESULT_SUCCESS  = 1,
    RESULT_FAILED   = 2,
    RESULT_END_OF_DATA = 3,
};

class DV7Channel3E : public Channel3E
{
private:
    uint32_t    m_point_pos;
    Value       m_value;
    DV7Measure* m_parent;

public:
    DV7Channel3E(const Channel3E& channel);
    DV7Channel3E(const DV7Channel3E& other);
    virtual ~DV7Channel3E();

    void          operator = (const DV7Channel3E& other);

    uint32_t      PointPos() const;
    DV7ResultCode Parse(StreamFile& convertor);
    void          InitSample(DV7Measure* measure);

    void          Assign(const DV7Channel3E& other);


private:
    bool          ValueCreate();
    bool          ValueAssign(const double& val);

    bool          IsEndOfPoints();
    uint32_t      AmountOfSavingCalc();
};


class DV7Measure
{
private:
    typedef std::vector<DV7Channel3E>  DV7Channel3EArray;    
    typedef std::vector<DV7Channel3E*> DV7Channel3PtrEArray;


private:
    DV7Channel3EArray    m_channels; 
    DV7Channel3PtrEArray m_channels_stack;        
    uint32_t             m_channel_pos;


public:
    DV7Measure();
    ~DV7Measure();
    
    void   Clear();
    void   InitSample();   
    bool   ChannelAdd(Channel3E& channel);

    bool   ChannelAdd(DV7Channel3E* channel);
    void   ChannelRemove(const DV7Channel3E* channel);
    void   ChannelNext();

    DV7ResultCode  Parse(StreamFile& convertor);

private:
    DV7Channel3E* Next();
};


class DV7ContrainterMeasure
{
private:
    typedef std::vector<DV7Measure> DV7MeasureArray;

    struct DV7Interval
    {
        DV7Interval(uint32_t pos) : interval_pos(pos) { };

        uint32_t         interval_pos;
        DV7MeasureArray  measures; 
    };
    typedef std::vector<DV7Interval> Intervals;


private:
    Intervals   m_intervals;

public:
    DV7ContrainterMeasure();
    ~DV7ContrainterMeasure();

    bool     Create(Cyclogram3E& cyclo);
    void     Clear();
    bool     Parse(uint32_t interval_pos, StreamFile& convertor);

private:
    uint32_t MeasureFind(uint32_t interval_pos);
    bool     ParseInterval(DV7Interval& interval, StreamFile& convertor);
    void     InitSample(DV7Interval& interval);
};

