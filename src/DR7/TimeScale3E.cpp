#include "StdAfx.h"
#include "TimeScale3E.h"

TimeScale3E::ScaleLogInfo TimeScale3E::s_scale_32_log[] = 
{
{  0.135, 	12,	    4     },
{  0.180, 	16,	    5     },
{  0.235, 	21,	    6     }, 
{  0.315, 	29,	    6     },
{  0.365, 	35,	    4     },
{  0.420, 	39,	    7     },
{  0.485, 	46,	    6     },
{  0.560, 	54,	    5     },
{  0.605, 	59,	    4     },
{  0.650, 	63,	    5     },
{  0.700, 	68,	    5     },
{  0.750, 	73,	    5     },
{  0.805, 	78,	    6     },
{  0.865, 	84,	    6     },
{  0.930, 	90,	    7     },
{  1.000, 	97,	    7     },
{  1.075, 	104,	8     },
{  1.155, 	112,	8     },
{  1.240, 	120,	9     },
{  1.335, 	129,	10    },
{  1.435, 	139,	10    },
{  1.540, 	149,	11    },
{  1.655, 	160,	12    },
{  1.780, 	172,	13    },
{  1.910, 	185,	13    },
{  2.055, 	198,	16    },
{  2.205, 	214,	14    },
{  2.370, 	228,	19    },
{  2.550, 	247,	17    },
{  2.740, 	264,	21    },
{  2.945, 	285,	20    },
{  3.160, 	305,	23    },
{  3.400, 	328,	25    },
{  3.650, 	353,	25    },
{  3.925, 	378,	30    },
{  4.215, 	408,	28    },
{  4.530, 	436,	35    },
{  4.870, 	471,	33    },
{  5.235, 	504,	40    },
{  5.625, 	544,	38    },
{  6.045, 	582,	46    },
{  6.495, 	628,	44    },
{  6.980, 	672,	53    },
{  7.500, 	725,	51    },
{  8.060, 	776,	61    },
{  8.660, 	837,	59    },
{  9.305, 	896,	70    },
{  10.000,	966,	69    },
{  10.745,	1035,	80    },
{  11.550,	1115,	81    },
{  12.410,	1196,	91    },
{  13.335,	1287,	94    },
{  14.330,	1381,	105   },
{  15.400,	1486,	109   },
{  16.550,	1595,	121   },
{  17.785,	1716,	126   },
{  19.110,	1842,	139   },
{  20.535,	1981,	146   },
{  22.065,	2127,	160   },
{  23.715,	2287,	170   },
{  25.485,	2457,	184   },
{  27.385,	2641,	196   },
{  29.425,	2837,	212   },
{  31.625,	3049,	228   },
{  33.980,	3277,	243   },
{  36.515,	3520,	264   },
{  39.240,	3784,	281   },
{  42.170,	4065,	305   },
{  45.315,	4370,	324   },
{  48.695,	4694,	352   },
{  52.330,	5046,	375   },
{  56.235,	5421,	406   },
{  60.430,	5827,	433   },
{  64.940,	6260,	469   },
{  69.785,	6729,	500   },
{  74.990,	7229,	541   },
{  80.585,	7770,	578   },
{  86.595,	8348,	624   },
{  93.055,	8972,	668   },
{  100.00,	9640,	721   },
{  107.46,	10361,	771   },
{  115.48,	11132,	833   },
{  124.10,	11965,	890   },
{  133.35,	12855,	961   },
{  143.30,	13816,	1029  },
{  154.00,	14845,	1110  },
{  165.48,	15955,	1187  },
{  177.83,	17142,	1283  },
{  191.10,	18425,	1370  },
{  205.36,	19795,	1482  },
{  220.68,	21277,	1582  },
{  237.14,	22859,	1710  },
{  254.83,	24569,	1829  },
{  273.84,	26398,	1973  },
{  294.28,	28371,	2114  },
{  316.23,	30485,	2277  },
{  339.82,	32762,	2441  },
{  365.18,	35203,	2630  },
{  392.42,	37833,	2819  },
{  421.70,	40652,	3036  },
{  453.16,	43688,	3257  },
{  486.97,	46945,	3505  },
{  523.30,	50450,	3761  },
{  562.34,	54211,	4047  },
{  604.30,	58258,	4344  },
{  649.38,	62602,	4673  },
{  697.83,	67275,	5017  },
{  749.90,	72292,	5396  },
{  805.84,	77688,	5793  },
{  865.97,	83481,	6232  },
{  930.57,	89713,	6689  },
{  1000.0,	96402,	7197  },
{  1074.6,	103599,	7725  },
{  1154.8,	111324,	8309  },
{  1240.9,	119633,	8923  },
{  1334.5,	128556,	9593  },
{  1433.0,	138149,	10306 },
{  1539.9,	148455,	11076 },
{  1654.8,	159531,	11902 },
{  1778.3,	171433,	12791 },
{  1911.0,	184224,	13744 },
{  2053.5,	197968,	14770 },
{  2206.7,	212738,	15872 },
{  2371.4,	228610,	17056 },
{  2548.3,	245666,	18328 },
{  2738.4,	263994,	19697 },
{  2942.7,	283691,	21164 },
{  3162.3,	327601,	22747 },
};


