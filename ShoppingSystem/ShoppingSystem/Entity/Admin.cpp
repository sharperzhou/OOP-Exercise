#include "..\framework\stdafx.h"
#include "Admin.h"

Admin::Admin(int id, CString password, CString userName)
: id(id), password(password), userName(userName) {}

Admin::Admin(CString password, CString userName)
: password(password), userName(userName) {}

int Admin::getId() {
    return id;
}

void Admin::setId(int id) {
    this->id = id;
}

CString Admin::getPassword() {
    return password;
}

void Admin::setPassword(CString password) {
    this->password = password;
}

CString Admin::getUserName() {
    return userName;
}

void Admin::setUserName(CString userName) {
    this->userName = userName;
}