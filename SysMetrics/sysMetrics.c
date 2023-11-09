#define WINVER 0x0500
#include <windows.h>
#include "sysmets.h"
//                                                                   0x01ef03e0 32441312
LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	TEXTMETRIC tm;
	static int cxChar,cxCaps,cyChar,iMaxWidth;
	PAINTSTRUCT ps;
	int i,y,iPaintBeg,iPaintEnd,iVscrollPos;
	TCHAR szBuffer[10];
	static int cyClient,cxClient;
	SCROLLINFO si;

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

			iMaxWidth = 40 * cxChar + 22 * cxCaps;

			return 0;

		case WM_SIZE:
			// 0x000001ef 495
			cyClient = HIWORD(lParam);
			cxClient = LOWORD(lParam);
			
			si.fMask = SIF_RANGE | SIF_PAGE;
			si.cbSize = sizeof(si);
			si.nMin = 0;
			si.nMax = NUMLINES - 1;
			si.nPage = cyClient / cyChar;
			SetScrollInfo(hwnd,SB_VERT,&si,TRUE);

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
			si.cbSize = sizeof(si);
			si.fMask = SIF_POS;
			GetScrollInfo(hwnd,SB_VERT,&si);
			iVscrollPos = si.nPos;
			
			iPaintBeg = max(0,iVscrollPos + ps.rcPaint.top / cyChar);
			iPaintEnd = min(NUMLINES - 1,iVscrollPos + ps.rcPaint.bottom / cyChar);
			for(i = iPaintBeg;i <= iPaintEnd;i++){
				y = cyChar * (i - iVscrollPos);
				TextOut(hdc,0,y,sysmetrics[i].szLabel,lstrlen(sysmetrics[i].szLabel));
				TextOut(hdc,22 * cxCaps,y,sysmetrics[i].szDesc,lstrlen(sysmetrics[i].szDesc));
				//SetTextAlign(hdc,TA_RIGHT | TA_TOP);
				TextOut(hdc,22 * cxCaps + 40 *cxChar,y,szBuffer,wsprintf((szBuffer),TEXT("%5d"),GetSystemMetrics(sysmetrics[i].iIndex)));
				//SetTextAlign(hdc,TA_LEFT | TA_TOP);
			}

			EndPaint(hwnd,&ps);
			
			return 0;

		case WM_VSCROLL:
			si.cbSize = sizeof(si);
			si.fMask = SIF_ALL;
			GetScrollInfo(hwnd,SB_VERT,&si);
			iVscrollPos = si.nPos;
			//0x00000000    0
			switch(LOWORD(wParam)){
				case SB_TOP:
					si.nPos = si.nMin;

					break;

				case SB_BOTTOM:
					si.nPos = si.nMax;

					break;

				case SB_LINEUP:
					si.nPos -= 1;

					break;

				case SB_LINEDOWN:
					si.nPos += 1;

					break;

				case SB_PAGEUP:
					si.nPos -= si.nPage;

					break;

				case SB_PAGEDOWN:
					si.nPos += si.nPage;

					break;

				case SB_THUMBPOSITION:
					si.nPos = si.nTrackPos;

					break;

				default:

					break;
			}

			si.fMask = SIF_POS;
			SetScrollInfo(hwnd,SB_VERT,&si,TRUE);
			GetScrollInfo(hwnd,SB_VERT,&si);
			if(si.nPos != iVscrollPos){
				ScrollWindow(hwnd,0,cyChar * (iVscrollPos - si.nPos),NULL,NULL);
				//UpdateWindow(hwnd);
			}

			return 0;

		case WM_KEYDOWN:
			switch(wParam){
				case VK_HOME:
					SendMessage(hwnd,WM_VSCROLL,SB_TOP,0);

					break;

				case VK_END:
					SendMessage(hwnd,WM_VSCROLL,SB_BOTTOM,0);

					break;

				case VK_PRIOR:
					SendMessage(hwnd,WM_VSCROLL,SB_PAGEUP,0);
					
					break;

				case VK_NEXT:
					SendMessage(hwnd,WM_VSCROLL,SB_PAGEDOWN,0);

					break;

				case VK_UP:
					SendMessage(hwnd,WM_VSCROLL,SB_LINEUP,0);

					break;

				case VK_DOWN:
					SendMessage(hwnd,WM_VSCROLL,SB_LINEDOWN,0);

					break;
			}

			return 0;


		case WM_DESTROY:
			PostQuitMessage(0);

			return 0;
	}
	

	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = TEXT("SysMetrics");
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

	hwnd = CreateWindow(szAppName,TEXT("Get System Metrics"),WS_OVERLAPPEDWINDOW | WS_VSCROLL,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
