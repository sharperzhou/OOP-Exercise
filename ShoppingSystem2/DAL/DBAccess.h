#pragma once
#include "stdafx.h"
#include "Ado.h"

class DAL_API DBAccess
{
public:
    DBAccess();
    ~DBAccess();

public:
    BOOL DBAccess::executeQuery(CString sql, CAdoRecordSet& adoRecordSet);
    long executeNonQuery(CString sql);

private:
    CAdoConnection adoConn;
};