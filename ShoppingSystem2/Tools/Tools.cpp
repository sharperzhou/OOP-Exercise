// Tools.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "Tools.h"

CString toCString(double value) {
    CString str;
    str.Format(_T("%g"), value);
    return str;
}

CString toCString(int value) {
    CString str;
    str.Format(_T("%d"), value);
    return str;
}

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

