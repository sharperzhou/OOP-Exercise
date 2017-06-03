#include "stdafx.h"
#include "..\UIL\UIL.h"

int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd )
{
    //初始化COM
    if (!AfxOleInit()) {
        AfxMessageBox(_T("COM初始化出错！"));
        return -1;
    }

    showWnd();
    return 0;
}