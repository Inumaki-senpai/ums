
#ifndef LOGIN_H
#define LOGIN_H

int login(MYSQL *conn, char *uid, char *pswd);
int signup(MYSQL *conn);
int del_user(MYSQL *conn);

#endif //LOGIN_H
