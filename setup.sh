#!/bin/bash
# setup.sh

# Set up testing infrastructure.

# Install git.
GIT=$(which git)
if [ -z "$GIT" ]
then
    echo "You have to install git first."
    exit 1
fi

# Clone unity repository.
mkdir -p ~/code/c
if [ ! -d "$HOME/code/c/unity" ]
then
    git clone https://github.com/ThrowTheSwitch/Unity.git $HOME/code/c/unity
fi

# Create minimal makefile.

cat <<'EOF' > makefile
include path_to_unity
CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDES = -Isrc
UNITY_INCLUDES = -I$(UNITY_HOME)/src \
                 -I$(UNITY_HOME)/extras/fixture/src

UNITY_SOURCES = $(UNITY_HOME)/src/unity.c \
                $(UNITY_HOME)/extras/fixture/src/unity_fixture.c

SOURCES = test/test_runners/all_tests.c \
          test/test_runners/test_getline_runner.c \
          test/test_getline.c \
          src/getline.c

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

test/test_getline.o: test/test_getline.c src/getline.h
	$(CC) $(CFLAGS) $(UNITY_INCLUDES) $(INCLUDES) -c -o $@ $<

# ==== getline =======================================================

src/getline.o: src/getline.c src/getline.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
EOF

echo "UNITY_HOME = $HOME/code/c/unity" > path_to_unity

# Add directories and files needed to get the above makefile working.

mkdir -p src test/test_runners

touch src/getline.c src/getline.h

cat <<'EOF' > test/test_getline.c
#include "unity_fixture.h"
#include "getline.h"

TEST_GROUP(getline);

TEST_SETUP(getline)
{
}

TEST_TEAR_DOWN(getline)
{
}

TEST(getline, fail)
{
    TEST_FAIL_MESSAGE("start here");
}
EOF

cat <<'EOF' > test/test_runners/test_getline_runner.c
#include "unity_fixture.h"

TEST_GROUP_RUNNER(getline)
{
    RUN_TEST_CASE(getline, fail);
}
EOF

cat <<'EOF' > test/test_runners/all_tests.c
#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(getline);
}

int main(int argc, const char *argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
EOF

# Run minimal build and get failing test.
make
