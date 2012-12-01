#ifndef FRIEND_H_INCLUDED
#define FRIEND_H_INCLUDED
#include "type.h"
bool getFriendList(userinfo* m_info);
bool getFriend(userinfo* m_info);

friendinfo* getInfoByMobileNo(friendListinfo* Listinfo,  char *MobileNo);
friendinfo* getInfoByFetionId(friendListinfo* Listinfo,  unsigned int FetionId);
void freeAllfriend(friendListinfo* BaseList);
#endif // FRIEND_H_INCLUDED
