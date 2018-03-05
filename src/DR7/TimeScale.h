#pragma once

#include "..\CommonDevice.h"


class TimeScale
{
private:
    struct ScaleLogInfo
    {
        double    ms;                   // соответствие ms
        uint32_t  point_start;          // стартовая точка
        uint32_t  amount_of_saving;     // колво накоплений
    };

private:
    static ScaleLogInfo s_scale_32_log[];
    static ScaleLogInfo s_scale_32_log_50Hz[];
    static ScaleLogInfo s_scale_32_log_60Hz[];

    static ScaleLogInfo s_scale_16_log[];
    static ScaleLogInfo s_scale_16_log_50Hz[];
    static ScaleLogInfo s_scale_16_log_60Hz[];

public:
    TimeScale();
    ~TimeScale();

    uint32_t   AmountOfPointsGet(ScVar scale, uint32_t num_point) const;
    //bool   GetMs(const DV7Channel3E& channel, double& ms) const;

};

