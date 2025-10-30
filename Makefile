# ---------------------------------------------
# Makefile for Pipes and Processes Lab
# Builds:
#   1. pipes_proc1  - two-way parent/child communication
#   2. pipes_proc2  - chaining two processes (cat | grep)
#   3. pipes_proc3  - chaining three processes (cat | grep <arg> | sort)
# ---------------------------------------------

CFLAGS = -D_SVID_SOURCE -D_GNU_SOURCE -Wall -std=c99 -Werror=cpp -pedantic

all: pipes_proc1 pipes_proc2 pipes_proc3

# Build Program 1: Two-way pipe (parent ↔ child)
pipes_proc1: pipes_processes1.c
	gcc $(CFLAGS) pipes_processes1.c -o pipes_proc1

# Build Program 2: Two-process chain (cat | grep)
pipes_proc2: pipes_processes2.c
	gcc $(CFLAGS) pipes_processes2.c -o pipes_proc2

# Build Program 3: Three-process chain (cat | grep <arg> | sort)
pipes_proc3: pipes_processes3.c
	gcc $(CFLAGS) pipes_processes3.c -o pipes_proc3

# Clean up compiled executables
clean:
	rm -f pipes_proc1 pipes_proc2 pipes_proc3
