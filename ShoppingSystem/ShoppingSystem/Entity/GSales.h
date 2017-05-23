#pragma once

class GSales
{
public:
    GSales(int gId, int sId, int sNum);
    GSales(CString gName, double gPrice, int gNum, int allSNum);
    GSales(int gId, CString gName, double gPrice, int amount);
    GSales() {};
    ~GSales() {};

public:
    int getGId();
    void setGId(int gId);
    int getSId();
    void setSId(int sId);
    int getSNum();
    void setSNum(int sNum);
    CString getGName();
    void setGName(CString gName);
    double getGPrice();
    void setGPrice(double gPrice);
    int getGNum();
    void setGNum(int gNum);
    int getAllSNum();
    void setAllSNum(int allSNum);

private:
    int gId;  //商品Id
    int sId;  //售货员Id
    int sNum; //销售数量

    CString gName;  //商品名称
    double gPrice;  //商品单价
    int gNum;       //商品数量
    int allSNum;    //单种商品销售总和
};
