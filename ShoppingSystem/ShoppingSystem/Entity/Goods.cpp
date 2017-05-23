#include "..\framework\stdafx.h"
#include "Goods.h"

Goods::Goods(int gId, CString gName, double gPrice, int gNum)
: gId(gId), gName(gName), gPrice(gPrice), gNum(gNum) {}

Goods::Goods(CString gName, double gPrice, int gNum)
: gName(gName), gPrice(gPrice), gNum(gNum) {}

int Goods::getGId() {
    return gId;
}

void Goods::setGId(int gId) {
    this->gId = gId;
}

CString Goods::getGName() {
    return gName;
}

void Goods::setGName(CString gName) {
    this->gName = gName;
}

double Goods::getGPrice() {
    return gPrice;
}

void Goods::setGPrice(double gPrice) {
    this->gPrice = gPrice;
}

int Goods::getGNum() {
    return gNum;
}

void Goods::setGNum(int gNum) {
    this->gNum = gNum;
}