#pragma once

class BLL_API GSalesManager
{
public:
    GSalesManager() {};
    ~GSalesManager() {};

public:
    CArray<GSales> * dailyGSales();
    BOOL cashierByOnce(CArray<GSales> *pArrayOrder, int gId, unsigned int amount); //每次扫码收银
    BOOL uncashierAll(CArray<GSales> *pArrayOrder);  //取消本次单据
    BOOL settleAccount(CArray<GSales> *pArrayOrder, int sId); //将结算后的单据内容插入销售表
};