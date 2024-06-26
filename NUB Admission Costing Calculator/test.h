#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include "database/sqlite3.h"

// The function pointer type prototype for the display callback
typedef void (*ResultCallback)(const char *);

// getwaiver functions
void getwaiver(double SSC, double HSC, const char *department);
bool D_getwaiver(double DiplomaResult);

void replace_placeholder(char *buffer, const char *placeholder, const char *value);

// Disply functions
void Display(ResultCallback callback);
void D_Display(ResultCallback callback);

// Opens database and reads data and calculates
void getCalculated(const char *department, double SSC, double HSC, ResultCallback callback);
void D_getCalculated(const char *department, double DiplomaResult, ResultCallback callback);

#endif