#include <windows.h>
#include <math.h>

#define TWO_PI (2.0 * 3.14159)

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static int cxClient,cyClient;
	HCURSOR hCursor;
	static HRGN hRgnClip;
	HRGN hRgnTemp[6] ;
	int i;
	double fAngle, fRadius; 

	//0x00000024
	switch(message){
		case WM_CREATE:
		
			return 0;

		case WM_SIZE:
			// 0x000003f1 1009
			cxClient = LOWORD(lParam);
			// 0x000001ef 495
			cyClient = HIWORD(lParam);
			//0x00010007
			hCursor = SetCursor(LoadCursor(NULL,IDC_WAIT));
			//ShowCursor(TRUE);
			
			if(hRgnClip){
				DeleteObject(hRgnClip);
			}

			hRgnTemp[0] = CreateEllipticRgn (0, cyClient / 3,cxClient / 2, 2 * cyClient / 3) ;
			hRgnTemp[1] = CreateEllipticRgn (cxClient / 2, cyClient / 3,cxClient, 2 * cyClient / 3) ;
			hRgnTemp[2] = CreateEllipticRgn (cxClient / 3, 0,2 * cxClient / 3, cyClient / 2) ;
			hRgnTemp[3] = CreateEllipticRgn (cxClient / 3, cyClient / 2,2 * cxClient / 3, cyClient) ;
			hRgnTemp[4] = CreateRectRgn (0, 0, 1, 1) ;
			hRgnTemp[5] = CreateRectRgn (0, 0, 1, 1) ;
			
			hRgnClip = CreateRectRgn (0, 0, 1, 1) ;
			
			CombineRgn (hRgnTemp[4], hRgnTemp[0], hRgnTemp[1], RGN_OR) ;
            CombineRgn (hRgnTemp[5], hRgnTemp[2], hRgnTemp[3], RGN_OR) ;
            CombineRgn (hRgnClip,    hRgnTemp[4], hRgnTemp[5], RGN_XOR) ;
			for (i = 0 ; i < 6 ; i++)
				DeleteObject (hRgnTemp[i]) ;

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
			SetViewportOrgEx (hdc, cxClient / 2, cyClient / 2, NULL) ;
            SelectClipRgn (hdc, hRgnClip) ;
			fRadius = _hypot (cxClient / 2.0, cyClient / 2.0) ;
			for (fAngle = 0.0 ; fAngle < TWO_PI ; fAngle += TWO_PI / 360){
			    MoveToEx (hdc, 0, 0, NULL) ;
			    LineTo (hdc, (int) ( fRadius * cos (fAngle) + 0.5),
							(int) (-fRadius * sin (fAngle) + 0.5)) ;
			}

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
	static TCHAR szAppName[] = TEXT("Clover");
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

	hwnd = CreateWindow(szAppName,TEXT("The Clover program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
