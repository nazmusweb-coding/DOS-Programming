#include "headers.h"

void create_db(sqlite3 *db) 
{
    char *err_msg = 0;

    const char *sql = "CREATE TABLE IF NOT EXISTS ClassRoutine ("
                    "\"Day and Time\" TEXT PRIMARY KEY, "
                    "\"8:00-9:20\" TEXT, "
                    "\"9:30-10:50\" TEXT, "
                    "\"11:00-12:50\" TEXT, "
                    "\"1:00-2:20\" TEXT, "
                    "\"2:30-3:50\" TEXT, "
                    "\"4:00-5:20\" TEXT);";

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Table created successfully\n");
    }
}

void insert_data(sqlite3 *db, const char *day_and_time, const char *slot1, const char *slot2, const char *slot3, const char *slot4, const char *slot5, const char *slot6) 
{
    char *err_msg = 0;

    const char *sql = "INSERT INTO ClassRoutine(\"Day and Time\", \"8:00-9:20\", \"9:30-10:50\", \"11:00-12:50\", \"1:00-2:20\", \"2:30-3:50\", \"4:00-5:20\") VALUES (?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, day_and_time, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, slot1, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, slot2, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, slot3, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, slot4, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, slot5, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, slot6, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        printf("Execution failed: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Record inserted successfully.\n");
    }

    sqlite3_finalize(stmt);
}

void update_data(sqlite3 *db, const char *day_and_time, const char *slot1, const char *slot2, const char *slot3, const char *slot4, const char *slot5, const char *slot6) 
{
    char *err_msg = 0;

    const char *sql = "UPDATE ClassRoutine SET \"8:00-9:20\" = ?, \"9:30-10:50\" = ?, \"11:00-12:50\" = ?, \"1:00-2:20\" = ?, \"2:30-3:50\" = ?, \"4:00-5:20\" = ? WHERE \"Day and Time\" = ?;";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, slot1, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, slot2, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, slot3, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, slot4, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, slot5, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, slot6, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, day_and_time, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        printf("Execution failed: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Record updated successfully.\n");
    }

    sqlite3_finalize(stmt);
}

void delete_data(sqlite3 *db, const char *day_and_time) 
{
    char *err_msg = 0;

    const char *sql = "DELETE FROM ClassRoutine WHERE \"Day and Time\" = ?;";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, day_and_time, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        printf("Execution failed: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Record deleted successfully.\n");
    }

    sqlite3_finalize(stmt);
}

void show_table(sqlite3 *db) 
{
    sqlite3_stmt *stmt;

    const char *sql = "SELECT \"Day and Time\", \"8:00-9:20\", \"9:30-10:50\", \"11:00-12:20\", \"1:00-2:20\", \"2:30-3:50\", \"4:00-5:20\" FROM ClassRoutine;";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) 
    {
        printf("Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("Day and Time: %s\n", sqlite3_column_text(stmt, 0));
        printf("8:00-9:20: %s\n", sqlite3_column_text(stmt, 1));
        printf("9:30-10:50: %s\n", sqlite3_column_text(stmt, 2));
        printf("11:00-12:50: %s\n", sqlite3_column_text(stmt, 3));
        printf("1:00-2:20: %s\n", sqlite3_column_text(stmt, 4));
        printf("2:30-3:50: %s\n", sqlite3_column_text(stmt, 5));
        printf("4:00-5:20: %s\n", sqlite3_column_text(stmt, 6));
        printf("\n");
    }

    sqlite3_finalize(stmt);
}

int main(int argc, char **argv)
{
    sqlite3 *db;
    char *err_msg = NULL;

    int rc = sqlite3_open("4f.db", &db);

    create_db(db);

    if (argc > 1 && strcmp(argv[1], "-s") == 0)
    {
        show_table(db);
    }

    if (argc > 1 && strcmp(argv[1], "-i") == 0)
    {
        if (argc != 9)
        {
            printf("Usage: %s -i <Day and Time> <Slot1> <Slot2> <Slot3> <Slot4> <Slot5> <Slot6> \n", argv[0]);
            sqlite3_close(db);
            return 1;
        }

        insert_data(db, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
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
        if (argc != 9)
        {
            printf("Usage: %s -u <Day and Time> <Slot1> <Slot2> <Slot3> <Slot4> <Slot5> <Slot6> \n", argv[0]);
            sqlite3_close(db);
            return 1;
        }

        update_data(db, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
    }

    sqlite3_close(db);
}