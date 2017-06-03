#include "stdafx.h"
#include "AdminManager.h"

BOOL AdminManager::validateLogin(int &id, CString userName, CString password) {
    BOOL fRet = FALSE;
    DBAccess dbAccess;
    CString sql = _T("SELECT * FROM ADMIN WHERE USERNAME = \'")
        + userName + _T("\' AND PASSWORD = \'") + password + _T("\'");
    CAdoRecordSet recordSet;
    dbAccess.executeQuery(sql, recordSet);
    if (!recordSet.IsEOF()) {
    recordSet.GetCollect(_T("ID"), id);
    fRet = TRUE;
    }

    recordSet.Close();
    return fRet;
}