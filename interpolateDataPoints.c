#include<stdio.h>
//interpolateDataPoints.c

//function prototypes
void print2dArray(float array[][2], int nRows);
void setInterpolationMxb(float data[][2], float mxb[][2], unsigned long int nDataPoints);
float getSlopeFromPoints(float x1, float y1, float x2, float y2);
float getInterceptFromPoints(float x1, float y1, float x2, float y2);
float interpolate(float x, float data[][2], float mxb[][2], unsigned long int nMxb);

//print2darray
void print2dArray(float array[][2], int nRows){
  printf("\nPrinting %d row array\n",nRows);

  int i,j;
  float c;
  for(i=0;i<nRows;++i){
    for(j=0;j<2;++j)
        printf("%f. ", array[i][j]);
    printf("\n");
  }

}

//take data array and mx+b array and calculate m, b for each pair of points
void setInterpolationMxb(float data[][2], float mxb[][2], unsigned long int nDataPoints){

  int i=0;

  //get dataPoints values for two points
  float x1, y1, x2, y2;

  //stop at second-to-last data point (there is last interpolation regions)
  for(i=0;i<nDataPoints-1;++i){
    x1=data[i][0];
    y1=data[i][1];
    x2=data[i+1][0];
    y2=data[i+1][1];

    //set slope/intercepts
    mxb[i][0]=getSlopeFromPoints(x1,y1,x2,y2);
    mxb[i][1]=getInterceptFromPoints(x1,y1,x2,y2);
  }
}

//helper function
float getSlopeFromPoints(float x1, float y1, float x2, float y2){
  return (y2-y1)/(x2-x1);
}

//helper function
float getInterceptFromPoints(float x1, float y1, float x2, float y2){
  return y1-(y2-y1)/(x2-x1)*x1;
}

//return interpolated value
float interpolate(float x, float data[][2], float mxb[][2], unsigned long int nMxb){

  //return end points of out of bounds
  if(x<data[0][0])
    return data[0][1];
  if(x>data[nMxb][0])
    return data[nMxb][1];

  //find the first datapoint to the right of x
  int upperRegionXIndex=0;

  while(x>=data[upperRegionXIndex][0]){
    printf("data[%i]=%f\n",upperRegionXIndex, data[upperRegionXIndex][0]);
    upperRegionXIndex++;
  }

  //region # corresponds to # of left bounding data point
  int lowerRegionXIndex=upperRegionXIndex-1;

  printf("***Success: %f in region %i (between %f and %f)***\n",
      x,
      lowerRegionXIndex,
      data[lowerRegionXIndex][0],
      data[upperRegionXIndex][0]);

  //y=mx+b
  float m=mxb[lowerRegionXIndex][0];
  float b=mxb[lowerRegionXIndex][1];

  return m*x+b;
}

