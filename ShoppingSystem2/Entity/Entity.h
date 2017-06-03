#pragma once

#ifdef ENTITY_EXPORTS
#define ENTITY_API __declspec(dllexport)
#else
#define ENTITY_API __declspec(dllimport)
#endif


#include "Admin.h"
#include "Goods.h"
#include "GSales.h"
#include "Salesman.h"