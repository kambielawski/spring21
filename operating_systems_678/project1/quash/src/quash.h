/**
 * @file quash.h
 *
 * Quash essential functions and structures.
 */

#ifndef SRC_QUASH_H
#define SRC_QUASH_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "execute.h"
#include "deque.h"

typedef struct Process {
    pid_t pid;
} Process;

/* make a queue of pids */
IMPLEMENT_DEQUE_STRUCT(ProcessQueue, Process);
/* Define Process Queue functions */
PROTOTYPE_DEQUE(ProcessQueue, Process);

typedef struct Job {
    int job_id;         // Job ID
    ProcessQueue pid_queue;        // List of process IDs for all processes in job
    char *cmd_str;      // Initial command string of job
} Job;

/* Generate the JobQueue struct */
IMPLEMENT_DEQUE_STRUCT(JobQueue, Job);
/* Define the JobQueue functions */
PROTOTYPE_DEQUE(JobQueue, Job);

/**
 * @brief Holds information about the state and environment Quash is running in
 */
typedef struct QuashState {
  bool running;     /**< Indicates if Quash should keep accept more input */
  bool is_a_tty;    /**< Indicates if the shell is receiving input from a file
                     * or the command line */
  char* parsed_str; /**< Holds a string representing the parsed structure of the
                     * command input from the command line */
} QuashState;

JobQueue* get_job_queue();

/**
 * @brief Check if Quash is receiving input from the command line (TTY)
 *
 * @return True if stdin is a TTY false if stdin is not a TTY
 */
bool is_tty();

/**
 * @brief Get a deep copy of the current command string
 *
 * @note The free function must be called on the result eventually
 *
 * @return A copy of the command string
 */
char* get_command_string();

/**
 * @brief Query if quash should accept more input or not.
 *
 * @return True if Quash should accept more input and false otherwise
 */
bool is_running();

/**
 * @brief Causes the execution loop to end.
 */
void end_main_loop();

#endif // QUASH_H
