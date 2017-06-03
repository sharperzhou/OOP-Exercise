#include "stdafx.h"
#include "LoginManager.h"

int LoginManager::count = 0;

int LoginManager::getInstanceCount() const {
    return count;
}

LoginManager::LoginManager() {
    ++count;
}

LoginManager::~LoginManager() {
}
