# Makefile for compiling SQL programs and cleaning binaries

CC = gcc
CFLAGS = -Wall
LIBS = libsqlite3.a

# Targets
TARGET1 = sql
TARGET2 = D_sql

# Source files
SRC1 = sql.c
SRC2 = D_sql.c

# Compile the first program
$(TARGET1): $(SRC1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(SRC1) $(LIBS)

# Compile the second program
$(TARGET2): $(SRC2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(SRC2) $(LIBS)

# Clean target to remove binaries
clean:
	rm -f $(TARGET1) $(TARGET2)
