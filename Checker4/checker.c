#include <windows.h>
#define DIVISIONS 5

TCHAR szChildClass[] = "Checker4_Child";
int idFocus = 0;

LRESULT CALLBACK ChildWindProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch(message){
		case WM_CREATE:
			SetWindowLong(hwnd,0,0);

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);

			GetClientRect(hwnd,&rect);
			Rectangle(hdc,0,0,rect.right,rect.bottom);
			if(GetWindowLong(hwnd,0)){
				MoveToEx(hdc,0,0,NULL);
				LineTo(hdc,rect.right,rect.bottom);
				MoveToEx(hdc,0,rect.bottom,NULL);
				LineTo(hdc,rect.right,0);
			}

			if(hwnd == GetFocus()){
				rect.left += rect.right / 10;
				rect.right -= rect.left;
				rect.top += rect.bottom / 10;
				rect.bottom -= rect.top;

				SelectObject(hdc,GetStockObject(NULL_BRUSH));
				SelectObject(hdc,CreatePen(PS_DASH,0,0));
				Rectangle(hdc,rect.left,rect.top,rect.right,rect.bottom);
				DeleteObject(SelectObject(hdc,GetStockObject(BLACK_PEN)));
			}

			EndPaint(hwnd,&ps);

			return 0;

		case WM_SETFOCUS:
			//MessageBox(hwnd,"WM_SETFOCUS","tip",0);
			idFocus = GetWindowLong(hwnd,GWL_ID);

		case WM_KILLFOCUS:
			//MessageBox(hwnd,"WM_KILLFOCUS","tip",0);
			InvalidateRect(hwnd,NULL,TRUE);

			return 0;

		case WM_LBUTTONDOWN:
			SetWindowLong(hwnd,0,1 ^ GetWindowLong(hwnd,0));
			SetFocus(hwnd);
			InvalidateRect(hwnd,NULL,TRUE);

			return 0;

		case WM_KEYDOWN:
			if(wParam != VK_SPACE){
				SendMessage(GetParent(hwnd),message,wParam,lParam);
				
				return 0;
			}
	}

	return DefWindowProc(hwnd,message,wParam,lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	static cxBlock,cyBlock;
	int x,y;
	static BOOL fState[DIVISIONS][DIVISIONS];
	static HWND hwndChild[DIVISIONS][DIVISIONS];
	
	//0x00000024
	switch(message){
		case WM_CREATE:
			for(x = 0;x < DIVISIONS;x++){
				for(y = 0;y < DIVISIONS;y++){
					hwndChild[x][y] = CreateWindow(szChildClass,NULL,WS_CHILDWINDOW | WS_VISIBLE,0,0,0,0,hwnd,(HMENU)(y << 8 | x),(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),NULL);
				}
			}

			return 0;

		case WM_SIZE:
			cxBlock = LOWORD(lParam) / DIVISIONS;
			cyBlock = HIWORD(lParam) / DIVISIONS;
			for(x = 0;x < DIVISIONS;x++){
				for(y = 0;y < DIVISIONS;y++){
					MoveWindow(hwndChild[x][y],x * cxBlock,y * cyBlock,cxBlock,cyBlock,TRUE);
				}
			}

			return 0;

		case WM_SETFOCUS:
			//MessageBox(hwnd,"WM_SETFOCUS","tip",0);
			SetFocus(GetDlgItem(hwnd,idFocus));

			return 0;

		case WM_KEYDOWN:
			x = idFocus & 0xFF;
			y = idFocus >> 8;
			switch(wParam){
				case VK_RIGHT:
					x++;

					break;

				case VK_LEFT:
					x--;

					break;

				case VK_DOWN:
					y++;

					break;

				case VK_UP:
					y--;

					break;

				default:

					return 0;
			}

			x = (x + DIVISIONS) % DIVISIONS;
			y = (y + DIVISIONS) % DIVISIONS;

			idFocus = y << 8 | x;

			SetFocus(GetDlgItem(hwnd,idFocus));

			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);

			return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = TEXT("Checker4");
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

	wndclass.lpfnWndProc = ChildWindProc;
	wndclass.cbWndExtra = sizeof(long);
	wndclass.hIcon = NULL;
	wndclass.lpszClassName = szChildClass;

	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName,TEXT("The Checker4 program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
