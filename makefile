CC = gcc 
CFLAGS = -g -pg -Wall -O3 -pedantic -Wextra -std=gnu11 -Wconversion #-Werror 
OBJS = obj#nombre de la carpeta donde se guardan los .o
SRC = src
BIN = bin
INC = inc
LIB = lib
DEP = inc/dependencies.h
WHERE = -Wl,-rpath,.

all:  mkdir main #cl

#cl:
#	rm ./bin/distancia.pgm
mkdir:
	mkdir -p $(SRC) $(BIN) $(LIB) $(OBJS) $(INC)

lib_misc.a: file_processing.o
	ar rcs $(LIB)/$@ $(OBJS)/file_processing.o 

file_processing.o: $(SRC)/file_processing.c $(INC)/file_processing.h
	$(CC) -c $< $(CFLAGS) -o $(OBJS)/$@ -lm 

main.o: $(SRC)/main.c $(INC)/file_processing.h 
	$(CC) $(CFLAGS) -c $< -o $(OBJS)/$@

main: main.o lib_misc.a
	$(CC) $(OBJS)/$< $(LIB)/lib_misc.a -o $(BIN)/$@ -lm 

#B_client: $(SRC)/B_client.c $(INC)/client_config.h
#	$(CC) $< $(CFLAGS) -o $(BIN)/$@

clean:
	rm -rf $(BIN) $(OBJS) $(LIB) 