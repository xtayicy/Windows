#include <windows.h>
#include <math.h>

#define NUM 1000
#define TWOPI (2 * 3.14)

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static int cxClient,cyClient;
	int i;
	POINT apt[NUM];

	//0x00000024
	switch(message){
		case WM_SIZE:
			// 0x000003f1 1009
			cxClient = LOWORD(lParam);
			// 0x000001ef 495
			cyClient = HIWORD(lParam);

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
			MoveToEx(hdc,0,cyClient / 2,NULL);
			LineTo(hdc,cxClient,cyClient / 2);
			for(i = 0;i < NUM;i++){
				apt[i].x = i * cxClient / NUM;
				apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / NUM)));
			}

			Polyline(hdc,apt,NUM);

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
	static TCHAR szAppName[] = TEXT("SingleWave");
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

	hwnd = CreateWindow(szAppName,TEXT("The SingleWave program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
