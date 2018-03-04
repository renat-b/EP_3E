#pragma once

#include "Sample.h"

class Rule
{
public:
    Rule();
    ~Rule();

    virtual bool Execute(Sample& sample);
};
