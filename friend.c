#include "friend.h"
#include "netCore.h"
#include "parson.h"
#include "type.h"
#include <string.h>

//-----------------------------------------------------------------------
friendinfo* getInfoByFetionId(friendListinfo* Listinfo,  unsigned int FetionId)
{
    friendListinfo* listPtr =  Listinfo;
    friendinfo*  friendPtr = listPtr ->friendfrist;
    while(listPtr != NULL )
    {
        while(friendPtr != NULL)
        {
            if( friendPtr -> idFetion == FetionId )
            {
                return friendPtr;
            }
            friendPtr = (friendinfo*)(friendPtr -> next);
        }
        listPtr  = listPtr -> next;
    }
    return NULL;
}

//-------------------------------------------------------------------------
friendinfo* getInfoByMobileNo(friendListinfo* Listinfo,  char *MobileNo)
{
    friendinfo*  friendPtr = NULL;
    friendListinfo* listPtr =  Listinfo;
    if(listPtr != NULL)  friendPtr = listPtr ->friendfrist;
    while(listPtr != NULL )
    {
        while(friendPtr != NULL)
        {
            if( strcmp(friendPtr -> mobileNo,MobileNo) == 0 )
            {
                return friendPtr;
            }
            friendPtr = (friendinfo*)(friendPtr -> next);
        }
        listPtr  = listPtr -> next;
        if(listPtr != NULL)  friendPtr = listPtr ->friendfrist;
    }
    return NULL;
}
//-----------------------------------------------------------------------------
void insertFriendList(userinfo* m_info, friendListinfo* insertInfo)
{
    friendListinfo** listPtr =  &(m_info-> friendList);
    friendListinfo*  info = malloc(sizeof(friendListinfo));
    memcpy(info, insertInfo, sizeof(friendListinfo) );

    while(*listPtr != NULL )
    {
        listPtr  =  &((*listPtr) -> next);
    }
    *listPtr = info;
}
//--------------------------------------------------------------------------------
void insertFriend(friendListinfo* m_friendListInfo, friendinfo* insertInfo)
{
    friendinfo** friendPtr =  &(m_friendListInfo -> friendfrist) ;
    friendinfo*  info = malloc(sizeof(friendinfo));
    memcpy(info, insertInfo, sizeof(friendinfo) );

    while(*friendPtr != NULL )
    {
        friendPtr = &( (*friendPtr) -> next);
    }
    *friendPtr = info;
}
//--------------------------------------------------------------------------------------
void freeAllfriend(friendListinfo* BaseList)
{
    friendListinfo* listPtr = BaseList;
    friendinfo*  friendPtr = listPtr ->friendfrist;

    while(listPtr != NULL )
    {
        friendListinfo*  listNextPtr = NULL;
        while(friendPtr != NULL)
        {
            friendinfo*  friendNextPtr = (friendinfo*)(friendPtr -> next);
            free(friendPtr);
            friendPtr = friendNextPtr;
        }
        listNextPtr = listPtr -> next;
        free(listPtr );
        listPtr = listNextPtr;
    }
}

//--------------------------------------------------------------------------------------
bool getFriendList(userinfo* m_info)
{
    char m_url[225];
    fetionBuff buff;
    unsigned  long long serverId = getServerID();
    netCoreHand* netHander = m_info ->netHander;
    memset(&buff, 0, sizeof(fetionBuff));
    memset(m_url, 0, 225);
    sprintf(m_url, "http://f.10086.cn/im5/index/loadGroupContactsAjax.action?fromUrl=&t=%llu&_=%llu",  serverId , serverId + 1 );
    netGET(netHander,  m_url, &buff);
    if(buff.buffSize != 0) {
        unsigned int listNum = 0;
        int flag = 0;
        JSON_Value* root_value = NULL;
        JSON_Object *object = NULL;
        JSON_Array *array = NULL;

        root_value =  json_parse_string(buff.buff);
        if(root_value != NULL)
        {
            object = json_value_get_object(root_value);
            if(object != NULL)
            {
                listNum = json_object_get_number(object, "total");
                array = json_object_get_array(object, "contacts");
                while (array != NULL && flag < listNum)
                {
                    friendListinfo  info;
                    JSON_Object* listObject = NULL;
                    memset(&info, 0, sizeof(friendListinfo));
                    info.friendfrist = NULL;
                    info.next = NULL;
                    listObject  = json_array_get_object(array, flag);

                    strcpy_safe(info.listName,   json_object_get_string(listObject, "contactListName") );
                    info.idContactList =  json_object_get_number(listObject, "idContactList" ) ;
                    info.contactTotal = json_object_get_number(listObject, "contactTotal");
                    info.onlineContactTotal = json_object_get_number(listObject, "nlineContactTotal");

                    insertFriendList(m_info, &info);
                    flag++;
                }
            }
        }
    }

}

//-----------------------------------------------------------------------------------------
bool getFriend(userinfo* m_info)
{
    char m_url[225];
    fetionBuff buff;  //buff

    friendListinfo* baseList = m_info->friendList;

    while(baseList != NULL)
    {
        unsigned  long long serverId = getServerID();     
         
	memset(&buff, 0, sizeof(fetionBuff));    

        sprintf(m_url, "http://f.10086.cn/im5/index/contactlistView.action?fromUrl=&idContactList=%d&t=%llu&_=%llu", baseList->idContactList, serverId , serverId + 1 );
        netGET(m_info ->netHander, m_url, &buff);

        if(buff.buffSize != 0)
        {
            unsigned int listNum = 0;
            int flag = 0;
            JSON_Value* root_value = NULL;
            JSON_Object *object = NULL;
            JSON_Array *array = NULL;
	    friendListinfo* m_friendListInfo = NULL;
	    
            m_friendListInfo  = (friendListinfo*)baseList;

            root_value =  json_parse_string(buff.buff);
            if(root_value != NULL)
            {
                object = json_value_get_object(root_value);
                if(object != NULL)
                {
                    listNum = json_object_get_number(object, "total");
                    array = json_object_get_array(object, "contacts");
                    while (array != NULL && flag < listNum)
                    {
                        friendinfo info;
                        JSON_Object* listObject  = NULL;
                        memset(&info, 0, sizeof(friendinfo));
                        info.next = NULL;
                        listObject  = json_array_get_object(array, flag);
                        strcpy_safe(info.carrier,json_object_get_string(listObject, "carrier") );

                        info.idContact = json_object_get_number(listObject, "idContact");
                        info.idFetion = json_object_dotget_number(listObject, "idFetion");

                        strcpy_safe(info.mobileNo, json_object_get_string(listObject, "mobileNo"));
                        strcpy_safe(info.nickname, json_object_get_string(listObject, "nickname"));

                        insertFriend(m_friendListInfo, &info);
                        flag++;
                    }

                }
            }
        }

        baseList = baseList ->next;
    }
    return true;
}



