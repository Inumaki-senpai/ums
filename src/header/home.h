
#ifndef HOME_H
#define HOME_H

int unenroll_user(MYSQL *conn);

int administration(MYSQL *conn, int role);
int teacher(MYSQL *conn);
int student(MYSQL *conn);
int library(MYSQL *conn);

#endif //HOME_H
