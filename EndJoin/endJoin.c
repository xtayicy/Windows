#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	static int  iEnd[] = { PS_ENDCAP_ROUND, PS_ENDCAP_SQUARE, PS_ENDCAP_FLAT };
     static int  iJoin[]= { PS_JOIN_ROUND,   PS_JOIN_BEVEL,    PS_JOIN_MITER } ;
     static int  cxClient, cyClient ;
     HDC         hdc ;
     int         i ;
     LOGBRUSH    lb ;
     PAINTSTRUCT ps ;
	//0x00000024
	switch(message){
		case WM_SIZE:
			cxClient = LOWORD (lParam) ;
			cyClient = HIWORD (lParam) ;

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);

			SetMapMode (hdc, MM_ANISOTROPIC) ;
          SetWindowExtEx (hdc, 100, 100, NULL) ;
          SetViewportExtEx (hdc, cxClient, cyClient, NULL) ;
          
          lb.lbStyle = BS_SOLID ;
          lb.lbColor = RGB (128, 128, 128) ;
          lb.lbHatch = 0 ;
          
          for (i = 0 ; i < 3 ; i++)
          {
               SelectObject (hdc,
                    ExtCreatePen (PS_SOLID | PS_GEOMETRIC |
                                  iEnd [i] | iJoin [i], 10,
                                  &lb, 0, NULL)) ;
               BeginPath (hdc) ;
               
               MoveToEx (hdc, 10 + 30 * i, 25, NULL) ;
               LineTo   (hdc, 20 + 30 * i, 75) ;
               LineTo   (hdc, 30 + 30 * i, 25) ;
               
               EndPath (hdc) ;
               StrokePath (hdc) ;
               
               DeleteObject (
                    SelectObject (hdc,
                         GetStockObject (BLACK_PEN))) ;
               
               MoveToEx (hdc, 10 + 30 * i, 25, NULL) ;
               LineTo   (hdc, 20 + 30 * i, 75) ;
               LineTo   (hdc, 30 + 30 * i, 25) ;
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
	static TCHAR szAppName[] = "EndJoin";
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

	hwnd = CreateWindow(szAppName,"The EndJoin program",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
