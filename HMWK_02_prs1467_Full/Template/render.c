// Dalio, Brian A.
// dalioba
// 2021-04-24
//----------------------------------------------------------------
#include <stdio.h>

#include "model.h"
#include "parameters.h"

//----------------------------------------------------------------
int main( int argc, char *argv[] )
{
  if ( argc != 3 ) {
    printf( "Usage:\n%s <modelFileName> <paramsFileName>\n",
      argv[0] );

    return 1;
  }

  Model      *model  = loadModel( argv[1] );
  Parameters *params = loadParameters( argv[2] );

  dumpModel( model, 12, 12 );
  dumpParameters( params );

  //--------------------------------------------------------------
  rotateModel( model, params );

  dumpModel( model, 12, 0 );

  //--------------------------------------------------------------
  projectModel( model, params );

  //--------------------------------------------------------------
  drawModel( model, params );

  //--------------------------------------------------------------
  disposeParameters( params );
  disposeModel( model );

  //--------------------------------------------------------------
  return 0;
}

//----------------------------------------------------------------
