#include "stdafx.h"
#include "GSalesManager.h"

/*****************************************************************************************\
* FuncName :   dailyGSales
* Usage    :   Today's sales status
* DataTime :   2017/05/15
* Access   :   public 
* Return   :   CArray<GSales> *
* Waring   :   User must release the memory
\*****************************************************************************************/
CArray<GSales> * GSalesManager::dailyGSales() {
    DBAccess dbAccess;
    CString sql = _T("select GNAME,GPRICE,GNUM,ALLSUM from GOODS,")
        _T("(select GID as SALESID,SUM(SNUM) as ALLSUM from GSALES where ")
        _T("FORMAT(SDATE,\'yyyy-mm-dd\')=FORMAT(NOW,\'yyyy-mm-dd\') GROUP BY GID) ")
        _T("where GID=SALESID");
    CArray<GSales> *pArrayGSales = new CArray<GSales>;
    CAdoRecordSet recordSet;
    dbAccess.executeQuery(sql, recordSet);
    while (!recordSet.IsEOF())
    {
        CString gName;
        double gPrice;
        int gNum;
        int allSNum;

        recordSet.GetCollect(_T("GNAME"), gName);
        recordSet.GetCollect(_T("GPRICE"), gPrice);
        recordSet.GetCollect(_T("GNUM"), gNum);
        recordSet.GetCollect(_T("ALLSUM"), allSNum);

        GSales gSales(gName, gPrice, gNum, allSNum);
        pArrayGSales->Add(gSales);

        recordSet.MoveNext();
    }
    recordSet.Close();
    return pArrayGSales;
}

/*****************************************************************************************\
* FuncName :   cashierByOnce
* Usage    :   每次商品扫码后将销售信息存入向量中，供结算使用
* DataTime :   2017/05/15
* Access   :   public 
* Return   :   BOOL
* Params   :   CArray<GSales> * pArrayOrder
* Params   :   int gId
* Params   :   unsigned int amount
\*****************************************************************************************/
BOOL GSalesManager::cashierByOnce(CArray<GSales> *pArrayOrder, int gId, unsigned int amount) {
    GoodsManager goodsMgr;
    Goods goods = goodsMgr.queryGoods(gId);
    int stock = goods.getGNum(); //当前库存
    if (stock < 1 || stock < amount) return FALSE;

    goods.setGNum(stock - amount);
    goodsMgr.updateGoods(&goods);

    GSales sales(gId, goods.getGName(), goods.getGPrice(), amount);
    pArrayOrder->Add(sales);

    return TRUE;
}

/*****************************************************************************************\
* FuncName :   uncashierAll
* Usage    :   取消结算时，需将单据向量内容清空，并还原商品库存表
* DataTime :   2017/05/15
* Access   :   public 
* Return   :   BOOL
* Params   :   CArray<GSales> * pArrayOrder
\*****************************************************************************************/
BOOL GSalesManager::uncashierAll(CArray<GSales> *pArrayOrder) {
    GoodsManager goodsMgr;
    for (int i = 0, n = pArrayOrder->GetCount(); i < n; ++i) {
        GSales sales = pArrayOrder->GetAt(i);
        Goods goods = goodsMgr.queryGoods(sales.getGId());
        int gNum = goods.getGNum();
        gNum += sales.getSNum();  //还原库存量
        goods.setGNum(gNum);
        goodsMgr.updateGoods(&goods);
    }
    pArrayOrder->RemoveAll();
    return TRUE;
}

/*****************************************************************************************\
* FuncName :   settleAccount
* Usage    :   将结算单据数据写入GSALES表，并清空单据向量内容
* DataTime :   2017/05/15
* Access   :   public 
* Return   :   BOOL
* Params   :   CArray<GSales> * pArrayOrder
* Params   :   int sId
\*****************************************************************************************/
BOOL GSalesManager::settleAccount(CArray<GSales> *pArrayOrder, int sId) {
    DBAccess dbAccess;
    for (int i = 0, n = pArrayOrder->GetCount(); i < n; ++i)
    {
        GSales sales = pArrayOrder->GetAt(i);
        CString sql = _T("INSERT INTO GSALES(GID,SID,SDATE,SNUM) VALUES(")
            + toCString(sales.getGId()) + _T(",")
            + toCString(sId) + _T(",NOW(),")
            + toCString(sales.getSNum()) + _T(")");
        dbAccess.executeNonQuery(sql);
    }
    pArrayOrder->RemoveAll();
    return TRUE;
}