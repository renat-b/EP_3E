#pragma once

#include "CommonDevice3E.h"


class TimeScale3E
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
    TimeScale3E();
    ~TimeScale3E();

    uint32_t   AmountOfPointsGet(ScaleVariantInner3E scale, uint32_t num_point) const;
    double     MsGet(ScaleVariantInner3E scale, uint32_t num_point) const;
};

