// Dalio, Brian A.
// dalioba
// 2021-04-24
//----------------------------------------------------------------
#if !defined( __MODEL_H__ )
#define __MODEL_H__

//----------------------------------------------------------------
#include "matrix.h"
#include "parameters.h"

//----------------------------------------------------------------
typedef int     Face[3];

typedef struct _Model {
  char  *sourceFileName;
  char  *drawFileName;

  int    numPoints;
  int    numFaces;

  Point *points;
  Face  *faces;

  FLOAT64 xMin, xMax;
  FLOAT64 yMin, yMax;
  FLOAT64 zMin, zMax;

  FLOAT64 xCenter;
  FLOAT64 yCenter;
  FLOAT64 zCenter;
} Model;

//----------------------------------------------------------------
extern Model *loadModel( char *fName );
extern void   disposeModel( Model *model );
extern void   dumpModel( Model *model, int pLimit, int fLimit );

extern void   rotateModel( Model *model, Parameters *params );
extern void   projectModel( Model *model, Parameters *params );
extern void   drawModel( Model *model, Parameters *params );

//----------------------------------------------------------------
#endif
