#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    char *my_argv[4];
    int   null_fd;
    pid_t pid;

    // Check argument count
    if (argc != 2) {
        fprintf(stderr, "Start a shell command as a detached process\n");
        fprintf(stderr, "usage: %s <command>\n", argv[0]);
        return 1;
    }

    // Create a new process
    pid = fork();
    if (pid == -1) {
        return 1;
    }

    if (pid == 0) {
        // Become the session leader
        if (setsid() == -1) {
            return 1;
        }

        // Replace the standard streams
        null_fd = open("/dev/null", O_RDWR);
        if (null_fd == -1) {
            return 1;
        }
        dup2(null_fd, 0);
        dup2(null_fd, 1);
        dup2(null_fd, 2);
        close(null_fd);

        // Execute the given command using sh(1)
        my_argv[0] = "/bin/sh";
        my_argv[1] = "-c";
        my_argv[2] = argv[1];
        my_argv[3] = NULL;
        if (execve(my_argv[0], my_argv, envp) != 0) {
            return 1;
        }
    }

    return 0;
}
