#include <windows.h>
#include <math.h>

#define ID_TIMER 1
#define TWOPI (2 * 3.14159)

void RotatePoint (POINT pt[], int iNum, int iAngle)
{
     int   i ;
     POINT ptTemp ;
     
     for (i = 0 ; i < iNum ; i++)
     {
          ptTemp.x = (int) (pt[i].x * cos (TWOPI * iAngle / 360) +
               pt[i].y * sin (TWOPI * iAngle / 360)) ;
          
          ptTemp.y = (int) (pt[i].y * cos (TWOPI * iAngle / 360) -
               pt[i].x * sin (TWOPI * iAngle / 360)) ;
          
          pt[i] = ptTemp ;
     }
}

void DrawHands (HDC hdc, SYSTEMTIME * pst, BOOL fChange)
{
     static POINT pt[3][5] = { 0, -150, 100, 0, 0, 600, -100, 0, 0, -150,
                               0, -200,  50, 0, 0, 800,  -50, 0, 0, -200,
                               0,    0,   0, 0, 0,   0,    0, 0, 0,  800 } ;
     int          i, iAngle[3] ;
     POINT        ptTemp[3][5] ;
     
     iAngle[0] = (pst->wHour * 30) % 360 + pst->wMinute / 2 ;
     iAngle[1] =  pst->wMinute  *  6 ;
     iAngle[2] =  pst->wSecond  *  6 ;
     
     memcpy (ptTemp, pt, sizeof (pt)) ;
     
     for (i = fChange ? 0 : 2 ; i < 3 ; i++)
     {
          RotatePoint (ptTemp[i], 5, iAngle[i]) ;
          
          Polyline (hdc, ptTemp[i], 5) ;
     }
}

void DrawClock(HDC hdc){
	 int   iAngle ;
     POINT pt[3] ;
     
     for (iAngle = 0 ; iAngle < 360 ; iAngle += 6)
     {
          pt[0].x =   0 ;
          pt[0].y = 900 ;
          
          RotatePoint (pt, 1, iAngle) ;
          
          pt[2].x = pt[2].y = iAngle % 5 ? 33 : 100 ;
          
          pt[0].x -= pt[2].x / 2 ;
          pt[0].y -= pt[2].y / 2 ;
          
          pt[1].x  = pt[0].x + pt[2].x ;
          pt[1].y  = pt[0].y + pt[2].y ;
          
          SelectObject (hdc, GetStockObject (BLACK_BRUSH)) ;
          
          Ellipse (hdc, pt[0].x, pt[0].y, pt[1].x, pt[1].y) ;
     }
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;
	static SYSTEMTIME stPrevious ;
	static int cxClient, cyClient ;
	BOOL              fChange ;
	
	//0x00000024
	switch(message){
		case WM_CREATE:
			SetTimer (hwnd, ID_TIMER, 1000, NULL) ;
			GetLocalTime (&st) ;
			stPrevious = st;

			return 0;

		case WM_SIZE:
			// 0x000003f1 1009
			cxClient = LOWORD(lParam);
			// 0x000001ef 495
			cyClient = HIWORD(lParam);

			return 0;

		case WM_TIMER:
			GetLocalTime (&st) ;

			fChange = st.wHour   != stPrevious.wHour ||
                    st.wMinute != stPrevious.wMinute ;

			hdc = GetDC (hwnd) ;
			
			SetMapMode (hdc, MM_ISOTROPIC) ;
			//SetWindowExtEx (hdc, 1000, 1000, NULL) ;
			//设置该函数用指定的值来设置指定设备环境坐标的X轴、Y轴范围。
			//SetViewportExtEx (hdc, cxClient / 2, -cyClient / 2, NULL) ;
			//设置原点
			SetViewportOrgEx (hdc, cxClient / 2,  cyClient / 2, NULL) ;
			SelectObject (hdc, GetStockObject (WHITE_PEN)) ;
            DrawHands (hdc, &stPrevious, fChange) ;
          
            SelectObject (hdc, GetStockObject (BLACK_PEN)) ;
            DrawHands (hdc, &st, TRUE) ;
			
			ReleaseDC (hwnd, hdc) ;
			
			stPrevious = st ;

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
			SetMapMode (hdc, MM_ISOTROPIC) ;
			//SetWindowExtEx (hdc, 1000, 1000, NULL) ;
			//设置该函数用指定的值来设置指定设备环境坐标的X轴、Y轴范围。
			//SetViewportExtEx (hdc, cxClient / 2, -cyClient / 2, NULL) ;
			//设置原点
			SetViewportOrgEx (hdc, cxClient / 2,  cyClient / 2, NULL) ;
			DrawClock(hdc);
			DrawHands(hdc,&stPrevious,TRUE);
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
	static TCHAR szAppName[] = TEXT("Clock");
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

	hwnd = CreateWindow(szAppName,TEXT("The Clock program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
