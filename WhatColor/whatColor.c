#include <windows.h>

#define ID_TIMER    1

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static HDC hdcScreen;
	RECT rc;
	TCHAR szBuffer [16] ;
	static COLORREF cr, crLast ;
	POINT pt;

	//0x00000024
	switch(message){
		case WM_CREATE:
			hdcScreen = CreateDC (TEXT ("DISPLAY"), NULL, NULL, NULL) ;
			SetTimer (hwnd, ID_TIMER, 100, NULL) ;

			return 0;

		case WM_TIMER:
			GetCursorPos(&pt);
			cr = GetPixel (hdcScreen, pt.x, pt.y) ;
			if (cr != crLast){
                  crLast = cr ;
                  InvalidateRect (hwnd, NULL, TRUE) ;
            }



			return 0;

		case WM_PAINT:
			hdc = BeginPaint (hwnd, &ps) ;
          
          GetClientRect (hwnd, &rc) ;
          
          wsprintf (szBuffer, TEXT ("  %02X %02X %02X  "),
                    GetRValue (cr), GetGValue (cr), GetBValue (cr)) ;
          
          DrawText (hdc, szBuffer, -1, &rc,
                    DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
          
          EndPaint (hwnd, &ps) ;
			
			return 0;

		case WM_DESTROY:
			DeleteDC(hdcScreen);
			KillTimer(hwnd,ID_TIMER);
			PostQuitMessage(0);

			return 0;
	}
	

	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = TEXT("WhatColor");
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
		MessageBox(NULL,TEXT("The program requires Windows NT"),szAppName,MB_ICONERROR);
	
		return 0;
	}
	
	hwnd = CreateWindow(szAppName,TEXT("The WhatColor program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
