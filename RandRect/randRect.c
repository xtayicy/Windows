#include <windows.h>

int cxClient, cyClient;

void DrawRectangle(HWND hwnd){
	RECT rect;
	HBRUSH hBrush;
	HDC hdc;

	if(cxClient == 0 || cyClient == 0){
		return;
	}

	SetRect(&rect,rand() % cxClient,rand() % cyClient,rand() % cxClient,rand() % cyClient);
	hBrush = CreateSolidBrush(RGB(rand() % 256,rand() % 256,rand() % 256));
	hdc = GetDC(hwnd);
	FillRect(hdc,&rect,hBrush);
	ReleaseDC(hwnd,hdc);
	DeleteObject(hBrush);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;

	//0x00000024
	switch(message){
		case WM_CREATE:
			
			return 0;

		case WM_SIZE:
			// 0x000003f1 1009
			cxClient = LOWORD(lParam);
			// 0x000001ef 495
			cyClient = HIWORD(lParam);

			return 0;

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
	static TCHAR szAppName[] = TEXT("RandRect");
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

	hwnd = CreateWindow(szAppName,TEXT("The RandRect program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(TRUE){
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
			if(msg.message == WM_QUIT){
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}else{
			DrawRectangle(hwnd);
		}
	}

	return 0;
}
