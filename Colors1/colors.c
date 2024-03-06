#include <windows.h>

int idFocus;
WNDPROC OldScroll[3];

LRESULT CALLBACK ScrollProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	int id = GetWindowLong(hwnd,GWL_ID);
	switch(message){
		case WM_SETFOCUS:
			idFocus = id;

			break;
	}

	return CallWindowProc (OldScroll[id],hwnd,message,wParam,lParam) ;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HINSTANCE hInstance;
	int cxClient,cyClient,i;
	static RECT rcColor;
	static HWND hwndRect,hwndScroll[3],hwndLabel[3],hwndValue[3];
	static int cyChar,color[3];
	static HBRUSH hBrush[3],hBrushStatic;
	static COLORREF crPrim[3] = {RGB(255,0,0),RGB(0,255,0),RGB(0,0,255)};
	static TCHAR * szColorLabel[] = { TEXT ("Red"), TEXT ("Green"), 
                                       TEXT ("Blue") } ;
	TCHAR szBuffer[10] ;

	//0x00000024
	switch(message){
		case WM_CREATE:
			hInstance = (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE);
			hwndRect = CreateWindow("static",NULL,WS_CHILD | WS_VISIBLE | SS_WHITERECT,0,0,0,0,hwnd,(HMENU)9,hInstance,NULL);
			for(i = 0;i < 3;i++){
				hwndScroll[i] = CreateWindow("scrollBar",NULL,WS_CHILD | WS_VISIBLE | WS_TABSTOP | SBS_VERT,0,0,0,0,hwnd,(HMENU)i,hInstance,NULL);
				SetScrollRange(hwndScroll[i],SB_CTL,0,255,FALSE);
				SetScrollPos(hwndScroll[i],SB_CTL,0,FALSE);
				
				hwndLabel[i] = CreateWindow("static",szColorLabel[i],WS_CHILD | WS_VISIBLE | SS_CENTER,0,0,0,0,hwnd,(HMENU)(i + 3),hInstance,NULL);
				hwndValue[i] = CreateWindow("static","0",WS_CHILD | WS_VISIBLE | SS_CENTER,0,0,0,0,hwnd,(HMENU)(i + 6),hInstance,NULL);
				
				OldScroll[i] = (WNDPROC)SetWindowLong(hwndScroll[i],GWL_WNDPROC,(LONG)ScrollProc);

				hBrush[i] = CreateSolidBrush(crPrim[i]);
			}

			hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));

			cyChar = HIWORD(GetDialogBaseUnits());

			return 0;

		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			SetRect(&rcColor,cxClient / 2,0,cxClient,cyClient);
			MoveWindow(hwndRect,0,0,cxClient / 2,cyClient,TRUE);
			for(i = 0;i < 3;i++){
				MoveWindow(hwndScroll[i],(2 * i + 1) * cxClient / 14,2 * cyChar,cxClient / 14,cyClient - 4 * cyChar,TRUE);
				MoveWindow(hwndLabel[i],(4 * i + 1) * cxClient / 28,cyChar / 2,cxClient / 7,cyChar,TRUE);
				MoveWindow(hwndValue[i],(4 * i + 1) * cxClient / 28,cyClient - 3 * cyChar / 2,cxClient / 7,cyChar,TRUE);
			}

			SetFocus(hwnd);

			return 0;

		case WM_SETFOCUS:
			SetFocus(hwndScroll[idFocus]);

			return 0;

		case WM_VSCROLL:
			i = GetWindowLong((HWND)lParam,GWL_ID);
			switch(LOWORD(wParam)){
				case SB_LINEDOWN:
					color[i] = min (255, color[i] + 1) ;

					break;

				case SB_LINEUP:
					color[i] = max (0, color[i] - 1);

					break;
				default:

					break;
			}

			SetScrollPos(hwndScroll[i],SB_CTL,color[i],TRUE);
			wsprintf (szBuffer, TEXT ("%i"), color[i]) ;
            SetWindowText (hwndValue[i], szBuffer) ;
			DeleteObject ((HBRUSH)SetClassLong (hwnd, GCL_HBRBACKGROUND, (LONG) 
            CreateSolidBrush (RGB (color[0], color[1], color[2])))) ;
            InvalidateRect (hwnd, &rcColor, TRUE) ;

			return 0;

		case WM_CTLCOLORSCROLLBAR:
			//MessageBox(hwnd,"WM_CTLCOLORSCROLLBAR","tip",0);
			i = GetWindowLong((HWND)lParam,GWL_ID);

			return (LRESULT)hBrush[i];

		case WM_CTLCOLORSTATIC:
			//MessageBox(hwnd,"WM_CTLCOLORSTATIC","tip",0);
			i = GetWindowLong((HWND)lParam,GWL_ID);
			if(i >= 3 && i <= 8){
				//MessageBox(hwnd,"i","tip",0);
				SetTextColor((HDC)wParam,crPrim[i % 3]);
				SetBkColor((HDC)wParam,GetSysColor(COLOR_BTNHIGHLIGHT));
				
				return (LRESULT)hBrushStatic;
			}

			break;

		case WM_SYSCOLORCHANGE:
			MessageBox(hwnd,"WM_SYSCOLORCHANGE","tip",0);

			return 0;
		case WM_DESTROY:
			//DeleteObject(SetClassLong(hwnd,GCL_HBRBACKGROUND,(LONG)GetStockObject(WHITE_BRUSH)));
			for(i = 0;i < 3;i++){
				DeleteObject(hBrush[i]);
			}

			DeleteObject(hBrushStatic);
			PostQuitMessage(0);

			return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = TEXT("Colors1");
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

	hwnd = CreateWindow(szAppName,TEXT("The Colors1 program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