TimeScale3E::ScaleLogInfo TimeScale3E::s_scale_32_log_50Hz[] = 
{
{  0.135,	12,	    4      },
{  0.180,	16,	    5      },
{  0.235,	21,	    6      },
{  0.315,	29,	    6      },
{  0.365,	35,	    4      },
{  0.420,	39,	    7      },
{  0.485,	46,	    6      },
{  0.560,	54,	    5      },
{  0.605,	59,	    4      },
{  0.650,	63,	    5      },
{  0.700,	68,	    5      },
{  0.750,	73,	    5      },
{  0.805,	78,	    6      },
{  0.865,	84,	    6      },
{  0.930,	90,	    7      },
{  1.000,	97,	    7      },
{  1.075,	104,	8      },
{  1.155,	112,	8      },
{  1.240,	120,	9      },
{  1.335,	129,	10     },
{  1.435,	139,	10     },
{  1.540,	149,	11     },
{  1.655,	160,	12     },
{  1.780,	172,	13     },
{  1.910,	185,	13     },
{  2.055,	198,	16     },
{  2.205,	214,	14     },
{  2.370,	228,	19     },
{  2.550,	247,	17     },
{  2.740,	264,	21     },
{  2.945,	285,	20     },
{  3.160,	305,	23     },
{  3.400,	328,	25     },
{  3.650,	353,	25     },
{  3.925,	378,	30     },
{  4.215,	408,	28     },
{  4.530,	436,	35     },
{  4.870,	471,	33     },
{  5.235,	504,	40     },
{  5.625,	544,	38     },
{  6.045,	582,	46     },
{  6.495,	628,	44     },
{  6.980,	672,	53     },
{  7.500,	725,	51     },
{  8.060,	776,	61     },
{  8.660,	837,	59     },
{  9.305,	896,	70     },
{  10.000,	966,	69     },
{  10.745,	1035,	80     },
{  11.550,	1115,	81     },
{  12.410,	1196,	91     },
{  13.335,	1287,	94     },
{  14.330,	1381,	105    },
{  15.400,	1486,	109    },
{  16.550,	1595,	121    },
{  17.785,	1716,	126    },
{  19.110,	1842,	139    },
{  20.535,	1981,	146    },
{  22.065,	2127,	160    },
{  23.715,	2287,	170    },
{  25.485,	2457,	184    },
{  27.385,	2641,	196    },
{  29.425,	2837,	212    },
{  31.625,	3049,	228    },
{  33.980,	3277,	243    },
{  36.515,	3520,	264    },
{  39.240,	3784,	281    },
{  42.170,	4065,	305    },
{  45.315,	4370,	324    },
{  48.695,	4694,	352    },
{  52.330,	5046,	375    },
{  56.235,	5421,	406    },
{  60.430,	5827,	433    },
{  64.940,	6260,	469    },
{  69.785,	6729,	500    },
{  74.990,	7229,	541    },
{  80.585,	7770,	578    },
{  86.595,	8348,	624    },
{  93.055,	8972,	668    },
{  100.00,	9640,	721    },
{  107.46,	10361,	771    },
{  115.48,	11132,	833    },
{  124.10,	11965,	890    },
{  133.35,	12855,	961    },
{  143.30,	13816,	1029   },
{  154.00,	14845,	1110   },
{  165.48,	15955,	1187   },
{  177.83,	17142,	1283   },
{  191.10,	18425,	1370   },
{  205.36,	19795,	1482   },
{  220.68,	21277,	1582   },
{  237.14,	22859,	1710   },
{  254.83,	24569,	1829   },
{  273.84,	26398,	1973   },
{  294.28,  28428, 	2000   },
{  316.23,	30623,	2001   },
{  339.82,	32982,	2001   },
{  365.18,	35518,	2000   },
{  392.42,	38242,	2001   },
{  421.70,	41170,	2000   },
{  453.16,	44316,	2001   },
{  486.97,	47697,	2001   },
{  523.30,	51330,	2001   },
{  562.34,	54234,	4001   },
{  604.30,	58430,	4000   },
{  649.38,	62938,	4001   },
{  697.83,	67783,	4001   },
{  749.90,	72990,	4000   },
{  805.84,	78584,	4001   },
{  865.97,	83597,	6000   },
{  930.57,	90057,	6001   },
{  1000.0,	97000,	6001   },
{  1074.6,	104461,	6001   },
{  1154.8,	111478,	8001   },
{  1240.9,	120094,	8001   },
{  1334.5,	129352,	8001   },
{  1433.0,	138302,	10000  },
{  1539.9,	148993,	10000  },
{  1654.8,	160482,	10000  },
{  1778.3,	171828,	12001  },
{  1911.0,	185096,	12000  },
{  2053.5,	198353,	14000  },
{  2206.7,	213674,	14000  },
{  2371.4,	229138,	16000  },
{  2548.3,	245830,	18000  },
{  2738.4,	264842,	18001  },
{  2942.7,	284273,	20000  },
{  3162.3,	305228,	22001  },
};


