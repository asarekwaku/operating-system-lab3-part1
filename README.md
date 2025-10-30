## Lab 3 (Part 1): Processes and Pipes

This repository contains C programs and references for practicing Unix process creation and inter-process communication (IPC) using anonymous pipes.

### Contents
- `pipes_processes1.c`, `pipes_processes2.c`, `pipes_processes3.c`: Source files demonstrating fork/exec, pipe setup, and data flow across multiple processes.
- `pipes_proc1`, `pipes_proc2`, `pipes_proc3`: Compiled reference binaries for comparison.
- `ref_pipes2`, `ref_pipes3`: Additional reference binaries for multi-stage pipelines.
- `Makefile`: Targets to build and clean the project.
- `scores`: Placeholder for grading or notes.

### Prerequisites
- GCC or Clang
- Make
- A Unix-like environment (macOS or Linux)

### Build
From the project root:

```bash
make
```

This will compile the C sources and produce executables (e.g., `pipes_processes1`, `pipes_processes2`, `pipes_processes3`) depending on the `Makefile` targets.

To clean build artifacts:

```bash
make clean
```

### Run
Example invocations (adjust based on your implementation):

```bash
./pipes_processes1
./pipes_processes2
./pipes_processes3
```

You can also compare your outputs with the provided reference binaries:

```bash
./pipes_proc1
./ref_pipes2
./ref_pipes3
```

### What to focus on
- Creating pipes with `pipe(int fds[2])`
- Correctly ordering `fork()` and `dup2()` calls
- Closing unused file descriptors in both parent and child processes
- Handling `exec*` failures and exit statuses

### Repository
GitHub: `https://github.com/asarekwaku/operating-system-lab3-part1.git`

### License
For coursework use. If reusing, cite the source repository.