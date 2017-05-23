#include "..\framework\stdafx.h"
#include "GoodsManager.h"
#include "..\DAL\DBAccess.h"
#include "..\Tools\Tools.h"

/*****************************************************************************************\
* FuncName :   addGoods
* Usage    :   Add goods to database
* DataTime :   2017/05/14
* Access   :   public 
* Return   :   BOOL
* Params   :   Goods * goods
\*****************************************************************************************/
BOOL GoodsManager::addGoods(Goods *goods) {
    DBAccess dbAccess;
    CString sql = _T("INSERT INTO GOODS(GNAME,GPRICE,GNUM) VALUES(\'")
        + goods->getGName() + _T("\',") + toCString(goods->getGPrice())
        + _T(",") + toCString(goods->getGNum()) + _T(")");
    long lRet = 0;
    try
    {
        lRet = dbAccess.executeNonQuery(sql);
    }
    catch (...) {}

    return lRet > 0 ? TRUE : FALSE;
}

/*****************************************************************************************\
* FuncName :   updateGoods
* Usage    :   Update ths goods from UI to database
* DataTime :   2017/05/14
* Access   :   public 
* Return   :   BOOL
* Params   :   Goods * goods
\*****************************************************************************************/
BOOL GoodsManager::updateGoods(Goods *goods) {
    DBAccess dbAccess;
    CString sql = _T("UPDATE GOODS SET GNAME=\'") + goods->getGName()
        + _T("\',GPRICE=") + toCString(goods->getGPrice())
        + _T(",GNUM=") + toCString(goods->getGNum()) + _T(" WHERE GID=")
        + toCString(goods->getGId());
    long lRet = 0;
    try
    {
        lRet = dbAccess.executeNonQuery(sql);
    }
    catch (...) {}

    return lRet > 0 ? TRUE : FALSE;
}

/*****************************************************************************************\
* FuncName :   deleteGoods
* Usage    :   delete goods from database
* DataTime :   2017/05/14
* Access   :   public 
* Return   :   BOOL
* Params   :   Goods * goods
\*****************************************************************************************/
BOOL GoodsManager::deleteGoods(int gId) {
    DBAccess dbAccess;
    CString sql = _T("DELETE FROM GOODS WHERE GID=")
        + toCString(gId);
    long lRet = 0;
    try
    {
        lRet = dbAccess.executeNonQuery(sql);
    }
    catch (...) {}

    return lRet > 0 ? TRUE : FALSE;
}

/*****************************************************************************************\
* FuncName :   queryGoods
* Usage    :   According to the goods name to query goods from database (fuzzy query)
* DataTime :   2017/05/14
* Access   :   public 
* Return   :   CArray<Goods> *
* Params   :   CString gName
* Warning  :   User must free memory
\*****************************************************************************************/
CArray<Goods> * GoodsManager::queryGoods(CString gName) {
    CArray<Goods> *pArrayGoods = new CArray<Goods>;
    DBAccess dbAccess;
    CString sql = _T("SELECT * FROM GOODS WHERE GNAME LIKE \'%")
        + gName + _T("%\'");
    CAdoRecordSet recordSet;
    dbAccess.executeQuery(sql, recordSet);
    while (!recordSet.IsEOF())
    {
        int gId;
        CString gName;
        double gPrice;
        int gNum;

        recordSet.GetCollect(_T("GID"), gId);
        recordSet.GetCollect(_T("GNAME"), gName);
        recordSet.GetCollect(_T("GPRICE"), gPrice);
        recordSet.GetCollect(_T("GNUM"), gNum);

        Goods goods(gId, gName, gPrice, gNum);
        pArrayGoods->Add(goods);

        recordSet.MoveNext();
    }
    recordSet.Close();
    
    return pArrayGoods;
}

/*****************************************************************************************\
* FuncName :   queryGoods
* Usage    :   Query goods through gId, result is unique
* DataTime :   2017/05/15
* Access   :   public 
* Return   :   Goods
* Params   :   int gId
\*****************************************************************************************/
Goods GoodsManager::queryGoods(int gId) {
    DBAccess dbAccess;
    CString sql = _T("SELECT * FROM GOODS WHERE GID =")
        + toCString(gId);
    CAdoRecordSet recordSet;
    dbAccess.executeQuery(sql, recordSet);
    Goods goods;
    while (!recordSet.IsEOF())
    {
        int gId;
        CString gName;
        double gPrice;
        int gNum;

        recordSet.GetCollect(_T("GID"), gId);
        recordSet.GetCollect(_T("GNAME"), gName);
        recordSet.GetCollect(_T("GPRICE"), gPrice);
        recordSet.GetCollect(_T("GNUM"), gNum);

        goods.setGId(gId);
        goods.setGName(gName);
        goods.setGPrice(gPrice);
        goods.setGNum(gNum);

        recordSet.MoveNext();
    }
    recordSet.Close();
    return goods;
}

/*****************************************************************************************\
* FuncName :   displayGoods
* Usage    :   Display all goods
* DataTime :   2017/05/14
* Access   :   public 
* Return   :   CArray<Goods> *
* Warning  :   User must free memory
\*****************************************************************************************/
CArray<Goods> * displayGoods()  {
    CArray<Goods> *pArrayGoods = new CArray<Goods>;
    DBAccess dbAccess;
    CString sql = _T("SELECT * FROM GOODS");
    CAdoRecordSet recordSet;
    dbAccess.executeQuery(sql, recordSet);
    while (!recordSet.IsEOF())
    {
        int gId;
        CString gName;
        double gPrice;
        int gNum;

        recordSet.GetCollect(_T("GID"), gId);
        recordSet.GetCollect(_T("GNAME"), gName);
        recordSet.GetCollect(_T("GPRICE"), gPrice);
        recordSet.GetCollect(_T("GNUM"), gNum);

        Goods goods(gId, gName, gPrice, gNum);
        pArrayGoods->Add(goods);

        recordSet.MoveNext();
    }
    recordSet.Close();

    return pArrayGoods;
}