#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	HINSTANCE hInstance;
	static HMENU hMenuMain,hMenuFile,hMenuEdit;
	
	//0x00000024
	switch(message){
		case WM_CREATE:
			hInstance = (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE);
			hMenuMain = LoadMenu(hInstance,"MenuMain");
			hMenuFile = LoadMenu(hInstance,"MenuFile");
			hMenuEdit = LoadMenu(hInstance,"MenuEdit");
			SetMenu(hwnd,hMenuMain);

			return 0;

		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDM_FILE:
					SetMenu(hwnd,hMenuFile);

					return 0;

				case IDM_MAIN:
					SetMenu(hwnd,hMenuMain);

					return 0;

				case IDM_EDIT:
					SetMenu(hwnd,hMenuEdit);

					return 0;

				case IDM_FILE_NEW:
				case IDM_EDIT_UNDO:
					MessageBeep(0);

					return 0;
			}

			break;

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
	static TCHAR szAppName[] = "NoPupUps";
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

	hwnd = CreateWindow(szAppName,"The NoPupUps program",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
