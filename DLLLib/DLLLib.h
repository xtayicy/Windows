#ifdef __cplusplus
#define EXPORT extern "C" __declspec (dllexport)
#else
#define EXPORT __declspec (dllexport)
#endif

EXPORT BOOL CALLBACK DLLCenterTextA (HDC, PRECT, PCSTR) ;
EXPORT BOOL CALLBACK DLLCenterTextW (HDC, PRECT, PCWSTR) ;

#ifdef UNICODE
#define DLLCenterText DLLCenterTextW
#else
#define DLLCenterText DLLCenterTextA
#endif