#include "StdAfx.h"
#include "Calibration.h"

float Calibration::R_REF = 0.2f;

Calibration::Calibration()
{
}

Calibration::~Calibration()
{
}

bool Calibration::Load(const uint8_t *data, uint32_t size)
{
    if (!data || !size)
        return false;

    if (size > sizeof(m_table))
        return false;
    
    if (!memcpy(&m_table, data, size))
        return false;

    return true;
}

bool Calibration::Calibrate(uint32_t channel_id, const Value &adc_val, Value &val) const
{
    return false;
}
