#include <windows.h>

HWND hDlgModeless;

BOOL CALLBACK ColorScrDlg(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
	int iCtrlID,iIndex;
	HWND hCtrl,hwndParent;
	static int iColor[13];

	switch(message){
		case WM_INITDIALOG:
			//MessageBox(hDlg,"WM_INITDIALOG","tip",0);
			for(iCtrlID = 10;iCtrlID < 13;iCtrlID++){
				hCtrl = GetDlgItem(hDlg,iCtrlID);
				SetScrollRange(hCtrl,SB_CTL,0,255,FALSE);
				SetScrollPos(hCtrl,SB_CTL,0,FALSE);
			}

			return TRUE;

		case WM_VSCROLL:
			hCtrl = (HWND)lParam;
			iCtrlID = GetWindowLong(hCtrl,GWL_ID);
			iIndex = iCtrlID - 10;
			hwndParent = GetParent(hDlg);
			switch(LOWORD(wParam)){
				case SB_LINEDOWN:
					iColor[iIndex] = min(255,iColor[iIndex] + 1);

					break;

				case SB_LINEUP:
					iColor[iIndex] = max(0,iColor[iIndex] - 1);

					break;

				default:

					return FALSE;
			}

			SetScrollPos(hCtrl,SB_CTL,iColor[iIndex],TRUE);
			SetDlgItemInt(hDlg,iCtrlID + 3,iColor[iIndex],FALSE);
			DeleteObject((HGDIOBJ)SetClassLong(hwndParent,GCL_HBRBACKGROUND,(LONG)CreateSolidBrush(RGB(iColor[0],iColor[1],iColor[2]))));
			InvalidateRect(hwndParent,NULL,TRUE);

			return TRUE;
	}

	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	//0x00000024
	switch(message){
		case WM_DESTROY:
			DeleteObject((HGDIOBJ)SetClassLong(hwnd,GCL_HBRBACKGROUND,(LONG)GetStockObject(WHITE_BRUSH)));
			PostQuitMessage(0);

			return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = TEXT("Colors2");
	HWND hwnd;
	MSG msg;
	
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = CreateSolidBrush(0);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if(!RegisterClass(&wndclass)){
		MessageBox(NULL,TEXT("The program requires Windows NT"),szAppName,MB_ICONERROR);
	
		return 0;
	}

	hwnd = CreateWindow(szAppName,TEXT("The Colors2 program"),WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	hDlgModeless = CreateDialog(hInstance,"ColorScrDlg",hwnd,ColorScrDlg);
	while(GetMessage(&msg,NULL,0,0)){
		if(hDlgModeless == 0 || !IsDialogMessage(hDlgModeless,&msg)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}
