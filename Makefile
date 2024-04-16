CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -pedantic -D_XOPEN_SOURCE -D_GNU_SOURCE
DBGFLAGS := -g -O0

PROJ := account_to_sql

SRC_DIR := $(PROJ)/src
INCLUDE_DIR := $(PROJ)/include
TEST_DIR := $(PROJ)/test

SRC := $(SRC_DIR)/account.c \
			 $(SRC_DIR)/account_deserialization.c \
			 $(SRC_DIR)/account_to_sql.c \
			 $(SRC_DIR)/deserialization.c \
			 $(SRC_DIR)/flags.c \
			 $(SRC_DIR)/message.c \
			 $(SRC_DIR)/value_validation.c
MAIN := $(SRC_DIR)/main.c

TEST_SRC := $(TEST_DIR)/test_account.c \
						$(TEST_DIR)/test_validation.c
TEST_MAIN := $(TEST_DIR)/test.c
TEST_LIB := -lcheck

COVERAGE_FLAGS := --coverage -fprofile-abs-path

TARGET := acct2sql
TEST_TARGET := test
COVERAGE_TARGET := coverage

INCLUDE := $(addprefix -I, $(INCLUDE_DIR))

BUILD_DIR := build

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(BUILD_DIR) $(SRC) $(MAIN)
	$(CC) $(CFLAGS) $(DBGFLAGS) $(INCLUDE) $(SRC) $(MAIN) -o $(BUILD_DIR)/$(TARGET)

$(TEST_TARGET): $(BUILD_DIR) $(SRC) $(TEST_SRC) $(TEST_MAIN)
	$(CC) $(CFLAGS) $(DBGFLAGS) $(INCLUDE) $(TEST_LIB) \
		$(SRC) $(TEST_SRC) $(TEST_MAIN) -o $(BUILD_DIR)/$(TEST_TARGET).out


$(COVERAGE_TARGET): $(BUILD_DIR) $(SRC) $(TEST_SRC) $(TEST_MAIN)
	$(CC) $(CFLAGS) $(DBGFLAGS) $(INCLUDE) $(SRC) $(TEST_MAIN) \
		$(TEST_SRC) $(TEST_LIB) $(COVERAGE_FLAGS) -o $(BUILD_DIR)/test_coverage.out
	./$(BUILD_DIR)/test_coverage.out
	gcovr --exclude $(TEST_DIR)/ --html-details -o $(BUILD_DIR)/coverage.html
	xdg-open build/coverage.html

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all
