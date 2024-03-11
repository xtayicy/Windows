#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc,hdcMem;
	PAINTSTRUCT ps;
	static HBITMAP hBitmap;
	static BITMAP bitmap = { 0, 8, 8, 2, 1, 1 };
	static int cxClient,cyClient,cxSource,cySource;
	static BYTE bits [8][2] = { 0xFF, 0, 0x0C, 0, 0x0C, 0, 0x0C, 0,
                                    0xFF, 0, 0xC0, 0, 0xC0, 0, 0xC0, 0 } ;
	int x,y;
	//0x00000024
	switch(message){
		case WM_CREATE:
			bitmap.bmBits = bits;
			hBitmap = CreateBitmapIndirect(&bitmap);
			cxSource = bitmap.bmWidth;
			cySource = bitmap.bmHeight;

			return 0;

		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);

			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem,hBitmap);
			for(y = 0;y < cyClient;y += cySource){
				for(x = 0;x < cxClient;x += cxSource){
					BitBlt(hdc,x,y,cxSource,cySource,hdcMem,0,0,SRCCOPY);
				}
			}
			
			DeleteDC(hdcMem);
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
	static TCHAR szAppName[] = "Bricks2";
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

	hwnd = CreateWindow(szAppName,"The Bricks2 program",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
