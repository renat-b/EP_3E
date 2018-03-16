#include "StdAfx.h"
#include "Interval3E.h"

Interval3E::Interval3E()
{
}


Interval3E::Interval3E(const Interval3E &other)
{
    *this = other;
}

Interval3E::~Interval3E()
{
}


void Interval3E::operator=(const Interval3E &other)
{
    m_interval = other.m_interval; 
    m_script   = other.m_script;
}

uint32_t Interval3E::ScrTim() const
{
    uint32_t val = m_interval.ScrTim.Get();
    return val;
}

uint32_t Interval3E::Pause() const
{
    uint32_t val = m_interval.Pause.Get();
    return val;
}

uint32_t Interval3E::Cycles() const
{
    uint32_t val = m_interval.Cycles.Get();
    return val;
}

uint32_t Interval3E::CyclesReal() const
{
    uint32_t val = m_interval.CycCnt.Get();
    return val;
}

Script3E &Interval3E::ScriptGet()
{
    return m_script;
}