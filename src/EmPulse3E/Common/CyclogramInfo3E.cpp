#include "StdAfx.h"
#include "CyclogramInfo3E.h"
#include "FrameLib/MetaInfo.h"

CyclogramMetaInfo3E::CyclogramMetaInfo3E()
{

}

CyclogramMetaInfo3E::CyclogramMetaInfo3E(const CyclogramMetaInfo3E &other)
{
    *this = other;
}

CyclogramMetaInfo3E::~CyclogramMetaInfo3E()
{

}

uint32_t CyclogramMetaInfo3E::ID() const
{
    return ID_EmPulse3E;
}

IMetaInfo *CyclogramMetaInfo3E::Copy() const
{
    CyclogramMetaInfo3E *meta = new(std::nothrow) CyclogramMetaInfo3E;
    if (!meta)
        return nullptr;

    *meta = *this;
    return meta;
}

void CyclogramMetaInfo3E::operator=(const CyclogramMetaInfo3E& other)
{
    m_cyclos = other.m_cyclos;
}

uint32_t CyclogramMetaInfo3E::Cyclos(uint32_t pos_interval) const
{
    if (pos_interval >= m_cyclos.size())
        return 0;

    uint32_t cyclos = m_cyclos[pos_interval];
    return cyclos;
}

bool CyclogramMetaInfo3E::Create(Cyclogram3E &cyclogram)
{
    m_cyclos.clear();

    for (uint32_t i = 0; i < cyclogram.IntervalCount(); i++)
    {
        Interval3E &interval = cyclogram.IntervalGet(i);
    
        m_cyclos.push_back(interval.CycCnt());
    }
    return true;
}




CyclogramInfo3E::CyclogramInfo3E(const CyclogramBase &cyclogram) : m_cyclogram(cyclogram)
{
}

CyclogramInfo3E::~CyclogramInfo3E()
{
}

uint32_t CyclogramInfo3E::GetCyclos(uint32_t pos_interval) const
{
    CyclogramMetaInfo3E *meta = nullptr; 

    if (!m_cyclogram.MetaInfoGet((IMetaInfo **)&meta, CyclogramMetaInfo3E::ID_EmPulse3E))
        return 0;

    uint32_t cyclos = meta->Cyclos(pos_interval);
    return cyclos;
}
