#pragma once

class Admin
{
public:
    Admin(int id, CString password, CString userName);
    Admin(CString password, CString sName);
    Admin() {};
    ~Admin() {};

public:
    int getId();
    void setId(int id);
    CString getPassword();
    void setPassword(CString password);
    CString getUserName();
    void setUserName(CString userName);

private:
    int id;
    CString password;
    CString userName;
};
