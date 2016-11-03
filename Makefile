EXEC = exe
OBJS = main.o Queue.o

CFLAG = -Wall -g
LIBS = -lpthread

HEADS = -I./

all: $(OBJS)
	gcc $(CFLAG) -o $(EXEC) $(OBJS) $(LIBS)
	objdump -D $(EXEC) > $(EXEC).dis

main.o:
	gcc -c main.c $(HEADS) 

Queue.o:
	gcc -c Queue.c $(HEADS)

clean:
	rm -f *.o
	rm -f exe*
