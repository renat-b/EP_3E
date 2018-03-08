#pragma once

#include "MetaInfoStorage.h"

class Channel
{
private:
    uint32_t   m_id    = 0;
    uint32_t   m_flags = 0;
    bool       m_single_point   = true;
    bool       m_multi_point    = false;
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

    bool     SinglePointIs() const;
    void     SinglePointSet(bool single);

    bool     MultiPointIs() const;
    void     MultiPointSet(bool multi);

    bool     MetaInfoGet(IMetaInfo **object, uint32_t id_meta_info) const;
    bool     MetaInfoAdd(IMetaInfo *object);
};
