#include <windows.h>
#include "resource.h"

#ifdef UNICODE

#define CF_TCHAR CF_UNICODETEXT
TCHAR szDefaultText[] = TEXT ("Default Text - Unicode Version") ;
TCHAR szCaption[]     = TEXT ("Clipboard Text Transfers - Unicode Version") ;

#else

#define CF_TCHAR CF_TEXT
TCHAR szDefaultText[] = TEXT ("Default Text - ANSI Version") ;
TCHAR szCaption[]     = TEXT ("Clipboard Text Transfers - ANSI Version") ;

#endif

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	static PTSTR pText ;
	RECT         rect ;
	BOOL         bEnable ;
	HGLOBAL      hGlobal ;
	PTSTR        pGlobal ;
	
	//0x00000024
	switch(message){
		case WM_CREATE:
			SendMessage(hwnd,WM_COMMAND,IDM_EDIT_RESET,0);

			return 0;

		case WM_INITMENUPOPUP:
			EnableMenuItem((HMENU)wParam,IDM_EDIT_PASTE,IsClipboardFormatAvailable(CF_TCHAR) ? MF_ENABLED : MF_GRAYED);
			bEnable = pText ? MF_ENABLED : MF_GRAYED ;
			EnableMenuItem ((HMENU) wParam, IDM_EDIT_CUT,   bEnable) ;
            EnableMenuItem ((HMENU) wParam, IDM_EDIT_COPY,  bEnable) ;
            EnableMenuItem ((HMENU) wParam, IDM_EDIT_DELETE, bEnable) ;

			return 0;

		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDM_EDIT_PASTE:
					OpenClipboard (hwnd);

					   if (hGlobal = GetClipboardData (CF_TCHAR))
					   {
							pGlobal = GlobalLock (hGlobal) ;

							if (pText)
							{
								 free (pText) ;
								 pText = NULL ;
							}
							pText = malloc (GlobalSize (hGlobal)) ;
							lstrcpy (pText, pGlobal) ;
							InvalidateRect (hwnd, NULL, TRUE) ;
					   }
					   GlobalUnlock(hGlobal);
					   CloseClipboard () ;

					return 0;

				case IDM_EDIT_CUT:
				case IDM_EDIT_COPY:
					if (!pText)
						return 0 ;

					   hGlobal = GlobalAlloc (GHND | GMEM_SHARE, 
											  (lstrlen (pText) + 1) * sizeof (TCHAR)) ;
					   pGlobal = GlobalLock (hGlobal) ;
					   lstrcpy (pGlobal, pText) ;
					   GlobalUnlock (hGlobal) ;

					   OpenClipboard (hwnd) ;
					   EmptyClipboard () ;
					   SetClipboardData (CF_TCHAR, hGlobal) ;
					   CloseClipboard () ;

					   if (LOWORD (wParam) == IDM_EDIT_COPY)
							return 0 ;

				case IDM_EDIT_DELETE:
					if (pText)
					   {
							free (pText) ;
							pText = NULL ;
					   }
						InvalidateRect (hwnd, NULL, TRUE) ;

					return 0;

				case IDM_EDIT_RESET:
					if(pText){
						free(pText);
						pText = NULL;
					}

					pText = malloc ((lstrlen (szDefaultText) + 1) * sizeof (TCHAR)) ;
					lstrcpy (pText, szDefaultText) ;
					InvalidateRect (hwnd, NULL, TRUE) ;

					return 0;
			}

			return 0;

		case WM_SIZE:

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			
			GetClientRect (hwnd, &rect) ;
			if (pText != NULL)
               DrawText (hdc, pText, -1, &rect, DT_EXPANDTABS | DT_WORDBREAK) ;

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
	static TCHAR szAppName[] = TEXT("ClipText");
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

	hwnd = CreateWindow(szAppName,TEXT("The ClipText program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU)),hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
