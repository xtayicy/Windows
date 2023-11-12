#include <windows.h>
#include "resource.h"

#define ID_TIMER 1

TCHAR szAppName[] = TEXT("MenuDemo");

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	HMENU      hMenu ;
	static int iSelection = IDM_BACKGROUND_WHITE ;
	static int idColor [5] = { WHITE_BRUSH,  LTGRAY_BRUSH, GRAY_BRUSH,
                                DKGRAY_BRUSH, BLACK_BRUSH } ;

	//0x00000024
	switch(message){
		case WM_CREATE:

			return 0;

		case WM_SIZE:

			return 0;

		case WM_COMMAND:
			hMenu = GetMenu (hwnd) ;
			switch(LOWORD(wParam)){
				case IDM_FILE_NEW:
				case IDM_FILE_OPEN:
				case IDM_FILE_SAVE:
				case IDM_FILE_SAVE_AS:
					MessageBeep(0);

					return 0;

				case IDM_APP_EXIT:
					SendMessage (hwnd, WM_CLOSE, 0, 0) ;

					return 0;

				case IDM_EDIT_UNDO:
				case IDM_EDIT_CUT:
				case IDM_EDIT_COPY:
				case IDM_EDIT_PASTE:
				case IDM_EDIT_DELETE:
					MessageBeep(0);
					
					return 0;

				case IDM_BACKGROUND_WHITE:
				case IDM_BACKGROUND_LIGHT_GRAY:
				case IDM_BACKGROUND_GRAY:
				case IDM_BACKGROUND_DARK_GRAY:
				case IDM_BACKGROUND_BLACK:
					CheckMenuItem (hMenu, iSelection, MF_UNCHECKED) ;
				    iSelection = LOWORD (wParam) ;
				    CheckMenuItem (hMenu, iSelection, MF_CHECKED) ;
               
				    SetClassLong (hwnd, GCL_HBRBACKGROUND, (LONG) 
						GetStockObject 
								 (idColor [LOWORD (wParam) - IDM_BACKGROUND_WHITE])) ;
               
				    InvalidateRect (hwnd, NULL, TRUE) ;

					return 0;

				case IDM_TIMER_START:
					if (SetTimer (hwnd, ID_TIMER, 1000, NULL)){
						EnableMenuItem (hMenu, IDM_TIMER_START, MF_GRAYED) ;
						EnableMenuItem (hMenu, IDM_TIMER_STOP,  MF_ENABLED) ;
					}

					return 0;

				case IDM_TIMER_STOP:
					KillTimer (hwnd, ID_TIMER) ;
					EnableMenuItem (hMenu, IDM_TIMER_START, MF_ENABLED) ;
					EnableMenuItem (hMenu, IDM_TIMER_STOP,  MF_GRAYED) ;

					return 0;

				case IDM_APP_HELP:
					MessageBox (hwnd, TEXT ("Help not yet implemented!"),
                           szAppName, MB_ICONEXCLAMATION | MB_OK) ;

					return 0;

				case IDM_APP_ABOUT:
					MessageBox (hwnd, TEXT ("Menu Demonstration Program\n")
                                 TEXT ("(c) Charles Petzold, 1998"),
                           szAppName, MB_ICONINFORMATION | MB_OK) ;

					return 0;
			}

			return 0;

		case WM_TIMER:
			MessageBeep (0) ;

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
	HWND hwnd;
	MSG msg;
	HMENU hMenu;

	hMenu = LoadMenu (hInstance, MAKEINTRESOURCE (IDR_MENU)) ;
	
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

	hwnd = CreateWindow(szAppName,TEXT("The MenuDemo program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,hMenu,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
