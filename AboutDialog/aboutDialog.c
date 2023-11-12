#include <windows.h>
#include "resource.h"

//  0x000003e8
int iCurrentColor         = IDC_RADIO_BLACK,
    iCurrentFigure        = IDC_RADIO_RECTANGLE ;

HWND hWnd;

void PaintWindow (HWND hwnd, int iColor, int iFigure){
	static COLORREF crColor[2] = { RGB ( 0, 0, 0), RGB ( 0, 0, 255)} ;
	HDC hdc ;
	RECT rect;
	HBRUSH hBrush;
	
	hdc = GetDC(hwnd);
	
	GetClientRect(hwnd,&rect);
	hBrush = CreateSolidBrush (crColor[iColor - IDC_RADIO_BLACK]) ;
	hBrush = (HBRUSH) SelectObject (hdc, hBrush) ;
	if(iFigure == IDC_RADIO_RECTANGLE){
		Rectangle (hdc, rect.left, rect.top, rect.right, rect.bottom) ;
	}else{
		Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom) ;
	}
	
	DeleteObject(SelectObject(hdc,hBrush));
	ReleaseDC(hwnd,hdc);
}

BOOL CALLBACK AboutDlgProc (HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam){
	static int iColor, iFigure;
	
	switch(message){
		case WM_INITDIALOG:
			iColor = iCurrentColor ;
			iFigure = iCurrentFigure ;
			
			CheckRadioButton (hDlg, IDC_RADIO_BLACK, IDC_RADIO_BLUE,iColor) ;
			CheckRadioButton (hDlg, IDC_RADIO_RECTANGLE,  IDC_RADIO_ELLIPSE, iFigure) ;

			return FALSE;

		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDOK:
					iCurrentColor = iColor;
					iCurrentFigure = iFigure;
					InvalidateRect(hWnd,NULL,TRUE);
					//UpdateWindow(hWnd);
					PaintWindow(hWnd,iCurrentColor,iCurrentFigure);
					EndDialog(hDlg,0);
			
					return TRUE;

				case IDC_RADIO_BLACK:
				case IDC_RADIO_BLUE:
					iColor = LOWORD (wParam);
					CheckRadioButton (hDlg, IDC_RADIO_RECTANGLE,IDC_RADIO_ELLIPSE, iFigure);
					CheckRadioButton (hDlg, IDC_RADIO_BLACK,IDC_RADIO_BLUE, iColor);

					return TRUE;

				case IDC_RADIO_RECTANGLE:
				case IDC_RADIO_ELLIPSE:
					iFigure = LOWORD (wParam);
					CheckRadioButton (hDlg, IDC_RADIO_BLACK,IDC_RADIO_BLUE, iColor);
					CheckRadioButton (hDlg, IDC_RADIO_RECTANGLE,IDC_RADIO_ELLIPSE, iFigure);

					return TRUE;
			}

			break;

			case WM_PAINT:

				break;
	}

	return FALSE;
}


LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static HINSTANCE hInstance ;
	char szError[256];
	
	//0x00000024
	switch(message){
		case WM_CREATE:
			hInstance = ((LPCREATESTRUCT) lParam)->hInstance ;
			hWnd = hwnd;

			return 0;

		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDM_HELP_ABOUT:
					if(DialogBox(hInstance, TEXT ("AboutDialog"), hwnd, AboutDlgProc)){
						InvalidateRect(hwnd,NULL,TRUE);
					}

					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(),0,szError,sizeof(szError),NULL);

					break;
			}

			return 0;

		case WM_SIZE:

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
			EndPaint(hwnd,&ps);
			
			PaintWindow (hwnd, iCurrentColor, iCurrentFigure) ;

			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);

			return 0;
	}
	

	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = TEXT("AboutDialog");
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

	hwnd = CreateWindow(szAppName,TEXT("The AboutDialog program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
