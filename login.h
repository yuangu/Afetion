#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

//获取验证码，并保存到相应的目录下；
bool getVerify(userinfo* m_info, const char* m_path);
userinfo* login(userinfo* m_info, const char* m_id, const char* m_passwd, const char* Verify);

#endif // LOGIN_H_INCLUDED
