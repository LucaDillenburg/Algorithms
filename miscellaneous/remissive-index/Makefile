EXEC ?= main
CFLAGS = -Wall -ansi -pedantic -O0 -g # if you just want to run, you can use: -O2
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
	make clean

run:
	make
	-./$(BUILD_DIR)/$(EXEC)
	make clean

clean:
	-rm -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p