TimeScale3E::ScaleLogInfo TimeScale3E::s_scale_32_log_60Hz[] = 
{
{  0.135,	12,	    4      },
{  0.180,	16,	    5      },
{  0.235,	21,	    6      },
{  0.315,	29,	    6      },
{  0.365,	35,	    4      },
{  0.420,	39,	    7      },
{  0.485,	46,	    6      },
{  0.560,	54,	    5      },
{  0.605,	59,	    4      },
{  0.650,	63,	    5      },
{  0.700,	68,	    5      },
{  0.750,	73,	    5      },
{  0.805,	78,	    6      },
{  0.865,	84,	    6      },
{  0.930,	90,	    7      },
{  1.000,	97,	    7      },
{  1.075,	104,	8      },
{  1.155,	112,	8      },
{  1.240,	120,	9      },
{  1.335,	129,	10     },
{  1.435,	139,	10     },
{  1.540,	149,	11     },
{  1.655,	160,	12     },
{  1.780,	172,	13     },
{  1.910,	185,	13     },
{  2.055,	198,	16     },
{  2.205,	214,	14     },
{  2.370,	228,	19     },
{  2.550,	247,	17     },
{  2.740,	264,	21     },
{  2.945,	285,	20     },
{  3.160,	305,	23     },
{  3.400,	328,	25     },
{  3.650,	353,	25     },
{  3.925,	378,	30     },
{  4.215,	408,	28     },
{  4.530,	436,	35     },
{  4.870,	471,	33     },
{  5.235,	504,	40     },
{  5.625,	544,	38     },
{  6.045,	582,	46     },
{  6.495,	628,	44     },
{  6.980,	672,	53     },
{  7.500,	725,	51     },
{  8.060,	776,	61     },
{  8.660,	837,	59     },
{  9.305,	896,	70     },
{  10.000,	966,	69     },
{  10.745,	1035,	80     },
{  11.550,	1115,	81     },
{  12.410,	1196,	91     },
{  13.335,	1287,	94     },
{  14.330,	1381,	105    },
{  15.400,	1486,	109    },
{  16.550,	1595,	121    },
{  17.785,	1716,	126    },
{  19.110,	1842,	139    },
{  20.535,	1981,	146    },
{  22.065,	2127,	160    },
{  23.715,	2287,	170    },
{  25.485,	2457,	184    },
{  27.385,	2641,	196    },
{  29.425,	2837,	212    },
{  31.625,	3049,	228    },
{  33.980,	3277,	243    },
{  36.515,	3520,	264    },
{  39.240,	3784,	281    },
{  42.170,	4065,	305    },
{  45.315,	4370,	324    },
{  48.695,	4694,	352    },
{  52.330,	5046,	375    },
{  56.235,	5421,	406    },
{  60.430,	5827,	433    },
{  64.940,	6260,	469    },
{  69.785,	6729,	500    },
{  74.990,	7229,	541    },
{  80.585,	7770,	578    },
{  86.595,	8348,	624    },
{  93.055,	8972,	668    },
{  100.00,	9640,	721    },
{  107.46,	10361,	771    },
{  115.48,	11132,	833    },
{  124.10,	11965,	890    },
{  133.35,	12855,	961    },
{  143.30,	13816,	1029   },
{  154.00,	14845,	1110   },
{  165.48,	15955,	1187   },
{  177.83,	17142,	1283   },
{  191.10,	18425,	1370   },
{  205.36,	19795,	1482   },
{  220.68,	21277,	1582   },
{  237.14,  22881,	1666   },
{  254.83,	24650,	1667   },
{  273.84,	26551,	1667   },
{  294.28,	28595,	1666   },
{  316.23,	30790,	1667   },
{  339.82,	33149,	1667   },
{  365.18,	35685,	1666   },
{  392.42,	38409,	1667   },
{  421.70,	41337,	1666   },
{  453.16,	44483,	1667   },
{  486.97,	47031,	3333   },
{  523.30,	50664,	3333   },
{  562.34,	54568,	3333   },
{  604.30,	58763,	3334   },
{  649.38,	63272,	3333   },
{  697.83,	67283,	5001   },
{  749.90,	72490,	5000   },
{  805.84,	78084,	5001   },
{  865.97,	84097,	5000   },
{  930.57,	89724,	6667   },
{  1000.0,	96667,	6667   },
{  1074.6,	104128,	6667   },
{  1154.8,	112145,	6667   },
{  1240.9,	119928,	8333   },
{  1334.5,	129186,	8333   },
{  1433.0,	138302,	10000  },
{  1539.9,	148993,	10000  },
{  1654.8,	159649,	11666  },
{  1778.3,	171995,	11667  },
{  1911.0,	184429,	13334  },
{  2053.5,	198686,	13334  },
{  2206.7,	213174,	15000  },
{  2371.4,	228805,	16666  },
{  2548.3,	246676,	16666  },
{  2738.4,	264676,	18333  },
{  2942.7,	284273,	20000  },
{  3162.3,	305395,	21667  },
};


