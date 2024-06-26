#include "test.h"

// Global variables to read and write data, for "waiver" "TC" "year" "semester" "credit" placeholders
double waiver;
int TC, year, semester, credit;



// Global variable to read only data and used in calculations
double semesterFee, creditFee, admissionFee, otherFees;



// Readfile buffer size, format text files and temporary text file name for output generation
#define BUFFER_SIZE 1024
char FILE_NAME[] = "../formats/format.txt";
char D_FILE_NAME[] = "../formats/D_format.txt";
char TEMP_FILE_NAME[] = "../formats/temp.txt";




// Database row buffer size and file paths
#define ROW_BUFFFER_SIZE 256
char DATABASE_NAME[] = "../database/costing_chart.db";
char D_DATABASE_NAME[] = "../database/d_costing_chart.db";





// Global variable to store the about descriptionGlobal variable to store the about description
char about_description[MAX_BUF_SIZE] = {0};
char ABOUT_DETAILS_PATH[] = "../formats/about.txt";





// getwaiver function to calculate waiver based on SSC and HSC result for Undergraduate
void getwaiver(double SSC, double HSC, const char *department) 
{
    // Waiver is given on lowest result.
    double Result = fmin(SSC, HSC);

    // Initially sets waiver to zero for LLB, Pharmacy department, and lowest result under 3.50
    if (strcmp(department, "LLB") == 0 || 
        strcmp(department, "B_Pharm") == 0 ||
        Result < 3.50)
    {
        waiver = 0;
        return;
    }
    
    if (Result > 5.00) 
    {
        waiver = 70.0;
    } 
    else if (Result == 5.00) 
    {
        waiver = 40.0;
    } 
    else if (Result >= 4.80) 
    {
        waiver = 30.0;
    } 
    else if (Result >= 4.50) 
    {
        waiver = 20.0;
    } 
    else if (Result >= 4.00) 
    {
        waiver = 15.0;
    } 
    else if (Result >= 3.50)
    {
        waiver = 10.0;
    }
}





// D_getwaiver function to calculate waiver based on SSC and HSC result for Undergraduate(for diploma holder)
bool D_getwaiver(double DiplomaResult)
{
    if (DiplomaResult >= 3.0)
    {
        return true;
    }
    return false;
}





// Replace_placeholder utility function to reduce the code in Display function
void replace_placeholder(char *buffer, const char *placeholder, const char *value) 
{
    char temp[BUFFER_SIZE];
    char *pos = NULL;

    // loop continues until pos is not NULL
    while ((pos = strstr(buffer, placeholder)) != NULL) 
    {
        *pos = '\0';
        snprintf(temp, BUFFER_SIZE, "%s%s%s", buffer, value, pos + strlen(placeholder));    // %s%s%s for temp, buffer and value
        strncpy(buffer, temp, BUFFER_SIZE);
    }
}





// Display function to read output format from csv file and print output to user
void Display(ResultCallback callback) 
{
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) 
    {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    // We will safely work in temporary file and later on delete it.
    FILE *temp_fp = fopen(TEMP_FILE_NAME, "w+");
    if (temp_fp == NULL) 
    {
        perror("Failed to open temporary file");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    char value[20];

    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) 
    {
        sprintf(value, "%0.0f", waiver);
        replace_placeholder(buffer, "\"waiver\"", value);

        sprintf(value, "%d", TC);
        replace_placeholder(buffer, "\"TC\"", value);

        sprintf(value, "%d", year);
        replace_placeholder(buffer, "\"year\"", value);

        sprintf(value, "%d", semester);
        replace_placeholder(buffer, "\"semester\"", value);

        sprintf(value, "%d", credit);
        replace_placeholder(buffer, "\"credit\"", value);

        sprintf(value, "%0.0f", creditFee);
        replace_placeholder(buffer, "\"CF\"", value);

        sprintf(value, "%0.0f", semesterFee);
        replace_placeholder(buffer, "\"SF\"", value);

        sprintf(value, "%0.0f", admissionFee);
        replace_placeholder(buffer, "\"AF\"", value);

        sprintf(value, "%0.0f", otherFees);
        replace_placeholder(buffer, "\"OTF\"", value);

        fputs(buffer, temp_fp);
    }

    rewind(temp_fp);

    while (fgets(buffer, BUFFER_SIZE, temp_fp) != NULL) 
    {
        printf("Buffer content: %s\n", buffer);         // Debug print
        callback(buffer);                               // Calls the callback with each line of output
    }

    fclose(fp);
    fclose(temp_fp);
    remove(TEMP_FILE_NAME);
}





