#include <windows.h>

void DrawBezier(HDC hdc,POINT apt[]){
	//char szError[256];

	PolyBezier(hdc,apt,4);
	//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(),0,szError,sizeof(szError),NULL);
	MoveToEx(hdc,apt[0].x,apt[0].y,NULL);
	LineTo(hdc,apt[1].x,apt[1].y);
	//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(),0,szError,sizeof(szError),NULL);
	MoveToEx(hdc,apt[2].x,apt[2].y,NULL);
	LineTo(hdc,apt[3].x,apt[3].y);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	int cxClient,cyClient;
	static POINT apt[4];
	
	//0x00000024
	switch(message){
		case WM_SIZE:
			// 0x000003f1 1009
			cxClient = LOWORD(lParam);
			// 0x000001ef 495
			cyClient = HIWORD(lParam);
			
			 // [252,247]
			apt[0].x = cxClient / 4;
			apt[0].y = cyClient / 2;
			//[504,123]
			apt[1].x = cxClient / 2;
			apt[1].y = cyClient / 4;
			//[504,371]
			apt[2].x = cxClient / 2;
			apt[2].y = 3 * cyClient / 4;
			//[756,247]
			apt[3].x = 3 * cxClient / 4;
			apt[3].y = cyClient / 2;

			return 0;
		
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MOUSEMOVE:
			if(wParam & MK_LBUTTON || wParam & MK_RBUTTON){
				hdc = GetDC(hwnd);
				SelectObject(hdc,GetStockObject(WHITE_PEN));
				DrawBezier(hdc,apt);
				if(wParam & MK_LBUTTON){
					apt[1].x = LOWORD(lParam);
					apt[1].y = HIWORD(lParam);
				}

				if(wParam & MK_RBUTTON){
					apt[2].x = LOWORD(lParam);
					apt[2].y = HIWORD(lParam);
				}

				SelectObject(hdc,GetStockObject(BLACK_PEN));
				DrawBezier(hdc,apt);

				ReleaseDC(hwnd,hdc);
			}

			return 0;

		case WM_PAINT:
			//InvalidateRect(hwnd,NULL,TRUE);
			hdc = BeginPaint(hwnd,&ps);
			DrawBezier(hdc,apt);
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
	static TCHAR szAppName[] = TEXT("Bezier");
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

	hwnd = CreateWindow(szAppName,TEXT("The Bezier program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
