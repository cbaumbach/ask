include path_to_unity
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
INCLUDES = -Isrc
UNITY_INCLUDES = -I$(UNITY_HOME)/src \
                 -I$(UNITY_HOME)/extras/fixture/src

UNITY_SOURCES = $(UNITY_HOME)/src/unity.c \
                $(UNITY_HOME)/extras/fixture/src/unity_fixture.c

TEST_SOURCES = test/test_runners/all_tests.c \
               test/test_runners/test_getline_runner.c \
               test/test_getline.c \
               test/test_runners/test_splitline_runner.c \
               test/test_splitline.c \
               test/test_runners/test_makeentry_runner.c \
               test/test_makeentry.c \
               test/test_runners/test_insert_runner.c \
               test/test_insert.c \
               test/test_runners/test_prompt_runner.c \
               test/test_prompt.c \
               test/test_runners/test_sort_runner.c \
               test/test_sort.c

SOURCES = src/getline.c \
          src/splitline.c \
          src/makeentry.c \
          src/insert.c \
          src/prompt.c \
          src/sort.c \
		  src/err_msg.c

TEST_OBJECTS = $(subst .c,.o,$(TEST_SOURCES))

OBJECTS = $(subst .c,.o,$(SOURCES))

ALL_OBJECTS = $(TEST_OBJECTS) $(OBJECTS)

BINARIES = test/test_runners/all_tests
OUTPUT = test/test_runners/all_tests.out

.PHONY: all test clean
all: test ask
clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(BINARIES) $(OUTPUT)

# ==== ask ===========================================================

ask: src/main.c $(OBJECTS)
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDE) -o $@ $^

# ==== generate test output ==========================================

test: test/test_runners/all_tests.out

test/test_runners/all_tests.out: test/test_runners/all_tests
	test/test_runners/all_tests | tee $@

test/test_runners/all_tests: $(ALL_OBJECTS) $(UNITY_SOURCES)
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

# ==== test splitline function =======================================

# test runner
test/test_runners/test_splitline_runner.o: \
		test/test_runners/test_splitline_runner.c
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

test/test_splitline.o: test/test_splitline.c src/splitline.h src/err_msg.h
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

# ==== test makeentry function =======================================

# test runner
test/test_runners/test_makeentry_runner.o: \
		test/test_runners/test_makeentry_runner.c
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

test/test_makeentry.o: test/test_makeentry.c src/makeentry.h src/err_msg.h
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

# ==== test prompt function =======================================

# test runner
test/test_runners/test_prompt_runner.o: \
		test/test_runners/test_prompt_runner.c
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

test/test_prompt.o: test/test_prompt.c src/prompt.h src/err_msg.h
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

# ==== test insert function ==========================================

# test runner
test/test_runners/test_insert_runner.o: \
		test/test_runners/test_insert_runner.c
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

test/test_insert.o: test/test_insert.c src/insert.h src/err_msg.h
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

# ==== test sort functions ===========================================

# test runner
test/test_runners/test_sort_runner.o: \
		test/test_runners/test_sort_runner.c
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

test/test_sort.o: test/test_sort.c src/sort.h src/err_msg.h
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

# ==== splitline =====================================================

src/splitline.o: src/splitline.c src/splitline.h src/err_msg.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# ==== getline =======================================================

src/getline.o: src/getline.c src/getline.h src/err_msg.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# ==== makeentry =====================================================

src/makeentry.o: src/makeentry.c src/makeentry.h src/err_msg.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# ==== insert =====================================================

src/insert.o: src/insert.c src/insert.h src/err_msg.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# ==== prompt =====================================================

src/prompt.o: src/prompt.c src/prompt.h src/err_msg.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# ==== sort functions ================================================

src/sort.o: src/sort.c src/sort.h src/err_msg.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# ==== error handling ================================================

src/err_msg.o: src/err_msg.c src/err_msg.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
