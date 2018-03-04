#pragma once

#include "Frames.h"

class Sample
{
private:
    typedef std::vector<Frames> FrameArray;

private:
    FrameArray m_frames;

public:
    Sample();
    ~Sample();
   
    uint32_t  Count() const;
    Frames&   Get(uint32_t pos);
    Frames*   Find(const FrameKey& key);

    bool      Add(const Frames& frame);
    bool      Remove(uint32_t pos);
};
