#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <gtk/gtk.h>
#include "sqlite3.h"
#include <time.h>
#include <string.h>

// login credentials
extern const char *admin_db;
extern const char *faculty_db;
extern const char *class_schedule;

// Login priority
extern int logged_priority;
// Login Credential for faculty
extern char *logged_id;


int login(const char *credential_db, const char *id, const char *passcode);

char *login_faculty(const char *credential_db, const char *id, const char *passcode);


#endif