int main(){
  //set data points
  float dataPoints[][2]={
    {1.15866529715041E+03,4.50301069366019E+01},
    {1.16746663791400E+03,4.20348781409742E+01},
    {1.17721235255750E+03,3.90279410604983E+01},
    {1.18800973618585E+03,3.60212821480793E+01},
    {1.19978259001363E+03,3.30190918776019E+01},
    {1.20900330938726E+03,3.09109206733959E+01},
    {1.21743885586541E+03,2.91047322195714E+01},
    {1.22550149791847E+03,2.74937747961770E+01},
    {1.23416244962562E+03,2.58903948918460E+01},
    {1.24339517040247E+03,2.43017929205896E+01},
    {1.25325132686766E+03,2.27084397580009E+01},
    {1.26396964606193E+03,2.11195309631994E+01},
    {1.27187950977041E+03,2.00430941002044E+01},
    {1.27936384189714E+03,1.90626010068845E+01},
    {1.28722934127037E+03,1.80837544483858E+01},
    {1.29574759047070E+03,1.71005882793930E+01},
    {1.30462105050847E+03,1.61187203584390E+01},
    {1.31442017104110E+03,1.51274624048328E+01},
    {1.32472218300874E+03,1.41334647503066E+01},
    {1.33594976105827E+03,1.31325321851821E+01},
    {1.34817125459252E+03,1.21231743335565E+01},
    {1.36144449280113E+03,1.11089236295542E+01},
    {1.37599419281473E+03,1.00887267540115E+01},
    {1.39183479639045E+03,9.06913622637870E+00},
    {1.40954426489785E+03,8.04816734621171E+00},
    {1.42966395040817E+03,7.03038460717076E+00},
    {1.44803071964235E+03,6.21918126564188E+00},
    {1.46639736561052E+03,5.50677316914736E+00},
    {1.48143361599810E+03,5.00079719591634E+00},
    {1.49482205096690E+03,4.59552503998849E+00},
    {1.50928139937351E+03,4.20520510435486E+00},
    {1.51749647765215E+03,3.99982054497020E+00},
    {1.52600538164916E+03,3.80116505010830E+00},
    {1.53504308357240E+03,3.60649038025064E+00},
    {1.54521806346207E+03,3.40648303346111E+00},
    {1.55621166365908E+03,3.20018193873406E+00},
    {1.56790219236253E+03,3.00068724975927E+00},
    {1.58077863430236E+03,2.80242913148032E+00},
    {1.59568104326293E+03,2.59494585262285E+00},
    {1.61102290744041E+03,2.40347372323739E+00},
    {1.62935054078325E+03,2.20047619224864E+00},
    {1.64976915441758E+03,2.00105436022359E+00},
    {1.67349179538564E+03,1.80153389446074E+00},
    {1.70155732512926E+03,1.60130933114831E+00},
    {1.73591860654589E+03,1.40014646991564E+00},
    {1.75474906703357E+03,1.30518881129438E+00},
    {1.77769752561913E+03,1.20116716268343E+00},
    {1.79063000000000E+03,1.14921975100000E+00},
    {1.81829000000000E+03,1.04940675600000E+00},
    {1.84970000000000E+03,9.49972627000000E-01},
    {1.88391000000000E+03,8.56065505000000E-01},
    {1.92307000000000E+03,7.65741249000000E-01},
    {1.96321000000000E+03,6.86522538000000E-01},
    {2.00894000000000E+03,6.11332665000000E-01},
    {2.06372000000000E+03,5.35658217000000E-01},
    {2.11717000000000E+03,4.75288276000000E-01},
    {2.17997000000000E+03,4.16368136000000E-01},
    {2.24543000000000E+03,3.65702920000000E-01},
    {2.30533000000000E+03,3.27337225000000E-01},
    {2.33918000000000E+03,3.08559372000000E-01},
    {2.37900000000000E+03,2.87903319000000E-01},
    {2.44255000000000E+03,2.59541947000000E-01},
    {2.51962000000000E+03,2.30302739000000E-01},
    {2.60070000000000E+03,2.04819655000000E-01},
    {2.68117000000000E+03,1.83156228000000E-01},
    {2.76689000000000E+03,1.63335118000000E-01},
    {2.85542000000000E+03,1.46628231000000E-01},
    {2.96531000000000E+03,1.28684586000000E-01},
    {3.08736000000000E+03,1.12392286000000E-01},
    {3.23269000000000E+03,9.63750770000000E-02},
    {3.37048000000000E+03,8.45120380000000E-02},
    {3.50987000000000E+03,7.45372560000000E-02},
    {3.68846000000000E+03,6.43737140000000E-02},
    {3.84892000000000E+03,5.70101820000000E-02},
    {3.97983000000000E+03,5.22021750000000E-02},
    {4.10356000000000E+03,4.81713040000000E-02},
    {4.29915000000000E+03,4.32861200000000E-02},
    {4.44334000000000E+03,4.01888320000000E-02},
    {4.58872000000000E+03,3.70092890000000E-02},
    {4.75750000000000E+03,3.40751750000000E-02},
    {5.02345000000000E+03,3.01825940000000E-02},
    {5.20600000000000E+03,2.80622370000000E-02},
    {5.41330000000000E+03,2.58337130000000E-02},
    {5.63890000000000E+03,2.37371790000000E-02},
    {5.86967000000000E+03,2.19165000000000E-02},
    {6.16410000000000E+03,2.00710000000000E-02},
    {6.44140000000000E+03,1.87522550000000E-02},
    {6.79160000000000E+03,1.72500310000000E-02}
  };


  //calculate number of data points and interpolation regions above
  unsigned long nDataPoints = (unsigned long) (sizeof(dataPoints)/sizeof(float))/2;
  unsigned long nMxb = nDataPoints-1; //one less region than set of points

  //set m and b for each pair of data points
  float mxb[nMxb][2]; 
  setInterpolationMxb(dataPoints, mxb, nDataPoints);

  //get interpolated y value for independent x
  float x=6792.;
  float y=interpolate(x, dataPoints, mxb, nMxb);

  printf("f(%f)=%f\n",x,y);

  return 0;
}
