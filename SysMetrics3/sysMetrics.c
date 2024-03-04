#define WINVER 0x0500
#include <windows.h>
#include "sysmets.h"

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	static int cxChar,cxCaps,cyChar,cyClient,iMaxWidth,cxClient;
	int i,iVertPos,iPaintBeg,iPaintEnd,y;
	TCHAR szBuffer[10];
	SCROLLINFO si;
	//RECT rect;
	//0x00000024
	switch(message){
		case WM_CREATE:
			hdc = GetDC(hwnd);
			
			GetTextMetrics(hdc,&tm);
			cxChar = tm.tmAveCharWidth;
			cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
			cyChar = tm.tmHeight + tm.tmExternalLeading;

			ReleaseDC(hwnd,hdc);

			iMaxWidth = 22 * cxCaps + 40 * cxChar;

			return 0;

			case WM_SIZE:
				cxClient = LOWORD(lParam);
				cyClient = HIWORD(lParam);

				si.cbSize = sizeof(si);
				si.fMask = SIF_RANGE | SIF_PAGE;
				si.nMin = 0;
				si.nMax = NUMLINES - 1;
				si.nPage = cyClient / cyChar;

				SetScrollInfo(hwnd,SB_VERT,&si,TRUE);

				return 0;

				case WM_VSCROLL:
					si.cbSize = sizeof(si);
					si.fMask = SIF_ALL;
					GetScrollInfo(hwnd,SB_VERT,&si);
					iVertPos = si.nPos;
					switch(LOWORD(wParam)){
						case SB_LINEDOWN:
							si.nPos += 1;

							break;

						case SB_LINEUP:
							si.nPos -= 1;

							break;

						case SB_PAGEDOWN:
							si.nPos += si.nPage;

							break;

						case SB_PAGEUP:
							si.nPos -= si.nPage;

							break;
							
						default:

							break;
					}
					
					si.fMask = SIF_POS;
					SetScrollInfo(hwnd,SB_VERT,&si,TRUE);
					GetScrollInfo(hwnd,SB_VERT,&si);
					if(si.nPos != iVertPos){
						ScrollWindow(hwnd,0,cyChar * (iVertPos - si.nPos),NULL,NULL);						
						//UpdateWindow(hwnd);
					}

					return 0;

		case WM_PAINT:
			//MessageBox(hwnd,"hello","caption",MB_OK);
			hdc = BeginPaint(hwnd,&ps);
			
			si.cbSize = sizeof(si);
			si.fMask = SIF_POS;
			
			GetScrollInfo(hwnd,SB_VERT,&si);
			iVertPos = si.nPos;
			
			iPaintBeg = max(0,iVertPos + ps.rcPaint.top / cyChar);
			iPaintEnd = min(NUMLINES - 1,iVertPos + ps.rcPaint.bottom / cyChar);
			
			for(i = iPaintBeg;i <= iPaintEnd;i++){
				y = cyChar * (i - iVertPos);
				TextOut(hdc,0,y,sysmetrics[i].szLabel,lstrlen(sysmetrics[i].szLabel));
				TextOut(hdc,22 * cxCaps,y,sysmetrics[i].szDesc,lstrlen(sysmetrics[i].szDesc));
				TextOut(hdc, 22 * cxCaps + 40 * cxChar,y,szBuffer,wsprintf(szBuffer,TEXT("%5d"),GetSystemMetrics(sysmetrics[i].iIndex)));
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
	static TCHAR szAppName[] = TEXT("sysMetrics3");
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

	hwnd = CreateWindow(szAppName,TEXT("The sysMetrics3 program"),WS_OVERLAPPEDWINDOW | WS_VSCROLL,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
