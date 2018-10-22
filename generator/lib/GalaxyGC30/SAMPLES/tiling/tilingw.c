/***************************************************************************
*
*             tilingw -  Microsoft Windows application.
*             non Galaxy version of the Galaxy tiling sample
*             files: tilingw.c gridw.c tilingw.h - source
*                    tilingw.rc  - resources
*                    tilingw.ico - icon
*
*                  (c) Visix Software Inc. 1994
*
****************************************************************************/
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <direct.h>

#if !defined (APIENTRY)
#define APIENTRY far pascal
#endif

#if !defined(_WIN32) && !defined(WIN32)
#define DLGPROC FARPROC
#endif

#include "tilingw.h"

char szIniFileName[128] = "tilingw.ini";
char szApplName[32] = "Tiling";


HINSTANCE  hInst;
HCURSOR    hSaveCursor;                        /* handle to current cursor      */
HCURSOR    hHourGlass;                         /* handle to hourglass cursor    */
HBRUSH     hbrush[10];
HPEN       hpen[10];

int  SaveMapMode;
int  xClient, yClient;
int  ScrX0;
int  ScrY0;

int  TilingSize = SIZE_MEDIUM;  // 0 Auto, 1 Small , 2 Medium, 3 Large

HDC  hDC;

/****************************************************************************
*  WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
****************************************************************************/
int APIENTRY WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow)
  {
  MSG msg;

  if (!hPrevInstance)
    if (!InitApplication(hInstance))
	    return (FALSE);

  if (!InitInstance(hInstance, nCmdShow))
    return (FALSE);

  while (GetMessage(&msg, NULL, 0, 0))
    {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }
  return (msg.wParam);

  lpCmdLine; // This will prevent 'unused formal parameter' warnings

  }

/****************************************************************************
*  InitApplication(HINSTANCE)
****************************************************************************/
BOOL InitApplication(HINSTANCE hInstance)

  {
  WNDCLASS  wc;

  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = (WNDPROC)MainWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(hInstance, "TilingIcon");
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  // wc.hbrBackground = GetStockObject(BLACK_BRUSH);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // Default color
  wc.lpszMenuName =  "TilingMenu";
  wc.lpszClassName = "TilingWClass";
  return (RegisterClass(&wc));
  }


/****************************************************************************
*  InitInstance(HINSTANCE, int)
****************************************************************************/
BOOL InitInstance(HINSTANCE  hInstance,  int nCmdShow)
  {
  HWND  hWnd;
  HDC   hDC;
  int cx = 0, cy = 0;

  hInst = hInstance;
  hHourGlass = LoadCursor(NULL, IDC_WAIT);
  hWnd = CreateWindow(
        "TilingWClass",
        "Penrose Tiling",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
         );
  if (!hWnd)
     return (FALSE);

  hDC = GetDC(hWnd);
  cx = (int)(0.7*GetDeviceCaps(hDC, HORZRES));
  cy = (int)(0.7*GetDeviceCaps(hDC, VERTRES));
  ReleaseDC(hWnd, hDC);

  SetWindowPos(hWnd, NULL, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOMOVE );
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  return (TRUE);
  }

