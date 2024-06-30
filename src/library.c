#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mariadb/mysql.h>
#include "formatting.h"
#include "library.h"

int issue_book(MYSQL *conn) {
    char *title = calloc(101, 2), *author = calloc(31, 2), *alias = calloc(31, 2), *query = calloc(250, 2);

    fprintf(stdout, BOLD GREEN"``` Issue a Book ```\n"RESET);
    fprintf(stdout, YELLOW"Book Title: "RESET);
    fgets(title, 100, stdin);
    str_blank_error(conn, title);
    title[strlen(title)-1] = '\0';
    fprintf(stdout, YELLOW"Author: "RESET);
    fgets(author, 30, stdin);
    str_blank_error(conn, author);
    author[strlen(author)-1] = '\0';
    fprintf(stdout, YELLOW"Issuer alias: "RESET);
    fgets(alias, 30, stdin);
    str_blank_error(conn, alias);
    alias[strlen(alias)-1] = '\0';

    sprintf(query, "SELECT 1 FROM library WHERE title='%s' AND author='%s'", title, author);
    if (mysql_query(conn, query))
        return 1;
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL)
        return 1;
    const MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL)
        return 1;
    mysql_free_result(result);

    if (atoi(row[0]) != 1) {
        fprintf(stdout, "The book is currently issued by someone..\n");
        fprintf(stderr, "Cannot issue this book!!\n");
        return 0;
    }

    sprintf(query, "UPDATE library SET availability='NO' WHERE title='%s' AND author='%s'", title, author);
    if (mysql_query(conn, query))
        return 1;
    sprintf(query, "INSERT INTO library_record(book_title, book_author, issuer_alias) VALUES('%s','%s','%s')", title, author, alias);
    if (mysql_query(conn, query))
        return 1;

    fprintf(stdout, GREEN"Book issued..\n"RESET);

    return 0;
}

int return_book(MYSQL *conn) {
    char *title = calloc(101, 2), *author = calloc(31, 2), *alias = calloc(31, 2), *query = calloc(250, 2);

    fprintf(stdout, BOLD GREEN"``` Return a Book ```\n"RESET);
    fprintf(stdout, YELLOW"Book Title: "RESET);
    fgets(title, 100, stdin);
    str_blank_error(conn, title);
    title[strlen(title)-1] = '\0';
    fprintf(stdout, YELLOW"Author: "RESET);
    fgets(author, 30, stdin);
    str_blank_error(conn, author);
    author[strlen(author)-1] = '\0';
    fprintf(stdout, YELLOW"Issuer alias: "RESET);
    fgets(alias, 30, stdin);
    str_blank_error(conn, alias);
    alias[strlen(alias)-1] = '\0';

    sprintf(query, "SELECT 1 FROM library WHERE title='%s'AND author='%s' AND availability='NO'", title, author);
    if (mysql_query(conn, query))
        return 1;
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL)
        return 1;
    const MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL)
        return 1;
    mysql_free_result(result);

    if (atoi(row[0]) != 1) {
        fprintf(stdout, "The book is currently not issued by anyone..\n");
        fprintf(stderr, "Cannot return this book!!\n");
        return 0;
    }

    sprintf(query, "UPDATE library_record SET date_of_return=now() WHERE book_title='%s' AND book_author='%s' AND issuer_alias='%s'", title, author, alias);
    if (mysql_query(conn, query))
        return 1;
    sprintf(query, "UPDATE library SET availability='YES' WHERE title='%s' AND author='%s'", title, author);
    if (mysql_query(conn, query))
        return 1;

    fprintf(stdout, GREEN"Book returned..\n"RESET);

    return 0;
}

int retrieve_book_info(MYSQL *conn) {
    char *title = calloc(101, 2), *author = calloc(31, 2), *query = calloc(200, 2);

    fprintf(stdout, BOLD GREEN"``` Retrieve Book Info ```\n"RESET);
    fprintf(stdout, YELLOW"Book Title: "RESET);
    fgets(title, 100, stdin);
    str_blank_error(conn, title);
    title[strlen(title)-1] = '\0';
    fprintf(stdout, YELLOW"Author: "RESET);
    fgets(author, 30, stdin);
    str_blank_error(conn, author);
    author[strlen(author)-1] = '\0';

    sprintf(query, "SELECT * FROM library WHERE title='%s' AND author='%s'", title, author);
    if (mysql_query(conn, query))
        return 1;

    //  PRINT RESULT
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL)
        return 1;
    MYSQL_ROW row;

    const unsigned int num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
    {
        const unsigned long *lengths = mysql_fetch_lengths(result);
        for(unsigned int i = 0; i < num_fields; i++)
        {
            printf("[%.*s] ", (int) lengths[i],
                   row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(result);

    return 0;
}

int add_book(MYSQL *conn) {
    char *title = calloc(101, 2), *author = calloc(31, 2), *genre = calloc(31, 2), *query = calloc(250, 2);

    fprintf(stdout, BOLD GREEN"``` Add a Book to Collection ```\n"RESET);
    fprintf(stdout, YELLOW"Title: "RESET);
    fgets(title, 100, stdin);
    str_blank_error(conn, title);
    title[strlen(title)-1] = '\0';
    fprintf(stdout, YELLOW"Author: "RESET);
    fgets(author, 30, stdin);
    str_blank_error(conn, author);
    author[strlen(author)-1] = '\0';
    fprintf(stdout, YELLOW"Genre: "RESET);
    fgets(genre, 30, stdin);
    str_blank_error(conn, genre);
    genre[strlen(genre)-1] = '\0';

    sprintf(query, "INSERT INTO library(title, author, genre) VALUES('%s', '%s', '%s')", title, author, genre);

    if (mysql_query(conn, query))
        return 1;
    fprintf(stdout, GREEN"Book successfully added..\n"RESET);

    return 0;
}

int remove_book(MYSQL *conn) {
    char *title = calloc(101, 2), *author = calloc(31, 2), *query = calloc(200, 2);

    fprintf(stdout, BOLD GREEN"``` Remove a Book from Collection```\n"RESET);
    fprintf(stdout, YELLOW"Book Title: "RESET);
    fgets(title, 100, stdin);
    str_blank_error(conn, title);
    title[strlen(title)-1] = '\0';
    fprintf(stdout, YELLOW"Author: "RESET);
    fgets(author, 30, stdin);
    str_blank_error(conn, author);
    author[strlen(author)-1] = '\0';

    sprintf(query, "SELECT 1 FROM library WHERE title='%s' AND author='%s'", title, author);
    if (mysql_query(conn, query))
        return 1;
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL)
        return 1;
    const MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL)
        return 1;
    mysql_free_result(result);

    if (atoi(row[0]) != 1) {
        fprintf(stdout, "The book is currently issued by someone..\n");
        fprintf(stdout, "Do you still want to remove from collection? (Y/N): ");
        if (getchar() == 'N') {
            clear_buffer();
            return 0;
        }
    } sprintf(query, "DELETE FROM library WHERE title='%s' AND author='%s'", title, author);

    if (mysql_query(conn, query))
        return 1;
    fprintf(stdout, GREEN"Book successfully removed..\n"RESET);

    return 0;
}
