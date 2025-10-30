#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <search_term>\n", argv[0]);
        exit(1);
    }

    int pipe1[2];  // cat -> grep
    int pipe2[2];  // grep -> sort
    pipe(pipe1);
    pipe(pipe2);

    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == 0) {
        // Child -> will fork again for grep/sort chain
        pid2 = fork();

        if (pid2 == 0) {
            // Grandchild runs "sort"
            dup2(pipe2[0], STDIN_FILENO);
            close(pipe2[1]);
            close(pipe1[0]);
            close(pipe1[1]);
            execlp("sort", "sort", NULL);
            perror("execlp sort");
            exit(1);
        } else {
            // Child runs "grep <arg>"
            dup2(pipe1[0], STDIN_FILENO);
            dup2(pipe2[1], STDOUT_FILENO);
            close(pipe1[1]);
            close(pipe2[0]);
            execlp("grep", "grep", argv[1], NULL);
            perror("execlp grep");
            exit(1);
        }
    } else {
        // Parent runs "cat scores"
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe2[1]);
        execlp("cat", "cat", "scores", NULL);
        perror("execlp cat");
        exit(1);
    }

    return 0;
}
