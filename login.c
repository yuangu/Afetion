#include "type.h"
#include "login.h"
#include  "netCore.h"
#include "parson.h"  // for json


//------------------------------------------------------------------------------
userinfo* login(userinfo* m_info, const char* m_id, const char* m_passwd, const char* Verify)
{
    char m_url[225];
    fetionBuff buff;
    memset(&buff, 0, sizeof(fetionBuff));
    memset(m_url, 0 , 225);
    sprintf(m_url, "m=%s&pass=%s&t=%llu&captchaCode=%s", m_id, m_passwd, getServerID(), Verify);
    netPOST(m_info ->netHander, "http://f.10086.cn/im5/login/loginHtml5.action", m_url, &buff);

    if(buff.buffSize != 0)
    {
        JSON_Value* root_value = NULL;
        JSON_Object *object = NULL;

        root_value =  json_parse_string(buff.buff);
        if(root_value != NULL)
        {
            object = json_value_get_object(root_value);
            if(object != NULL)
            {
                strcpy_safe(m_info -> headurl ,json_object_get_string(object, "headurl") );
                strcpy_safe(m_info -> nickname ,json_object_get_string(object, "nickname") );
                m_info -> loginstatus = json_object_get_number(object, "loginstatus");
                m_info -> loginstate = json_object_get_number(object, "loginstate");
                m_info -> idUser = json_object_get_number(object, "idUser");
                strcpy_safe (m_info -> sessionId , json_object_get_string(object, "sessionId") );
                m_info -> checkCodeKey =  json_object_get_boolean(object, "checkCodeKey");
                strcpy_safe(m_info -> tip ,json_object_get_string(object, "tip") );
            }
        }
      
    }
    return m_info;
}

bool getVerify(userinfo* m_info, const char* m_path)
{
    char m_url[225];
    char saverpath[225];
    char picName[40];
    unsigned  long long id;
    fetionBuff buff;

    memset(saverpath, 0, 225);
    memset(picName, 0 ,40);
    memset(m_url, 0 ,225);
    memset(&buff, 0, sizeof(fetionBuff));
    
    id = getServerID();
    sprintf(m_url,"http://f.10086.cn/im5/systemimage/verifycode%llu.jpeg?t=%llu", id, id);

    strcpy_safe(saverpath, m_path);
    sprintf(picName,"verifycode%llu.jpeg",id);

    netGET(m_info ->netHander, m_url, &buff);

    if(buff.buffSize != 0) {        
        FILE *fp = NULL;	
        if ( access( (char*)saverpath, 0 ) == -1 ) {
            fp = fopen( (char*) saverpath, "wb" );
        }
        else {
            fp = fopen( (char*) saverpath, "ab" );
        }
        
        if (fp) {
            fwrite( buff.buff, buff.buffSize, 1, fp );
	    printf("Please get the VerifyCode at path: %s \n",saverpath);
            fclose(fp);
	    return true;
        }else return false;
    } else return true;

}

