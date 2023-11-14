#include <windows.h>
#include "resource.h"

HMENU     hMenuInit, hMenuHello ;
TCHAR     szHelloClass[] = TEXT ("MdiHelloChild") ;
HINSTANCE hInst ;
HMENU     hMenuInitWindow, hMenuHelloWindow;
#define IDM_FIRSTCHILD   50000
#define INIT_MENU_POS    0
#define HELLO_MENU_POS   1

typedef struct tagHELLODATA
{
     UINT     iColor ;
     COLORREF clrText ;
}
HELLODATA, * PHELLODATA ;

LRESULT CALLBACK HelloWndProc (HWND hwnd, UINT message,WPARAM wParam, LPARAM lParam){
	HDC             hdc ;
	PHELLODATA      pHelloData ;
	PAINTSTRUCT     ps ;
	RECT            rect ;
	char szError[256];
	static HWND     hwndClient, hwndFrame ;
	
	switch(message){
		case WM_CREATE:
			pHelloData = (PHELLODATA) HeapAlloc (GetProcessHeap (),HEAP_ZERO_MEMORY, sizeof (HELLODATA)) ;
			pHelloData->clrText = RGB (0, 0, 0) ;
			SetWindowLong (hwnd, 0, (long) pHelloData) ;
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(),0,szError,sizeof(szError),NULL);
			
			return 0;

		case WM_PAINT:
			hdc = BeginPaint (hwnd, &ps);

			pHelloData = (PHELLODATA) GetWindowLong (hwnd, 0) ;
            SetTextColor (hdc, pHelloData->clrText) ;
			GetClientRect (hwnd, &rect) ;
            DrawText (hdc, TEXT ("Hello, World!"), -1, &rect,
                    DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
               
			EndPaint (hwnd, &ps) ;

			return 0;

		case WM_DESTROY:
			pHelloData = (PHELLODATA) GetWindowLong (hwnd, 0) ;
            HeapFree (GetProcessHeap (), 0, pHelloData) ;

			return 0;
	}

	return DefMDIChildProc (hwnd, message, wParam, lParam) ;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	MDICREATESTRUCT    mdicreate ;
	HWND               hwndChild ;
	static HWND        hwndClient ;
	//CLIENTCREATESTRUCT clientcreate ;
	char szError[256];

	//0x00000024
	switch(message){
		case WM_CREATE:
			//clientcreate.hWindowMenu  = hMenuInitWindow ;
			//clientcreate.idFirstChild = IDM_FIRSTCHILD ;
			hwndClient = CreateWindow (TEXT ("MDICLIENT"), NULL,
                                     WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,   
                                     0, 0, 0, 0, hwnd, NULL, hInst,
                                     NULL) ;
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(),0,szError,sizeof(szError),NULL);

			return 0;

		case WM_COMMAND:
			switch(LOWORD (wParam)){
				case IDM_FILE_NEW_HELLO:
					mdicreate.szClass = szHelloClass ;
					mdicreate.szTitle = TEXT ("Hello") ;
					mdicreate.hOwner  = hInst ;
					mdicreate.x       = CW_USEDEFAULT ;
					mdicreate.y       = CW_USEDEFAULT ;
					mdicreate.cx      = CW_USEDEFAULT ;
					mdicreate.cy      = CW_USEDEFAULT ;
					mdicreate.style   = 0 ;
					mdicreate.lParam  = 0 ;

					hwndChild = (HWND) SendMessage (hwndClient,
									   WM_MDICREATE, 0,
									   (LPARAM) (LPMDICREATESTRUCT) &mdicreate) ;

					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(),0,szError,sizeof(szError),NULL);

					return 0;
			}

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
			EndPaint(hwnd,&ps);
			
			return 0;

		case WM_MDIACTIVATE:

			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);

			return 0;
	}

	return DefFrameProc (hwnd, hwndClient, message, wParam, lParam) ;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = TEXT("MDIDemo");
	HWND hwnd,hwndClient;
	MSG msg;
	char szError[256];

	hInst = hInstance;
	
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) (COLOR_APPWORKSPACE + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if(!RegisterClass(&wndclass)){
		MessageBox(NULL,TEXT("The program requires Windows NT"),szAppName,MB_ICONERROR);
	
		return 0;
	}

	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(),0,szError,sizeof(szError),NULL);

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = HelloWndProc ;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = sizeof (HANDLE) ;
    wndclass.hInstance     = hInstance ;
    wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName  = NULL;
    wndclass.lpszClassName = szHelloClass ;
          
    RegisterClass (&wndclass) ;

	hMenuInit  = LoadMenu (hInstance, MAKEINTRESOURCE(IDR_MENU)) ;
	hMenuInitWindow  = GetSubMenu (hMenuInit, INIT_MENU_POS) ;

	hwnd = CreateWindow(szAppName,TEXT("The MDIDemo program"),WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,hMenuInit,hInstance,NULL);
	hwndClient = GetWindow (hwnd, GW_CHILD) ;
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(),0,szError,sizeof(szError),NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		if (!TranslateMDISysAccel (hwndClient, &msg))
          {
               TranslateMessage (&msg) ;
               DispatchMessage (&msg) ;
          }
	}

	return msg.wParam;
}
