#include "libfetion.h"
//--------------------------------------------------------------------------------

userinfo* fetionInit()
{
    userinfo* info = malloc(sizeof(userinfo));
    memset(info, 0, sizeof(userinfo));
    info -> friendList = NULL;
    info -> netHander = netInit();
    return info;
}


//---------------------------------------------------------------------------------

void fetionFree(userinfo* info)
{
    netFree(info -> netHander );
    freeAllfriend(info -> friendList);
}
