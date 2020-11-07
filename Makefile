# alvo (pode ser arquivo): pre-requisitos separado por virgula
#	comandos (precisa ser iniciado com tab)
# arquivos objeto:
# 	comandos
# bibliotecas:
#	comandos
# 
# - a primeira regra eh a padrao, entao se deseja-se executar mais do que um alvo como default colocar "all: alvo1 alvo2 ..." no topo
# - cada divisao dessa soh vai ser executada caso o alvo nao exista ou tenha uma data de modificacao mais velha do que seus pre-requisitos ou dos pre-requisitos de seus pre-requisitos (essa verificacao eh feita de forma recursiva)
# - o make verifica se houve modificacao comparando as datas de mofidicacao dos arquivos (nao o conteudo deles)
# - if you don't make to stop after an error at one command put '-' before the command

EXECS = ep2
CFLAGS = -Wall -ansi -pedantic -O0 -g #-O2
CC = gcc

all: ep2

run:
	gdb ep2

ep2: ep2.o board.o utils.o vector.o
	$(CC) -o ep2 ep2.o board.o utils.o vector.o $(CFLAGS)

ep2.o: ep2.c
	$(CC) -c ep2.c $(CFLAGS)

board.o: board.c board.h
	$(CC) -c board.c $(CFLAGS)

utils.o: utils.c utils.h
	$(CC) -c utils.c $(CFLAGS)

vector.o: vector.c vector.h
	$(CC) -c vector.c $(CFLAGS)

clean:
	-rm $(EXECS) *.o
