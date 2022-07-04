// Dalio, Brian A.
// dalioba
// 2021-04-24
//----------------------------------------------------------------
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parameters.h"

//----------------------------------------------------------------
Parameters *loadParameters( char *fName )
{
  // Is the input file available?
  FILE *fp = fopen( fName, "r" );
  if ( fp == NULL ) {
    // Rats!  A file open-to-read error.
    printf( "# Unable to open \"%s\" for read.  (%d) %s.\n",
      fName, errno, strerror( errno ) );
    exit( 1 );
  }

  // Allocate an empty Parameters structure
  Parameters *params = (Parameters *) calloc( 1, sizeof( Parameters ) );
  if ( params == NULL ) {
    printf( "# (%s) Unable to allocate a Parameters structure (%lu bytes).\n",
      fName, sizeof( Parameters ) );
    exit( 1 );
  }

  // Remember the source file name (for messages)
  params->sourceFileName = strdup( fName );

  //-- Read ------------------------------------------------------
  // Get the values of all of the parameters we use to render
  //  a model.
  char   *line    = NULL;
  size_t  len     = 0;
  size_t  read;
  int     lineNum = 0;

  while ( ( read = getline( &line, &len, fp ) ) != -1ul ) {
    lineNum++;

    char *ptr = line;

    while ( *ptr && isspace( *ptr ) ) ptr++;

    switch ( *ptr ) {
      case 'd' : {
        int conv = sscanf( ptr+1, " %lf",
          &params->d );

        if ( conv != 1 ) {
          printf( "# (%s) Unable to load camera position at line %d.\n",
            params->sourceFileName, lineNum );
        }

        break;
      }

      case 'r' : {
        int conv = sscanf( ptr+1, " %lf %lf %lf",
          &params->phi, &params->theta, &params->psi );

        if ( conv != 3 ) {
          printf( "# (%s) Unable to load Euler angles at line %d.\n",
            params->sourceFileName, lineNum );
        }

        // Convert the external degree measure into radians for
        //  internal use.
        params->phi   = DEG_TO_RAD( params->phi );
        params->theta = DEG_TO_RAD( params->theta );
        params->psi   = DEG_TO_RAD( params->psi );

        break;
      }

      case 's' : {
        int conv = sscanf( ptr+1, " %d %d",
          &params->width, &params->height );

        if ( conv != 2 ) {
          printf( "# (%s) Unable to load screen size at line %d.\n",
            params->sourceFileName, lineNum );
        }

        break;
      }

      case 'w' : {
        int conv = sscanf( ptr+1, " %lf %lf %lf %lf",
          &params->xMin, &params->yMin, &params->xMax, &params->yMax );

        if ( conv != 4 ) {
          printf( "# (%s) Unable to load World space subset limits at line %d.\n",
            params->sourceFileName, lineNum );
        }

        break;
      }

      case '#' :
      case '\0' :
        // Comment or blank line -- ignore
        break;

      default :
        printf( "# (%s) Line %d not understood:\n%s\n",
          params->sourceFileName, lineNum, ptr );
        break;
    }
  }

  //-- Done! -----------------------------------------------------
  // Free/close local items.
  if ( line != NULL ) free( line );
  fclose( fp );

  // Ta-da!  All done!
  return params;
}

void disposeParameters( Parameters *params )
{
  if ( params ) {
    if ( params->sourceFileName ) free( params->sourceFileName );

    free( params );
  }
}

void dumpParameters( Parameters *params )
{
  printf( "#---------------------------------------\n" );
  printf( "# Parameters \"%s\"\n", params->sourceFileName );
  printf( "#  Euler angles    : phi %g°, theta %g°, psi %g°\n",
    RAD_TO_DEG( params->phi ),
    RAD_TO_DEG( params->theta ),
    RAD_TO_DEG( params->psi ) );
  printf( "#  World subset    : (%g, %g) .. (%g, %g)\n",
    params->xMin, params->yMin,
    params->xMax, params->yMax );
  printf( "#  Screen space    : (%d, %d)\n",
    params->width, params->height );
  printf( "#  Camera position : (0, 0, %g)\n",
    params->d );
  printf( "#---------------------------------------\n" );
}

//----------------------------------------------------------------
