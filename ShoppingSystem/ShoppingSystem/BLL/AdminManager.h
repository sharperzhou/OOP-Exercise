#pragma once
#include "..\Entity\Admin.h"
#include "LoginManager.h"

class AdminManager : public LoginManager
{
public:
    AdminManager() : LoginManager() {};
    virtual ~AdminManager() {};

public:
    BOOL virtual validateLogin(int &id, CString userName, CString password);
};