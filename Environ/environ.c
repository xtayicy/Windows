#include <windows.h>
#define ID_LIST 1
#define ID_TEXT 2

void FillListBox(HWND hwndList){
	TCHAR *pVarBlock,*pVarBeg,*pVarEnd,*pVarName;
	int iLength;

	pVarBlock = GetEnvironmentStrings();
	while(*pVarBlock){
		if(*pVarBlock != '='){
			pVarBeg = pVarBlock;
			while(*pVarBlock++ != '=');
			pVarEnd = pVarBlock - 1;
			iLength = pVarEnd - pVarBeg;
			pVarName = calloc(iLength + 1,sizeof(TCHAR));
			CopyMemory(pVarName,pVarBeg,iLength * sizeof(TCHAR));
			pVarName[iLength] = '\0';
			SendMessage(hwndList,LB_ADDSTRING,0,(LPARAM)pVarName);
			free(pVarName);
		}
		
		while(*pVarBlock++ != '\0');
	}

	FreeEnvironmentStrings(pVarBlock);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	int cxChar,cyChar,iIndex,iLength;
	static HWND hwndList,hwndText;
	TCHAR *pVarName,*pVarValue;
	//0x00000024
	switch(message){
		case WM_CREATE:
			cxChar = LOWORD(GetDialogBaseUnits());
			cyChar = HIWORD(GetDialogBaseUnits());

			hwndList = CreateWindow("listbox",NULL,WS_CHILD | WS_VISIBLE | LBS_STANDARD,cxChar,cyChar * 3,cxChar * 16 + GetSystemMetrics(SM_CXVSCROLL),cyChar * 5,hwnd,(HMENU)ID_LIST,(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),NULL);
			hwndText = CreateWindow("static",NULL,WS_CHILD | WS_VISIBLE | SS_LEFT,cxChar,cyChar,GetSystemMetrics(SM_CXSCREEN),cyChar,hwnd,(HMENU)ID_TEXT,(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),NULL);
			FillListBox(hwndList);
			
			return 0;

		case WM_SETFOCUS:
			SetFocus(hwndList);
			
			return 0;

		case WM_COMMAND:
			//MessageBox(hwnd,"WM_COMMAND","tip",0);
			if(LOWORD(wParam) == ID_LIST && HIWORD(wParam) == LBN_SELCHANGE){
				//MessageBox(hwnd,"LBN_SELCHANGE","tip",0);
				iIndex = SendMessage(hwndList,LB_GETCURSEL,0,0);
				iLength = SendMessage(hwndList,LB_GETTEXTLEN,iIndex,0) + 1;
				pVarName = calloc(iLength,sizeof(TCHAR));
				SendMessage(hwndList,LB_GETTEXT,iIndex,(LPARAM)pVarName);
				iLength = GetEnvironmentVariable(pVarName,NULL,0);
				pVarValue = calloc(iLength,sizeof(TCHAR));
				GetEnvironmentVariable(pVarName,pVarValue,iLength);
				SetWindowText(hwndText,pVarValue);
				free(pVarName);
				free(pVarValue);
			}

			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);

			return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	WNDCLASS wndclass;
	static TCHAR szAppName[] = TEXT("Environ");
	HWND hwnd;
	MSG msg;
	
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if(!RegisterClass(&wndclass)){
		MessageBox(NULL,TEXT("The program requires Windows NT"),szAppName,MB_ICONERROR);
	
		return 0;
	}

	hwnd = CreateWindow(szAppName,TEXT("The Environ program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
