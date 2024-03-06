#include <windows.h>
#define DIVISIONS 5

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static cxBlock,cyBlock;
	int x,y;
	static BOOL fState[DIVISIONS][DIVISIONS];
	RECT rect;
	POINT point;
	
	//0x00000024
	switch(message){
		case WM_SIZE:
			cxBlock = LOWORD(lParam) / DIVISIONS;
			cyBlock = HIWORD(lParam) / DIVISIONS;

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
			for(x = 0;x < DIVISIONS;x++){
				for(y = 0;y < DIVISIONS;y++){
					Rectangle(hdc,x * cxBlock,y * cyBlock,(x + 1) * cxBlock,(y + 1) * cyBlock);
					if(fState[x][y]){
						MoveToEx(hdc,x * cxBlock,y * cyBlock,NULL);
						LineTo(hdc,(x + 1) * cxBlock,(y + 1) * cyBlock);
						MoveToEx(hdc,x * cxBlock,(y + 1) * cyBlock,NULL);
						LineTo(hdc,(x + 1) * cxBlock,y * cyBlock);
					}
				}
			}

			EndPaint(hwnd,&ps);
			
			return 0;

		case WM_LBUTTONDOWN:
			x = LOWORD(lParam) / cxBlock;
			y = HIWORD(lParam) / cyBlock;

			if(x < DIVISIONS && y < DIVISIONS){
				fState[x][y] ^= 1;
				
				rect.left = x * cxBlock;
				rect.right = (x + 1) * cxBlock;
				rect.top = y * cyBlock;
				rect.bottom = (y + 1) * cyBlock;

				InvalidateRect(hwnd,&rect,TRUE);
			}else{
				MessageBeep(0);
			}

			return 0;

		case WM_SETFOCUS:
			//MessageBox(hwnd,"WM_SETFOCUS","tip",0);
			ShowCursor(TRUE);

			return 0;

		case WM_KILLFOCUS:
			//MessageBox(hwnd,"WM_KILLFOCUS","tip",0);
			ShowCursor(FALSE);

			return 0;

		case WM_KEYDOWN:
			GetCursorPos(&point);
			ScreenToClient(hwnd,&point);
			x = max(0,min(DIVISIONS - 1,point.x / cxBlock));
			y = max(0,min(DIVISIONS - 1,point.y / cyBlock));
			switch(wParam){
				case VK_SPACE:
					SendMessage(hwnd,WM_LBUTTONDOWN,MK_LBUTTON,MAKELONG(x * cxBlock,y * cyBlock));

					break;

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
			}

			x = (x + DIVISIONS) % DIVISIONS;
			y = (y + DIVISIONS) % DIVISIONS;

			point.x = x * cxBlock + cxBlock / 2;
			point.y = y * cyBlock + cyBlock / 2;

			ClientToScreen(hwnd,&point);
			SetCursorPos(point.x,point.y);

			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);

			return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = TEXT("Checker2");
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

	hwnd = CreateWindow(szAppName,TEXT("The Checker2 program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
