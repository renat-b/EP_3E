#pragma once

/*
Description of fields and their offsets
-----------------------------------------------
| name field |    ID   |  Flags   |  Reserved |
-----------------------------------------------
| bit offset | 63 - 56 |  55 - 48 |  47 - 0   |
-----------------------------------------------
| amount bits|    8    |     8    |    48     |
-----------------------------------------------
*/


class ChannelID
{
protected:
    uint64_t  m_data;

public:
    ChannelID();

    bool operator==(const ChannelID &other);

    uint8_t  IDGet() const;
    void     IDSet(uint8_t id); 

    uint8_t FlagsGet() const;
    void     FlagsSet(uint8_t flags);

    void     Clear();
};


inline ChannelID::ChannelID() : m_data(0)
{
}


inline bool ChannelID::operator==(const ChannelID &other)
{
    return m_data == other.m_data;
}

inline uint8_t ChannelID::IDGet() const
{
    uint64_t mask = 0xFF00000000000000;
    uint8_t  id   = (uint8_t)(((m_data & mask) >> 56));

    return id;
}

inline void ChannelID::IDSet(uint8_t id)
{
    uint64_t mask = 0xFF00000000000000;
    m_data |= ((((uint64_t)id) << 56) & mask); 
}

inline uint8_t ChannelID::FlagsGet() const
{
    uint64_t mask  = 0xFF000000000000;
    uint8_t  flags = (uint8_t)(((m_data & mask) >> 48));

    return flags;
}

inline void ChannelID::FlagsSet(uint8_t flags)
{
    uint64_t mask = 0xFF000000000000;
    m_data |= ((((uint64_t)flags) << 48) & mask); 
}

inline void ChannelID::Clear()
{
    m_data = 0;
}