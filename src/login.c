
#include <stdio.h>
#include <string.h>
#include <mariadb/mysql.h>
#include "login.h"
#include "hashing.h"
#include "formatting.h"

int login(MYSQL *conn, char *alias,char *ukey) {
    if(alias[0] == 10) {
        fprintf(stderr, BOLD RED"Username cannot be empty!\n" RESET);
        return 1;
    }
    if (ukey[0] == '\0') {
        fprintf(stderr, BOLD RED"Password cannot be empty!\n" RESET);
        return 1;
    }

    char query[100] = {'\0'};
    sprintf(query, "SELECT 1 FROM user WHERE alias = '%lu' and ukey = '%lu'", hash(alias), hash(ukey));
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
    char name[27] = {'\0'}, alias[27] = {'\0'}, ukey[32] = {'\0'}, query[100] = {'\0'};

    //  NAME INPUT
    fprintf(stdout, BOLD"Full Name: "RESET);
    fgets(name, 26, stdin);
    if (name[0] == 10) {
        fprintf(stderr, BOLD RED"Error: Name can't be left blank..\n"RESET);
        return 1;
    }

    //  ENROLLMENT_ID INPUT
    fprintf(stdout, BOLD"Enrollment id: "RESET);
    const char role = getchar();
    while (getchar() != 10) {}      //  CLEARING BUFFER

    //  ALIAS INPUT
    fprintf(stdout, BOLD"Alias: "RESET);
    fgets(alias, 26, stdin);
    if (alias[0] == 10) {
        fprintf(stderr, BOLD RED"Error: alias can't be left blank! \nIt is used for logging in to account..\n"RESET);
        return 1;
    } sscanf(alias, " %s", alias);

    //  PASSWORD INPUT
    fprintf(stdout, BOLD"User Password: "RESET);
    fgets(ukey, 31, stdin);
    if (ukey[0] == 10) {
        fprintf(stderr, BOLD RED"Error: Password can't be left blank..\n"RESET);
        return 1;
    }

    //  REMOVING NEWLINE '\n' FROM NAME AND PASSWORD
    name[strlen(name)-1] = '\0';
    ukey[strlen(ukey)-1] = '\0';

    //  INSERTING DATA INTO THE DATABASE;
    sprintf(query, "INSERT INTO user(alias,name,role_id,ukey) VALUES(%lu,'%s',%c,%lu)", hash(alias), name, role, hash(ukey));
    if (mysql_query(conn, query)) {
        return 1;
    }

    fprintf(stdout, BOLD RED"NOTE: Store password at a secure place.\n"RESET);
    fprintf(stdout, BOLD GREEN"Alias: "RESET"%s \n"RESET, alias);
    fprintf(stdout, BOLD GREEN"Pass: "RESET"%s \n"RESET, ukey);

    return 0;
}

int del_user(MYSQL *conn) {
    char alias[27] = {'\0'}, query[100] = {'\0'};

    //  ALIAS INPUT
    fprintf(stdout, BOLD"Alias: "RESET);
    fgets(alias, 26, stdin);
    if (alias[0] == 10) {
        fprintf(stderr, BOLD RED"Error: no input for alias!!\n"RESET);
        return 1;
    } sscanf(alias, " %s", alias);

    //  ENROLLMENT_ID INPUT
    fprintf(stdout, BOLD"Enrollment id: "RESET);
    char role;
    if((role = getchar()) == 10) {
        fprintf(stderr, "Error: no input for enrollment_id!!");
        return 1;
    }
    while (getchar() != 10) {}      //  CLEARING BUFFER

    //  REMOVING DATA FROM THE DATABASE;
    sprintf(query, "DELETE FROM user WHERE alias='%lu' AND role_id='%c'", hash(alias), role);
    if (mysql_query(conn, query)) {
        return 1;
    } else {
        if (mysql_affected_rows(conn) == 0) {
            fprintf(stderr, "No such user was found..\n");
            return 1;
        }
        fprintf(stdout, RED"User '%s' no longer exists.\n", alias);
    }

    return 0;
}
