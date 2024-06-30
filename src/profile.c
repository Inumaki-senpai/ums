#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mariadb/mysql.h>
#include "formatting.h"

int setup_profile(MYSQL *conn, const char *role, const char *alias) {
    char *query = calloc(500, 2), *name = calloc(39, 2), *crs_or_subj = calloc(101, 2), *age = calloc(5, 2), gender[1] = {'\0'}, *contact = calloc(19, 2), *fname = calloc(39, 2), *mname = calloc(39, 2);
    fprintf(stdout, RED "Complete the profile..\n"RESET);

    fflush(stdout);
        // NAME INPUT
    fprintf(stdout, BOLD YELLOW"Full name: "RESET);
    fgets(name, 37, stdin);
    str_blank_error(conn, name);
    name[strlen(name)-1] = '\0';

    fflush(stdout);
        //  COURSE/SUBJECT INPUT
    if (role[0] != '4') {
        if (role[0] == '2')
            fprintf(stdout, BOLD YELLOW"Subjects: "RESET);
        if (role[0] == '3')
            fprintf(stdout, BOLD YELLOW"Course id: "RESET);
        fgets(crs_or_subj, 100, stdin);
        str_blank_error(conn, crs_or_subj);
        crs_or_subj[strlen(crs_or_subj)-1] = '\0';
    }

    fflush(stdout);
    fprintf(stdout, BOLD YELLOW"Age: "RESET);               //  AGE
    fgets(age, 4, stdin);
    str_blank_error(conn, age);
    age[strlen(age)-1] = '\0';

    fflush(stdout);
    fprintf(stdout, BOLD YELLOW"Gender (M/F/O): "RESET);    //  GENDER
    gender[0] = getchar();
    str_blank_error(conn, gender);
    clear_buffer();

    fflush(stdout);
    fprintf(stdout, BOLD YELLOW"Contact no: "RESET);        //  CONTACT
    fgets(contact, 15, stdin);
    str_blank_error(conn, contact);
    contact[strlen(contact)-1] = '\0';
    fflush(stdout);
    fprintf(stdout, BOLD YELLOW"Father's Name: "RESET);     //  FNAME
    fgets(fname, 26, stdin);
    str_blank_error(conn, fname);
    fname[strlen(fname)-1] = '\0';

    fflush(stdout);
    fprintf(stdout, BOLD YELLOW"Mother's Name: "RESET);     //  MNAME
    fgets(mname, 26, stdin);
    str_blank_error(conn, mname);
    mname[strlen(mname)-1] = '\0';
    fflush(stdout);

    //  INSERTING VALUES TO DATABASE
    if (role[0] == '2')
        sprintf(query, "INSERT INTO user_info(alias, name, age, gender, contact, fname, mname, subjects) VALUES('%s', '%s', '%s', '%c', '%s', '%s', '%s', '%s')", alias, name, age, gender[0], contact, fname, mname, crs_or_subj);
    if (role[0] == '3')
        sprintf(query, "INSERT INTO user_info(alias, name, age, gender, contact, fname, mname, course_id) VALUES('%s', '%s', '%s', '%c', '%s', '%s', '%s', '%s')", alias, name, age, gender[0], contact, fname, mname, crs_or_subj);
    if (role[0] == '4')
        sprintf(query, "INSERT INTO user_info(alias, name, age, gender, contact, fname, mname) VALUES('%s', '%s', '%s', '%c', '%s', '%s', '%s')", alias, name, age, gender[0], contact, fname, mname);

    if (mysql_query(conn, query))
        finish_with_error(conn);

    return 0;
}

