#pragma once

#ifdef DAL_EXPORTS
#define DAL_API __declspec(dllexport)
#else
#define DAL_API __declspec(dllimport)
#endif


#include "DBAccess.h"
#include "Ado.h"