TimeScale3E::ScaleLogInfo TimeScale3E::s_scale_16_log[] = 
{
{   0.135,	12,	    4     },
{   0.180,	16,	    5     },
{   0.235,	21,	    6     },
{   0.315,	29,	    6     },
{   0.365,	35,	    4     },
{   0.420,	39,	    7     },
{   0.485,	46,	    6     },
{   0.560,	52,	    9     },
{   0.650,	61,	    9     },
{   0.750,	70,	    11    },
{   0.865,	81,	    12    },
{   1.000,	93,	    15    },
{   1.155,	108,	16    },
{   1.335,	124,	20    },
{   1.540,	144,	21    },
{   1.780,	165,	27    },
{   2.055,	192,	28    },
{   2.370,	220,	35    },
{   2.740,	255,	39    },
{   3.160,	294,	45    },
{   3.650,	339,	53    },
{   4.215,	392,	60    },
{   4.870,	452,	71    },
{   5.625,	523,	80    },
{   6.495,	603,	94    },
{   7.500,	697,	107   },
{   8.660,	804,	125   },
{   10.000,	929,	143   },
{   11.550,	1072,	167   },
{   13.335,	1239,	190   },
{   15.400,	1429,	223   },
{   17.785,	1652,	254   },
{   20.535,	1906,	296   },
{   23.715,	2202,	340   },
{   27.385,	2542,	394   },
{   31.625,	2936,	454   },
{   36.515,	3390,	524   },
{   42.170,	3914,	607   },
{   48.695,	4521,	698   },
{   56.235,	5219,	810   },
{   64.940,	6029,	931   },
{   74.990,	6960,	1079  },
{   86.595,	8039,	1242  },
{   100.00,	9281,	1439  },
{   115.48,	10720,	1657  },
{   133.35,	12377,	1917  },
{   154.00,	14294,	2212  },
{   177.83,	16506,	2555  },
{   205.36,	19061,	2950  },
{   237.14,	22011,	3406  },
{   273.84,	25417,	3935  },
{   316.23,	29352,	4543  },
{   365.18,	33895,	5246  },
{   421.70,	39141,	6058  },
{   486.97,	45199,	6997  },
{   562.34,	52196,	8077  },
{   649.38,	60273,	9331  },
{   749.90,	69604,	10772 },
{   865.97,	80376,	12442 },
{   1000.0,	92818,	14365 },
{   1154.8,	107183,	16591 },
{   1334.5,	123774,	19257 },
{   1539.9,	142931,	22124 },
{   1778.3,	165055,	25547 },
{   2053.5,	190602,	29502 },
{   2371.4,	220104,	34067 },
{   2738.4,	254172,	39341 },
{   3162.3,	293513,	45431 },
};


