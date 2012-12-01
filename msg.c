#include "msg.h"
#include "friend.h"
#include "netCore.h"
#include "parson.h"
#include "friend.h"
#include <string.h>

//---------------------------------------------------------------------------------
void alllist(userinfo* m_info)
{
    char m_url[30];
    fetionBuff buff;
    memset(&buff, 0, sizeof(fetionBuff));
    sprintf(m_url, "t=%llu", getServerID());
    netPOST(m_info ->netHander, "http://f.10086.cn/im5/box/alllist.action", m_url, &buff);
    
    
    
}

//---------------------------------------------------------------------------------
void toChat(userinfo* m_info)
{
    char m_url[30];
    fetionBuff buff;
    memset(&buff, 0, sizeof(fetionBuff));
    sprintf(m_url, "t=%llu", getServerID());
    netPOST(m_info ->netHander, "http://f.10086.cn/im5/chat/toChatMsg.action", m_url, &buff);
}

//--------------------------------------------------------------------------------
bool sendMsgByInfo( netCoreHand* netHander,friendinfo* m_friendInfo, char* msg)
{  
   //{"sendCode":"true","info":"消息发送成功"}
    char m_url[1024];
    fetionBuff buff;
    memset(&buff, 0, sizeof(fetionBuff));
    sprintf(m_url, "touserid=%d&msg=%s",m_friendInfo->idContact, msg);
    return   netPOST(netHander, "http://f.10086.cn/im5/chat/sendNewMsg.action", m_url,  &buff);
}
//--------------------------------------------------------------------------------
bool sendMsgByFetionID(userinfo* m_info, unsigned int fetionID, char* msg)
{

    friendinfo* m_friendInfo = getInfoByFetionId(m_info-> friendList,  fetionID);

    if(m_friendInfo != NULL)  sendMsgByInfo(m_info ->netHander, m_friendInfo,  msg);

}
//---------------------------------------------------------------------------------
bool sendMsgBymobileNo(userinfo* m_info, char* mobileNo,  char* msg)
{
    friendinfo* m_friendInfo = getInfoByMobileNo(m_info-> friendList,  mobileNo);
    if(m_friendInfo != NULL)   sendMsgByInfo(m_info ->netHander, m_friendInfo,  msg);
}

//-----------------------------------------------------------------------------------
bool queryNewMsg(userinfo* m_info)
{

    char m_url[225];
    fetionBuff buff;
    memset(&buff, 0, sizeof(fetionBuff));
    //curl_easy_setopt( m_info ->netHander -> m_curl, CURLOPT_WRITEDATA, (void*)m_info );
    unsigned  long long serverId = getServerID();
    sprintf(m_url, "http://f.10086.cn/im5/chat/queryNewMsg.action?t=%llu&_=%llu&idMsgs=%d&t=%llu",  serverId , serverId + 1 , m_info-> queryMsgId ,serverId);
    return netGET(m_info ->netHander,  m_url, &buff);
}



