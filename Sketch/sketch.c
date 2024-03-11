#include <windows.h>

void GetLargesDisplayMode(int *pcxBitmap,int *pcyBitmap){
	DEVMODE devmode;
	int iModeNum = 0;
	*pcxBitmap = *pcyBitmap = 0;

	ZeroMemory(&devmode,sizeof(DEVMODE));
	//MessageBeep(0);
	devmode.dmSize = sizeof(DEVMODE);
	while(EnumDisplaySettings(NULL,iModeNum++,&devmode)){
		*pcxBitmap = max(*pcxBitmap,(int)devmode.dmPelsWidth);
		*pcyBitmap = max(*pcyBitmap,(int)devmode.dmPelsHeight);
	}
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static int cxBitmap,cyBitmap,cxClient,cyClient,xMouse,yMouse;
	static HBITMAP hBitmap;
	static HDC hdcMem;
	static BOOL fLeftButtonDown,fRightButtonDown;
	
	//0x00000024
	switch(message){
		case WM_CREATE:
			GetLargesDisplayMode(&cxBitmap,&cyBitmap);

			hdc = GetDC(hwnd);

			hBitmap = CreateCompatibleBitmap(hdc,cxBitmap,cyBitmap);
			hdcMem = CreateCompatibleDC(hdc);

			ReleaseDC(hwnd,hdc);

			if(!hBitmap){
				DeleteDC(hdcMem);

				return -1;
			}

			SelectObject(hdcMem,hBitmap);
			PatBlt(hdcMem,0,0,cxBitmap,cyBitmap,WHITENESS);

			return 0;

		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			return 0;

		case WM_LBUTTONDOWN:
			if(!fRightButtonDown){
				SetCapture(hwnd);
			}

			xMouse = LOWORD(lParam);
			yMouse = HIWORD(lParam);
			fLeftButtonDown = TRUE;

			return 0;

		case WM_RBUTTONDOWN:
			if(!fLeftButtonDown){
				SetCapture(hwnd);
			}

			xMouse = LOWORD(lParam);
			yMouse = HIWORD(lParam);
			fRightButtonDown = TRUE;

			return 0;

		case WM_RBUTTONUP:
			if(fRightButtonDown){
				SetCapture(NULL);
			}

			fRightButtonDown = FALSE;

			return 0;

		case WM_LBUTTONUP:
			if(fLeftButtonDown){
				SetCapture(NULL);
			}

			fLeftButtonDown = FALSE;

			return 0;

		case WM_MOUSEMOVE:
			if(!fLeftButtonDown && !fRightButtonDown){
				return 0;
			}

			hdc = GetDC(hwnd);

			SelectObject(hdc,GetStockObject(fLeftButtonDown ? BLACK_PEN : WHITE_PEN));
			SelectObject(hdcMem,GetStockObject(fLeftButtonDown ? BLACK_PEN : WHITE_PEN));
			MoveToEx(hdc,xMouse,yMouse,NULL);
			MoveToEx(hdcMem,xMouse,yMouse,NULL);
			xMouse = (short)LOWORD(lParam);
			yMouse = (short)HIWORD(lParam);
			LineTo(hdc,xMouse,yMouse);
			LineTo(hdcMem,xMouse,yMouse);

			ReleaseDC(hwnd,hdc);

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);

			BitBlt(hdc,0,0,cxClient,cyClient,hdcMem,0,0,SRCCOPY);

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
	static TCHAR szAppName[] = "Sketch";
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

	hwnd = CreateWindow(szAppName,"The Sketch program",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
