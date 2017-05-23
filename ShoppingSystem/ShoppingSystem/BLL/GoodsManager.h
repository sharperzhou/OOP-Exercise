#pragma once
#include "..\Entity\Goods.h"

class GoodsManager
{
public:
    GoodsManager() {};
    ~GoodsManager() {};

public:
    BOOL addGoods(Goods *goods);
    BOOL updateGoods(Goods *goods);
    BOOL deleteGoods(int gId);
    CArray<Goods> * displayGoods();
    CArray<Goods> * queryGoods(CString gName);
    Goods queryGoods(int gId);
};
