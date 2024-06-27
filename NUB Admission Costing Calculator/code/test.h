#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include "../database/sqlite3.h"

// Global variables to read and write data (to be used across multiple files)
extern int year, semester, credit;

// Global macro for buffer size and array to read about and write it (to be used across multiple files)
#define MAX_BUF_SIZE 4096
extern char about_description[MAX_BUF_SIZE];

// The function pointer type prototype for the display callback
typedef void (*ResultCallback)(const char *);
typedef int (*CreditCallback)(sqlite3_stmt *);
typedef int (*D_CreditCallback)(sqlite3_stmt *, double);

// getwaiver functions
void getwaiver(double SSC, double HSC, const char *department);
bool D_getwaiver(double DiplomaResult);

void replace_placeholder(char *buffer, const char *placeholder, const char *value);

// Disply functions
void Display(ResultCallback callback);
void D_Display(ResultCallback callback);

// Opens database and reads data and calculates
void getCalculated(const char *department, double SSC, double HSC, CreditCallback getcredit, ResultCallback callback);
void D_getCalculated(const char *department, double DiplomaResult, D_CreditCallback getcredit, ResultCallback callback);

void read_about_description();

#endif