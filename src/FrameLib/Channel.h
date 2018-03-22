#pragma once

#include "MetaInfoStorage.h"

class Channel
{
private:
    uint32_t   m_id     = 0;
    uint32_t   m_flags  = 0;
    uint32_t   m_points = 1;
    MetaInfoStorage  m_storage;

public:
    Channel();
    Channel(const Channel &other);
    ~Channel();
    
    void operator = (const Channel &other);

    uint32_t IDGet() const;
    void     IDSet(uint32_t id);

    uint32_t FlagsGet() const;
    void     FlagsSet(uint32_t flags);

    uint32_t Points() const;
    void     PointsSet(uint32_t points);

    bool     MetaInfoGet(IMetaInfo **object, uint32_t id_meta_info) const;
    bool     MetaInfoAdd(IMetaInfo *object);
};