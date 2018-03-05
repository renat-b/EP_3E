#include "StdAfx.h"
#include "Calibration3E.h"
#include "..\Common.h"

float Calibration3E::R_REF = 0.2f;

Calibration3E::Calibration3E()
{
}

Calibration3E::~Calibration3E()
{
}

bool Calibration3E::Load(const uint8_t *data, uint32_t size)
{
    if (!data || !size)
        return false;

    if (size > sizeof(m_table))
        return false;
    
    if (!memcpy(&m_table, data, size))
        return false;

    return true;
}

bool Calibration3E::Calibrate(double &val, uint32_t channel_id, const double &adc_voltage) const
{
    if (channel_id < 1 || channel_id > Channel2stMultiZHA)
        return false;

    const float *adc_ch_offset   = &m_table.adc_ch_0_offset; 
    const float *adc_ch_coeff    = &m_table.adc_ch_0_coeff;  
 
    adc_ch_offset += (channel_id - 1); 
    adc_ch_coeff  += (channel_id - 1);

    val = (adc_voltage - ((double)*adc_ch_offset)) * ((double)*adc_ch_coeff);

    return true;
}
