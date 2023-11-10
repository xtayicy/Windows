#include <windows.h>

#define BUFFER(x,y) *(pBuffer + y * cxBuffer + x)

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	static int cxChar,cyChar,cxClient,cyClient,cxBuffer,cyBuffer,xCaret,yCaret;
	static TCHAR * pBuffer = NULL ;
	int x,y;

	//0x00000024
	switch(message){
		case WM_CREATE:
			hdc = GetDC(hwnd);
			
			SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
			GetTextMetrics(hdc,&tm);
			cxChar = tm.tmAveCharWidth;
			cyChar = tm.tmHeight;
			
			ReleaseDC(hwnd,hdc);

			return 0;

		case WM_SIZE:
			if(message == WM_SIZE){
				cxClient = LOWORD(lParam);
				cyClient = HIWORD(lParam);
			}

			cxBuffer = max(1,cxClient / cxChar);
			cyBuffer = max(1,cyClient / cyChar);
			
			//allocate memory for buffer and clear it
			if(pBuffer != NULL){
				free(pBuffer);
			}

			pBuffer = (TCHAR *) malloc (cxBuffer * cyBuffer * sizeof (TCHAR)) ;
			for (y = 0 ; y < cyBuffer ; y++)
               for (x = 0 ; x < cxBuffer ; x++)
                   BUFFER(x,y) = ' ' ;
                    
		    xCaret = 0 ;
		    yCaret = 0 ;

			if (hwnd == GetFocus ())
               SetCaretPos (xCaret * cxChar, yCaret * cyChar) ;

			return 0;

		case WM_SETFOCUS:
			CreateCaret(hwnd,NULL,cxChar,cyChar);
			ShowCaret(hwnd);

			return 0;

		case WM_KILLFOCUS:
			HideCaret(hwnd);
			DestroyCaret();

			return 0;

		case WM_KEYDOWN:
			switch(wParam){
				case VK_HOME:
					xCaret = 0;

					break;

				case VK_END:
					xCaret = cxBuffer - 1;

					break;

				case VK_PRIOR:
					yCaret = 0;

					break;

				case VK_NEXT:
					yCaret = cyBuffer - 1;

					break;

				case VK_LEFT:
					xCaret = max(xCaret - 1,0);

					break;

				case VK_RIGHT:
					xCaret = min(xCaret + 1,cxBuffer - 1);

					break;

				case VK_UP:
					yCaret = max(yCaret - 1,0);

					break;

				case VK_DOWN:
					yCaret = min(yCaret + 1,cyBuffer - 1);

					break;
			}

			SetCaretPos(xCaret * cxChar,yCaret * cyChar);

			return 0;
			
		case WM_CHAR:
			BUFFER(xCaret,yCaret) = (TCHAR)wParam;
			HideCaret(hwnd);
			hdc = GetDC(hwnd);

			SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
			TextOut (hdc, xCaret * cxChar, yCaret * cyChar,
                             & BUFFER (xCaret, yCaret), 1) ;
			
			ReleaseDC(hwnd,hdc);

			ShowCaret(hwnd);
			if(++xCaret == cxBuffer){
				xCaret = 0;
				if(++yCaret == cyBuffer){
					yCaret = 0;
				}
			}

			SetCaretPos(xCaret * cxChar,yCaret * cyChar);

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
	static TCHAR szAppName[] = TEXT("Typer");
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

	hwnd = CreateWindow(szAppName,TEXT("The Typer program"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nShowCmd);
	//UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
