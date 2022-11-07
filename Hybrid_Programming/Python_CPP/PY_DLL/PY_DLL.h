// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the PYDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// PYDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef PYDLL_EXPORTS
#define PYDLL_API extern "C" __declspec(dllexport)
#else
#define PYDLL_API extern "C" __declspec(dllimport)
#endif
#include <iostream>

PYDLL_API int sum(int a, int b);
