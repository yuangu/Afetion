#include <stdio.h>
#include <stdlib.h>

#include "libfetion.h"
int main()
{
    char Verify[4];
    char Account[20];
    char passwd[20];
    userinfo* info = fetionInit();

    printf("Account:");
    gets(Account);
    printf("Passwd:");
    gets(passwd);
    getVerify(info,"./");
    printf("Verify:");
    gets(Verify);

    login(info, Account, passwd, Verify);

    getFriendList(info);
    getFriend(info);
    toChat(info);


    sendMsgBymobileNo(info, "10086",  "zhai gan sha!");

    return 0;
}
