#include <windows.h>
#define ID_LIST 1
#define ID_TEXT 2

#define DIRATTR     (DDL_READWRITE | DDL_READONLY | DDL_HIDDEN | DDL_SYSTEM | \
                     DDL_DIRECTORY | DDL_ARCHIVE  | DDL_DRIVES)

#define MAXREAD 8192

#define DTFLAGS     (DT_WORDBREAK | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX)

WNDPROC OldList;

LRESULT CALLBACK ListProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	return CallWindowProc(OldList,hwnd,message,wParam,lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	int cxChar,cyChar,i;
	static RECT rect;
	static BOOL bValidFile;
	static HWND hwndList,hwndText;
	TCHAR szBuffer[MAX_PATH + 1];
	HANDLE hFile;
	static TCHAR szFile[MAX_PATH + 1];
	static BYTE buffer[MAXREAD];

	//0x00000024
	switch(message){
		case WM_CREATE:
			cxChar = LOWORD(GetDialogBaseUnits());
			cyChar = HIWORD(GetDialogBaseUnits());

			rect.left = 20 * cxChar;
			rect.top = 3 * cyChar;

			hwndList = CreateWindow("listbox",NULL,WS_CHILDWINDOW | WS_VISIBLE | LBS_STANDARD,cxChar,cyChar * 3,cxChar * 13 + GetSystemMetrics(SM_CXVSCROLL),cyChar * 10,hwnd,(HMENU)ID_LIST,(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),NULL);
			
			GetCurrentDirectory(MAX_PATH + 1,szBuffer);
			hwndText = CreateWindow("static",szBuffer,WS_CHILDWINDOW | WS_VISIBLE | SS_LEFT,cxChar,cyChar,cxChar * MAX_PATH,cyChar,hwnd,(HMENU)ID_TEXT,(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),NULL);
			
			OldList = (WNDPROC)SetWindowLong(hwndList,GWL_WNDPROC,(LPARAM)ListProc);
			SendMessage(hwndList,LB_DIR,DIRATTR,(LPARAM)"*.*");

			return 0;

		case WM_SIZE:
			rect.right = LOWORD(lParam);
			rect.bottom = HIWORD(lParam);

			return 0;

		case WM_SETFOCUS:
			SetFocus(hwndList);

			return 0;

		case WM_COMMAND:
			if(LOWORD(wParam) == ID_LIST && HIWORD(wParam) == LBN_DBLCLK){
				//MessageBox(hwnd,"WM_COMMAND","tip",0);
				if (LB_ERR == (i = SendMessage (hwndList, LB_GETCURSEL, 0, 0)))
                    break ;

				//MessageBox(hwnd,"WM_COMMAND","tip",0);
				SendMessage(hwndList,LB_GETTEXT,i,(LPARAM)szBuffer);
				//MessageBox(hwnd,"WM_COMMAND","tip",0);
				if(INVALID_HANDLE_VALUE != (hFile = CreateFile(szBuffer,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL))){
					//MessageBox(hwnd,"INVALID_HANDLE_VALUE","tip",0);
					CloseHandle(hFile);
					bValidFile = TRUE;
					lstrcpy(szFile,szBuffer);
					GetCurrentDirectory(MAX_PATH + 1,szBuffer);
					if(szBuffer[lstrlen(szBuffer) - 1] != '\\'){
						lstrcat(szBuffer,"\\");
					}

					SetWindowText(hwndText,lstrcat(szBuffer,szFile));
				}

				InvalidateRect (hwnd, NULL, TRUE) ;
			}

			return 0;

		case WM_PAINT:
			if(!bValidFile){
				break;
			}

			//MessageBox(hwnd,"WM_PAINT","tip",0);
			hFile = CreateFile (szFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (INVALID_HANDLE_VALUE == (hFile))
			{
               bValidFile = FALSE ;
               break ;
			}

			ReadFile(hFile,buffer,MAXREAD,&i,NULL);
			CloseHandle(hFile);

			hdc = BeginPaint(hwnd,&ps);
			
			SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
			SetTextColor(hdc,GetSysColor(COLOR_BTNTEXT));
			SetBkColor(hdc,GetSysColor(COLOR_BTNFACE));

			DrawTextA(hdc,buffer,i,&rect,DTFLAGS);

			EndPaint(hwnd,&ps);
			
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);

			return 0;
	}
	
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = TEXT("Head");
	HWND hwnd;
	MSG msg;
	
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if(!RegisterClass(&wndclass)){
		MessageBox(NULL,TEXT("The program requires Windows NT"),szAppName,MB_ICONERROR);
	
		return 0;
	}

	hwnd = CreateWindow(szAppName,TEXT("The Head program"),WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
