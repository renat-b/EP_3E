#pragma once

class IMetaInfo
{
public:
    virtual ~IMetaInfo() {};

    virtual  uint32_t   ID()   const = 0;
    virtual  IMetaInfo *Copy() const = 0;
};