/****************************************************************************
*  CenterWindow (HWND, HWND)
****************************************************************************/
BOOL CenterWindow (HWND hwndChild, HWND hwndParent)
{
        RECT    rChild, rParent;
        int     wChild, hChild, wParent, hParent;
        int     wScreen, hScreen, xNew, yNew;
        HDC     hdc;

        // Get the Height and Width of the child window
        GetWindowRect (hwndChild, &rChild);
        wChild = rChild.right - rChild.left;
        hChild = rChild.bottom - rChild.top;

        // Get the Height and Width of the parent window
        GetWindowRect (hwndParent, &rParent);
        wParent = rParent.right - rParent.left;
        hParent = rParent.bottom - rParent.top;

        // Get the display limits
        hdc = GetDC (hwndChild);
        wScreen = GetDeviceCaps (hdc, HORZRES);
        hScreen = GetDeviceCaps (hdc, VERTRES);
        ReleaseDC (hwndChild, hdc);

        // Calculate new X position, then adjust for screen
        xNew = rParent.left + ((wParent - wChild) /2);
        if (xNew < 0)
          xNew = 0;
        else if ((xNew+wChild) > wScreen)
               xNew = wScreen - wChild;


        // Calculate new Y position, then adjust for screen
        yNew = rParent.top  + ((hParent - hChild) /2);
        if (yNew < 0)
           yNew = 0;
        else if ((yNew+hChild) > hScreen)
               yNew = hScreen - hChild;


        // Set it, and return
        return SetWindowPos (hwndChild, NULL,
                xNew, yNew, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

/****************************************************************************
*  WndProc(HWND, UINT, WPARAM, LPARAM)
****************************************************************************/
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message,
                             WPARAM wParam, LPARAM lParam)
  {
  FARPROC      lpProcAbout, lpDlgProc;
  PAINTSTRUCT  ps;
  int          knum;
  int          i,j;
  int          retval;
  HBRUSH       hSaveBrush, hbrush1;
  HPEN         hSavePen,   hpen1;
  int          wmId, wmEvent;

  switch (message)
    {
    case WM_COMMAND:

#if defined (_WIN32) || defined(WIN32)
         wmId    = LOWORD(wParam);
         wmEvent = HIWORD(wParam);
#else
         wmId    = wParam;
         wmEvent = HIWORD(lParam);
#endif

         switch (wmId)
           {
           case IDM_EXIT:
                DestroyWindow (hWnd);
                break;

           case IDM_ABOUT :
                lpProcAbout = MakeProcInstance(About, hInst);
                DialogBox(hInst, "AboutBox", hWnd, lpProcAbout);
                FreeProcInstance(lpProcAbout);
                break;

           case IDM_OPTIONS:
                lpDlgProc = MakeProcInstance(OptionsDlgProc, hInst);
                retval = DialogBox(hInst, "OPTIONS", hWnd, lpDlgProc);
                FreeProcInstance(lpDlgProc);

                if (retval == IDOK)
                  InvalidateRect (hWnd, NULL, TRUE);
                break;


           }
         break;

    case WM_SIZE:
         xClient = LOWORD(lParam);
         yClient = HIWORD(lParam);
         ScrX0 = xClient / 2;
         ScrY0 = yClient / 2;
         SetupParam();

         break;

    case WM_PAINT:

         hSaveCursor = SetCursor(hHourGlass);

         hDC = BeginPaint (hWnd, &ps);
         SaveMapMode = SetMapMode(hDC, MM_ISOTROPIC);

#if defined (_WIN32) || defined(WIN32)
         SetViewportExtEx(hDC, 1, - 1, NULL);
         SetViewportOrgEx(hDC, ScrX0, ScrY0, NULL);
         SetWindowExtEx(hDC, 1, 1, NULL);
         SetWindowOrgEx(hDC, 0, 0, NULL);
#else
         SetViewportExt(hDC, 1, - 1);
         SetViewportOrg(hDC, ScrX0, ScrY0);
         SetWindowExt(hDC, 1, 1);
         SetWindowOrg(hDC, 0, 0);
#endif

         hSaveBrush = SelectObject(hDC, (HBRUSH)(COLOR_WINDOW+1));
         hSavePen   = SelectObject(hDC, (HPEN)(COLOR_WINDOWTEXT));

         knum = 0;
         for (i = 1;     i <= MaxGrid; i++)
           {
           for (j = i + 1; j <= MaxGrid; j++)
             {
             if (bFillTiling)
                if (MaxGrid <= 5)
                  {
                  SelectObject(hDC, hbrush[knum]);
                  SelectObject(hDC, hpen[knum]);
                  }
                else
                  {
                  hbrush1 = CreateSolidBrush(RGB(255-7*(knum), 8*(knum+1), 16*knum));
                  SelectObject(hDC, hbrush1);
                  hpen1   = CreatePen(PS_SOLID, 1,
                                          RGB(255-7*(knum-1), 8*knum, 16*knum));
                  }
             knum++;

             ProcessVectors(g[i], g[j], d[i], d[j]);

             SelectObject(hDC, hSaveBrush);
             SelectObject(hDC, hSavePen);
             DeleteObject(hbrush1);
             DeleteObject(hpen1);
             }
           };

         SetMapMode(hDC,SaveMapMode);

         EndPaint (hWnd, &ps);
         SetCursor(hSaveCursor);

         break;

    case WM_CREATE:
         {
         char szBuff[128];

          getcwd(szBuff, sizeof(szBuff));
          if (szBuff[strlen(szBuff)-1] != '\\')
            strcat(szBuff, "\\");
         strcat(szBuff, szIniFileName);
         strcpy(szIniFileName, szBuff);  /* ini file will be in cur. dir now */

         ReadIniFile( (LPCSTR)szIniFileName);

         SetupParam();

         hbrush[0] = CreateSolidBrush(RGB(255,   0,   0));
         hbrush[1] = CreateSolidBrush(RGB(0,   255, 255));
    		 hbrush[2] = CreateSolidBrush(RGB(0,     0, 255));
         hbrush[3] = CreateSolidBrush(RGB(0,   255,   0));
         hbrush[4] = CreateSolidBrush(RGB(0,     0, 127));
         hbrush[5] = CreateSolidBrush(RGB(255, 255,   0));
         hbrush[6] = CreateSolidBrush(RGB(127, 127, 127));
         hbrush[7] = CreateSolidBrush(RGB(127,   0,   0));
         hbrush[8] = CreateSolidBrush(RGB(255,   0, 255));
         hbrush[9]= CreateSolidBrush(RGB(0  , 127, 127));

         hpen[0] = CreatePen(PS_SOLID, 1, RGB(255,   0,   0));
         hpen[1] = CreatePen(PS_SOLID, 1, RGB(0,   255, 255));
         hpen[2] = CreatePen(PS_SOLID, 1, RGB(0,     0, 255));
         hpen[3] = CreatePen(PS_SOLID, 1, RGB(0,   255,   0));
         hpen[4] = CreatePen(PS_SOLID, 1, RGB(0,     0, 127));
         hpen[5] = CreatePen(PS_SOLID, 1, RGB(255, 255,   0));
         hpen[6] = CreatePen(PS_SOLID, 1, RGB(127, 127, 127));
         hpen[7] = CreatePen(PS_SOLID, 1, RGB(127,   0,   0));
         hpen[8] = CreatePen(PS_SOLID, 1, RGB(255,   0, 255));
         hpen[9] = CreatePen(PS_SOLID, 1, RGB(0  , 127, 127));

         break;
         }

    case WM_DESTROY:
         for (i = 0; i < 10; i++)
           {
           DeleteObject(hbrush[i]);
           DeleteObject(hpen[i]);
           }
         PostQuitMessage(0);
         break;

    default:
         return (DefWindowProc(hWnd, message, wParam, lParam));
    };
    return (0);
}


/***************************************************************************
*   About(HWND, unsigned, WORD, LONG)
****************************************************************************/
LRESULT CALLBACK About(HWND hDlg, UINT message,
                       WPARAM wParam, LPARAM lParam)
  {
  switch (message)
    {
    case WM_INITDIALOG:
      // Center the dialog over the application window
      CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
      return (TRUE);

    case WM_COMMAND:
      if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
        EndDialog(hDlg, TRUE);
        return (TRUE);
        }
	    break;
    }
    return (FALSE);

    lParam;
}