TimeScale3E::ScaleLogInfo TimeScale3E::s_scale_16_log_50Hz[] = 
{
{  0.135,	12,	    4     },
{  0.180,	16,	    5     },
{  0.235,	21,	    6     },
{  0.315,	29,	    6     },
{  0.365,	35,	    4     },
{  0.420,	39,	    7     },
{  0.485,	46,	    6     },
{  0.560,	52,	    9     },
{  0.650,	61,	    9     },
{  0.750,	70,	    11    },
{  0.865,	81,	    12    },
{  1.000,	93,	    15    },
{  1.155,	108,	16    },
{  1.335,	124,	20    },
{  1.540,	144,	21    },
{  1.780,	165,	27    },
{  2.055,	192,	28    },
{  2.370,	220,	35    },
{  2.740,	255,	39    },
{  3.160,	294,	45    },
{  3.650,	339,	53    },
{  4.215,	392,	60    },
{  4.870,	452,	71    },
{  5.625,	523,	80    },
{  6.495,	603,	94    },
{  7.500,	697,	107   },
{  8.660,	804,	125   },
{  10.000,	929,	143   },
{  11.550,	1072,	167   },
{  13.335,	1239,	190   },
{  15.400,	1429,	223   },
{  17.785,	1652,	254   },
{  20.535,	1906,	296   },
{  23.715,	2202,	340   },
{  27.385,	2542,	394   },
{  31.625,	2936,	454   },
{  36.515,	3390,	524   },
{  42.170,	3914,	607   },
{  48.695,	4521,	698   },
{  56.235,	5219,	810   },
{  64.940,	6029,	931   },
{  74.990,	6960,	1079  },
{  86.595,	8039,	1242  },
{  100.00,	9281,	1439  },
{  115.48,	10720,	1657  },
{  133.35,	12377,	1917  },
{  154.00,  14400,	2000  },
{  177.83,	16783,	2001  },
{  205.36,	21535,	2000  },
{  237.14,	24713,	2000  },
{  273.84,	26384,	2001  },
{  316.23,	29623,	4001  },
{  365.18,	34518,	4000  },
{  421.70,	39170,	6000  },
{  486.97,	45697,	6001  },
{  562.34,	52234,	8001  },
{  649.38,	60938,	8001  },
{  749.90,	69990,	10000 },
{  865.97,	80597,	12000 },
{  1000.0,	93000,	14001 },
{  1154.8,	107478,	16001 },
{  1334.5,	124993,	18001 },
{  1539.9,	142993,	22000 },
{  1778.3,	165828,	24001 },
{  2053.5,	191353,	28000 },
{  2371.4,	220138,	34000 },
{  2738.4,	254842,	38001 },
{  3162.3,	294228,	44001 },
};


TimeScale3E::ScaleLogInfo TimeScale3E::s_scale_16_log_60Hz[] = 
{
{  0.135,	12,	    4     },
{  0.180,	16,	    5     },
{  0.235,	21,	    6     },
{  0.315,	29,	    6     },
{  0.365,	35,	    4     },
{  0.420,	39,	    7     },
{  0.485,	46,	    6     },
{  0.560,	52,	    9     },
{  0.650,	61,	    9     },
{  0.750,	70,	    11    },
{  0.865,	81,	    12    },
{  1.000,	93,	    15    },
{  1.155,	108,	16    },
{  1.335,	124,	20    },
{  1.540,	144,	21    },
{  1.780,	165,	27    },
{  2.055,	192,	28    },
{  2.370,	220,	35    },
{  2.740,	255,	39    },
{  3.160,	294,	45    },
{  3.650,	339,	53    },
{  4.215,	392,	60    },
{  4.870,	452,	71    },
{  5.625,	523,	80    },
{  6.495,	603,	94    },
{  7.500,	697,	107   },
{  8.660,	804,	125   },
{  10.000,	929,	143   },
{  11.550,	1072,	167   },
{  13.335,	1239,	190   },
{  15.400,	1429,	223   },
{  17.785,	1652,	254   },
{  20.535,	1906,	296   },
{  23.715,	2202,	340   },
{  27.385,	2542,	394   },
{  31.625,	2936,	454   },
{  36.515,	3390,	524   },
{  42.170,	3914,	607   },
{  48.695,	4521,	698   },
{  56.235,	5219,	810   },
{  64.940,	6029,	931   },
{  74.990,	6960,	1079  },
{  86.595,	8039,	1242  },
{  100.00,	9281,	1439  },
{  115.48,	10720,	1657  },
{  133.35,  12502,	1667  },
{  154.00,	14567,	1666  },
{  177.83,	16950,	1667  },
{  205.36,	19703,	1666  },
{  237.14,	22047,	3334  },
{  273.84,	25718,	3333  },
{  316.23,	29957,	3333  },
{  365.18,	34018,	5000  },
{  421.70,	39670,	5000  },
{  486.97,	45364,	6667  },
{  562.34,	52901,	6667  },
{  649.38,	60772,	8333  },
{  749.90,	69990,	10000 },
{  865.97,	80764,	11666 },
{  1000.0,	93334,	13333 },
{  1154.8,	107978,	15001 },
{  1334.5,	124186,	18333 },
{  1539.9,	143160,	21666 },
{  1778.3,	165328,	25001 },
{  2053.5,	191186,	28334 },
{  2371.4,	220471,	33334 },
{  2738.4,	254676,	38333 },
{  3162.3,	293728,	45001 },
};


