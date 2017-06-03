#pragma once

#ifdef BLL_EXPORTS
#define BLL_API __declspec(dllexport)
#else
#define BLL_API __declspec(dllimport)
#endif


#include "LoginManager.h"
#include "AdminManager.h"
#include "GoodsManager.h"
#include "GSalesManager.h"
#include "SalesmanManager.h"

