#include <windows.h>
#include "buttonLook.h"

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static int   cxChar, cyChar ;
	static TCHAR szTop[]    = TEXT ("message            wParam       lParam"),
                  szUnd[]    = TEXT ("_______            ______       ______"),
                  szFormat[] = TEXT ("%-16s%04X-%04X    %04X-%04X"),
                  szBuffer[50] ;
	int          i ;
	static HWND  hwndButton[NUM] ;
	static RECT  rect ;
	
	//0x00000024
	switch(message){
		case WM_CREATE:
			cxChar = LOWORD (GetDialogBaseUnits ()) ;
			cyChar = HIWORD (GetDialogBaseUnits ()) ;
			for (i = 0 ; i < NUM ; i++)
               hwndButton[i] = CreateWindow ( TEXT("button"), 
                                   button[i].szText,
                                   WS_CHILD | WS_VISIBLE | button[i].iStyle,
                                   cxChar, cyChar * (1 + 2 * i),
                                   20 * cxChar, 7 * cyChar / 4,
                                   hwnd, (HMENU) i,
                                   ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;

			return 0;

		case WM_SIZE:
			rect.left   = 24 * cxChar ;
			rect.top    =  2 * cyChar ;
			rect.right  = LOWORD (lParam) ;
			rect.bottom = HIWORD (lParam) ;

			return 0;

		case WM_DRAWITEM:
		case WM_COMMAND:
			ScrollWindow (hwnd, 0, -cyChar, &rect, &rect) ;
			
			hdc = GetDC (hwnd) ;

			SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT)) ;
      
			TextOut (hdc, 24 * cxChar, cyChar * (rect.bottom / cyChar - 1),
					   szBuffer,
					   wsprintf (szBuffer, szFormat,
							 message == WM_DRAWITEM ? TEXT ("WM_DRAWITEM") : 
													  TEXT ("WM_COMMAND"),
							 HIWORD (wParam), LOWORD (wParam),
							 HIWORD (lParam), LOWORD (lParam))) ;
      
			ReleaseDC (hwnd, hdc) ;

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
			SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT)) ;
            SetBkMode (hdc, TRANSPARENT) ;
			TextOut (hdc, 24 * cxChar, cyChar, szTop, lstrlen (szTop)) ;
			TextOut (hdc, 24 * cxChar, cyChar, szUnd, lstrlen (szUnd)) ;

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
	static TCHAR szAppName[] = TEXT("ButtonLook");
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

	hwnd = CreateWindow(szAppName,TEXT("The ButtonLook program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
