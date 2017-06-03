#pragma once


#ifdef TOOLS_EXPORTS
#define TOOLS_API __declspec(dllexport)
#else
#define TOOLS_API __declspec(dllimport)
#endif


CString TOOLS_API toCString(double value);
CString TOOLS_API toCString(int value);