/***************************************************************************
*   gridw.c -  
*   for non Galaxy tilingw MSW application
*
*   functions for drawing Penrose tiling of a plane
*   for tilingw aplicaiton
*   
*    (c)  Visix Software Inc. 1994
*
****************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "tilingw.h"

int  MaxGrid = 5;         /* dimension of the grid  */
int  MaxStep = 2;
int  kdim = 1;            /* coefficient for determination of MaxStep */

double  Rsize = 60;

double  alfa0;
double  alfa[NumMaxGrid+1];
double  d[NumMaxGrid+1];
vector  g[NumMaxGrid+1];

BOOL  bFillTiling = TRUE;

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
  int      i;
  double   value, k;
  vector   c;
  RHOMBUS  rhombus;

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

  rhombus[0].x =  (int)c[1];
  rhombus[0].y =  (int)c[2];

  rhombus[1].x = (int)(c[1] + u[1]);
  rhombus[1].y = (int)(c[2] + u[2]);

  rhombus[2].x = (int)(c[1] + u[1] + v[1]);
  rhombus[2].y = (int)(c[2] + u[2] + v[2]);

  rhombus[3].x = (int)(c[1] + v[1]);
  rhombus[3].y = (int)(c[2] + v[2]);

  if (bFillTiling)
    Polygon(hDC, rhombus, 4);
  else
    {
  /* MoveTo is deleted in Win32  */
  #if defined (_WIN32) || defined(WIN32)
    MoveToEx(hDC, rhombus[0].x, rhombus[0].y, NULL );
  #else
    MoveTo(hDC, rhombus[0].x, rhombus[0].y);
  #endif
    LineTo(hDC, rhombus[1].x, rhombus[1].y);
    LineTo(hDC, rhombus[2].x, rhombus[2].y);
    LineTo(hDC, rhombus[3].x, rhombus[3].y);
    LineTo(hDC, rhombus[0].x, rhombus[0].y);
    }
  };

/***************************************************************************
*  ProcessVectors()
*
*  draws tiling for the pair of vectors u, v
***************************************************************************/
BOOL  ProcessVectors( vector u, vector v, double du, double dv)
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
    for (m2 = - MaxStep; m2<=MaxStep; m2++)
      {
      DrawRhombus(x0, u, v);
      x0[1] = x0[1] + nv[1];
      x0[2] = x0[2] + nv[2];
      };
    xStart[1] = xStart[1] + nu[1];
    xStart[2] = xStart[2] + nu[2];
    };
  return TRUE;
  };

/**************************************************************************
*  OptionsDlgProc(HWND, UINT, WPARAM, LPARAM)
***************************************************************************/
LRESULT CALLBACK  OptionsDlgProc(HWND hDlg, UINT iMessage,
                                 WPARAM wParam, LPARAM lParam)
    {
    int     ind, i;
    char    szBuff[128];
    static BOOL  bSaveIni = FALSE;

    switch (iMessage)
     {
        case WM_INITDIALOG:
            {
            ind = (int)SendDlgItemMessage(hDlg, IDC_TSIZE,
                                            CB_ADDSTRING, 0,
                                            (LONG)(LPSTR)"Auto");
            ind = (int)SendDlgItemMessage(hDlg, IDC_TSIZE,
                                            CB_ADDSTRING, 0,
                                            (LONG)(LPSTR)"Small");
            ind = (int)SendDlgItemMessage(hDlg, IDC_TSIZE,
                                            CB_ADDSTRING, 0,
                                            (LONG)(LPSTR)"Medium");
            ind = (int)SendDlgItemMessage(hDlg, IDC_TSIZE,
                                            CB_ADDSTRING, 0,
                                            (LONG)(LPSTR)"Large");

            SendDlgItemMessage(hDlg,IDC_TSIZE, CB_SETCURSEL,
                                 TilingSize, 0);

            for (i = 3;  i <= NumMaxGrid; i = i + 2)
              {
              sprintf(szBuff, "Dimension %d", i);
              ind = (int)SendDlgItemMessage(hDlg, IDC_DIM,
                                            CB_ADDSTRING, 0,
                                            (LONG)(LPSTR)szBuff);
              }

           ind = (MaxGrid-1)/2 - 1;
           SendDlgItemMessage(hDlg,IDC_DIM, CB_SETCURSEL,
                                ind, (LONG)NULL);
           SendDlgItemMessage(hDlg, IDC_FILL, BM_SETCHECK,
                                bFillTiling, 0);
           SendDlgItemMessage(hDlg, IDC_SAVE, BM_SETCHECK,
                                bSaveIni, 0);
           CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
					 break;
           }

        case WM_COMMAND:
             switch (wParam)
               {
               int svSize = 0;
               int svDim = 0, svFill = 0;

               case IDOK:
                 svSize = TilingSize;
                 svDim  = MaxGrid;
                 svFill = bFillTiling;

                 bFillTiling = (BOOL)SendDlgItemMessage(hDlg, IDC_FILL,
                                                      BM_GETCHECK, 0, 0L);

                 ind = (int)SendDlgItemMessage(hDlg,IDC_DIM,
                                                 CB_GETCURSEL, 0, 0L);
                 MaxGrid = 2*(ind+1) + 1;

                 ind = (int)SendDlgItemMessage(hDlg,IDC_TSIZE,
                                                 CB_GETCURSEL, 0, 0L);
                 TilingSize = ind;
                 
								 bSaveIni = (BOOL)SendDlgItemMessage(hDlg, IDC_SAVE,
                                                      BM_GETCHECK, 0, 0L);
								 if (bSaveIni)
                   WriteIniFile((LPCSTR)szIniFileName);
                 if (svSize != TilingSize || svDim != MaxGrid ||
                     svFill != bFillTiling)
                   {
                   SetupParam();
                   EndDialog(hDlg, IDOK);
                   return(TRUE);
                   }
                 EndDialog(hDlg, IDCANCEL);
                 return (TRUE);

               case IDCANCEL:
                 EndDialog(hDlg, IDCANCEL);
                 return (TRUE);

               }
               break;
    }
  lParam; // This will prevent 'unused formal parameter' warnings
  return FALSE;
  }
/**************************************************************************/
