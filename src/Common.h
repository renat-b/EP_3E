#pragma once

enum ChannelKeyID
{
    ChannelBase_SSL = 0,        // SS signal low ampl.
    ChannelBase_VSL,            // VS signal low ampl.
    ChannelBase_SSH,            // SS signal high ampl.
    ChannelBase_VSH,            // VS signal high ampl.
    ChannelBaseLast = ChannelBase_VSH, 

    Channel1stMultiFXMinus,     // - Gs mGs 0 0.164 Magn.field X sens.
    Channel1stMultiFXPlus,      // + Gs mGs 0 - 0.164 Magn.field X sens.
    Channel1stMultiVJE,         // mA uA 0 1 VS exc.current
    Channel1stMultiSJE,         // mA uA 0 1 SS exc.current
    Channel1stMultiTin,         // degC degC 0 1 Internal temperature
    Channel1stMultiAcX,         // mV uV 452 1 Accelerometer X
    Channel1stMultiSpd,         // mV uV 0 1 Speed deviation
    Channel1stMultiVHA,         // mV uV 0 1 VS signal high ampl.
    Channel1stMultiLast = Channel1stMultiVHA,

    Channel2stMultiFYMinus,     // Gs mGs 0 0.164 Magn.field Y sens.
    Channel2stMultiFYPlus,      // Gs mGs 0 - 0.164 Magn.field Y sens.
    Channel2stMultiUbt,         // V mV - 2048 0.006357 Battery voltage
    Channel2stMulti1_8v,        // V mV - 2048 0.001 + 1.8V power voltage
    Channel2stMultiTex,         // degC degC 0 1 External temperature
    Channel2stMultiAcY,         // mV uV 452 1 Accelerometer Y
    Channel2stMultiAcZ,         // mV uV 452 1 Accelerometer Z
    Channel2stMultiSHA,         // mV uV 0 1 SS signal high ampl.
    ChannelLast = Channel2stMultiSHA,
};

enum ChannelFlags
{
   ChannelFlagSingleMeasure = 0x1, 
   ChannelFlag1stMulti      = 0x2,
   ChannelFlag2ndMulti      = 0x4,
   ChannelFlagDecayMeasure  = 0x8,
};

