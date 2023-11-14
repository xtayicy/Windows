#include <windows.h>
#include "DLLLib.h"

EXPORT BOOL CALLBACK DLLCenterTextW (HDC hdc, PRECT prc, PCWSTR pString)
{
     int  iLength ;
     SIZE size ;

     iLength = lstrlenW (pString) ;

     GetTextExtentPoint32W (hdc, pString, iLength, &size) ;

     return TextOutW (hdc, (prc->right - prc->left - size.cx) / 2,
                           (prc->bottom - prc->top - size.cy) / 2,
                      pString, iLength) ;
}

EXPORT BOOL CALLBACK DLLCenterTextA(HDC hdc,PRECT prc,PCSTR pString){
	int iLength;
	SIZE size ;

	iLength = lstrlenA(pString);
	GetTextExtentPoint32A (hdc, pString, iLength, &size) ;

    return TextOutA (hdc, (prc->right - prc->left - size.cx) / 2,
                           (prc->bottom - prc->top - size.cy) / 2,
                      pString, iLength) ;
}

int WINAPI DLLMain(HINSTANCE hInstance,DWORD fdwReason,PVOID pvReserved){
	
	return TRUE;
}