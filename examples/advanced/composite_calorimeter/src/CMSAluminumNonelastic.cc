#include "CMSAluminumNonelastic.hh"

  CMSAluminumNonelastic::CMSAluminumNonelastic()
  {
  theData.insert(0.100000E+07, 0.135249E-01);
  theData.insert(0.150000E+07, 0.742370E-01);
  theData.insert(0.200000E+07, 0.152628E+00);
  theData.insert(0.300000E+07, 0.354538E+00);
  theData.insert(0.400000E+07, 0.518918E+00);
  theData.insert(0.500000E+07, 0.619045E+00);
  theData.insert(0.580333E+07, 0.629610E+00);
  theData.insert(0.600000E+07, 0.632860E+00);
  theData.insert(0.700000E+07, 0.653130E+00);
  theData.insert(0.799843E+07, 0.677926E+00);
  theData.insert(0.800000E+07, 0.677968E+00);
  theData.insert(0.858134E+07, 0.694321E+00);
  theData.insert(0.900000E+07, 0.706163E+00);
  theData.insert(0.100000E+08, 0.732499E+00);
  theData.insert(0.104670E+08, 0.741819E+00);
  theData.insert(0.110000E+08, 0.747724E+00);
  theData.insert(0.112386E+08, 0.749302E+00);
  theData.insert(0.120000E+08, 0.753472E+00);
  theData.insert(0.129112E+08, 0.757437E+00);
  theData.insert(0.130000E+08, 0.757802E+00);
  theData.insert(0.140000E+08, 0.761642E+00);
  theData.insert(0.150000E+08, 0.764175E+00);
  theData.insert(0.154890E+08, 0.764989E+00);
  theData.insert(0.160000E+08, 0.765686E+00);
  theData.insert(0.165383E+08, 0.766258E+00);
  theData.insert(0.170000E+08, 0.766638E+00);
  theData.insert(0.177810E+08, 0.766741E+00);
  theData.insert(0.180000E+08, 0.766668E+00);
  theData.insert(0.190000E+08, 0.764902E+00);
  theData.insert(0.195898E+08, 0.762492E+00);
  theData.insert(0.196127E+08, 0.762370E+00);
  theData.insert(0.200000E+08, 0.759877E+00);
  theData.insert(0.203408E+08, 0.757296E+00);
  theData.insert(0.210000E+08, 0.752237E+00);
  theData.insert(0.210420E+08, 0.751911E+00);
  theData.insert(0.213282E+08, 0.749680E+00);
  theData.insert(0.220000E+08, 0.744355E+00);
  theData.insert(0.230000E+08, 0.736303E+00);
  theData.insert(0.232530E+08, 0.734264E+00);
  theData.insert(0.240000E+08, 0.728266E+00);
  theData.insert(0.250000E+08, 0.720333E+00);
  theData.insert(0.254920E+08, 0.716494E+00);
  theData.insert(0.254993E+08, 0.716438E+00);
  theData.insert(0.260000E+08, 0.712591E+00);
  theData.insert(0.260313E+08, 0.712353E+00);
  theData.insert(0.270000E+08, 0.705347E+00);
  theData.insert(0.280000E+08, 0.698647E+00);
  theData.insert(0.280306E+08, 0.698447E+00);
  theData.insert(0.290000E+08, 0.692183E+00);
  theData.insert(0.291285E+08, 0.691364E+00);
  theData.insert(0.291605E+08, 0.691160E+00);
  theData.insert(0.296212E+08, 0.688249E+00);
  theData.insert(0.298426E+08, 0.686866E+00);
  theData.insert(0.300000E+08, 0.685890E+00);
  theData.insert(0.302934E+08, 0.684077E+00);
  theData.insert(0.310000E+08, 0.679720E+00);
  theData.insert(0.320000E+08, 0.673582E+00);
  theData.insert(0.328432E+08, 0.668434E+00);
  theData.insert(0.330000E+08, 0.667479E+00);
  theData.insert(0.340000E+08, 0.661414E+00);
  theData.insert(0.341035E+08, 0.660789E+00);
  theData.insert(0.343522E+08, 0.659287E+00);
  theData.insert(0.344227E+08, 0.658863E+00);
  theData.insert(0.350000E+08, 0.655390E+00);
  theData.insert(0.354294E+08, 0.652818E+00);
  theData.insert(0.356588E+08, 0.651450E+00);
  theData.insert(0.360000E+08, 0.649420E+00);
  theData.insert(0.360811E+08, 0.648939E+00);
  theData.insert(0.368945E+08, 0.644134E+00);
  theData.insert(0.370000E+08, 0.643515E+00);
  theData.insert(0.375738E+08, 0.640154E+00);
  theData.insert(0.380000E+08, 0.637672E+00);
  theData.insert(0.388794E+08, 0.632585E+00);
  theData.insert(0.390000E+08, 0.631891E+00);
  theData.insert(0.397625E+08, 0.627523E+00);
  theData.insert(0.400000E+08, 0.626170E+00);
  theData.insert(0.410000E+08, 0.620566E+00);
  theData.insert(0.412413E+08, 0.619237E+00);
  theData.insert(0.415260E+08, 0.617679E+00);
  theData.insert(0.420000E+08, 0.615108E+00);
  theData.insert(0.422555E+08, 0.613732E+00);
  theData.insert(0.428773E+08, 0.610408E+00);
  theData.insert(0.430000E+08, 0.609756E+00);
  theData.insert(0.437707E+08, 0.605678E+00);
  theData.insert(0.440000E+08, 0.604470E+00);
  theData.insert(0.450000E+08, 0.599210E+00);
  theData.insert(0.460000E+08, 0.594198E+00);
  theData.insert(0.461595E+08, 0.593436E+00);
  theData.insert(0.464692E+08, 0.591974E+00);
  theData.insert(0.469790E+08, 0.589606E+00);
  theData.insert(0.470000E+08, 0.589510E+00);
  theData.insert(0.480000E+08, 0.584881E+00);
  theData.insert(0.487296E+08, 0.581390E+00);
  theData.insert(0.490000E+08, 0.580048E+00);
  theData.insert(0.499542E+08, 0.575007E+00);
  theData.insert(0.500000E+08, 0.574750E+00);
  theData.insert(0.502709E+08, 0.573211E+00);
  theData.insert(0.510000E+08, 0.568914E+00);
  theData.insert(0.520000E+08, 0.562754E+00);
  theData.insert(0.525622E+08, 0.559208E+00);
  theData.insert(0.530000E+08, 0.556431E+00);
  theData.insert(0.533731E+08, 0.554064E+00);
  theData.insert(0.540000E+08, 0.550109E+00);
  theData.insert(0.550000E+08, 0.543950E+00);
  theData.insert(0.560000E+08, 0.537754E+00);
  theData.insert(0.570000E+08, 0.531433E+00);
  theData.insert(0.576915E+08, 0.527161E+00);
  theData.insert(0.580000E+08, 0.525316E+00);
  theData.insert(0.590000E+08, 0.519732E+00);
  theData.insert(0.596934E+08, 0.516346E+00);
  theData.insert(0.600000E+08, 0.515010E+00);
  theData.insert(0.604445E+08, 0.513191E+00);
  theData.insert(0.610000E+08, 0.511017E+00);
  theData.insert(0.618634E+08, 0.507816E+00);
  theData.insert(0.620000E+08, 0.507326E+00);
  theData.insert(0.630000E+08, 0.503826E+00);
  theData.insert(0.640000E+08, 0.500408E+00);
  theData.insert(0.650000E+08, 0.496960E+00);
  theData.insert(0.660000E+08, 0.493461E+00);
  theData.insert(0.669216E+08, 0.490240E+00);
  theData.insert(0.670000E+08, 0.489966E+00);
  theData.insert(0.680000E+08, 0.486482E+00);
  theData.insert(0.680000E+08, 0.486481E+00);
  theData.insert(0.690000E+08, 0.483014E+00);
  theData.insert(0.700000E+08, 0.479570E+00);
  theData.insert(0.710000E+08, 0.476168E+00);
  theData.insert(0.720000E+08, 0.472867E+00);
  theData.insert(0.730000E+08, 0.469734E+00);
  theData.insert(0.740000E+08, 0.466836E+00);
  theData.insert(0.750000E+08, 0.464240E+00);
  theData.insert(0.760000E+08, 0.461912E+00);
  theData.insert(0.770000E+08, 0.459750E+00);
  theData.insert(0.780000E+08, 0.457722E+00);
  theData.insert(0.790000E+08, 0.455796E+00);
  theData.insert(0.800000E+08, 0.453940E+00);
  theData.insert(0.810000E+08, 0.452108E+00);
  theData.insert(0.820000E+08, 0.450277E+00);
  theData.insert(0.830000E+08, 0.448447E+00);
  theData.insert(0.840000E+08, 0.446621E+00);
  theData.insert(0.850000E+08, 0.444800E+00);
  theData.insert(0.860000E+08, 0.442982E+00);
  theData.insert(0.870000E+08, 0.441165E+00);
  theData.insert(0.880000E+08, 0.439352E+00);
  theData.insert(0.890000E+08, 0.437546E+00);
  theData.insert(0.900000E+08, 0.435750E+00);
  theData.insert(0.910000E+08, 0.434015E+00);
  theData.insert(0.920000E+08, 0.432375E+00);
  theData.insert(0.930000E+08, 0.430804E+00);
  theData.insert(0.940000E+08, 0.429278E+00);
  theData.insert(0.950000E+08, 0.427770E+00);
  theData.insert(0.960000E+08, 0.426285E+00);
  theData.insert(0.970000E+08, 0.424840E+00);
  theData.insert(0.980000E+08, 0.423434E+00);
  theData.insert(0.990000E+08, 0.422062E+00);
  theData.insert(0.100000E+09, 0.420720E+00);
  theData.insert(0.102000E+09, 0.418145E+00);
  theData.insert(0.104000E+09, 0.415710E+00);
  theData.insert(0.106000E+09, 0.413386E+00);
  theData.insert(0.108000E+09, 0.411146E+00);
  theData.insert(0.110000E+09, 0.408960E+00);
  theData.insert(0.112000E+09, 0.406845E+00);
  theData.insert(0.114000E+09, 0.404882E+00);
  theData.insert(0.116000E+09, 0.403140E+00);
  theData.insert(0.118000E+09, 0.401690E+00);
  theData.insert(0.120000E+09, 0.400600E+00);
  theData.insert(0.122000E+09, 0.399825E+00);
  theData.insert(0.124000E+09, 0.399255E+00);
  theData.insert(0.126000E+09, 0.398866E+00);
  theData.insert(0.128000E+09, 0.398636E+00);
  theData.insert(0.130000E+09, 0.398540E+00);
  theData.insert(0.132000E+09, 0.398501E+00);
  theData.insert(0.134000E+09, 0.398468E+00);
  theData.insert(0.136000E+09, 0.398452E+00);
  theData.insert(0.138000E+09, 0.398469E+00);
  theData.insert(0.140000E+09, 0.398530E+00);
  theData.insert(0.142000E+09, 0.398618E+00);
  theData.insert(0.144000E+09, 0.398712E+00);
  theData.insert(0.146000E+09, 0.398818E+00);
  theData.insert(0.148000E+09, 0.398945E+00);
  theData.insert(0.150000E+09, 0.399100E+00);
  }
  
