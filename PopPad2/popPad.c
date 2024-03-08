#include <windows.h>
#include "resource.h"
#define ID_EDIT 1

TCHAR szAppName[] = "PopPad2";

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	static HWND hwndEdit;
	int iSelect,iEnable;
	
	//0x00000024
	switch(message){
		case WM_CREATE:
			hwndEdit = CreateWindow("edit",NULL,WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,0,0,0,0,hwnd,(HMENU)ID_EDIT,((LPCREATESTRUCT)lParam)->hInstance,NULL);

			return 0;

		case WM_SETFOCUS:
			SetFocus(hwndEdit);

			return 0;

		case WM_SIZE:
			MoveWindow(hwndEdit,0,0,LOWORD(lParam),HIWORD(lParam),TRUE);

			return 0;

		case WM_INITMENUPOPUP:
			//MessageBox(hwnd,"WM_INITMENUPOPUP","tip",0);
			if(lParam == 1){
				EnableMenuItem((HMENU)wParam,IDM_EDIT_UNDO,SendMessage(hwndEdit,EM_CANUNDO,0,0) ? MF_ENABLED : MF_GRAYED);
				EnableMenuItem((HMENU)wParam,IDM_EDIT_PASTE,IsClipboardFormatAvailable(CF_TEXT) ? MF_ENABLED : MF_GRAYED);
				iSelect = SendMessage(hwndEdit,EM_GETSEL,0,0);
				if(HIWORD(iSelect) == LOWORD(iSelect)){
					iEnable = MF_GRAYED;
				}else{
					iEnable = MF_ENABLED;
				}

				EnableMenuItem((HMENU)wParam,IDM_EDIT_CUT,iEnable);
				EnableMenuItem((HMENU)wParam,IDM_EDIT_COPY,iEnable);
				EnableMenuItem((HMENU)wParam,IDM_EDIT_CLEAR,iEnable);

				return 0;
			}

			break;

		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDM_FILE_NEW:
					MessageBeep(0);

					return 0;

				case IDM_EDIT_UNDO:
					SendMessage(hwndEdit,WM_UNDO,0,0);

					return 0;

				case IDM_EDIT_CUT:
					SendMessage(hwndEdit,WM_CUT,0,0);

					return 0;

				case IDM_EDIT_COPY:
					SendMessage(hwndEdit,WM_COPY,0,0);

					return 0;

				case IDM_EDIT_PASTE:
					SendMessage(hwndEdit,WM_PASTE,0,0);

					return 0;

				case IDM_EDIT_CLEAR:
					SendMessage(hwndEdit,WM_CLEAR,0,0);

					return 0;

				case IDM_EDIT_SELECT_ALL:
					SendMessage(hwndEdit,EM_SETSEL,0,-1);

					return 0;

				case IDM_HELP_HELP:
					MessageBox (hwnd, TEXT ("Help not yet implemented!"),
                           szAppName, MB_OK | MB_ICONEXCLAMATION) ;

					return 0;

				case IDM_APP_ABOUT:
					MessageBox (hwnd, TEXT ("POPPAD2 (c) Charles Petzold, 1998"),
                           szAppName, MB_OK | MB_ICONINFORMATION) ;

					return 0;
			}

			break;

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
	wndclass.lpszMenuName = szAppName;
	wndclass.lpszClassName = szAppName;
	if(!RegisterClass(&wndclass)){
		MessageBox(NULL,TEXT("The program requires Windows NT"),szAppName,MB_ICONERROR);
	
		return 0;
	}

	hwnd = CreateWindow(szAppName,szAppName,WS_OVERLAPPEDWINDOW,GetSystemMetrics(SM_CXSCREEN) / 4,GetSystemMetrics(SM_CYSCREEN) / 4,GetSystemMetrics(SM_CXSCREEN) / 2,GetSystemMetrics(SM_CYSCREEN) / 2,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
