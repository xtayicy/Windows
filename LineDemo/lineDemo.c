#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static int cxClient,cyClient;
	//char szError[256];

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
			
			Rectangle(hdc,cxClient / 8,cyClient / 8,7 * cxClient / 8,7 * cyClient / 8);
			
			MoveToEx(hdc,0,0,NULL);
			LineTo(hdc,cxClient,cyClient);

			MoveToEx(hdc,0,cyClient,NULL);
			LineTo(hdc,cxClient,0);

			Ellipse(hdc,cxClient / 8,cyClient / 8,7 * cxClient / 8,7 * cyClient / 8);

			RoundRect(hdc,cxClient / 4,cyClient / 4,3 * cxClient / 4,3 * cyClient / 4,cxClient / 4,cyClient / 4);
			
			EndPaint(hwnd,&ps);

			//RoundRect(hdc,cxClient / 4,cyClient / 4,3 * cxClient / 4,3 * cyClient / 4,cxClient / 4,cyClient / 4);
			//k = GetLastError();
			//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,k,0,szError,sizeof(szError),NULL);
			
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);

			return 0;
	}
	

	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = TEXT("LineDemo");
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

	hwnd = CreateWindow(szAppName,TEXT("The LineDemo program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
