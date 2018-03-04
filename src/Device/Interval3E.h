#pragma once

#include "..\CommonDevice.h"
#include "Script3E.h"

class Interval3E
{
    friend class Cyclogram3E;

private:
    Interval   m_interval;
    Script3E   m_script;

public:
    Interval3E();
    Interval3E(const Interval3E &other);
    ~Interval3E();

    void operator=(const Interval3E &other);

    uint32_t   ScrTim() const;   
    uint32_t   Pause()  const;    
    uint32_t   Cycles() const;   
    uint32_t   CycCnt() const;   

    Script3E &ScriptGet();
};