// Display function for Diploma Holders
void D_Display(ResultCallback callback) 
{
    FILE *fp = fopen(D_FILE_NAME, "r");
    if (fp == NULL) 
    {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    // We will safely work in temporary file and later on delete it.
    FILE *temp_fp = fopen(TEMP_FILE_NAME, "w+");
    if (temp_fp == NULL) 
    {
        perror("Failed to open temporary file");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    char value[20];

    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) 
    {
        sprintf(value, "%d", TC);
        replace_placeholder(buffer, "\"TC\"", value);

        sprintf(value, "%d", year);
        replace_placeholder(buffer, "\"year\"", value);

        sprintf(value, "%d", semester);
        replace_placeholder(buffer, "\"semester\"", value);

        sprintf(value, "%d", credit);
        replace_placeholder(buffer, "\"credit\"", value);

        sprintf(value, "%0.0f", creditFee);
        replace_placeholder(buffer, "\"CF\"", value);

        sprintf(value, "%0.0f", semesterFee);
        replace_placeholder(buffer, "\"SF\"", value);

        sprintf(value, "%0.0f", admissionFee);
        replace_placeholder(buffer, "\"AF\"", value);

        sprintf(value, "%0.0f", otherFees);
        replace_placeholder(buffer, "\"OTF\"", value);

        fputs(buffer, temp_fp);
    }

    rewind(temp_fp);

    while (fgets(buffer, BUFFER_SIZE, temp_fp) != NULL) 
    {
        printf("Buffer content: %s\n", buffer);         // Debug print
        callback(buffer);                               // Call the callback with each line of output
    }

    fclose(fp);
    fclose(temp_fp);
    remove(TEMP_FILE_NAME);
}





// This function reads data from database, calculates total cost, and calls display function for Undergraduate
void getCalculated(const char *department, double SSC, double HSC, CreditCallback getcredit, ResultCallback callback)
{
    sqlite3 *db;
    char *err_msg = NULL;

    // Opening a connection to an database (rc = result code)
    int rc = sqlite3_open(DATABASE_NAME, &db);

    // Database Handling properly
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));  // Debug print
        sqlite3_close(db);

        return;
    }

    char sql[ROW_BUFFFER_SIZE];
    sqlite3_stmt *stmt;

    // Taking row-wise data into sql for given department.
    sprintf(sql, "SELECT SemesterFee, CreditFee, AdmissionFee, OtherFees, TotalCredits, Duration, Semesters FROM CostingChart WHERE Department='%s';", department);

    // Compiles a SQL statement into a byte-code program
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    // Database execution Handling properly
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));   // Debug print
        return;
    }

    // Debug print and safety check for dev 
    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        printf("Department not found.\n");
        return;
    }

    // Retrieving data from columns
    semesterFee = sqlite3_column_double(stmt, 0);
    creditFee = sqlite3_column_double(stmt, 1);
    admissionFee = sqlite3_column_double(stmt, 2);
    otherFees = sqlite3_column_double(stmt, 3);

    // Fetch rest of the data from database and approximate data for credit transfer
    rc = getcredit(stmt);

    // Fetch operation handling
    if (rc == -1)
    {
        fprintf(stderr, "Failed to get data.\n");   // Debug print
        return;
    }

    getwaiver(SSC, HSC, department);
    const int waivercreditFee = creditFee * ((100.0 - waiver)/100.0);
    TC = (credit * waivercreditFee) + (semesterFee * semester) + admissionFee + otherFees;
    Display(callback); // Pass the callback function as callback
    waiver = TC = year = semester = credit = semesterFee = creditFee = admissionFee = otherFees = 0;

    // Deleting the statement obj and closing the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}





// This function reads data from database, calculates total cost, and calls display function for Undergraduate (for Diploma Holders)
void D_getCalculated(const char *department, double DiplomaResult, D_CreditCallback getcredit, ResultCallback callback)
{
    sqlite3 *db;
    char *err_msg = NULL;

    // Opening a connection to an database (rc = result code)
    int rc = sqlite3_open(D_DATABASE_NAME, &db);

    // Database Handling properly
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));  // Debug print
        sqlite3_close(db);

        return;
    }

    char sql[ROW_BUFFFER_SIZE];
    sqlite3_stmt *stmt;

    // Taking row-wise data into sql for given department.
    sprintf(sql, "SELECT CreditFee, SemesterFee, OtherFees, AdmissionFee, TotalCredit, TotalCreditBelow, Duration, Semester, SemesterBelow FROM D_CostingChart WHERE Department='%s';", department);

    // Compiles a SQL statement into a byte-code program
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    // Database execution Handling properly
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));   // Debug print
        return;
    }

    // Debug print and safety check for dev 
    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        printf("Department not found.\n");
        return;
    }

    // Retrieving data from columns
    creditFee = sqlite3_column_double(stmt, 0);
    semesterFee = sqlite3_column_double(stmt, 1);
    otherFees = sqlite3_column_double(stmt, 2);
    admissionFee = sqlite3_column_double(stmt, 3);
    year = sqlite3_column_int(stmt, 6);

    // Fetch rest of the data from database and approximate data for credit transfer
    rc = getcredit(stmt, DiplomaResult);

    // Fetch operation handling
    if (rc == -1)
    {
        fprintf(stderr, "Failed to get data.\n");   // Debug print
        return;
    }

    TC = (credit * creditFee) + (semesterFee * semester) + admissionFee + otherFees;
    D_Display(callback); // Pass the callback function as callback
    TC = year = semester = credit = semesterFee = creditFee = admissionFee = otherFees = 0;

    // Deleting the statement obj and closing the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}





// Function to read the about description from file
void read_about_description() 
{
    FILE *fp;
    char line[MAX_BUF_SIZE];
    int len = 0;
    
    fp = fopen(ABOUT_DETAILS_PATH, "r");
    if (fp == NULL) 
    {
        fprintf(stderr, "Error opening file %s\n", ABOUT_DETAILS_PATH);
        sprintf(about_description, "ERROR 404\nNot Found");
        return;
    }
    
    // Initialize about_description as empty string
    about_description[0] = '\0';

    // Read lines from the file until the end
    while (fgets(line, sizeof(line), fp)) 
    {
        len = strlen(line);
        if (len > 0 && line[len-1] == '\n')
        {
            line[len-1] = '\0'; // Removes newline character if present
        }

        strcat(about_description, line); // Concatenation of strings
        strcat(about_description, "\n"); // Add newline for formatting between lines
    }

    fclose(fp);
}