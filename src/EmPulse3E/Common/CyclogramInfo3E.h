#pragma once

#include "EmPulse3E/Device/Cyclogram3E.h"
#include "FrameLib/MetaInfo.h"
#include "FrameLib/CyclogramBase.h"

class CyclogramMetaInfo3E : public IMetaInfo
{
private:
    typedef std::vector<uint32_t> CyclosOfInterval;

private:
    CyclosOfInterval  m_cyclos;

public:
    enum ID_Constants
    {
        ID_EmPulse3E = 1,
    };

public:
    CyclogramMetaInfo3E();
    CyclogramMetaInfo3E(const CyclogramMetaInfo3E &other);

public:
    virtual ~CyclogramMetaInfo3E();
    virtual  uint32_t   ID()   const override;
    virtual  IMetaInfo *Copy() const override;

public:
    void operator = (const CyclogramMetaInfo3E& other);
    
    uint32_t Cyclos(uint32_t pos_interval) const;

    bool     Create(Cyclogram3E &cyclogram);
};


class CyclogramInfo3E
{
private:
    const CyclogramBase &m_cyclogram;

public:
    CyclogramInfo3E(const CyclogramBase &cyclogram);
    ~CyclogramInfo3E();
    
    uint32_t    GetCyclos(uint32_t pos_interval) const;
};