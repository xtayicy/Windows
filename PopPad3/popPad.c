#include <windows.h>
#include "resource.h"
#define ID_EDIT 1
#define UNTITLED "(untitled)"

TCHAR szAppName[] = "PopPad3";
static HWND hDlgModeless;

void PopFileInitialize(HWND);
void PopFontInitialize(HWND);
BOOL PopFileWrite(HWND,PTSTR);
BOOL PopFileSaveDlg(HWND,PTSTR,PTSTR);
BOOL PopFileRead(HWND,PTSTR);
BOOL PopFileOpenDlg(HWND,PTSTR,PTSTR);
BOOL PopPrntPrintFile(HINSTANCE,HWND,HWND,PTSTR);
void PopFontDeinitialize();
HWND PopFindFindDlg(HWND);
BOOL PopFindFindText(HWND,int *,LPFINDREPLACE);
BOOL PopFindValidFind();
BOOL PopFindNextText(HWND,int *);
HWND PopFindReplaceDlg(HWND);
BOOL PopFindReplaceText(HWND,int *,LPFINDREPLACE);
BOOL PopFontChooseFont(HWND);
void PopFontSetFont(HWND);

BOOL CALLBACK AboutDlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
	switch(message){
		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDOK:
					EndDialog(hDlg,0);

					return TRUE;
			}

			break;
	}

	return FALSE;
}

void OkMessage(HWND hwnd,TCHAR *szMessage,TCHAR *szTitleName){
	TCHAR szBuffer[64 + MAX_PATH];

	wsprintf(szBuffer,szMessage,szTitleName[0] ? szTitleName : UNTITLED);
	MessageBox(hwnd,szBuffer,szAppName,MB_OK | MB_ICONEXCLAMATION);
}

short AskAboutSave(HWND hwnd,TCHAR *szTitleName){
	TCHAR szBuffer[64 + MAX_PATH];
	int iReturn;

	wsprintf(szBuffer,"Save current changes in %s?",szTitleName[0] ? szTitleName : UNTITLED);
	iReturn = MessageBox(hwnd,szBuffer,szAppName,MB_YESNOCANCEL | MB_ICONQUESTION);
	if(iReturn == IDYES){
		if(!SendMessage(hwnd,WM_COMMAND,IDM_FILE_SAVE,0)){
			iReturn = IDCANCEL;
		}
	}

	return iReturn;
}

