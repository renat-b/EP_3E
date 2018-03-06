#include "StdAfx.h"
#include "Calibration3E.h"
#include "..\Common.h"

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

bool Calibration3E::Calibrate(double &val, uint32_t channel_id, const double &adc_voltage) const
{
    if (channel_id < 1 || channel_id > Channel2stMultiZHA)
        return false;

    const float *adc_ch_offset   = &m_table.adc_ch_0_offset; 
    const float *adc_ch_coeff    = &m_table.adc_ch_0_coeff;  
 
    adc_ch_offset += (channel_id - 1) * 2; 
    adc_ch_coeff  += (channel_id - 1) * 2;

    val = (adc_voltage - ((double)*adc_ch_offset)) * ((double)*adc_ch_coeff);
    val = NormalizeDouble(val, 3);
    return true;
}

double __fastcall Calibration3E::NormalizeDouble(const double val, UINT digits) const
{
    double dbl_integer;
    // �������� �����
    if (digits > 8) 
        digits = 8;
    // ������� ��������
    double p = s_decimal[digits];
    double dbl_fract = modf(val, &dbl_integer)*p;
    // ��������� ����
    if (val > 0) 
        dbl_fract += 0.5000001;
    else
        dbl_fract -= 0.5000001;
    // � ����������� ������� ����� (� 64 ������ ������ ��� �������� �������, ��� modf)
    dbl_fract = double(__int64(dbl_fract));
    // �����
    return(dbl_integer + dbl_fract / p);
}