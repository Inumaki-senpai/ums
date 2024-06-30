#ifndef LIBRARY_H
#define LIBRARY_H

int  issue_book(MYSQL *conn);
int return_book(MYSQL *conn);
int retrieve_book_info(MYSQL *conn);
int add_book(MYSQL *conn);
int remove_book(MYSQL *conn);

#endif //LIBRARY_H
