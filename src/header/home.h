
#ifndef HOME_H
#define HOME_H

int unenroll_user(MYSQL *conn);

int management(MYSQL *conn);
int teacher(MYSQL *conn);
int staff(MYSQL *conn);
int student(MYSQL *conn);

#endif //HOME_H
