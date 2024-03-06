#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static int cxClient,cyClient,cyChar,cxClientMax,cyClientMax,cxChar;
	static RECT rectScroll;
	static TCHAR szTop[] = TEXT ("Message        Key       Char     ")
                            TEXT ("Repeat Scan Ext ALT Prev Tran") ;
	static TCHAR szUnd[] = TEXT ("_______        ___       ____     ")
                            TEXT ("______ ____ ___ ___ ____ ____") ;
	int i,iType;
	static int cLines,cLinesMax;
	static PMSG pmsg;
	TEXTMETRIC tm;
	TCHAR szBuffer[128], szKeyName [32] ;
	static TCHAR * szFormat[2] = { 
               TEXT ("%-13s %3d %-15s%c%6u %4d %3s %3s %4s %4s"),
               TEXT ("%-13s            0x%04X%1s%c %6u %4d %3s %3s %4s %4s") } ;
    static TCHAR * szMessage [] = { 
             TEXT ("WM_KEYDOWN"),    TEXT ("WM_KEYUP"), 
             TEXT ("WM_CHAR"),       TEXT ("WM_DEADCHAR"), 
             TEXT ("WM_SYSKEYDOWN"), TEXT ("WM_SYSKEYUP"), 
             TEXT ("WM_SYSCHAR"),    TEXT ("WM_SYSDEADCHAR") } ;
	 static TCHAR * szYes  = TEXT ("Yes") ;
     static TCHAR * szNo   = TEXT ("No") ;
     static TCHAR * szDown = TEXT ("Down") ;
     static TCHAR * szUp   = TEXT ("Up") ;
	//0x00000024
	switch(message){
		case WM_CREATE:
		case WM_DISPLAYCHANGE:
			//MessageBox(hwnd,"WM_DISPLAYCHANGE","titile",0);
			cxClientMax = GetSystemMetrics(SM_CXMAXIMIZED);
			cyClientMax = GetSystemMetrics(SM_CYMAXIMIZED);
			
			hdc = GetDC(hwnd);
			
			SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
			GetTextMetrics(hdc,&tm);
			cxChar = tm.tmAveCharWidth;
			cyChar = tm.tmHeight;

			ReleaseDC(hwnd,hdc);
			
			//µ÷ÄÚ´æ allocate memory for display lines
			if (pmsg)
               free (pmsg) ;

            cLinesMax = cyClientMax / cyChar ;
            pmsg = malloc (cLinesMax * sizeof (MSG)) ;
            cLines = 0 ;

		case WM_SIZE:
			//MessageBox(hwnd,"WM_SIZE","titile",0);
			if(message == WM_SIZE){
				cxClient = LOWORD(lParam);
				cyClient = HIWORD(lParam);
			}

			rectScroll.left = 0;
			rectScroll.right = cxClient;
			rectScroll.top = cyChar;
			rectScroll.bottom = cyChar * (cyClient / cyChar);

			InvalidateRect(hwnd,NULL,TRUE);

			return 0;

		case WM_KEYDOWN:
			//MessageBox(hwnd,"WM_KEYDOWN","titile",0);
		case WM_KEYUP:
			//MessageBox(hwnd,"WM_KEYUP","titile",0);
		case WM_CHAR:
			//MessageBox(hwnd,"WM_CHAR","titile",0);
		case WM_DEADCHAR:
			//MessageBox(hwnd,"WM_DEADCHAR","titile",0);
			for(i = cLinesMax - 1;i > 0;i--){
				//MessageBox(hwnd,"cLinesMax","titile",0);
				pmsg[i] = pmsg[i - 1];
			}

			pmsg[0].hwnd = hwnd;
			pmsg[0].message = message;
			pmsg[0].wParam = wParam;
			pmsg[0].lParam = lParam;

			cLines = min(cLines + 1,cLinesMax);
			ScrollWindow(hwnd,0,-cyChar,&rectScroll,&rectScroll);

			break;
		case WM_PAINT:
			//MessageBox(hwnd,"WM_PAINT","titile",0);
			hdc = BeginPaint(hwnd,&ps);
			
			SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
			SetBkMode(hdc,TRANSPARENT);
			TextOut(hdc,0,0,szTop,lstrlen(szTop));
			TextOut(hdc,0,0,szUnd,lstrlen(szUnd));
			for(i = 0;i < min(cLines,cyClient / cyChar - 1);i++){
				//MessageBox(hwnd,"for","titile",0);
				iType = pmsg[i].message == WM_CHAR || pmsg[i].message == WM_DEADCHAR;
				GetKeyNameText (pmsg[i].lParam, szKeyName, sizeof (szKeyName) / sizeof (TCHAR)) ;
                TextOut (hdc, 0, (cyClient / cyChar - 1 - i) * cyChar, szBuffer,
                        wsprintf (szBuffer, szFormat [iType],
                             szMessage [pmsg[i].message - WM_KEYFIRST],                   
                             pmsg[i].wParam,
                             (PTSTR) (iType ? TEXT (" ") : szKeyName),
                             (TCHAR) (iType ? pmsg[i].wParam : ' '),
                             LOWORD (pmsg[i].lParam),
                             HIWORD (pmsg[i].lParam) & 0xFF,
                             0x01000000 & pmsg[i].lParam ? szYes  : szNo,
                             0x20000000 & pmsg[i].lParam ? szYes  : szNo,
                             0x40000000 & pmsg[i].lParam ? szDown : szUp,
                             0x80000000 & pmsg[i].lParam ? szUp   : szDown)) ;
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
	static TCHAR szAppName[] = TEXT("KeyView1");
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

	hwnd = CreateWindow(szAppName,TEXT("The KeyView1 program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
