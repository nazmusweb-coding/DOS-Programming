#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prints data  
int callback(void *NotUsed, int argc, char **argv, char **ColName)
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", ColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

// Insert function to enter new data in database through the arguments
int insert_data(sqlite3 *db, char *department, double credit_fee, double semester_fee, double other_fees, double admission_fee, int total_credit, int total_credit_below, int duration, int semester, int semester_below)
{
    char *err_msg = NULL;
    char sql[512];

    sprintf(sql, "INSERT INTO D_CostingChart(Department, CreditFee, SemesterFee, OtherFees, AdmissionFee, TotalCredit, TotalCreditBelow, Duration, Semester, SemesterBelow) VALUES('%s', %.2f, %.2f, %.2f, %.2f, %d, %d, %d, %d, %d);",
            department, credit_fee, semester_fee, other_fees, admission_fee, total_credit, total_credit_below, duration, semester, semester_below);

    // Execute an sql statement in the database (to be simple here it inserts) 
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    return 0;
}

// Shows the whole table
int show_table(sqlite3 *db)
{
    char *err_msg = NULL;
    char *sql = "SELECT * FROM D_CostingChart;";

    // Execute an sql statement in the database (to be simple here it prints) 
    int rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    return 0;
}

// Delete function to Delete any data in database through the argument
int delete_data(sqlite3 *db, char *department)
{
    char *err_msg = NULL;
    char sql[256];

    sprintf(sql, "DELETE FROM D_CostingChart WHERE Department='%s';", department);

    // Execute an sql statement in the database (to be simple here it deletes)
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    return 0;
}

// Update function to modify data in database through the arguments
int update_data(sqlite3 *db, char *department, double credit_fee, double semester_fee, double other_fees, double admission_fee, int total_credit, int total_credit_below, int duration, int semester, int semester_below)
{
    char *err_msg = NULL;
    char sql[512];

    sprintf(sql, "UPDATE D_CostingChart SET CreditFee=%.2f, SemesterFee=%.2f, OtherFees=%.2f, AdmissionFee=%.2f, TotalCredit=%d, TotalCreditBelow=%d, Duration=%d, Semester=%d, SemesterBelow=%d WHERE Department='%s';",
            credit_fee, semester_fee, other_fees, admission_fee, total_credit, total_credit_below, duration, semester, semester_below, department);

    // Execute an sql statement in the database (to be simple here it updates) 
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    return 0;
}

// Total cost calculation function that was initially practiced here before implementing in test.c
int calculate_total_cost(sqlite3 *db, char *department)
{
    char sql[256];
    sqlite3_stmt *stmt;

    sprintf(sql, "SELECT CreditFee, SemesterFee, OtherFees, AdmissionFee, TotalCredit, TotalCreditBelow, Semester, SemesterBelow FROM D_CostingChart WHERE Department='%s';", department);

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        double credit_fee = sqlite3_column_double(stmt, 0);
        double semester_fee = sqlite3_column_double(stmt, 1);
        double other_fees = sqlite3_column_double(stmt, 2);
        double admission_fee = sqlite3_column_double(stmt, 3);
        int total_credit = sqlite3_column_int(stmt, 4);
        int semester = sqlite3_column_int(stmt, 6);

        double total_cost = (credit_fee * total_credit) + (semester_fee * semester) + admission_fee + other_fees;
        printf("Total cost for %s: %.2f\n", department, total_cost);
    }
    else
    {
        printf("Department not found.\n");
    }

    sqlite3_finalize(stmt);

    return 0;
}

int main(int argc, char **argv)
{
    sqlite3 *db;
    char *err_msg = NULL;

    int rc = sqlite3_open("d_costing_chart.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS D_CostingChart(Department TEXT PRIMARY KEY, CreditFee REAL, SemesterFee REAL, OtherFees REAL, AdmissionFee REAL, TotalCredit INTEGER, TotalCreditBelow INTEGER, Duration INTEGER, Semester INTEGER, SemesterBelow INTEGER);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    if (argc > 1 && strcmp(argv[1], "-s") == 0)
    {
        show_table(db);
    }

    if (argc > 1 && strcmp(argv[1], "-i") == 0)
    {
        if (argc != 12)
        {
            printf("Usage: %s -i <department> <credit_fee> <semester_fee> <other_fees> <admission_fee> <total_credit> <total_credit_below> <duration> <semester> <semester_below>\n", argv[0]);
            return 1;
        }

        insert_data(db, argv[2], atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atoi(argv[7]), atoi(argv[8]), atoi(argv[9]), atoi(argv[10]), atoi(argv[11]));
    }

    if (argc > 1 && strcmp(argv[1], "-d") == 0)
    {
        if (argc != 3)
        {
            printf("Usage: %s -d <department>\n", argv[0]);
            return 1;
        }

        delete_data(db, argv[2]);
    }

    if (argc > 1 && strcmp(argv[1], "-u") == 0)
    {
        if (argc != 12)
        {
            printf("Usage: %s -u <department> <credit_fee> <semester_fee> <other_fees> <admission_fee> <total_credit> <total_credit_below> <duration> <semester> <semester_below>\n", argv[0]);
            return 1;
        }

        update_data(db, argv[2], atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atoi(argv[7]), atoi(argv[8]), atoi(argv[9]), atoi(argv[10]), atoi(argv[11]));
    }

    if (argc > 1 && strcmp(argv[1], "-c") == 0)
    {
        if (argc != 3)
        {
            printf("Usage: %s -c <department>\n", argv[0]);
            return 1;
        }

        calculate_total_cost(db, argv[2]);
    }

    sqlite3_close(db);

    return 0;
}
