// PY_DLL.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "PY_DLL.h"


PYDLL_API int sum(int a, int b) {
	return a + b;
}