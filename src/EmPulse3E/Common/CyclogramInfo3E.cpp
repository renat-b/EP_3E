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
}




CyclogramInfo3E::CyclogramInfo3E(const CyclogramBase &cyclogram) : m_cyclogram(cyclogram)
{
}

CyclogramInfo3E::~CyclogramInfo3E()
{
}

uint32_t CyclogramInfo3E::Cycles(uint32_t pos_interval) const
{
    uint32_t cycles = m_cyclogram.Cycles(pos_interval);
    return cycles;
}
