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

EXEC ?= main
CFLAGS = -Wall -ansi -pedantic -O0 -g # if you just want to run, you can use: -O2
LDFLAGS = -lm
CC = gcc

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

$(BUILD_DIR)/$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

debug:
	make
	-gdb ./$(BUILD_DIR)/$(EXEC)

run:
	make
	-./$(BUILD_DIR)/$(EXEC)

clean:
	-rm -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p
