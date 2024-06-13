#include  <stdio.h>
#include <stdlib.h>
#include <mariadb/mysql.h>
#include "formatting.h"

// SQL ERROR HANDLING;
void finish_with_error(MYSQL *con) {
    fprintf(stderr, BOLD RED"%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}
