PROJECT_NAME = hashcode2022

CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -O3 
OBJECTS = Main.o List.o

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)
	rm -f *.o

Main.o: Main.c