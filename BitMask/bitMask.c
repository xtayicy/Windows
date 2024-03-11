#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc,hdcMemImag, hdcMemMask ;
	PAINTSTRUCT ps;
	static HINSTANCE hInstance;
	static HBITMAP hBitmapImag,hBitmapMask;
	BITMAP           bitmap ;
	static int       cxClient, cyClient, cxBitmap, cyBitmap ;
	int              x, y ;
	//0x00000024
	switch(message){
		case WM_CREATE:
			hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
			hBitmapImag = LoadBitmap(hInstance,"Matthew");
			GetObject(hBitmapImag,sizeof(BITMAP),&bitmap);
			cxBitmap = bitmap.bmWidth ;
			cyBitmap = bitmap.bmHeight ;
			hdcMemImag  = CreateCompatibleDC (NULL) ;
			SelectObject (hdcMemImag, hBitmapImag) ;
			hBitmapMask = CreateBitmap (cxBitmap, cyBitmap, 1, 1, NULL) ;
			hdcMemMask = CreateCompatibleDC (NULL) ;
			SelectObject (hdcMemMask, hBitmapMask) ;
			SelectObject (hdcMemMask, GetStockObject (BLACK_BRUSH)) ;
			Rectangle (hdcMemMask, 0, 0, cxBitmap, cyBitmap) ;
			SelectObject (hdcMemMask, GetStockObject (WHITE_BRUSH)) ;
			Ellipse (hdcMemMask, 0, 0, cxBitmap, cyBitmap) ;
			BitBlt (hdcMemImag, 0, 0, cxBitmap, cyBitmap, 
                  hdcMemMask, 0, 0, SRCAND) ;
			DeleteDC (hdcMemImag) ;
			DeleteDC (hdcMemMask) ;
			
			return 0;

		case WM_SIZE:
			cxClient = LOWORD (lParam) ;
			cyClient = HIWORD (lParam) ;

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);

			hdcMemImag = CreateCompatibleDC (hdc) ;
			SelectObject (hdcMemImag, hBitmapImag) ;
			hdcMemMask = CreateCompatibleDC (hdc) ;
			SelectObject (hdcMemMask, hBitmapMask) ;
			x = (cxClient - cxBitmap) / 2 ;
			y = (cyClient - cyBitmap) / 2 ;
			BitBlt (hdc, x, y, cxBitmap, cyBitmap, hdcMemMask, 0, 0, 0x220326) ;
			BitBlt (hdc, x, y, cxBitmap, cyBitmap, hdcMemImag, 0, 0, SRCPAINT) ;
			
			DeleteDC (hdcMemImag) ;
			DeleteDC (hdcMemMask) ;
			EndPaint(hwnd,&ps);
			
			return 0;

		case WM_DESTROY:
			DeleteObject (hBitmapImag) ;
			DeleteObject (hBitmapMask) ;
			PostQuitMessage(0);

			return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = "BitMask";
	HWND hwnd;
	MSG msg;
	
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if(!RegisterClass(&wndclass)){
		MessageBox(NULL,"The program requires Windows NT",szAppName,MB_ICONERROR);
	
		return 0;
	}

	hwnd = CreateWindow(szAppName,"The BitMask program",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
