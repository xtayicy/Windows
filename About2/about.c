#include <windows.h>
#include "resource.h"

int iCurrentColor = IDC_BLACK,iCurrentFigure = IDC_RECT;

void PaintWindow(HWND hwnd,int iColor,int iFigure){
	HDC hdc;
	RECT rect;
	static COLORREF crColor[2] = {RGB(0,0,0),RGB(0,0,255)};
	HBRUSH hBrush;

	hdc = GetDC(hwnd);

	GetClientRect(hwnd,&rect);
	hBrush = CreateSolidBrush(crColor[iColor - IDC_BLACK]);
	hBrush = (HBRUSH)SelectObject(hdc,hBrush);
	if(iFigure == IDC_RECT){
		Rectangle(hdc,rect.left,rect.top,rect.right,rect.bottom);
	}else{
		Ellipse(hdc,rect.left,rect.top,rect.right,rect.bottom);
	}

	DeleteObject(SelectObject(hdc,hBrush));

	ReleaseDC(hwnd,hdc);
}

void PaintTheBlock(HWND hCtrl,int iColor,int iFigure){
	InvalidateRect(hCtrl,NULL,TRUE);
	UpdateWindow(hCtrl);
	PaintWindow(hCtrl,iColor,iFigure);
}

BOOL CALLBACK AboutDlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
	static int iColor,iFigure;
	static HWND hCtrlBlock;

	switch(message){
		case WM_INITDIALOG:
			//MessageBox(hDlg,"WM_INITDIALOG","tip",0);
			iColor = iCurrentColor;
			iFigure = iCurrentFigure;
			CheckRadioButton(hDlg,IDC_BLACK,IDC_BLUE,iColor);
			CheckRadioButton(hDlg,IDC_RECT,IDC_ELLIPSE,iFigure);
			hCtrlBlock = GetDlgItem(hDlg,IDC_PAINT);
			SetFocus(GetDlgItem(hDlg,iColor));
			
			return FALSE;

		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDOK:
					iCurrentColor = iColor;
					iCurrentFigure = iFigure;
					EndDialog(hDlg,TRUE);

					return TRUE;
				case IDCANCEL:
					EndDialog(hDlg,FALSE);

					return TRUE;

				case IDC_BLUE:
				case IDC_BLACK:
					iColor = LOWORD(wParam);
					CheckRadioButton(hDlg,IDC_BLACK,IDC_BLUE,LOWORD(wParam));
					PaintTheBlock(hCtrlBlock,iColor,iFigure);

					return TRUE;

				case IDC_ELLIPSE:
				case IDC_RECT:
					iFigure = LOWORD(wParam);
					CheckRadioButton(hDlg,IDC_RECT,IDC_ELLIPSE,LOWORD(wParam));
					PaintTheBlock(hCtrlBlock,iColor,iFigure);

					return TRUE;
			}

			break;

		case WM_PAINT:
			PaintTheBlock(hCtrlBlock,iColor,iFigure);

			break;
	}

	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	static HINSTANCE hInstance;
	PAINTSTRUCT ps;
	//0x00000024
	switch(message){
		case WM_CREATE:
			hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
			
			return 0;

		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDM_APP_ABOUT:
					if(DialogBox(hInstance,"AboutBox",hwnd,AboutDlgProc)){
						InvalidateRect(hwnd,NULL,TRUE);
					}

					return 0;
			}
			
			break;

		case WM_PAINT:
			BeginPaint(hwnd,&ps);

			EndPaint(hwnd,&ps);

			PaintWindow(hwnd,iCurrentColor,iCurrentFigure);

			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);

			return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = "About2";
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
		MessageBox(NULL,"The program requires Windows NT",szAppName,MB_ICONERROR);
	
		return 0;
	}

	hwnd = CreateWindow(szAppName,"The About2 program",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
