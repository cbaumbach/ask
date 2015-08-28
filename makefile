include path_to_unity
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
INCLUDES = -Isrc
UNITY_INCLUDES = -I$(UNITY_HOME)/src \
                 -I$(UNITY_HOME)/extras/fixture/src

UNITY_SOURCES = $(UNITY_HOME)/src/unity.c \
                $(UNITY_HOME)/extras/fixture/src/unity_fixture.c

SOURCES = test/test_runners/all_tests.c \
          test/test_runners/test_getline_runner.c \
          test/test_getline.c \
          src/getline.c \
		  src/err_msg.c

OBJECTS = $(subst .c,.o,$(SOURCES))

BINARIES = test/test_runners/all_tests
OUTPUT = test/test_runners/all_tests.out

.PHONY: all test clean
all: test
clean:
	rm -f $(OBJECTS) $(BINARIES) $(OUTPUT)

# ==== generate test output ==========================================

test: test/test_runners/all_tests.out

test/test_runners/all_tests.out: test/test_runners/all_tests
	test/test_runners/all_tests | tee $@

test/test_runners/all_tests: $(OBJECTS) $(UNITY_SOURCES)
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -o $@ $^

test/test_runners/all_tests.o: test/test_runners/all_tests.c
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

# ==== test getline function =========================================

# test runner
test/test_runners/test_getline_runner.o: \
		test/test_runners/test_getline_runner.c
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

test/test_getline.o: test/test_getline.c src/getline.h src/err_msg.h
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

# ==== getline =======================================================

src/getline.o: src/getline.c src/getline.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# ==== error handling ================================================

src/err_msg.o: src/err_msg.c src/err_msg.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
