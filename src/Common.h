#pragma once

enum ChannelKeyID
{
    ChannelBase_SLA = 1,        // SS signal low ampl.
    ChannelBase_VLA = 2,        // VS signal low ampl.
    ChannelBase_SHA = 3,        // SS signal high ampl.
    ChannelBase_VHA = 4,        // VS signal high ampl.
    ChannelBaseLast = ChannelBase_SHA, 

    Channel1stMultiFXPlus,      // - Gs mGs 0 0.164 Magn.field X sens.
    Channel1stMultiFXMinus,     // + Gs mGs 0 - 0.164 Magn.field X sens.
    Channel1stMultiVJE,         // mA uA 0 1 VS exc.current
    Channel1stMultiSJE,         // mA uA 0 1 SS exc.current
    Channel1stMultiTin,         // degC degC 0 1 Internal temperature
    Channel1stMultiAcX,         // mV uV 452 1 Accelerometer X
    Channel1stMultiSpd,         // mV uV 0 1 Speed deviation
    Channel1stMultiVHA,         // mV uV 0 1 VS signal high ampl.
    Channel1stMultiLast = Channel1stMultiVHA,    

    Channel2stMultiFY_Plus,     // Gs mGs 0 0.164 Magn.field Y sens.
    Channel2stMultiFY_Minus,    // Gs mGs 0 - 0.164 Magn.field Y sens.
    Channel2stMultiUbt,         // V mV - 2048 0.006357 Battery voltage
    Channel2stMulti1_8,         // V mV - 2048 0.001 + 1.8V power voltage
    Channel2stMultiTex,         // degC degC 0 1 External temperature
    Channel2stMultiAcY,         // mV uV 452 1 Accelerometer Y
    Channel2stMultiAcZ,         // mV uV 452 1 Accelerometer Z
    Channel2stMultiZHA,         // mV uV 0 1 SS signal high ampl.
};

enum ChannelFlags
{
   ChannelFlagSingleMeasure = 0x1, 
   ChannelFlag1stMulti      = 0x2,
   ChannelFlag2ndMulti      = 0x4,
   ChannelFlagDecayMeasure  = 0x8,
};

