#include "netCore.h"
#include "time.h"
//--------------------------------------------------------------------------------------------------

netCoreHand* netInit()
{

    struct curl_slist *headers = NULL;
    netCoreHand* m_hand = NULL;

    m_hand = malloc(sizeof(netCoreHand));


    curl_global_init(CURL_GLOBAL_ALL);
    m_hand-> m_curl = curl_easy_init();
    m_hand-> pShared = curl_share_init( );   ///创建一个share_handle
    //开启cookie系统;
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_COOKIEFILE, "");
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_COOKIELIST, "ALL");
    curl_share_setopt(m_hand-> pShared, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_SHARE, m_hand-> pShared);

    headers = curl_slist_append(headers,"Connection: keep-alive");
    curl_easy_setopt(m_hand-> m_curl,CURLOPT_HTTPHEADER , headers );

    return m_hand;
}

//--------------------------------------------------------------------------------------------------

static size_t handFunc( void *ptr, size_t size, size_t nmemb, void *stream )
{
    fetionBuff* buff = stream;
    int len = size * nmemb;
    memcpy(buff->buff+ buff->buffSize, ptr, len);
    buff->buffSize += len;
    return len;
}
//-------------------------------------------------------------------------------------------------
bool netPOST(netCoreHand* m_hand, const char* m_url, const char* m_postData, fetionBuff* m_buff)
{
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_HTTPGET ,false);
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_POST, true);
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_POSTFIELDS, m_postData);
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_URL, m_url);
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_WRITEDATA, (void*)m_buff);
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_WRITEFUNCTION,handFunc);

    return curl_easy_perform(m_hand-> m_curl);
}

//--------------------------------------------------------------------------------------------------

bool netGET(netCoreHand* m_hand, const char* m_url,  fetionBuff* m_buff)
{
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_POST, false);
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_HTTPGET ,true);
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_URL,m_url);
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_WRITEDATA, (void*)m_buff);
    curl_easy_setopt(m_hand-> m_curl, CURLOPT_WRITEFUNCTION,handFunc);

    return curl_easy_perform(m_hand-> m_curl);
}

//--------------------------------------------------------------------------------------------------

bool netFree(netCoreHand* m_hand)
{
    if(m_hand-> m_curl != NULL)
    {
        curl_easy_cleanup(m_hand-> m_curl);
        curl_global_cleanup();
    }
    if(m_hand != NULL)
    {
        free(m_hand);
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
unsigned long long getServerID()
{

    int randNum;
    unsigned long long id;
    static int flag = 0;
    static unsigned long long server[6] = { 1352738025993LL,1352739124859LL, 1352737715357LL, 1352738043561LL, 1352738047682LL, 1352741975041LL};
    do
    {
        randNum = rand()%6;
    }
    while(randNum == flag) ;

    flag = randNum;
    id =   (unsigned long long)*(server + flag);
    return id;
}

//--------------------------------------------------------------------------------------------------
