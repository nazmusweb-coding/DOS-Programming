#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>

// The function prototype for the display callback
typedef void (*ResultCallback)(const char *);
void getwaiver(float SSC, float HSC);
bool D_getwaiver(float DiplomaResult);
void replace_placeholder(char *buffer, const char *placeholder, const char *value);
void Display(ResultCallback callback);
void D_Display(ResultCallback callback);

void BBA(float SSC, float HSC, ResultCallback callback);
void LLB(ResultCallback callback);
void EEE(float SSC, float HSC, ResultCallback callback);
void Textile(float SSC, float HSC, ResultCallback callback);
void CSE(float SSC, float HSC, ResultCallback callback);
void Civil(float SSC, float HSC, ResultCallback callback);
void ME(float SSC, float HSC, ResultCallback callback);
void ECE(float SSC, float HSC, ResultCallback callback);
void B_Pharm(ResultCallback callback);
void ELL(float SSC, float HSC, ResultCallback callback);
void Bangla(float SSC, float HSC, ResultCallback callback);

struct Undergraduate 
{
    void (*BBA)(float SSC, float HSC, ResultCallback callback);
    void (*LLB)(ResultCallback callback);
    void (*EEE)(float SSC, float HSC, ResultCallback callback);
    void (*Textile)(float SSC, float HSC, ResultCallback callback);
    void (*CSE)(float SSC, float HSC, ResultCallback callback);
    void (*Civil)(float SSC, float HSC, ResultCallback callback);
    void (*ME)(float SSC, float HSC, ResultCallback callback);
    void (*ECE)(float SSC, float HSC, ResultCallback callback);
    void (*B_Pharm)(ResultCallback callback);
    void (*ELL)(float SSC, float HSC, ResultCallback callback);
    void (*Bangla)(float SSC, float HSC, ResultCallback callback);
};

void D_EEE(float DiplomaResult, ResultCallback callback);
void D_Textile(float DiplomaResult, ResultCallback callback);
void D_CSE(float DiplomaResult, ResultCallback callback);
void D_ECE(float DiplomaResult, ResultCallback callback);
void D_Civil(float DiplomaResult, ResultCallback callback);
void D_ME(float DiplomaResult, ResultCallback callback);

struct UndergraduateDiploma 
{
    void (*EEE)(float DiplomaResult, ResultCallback callback);
    void (*Textile)(float DiplomaResult, ResultCallback callback);
    void (*CSE)(float DiplomaResult, ResultCallback callback);
    void (*ECE)(float DiplomaResult, ResultCallback callback);
    void (*Civil)(float DiplomaResult, ResultCallback callback);
    void (*ME)(float DiplomaResult, ResultCallback callback);
};

#endif
