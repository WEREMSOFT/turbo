#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <signal.h>
#include <stdarg.h>
#include <string.h>

typedef struct {
    pid_t pid;
    int stdout_fd;
} process_t;

/**
 * Starts a process and captures its stdout, forcing line buffering via stdbuf.
 * The child will automatically receive SIGTERM if the parent dies.
 * 
 * Usage: process_t p = process_start("./my_prog", "arg1", "arg2", NULL);
 * 
 * @param path The executable path or name.
 * @param ... NULL-terminated list of arguments (optional).
 * @return process_t structure. pid will be -1 on failure.
 */
process_t process_start(const char *path, ...);

/**
 * Polls for output. Returns bytes read, 0 if no data, -1 on EOF/Error.
 */
int process_poll_output(process_t p, char *buffer, size_t buffer_size);

/**
 * Explicitly kills the process.
 */
void process_kill(process_t p);

/**
 * Checks if the process is still running.
 * @return 1 if running, 0 if it has exited.
 */
int process_is_running(process_t p);

#endif // PROCESS_H
