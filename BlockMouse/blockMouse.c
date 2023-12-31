#include <windows.h>

void DrawBoxOutline(HWND hwnd,POINT ptBeg,POINT ptEnd){
	HDC hdc;

	hdc = GetDC(hwnd);

	//SetROP2(hdc,R2_NOT);
	SelectObject(hdc,GetStockObject(WHITE_BRUSH));
	Rectangle(hdc,ptBeg.x,ptBeg.y,ptEnd.x,ptEnd.y);

	ReleaseDC(hwnd,hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static POINT  ptBeg, ptEnd, ptBoxBeg, ptBoxEnd ;
	static BOOL   fBlocking, fValidBox ;

	
	//0x00000024
	switch(message){
		case WM_CREATE:
			

			return 0;

		case WM_SIZE:

			return 0;

		case WM_LBUTTONDOWN:
			ptBeg.x = ptEnd.x = LOWORD (lParam) ;
			ptBeg.y = ptEnd.y = HIWORD (lParam) ;

			//DrawBoxOutline(hwnd,ptBeg,ptEnd);
			SetCursor(LoadCursor(NULL,IDC_CROSS));

			fBlocking = TRUE;

			return 0;

		case WM_MOUSEMOVE:
			if(fBlocking){
				SetCursor(LoadCursor(NULL,IDC_CROSS));
				//DrawBoxOutline(hwnd,ptBeg,ptEnd);

				ptEnd.x = LOWORD(lParam);
				ptEnd.y = HIWORD(lParam);

				DrawBoxOutline(hwnd,ptBeg,ptEnd);
			}


			return 0;

		case WM_LBUTTONUP:
			if(fBlocking){
				//DrawBoxOutline(hwnd,ptBeg,ptEnd);
				ptBoxBeg = ptBeg;
				ptBoxEnd.x = LOWORD(lParam);
				ptBoxEnd.y = HIWORD(lParam);

				SetCursor(LoadCursor(NULL,IDC_ARROW));
				fBlocking = FALSE;
				fValidBox = TRUE;

				InvalidateRect(hwnd,NULL,TRUE);
			}

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
			if(fValidBox){
				SelectObject(hdc,GetStockObject(BLACK_BRUSH));
				Rectangle(hdc,ptBoxBeg.x,ptBoxBeg.y,ptBoxEnd.x,ptBoxEnd.y);
			}

			if(fBlocking){
				//SetROP2(hdc,R2_NOT);
				SelectObject(hdc,GetStockObject(WHITE_BRUSH));
				Rectangle(hdc,ptBeg.x,ptBeg.y,ptEnd.x,ptEnd.y);
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
	static TCHAR szAppName[] = TEXT("BlockMouse");
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

	hwnd = CreateWindow(szAppName,TEXT("The BlockMouse program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
