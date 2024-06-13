
#include <stdio.h>
#include <mariadb/mysql.h>
#include "formatting.h"
#include "admin.h"

int admin(MYSQL *conn) {

    fprintf(stdout, "I am admin\n");

    return 0;
}
