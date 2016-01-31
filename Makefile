CC = gcc
TOP_DIR = .
CFG_DIR = $(TOP_DIR)/cfg
SRC_DIR = $(TOP_DIR)/src
LIB_DIR = $(TOP_DIR)/lib
DAT_DIR = $(TOP_DIR)/dat
BIN_DIR = $(TOP_DIR)/bin
PREFIX = /usr/local

LIBS = -lm
CFLAGS = -Werror -Wall -std=gnu99 -I$(SRC_DIR)

BINS = spell-checker
FILES = spell-checker util

TARGETS = $(foreach TARGET, $(BINS), $(BIN_DIR)/$(TARGET))
DEPS = $(foreach FILE, $(FILES), $(SRC_DIR)/$(FILE).h)
OBJS = $(foreach FILE, $(FILES), $(BIN_DIR)/$(FILE).o)

.PHONY: all tidy clean

all: $(BIN_DIR) $(TARGETS)

$(BIN_DIR)/spell-checker: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

tidy:
	rm -rf $(BIN_DIR)/*.o

clean:
	rm -rf $(BIN_DIR)
