#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdcClient, hdcWindow ;
	PAINTSTRUCT ps;
	static int  cxClient, cyClient, cxSource, cySource ;
	int         x, y ;
	
	switch(message){
		case WM_CREATE:
			cxSource = GetSystemMetrics (SM_CXSIZEFRAME) +
                     GetSystemMetrics (SM_CXSIZE) ;

            cySource = GetSystemMetrics (SM_CYSIZEFRAME) + 
                     GetSystemMetrics (SM_CYCAPTION) ;

			return 0;

		case WM_SIZE:
			cxClient = LOWORD (lParam) ;
			cyClient = HIWORD (lParam) ;

			return 0;

		case WM_PAINT:
			hdcClient = BeginPaint(hwnd,&ps);
			hdcWindow = GetWindowDC (hwnd) ;
			
			for (y = 0 ; y < cyClient ; y += cySource)
			  for (x = 0 ; x < cxClient ; x += cxSource)
			  {
				   BitBlt (hdcClient, x, y, cxSource, cySource,
						   hdcWindow, 0, 0, SRCCOPY) ;
			  }

			ReleaseDC (hwnd, hdcWindow) ;
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
	static TCHAR szAppName[] = TEXT("helloWindows");
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

	hwnd = CreateWindow(szAppName,TEXT("The hello program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
