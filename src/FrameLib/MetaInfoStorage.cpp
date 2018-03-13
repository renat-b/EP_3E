#include "StdAfx.h"
#include "MetaInfoStorage.h"

MetaInfoStorage::MetaInfoStorage()
{

}

MetaInfoStorage::~MetaInfoStorage()
{

}

void MetaInfoStorage::operator = (const MetaInfoStorage &other)
{
    Shutdown();

    MetaInfo **next       = &m_head_meta_info; 
    MetaInfo  *next_other = other.m_head_meta_info;
    while (next_other)
    {
        if (!next_other->object)
            return;

        MetaInfo *info = new(std::nothrow) MetaInfo; 
        if (!info)
            return;

        info->object = next_other->object->Copy();
        info->next   = nullptr;
        if (!info->object)
            return;

        *next = info;

        next       = &((*next)->next);
        next_other = next_other->next;
    }
}
bool MetaInfoStorage::MetaInfoGet(IMetaInfo **object, uint32_t id_meta_info) const
{
    if (!object)
        return false;

    *object = nullptr; 

    MetaInfo *next = m_head_meta_info;
    while (next)
    {
        if (next->object->ID() == id_meta_info)
        {
            *object = next->object;
            return true;
        }
        next = next->next;                
    }
    return false;
}

bool MetaInfoStorage::MetaInfoAdd(IMetaInfo *object)
{
    if (!object)
        return false;

    MetaInfo **next = &m_head_meta_info;
    // search tail from list
    while (*next)
    {
        next = &(*next)->next;
    }

    MetaInfo *element_meta_info = new(std::nothrow) MetaInfo;
    if (!element_meta_info)
        return false;
    element_meta_info->object = object;
    element_meta_info->next   = nullptr;

    // set object
    *next = element_meta_info; 
    return true;
}

void MetaInfoStorage::Shutdown()
{
    MetaInfo *next = m_head_meta_info;
    while (next)
    {
        m_head_meta_info = next->next;
        if (next->object)
            delete next->object;
        delete next;
        next = m_head_meta_info;
    }
    m_head_meta_info = nullptr;
}
