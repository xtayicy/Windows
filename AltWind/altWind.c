#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static int cxClient,cyClient;
	int i;
	POINT apt[10];
	static POINT aptFigure[10] = { 10,70, 50,70, 50,10, 90,10, 90,50,
                                   30,50, 30,90, 70,90, 70,30, 10,30 };

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
			SelectObject(hdc,GetStockObject(GRAY_BRUSH));
			for(i = 0;i < 10;i++){
				apt[i].x = cxClient * aptFigure[i].x / 200;
				apt[i].y = cyClient * aptFigure[i].y / 100;
			}

			//SetPolyFillMode(hdc,ALTERNATE);
			Polygon(hdc,apt,10);
			for(i = 0;i < 10;i++){
				apt[i].x += cxClient / 2;
			}

			SetPolyFillMode(hdc,WINDING);
			Polygon(hdc,apt,10);

			
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
	static TCHAR szAppName[] = TEXT("AltWind");
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

	hwnd = CreateWindow(szAppName,TEXT("The AltWind program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
