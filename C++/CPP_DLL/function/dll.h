#ifndef __dll_h__
#define __dll_h__
#ifndef DLL_EXPORT
#define DLL_EXPORT extern "C" __declspec(dllexport)
#endif

DLL_EXPORT int test(int x, int y);
#endif