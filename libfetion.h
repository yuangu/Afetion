#ifndef LIBFETION_H_INCLUDED
#define LIBFETION_H_INCLUDED
#include "netCore.h"
#include "type.h"
#include "login.h"
userinfo* fetionInit();
void fetionFree(userinfo* info);

#endif // LIBFETION_H_INCLUDED
