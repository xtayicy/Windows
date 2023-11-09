#include <windows.h>
#include <tchar.h>     
#include <stdio.h>    

//#ifndef _VA_LIST_DEFINED
//#ifdef  _M_ALPHA
//typedef struct {
//        char *a0;       /* pointer to first homed integer argument */
//        int offset;     /* byte offset of next parameter */
//} va_list;
//#else
//typedef char *  va_list;
//#endif
//#define _VA_LIST_DEFINED
//#endif

int CDECL MessageBoxPrintf(TCHAR *szCaption,TCHAR *szFormat,...){
	TCHAR szBuffer[1024];
	
	va_list pArgList ;

	va_start(pArgList, szFormat);

	_vsntprintf(szBuffer, sizeof (szBuffer) / sizeof (TCHAR), 
                  szFormat, pArgList) ;

	va_end(pArgList) ;

	return MessageBox(NULL,szBuffer,szCaption,0) ;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
	int cxScreen,cyScreen;
	
	//1366
	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	//768
	cyScreen = GetSystemMetrics(SM_CYSCREEN);
	
	MessageBoxPrintf(TEXT("ScrnSize"),TEXT("The screen is %i pixels wide by %i pixels high."),cxScreen,cyScreen);
	
	return 0;
}
