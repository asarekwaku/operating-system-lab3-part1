#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd1[2]; // Pipe 1: parent → child
    int fd2[2]; // Pipe 2: child → parent
    char fixed_str1[] = "howard.edu";
    char fixed_str2[] = "gobison.org";
    char input_str[100];
    pid_t p;

    // Create pipes
    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    p = fork();

    if (p < 0) {
        perror("Fork failed");
        exit(1);
    }

    // ===========================
    // PARENT PROCESS (P1)
    // ===========================
    else if (p > 0) {
        char concat_str[200];

        close(fd1[0]); // Close read end of pipe 1
        close(fd2[1]); // Close write end of pipe 2

        printf("Other string is: howard.edu\n");
        printf("Input : ");
        scanf("%s", input_str);

        // Write to child
        write(fd1[1], input_str, strlen(input_str) + 1);
        close(fd1[1]); // Done writing

        // Wait for child to finish processing
        wait(NULL);

        // Read back the string from the child
        read(fd2[0], concat_str, sizeof(concat_str));

        // Append "gobison.org"
        strcat(concat_str, fixed_str2);

        printf("Output : %s\n", concat_str);

        close(fd2[0]);
    }

    // ===========================
    // CHILD PROCESS (P2)
    // ===========================
    else {
        char received_str[200];
        char user_str[100];

        close(fd1[1]); // Close write end of pipe 1
        close(fd2[0]); // Close read end of pipe 2

        // Read from parent
        read(fd1[0], received_str, sizeof(received_str));

        // Append "howard.edu"
        strcat(received_str, fixed_str1);
        printf("Output : %s\n", received_str);

        // Ask for second input
        printf("Input : ");
        scanf("%s", user_str);

        // Append second input
        strcat(received_str, user_str);

        // Send back to parent
        write(fd2[1], received_str, strlen(received_str) + 1);

        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    }

    return 0;
}
