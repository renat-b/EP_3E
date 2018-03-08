#pragma once

#include "..\Device\Cyclogram3E.h"
#include "..\Frames\Frame.h"
#include "..\Device\CyclogramBase.h"

class NotifierParserBase
{
public:
    enum
    {
        FLAG_NOTIFY_BEGIN = 0x01,
        FLAG_NOTIFY_END   = 0x02,
    };

public:
    virtual bool   OnParse(uint32_t flags) = 0;
    virtual bool OnCyclogram(const CyclogramBase &cyclo) = 0;

    virtual bool   OnCyclo(uint32_t flags) = 0;
    virtual bool   OnFrame(const Frame &frame) = 0;
};
