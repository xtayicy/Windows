#include <windows.h>
#include "resource.h"

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	static int cxChar,cyChar,xScroll,cyClient,iPosition,iNumLines;
	static HWND hScroll;
	static HGLOBAL hResource;
	static char *pText;
	RECT rect;
	
	//0x00000024
	switch(message){
		case WM_CREATE:
			hdc = GetDC(hwnd);
			
			GetTextMetrics(hdc,&tm);
			cxChar = tm.tmAveCharWidth;
			cyChar = tm.tmHeight + tm.tmExternalLeading;

			ReleaseDC(hwnd,hdc);

			xScroll = GetSystemMetrics(SM_CXVSCROLL);
			
			hScroll = CreateWindow("scrollBar",NULL,WS_CHILD | WS_VISIBLE | SBS_VERT,0,0,0,0,hwnd,(HMENU)1,hInst,NULL);
			
			hResource = LoadResource(hInst,FindResource(hInst,"AnnabelLee","TEXT"));
			pText = (char*)LockResource(hResource);
			iNumLines = 0;
			while(*pText != '\\' && pText != '\0'){
				if(*pText == '\n'){
					iNumLines++;
				}

				pText = AnsiNext(pText);
			}

			*pText = '\0';
			SetScrollRange(hScroll,SB_CTL,0,iNumLines,FALSE);
			SetScrollPos(hScroll,SB_CTL,0,FALSE);

			return 0;

		case WM_SIZE:
			MoveWindow(hScroll,LOWORD(lParam) - xScroll,0,xScroll,cyClient = HIWORD(lParam),TRUE);
			SetFocus(hwnd);

			return 0;

		case WM_SETFOCUS:
			SetFocus(hScroll);

			return 0;

		case WM_VSCROLL:
			switch(wParam){
				case SB_LINEDOWN:
					iPosition += 1;

					break;

				case SB_LINEUP:
					iPosition -= 1;

					break;
			}

			iPosition = max(0,min(iPosition,iNumLines));
			if(iPosition != GetScrollPos(hScroll,SB_CTL)){
				SetScrollPos(hScroll,SB_CTL,iPosition,TRUE);
				InvalidateRect(hwnd,NULL,TRUE);
			}

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
			pText = (char*)LockResource(hResource);
			GetClientRect(hwnd,&rect);
			rect.left += cxChar;
			rect.top += cyChar * (1 - iPosition);
			DrawTextA(hdc,pText,-1,&rect,DT_EXTERNALLEADING);

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
	static TCHAR szAppName[] = TEXT("PoePoem");
	HWND hwnd;
	MSG msg;

	hInst = hInstance;
	
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

	hwnd = CreateWindow(szAppName,TEXT("The PoePoem program"),WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
