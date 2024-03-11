#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND hwndNextViewer;
	RECT rect;
	HGLOBAL hGlobal;
	PTSTR pGlobal;
	
	//0x00000024
	switch(message){
		case WM_CREATE:
			hwndNextViewer = SetClipboardViewer(hwnd);

			return 0;

		case WM_CHANGECBCHAIN:
			MessageBox(hwnd,"WM_CHANGECBCHAIN","tip",0);

			return 0;

		case WM_DRAWCLIPBOARD:
			//MessageBox(hwnd,"WM_DRAWCLIPBOARD","tip",0);
			if(hwndNextViewer){
				SendMessage(hwndNextViewer,message,wParam,lParam);
			}

			InvalidateRect(hwnd,NULL,TRUE);

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);

			GetClientRect(hwnd,&rect);
			OpenClipboard(hwnd);
#ifdef UNICODE
			hGlobal = GetClipboardData(CF_UNICOETEXTD);
#else
			hGlobal = GetClipboardData(CF_TEXT);
#endif
			if(hGlobal != NULL){
				pGlobal = (PTSTR)GlobalLock(hGlobal);
				DrawText(hdc,pGlobal,-1,&rect,DT_EXPANDTABS);
				GlobalUnlock(hGlobal);
			}

			CloseClipboard();

			EndPaint(hwnd,&ps);
			
			return 0;

		case WM_DESTROY:
			ChangeClipboardChain(hwnd,hwndNextViewer);
			PostQuitMessage(0);

			return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = "ClipView";
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

	hwnd = CreateWindow(szAppName,"The ClipView program",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
