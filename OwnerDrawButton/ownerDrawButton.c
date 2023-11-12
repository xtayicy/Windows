#include <windows.h>

#define ID_SMALLER      1
#define ID_LARGER       2

#define BTN_WIDTH        (8 * cxChar)
#define BTN_HEIGHT       (4 * cyChar)

HINSTANCE hInst ;

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static int       cxClient, cyClient, cxChar, cyChar ;
	static HWND      hwndSmaller, hwndLarger ;
	RECT             rc ;

	//0x00000024
	switch(message){
		case WM_CREATE:
			cxChar = LOWORD (GetDialogBaseUnits ()) ;
            cyChar = HIWORD (GetDialogBaseUnits ()) ;
			
			hwndSmaller = CreateWindow (TEXT ("button"), TEXT (""),
                                      WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                                      0, 0, BTN_WIDTH, BTN_HEIGHT,
                                      hwnd, (HMENU) ID_SMALLER, hInst, NULL) ;
          
            hwndLarger  = CreateWindow (TEXT ("button"), TEXT (""),
                                      WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                                      0, 0, BTN_WIDTH, BTN_HEIGHT,
                                      hwnd, (HMENU) ID_LARGER, hInst, NULL) ;

			return 0;

		case WM_SIZE:
			cxClient = LOWORD (lParam) ;
            cyClient = HIWORD (lParam) ;

			MoveWindow (hwndSmaller, cxClient / 2 - 3 * BTN_WIDTH  / 2,
                                   cyClient / 2 -     BTN_HEIGHT / 2,
                      BTN_WIDTH, BTN_HEIGHT, TRUE) ;
          
            MoveWindow (hwndLarger,  cxClient / 2 +     BTN_WIDTH  / 2,
                                   cyClient / 2 -     BTN_HEIGHT / 2,
                      BTN_WIDTH, BTN_HEIGHT, TRUE) ;

			return 0;

		case WM_COMMAND:
			GetWindowRect (hwnd, &rc) ;
			switch (wParam){
			  case ID_SMALLER :
				   rc.left   += cxClient / 20 ;
				   rc.right  -= cxClient / 20 ;
				   rc.top    += cyClient / 20 ;
				   rc.bottom -= cyClient / 20 ;
				   break ;
               
			  case ID_LARGER :
				   rc.left   -= cxClient / 20 ;
				   rc.right  += cxClient / 20 ;
				   rc.top    -= cyClient / 20 ;
				   rc.bottom += cyClient / 20 ;
				   break ;
			}

			MoveWindow (hwnd, rc.left, rc.top, rc.right  - rc.left,
                            rc.bottom - rc.top, TRUE) ;

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
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
	static TCHAR szAppName[] = TEXT("OwnerDrawButton");
	HWND hwnd;
	MSG msg;

	hInst = hInstance ;
	
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

	hwnd = CreateWindow(szAppName,TEXT("The OwnerDrawButton program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
