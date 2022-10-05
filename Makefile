SRC_DIR := src
TEST_DIR := tests
BIN_DIR := bin
CHECK404_DIR := check404
CC := gcc

PROBLEM_SET := main

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall
DLL_FLAGS := -fPIC -shared
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean install

all: $(PROBLEM_SET)

./dll:
	@mkdir -p ./dll

install: ./dll
	@$(CC) ./include/sqlite3.c -fPIC -shared -o ./dll/sqlite3.so

$(PROBLEM_SET): $(BIN_DIR)
	@$(CC) $(SRC_DIR)/$(@).c ./dll/sqlite3.so $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/$@.out

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

run: $(filter-out run, $(MAKECMDGOALS))
	@for i in $^; do ./$(BIN_DIR)/$$i.out; done

clean:
	@$(RM) -rf $(BIN_DIR)
	@$(RM) -rf ./dll
	@$(RM) -rf ./trash
