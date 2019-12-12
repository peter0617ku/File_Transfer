CC = gcc
CFLAG = -c
OFLAG = -o
OBJECT = %.o

all: $(OBJECT)
	$(CC) $(OFLAG) server.exe server.o
	$(CC) $(OFLAG) client.exe client.o
%.o:
	$(CC) $(CFLAG) *.c
clean:
	rm *.exe *.o
