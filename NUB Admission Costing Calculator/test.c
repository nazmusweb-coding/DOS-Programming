#include "test.h"

// Global variables to read and write data, for "waiver" "TC" "year" "semester" "credit" placeholders
int waiver, TC, year, semester, credit;

// Readfile buffer size and temporary text file name for output generation
#define BUFFER_SIZE 1024
char TEMP_FILE_NAME[] = "formats/temp.txt";

// getwaiver function to calculate waiver based on SSC and HSC result for Undergraduate
void getwaiver(float SSC, float HSC) 
{
    // Waiver is given on lowest result.
    float Result = fmin(SSC, HSC);
    if (Result > 5.00) 
    {
        waiver = 70;
    } 
    else if (Result == 5.00) 
    {
        waiver = 40;
    } 
    else if (Result >= 4.80) 
    {
        waiver = 30;
    } 
    else if (Result >= 4.50) 
    {
        waiver = 20;
    } 
    else if (Result >= 4.00) 
    {
        waiver = 15;
    } 
    else if (Result >= 3.50)
    {
        waiver = 10;
    } 
    else 
    {
        waiver = 0;
    }
}

// D_getwaiver function to calculate waiver based on SSC and HSC result for Undergraduate(for diploma holder)
bool D_getwaiver(float DiplomaResult)
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
    FILE *fp = fopen("formats/format.txt", "r");
    if (fp == NULL) 
    {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

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
        sprintf(value, "%d", waiver);
        replace_placeholder(buffer, "\"waiver\"", value);

        sprintf(value, "%d", TC);
        replace_placeholder(buffer, "\"TC\"", value);

        sprintf(value, "%d", year);
        replace_placeholder(buffer, "\"year\"", value);

        sprintf(value, "%d", semester);
        replace_placeholder(buffer, "\"semester\"", value);

        sprintf(value, "%d", credit);
        replace_placeholder(buffer, "\"credit\"", value);

        fputs(buffer, temp_fp);
    }

    rewind(temp_fp);

    while (fgets(buffer, BUFFER_SIZE, temp_fp) != NULL) 
    {
        printf("Buffer content: %s\n", buffer); // Debug print
        callback(buffer); // Calls the callback with each line of output
    }

    fclose(fp);
    fclose(temp_fp);
    remove(TEMP_FILE_NAME);
}

// Display function for Diploma Holders
void D_Display(ResultCallback callback) 
{
    FILE *fp = fopen("formats/D_format.txt", "r");
    if (fp == NULL) 
    {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

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

        fputs(buffer, temp_fp);
    }

    rewind(temp_fp);

    while (fgets(buffer, BUFFER_SIZE, temp_fp) != NULL) 
    {
        printf("Buffer content: %s\n", buffer); // Debug print
        callback(buffer); // Call the callback with each line of output
    }

    fclose(fp);
    fclose(temp_fp);
    remove(TEMP_FILE_NAME);
}

// Definition of Struct Undergraduate starts from here
void BBA(float SSC, float HSC, ResultCallback callback)
{
    getwaiver(SSC, HSC);
    const int creditFee = 3409;
    const int semesterFee = 5500;
    const int onetimeFee = 23000;
    const int waivercreditFee = (float)creditFee * ((100.0 - (float)waiver)/100.0);
    year = 4;
    semester = 12;
    credit = 129;
    TC = (credit * waivercreditFee) + (semesterFee * semester) + onetimeFee;// semester corrected
    Display(callback); // Pass the callback function as callback
    waiver = TC = year = semester = credit = 0;
}

void LLB(ResultCallback callback)
{
    const int creditFee = 3690;
    const int semesterFee = 7500;
    const int onetimeFee = 23000;
    const int waivercreditFee = creditFee;
    year = 4;
    semester = 8;
    credit = 141;
    TC = (credit * waivercreditFee) + (semesterFee * semester) + onetimeFee;// semester corrected
    Display(callback); // Pass the callback function as callback
    waiver = TC = year = semester = credit = 0;
}

void EEE(float SSC, float HSC, ResultCallback callback)
{
    getwaiver(SSC, HSC);
    const int creditFee = 2631;
    const int semesterFee = 5500;
    const int onetimeFee = 25500;
    const int waivercreditFee = (float)creditFee * ((100.0 - (float)waiver)/100.0);
    year = 4;
    semester = 12;
    credit = 160;
    TC = (credit * waivercreditFee) + (semesterFee * semester) + onetimeFee;// semester corrected
    Display(callback); // Pass the callback function as callback
    waiver = TC = year = semester = credit = 0;
}

void Textile(float SSC, float HSC, ResultCallback callback)
{
    getwaiver(SSC, HSC);
    const int creditFee = 2520;
    const int semesterFee = 5500;
    const int onetimeFee = 25500;
    const int waivercreditFee = (float)creditFee * ((100.0 - (float)waiver)/100.0);
    year = 4;
    semester = 12;
    credit = 164;
    TC = (credit * waivercreditFee) + (semesterFee * semester) + onetimeFee;// semester corrected
    Display(callback); // Pass the callback function as callback
    waiver = TC = year = semester = credit = 0;
}

void CSE(float SSC, float HSC, ResultCallback callback) 
{
    getwaiver(SSC, HSC);
    const int creditFee = 3000;
    const int semesterFee = 5500;
    const int onetimeFee = 23000;
    const int waivercreditFee = (float)creditFee * ((100.0 - (float)waiver)/100.0);
    year = 4;
    semester = 12;
    credit = 152;
    TC = (credit * waivercreditFee) + (semesterFee * semester) + onetimeFee;// semester corrected
    Display(callback); // Pass the callback function as callback
    waiver = TC = year = semester = credit = 0;
}

