#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

/**
 * Executes "cat scores | grep Lakers"
 */

int main(void)
{
    int pipefd[2];
    pid_t pid;

    char *cat_args[] = {"cat", "scores", NULL};
    char *grep_args[] = {"grep", "Lakers", NULL};

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    // Child → grep
    if (pid == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        execvp("grep", grep_args);
        perror("execvp grep failed");
        exit(1);
    }
    // Parent → cat
    else {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        execvp("cat", cat_args);
        perror("execvp cat failed");
        exit(1);
    }

    return 0;
}
