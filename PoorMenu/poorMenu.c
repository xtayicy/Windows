#include <windows.h>
#define IDM_SYS_ABOUT 1
#define IDM_SYS_HELP 2
#define IDM_SYS_REMOVE 3

static TCHAR szAppName[] = TEXT("PoorMenu");

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	switch(message){
		case WM_SYSCOMMAND:
			switch(LOWORD(wParam)){
				case IDM_SYS_ABOUT:
					MessageBox(hwnd,"A Poor-Person's Menu Program\n""(c) Charles Petzold, 1998",szAppName,MB_OK | MB_ICONINFORMATION);

					return 0;

				case IDM_SYS_HELP:
					MessageBox(hwnd,"Help not yet implemented!",szAppName,MB_OK | MB_ICONEXCLAMATION);

					return 0;

				case IDM_SYS_REMOVE:
					GetSystemMenu(hwnd,TRUE);

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
	HWND hwnd;
	MSG msg;
	HMENU hMenu;
	
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

	hwnd = CreateWindow(szAppName,TEXT("The PoorMenu program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	
	hMenu = GetSystemMenu(hwnd,FALSE);
	AppendMenu(hMenu,MF_SEPARATOR,0,NULL);
	AppendMenu(hMenu,MF_STRING,IDM_SYS_ABOUT,"About...");
	AppendMenu(hMenu,MF_STRING,IDM_SYS_HELP,"Help...");
	AppendMenu(hMenu,MF_STRING,IDM_SYS_REMOVE,"Remove Additions");
	
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