void DoCaption(HWND hwnd,TCHAR *szTitleName){
	TCHAR szCaption[64 + MAX_PATH];

	wsprintf(szCaption,"%s-%s",szAppName,szTitleName[0] ? szTitleName:UNTITLED);
	SetWindowText(hwnd,szCaption);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	static HWND hwndEdit;
	static HINSTANCE hInst;
	static UINT messageFindReplace;
	static TCHAR szTitleName[MAX_PATH],szFileName[MAX_PATH];
	int iSelBeg,iSelEnd,iEnable;
	static BOOL bNeedSave = FALSE;
	static int iOffset;
	LPFINDREPLACE pfr;
	
	//0x00000024
	switch(message){
		case WM_CREATE:
			hInst = ((LPCREATESTRUCT)lParam)->hInstance;
			hwndEdit = CreateWindow("edit",NULL,WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,0,0,0,0,hwnd,(HMENU)ID_EDIT,((LPCREATESTRUCT)lParam)->hInstance,NULL);
			PopFileInitialize(hwnd);
			PopFontInitialize(hwndEdit);
			messageFindReplace = RegisterWindowMessage(FINDMSGSTRING);
			DoCaption(hwnd,szTitleName);

			return 0;

		case WM_SETFOCUS:
			SetFocus(hwndEdit);

			return 0;

		case WM_SIZE:
			MoveWindow(hwndEdit,0,0,LOWORD(lParam),HIWORD(lParam),TRUE);

			return 0;

		case WM_INITMENUPOPUP:
			//MessageBox(hwnd,"WM_INITMENUPOPUP","tip",0);
			switch(lParam){
				case 1:
					EnableMenuItem((HMENU)wParam,IDM_EDIT_UNDO,SendMessage(hwndEdit,EM_CANUNDO,0,0) ? MF_ENABLED : MF_GRAYED);
					EnableMenuItem((HMENU)wParam,IDM_EDIT_PASTE,IsClipboardFormatAvailable(CF_TEXT) ? MF_ENABLED : MF_GRAYED);
					SendMessage(hwndEdit,EM_GETSEL,(WPARAM)&iSelBeg,(LPARAM)&iSelEnd);
					//MessageBeep(0);
					iEnable = iSelBeg != iSelEnd ? MF_ENABLED : MF_GRAYED;
					EnableMenuItem((HMENU)wParam,IDM_EDIT_CUT,iEnable);
					EnableMenuItem((HMENU)wParam,IDM_EDIT_COPY,iEnable);
					EnableMenuItem((HMENU)wParam,IDM_EDIT_CLEAR,iEnable);

					break;

				case 2:
					iEnable = hDlgModeless == NULL ? MF_ENABLED : MF_GRAYED;
					EnableMenuItem((HMENU)wParam,IDM_SEARCH_FIND,iEnable);
					EnableMenuItem((HMENU)wParam,IDM_SEARCH_NEXT,iEnable);
					EnableMenuItem((HMENU)wParam,IDM_SEARCH_REPLACE,iEnable);

					break;
			}

			return 0;

		case WM_COMMAND:
			if(lParam && LOWORD(wParam) == ID_EDIT){
				switch(HIWORD(wParam)){
					case EN_UPDATE:
						bNeedSave = TRUE;

						return 0;
				}

				break;
			}

			switch(LOWORD(wParam)){
				case IDM_FILE_NEW:
					//MessageBeep(0);
					if(bNeedSave && IDCANCEL == AskAboutSave(hwnd,szTitleName)){
						return 0;
					}

					SetWindowText(hwndEdit,"\0");
					szFileName[0] = '\0';
					szTitleName[0] = '\0';
					DoCaption(hwnd,szTitleName);
					bNeedSave = FALSE;

					return 0;

				case IDM_FILE_OPEN:
					if(bNeedSave && IDCANCEL == AskAboutSave(hwnd,szTitleName)){
						return 0;
					}
					
					if(PopFileOpenDlg(hwnd,szFileName,szTitleName)){
						if(!PopFileRead(hwndEdit,szFileName)){
							OkMessage(hwnd,"Could not read file %s",szTitleName);
							szFileName[0]  = '\0' ;
							szTitleName[0] = '\0' ;
						}
					}

					DoCaption (hwnd, szTitleName) ;
					bNeedSave = FALSE;

					return 0;

				case IDM_FILE_SAVE:
					if(szFileName[0]){
						if(PopFileWrite(hwndEdit,szFileName)){
							bNeedSave = FALSE;

							return 1;
						}else{
							OkMessage(hwnd,"Could not write file %s",szTitleName);

							return 0;
						}
					}
				
				case IDM_FILE_SAVE_AS:
					if(PopFileSaveDlg(hwnd,szFileName,szTitleName)){
						DoCaption(hwnd,szTitleName);
						if(PopFileWrite(hwndEdit,szFileName)){
							bNeedSave = FALSE;

							return 1;
						}else{
							OkMessage(hwnd,"Could not write file %s",szTitleName);

							return 0;
						}
					}

					return 0;

				case IDM_FILE_PRINT:
					if(!PopPrntPrintFile(hInst,hwnd,hwndEdit,szTitleName)){
						OkMessage(hwnd,"Could not print file %s",szTitleName);
					}

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

				case IDM_SEARCH_FIND:
					SendMessage(hwndEdit,EM_GETSEL,0,(LPARAM)&iOffset);
					//MessageBeep(0);
					hDlgModeless = PopFindFindDlg(hwnd);

					return 0;

				case IDM_SEARCH_NEXT:
					SendMessage(hwndEdit,EM_GETSEL,0,(LPARAM)&iOffset);
					if(PopFindValidFind()){
						//MessageBox(hwnd,"if","tip",0);
						PopFindNextText(hwndEdit,&iOffset);
					}else{
						//MessageBox(hwnd,"else","tip",0);
						hDlgModeless = PopFindFindDlg(hwnd);
					}

					return 0;

				case IDM_SEARCH_REPLACE:
					SendMessage(hwndEdit,EM_GETSEL,0,(LPARAM)&iOffset);
					hDlgModeless = PopFindReplaceDlg(hwnd);

					return 0;

				case IDM_FORMAT_FONT:
					if(PopFontChooseFont(hwnd)){
						PopFontSetFont(hwndEdit);
					}

					return 0;

				case IDM_HELP:
					OkMessage(hwnd,"Help not yet implemented!","\0");

					return 0;

				case IDM_APP_ABOUT:
					DialogBox(hInst,"AboutBox",hwnd,AboutDlgProc);

					return 0;
			}

			break;

		case WM_DESTROY:
			PopFontDeinitialize();
			PostQuitMessage(0);

			return 0;

		default:
			if(message == messageFindReplace){
				//MessageBox(hwnd,"messageFindReplace","tip",0);
				pfr = (LPFINDREPLACE)lParam;
				if(pfr->Flags & FR_DIALOGTERM){
					//MessageBox(hwnd,"FR_DIALOGTERM","tip",0);
					hDlgModeless = NULL;
				}

				if(pfr->Flags & FR_FINDNEXT){
					//MessageBox(hwnd,"FR_FINDNEXT","tip",0);
					if(!PopFindFindText(hwndEdit,&iOffset,pfr)){
						OkMessage(hwnd,"Text not found!","\0");
					}
				}

				if(pfr->Flags & FR_REPLACE || pfr->Flags & FR_REPLACEALL){
					if(!PopFindReplaceText(hwndEdit,&iOffset,pfr)){
						OkMessage(hwnd,"Text not found!","\0");
					}
				}

				return 0;
			}

			break;
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
		if(hDlgModeless == NULL || !IsDialogMessage(hDlgModeless,&msg)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}
