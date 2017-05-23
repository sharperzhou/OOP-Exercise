#pragma once

class Goods
{
public:
    Goods(int gId, CString gName, double gPrice, int gNum);
    Goods(CString gName, double gPrice, int gNum);
    Goods() {};
    ~Goods() {};

public:
    int getGId();
    void setGId(int gId);
    CString getGName();
    void setGName(CString gName);
    double getGPrice();
    void setGPrice(double gPrice);
    int getGNum();
    void setGNum(int gNum);

private:
    int gId;
    CString gName;
    double gPrice;
    int gNum;
};
