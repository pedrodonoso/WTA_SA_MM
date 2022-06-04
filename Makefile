# the compiler: gcc for C program, define as g++ for C++
CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -Werror
CTFLAGS = -D_POSIX_THREAD_SEMANTICS 
STFLAGS = -lpthread
RM = rm
# the build target executable:
# NOTHREADS = multiply
MAIN = main
# STHREAD = sthread

# all: $(STHREAD) $(NOTHREADS) $(THREADS)
all: $(MAIN)

# $(STHREAD): $(STHREAD).c
# 	$(CC) $(CFLAGS) $(CTFLAGS) -c $(MAIN).cpp -o $(MAIN).o $(STFLAGS)
# 	$(CC) $(CFLAGS) $(CTFLAGS) -c $(STHREAD).c -o $(STHREAD).o $(STFLAGS)
# 	$(CC) $(MAIN).o $(STHREAD).o -o $(MAIN) $(STFLAGS)

$(MAIN): $(MAIN).cpp
	$(CC) $(CFLAGS) $(MAIN).cpp -o $(MAIN)

# $(MAIN): $(MAIN).cpp
# 	$(CC) $(CFLAGS) $(TFLAGS) $(MAIN).cpp sthread.c -o $(MAIN) 

help:
	@echo 'sudo make TARGET=nombre_archivo'

# sudo make TARGET=C1