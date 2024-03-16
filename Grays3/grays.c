#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static int  cxClient, cyClient ;
	HBRUSH      hBrush ;
	int         i ;
	RECT        rect ;
	LOGPALETTE    * plp ;
	static HPALETTE hPalette ;
	//0x00000024
	switch(message){
		case WM_CREATE:
			plp = malloc (sizeof (LOGPALETTE) + 64 * sizeof (PALETTEENTRY)) ;
			plp->palVersion    = 0x0300 ;
			plp->palNumEntries = 65 ;
			for (i = 0 ; i < 65 ; i++)
			  {
				   plp->palPalEntry[i].peRed   = (BYTE) min (255, 4 * i) ;
				   plp->palPalEntry[i].peGreen = (BYTE) min (255, 4 * i) ;
				   plp->palPalEntry[i].peBlue  = (BYTE) min (255, 4 * i) ;
				   plp->palPalEntry[i].peFlags = 0 ;
			  }

			hPalette = CreatePalette (plp) ;
			free (plp) ;

			return 0;

		case WM_SIZE:
			cxClient = LOWORD (lParam) ;
			cyClient = HIWORD (lParam) ;

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);

			SelectPalette (hdc, hPalette, FALSE) ;
			RealizePalette (hdc) ;
			for (i = 0 ; i < 65 ; i++)
			  {
				   rect.left   = i * cxClient / 64 ;
				   rect.top    = 0 ;
				   rect.right  = (i + 1) * cxClient / 64 ;
				   rect.bottom = cyClient ;

				   hBrush = CreateSolidBrush (PALETTEINDEX (i)) ;
				   FillRect (hdc, &rect, hBrush) ;
				   DeleteObject (hBrush) ;
			  }
			
			EndPaint(hwnd,&ps);
			
			return 0;

		case WM_QUERYNEWPALETTE:
			MessageBox(hwnd,"WM_QUERYNEWPALETTE","tip",0);

			return TRUE;

		case WM_PALETTECHANGED:
			MessageBox(hwnd,"WM_PALETTECHANGED","tip",0);

			break;

		case WM_DESTROY:
			DeleteObject (hPalette) ;
			PostQuitMessage(0);

			return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = "Grays3";
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

	hwnd = CreateWindow(szAppName,"The Grays3 program",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
