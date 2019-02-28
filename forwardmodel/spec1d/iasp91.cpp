
#include "iasp91.hpp"

static std::vector<iasp91entry>::const_iterator
iasp91_interpolation_find(const std::vector<iasp91entry>::const_iterator &start,
			 const std::vector<iasp91entry>::const_iterator &end,
			 double depth,
			 double &alpha)
{
  if (depth <= start->depth) {
    alpha = 0.0;
    return start;
  } else if (depth >= end->depth) {
    alpha = 1.0;
    return end - 1;
  } else {

    if ((end - start) > 1) {
      
      std::vector<iasp91entry>::const_iterator centre = start + (end - start)/2;
      
      if (depth < centre->depth) {
	return iasp91_interpolation_find(start, centre, depth, alpha);
      } else {
	return iasp91_interpolation_find(centre, end, depth, alpha);
      }
    } else {

      alpha = (depth - start->depth)/(end->depth - start->depth);
      return start;
      
    }
  }
}
			 
double iasp91_density(double depth)
{
  double alpha;
  std::vector<iasp91entry>::const_iterator i = iasp91_interpolation_find(iasp91_table.cbegin(),
								       iasp91_table.cend() - 1,
								       depth,
								       alpha);

  return i->density * (1.0 - alpha) + (i + 1)->density * alpha;
}

double iasp91_Vp(double depth)
{
  double alpha;
  std::vector<iasp91entry>::const_iterator i = iasp91_interpolation_find(iasp91_table.cbegin(),
								       iasp91_table.cend() - 1,
								       depth,
								       alpha);

  return i->Vp * (1.0 - alpha) + (i + 1)->Vp * alpha;
}

double iasp91_Vs(double depth)
{
  double alpha;
  std::vector<iasp91entry>::const_iterator i = iasp91_interpolation_find(iasp91_table.cbegin(),
								       iasp91_table.cend() - 1,
								       depth,
								       alpha);

  return i->Vs * (1.0 - alpha) + (i + 1)->Vs * alpha;
}


