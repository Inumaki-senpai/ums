
#ifndef LOGIN_H
#define LOGIN_H

int login(MYSQL *conn, const char *alias, const char *ukey);
int signup(MYSQL *conn);
int del_user(MYSQL *conn);
int add_course(MYSQL *conn);
int remove_course(MYSQL *conn);

#endif //LOGIN_H
