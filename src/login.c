#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mariadb/mysql.h>
#include "formatting.h"
#include "hashing.h"
#include "profile.h"
#include "login.h"

#include <stdlib.h>

int login(MYSQL *conn, const char *alias, const char *ukey) {
    char query[100] = {'\0'};
    sprintf(query, "SELECT 1 FROM account WHERE alias = '%lu' and ukey = '%lu'", hash(alias), hash(ukey));
    if(mysql_query(conn, query))
        return 1;

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL)
        return 1;

    const MYSQL_ROW row = mysql_fetch_row(result);
    mysql_free_result(result);
    if (row == NULL) {
        fprintf(stdout, BOLD RED"Error: User not found!"RESET);
        return 1;
    }
    return 0;
}

int signup(MYSQL *conn) {
    char role[1] = {'\0'}, alias[27] = {'\0'}, ukey[32] = {'\0'}, query[100] = {'\0'};

    //  ENROLLMENT_ID INPUT
    fprintf(stdout, BOLD"Enrollment id: "RESET);
    role[0] = getchar();
    clear_buffer();
    str_blank_error(conn, role);
    if (role[0] == '7') {
        fprintf(stderr, BOLD RED"Invalid enrollment id\n"RESET);
        return 1;
    }

    //  ALIAS INPUT
    fprintf(stdout, BOLD"Alias: "RESET);
    fgets(alias, 26, stdin);
    str_blank_error(conn, alias);
    sscanf(alias, " %s", alias);

    //  PASSWORD INPUT
    fprintf(stdout, BOLD"Account Password: "RESET);
    fgets(ukey, 31, stdin);
    str_blank_error(conn, ukey);
    ukey[strlen(ukey)-1] = '\0';

    if (setup_profile(conn, role, alias))
        return 1;

    //  INSERTING DATA INTO THE DATABASE;
    sprintf(query, "INSERT INTO account(alias,role_id,ukey) VALUES(%lu,%c,%lu)", hash(alias), role[0], hash(ukey));
    if (mysql_query(conn, query)) {
        return 1;
    }

    fprintf(stdout, BOLD RED"NOTE: Store password at a secure place.\n"RESET);
    fprintf(stdout, BOLD GREEN"Alias: "RESET"%s \n"RESET, alias);
    fprintf(stdout, BOLD GREEN"Pass: "RESET"%s \n"RESET, ukey);

    return 0;
}

int del_user(MYSQL *conn) {
    char role[1] = {'\0'}, alias[27] = {'\0'}, query[100] = {'\0'};

    //  ALIAS INPUT
    fprintf(stdout, BOLD"Alias: "RESET);
    fgets(alias, 26, stdin);
    str_blank_error(conn, alias);
    sscanf(alias, " %s", alias);

    //  ENROLLMENT_ID INPUT
    fprintf(stdout, BOLD"Enrollment id: "RESET);
    role[0] = getchar();
    clear_buffer();
    str_blank_error(conn, role);
    if (role[0] == '7') {
        fprintf(stderr, BOLD RED"Invalid enrollment id\n"RESET);
        return 1;
    }

    //  REMOVING DATA FROM THE DATABASE;
    sprintf(query, "DELETE FROM account WHERE alias='%lu' AND role_id='%c'", hash(alias), role[0]);
    if (mysql_query(conn, query)) {
        return 1;
    }
    sprintf(query, "DELETE FROM user_info WHERE alias='%s'", alias);
    if (mysql_query(conn, query)) {
        return 1;
    }
    if (mysql_affected_rows(conn) == 0)
        fprintf(stderr, "No such account was found..\n");
    else
        fprintf(stdout, RED"Account '%s' no longer exists.\n", alias);

    return 0;
}

int add_course(MYSQL *conn) {
    int department_name;
    char *course_name = calloc(100, 2), *subjects = calloc(100, 2);

    fflush(stdout);
    fprintf(stdout, "Course Name: ");
    fgets(course_name, 99, stdin);

    return 0;
}

int remove_course(MYSQL *conn) {
    return 0;
}
