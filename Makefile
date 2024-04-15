CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -pedantic
DBGFLAGS := -g -O0 -D_XOPEN_SOURCE

PROJ := account_to_sql

SRC_DIR := $(PROJ)/src
INCLUDE_DIR := $(PROJ)/include

SRC := $(wildcard $(SRC_DIR)/*.c)
INCLUDE := $(addprefix -I, $(INCLUDE_DIR))

TARGET := acct2sql

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(DBGFLAGS) $(INCLUDE) $(SRC) -o $(TARGET)

clean:
	rm $(TARGET)

rebuild: clean all
