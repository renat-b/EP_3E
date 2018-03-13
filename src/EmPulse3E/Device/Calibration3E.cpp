#include "StdAfx.h"
#include "Calibration3E.h"
#include "EmPulse3E/Common3E.h"

float Calibration3E::R_REF = 0.2f;

const __declspec(selectany) double Calibration3E::s_decimal[10] =
{
    1.0,
    10.0,
    100.0,
    1000.0,
    10000.0,
    100000.0,
    1000000.0,
    10000000.0,
    100000000.0,
    1000000000.0,
};

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

bool Calibration3E::Calibrate(double &val, uint32_t channel_id, const double adc_voltage) const
{
    if (channel_id < ChannelBase_SSL || channel_id > ChannelLast)
        return false;

    const float *adc_ch_offset = &m_table.adc_ch_base0_offset; 
    const float *adc_ch_coeff  = &m_table.adc_ch_base0_coeff;  

    double  ch_offset = adc_ch_offset[(channel_id) * 2];
    double  ch_coeff  = adc_ch_coeff[(channel_id) * 2];
   
    val = (adc_voltage - ch_offset) * ch_coeff;
    val = NormalizeDouble(val, 5);
    return true;
}

double __fastcall Calibration3E::NormalizeDouble(const double val, UINT digits) const
{
    double dbl_integer;
    // проверим знаки
    if (digits > 8) 
        digits = 8;
    // получим делители
    double p = s_decimal[digits];
    double dbl_fract = modf(val, &dbl_integer)*p;
    // проверяем знак
    if (val > 0) 
        dbl_fract += 0.5000001;
    else
        dbl_fract -= 0.5000001;
    // и преобразуем дробную часть (в 64 битной версии это работает быстрее, чем modf)
    dbl_fract = double(__int64(dbl_fract));
    // итого
    return(dbl_integer + dbl_fract / p);
}