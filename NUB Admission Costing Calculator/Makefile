
PROG = main
OPTION1 = test

CC = gcc
CFLAGSANDLIBS = `pkg-config --cflags --libs gtk+-3.0` -lm

${PROG}: ${PROG}.c
	${CC} ${PROG}.c ${OPTION1}.c -o ${PROG} ${CFLAGSANDLIBS}

clean:
	rm ${PROG}