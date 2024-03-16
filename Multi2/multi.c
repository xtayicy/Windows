#include <windows.h>
#include <process.h>
#include <math.h>

typedef struct
{
     HWND hwnd ;
     int  cxClient ;
     int  cyClient ;
     int  cyChar ;
     BOOL bKill ;
}
PARAMS, *PPARAMS ;

int CheckBottom (HWND hwnd, int cyClient, int cyChar, int iLine)
{
     if (iLine * cyChar + cyChar > cyClient)
     {
          InvalidateRect (hwnd, NULL, TRUE) ;
          UpdateWindow (hwnd) ;
          iLine = 0 ;
     }
     return iLine ;
}

void Thread1 (PVOID pvoid)
{
     HDC     hdc ;
     int     iNum = 0, iLine = 0 ;
     PPARAMS pparams ;
     TCHAR   szBuffer[16] ;
     
     pparams = (PPARAMS) pvoid ;
     
     while (!pparams->bKill)
     {
          if (iNum < 0)
               iNum = 0 ;
          
          iLine = CheckBottom (pparams->hwnd,   pparams->cyClient,
                               pparams->cyChar, iLine) ;

          hdc = GetDC (pparams->hwnd) ;
          
          TextOut (hdc, 0, iLine * pparams->cyChar, szBuffer, 
                   wsprintf (szBuffer, TEXT ("%d"), iNum++)) ;               
          
          ReleaseDC (pparams->hwnd, hdc) ;
          iLine++ ;
     }
     _endthread () ;
}

