#include "stdafx.h"
#include "GSales.h"

GSales::GSales(int gId, int sId, int sNum)
 : gId(gId), sId(sId), sNum(sNum) {}

GSales::GSales(CString gName, double gPrice, int gNum, int allSNum)
: gName(gName), gPrice(gPrice), gNum(gNum), allSNum(allSNum) {}

GSales::GSales(int gId, CString gName, double gPrice, int amount)
: gId(gId), gName(gName), gPrice(gPrice), sNum(amount) {}

int GSales::getGId() {
    return gId;
}
void GSales::setGId(int gId) {
    this->gId = gId;
}
int GSales::getSId() {
    return sId;
}
void GSales::setSId(int sId) {
    this->sId = sId;
}
int GSales::getSNum() {
    return sNum;
}
void GSales::setSNum(int sNum) {
    this->sNum = sNum;
}
CString GSales::getGName() {
    return gName;
}
void GSales::setGName(CString gName) {
    this->gName = gName;
}
double GSales::getGPrice() {
    return gPrice;
}
void GSales::setGPrice(double gPrice) {
    this->gPrice = gPrice;
}
int GSales::getGNum() {
    return gNum;
}
void GSales::setGNum(int gNum) {
    this->gNum = gNum;
}
int GSales::getAllSNum() {
    return allSNum;
}
void GSales::setAllSNum(int allSNum) {
    this->allSNum = allSNum;
}