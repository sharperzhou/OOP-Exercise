#pragma once

class BLL_API SalesmanManager : public LoginManager
{
public:
    SalesmanManager() : LoginManager() {};
    virtual ~SalesmanManager() {};

public:
    BOOL addSalesman(Salesman *salesman);
    BOOL updateSalesman(Salesman *salesman);
    BOOL deleteSalesman(int sId);
    CArray<Salesman> * querySalesman(CString sName);
    Salesman querySalesman(int sId);
    CArray<Salesman> * displaySalesman();
    BOOL virtual validateLogin(int &id, CString userName, CString password);
};