TimeScale3E::TimeScale3E()
{
}

TimeScale3E::~TimeScale3E()
{
}

uint32_t TimeScale3E::AmountOfPointsGet(ScaleVariantInner3E scale, uint32_t num_point) const
{
    uint32_t amount_of_points = 0;

    if (ScVarType0 == scale)
    {
        amount_of_points = 0; 
    }
    else if (scale == ScVarType7)
    {
        amount_of_points = 0;
    }
    else if (scale == ScVarType1)
    {
        if (num_point >= _countof(s_scale_16_log))
            return 0;
        amount_of_points = s_scale_16_log[num_point].amount_of_saving;
    }
    else if (scale == ScVarType2)
    {
        if (num_point >= _countof(s_scale_16_log_50Hz))
            return 0;
        amount_of_points = s_scale_16_log_50Hz[num_point].amount_of_saving;
    }
    else if (scale == ScVarType3)
    {
        if (num_point >= _countof(s_scale_16_log_60Hz))
            return 0;
        amount_of_points = s_scale_16_log_60Hz[num_point].amount_of_saving;
    }
    else if (scale == ScVarType4)
    {
        if (num_point >= _countof(s_scale_32_log))
            return 0;
        amount_of_points = s_scale_32_log[num_point].amount_of_saving;
    }
    else if (scale == ScVarType5)
    {
        if (num_point >= _countof(s_scale_32_log_50Hz))
            return 0;
        amount_of_points = s_scale_32_log_50Hz[num_point].amount_of_saving;
    }
    else if (scale == ScVarType6)
    {
        if (num_point >= _countof(s_scale_32_log_60Hz))
            return 0;
        amount_of_points = s_scale_32_log_60Hz[num_point].amount_of_saving;
    }
    return amount_of_points;
}

double TimeScale3E::MsGet(ScaleVariantInner3E scale, uint32_t num_point) const
{
    double ms = 0.0;
    if (scale == ScVarType0 || scale == ScVarType7)
        return 0.0;

    if (scale == ScVarType1)
    {
        if (num_point >= _countof(s_scale_16_log))
            return 0.0;

        ms = s_scale_16_log[num_point].ms;
    }
    else if (num_point == ScVarType2)
    {
        if (num_point >= _countof(s_scale_16_log_50Hz))
            return 0.0;

        ms = s_scale_16_log_50Hz[num_point].ms;
    }
    else if (scale == ScVarType3)
    {
        if (num_point >= _countof(s_scale_16_log_60Hz))
            return 0.0;

        ms = s_scale_16_log_60Hz[num_point].ms;
    }
    else if (scale == ScVarType4)
    {
        if (num_point >= _countof(s_scale_32_log))
            return 0.0;

        ms = s_scale_32_log[num_point].ms;
    }
    else if (scale == ScVarType5)
    {
        if (num_point >= _countof(s_scale_32_log_50Hz))
            return 0.0;

        ms = s_scale_32_log_50Hz[num_point].ms;
    }
    else if (scale == ScVarType6)
    {
        if (num_point >= _countof(s_scale_32_log_60Hz))
            return 0.0;

        ms = s_scale_32_log_60Hz[num_point].ms;
    }
    return ms;
}