void Civil(float SSC, float HSC, ResultCallback callback)
{
    getwaiver(SSC, HSC);
    const int creditFee = 3200;
    const int semesterFee = 8250;
    const int onetimeFee = 23000;
    const int waivercreditFee = (float)creditFee * ((100.0 - (float)waiver)/100.0);
    year = 4;
    semester = 8;
    credit = 140;
    TC = (credit * waivercreditFee) + (semesterFee * semester) + onetimeFee;// semester corrected
    Display(callback); // Pass the callback function as callback
    waiver = TC = year = semester = credit = 0;
}

void ME(float SSC, float HSC, ResultCallback callback)
{
    getwaiver(SSC, HSC);
    const int creditFee = 3100;
    const int semesterFee = 8250;
    const int onetimeFee = 23000;
    const int waivercreditFee = (float)creditFee * ((100.0 - (float)waiver)/100.0);
    year = 4;
    semester = 8;
    credit = 160;
    TC = (credit * waivercreditFee) + (semesterFee * semester) + onetimeFee;// semester corrected
    Display(callback); // Pass the callback function as callback
    waiver = TC = year = semester = credit = 0;
}

void ECE(float SSC, float HSC, ResultCallback callback)
{
    getwaiver(SSC, HSC);
    const int creditFee = 2859;
    const int semesterFee = 5500;
    const int onetimeFee = 23000;
    const int waivercreditFee = (float)creditFee * ((100.0 - (float)waiver)/100.0);
    year = 4;
    semester = 8;
    credit = 155;
    TC = (credit * waivercreditFee) + (semesterFee * semester) + onetimeFee;// semester corrected
    Display(callback); // Pass the callback function as callback
    waiver = TC = year = semester = credit = 0;
}

void B_Pharm(ResultCallback callback)
{
    const int creditFee = 3574;
    const int semesterFee = 7500;
    const int onetimeFee = 23000;
    const int waivercreditFee = creditFee;
    year = 4;
    semester = 8;
    credit = 160;
    TC = (credit * waivercreditFee) + (semesterFee * semester) + onetimeFee;// semester corrected
    Display(callback); // Pass the callback function as callback
    waiver = TC = year = semester = credit = 0;
}

void ELL(float SSC, float HSC, ResultCallback callback)
{
    getwaiver(SSC, HSC);
    const int creditFee = 1565;
    const int semesterFee = 5500;
    const int onetimeFee = 23000;
    const int waivercreditFee = (float)creditFee * ((100.0 - (float)waiver)/100.0);
    year = 4;
    semester = 12;
    credit = 132;
    TC = (credit * waivercreditFee) + (semesterFee * semester) + onetimeFee;// semester corrected
    Display(callback); // Pass the callback function as callback
    waiver = TC = year = semester = credit = 0;
}

void Bangla(float SSC, float HSC, ResultCallback callback)
{
    getwaiver(SSC, HSC);
    const int creditFee = 800;
    const int semesterFee = 2000;
    const int onetimeFee = 14000;
    const int waivercreditFee = (float)creditFee * ((100.0 - (float)waiver)/100.0);
    year = 4;
    semester = 12;
    credit = 120;
    TC = (credit * waivercreditFee) + (semesterFee * semester) + onetimeFee;// semester corrected
    Display(callback); // Pass the callback function as callback
    waiver = TC = year = semester = credit = 0;
}// End of definition of struct Undergraduate

// Definition of Struct UndergraduateDiploma starts from here
void D_EEE(float DiplomaResult, ResultCallback callback)
{
    year = 3;
    if (D_getwaiver(DiplomaResult))
    {
        semester = 9;
        credit = 132;
        TC = 195000;
    }
    else
    {
        semester = 11;
        credit = 160;
        TC = 324840;
    }
    D_Display(callback);
    TC = year = semester = credit = 0;
}

void D_Textile(float DiplomaResult, ResultCallback callback)
{
    year = 3;
    if (D_getwaiver(DiplomaResult))
    {
        semester = 9;
        credit = 137;
        TC = 200000;
    }
    else
    {
        semester = 11;
        credit = 164;
        TC = 324576;
    }
    D_Display(callback);
    TC = year = semester = credit = 0;
}

void D_CSE(float DiplomaResult, ResultCallback callback)
{
    year = 3;
    if (D_getwaiver(DiplomaResult))
    {
        semester = 9;
        credit = 129;
        TC = 200000;
    }
    else
    {
        semester = 11;
        credit = 152;
        TC = 296796;
    }
    D_Display(callback);
    TC = year = semester = credit = 0;
}

void D_ECE(float DiplomaResult, ResultCallback callback)
{
    year = 3;
    if (D_getwaiver(DiplomaResult))
    {
        semester = 9;
        credit = 138;
        TC = 203760;
    }
    else
    {
        semester = 11;
        credit = 155;
        TC = 231000;
    }
    D_Display(callback);
    TC = year = semester = credit = 0;
}

void D_Civil(float DiplomaResult, ResultCallback callback)
{
    // new department in NUB, so enough details not provided
    year = 3;
    if (D_getwaiver(DiplomaResult))
    {
        semester = 11;
        credit = 110;
        TC = 220000;
    }
    else
    {
        semester = 11;
        credit = 140;
        TC = 300000; // no result given in pdf
    }
    D_Display(callback);
    TC = year = semester = credit = 0;
}

void D_ME(float DiplomaResult, ResultCallback callback)
{
    // new department in NUB, so enough details not provided
    year = 3;
    semester = 9;
    if (D_getwaiver(DiplomaResult))
    {
        credit = 132;
        TC = 244000;
    }
    else
    {
        credit = 160;
        TC = 300000; // no result given in pdf
    }
    D_Display(callback);
    TC = year = semester = credit = 0;
}// End of definition of struct UndergraduateDiploma