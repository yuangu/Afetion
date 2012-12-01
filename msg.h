#ifndef MSG_H_INCLUDED
#define MSG_H_INCLUDED
#include "type.h"
void alllist(userinfo* m_info);
void toChat(userinfo* m_info);
bool sendMsgByFetionID(userinfo* m_info, unsigned int fetionID, char* msg);
bool sendMsgBymobileNo(userinfo* m_info, char* mobileNo,  char* msg);
bool queryNewMsg(userinfo* m_info);


#endif // MSG_H_INCLUDED