const std::vector<iasp91entry> iasp91_table = {
  {   0.000,    2.7200,    5.8000,    3.3600},
  {  20.000,    2.7200,    5.8000,    3.3600},
  {  20.000,    2.9200,    6.5000,    3.7500},
  {  35.000,    2.9200,    6.5000,    3.7500},
  {  35.000,    3.3198,    8.0400,    4.4700},
  {  77.500,    3.3455,    8.0450,    4.4850},
  { 120.000,    3.3713,    8.0500,    4.5000},
  { 165.000,    3.3985,    8.1750,    4.5090},
  { 210.000,    3.4258,    8.3000,    4.5180},
  { 210.000,    3.4258,    8.3000,    4.5220},
  { 260.000,    3.4561,    8.4825,    4.6090},
  { 310.000,    3.4864,    8.6650,    4.6960},
  { 360.000,    3.5167,    8.8475,    4.7830},
  { 410.000,    3.5470,    9.0300,    4.8700},
  { 410.000,    3.7557,    9.3600,    5.0700},
  { 460.000,    3.8175,    9.5280,    5.1760},
  { 510.000,    3.8793,    9.6960,    5.2820},
  { 560.000,    3.9410,    9.8640,    5.3880},
  { 610.000,    4.0028,   10.0320,    5.4940},
  { 660.000,    4.0646,   10.2000,    5.6000},
  { 660.000,    4.3714,   10.7900,    5.9500},
  { 710.000,    4.4010,   10.9229,    6.0797},
  { 760.000,    4.4305,   11.0558,    6.2095},
  { 809.500,    4.4596,   11.1440,    6.2474},
  { 859.000,    4.4885,   11.2300,    6.2841},
  { 908.500,    4.5173,   11.3140,    6.3199},
  { 958.000,    4.5459,   11.3960,    6.3546},
  {1007.500,    4.5744,   11.4761,    6.3883},
  {1057.000,    4.6028,   11.5543,    6.4211},
  {1106.500,    4.6310,   11.6308,    6.4530},
  {1156.000,    4.6591,   11.7056,    6.4841},
  {1205.500,    4.6870,   11.7787,    6.5143},
  {1255.000,    4.7148,   11.8504,    6.5438},
  {1304.500,    4.7424,   11.9205,    6.5725},
  {1354.000,    4.7699,   11.9893,    6.6006},
  {1403.500,    4.7973,   12.0568,    6.6280},
  {1453.000,    4.8245,   12.1231,    6.6547},
  {1502.500,    4.8515,   12.1881,    6.6809},
  {1552.000,    4.8785,   12.2521,    6.7066},
  {1601.500,    4.9052,   12.3151,    6.7317},
  {1651.000,    4.9319,   12.3772,    6.7564},
  {1700.500,    4.9584,   12.4383,    6.7807},
  {1750.000,    4.9847,   12.4987,    6.8046},
  {1799.500,    5.0109,   12.5584,    6.8282},
  {1849.000,    5.0370,   12.6174,    6.8514},
  {1898.500,    5.0629,   12.6759,    6.8745},
  {1948.000,    5.0887,   12.7339,    6.8972},
  {1997.500,    5.1143,   12.7915,    6.9199},
  {2047.000,    5.1398,   12.8487,    6.9423},
  {2096.500,    5.1652,   12.9057,    6.9647},
  {2146.000,    5.1904,   12.9625,    6.9870},
  {2195.500,    5.2154,   13.0192,    7.0093},
  {2245.000,    5.2403,   13.0758,    7.0316},
  {2294.500,    5.2651,   13.1325,    7.0540},
  {2344.000,    5.2898,   13.1892,    7.0765},
  {2393.500,    5.3142,   13.2462,    7.0991},
  {2443.000,    5.3386,   13.3034,    7.1218},
  {2492.500,    5.3628,   13.3610,    7.1449},
  {2542.000,    5.3869,   13.4190,    7.1681},
  {2591.500,    5.4108,   13.4774,    7.1917},
  {2641.000,    5.4345,   13.5364,    7.2156},
  {2690.500,    5.4582,   13.5961,    7.2398},
  {2740.000,    5.4817,   13.6564,    7.2645},
  {2740.000,    5.4817,   13.6564,    7.2645},
  {2789.670,    5.5051,   13.6679,    7.2768},
  {2839.330,    5.5284,   13.6793,    7.2892},
  {2889.000,    5.5515,   13.6908,    7.3015},
  {2889.000,    9.9145,    8.0088,    0.0000},
  {2939.330,    9.9942,    8.0963,    0.0000},
  {2989.660,   10.0722,    8.1821,    0.0000},
  {3039.990,   10.1485,    8.2662,    0.0000},
  {3090.320,   10.2233,    8.3486,    0.0000},
  {3140.660,   10.2964,    8.4293,    0.0000},
  {3190.990,   10.3679,    8.5083,    0.0000},
  {3241.320,   10.4378,    8.5856,    0.0000},
  {3291.650,   10.5062,    8.6611,    0.0000},
  {3341.980,   10.5731,    8.7350,    0.0000},
  {3392.310,   10.6385,    8.8072,    0.0000},
  {3442.640,   10.7023,    8.8776,    0.0000},
  {3492.970,   10.7647,    8.9464,    0.0000},
  {3543.300,   10.8257,    9.0134,    0.0000},
  {3593.640,   10.8852,    9.0787,    0.0000},
  {3643.970,   10.9434,    9.1424,    0.0000},
  {3694.300,   11.0001,    9.2043,    0.0000},
  {3744.630,   11.0555,    9.2645,    0.0000},
  {3794.960,   11.1095,    9.3230,    0.0000},
  {3845.290,   11.1623,    9.3798,    0.0000},
  {3895.620,   11.2137,    9.4349,    0.0000},
  {3945.950,   11.2639,    9.4883,    0.0000},
  {3996.280,   11.3127,    9.5400,    0.0000},
  {4046.620,   11.3604,    9.5900,    0.0000},
  {4096.950,   11.4069,    9.6383,    0.0000},
  {4147.280,   11.4521,    9.6848,    0.0000},
  {4197.610,   11.4962,    9.7297,    0.0000},
  {4247.940,   11.5391,    9.7728,    0.0000},
  {4298.270,   11.5809,    9.8143,    0.0000},
  {4348.600,   11.6216,    9.8540,    0.0000},
  {4398.930,   11.6612,    9.8920,    0.0000},
  {4449.260,   11.6998,    9.9284,    0.0000},
  {4499.600,   11.7373,    9.9630,    0.0000},
  {4549.930,   11.7737,    9.9959,    0.0000},
  {4600.260,   11.8092,   10.0271,    0.0000},
  {4650.590,   11.8437,   10.0566,    0.0000},
  {4700.920,   11.8772,   10.0844,    0.0000},
  {4751.250,   11.9098,   10.1105,    0.0000},
  {4801.580,   11.9414,   10.1349,    0.0000},
  {4851.910,   11.9722,   10.1576,    0.0000},
  {4902.240,   12.0021,   10.1785,    0.0000},
  {4952.580,   12.0311,   10.1978,    0.0000},
  {5002.910,   12.0593,   10.2154,    0.0000},
  {5053.240,   12.0867,   10.2312,    0.0000},
  {5103.570,   12.1133,   10.2454,    0.0000},
  {5153.900,   12.1391,   10.2578,    0.0000},
  {5153.900,   12.7037,   11.0914,    3.4385},
  {5204.610,   12.7289,   11.1036,    3.4488},
  {5255.320,   12.7530,   11.1153,    3.4587},
  {5306.040,   12.7760,   11.1265,    3.4681},
  {5356.750,   12.7980,   11.1371,    3.4770},
  {5407.460,   12.8188,   11.1472,    3.4856},
  {5458.170,   12.8387,   11.1568,    3.4937},
  {5508.890,   12.8574,   11.1659,    3.5013},
  {5559.600,   12.8751,   11.1745,    3.5085},
  {5610.310,   12.8917,   11.1825,    3.5153},
  {5661.020,   12.9072,   11.1901,    3.5217},
  {5711.740,   12.9217,   11.1971,    3.5276},
  {5762.450,   12.9351,   11.2036,    3.5330},
  {5813.160,   12.9474,   11.2095,    3.5381},
  {5863.870,   12.9586,   11.2150,    3.5427},
  {5914.590,   12.9688,   11.2199,    3.5468},
  {5965.300,   12.9779,   11.2243,    3.5505},
  {6016.010,   12.9859,   11.2282,    3.5538},
  {6066.720,   12.9929,   11.2316,    3.5567},
  {6117.440,   12.9988,   11.2345,    3.5591},
  {6168.150,   13.0036,   11.2368,    3.5610},
  {6218.860,   13.0074,   11.2386,    3.5626},
  {6269.570,   13.0100,   11.2399,    3.5637},
  {6320.290,   13.0117,   11.2407,    3.5643},
  {6371.000,   13.0122,   11.2409,    3.5645}
};

