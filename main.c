#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mariadb/mysql.h>
#include "formatting.h"
#include "hashing.h"
#include "login.h"
#include "admin.h"
#include "home.h"

//  DATABASE CONNECTION CONSTANTS;
#define SERVER "localhost"
#define USER "meow"
#define PASSWORD "MeowNagar.."
#define DATABASE "ums"

//  MAIN FUNCTION;
void main(void) {
    //  MYSQL DATABASE CONNECTION (conn);
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "constmysql_init() failed!\n");
    }
    if (mysql_real_connect(conn, SERVER, USER, PASSWORD,
                            DATABASE, 0, NULL, 0) == NULL) {
        finish_with_error(conn);
    }

    //  UNIVERSITY MANAGEMENT SYSTEM;
    char alias[27] = {'\0'}, ukey[32] = {'\0'}, query[100] = {'\0'};

    fprintf(stdout, BOLD RED"  ````  University Management System  ```` " YELLOW);
    fprintf(stdout, "\n\nLogin to access management features..");
    fprintf(stdout, "\nNote: "RESET" Alias should not exceed 20 characters.\n    Password should not exceed 30 characters.\n   Do not use space in alias.\n");

    fprintf(stdout, BOLD"\nAlias: "RESET);
    fgets(alias, 26, stdin);
    sscanf(alias, " %s", alias);
    fprintf(stdout, BOLD"Password: "RESET);
    fgets(ukey, 31, stdin);
    ukey[strlen(ukey)-1] = '\0';

    if(login(conn, alias, ukey))
        finish_with_error(conn);

    fprintf(stdout, BOLD GREEN"Logged in successfully as %s..\n"RESET, alias);
    //  ADVANCE TO NEXT PAGE AS PER THE ROLE OF USER..
    sprintf(query, "SELECT role_id FROM user WHERE alias = '%lu'", hash(alias));
    if (mysql_query(conn, query))
        finish_with_error(conn);

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL)
        finish_with_error(conn);

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL)
        finish_with_error(conn);

    mysql_free_result(result);
    switch (atoi(row[0])) {
        case 7:
            if(admin(conn))
                finish_with_error(conn);
        break;
        case 1:
            if(management(conn))
                finish_with_error(conn);
        break;
        case 2:
            if(teacher(conn))
                finish_with_error(conn);
        break;
        case 3:
            if(staff(conn))
                finish_with_error(conn);
        break;
        case 4:
            if(student(conn))
                finish_with_error(conn);
        break;
        default:
            fprintf(stdout, RED"UNKNOWN ROLE_ID!\nTHIS ACCOUNT HAS BEEN CEASED TO EXIST..\n"RESET);
            finish_with_error(conn);
    }

    mysql_close(conn);
    exit(0);
}
