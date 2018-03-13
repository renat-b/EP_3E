#pragma once

#include "MetaInfo.h"

class MetaInfoStorage
{
private:
    struct MetaInfo
    {
        IMetaInfo *object;
        MetaInfo  *next;
    };

private:
    MetaInfo  *m_head_meta_info = nullptr;

public:
    MetaInfoStorage();
    ~MetaInfoStorage();

    void operator = (const MetaInfoStorage &other);

    bool     MetaInfoGet(IMetaInfo **object, uint32_t id_meta_info) const;
    bool     MetaInfoAdd(IMetaInfo *object);

    void     Shutdown();
};