LRESULT APIENTRY WndProc1 (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static PARAMS params ;
     
     switch (message)
     {
     case WM_CREATE:
          params.hwnd = hwnd ;
          params.cyChar = HIWORD (GetDialogBaseUnits ()) ;
          _beginthread (Thread1, 0, &params) ;
          return 0 ;
          
     case WM_SIZE:
          params.cyClient = HIWORD (lParam) ;
          return 0 ;
          
     case WM_DESTROY:
          params.bKill = TRUE ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

// ------------------------------------------------------
// Window 2: Display increasing sequence of prime numbers
// ------------------------------------------------------

void Thread2 (PVOID pvoid)
{
     HDC     hdc ;
     int     iNum = 1, iLine = 0, i, iSqrt ;
     PPARAMS pparams ;
     TCHAR   szBuffer[16] ;
     
     pparams = (PPARAMS) pvoid ;
     
     while (!pparams->bKill)
     {
          do
          {
               if (++iNum < 0)
                    iNum = 0 ;
               
               iSqrt = (int) sqrt (iNum) ;
               
               for (i = 2 ; i <= iSqrt ; i++)
                    if (iNum % i == 0)
                         break ;
          }
          while (i <= iSqrt) ;
          
          iLine = CheckBottom (pparams->hwnd,   pparams->cyClient,
                               pparams->cyChar, iLine) ;
          
          hdc = GetDC (pparams->hwnd) ;
          
          TextOut (hdc, 0, iLine * pparams->cyChar, szBuffer, 
                   wsprintf (szBuffer, TEXT ("%d"), iNum)) ;
          
          ReleaseDC (pparams->hwnd, hdc) ;
          iLine++ ;
     }
     _endthread () ;
}

LRESULT APIENTRY WndProc2 (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static PARAMS params ;
     
     switch (message)
     {
     case WM_CREATE:
          params.hwnd = hwnd ;
          params.cyChar = HIWORD (GetDialogBaseUnits ()) ;
          _beginthread (Thread2, 0, &params) ;
          return 0 ;
          
     case WM_SIZE:
          params.cyClient = HIWORD (lParam) ;
          return 0 ;
          
     case WM_DESTROY:
          params.bKill = TRUE ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

// Window 3: Display increasing sequence of Fibonacci numbers
// ----------------------------------------------------------

void Thread3 (PVOID pvoid)
{
     HDC     hdc ;
     int     iNum = 0, iNext = 1, iLine = 0, iTemp ;
     PPARAMS pparams ;
     TCHAR   szBuffer[16] ;
     
     pparams = (PPARAMS) pvoid ;
     
     while (!pparams->bKill)
     {
          if (iNum < 0)
          {
               iNum  = 0 ;
               iNext = 1 ;
          }
          iLine = CheckBottom (pparams->hwnd,   pparams->cyClient,
                               pparams->cyChar, iLine) ;

          hdc = GetDC (pparams->hwnd) ;
          
          TextOut (hdc, 0, iLine * pparams->cyChar, szBuffer, 
                   wsprintf (szBuffer, TEXT ("%d"), iNum)) ;
          
          ReleaseDC (pparams->hwnd, hdc) ;
          iTemp  = iNum ;
          iNum   = iNext ;
          iNext += iTemp ;
          iLine++ ;
     }
     _endthread () ;
}

LRESULT APIENTRY WndProc3 (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static PARAMS params ;
     
     switch (message)
     {
     case WM_CREATE:
          params.hwnd = hwnd ;
          params.cyChar = HIWORD (GetDialogBaseUnits ()) ;
          _beginthread (Thread3, 0, &params) ;
          return 0 ;
          
     case WM_SIZE:
          params.cyClient = HIWORD (lParam) ;
          return 0 ;
          
     case WM_DESTROY:
          params.bKill = TRUE ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

// -----------------------------------------
// Window 4: Display circles of random radii
// -----------------------------------------

void Thread4 (PVOID pvoid)
{
     HDC     hdc ;
     int     iDiameter ;
     PPARAMS pparams ;
     
     pparams = (PPARAMS) pvoid ;
     
     while (!pparams->bKill)
     {
          InvalidateRect (pparams->hwnd, NULL, TRUE) ;
          UpdateWindow (pparams->hwnd) ;
          
          iDiameter = rand() % (max (1,
                                min (pparams->cxClient, pparams->cyClient))) ;
          
          hdc = GetDC (pparams->hwnd) ;
          
          Ellipse (hdc, (pparams->cxClient - iDiameter) / 2,
                        (pparams->cyClient - iDiameter) / 2,
                        (pparams->cxClient + iDiameter) / 2,
                        (pparams->cyClient + iDiameter) / 2) ;
          
          ReleaseDC (pparams->hwnd, hdc) ;
     }
     _endthread () ;
}

LRESULT APIENTRY WndProc4 (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static PARAMS params ;
     
     switch (message)
     {
     case WM_CREATE:
          params.hwnd = hwnd ;
          params.cyChar = HIWORD (GetDialogBaseUnits ()) ;
          _beginthread (Thread4, 0, &params) ;
          return 0 ;
          
     case WM_SIZE:
          params.cxClient = LOWORD (lParam) ;
          params.cyClient = HIWORD (lParam) ;
          return 0 ;
          
     case WM_DESTROY:
          params.bKill = TRUE ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	HINSTANCE      hInstance ;
	static HWND    hwndChild[4] ;
     static TCHAR * szChildClass[] = { TEXT ("Child1"), TEXT ("Child2"),
                                       TEXT ("Child3"), TEXT ("Child4") } ;
     static WNDPROC ChildProc[] = { WndProc1, WndProc2, WndProc3, WndProc4 } ;
	 WNDCLASS       wndclass ;
	 int            i, cxClient, cyClient ;
	//0x00000024
	switch(message){
		case WM_CREATE:
			hInstance = (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE) ;
			wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
			wndclass.cbClsExtra    = 0 ;
			wndclass.cbWndExtra    = 0 ;
			wndclass.hInstance     = hInstance ;
			wndclass.hIcon         = NULL ;
			wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
			wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
			wndclass.lpszMenuName  = NULL ;
			for (i = 0 ; i < 4 ; i++)
          {
               wndclass.lpfnWndProc   = ChildProc[i] ;
               wndclass.lpszClassName = szChildClass[i] ;
               
               RegisterClass (&wndclass) ;
               
               hwndChild[i] = CreateWindow (szChildClass[i], NULL,
                                   WS_CHILDWINDOW | WS_BORDER | WS_VISIBLE,
                                   0, 0, 0, 0, 
                                   hwnd, (HMENU) i, hInstance, NULL) ;
          }

			return 0;

		case WM_SIZE:
			cxClient = LOWORD (lParam) ;
			cyClient = HIWORD (lParam) ;
          
          for (i = 0 ; i < 4 ; i++)
               MoveWindow (hwndChild[i], (i % 2) * cxClient / 2,
                                         (i > 1) * cyClient / 2,
                           cxClient / 2, cyClient / 2, TRUE) ;

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);

			EndPaint(hwnd,&ps);
			
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);

			return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = "Multi2";
	HWND hwnd;
	MSG msg;
	
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if(!RegisterClass(&wndclass)){
		MessageBox(NULL,"The program requires Windows NT",szAppName,MB_ICONERROR);
	
		return 0;
	}

	hwnd = CreateWindow(szAppName,"The Multi2 program",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
