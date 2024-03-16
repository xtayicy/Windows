#include <windows.h>
#include <process.h>
#include <math.h>
#define STATUS_READY     0
#define STATUS_WORKING   1
#define STATUS_DONE      2
#define WM_CALC_DONE     (WM_USER + 0)
#define WM_CALC_ABORTED  (WM_USER + 1)
#define REP              1000000

typedef struct
{
     HWND hwnd ;
     BOOL bContinue ;
}
PARAMS, *PPARAMS ;

void Thread (PVOID pvoid)
{
     double           A = 1.0 ;
     INT              i ;
     LONG             lTime ;
     volatile PPARAMS pparams ;
     
     pparams = (PPARAMS) pvoid ;
     
     lTime = GetCurrentTime () ;
     
     for (i = 0 ; i < REP && pparams->bContinue ; i++)
          A = tan (atan (exp (log (sqrt (A * A))))) + 1.0 ;
     
     if (i == REP)
     {
          lTime = GetCurrentTime () - lTime ;
          SendMessage (pparams->hwnd, WM_CALC_DONE, 0, lTime) ;
     }
     else
          SendMessage (pparams->hwnd, WM_CALC_ABORTED, 0, 0) ;
     
     _endthread () ;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static INT     iStatus ;
	static PARAMS  params ;
	static LONG    lTime ;
	static TCHAR * szMessage[] = { TEXT ("Ready (left mouse button begins)"),
                                    TEXT ("Working (right mouse button ends)"),
                                    TEXT ("%d repetitions in %ld msec") } ;
	RECT           rect ;
	TCHAR          szBuffer[64] ;
	//0x00000024
	switch(message){
		case WM_LBUTTONDOWN:
			if (iStatus == STATUS_WORKING)
			  {
				   MessageBeep (0) ;
				   return 0 ;
			  }
			
			iStatus = STATUS_WORKING ;
			params.hwnd = hwnd ;
			params.bContinue = TRUE ;
			_beginthread (Thread, 0, &params) ;
			InvalidateRect (hwnd, NULL, TRUE) ;

			return 0;

		case WM_RBUTTONDOWN:
			params.bContinue = FALSE ;
			lTime = lParam ;
			iStatus = STATUS_DONE ;
			InvalidateRect (hwnd, NULL, TRUE) ;

			return 0;

		case WM_CALC_DONE:
			//MessageBox(hwnd,"WM_CALC_DOWN","tip",0);

			return 0;

		case WM_CALC_ABORTED:
			MessageBox(hwnd,"WM_CALC_ABORTED","tip",0);

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
			GetClientRect (hwnd, &rect) ;
          
			wsprintf (szBuffer, szMessage[iStatus], REP, lTime) ;
			DrawText (hdc, szBuffer, -1, &rect,
                    DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;

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
	static TCHAR szAppName[] = "BigJob1";
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

	hwnd = CreateWindow(szAppName,"The BigJob1 program",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
