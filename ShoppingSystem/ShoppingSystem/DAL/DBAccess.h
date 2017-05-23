#pragma once
#include "Ado.h"

class DBAccess
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