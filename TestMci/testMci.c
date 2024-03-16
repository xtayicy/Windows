#include <windows.h>
#include "resource.h"

TCHAR szAppName [] = TEXT ("TestMci") ;

BOOL CALLBACK DlgProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	RECT        rect ;
	static HWND hwndEdit ;
	int         iCharBeg, iCharEnd, iLineBeg, iLineEnd, iChar, iLine, iLength ;
	TCHAR       szCommand [1024], szReturn [1024], 
                 szError [1024], szBuffer [32] ;
	MCIERROR    error ;

	switch(message){
		case WM_INITDIALOG:
			GetWindowRect (hwnd, &rect) ;
			SetWindowPos (hwnd, NULL, 
               (GetSystemMetrics (SM_CXSCREEN) - rect.right + rect.left) / 2,
               (GetSystemMetrics (SM_CYSCREEN) - rect.bottom + rect.top) / 2,
               0, 0, SWP_NOZORDER | SWP_NOSIZE) ;
			hwndEdit = GetDlgItem (hwnd, IDC_MAIN_EDIT) ;
			SetFocus (hwndEdit) ;

			return FALSE;

		case WM_COMMAND:
			switch(LOWORD (wParam)){
				case IDCANCEL:
					EndDialog (hwnd, 0) ;
				
					return TRUE;

				case IDOK:
					SendMessage (hwndEdit, EM_GETSEL, (WPARAM) &iCharBeg, 
                                                 (LPARAM) &iCharEnd) ;
					iLineBeg = SendMessage (hwndEdit, EM_LINEFROMCHAR, iCharBeg, 0) ;
					iLineEnd = SendMessage (hwndEdit, EM_LINEFROMCHAR, iCharEnd, 0) ;
					for(iLine = iLineBeg ; iLine <= iLineEnd ; iLine++){
						* (WORD *) szCommand = sizeof (szCommand) / sizeof (TCHAR) ;
						iLength = SendMessage (hwndEdit, EM_GETLINE, iLine, 
                                                     (LPARAM) szCommand) ;
						szCommand [iLength] = '\0' ;
						if (iLength == 0)
                            continue ;
						
						error = mciSendString (szCommand, szReturn, 
                              sizeof (szReturn) / sizeof (TCHAR), hwnd) ;
						SetDlgItemText (hwnd, IDC_RETURN_STRING, szReturn) ;
						mciGetErrorString (error, szError, 
                                       sizeof (szError) / sizeof (TCHAR)) ;
						SetDlgItemText (hwnd, IDC_ERROR_STRING, szError) ;
					}

					iChar  = SendMessage (hwndEdit, EM_LINEINDEX,  iLineEnd, 0) ;
					iChar += SendMessage (hwndEdit, EM_LINELENGTH, iCharEnd, 0) ;
					SendMessage (hwndEdit, EM_SETSEL, iChar, iChar) ;
					SendMessage (hwndEdit, EM_REPLACESEL, FALSE, 
                                      (LPARAM) TEXT ("\r\n")) ;
					SetFocus (hwndEdit) ;

					return TRUE;
			}

			break;

		case MM_MCINOTIFY:
			MessageBox(hwnd,"MM_MCINOTIFY","tip",0);

			return TRUE;

		case WM_TIMER:

			return TRUE;
	}

	return FALSE ;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	if (-1 == DialogBox (hInstance, szAppName, NULL, DlgProc))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"),
                      szAppName, MB_ICONERROR) ;
     }

	return 0;
}
