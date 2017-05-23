#include "..\Framework\stdafx.h"
#include "SalesmanManager.h"
#include "..\Entity\Salesman.h"
#include "..\DAL\DBAccess.h"
#include "..\Tools\Tools.h"

BOOL SalesmanManager::addSalesman(Salesman *salesman) {
    DBAccess dbAccess;
    CString sql = _T("INSERT INTO SALESMAN(SPASSWORD,SNAME) VALUES(\'")
        + salesman->getSPassword() + _T("\',\'")
        + salesman->getSName() + _T("\')");
    long lRet = 0;
    try {
        lRet = dbAccess.executeNonQuery(sql);
    }
    catch (...) {}
    return lRet > 0 ? TRUE : FALSE;
}

BOOL SalesmanManager::updateSalesman(Salesman *salesman) {
    DBAccess dbAccess;
    CString sql = _T("UPDATE SALESMAN SET SPASSWORD=\'")
        + salesman->getSPassword() + _T("\',SNAME=\'")
        + salesman->getSName() + _T("\' WHERE SID=")
        + toCString(salesman->getSId());
    long lRet = 0;
    try {
        lRet = dbAccess.executeNonQuery(sql);
    }
    catch (...) {}
    return lRet > 0 ? TRUE : FALSE;
}

BOOL SalesmanManager::deleteSalesman(int sId) {
    DBAccess dbAccess;
    CString sql = _T("DELETE FROM SALESMAN WHERE SID=")
        + toCString(sId);
    long lRet = 0;
    try {
        lRet = dbAccess.executeNonQuery(sql);
    }
    catch (...) {}
    return lRet > 0 ? TRUE : FALSE;
}

CArray<Salesman> * SalesmanManager::querySalesman(CString sName) {
    DBAccess dbAccess;
    CString sql = _T("SELECT * FROM SALESMAN WHERE SNAME LIKE \'%")
        + sName + _T("%\'");
    CAdoRecordSet recordSet;
    dbAccess.executeQuery(sql, recordSet);
    CArray<Salesman> *pArraySalesman = new CArray<Salesman>;
    while (!recordSet.IsEOF()) {
        int sId;
        CString sPassword;
        CString sName;

        recordSet.GetCollect(_T("SID"), sId);
        recordSet.GetCollect(_T("SPASSWORD"), sPassword);
        recordSet.GetCollect(_T("SNAME"), sName);

        Salesman salesman(sId, sPassword, sName);
        pArraySalesman->Add(salesman);

        recordSet.MoveNext();
    }
    recordSet.Close();
    return pArraySalesman;
}

Salesman SalesmanManager::querySalesman(int sId) {
    DBAccess dbAccess;
    CString sql = _T("SELECT * FROM SALESMAN WHERE SID =")
        + toCString(sId);
    CAdoRecordSet recordSet;
    dbAccess.executeQuery(sql, recordSet);
    Salesman salesman;
    while (!recordSet.IsEOF())
    {
        int sId;
        CString sPassword;
        CString sName;

        recordSet.GetCollect(_T("SID"), sId);
        recordSet.GetCollect(_T("SPASSWORD"), sPassword);
        recordSet.GetCollect(_T("SNAME"), sName);

        Salesman salesman(sId, sPassword, sName);

        recordSet.MoveNext();
    }
    recordSet.Close();
    return salesman;
}

CArray<Salesman> * SalesmanManager::displaySalesman() {
    DBAccess dbAccess;
    CString sql = _T("SELECT * FROM SALESMAN");
    CAdoRecordSet recordSet;
    dbAccess.executeQuery(sql, recordSet);
    CArray<Salesman> *pArraySalesman = new CArray<Salesman>;
    while (!recordSet.IsEOF()) {
        int sId;
        CString sPassword;
        CString sName;

        recordSet.GetCollect(_T("SID"), sId);
        recordSet.GetCollect(_T("SPASSWORD"), sPassword);
        recordSet.GetCollect(_T("SNAME"), sName);

        Salesman saleman(sId, sPassword, sName);
        pArraySalesman->Add(saleman);

        recordSet.MoveNext();
    }
    recordSet.Close();
    return pArraySalesman;
}

BOOL SalesmanManager::validateLogin(int &id, CString userName, CString password) {
    BOOL fRet = FALSE;
    DBAccess dbAccess;
    CString sql = _T("SELECT * FROM SALESMAN WHERE SNAME = \'")
        + userName + _T("\' AND SPASSWORD = \'") + password + _T("\'");
    CAdoRecordSet recordSet;
    dbAccess.executeQuery(sql, recordSet);
    if (!recordSet.IsEOF()) {
        recordSet.GetCollect(_T("SID"), id);
        fRet = TRUE;
    }
    recordSet.Close();
    return fRet;
}