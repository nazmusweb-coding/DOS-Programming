#include "headers.h"

const char *admin_db = "admin_credentials.db";
const char *faculty_db = "faculty_credentials.db";

int login(const char *credential_db, const char *id, const char *passcode) 
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open(credential_db, &db);

    if (rc != SQLITE_OK) 
    {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return -1;  // Return -1 for failure
    }

    const char *sql = "SELECT Priority FROM AdminCredentials WHERE ID = ? AND Passcode = ?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) 
    {
        printf("Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, id, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, passcode, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) 
    {
        int priority = sqlite3_column_int(stmt, 0);
        printf("Login successful! Priority: %d\n", priority);
        // You can use the priority value here to determine access
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return priority;
    } 
    else 
    {
        printf("Invalid ID or passcode.\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
    }
}

char *login_faculty(const char *credential_db, const char *id, const char *passcode) 
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open(credential_db, &db);

    if (rc != SQLITE_OK) 
    {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return -1;  // Return -1 for failure
    }

    const char *sql = "SELECT Priority FROM AdminCredentials WHERE ID = ? AND Passcode = ?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) 
    {
        printf("Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, id, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, passcode, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) 
    {
        // work here
        printf("Login successful! Priority: %s\n", id);
        // You can use the priority value here to determine access
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return id;
    } 
    else 
    {
        printf("Invalid ID or passcode.\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }
}

// page 7 8 9 10 11

// int main(int argc, char **argv)
// {
//     // Returns priority 1 and 2
//     if (login(admin_db, argv[1], argv[2]) == 1)
//     {

//     }
//     else if (login(admin_db, argv[1], argv[2]) == 2)
//     {

//     }
//     else
//     {

//     }

//     // Returns 1 if done 
//     if (login(faculty_db, argv[1], argv[2]) == 1)
//     {

//     }
//     else
//     {

//     }

//     return 0;
// }