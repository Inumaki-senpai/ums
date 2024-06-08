#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mariadb/mysql.h>

//  MARIADB CONSTANTS;
#define SERVER "localhost"
#define USER "meow"
#define PASSWORD "MeowNagar.."
#define DATABASE "ums"

//  COLOR CODES;
#define RED "\e[31m"
#define YELLOW "\e[33m"
#define GREEN "\e[32m"
#define BOLD "\e[0;1m"
#define RESET "\e[0m"

//  MARIADB ERROR HANDLING;
void finish_with_error(MYSQL *con){
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main(int argc, char *argv[]) {
    
    //  MYSQL DB_CONNECTION(conn) INITIALIZE;
    MYSQL *conn = mysql_init(NULL);
    if(mysql_real_connect(conn, SERVER, USER, 
                            PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        finish_with_error(conn);
    }

    //  UNIVERSITY MANAGEMENT SYSTEM;
    char uname[20], pswd[30];

    fprintf(stdout, BOLD RED"  ````  University Management System  ```` " YELLOW);
    fprintf(stdout, "\n\nLogin to access management features..");
    fprintf(stdout, "\nNote: "RESET" Username should not exceed 20 characters.\n    Password should not exceed 30 characters.\n   Do not use space in username.\n");
    
    fprintf(stdout, BOLD"\nUsername: "RESET);
    fgets(uname, 20, stdin);
    sscanf(uname, " %s", uname);
    fprintf(stdout, BOLD"Password: "RESET);
    fgets(pswd, 30, stdin);

    mysql_close(conn);
    return 0;
}