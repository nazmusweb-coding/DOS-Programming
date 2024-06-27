# Makefile for compiling SQL programs and cleaning binaries

CC = gcc
CFLAGS = -Wall
LIBS = ./libsqlite3.a

# Targets
TARGETS = sql D_sql

# Compile both programs
all: $(TARGETS)

# Compile each target
sql: sql.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

D_sql: D_sql.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

# Clean target to remove binaries
clean:
	rm -f $(TARGETS)