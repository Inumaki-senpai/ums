#include <stdio.h>
#include <stdlib.h>
#include <mariadb/mysql.h>
#include "formatting.h"
#include "admin.h"
#include "home.h"

int admin(MYSQL *conn) {
    fprintf(stdout, BOLD RED" ```` ADMIN PORTAL ```` \n");
    fprintf(stdout, YELLOW"1. Show Reports\n");
    fprintf(stdout, "2. Scoring Record\n");
    fprintf(stdout, "3. Library Record\n");
    fprintf(stdout, "4. Attendance Record\n");
    fprintf(stdout, "5. Add New Department\n");
    fprintf(stdout, "6. Remove a Department\n");
    fprintf(stdout, "7. Administration Portal\n");
    fprintf(stdout, "8. Exit\n");

    fprintf(stdout, BOLD"Select: "RESET);
    const char choice = getchar();
    clear_buffer();

    switch (choice) {
        case '1':
            fprintf(stdout, "Show Reports\n");
        break;
        case '2':
            fprintf(stdout, "Scoring Records\n");
        break;
        case '3':
            fprintf(stdout, "Library Records\n");
        break;
        case '4':
            fprintf(stdout, "Attendance Records\n");
        break;
        case '5':
            fprintf(stdout, "Add New Department\n");
        break;
        case '6':
            fprintf(stdout, "Remove Existing Department\n");
        break;
        case '7':
            while (administration(conn, 7) != 2) {}
        break;
        case '8':
            mysql_close(conn);
            exit(0);
        default:
            fprintf(stdout, RED"Invalid Selection!\n"RESET);
        return 1;
    }

    return 0;
}
