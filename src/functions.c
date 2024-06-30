#include <stdio.h>
#include <stdlib.h>
#include <mariadb/mysql.h>
#include "formatting.h"

void finish_with_error(MYSQL *conn) {
    fprintf(stderr, BOLD RED"%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

void clear_buffer() {
    while (getchar() != '\n') {}
}

void str_blank_error(MYSQL *conn, const char *field) {
    if(field[0] == 10) {
        fprintf(stderr, RED"Error: This field cannot be left blank!!\n"RESET);
        finish_with_error(conn);
    }
}