/**************************************************************************
*  ReadIniFile(LPCSTR)
*
*  Reads options from the application ini file
***************************************************************************/
BOOL ReadIniFile(LPCSTR szIniFileName)
  {
  int ival;

  ival = (int) GetPrivateProfileInt((LPSTR)"options", (LPSTR)"size",
                                       SIZE_MEDIUM, (LPSTR)szIniFileName);

  if ( ival >= 0  && ival <= SIZE_LARGE)
    TilingSize = ival;
  else
    TilingSize = SIZE_MEDIUM;

  ival = (int) GetPrivateProfileInt((LPSTR)"options", (LPSTR)"dimension",
                                       5, (LPSTR)szIniFileName);

  if ( (ival >= 3)  && (ival <= NumMaxGrid) && (ival % 2 != 0) )
    MaxGrid = ival;
  else
    MaxGrid = 5;

  ival = (int) GetPrivateProfileInt((LPSTR)"options", (LPSTR)"fill",
                                       1, (LPSTR)szIniFileName);

  if (ival == 0)
    bFillTiling = FALSE;
  else
    bFillTiling = TRUE;

  return TRUE;
  }

/**************************************************************************
*  WriteIniFile(LPCSTR)
*
*  Writes options to the application ini file
***************************************************************************/
BOOL  WriteIniFile(LPCSTR szIniFileName)
  {
  char  szBuff[128];

  sprintf(szBuff, "%d", TilingSize);
  WritePrivateProfileString("options", "size",
                              szBuff, szIniFileName);

  sprintf(szBuff, "%d", MaxGrid);
  WritePrivateProfileString("options", "dimension",
                              szBuff, szIniFileName);

  sprintf(szBuff, "%d", bFillTiling);
  WritePrivateProfileString("options", "fill",
                              szBuff, szIniFileName);

  return TRUE;
  }

/***************************************************************************
*  SetupParam()
*
*  sets parameters of the tiling
***************************************************************************/
void SetupParam(void)
  {
  double  sl;
  int     i;
  switch (TilingSize)
    {
    case SIZE_AUTO:
       break;
    case SIZE_SMALL:
       Rsize = 30;
       break;
    case SIZE_MEDIUM:
       Rsize = 60;
       break;
    case SIZE_LARGE:
       Rsize = 120;
       break;
    default:
       TilingSize = SIZE_MEDIUM;
       Rsize = 60;
       break;
    }

  if (MaxGrid > NumMaxGrid)
    MaxGrid = NumMaxGrid;

   kdim = 1;

  if (TilingSize != SIZE_AUTO)
    {
    sl = (MaxGrid-1)* kdim*Rsize;
    MaxStep = (int) ceil((xClient+yClient)/(2*sl))+1;
    }
  else
    {
    MaxStep = 2;
    Rsize = (xClient+yClient)/(3*(MaxStep-1)*kdim*(MaxGrid-1));
    };

   alfa0 = 2.0 * PI/MaxGrid;
   for (i = 1; i <= MaxGrid; i++)
     {
     alfa[i] = alfa0 * (i-1);
     g[i][1] = Rsize*cos(alfa[i]);
     g[i][2] = Rsize*sin(alfa[i]);
     d[i] =  Rsize * 0.33;
     };
  }

/**************************************************************************/
