/* $Id: grid.c,v 1.1 1994/10/28 19:47:51 alex Exp $
 ***************************************************************************
 *    grid.c
 *    C Source to tiling
 *    functions for drawing the quasy periodic Penrose tiling of a plane
 *
 *    (c) Copyright Visix Software Inc.
 *    All rights reserved
 ****************************************************************************/

#ifndef  vportINCLUDED
#include <vport.h>	
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER	
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#include "tiling.h"

int  MaxGrid = 5;         /* dimension of the grid                    */
int  MaxStep = 2;
int  kdim = 1;            /* coefficient for determination of MaxStep */

double  Rsize = 60.0;
double  alfa0 = 0.0;
double  alfa[NumMaxGrid+1];
double  d[NumMaxGrid+1];
vector  g[NumMaxGrid+1];

vbool   bFillTiling = TRUE;

/***************************************************************************
*  GetStartPoint()
*
*  finds x0 - starting point of the two-grid
***************************************************************************/
static void GetStartPoint(vector u, vector v, vector x0, double du, double dv)
  {
  double   det;
  double   det1, det2 ;

  det  = u[1]*v[2] - u[2]*v[1];
  det1 = du  *v[2] - u[2]*dv;
  det2 = u[1]*dv   - du  *v[1];
  x0[1] = det1/det;
  x0[2] = det2/det;
  }

/***************************************************************************
*  DrawRhombus()
*
* draws rhombus for the point x and vectors u, v
***************************************************************************/
static void DrawRhombus(vector x, vector u, vector v)
  {
  int     i;
  double  value, k;
  vector  c;

  /*
  *  define the position of the rhombus
  */
  c[1] = 0.0;
  c[2] = 0.0;
  for (i = 1; i <= MaxGrid; i++)
    {
    value = (x[1] * g[i][1] + x[2]*g[i][2] - d[i]) / Rsize;
    k = ceil(value);
    if (fabs(value - k) >= 0.99999)
      k = k - 1.0;

    c[1] = c[1] + k * g[i][1];
    c[2] = c[2] + k * g[i][2];
    };

  /*
  * draw rhombus
  */
  vdrawFMoveTo(c[1], c[2]);
  vdrawFLineTo(c[1]+u[1], c[2]+u[2]);
  vdrawFLineTo(c[1]+u[1]+v[1], c[2]+u[2]+v[2]);
  vdrawFLineTo(c[1]+v[1], c[2]+v[2]);
  vdrawFLineTo(c[1]+v[1], c[2]+v[2]);
  vdrawFLineTo(c[1], c[2]);

  if (bFillTiling)
    vdrawFill();
  else
    vdrawStroke();
  }

/***************************************************************************
*  ProcessVectors()
*
*  draws tiling for the pair of vectors u, v
***************************************************************************/
vbool ProcessVectors( vector u, vector v, double du, double dv)
  {
  int     m1, m2;
  double  cos_alf, sin_alf, rsin;
  vector  xStart, x0;
  vector  nu, nv;

  cos_alf = (u[1]*v[1] + u[2]*v[2]) / (Rsize*Rsize);
  sin_alf = sqrt (1.0- cos_alf*cos_alf);
  rsin = 1.0 / (Rsize*sin_alf);
  nu[1] = -rsin * u[2];
  nu[2] =  rsin * u[1];
  nv[1] =  rsin * v[2];
  nv[2] = -rsin * v[1];

  GetStartPoint( u, v, xStart, du, dv);
  xStart[1] = xStart[1] - MaxStep*(nu[1] + nv[1]);
  xStart[2] = xStart[2] - MaxStep*(nu[2] + nv[2]);

  for (m1 = - MaxStep; m1 <=  MaxStep ; m1++)
    {
    x0[1] = xStart[1];
    x0[2] = xStart[2];
    for (m2 = - MaxStep; ((m2<=MaxStep) ); m2++)
      {
      DrawRhombus(x0, u, v);
      x0[1] = x0[1] + nv[1];
      x0[2] = x0[2] + nv[2];
      };
    xStart[1] = xStart[1] + nu[1];
    xStart[2] = xStart[2] + nu[2];
    };
  return TRUE;
  }

/**************************************************************************/


