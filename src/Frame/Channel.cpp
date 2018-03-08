#include "StdAfx.h"
#include "Channel.h"

Channel::Channel()
{
}

Channel::Channel(const Channel &other)
{
    *this = other;
}

Channel::~Channel()
{
}

void Channel::operator = (const Channel &other)
{
    m_id    = other.m_id;
    m_flags = other.m_flags;
    m_single_point   = other.m_single_point;
    m_multi_point    = other.m_multi_point;
    m_storage        = other.m_storage;    
}

uint32_t Channel::IDGet() const
{
    return m_id;
}

void Channel::IDSet(uint32_t id)
{
    m_id = id;
}

uint32_t Channel::FlagsGet() const
{
    return m_flags;
}

void Channel::FlagsSet(uint32_t flags)
{
    m_flags = flags;
}

bool Channel::SinglePointIs() const
{
    return m_single_point;
}

void Channel::SinglePointSet(bool single)
{
    m_single_point = single;
}

bool Channel::MultiPointIs() const
{
    return m_multi_point;
}

void Channel::MultiPointSet(bool multi)
{
    m_multi_point = multi;
}

bool Channel::MetaInfoGet(IMetaInfo **object, uint32_t id_meta_info) const
{
    bool r = m_storage.MetaInfoGet(object, id_meta_info);
    return r;
}

bool Channel::MetaInfoAdd(IMetaInfo *object)
{
    bool r = m_storage.MetaInfoAdd(object);
    return r;
}