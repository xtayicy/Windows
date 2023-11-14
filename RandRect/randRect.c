#include <windows.h>
#include <process.h>

int cxClient, cyClient;
HWND hwnd;

void Thread (PVOID pvoid)
{
     HBRUSH hBrush ;
     HDC    hdc ;
     int    xLeft, xRight, yTop, yBottom, iRed, iGreen, iBlue ;
     
     while (TRUE)
     {
          if (cxClient != 0 || cyClient != 0)
          {
               xLeft   = rand () % cxClient ;
               xRight  = rand () % cxClient ;
               yTop    = rand () % cyClient ;
               yBottom = rand () % cyClient ;
               iRed    = rand () & 255 ;
               iGreen  = rand () & 255 ;
               iBlue   = rand () & 255 ;
               
               hdc = GetDC (hwnd) ;
               hBrush = CreateSolidBrush (RGB (iRed, iGreen, iBlue)) ;
               SelectObject (hdc, hBrush) ;
               
               Rectangle (hdc, min (xLeft, xRight), min (yTop, yBottom),
                               max (xLeft, xRight), max (yTop, yBottom)) ;
               
               ReleaseDC (hwnd, hdc) ;
               DeleteObject (hBrush) ;
          }
     }
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;

	//0x00000024
	switch(message){
		case WM_CREATE:
			_beginthread (Thread, 0, NULL) ;

			return 0;

		case WM_SIZE:
			// 0x000003f1 1009
			cxClient = LOWORD(lParam);
			// 0x000001ef 495
			cyClient = HIWORD(lParam);

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
	static TCHAR szAppName[] = TEXT("RandRect");
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
		MessageBox(NULL,TEXT("The program requires Windows NT"),szAppName,MB_ICONERROR);
	
		return 0;
	}

	hwnd = CreateWindow(szAppName,TEXT("The RandRect program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
