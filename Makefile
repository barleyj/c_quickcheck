CC     = gcc
CFLAGS = -Wall -Werror
OUT_DIR=bin
BUILD_DIR=build
TEST_BUILD_DIR=test_build
SRC_DIR=src
TEST_SRC_DIR=tests
EXCLUDE=""
DIRS=$(OUT_DIR)
SRC= $(wildcard $(SRC_DIR)/*.c)
OBJ= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
TESTS=$(patsubst $(SRC_DIR)/%.c, $(TEST_BUILD_DIR)/%_tests, $(filter-out $(EXCLUDE), $(SRC)))
TEST_SRC= $(patsubst $(SRC_DIR)/%.c, $(TEST_SRC_DIR)/%_tests.c, $(filter-out $(EXCLUDE), $(SRC)))
TEST_OBJ= $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_BUILD_DIR)/%.o, $(TEST_SRC))

# This will run all tests as long as there is a test file for EVERY src file

.PHONY: all_tests

all_tests: $(TESTS)

$(TESTS): $(TEST_BUILD_DIR)/%_tests : $(BUILD_DIR)/%.o $(TEST_BUILD_DIR)/%_tests.o
	$(CC) $(CFLAGS) -o $@ $^ `pkg-config --cflags --libs check`
	$@

$(TEST_OBJ): $(TEST_BUILD_DIR)/%.o : $(TEST_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f build/* 
	rm -f test_build/* 
	rm -f bin/*

init: 
	mkdir $(OUT_DIR)
	mkdir $(BUILD_DIR)
	mkdir $(TEST_BUILD_DIR)
	mkdir $(SRC_DIR)
	mkdir $(TEST_SRC_DIR)
