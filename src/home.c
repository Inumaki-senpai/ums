#include <stdio.h>
#include <stdlib.h>
#include <mariadb/mysql.h>
#include "formatting.h"
#include "library.h"
#include "login.h"
#include "home.h"

int administration(MYSQL *conn, int role) {
    fprintf(stdout, BOLD RED"  ```  ADMINISTRATION PORTAL  ``` \n");
    fprintf(stdout, YELLOW"1. Enroll a New User\n");
    fprintf(stdout, "2. Remove Existing User\n");
    fprintf(stdout, "3. Enroll a New Course\n");
    fprintf(stdout, "4. Remove Existing Course\n");
    if (role == 7)
        fprintf(stdout, "5. Return to Admin Portal\n");
    else
        fprintf(stdout, "5. Exit\n");

    fprintf(stdout, BOLD"SELECT: " RESET);
    const char choice = getchar();
    clear_buffer();
    switch (choice) {
        case '1':
            if(signup(conn))
                finish_with_error(conn);
        break;
        case '2':
            if (del_user(conn)) {
                finish_with_error(conn);
            }
        break;
        case '3':
            fprintf(stdout, "New Course\n");
        break;
        case '4':
            fprintf(stdout, "Remove Course\n");
        break;
        case '5':
            if (role == 7)
                return 2;
        mysql_close(conn);
        exit(0);
        default:
            fprintf(stdout, RED"\nInvalid selection!\n"RESET);
            return 1;
    }

    return 0;
}

int teacher(MYSQL *conn) {

    fprintf(stdout, BOLD RED " ``` TEACHER PORTAL ``` \n");
    fprintf(stdout, YELLOW"1. Retrieve Assignment\n");
    fprintf(stdout, "2. Report or Complain\n");
    fprintf(stdout, "3. Retrieve Student Record\n");
    fprintf(stdout, "4. Exit\n");

    fprintf(stdout, BOLD"Select: "RESET);
    const char choice = getchar();
    clear_buffer();
    switch (choice) {
        case '1':
            fprintf(stdout, "Retrieve Assignment..\n");
        break;
        case '2':
            fprintf(stdout, "Report or Complain..\n");
        break;
        case '3':
            fprintf(stdout, "Retrieve Student Record..\n");
        break;
        case '4':
            mysql_close(conn);
        exit(0);
        default:
            fprintf(stdout, RED"Invalid selection!"RESET);
        return 1;
    }

    return  0;
}

int student(MYSQL *conn) {
    fprintf(stdout, BOLD RED" ``` Student Portal ``` \n");
    fprintf(stdout, YELLOW"1. Submit Assignment\n");
    fprintf(stdout, "2. Report or Complain\n");
    fprintf(stdout, "3. Exit\n");
    fprintf(stdout, BOLD"Select: "RESET);

    const char choice = getchar();
    clear_buffer();
    switch (choice) {
        case '1':
            fprintf(stdout, "Submit Assignment..\n");
        break;
        case '2':
            fprintf(stdout, "Report or Complain..\n");
        break;
        case '3':
            mysql_close(conn);
        exit(0);
        default:
            fprintf(stdout, RED"Invalid selection!"RESET);
        return 1;
    }

    return 0;
}

int library(MYSQL *conn) {
    fprintf(stdout, BOLD RED" ``` Librarian Portal ``` \n");
    fprintf(stdout, YELLOW"1. Issue a Book\n");
    fprintf(stdout, "2. Return a Book\n");
    fprintf(stdout, "3. Retrieve Book Info\n");
    fprintf(stdout, "4. Add a Book to Collection\n");
    fprintf(stdout, "5. Remove a Book from Collection\n");
    fprintf(stdout, "6. Exit\n");

    fprintf(stdout, BOLD"Select: "RESET);
    const char choice = getchar();
    clear_buffer();
    switch (choice) {
        case '1':
            if (issue_book(conn))
                finish_with_error(conn);
        break;
        case '2':
            if (return_book(conn))
                finish_with_error(conn);
        break;
        case '3':
            if (retrieve_book_info(conn))
                finish_with_error(conn);
        break;
        case '4':
            if (add_book(conn))
                finish_with_error(conn);
        break;
        case '5':
            if (remove_book(conn))
                finish_with_error(conn);
        break;
        case '6':
            mysql_close(conn);
        exit(0);
        default:
            fprintf(stdout, RED"Invalid selection!"RESET);
        return 1;
    }

    return 0;
}
