#ifndef TYPE_INCLUDED
#define TYPE_INCLUDED
#include <curl/curl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

#define strcpy_safe(src, dec)   (src!=NULL &&dec != NULL) ? strcpy(src,dec):NULL

typedef struct netHand{
    CURL* m_curl;
    CURLSH *pShared;

    bool stat;

} netCoreHand;

typedef struct friendinfo{
    struct frinedinfo* next;
    unsigned int idContact;
    char nickname[30];
    unsigned int idFetion;
    char mobileNo[11];
    char carrier[8];
} friendinfo;

typedef struct friendListinfo
{
    struct friendListinfo* next;
    unsigned int idContactList;
    char listName[30];
    unsigned int onlineContactTotal;
    unsigned int contactTotal;
    friendinfo *friendfrist;
} friendListinfo;

typedef struct {
    char headurl[255];
    char nickname[30];
    int loginstatus;
    int loginstate;
    char tip[30];
    int idUser;
    int queryMsgId;
    char sessionId[50];
    bool checkCodeKey;
    friendListinfo* friendList;
    netCoreHand* netHander;
} userinfo;
typedef struct {
    int  buffSize;
    char buff[10240];
}fetionBuff;



#endif // TYPE_INCLUDED
