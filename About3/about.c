#include <windows.h>
#include "resource.h"

LRESULT CALLBACK EllipPushProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	RECT rect;
	TCHAR szText[40];
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush;
	
	switch(message){
		case WM_PAINT:
			GetClientRect(hwnd,&rect);
			GetWindowText(hwnd,szText,sizeof(szText));
			
			hdc = BeginPaint(hwnd,&ps);

			hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
			hBrush = (HBRUSH)SelectObject(hdc,hBrush);
			SetBkColor(hdc,GetSysColor(COLOR_WINDOW));
			SetTextColor(hdc,GetSysColor(COLOR_WINDOWTEXT));
			Ellipse(hdc,rect.left,rect.top,rect.right,rect.bottom);
			DrawText(hdc,szText,-1,&rect,DT_SINGLELINE | DT_CENTER | DT_VCENTER);	
			DeleteObject(SelectObject(hdc,hBrush));
		
			EndPaint(hwnd,&ps);

			return 0;

		case WM_LBUTTONUP:
			//MessageBox(hwnd,"WM_LBUTTONUP","tip",0);
			SendMessage(GetParent(hwnd),WM_COMMAND,GetWindowLong(hwnd,GWL_ID),(LPARAM)hwnd);

			return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

BOOL CALLBACK AboutDlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
	static int iColor,iFigure;
	static HWND hCtrlBlock;

	switch(message){
		case WM_INITDIALOG:
			
			return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDOK:
					EndDialog(hDlg,0);

					return TRUE;

				case IDCANCEL:
					EndDialog(hDlg,FALSE);

					return TRUE;
			}

			break;
	}

	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	static HINSTANCE hInstance;
	//0x00000024
	switch(message){
		case WM_CREATE:
			hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
			
			return 0;

		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDM_APP_ABOUT:
					DialogBox(hInstance,"AboutBox",hwnd,AboutDlgProc);

					return 0;
			}
			
			break;

		case WM_DESTROY:
			PostQuitMessage(0);

			return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = "About3";
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
	wndclass.lpszMenuName = szAppName;
	wndclass.lpszClassName = szAppName;
	if(!RegisterClass(&wndclass)){
		MessageBox(NULL,"The program requires Windows NT",szAppName,MB_ICONERROR);
	
		return 0;
	}

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = EllipPushProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = NULL;
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "EllipPush";
	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName,"The About3 program",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
