#include <windows.h>
#include "DeviceCaps.h"

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	static int cxChar,cxCaps,cyChar;
	int i;
	TCHAR szBuffer[10];

	//0x00000024
	switch(message){
		case WM_CREATE:
			hdc = GetDC(hwnd);
			GetTextMetrics(hdc,&tm);
			// 7              7
			cxChar = tm.tmAveCharWidth;
			//10               33                           7
			cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
			//16           16                  0
			cyChar = tm.tmHeight + tm.tmExternalLeading;
			ReleaseDC(hwnd,hdc);
			
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			for(i = 0;i < NUMLINES;i++){
				TextOut(hdc,0,cyChar * i,devcaps[i].szLabel,lstrlen(devcaps[i].szLabel));
				TextOut(hdc,14 * cxCaps,cyChar * i,devcaps[i].szDesc,lstrlen(devcaps[i].szDesc));
				//SetTextAlign(hdc,TA_RIGHT | TA_TOP);
				TextOut(hdc,14 * cxCaps + 35 *cxChar,cyChar * i,szBuffer,wsprintf((szBuffer),TEXT("%5d"),GetSystemMetrics(devcaps[i].iIndex)));
				//SetTextAlign(hdc,TA_LEFT | TA_TOP);
			}
			
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
	static TCHAR szAppName[] = TEXT("DeviceCaps");
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

	hwnd = CreateWindow(szAppName,TEXT("The DeviceCaps program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
