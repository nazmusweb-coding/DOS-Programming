#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int callback(void *NotUsed, int argc, char **argv, char **ColName) 
{
    for (int i = 0; i < argc; i++) 
    {
        printf("%s = %s ", ColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void show_table(sqlite3 *db) 
{
    char *err_msg = 0;
    int rc = sqlite3_open("admin_credentials.db", &db);

    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *sql = "SELECT * FROM AdminCredentials;";

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

// Function to create the database and table
void create_db(sqlite3 *db) 
{
    char *err_msg = 0;

    char *sql = "CREATE TABLE IF NOT EXISTS AdminCredentials("
                "ID TEXT PRIMARY KEY AUTOINCREMENT, "
                "Passcode TEXT NOT NULL, "
                "Priority INTEGER NOT NULL);";

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) 
    {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } 
    else 
    {
        printf("Table created successfully\n");
    }
}

void insert_data(sqlite3 *db, const char *id, const char *passcode, int priority) 
{
    char *err_msg = 0;

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO AdminCredentials(ID, Passcode, Priority) VALUES(%s, '%s', %d);", id, passcode, priority);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) 
    {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } 
    else 
    {
        printf("Record inserted successfully\n");
    }
}


void delete_data(sqlite3 *db, const char *id) 
{
    char *err_msg = 0;

    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM AdminCredentials WHERE ID = %s;", id);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) 
    {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } 
    else 
    {
        printf("Record deleted successfully\n");
    }
}

void update_data(sqlite3 *db, const char *id, const char *new_passcode, int new_priority) 
{
    char *err_msg = 0;

    char sql[256];
    snprintf(sql, sizeof(sql), "UPDATE AdminCredentials SET Passcode = '%s', Priority = %d WHERE ID = %s;", 
             new_passcode, new_priority, id);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) 
    {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } 
    else 
    {
        printf("Record updated successfully\n");
    }
}


int main(int argc, char **argv)
{
    sqlite3 *db;
    char *err_msg = NULL;

    int rc = sqlite3_open("admin_credentials.db", &db);

    create_db(db);

    if (argc > 1 && strcmp(argv[1], "-s") == 0)
    {
        show_table(db);
    }

    if (argc > 1 && strcmp(argv[1], "-i") == 0)
    {
        if (argc != 5)
        {
            printf("Usage: %s -i <id> <passcode> <priority>\n", argv[0]);
            sqlite3_close(db);
            return 1;
        }

        insert_data(db, argv[2], argv[3], atoi(argv[4]));
    }

    if (argc > 1 && strcmp(argv[1], "-d") == 0)
    {
        if (argc != 3)
        {
            printf("Usage: %s -d <id>\n", argv[0]);
            sqlite3_close(db);
            return 1;
        }

        delete_data(db, argv[2]);
    }

    if (argc > 1 && strcmp(argv[1], "-u") == 0)
    {
        if (argc != 5)
        {
            printf("Usage: %s -u <id> <new_passcode> <new_priority>\n", argv[0]);
            sqlite3_close(db);
            return 1;
        }

        update_data(db, argv[2], argv[3], atoi(argv[4]));
    }

    sqlite3_close(db);
}