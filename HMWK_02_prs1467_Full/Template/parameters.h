// Dalio, Brian A.
// dalioba
// 2021-04-24
//----------------------------------------------------------------
#if !defined( __PARAMETERS_H__ )
#define __PARAMETERS_H__

#include <math.h>

#include "primitiveTypes.h"

#define DEG_TO_RAD(d) ((d)*M_PI/180.0)
#define RAD_TO_DEG(r) ((r)*180.0/M_PI)

//----------------------------------------------------------------
typedef struct _Parameters {
  char *sourceFileName;

  // Euler rotation angles -- kept internally as radians though
  //  read and displayed as degrees.
  FLOAT64 phi;
  FLOAT64 theta;
  FLOAT64 psi;

  // World subset limits
  FLOAT64 xMin;
  FLOAT64 xMax;
  FLOAT64 yMin;
  FLOAT64 yMax;

  // Screen space size -- integer number of pixels.
  int     width;
  int     height;

  // Camera position on Z axis
  FLOAT64 d;
} Parameters;

//----------------------------------------------------------------
extern Parameters *loadParameters( char *fName );
extern void        disposeParameters( Parameters *params );
extern void        dumpParameters( Parameters *params );

//----------------------------------------------------------------
#endif
