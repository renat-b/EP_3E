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
    m_id      = other.m_id;
    m_flags   = other.m_flags;
    m_points  = other.m_points;
    m_storage = other.m_storage;    
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

uint32_t Channel::Points() const
{
    return m_points;
}

void Channel::PointsSet(uint32_t points)
{
    m_points = points;
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