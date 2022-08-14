# the compiler: gcc for C program, define as g++ for C++
CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -Werror
CTFLAGS = -D_POSIX_THREAD_SEMANTICS 
STFLAGS = -lpthread
RM = rm
MAIN = main
INS=5
K=0.9
T_INIT=1000 
T_FINISH=1e-50
MAX_ITER=1000
MOVE=1

all: compile run

compile: $(MAIN).cpp
	$(CC) $(CFLAGS) $(MAIN).cpp -o $(MAIN)
run:
	./$(MAIN) $(INS) $(K) $(T_INIT) $(T_FINISH) $(MAX_ITER) $(MOVE)
 
clean:
	rm $(MAIN)
