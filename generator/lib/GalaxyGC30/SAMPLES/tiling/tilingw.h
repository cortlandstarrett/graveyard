/*************************************************************************
*  tilingw.h  header file for tilingw,
*   MSW version of the Galaxy tiling sample
**************************************************************************/

#define IDM_ABOUT     100
#define IDM_EXIT      110
#define IDM_OPTIONS   120
#define IDM_STOPPAINT 130

#define IDC_TSIZE 205
#define IDC_DIM   210
#define IDC_SAVE  220
#define IDC_FILL  230

#define  PI  (3.14159)
#define  NumMaxGrid    13    /* maximal dimension of the grid  */

#define  SIZE_AUTO    0
#define  SIZE_SMALL   1
#define  SIZE_MEDIUM  2
#define  SIZE_LARGE   3

typedef double vector[3];

typedef  POINT  RHOMBUS[4];

extern char szIniFileName[128];
extern char szApplName[32];

extern int  MaxGrid;         /* dimension of the grid  */
extern int  MaxStep;
extern int  kdim;            /* coefficient for determination of MaxStep */
extern double  Rsize;
extern int TilingSize;
extern BOOL  AutoSize;

extern double  alfa0;
extern double  alfa[NumMaxGrid+1];
extern double  d[NumMaxGrid+1];
extern vector  g[NumMaxGrid+1];

extern HDC hDC;
extern BOOL  bFillTiling;

int  APIENTRY  WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About  (HWND, UINT, WPARAM, LPARAM);
BOOL CenterWindow (HWND hwndChild, HWND hwndParent);
LRESULT CALLBACK OptionsDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL  ProcessVectors(vector, vector, double, double);
BOOL  ReadIniFile( LPCSTR  IniFileName);
BOOL  WriteIniFile(LPCSTR IniFileName);
void SetupParam(void);
