#include <windows.h>

HINSTANCE hInst;
static TCHAR szAppName[] = "Print";

BOOL PrintMyPage(HWND);

void PageGDICalls(HDC hdcPrn,int cxPage,int cyPage){
	static TCHAR szTextStr[] = "Hello,Printer!";

	Rectangle(hdcPrn,0,0,cxPage,cyPage);
	MoveToEx(hdcPrn,0,0,NULL);
	LineTo(hdcPrn,cxPage,cyPage);
	MoveToEx(hdcPrn,cxPage,0,NULL);
	LineTo(hdcPrn,0,cyPage);
	SaveDC(hdcPrn);

	SetMapMode(hdcPrn,MM_ISOTROPIC);
	SetWindowExtEx(hdcPrn,1000,1000,NULL);
	SetViewportExtEx(hdcPrn,cxPage / 2,-cyPage / 2,NULL);
	SetViewportOrgEx(hdcPrn,cxPage / 2,cyPage / 2,NULL);

	Ellipse(hdcPrn,-500,500,500,-500);
	SetTextAlign(hdcPrn,TA_BASELINE | TA_CENTER);
	TextOut(hdcPrn,0,0,szTextStr,lstrlen(szTextStr));

	RestoreDC(hdcPrn,-1);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	HMENU hMenu;
	static int cxClient,cyClient;
	//0x00000024
	switch(message){
		case WM_CREATE:
			hMenu = GetSystemMenu(hwnd,FALSE);
			AppendMenu(hMenu,0,1,"Print");

			return 0;

		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			return 0;

		case WM_SYSCOMMAND:
			if(wParam == 1){
				//MessageBox(hwnd,"WM_SYSCOMMAND","tip",0);
				if(!PrintMyPage(hwnd)){
					MessageBox(hwnd,"Could not print page!",szAppName,MB_OK | MB_ICONEXCLAMATION);
				}
			}

			break;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);

			PageGDICalls(hdc,cxClient,cyClient);
			
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

	hInst = hInstance;
	hwnd = CreateWindow(szAppName,"The Print program",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
