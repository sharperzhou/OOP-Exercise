#include "stdafx.h"
#include "Salesman.h"

Salesman::Salesman(int sId, CString sPassword, CString sName)
: sId(sId), sPassword(sPassword), sName(sName) {}

Salesman::Salesman(CString sPassword, CString sName)
: sPassword(sPassword), sName(sName) {}

int Salesman::getSId() {
    return sId;
}

void Salesman::setSId(int sId) {
    this->sId = sId;
}

CString Salesman::getSPassword() {
    return sPassword;
}

void Salesman::setSPassword(CString sPassword) {
    this->sPassword = sPassword;
}

CString Salesman::getSName() {
    return sName;
}

void Salesman::setSName(CString sName) {
    this->sName = sName;
}