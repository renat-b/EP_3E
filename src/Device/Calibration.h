#pragma once

#include "..\Common\Value.h"


class Calibration
{
private:
    static float R_REF;

struct CalibrationTable
{
    float version    = 1.0;                     // Version of Calibration Table
    float reserved_1 = 0.0;                     // Reserved bytes

    // adc_code = (adc_voltage - adc_ch_offset) * adc_ch_coeff   //

    float adc_ch_0_offset   = 0.0;              // Channel 0 voltage offset on mV (VSH)
    float adc_ch_0_coeff    = 1.0;              // Channel 0 linear coefficient
    float adc_ch_1_offset   = 0.0;              // Channel 1 voltage offset on mV (VSL)
    float adc_ch_1_coeff    = 1.0;              // Channel 1 linear coefficient
    float adc_ch_2_offset   = 0.0;              // Channel 2 voltage offset on mV (SSH)
    float adc_ch_2_coeff    = 1.0;              // Channel 2 linear coefficient
    float adc_ch_3_offset   = 0.0;              // Channel 3 voltage offset on mV (SSL)
    float adc_ch_3_coeff    = 1.0;              // Channel 3 linear coefficient
    float adc_ch_4_offset   = 0.0;              // Channel 4 voltage offset on mV (ADC1_MUX0)
    float adc_ch_4_coeff    = 1.0;              // Channel 4 linear coefficient
    float adc_ch_5_offset   = 0.0;              // Channel 5 voltage offset on mV (ADC1_MUX1)
    float adc_ch_5_coeff    = 1.0;              // Channel 5 linear coefficient
    float adc_ch_6_offset   = 0.0;              // Channel 6 voltage offset on mV (ADC1_MUX2)
    float adc_ch_6_coeff    = 1.0;              // Channel 6 linear coefficient
    float adc_ch_7_offset   = 0.0;              // Channel 7 voltage offset on mV (ADC1_MUX3)
    float adc_ch_7_coeff    = 1.0;              // Channel 7 linear coefficient
    float adc_ch_8_offset   = 0.0;              // Channel 8 voltage offset on mV (ADC1_MUX4)
    float adc_ch_8_coeff    = 1.0;              // Channel 8 linear coefficient
    float adc_ch_9_offset   = 0.0;              // Channel 9 voltage offset on mV (ADC1_MUX5)
    float adc_ch_9_coeff    = 1.0;              // Channel 9 linear coefficient
    float adc_ch_10_offset  = 0.0;              // Channel 10 voltage offset on mV (ADC1_MUX6)
    float adc_ch_10_coeff   = 1.0;              // Channel 10 linear coefficient
    float adc_ch_11_offset  = 0.0;              // Channel 11 voltage offset on mV (ADC1_MUX7)
    float adc_ch_11_coeff   = 1.0;              // Channel 11 linear coefficient
    float adc_ch_12_offset  = 0.0;              // Channel 12 voltage offset on mV (ADC2_MUX0)
    float adc_ch_12_coeff   = 1.0;              // Channel 11 linear coefficient
    float adc_ch_13_offset  = 0.0;              // Channel 13 voltage offset on mV (ADC2_MUX1)
    float adc_ch_13_coeff   = 1.0;              // Channel 11 linear coefficient
    float adc_ch_14_offset  = 0.0;              // Channel 14 voltage offset on mV (ADC2_MUX2)
    float adc_ch_14_coeff   = 1.0;              // Channel 11 linear coefficient
    float adc_ch_15_offset  = 0.0;              // Channel 15 voltage offset on mV (ADC2_MUX3)
    float adc_ch_15_coeff   = 1.0;              // Channel 11 linear coefficient
    float adc_ch_16_offset  = 0.0;              // Channel 16 voltage offset on mV (ADC2_MUX4)
    float adc_ch_16_coeff   = 1.0;              // Channel 11 linear coefficient
    float adc_ch_17_offset  = 0.0;              // Channel 17 voltage offset on mV (ADC2_MUX5)
    float adc_ch_17_coeff   = 1.0;              // Channel 11 linear coefficient
    float adc_ch_18_offset  = 0.0;              // Channel 18 voltage offset on mV (ADC2_MUX6)
    float adc_ch_18_coeff   = 1.0;              // Channel 11 linear coefficient
    float adc_ch_19_offset  = 0.0;              // Channel 19 voltage offset on mV (ADC2_MUX7)
    float adc_ch_19_coeff   = 1.0;              // Channel 19 linear coefficient

    // dac_code = dac_value_offset - (current * 10000 * dac_value_coeff) 

    float dac_0_value_offset    = 66033.0;          // DAC_0 code offset (in digits)
    float dac_0_value_coeff     = 19.539f * R_REF;  // DAC_0 coeff
    float dac_1_value_offset    = 66033.0;          // DAC_1 code offset (in digits)
    float dac_1_value_coeff     = 19.539f * R_REF;  // DAC_0 coeff

    float control_point_offset  = 0.0;              // Control mesurement point offset (mV)
    float control_point_MSD     = 0.0;              // Control mesurement point MSD of Noise (uV)

    float air_exp_VS_amplitude  = 0.0;              // Amplitude of exponent on air, very long sensor (mV)
    float air_exp_VS_relax_time = 0.0;              // Relaxation time of exponent on air, very long sensor (ms)
    float air_exp_SS_amplitude  = 0.0;              // Amplitude of exponent on air, short sensor (mV)
    float air_exp_SS_relax_time = 0.0;              // Relaxation time of exponent on air, short sensor (ms)

    float al_exp_VS_amplitude   = 0.0;              // Amplitude of exponent in aluminium tube, very long sensor (mV)
    float al_exp_VS_relax_time  = 0.0;              // Relaxation time of exponent in aluminium tube, very long sensor (ms)
    float al_exp_SS_amplitude   = 0.0;              // Amplitude of exponent in aluminium tube, short sensor (mV)
    float al_exp_SS_relax_time  = 0.0;              // Relaxation time of exponent in aluminium tube, short sensor (ms)

    float reserved_56           = 0.0;
    float reserved_57           = 0.0;  
    float reserved_58           = 0.0;
    float reserved_59           = 0.0;
    float reserved_60           = 0.0;  
    float reserved_61           = 0.0; 
    float reserved_62           = 0.0; 
    float reserved_63           = 0.0; 
};


private:
    CalibrationTable  m_table;

public:
    Calibration();
    ~Calibration();

    bool  Load(const uint8_t *data, uint32_t size);
    bool  Calibrate(uint32_t channel_id, const Value &adc_val, Value &val) const;
};