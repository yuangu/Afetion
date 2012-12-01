#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include "type.h"
netCoreHand* netInit();
bool netPOST(netCoreHand* m_hand, const char* m_url, const char* m_postData, fetionBuff* m_buff);
bool netGET(netCoreHand* m_hand, const char* m_url,  fetionBuff* m_buff);
bool netFree(netCoreHand* m_hand);
unsigned long long getServerID();
#endif // CORE_H_INCLUDED
