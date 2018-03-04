#pragma once

#include "..\CommonEmPulse\ChannelID.h"

/*
Description of fields and their offsets
--------------------------------------------------------------------------------------------
| name field |  Inherited   |  Flags   |   Scale  |  Start Point |  Num Point  |  Reserved |
--------------------------------------------------------------------------------------------
| bit offset |  63 - 47     |  47 - 45 |  44 - 42 |  41 - 30     |  29 - 18    |  17 - 0   |
--------------------------------------------------------------------------------------------
| amount bits|     16       |     3    |     3    |     12       |     12      |    18     |
--------------------------------------------------------------------------------------------
*/

class ChannelID_3E : public ChannelID
{
private:
    enum Flags
    {
        FlagsBase   = 0x1,
        Flags1Multi = 0x2,
        Flags2Multi = 0x4,
        FlagsDecay  = 0x8,
    };

public:
    bool     IsBase() const;
    void     SetBase(bool set);

    bool     IsDecay() const;
    void     SetDecay(bool set);

    bool     Is1Multi() const;
    void     Set1Multi(bool set);

    bool     Is2Multi() const;
    void     Set2Multi(bool set);

    uint8_t  GetScale() const;
    void     SetScale(uint8_t val);

    uint16_t GetStartPoint() const;
    void     SetStartPoint(uint16_t val);

    uint16_t GetNumPoint() const;
    void     SetNumPoint(uint16_t val);
};


inline bool ChannelID_3E::IsBase() const
{
    uint64_t mask = 0xE00000000000;
    uint8_t  val  = (uint8_t)(((m_data & mask) >> 45));

    if (val & FlagsBase)
        return true;
    return false;
}

inline void ChannelID_3E::SetBase(bool set)
{
    uint64_t mask = 0xE00000000000;
    uint8_t  val = (uint8_t)(((m_data & mask) >> 45));
    
    if (set)
        val |= FlagsBase;
    else
        val &= ~FlagsBase;

    m_data |= ((((uint64_t)val) << 45) & mask);
}

inline bool ChannelID_3E::Is1Multi() const
{
    uint64_t mask = 0xE00000000000;
    uint8_t  val  = (uint8_t)(((m_data & mask) >> 45));

    if (val & Flags1Multi)
        return true;
    return false;
}

inline void ChannelID_3E::Set1Multi(bool set)
{
    uint64_t mask = 0xE00000000000;
    uint8_t  val = (uint8_t)(((m_data & mask) >> 45));
    
    if (set)
        val |= Flags1Multi;
    else
        val &= ~Flags1Multi;

    m_data |= ((((uint64_t)val) << 45) & mask);
}

inline bool ChannelID_3E::Is2Multi() const
{
    uint64_t mask = 0xE00000000000;
    uint8_t  val  = (uint8_t)(((m_data & mask) >> 45));

    if (val & Flags2Multi)
        return true;
    return false;
}

inline void ChannelID_3E::Set2Multi(bool set)
{
    uint64_t mask = 0xE00000000000;
    uint8_t  val = (uint8_t)(((m_data & mask) >> 45));
    
    if (set)
        val |= Flags2Multi;
    else
        val &= ~Flags2Multi;

    m_data |= ((((uint64_t)val) << 45) & mask);
}

inline bool ChannelID_3E::IsDecay() const
{
    uint64_t mask = 0xE00000000000;
    uint8_t  val  = (uint8_t)(((m_data & mask) >> 45));

    if (val & FlagsDecay)
        return true;
    return false;
}

inline void ChannelID_3E::SetDecay(bool set)
{
    uint64_t mask = 0xE00000000000;
    uint8_t  val = (uint8_t)(((m_data & mask) >> 45));
    
    if (set)
        val |= FlagsDecay;
    else
        val &= ~FlagsDecay;

    m_data |= ((((uint64_t)val) << 45) & mask);
}

inline uint8_t ChannelID_3E::GetScale() const
{
    uint64_t mask = 0x1C0000000000;
    uint8_t  val = (uint8_t)(((m_data & mask) >> 42));

    return val;
}

inline void ChannelID_3E::SetScale(uint8_t val)
{
    uint64_t mask = 0x1C0000000000;

    m_data |= ((((uint64_t)val) << 42) & mask);
}

inline uint16_t ChannelID_3E::GetStartPoint() const
{
    uint64_t mask = 0x3FFC0000000;
    uint16_t  val = (uint16_t)(((m_data & mask) >> 30));

    return val;
}

inline void ChannelID_3E::SetStartPoint(uint16_t val)
{
    uint64_t mask = 0x3FFC0000000;
    m_data |= ((((uint64_t)val) << 30) & mask);
}

inline uint16_t ChannelID_3E::GetNumPoint() const
{
    uint64_t mask = 0x3FFC0000;
    uint16_t  val = (uint16_t)(((m_data & mask) >> 18));

    return val;
}

inline void ChannelID_3E::SetNumPoint(uint16_t val)
{
    uint64_t mask = 0x3FFC0000;
    m_data |= ((((uint64_t)val) << 18) & mask);
}