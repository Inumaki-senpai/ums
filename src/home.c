
#include <stdio.h>
#include <mariadb/mysql.h>
#include "home.h"
#include "login.h"
#include "formatting.h"

int add_notice() {
    fprintf(stdout, "Headline: ");

    return 0;
}

int management(MYSQL *conn) {
    fprintf(stdout, BOLD RED"  ````  ADMINISTRATION PORTAL  ```` \n");
    fprintf(stdout, YELLOW"1. Enroll new user\n");
    fprintf(stdout, "2. Remove existing user\n");

    fprintf(stdout, BOLD"SELECT: " RESET);
    char select = getchar();
    while (getchar() != '\n'){}        //  CLEARING BUFFER
    switch (select) {
        case '1':
            if(signup(conn)) {
                finish_with_error(conn);
            }
        break;
        case '2':
            if (del_user(conn)) {
                finish_with_error(conn);
            }
        break;
        default:
            fprintf(stdout, RED"\nInvalid selection!\n"RESET);
            finish_with_error(conn);
    }

    return 0;
}

int teacher(MYSQL *conn) {
    char select = '\0';

    fprintf(stdout, BOLD RED " ``` TEACHER'S PORTAL ```\n");
    fprintf(stdout, YELLOW"1. Add Notice\n");
    fprintf(stdout, "2. Check schedule\n");
    fprintf(stdout, "3. Assignment record\n");
    fprintf(stdout, "4. Retrieve student record\n");
    fprintf(stdout, "5. Report an incident or issue\n");

    fprintf(stdout, BOLD"Select: "RESET);
    select = getchar();
    while (getchar() != 10){}        //  CLEARING BUFFER
    switch (select) {
        case '1':
            fprintf(stdout, "Add Notice..\n");
        break;
        case '2':
            fprintf(stdout, "Check Schedule..\n");
        break;
        case '3':
            fprintf(stdout, "Assignment Record..\n");
        break;
        case '4':
            fprintf(stdout, "Retrieve Student Record..\n");
        break;
        case '5':
            fprintf(stdout, "Report an incident or issue..\n");
        break;
        default:
            fprintf(stdout, RED"Invalid selection!"RESET);
        return 1;
    }

    return  0;
}

int staff(MYSQL *conn) {
    fprintf(stdout, "I am staff");
    return 0;
}

int student(MYSQL *conn) {
    fprintf(stdout, "I am student");
    return 0;
}
