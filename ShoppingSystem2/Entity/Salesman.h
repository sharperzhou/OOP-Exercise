#pragma once

class ENTITY_API Salesman
{
public:
    Salesman(int sId, CString sPassword, CString sName);
    Salesman(CString sPassword, CString sName);
    Salesman() {};
    ~Salesman() {};

public:
    int getSId();
    void setSId(int sId);
    CString getSPassword();
    void setSPassword(CString sPassword);
    CString getSName();
    void setSName(CString sName);

private:
    int sId;
    CString sPassword;
    CString sName;
};
