// Dalio, Brian A.
// dalioba
// 2021-04-27
//----------------------------------------------------------------
#include <stdio.h>

#include "matrix.h"
#include "transforms.h"

//----------------------------------------------------------------
int main()
{
  Point pts[] = {
    { 0.0, 1.0, 2.0, 1.0 },
    { 3.0, 4.0, 5.0, 1.0 },
    { 6.0, 7.0, 8.0, 1.0 },
    { 9.0, 0.0, 1.0, 1.0 },
    { 2.0, 3.0, 4.0, 1.0 },
    { 5.0, 6.0, 7.0, 1.0 },
    { 8.0, 9.0, 0.0, 1.0 },
    { 1.0, 2.0, 3.0, 1.0 },
    { 4.0, 5.0, 6.0, 1.0 },
    { 7.0, 8.0, 9.0, 1.0 }
  };
#define NUM_POINTS ( (int) ( sizeof( pts ) / sizeof( Point ) ) )

  struct _testcase {
    FLOAT64 xMin, yMin;
    FLOAT64 xMax, yMax;
    int     w, h;
    FLOAT64 d;
  } testcases[] = {
    { -16, -12, 16, 12,  320, 240,  27.5 },
    { -16, -12, 16, 12,  320, 240,  55.0 },
    { -16, -12, 16, 12,  320, 240, 110.0 },

    { -16, -12, 16, 12,  640, 480,  27.5 },
    { -16, -12, 16, 12,  640, 480,  55.0 },
    { -16, -12, 16, 12,  640, 480, 110.0 },

    { -16, -12, 16, 12, 1000, 750,  27.5 },
    { -16, -12, 16, 12, 1000, 750,  55.0 },
    { -16, -12, 16, 12, 1000, 750, 110.0 },
  };
#define NUM_TESTCASES ( (int) ( sizeof( testcases ) / sizeof( struct _testcase ) ) )

  printf( "//-----------------------------------------------------------------\n" );
  Point  pTmp;
  Matrix persp;

  for ( int i = 0; i < NUM_TESTCASES; i++ ) {
      printf( "\n//-- Test suite %2d ---------\n", i );
    printf( "//  World subset    : (%g, %g) .. (%g, %g)\n",
      testcases[i].xMin, testcases[i].yMin,
      testcases[i].xMax, testcases[i].yMax );
    printf( "//  Screen space    : (%d, %d)\n",
      testcases[i].w, testcases[i].h );
    printf( "//  Camera position : (0, 0, %g)\n",
      testcases[i].d );

    projectPerspective(
      testcases[i].xMin, testcases[i].yMin,
      testcases[i].xMax, testcases[i].yMax,
      testcases[i].w,    testcases[i].h,
      testcases[i].d,
      persp );

    for ( int j = 0; j < NUM_POINTS; j++ ) {
      projectPoint( persp, pts[j], pTmp );
      //printf( "\n//-- Point %2d --------------\n", j );
      dumpPoint( pTmp );
    }
  }

  printf( "\n//-----------------------------------------------------------------\n" );

  return 0;
}

//----------------------------------------------------------------
