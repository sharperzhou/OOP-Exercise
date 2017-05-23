#include "..\Framework\stdafx.h"
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
