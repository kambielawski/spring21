/**
 * @file execute.c
 *
 * @brief Implements interface functions between Quash and the environment and
 * functions that interpret an execute commands.
 *
 * @note As you add things to this file you may want to change the method signature
 */

#include "execute.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "quash.h"

// Remove this and all expansion calls to it
/**
 * @brief Note calls to any function that requires implementation
 */
#define IMPLEMENT_ME()                                                  \
    fprintf(stderr, "IMPLEMENT ME: %s(line %d): %s()\n", __FILE__, __LINE__, __FUNCTION__)

/***************************************************************************
 * Interface Functions
 ***************************************************************************/

// Return a string containing the current working directory.
char* get_current_directory(bool* should_free) {
    // TODO: Get the current working directory. This will fix the prompt path.

    // TODO: use a reliable size, not 100
    char * wd_buf = getcwd(NULL, 100);

    // Change this to true if necessary
    *should_free = true;

    return wd_buf;
}

// Returns the value of an environment variable env_var
const char* lookup_env(const char* env_var) {
    return getenv(env_var);
}

// Check the status of background jobs
void check_jobs_bg_status(JobQueue *job_queue) {
    // TODO: Check on the statuses of all processes belonging to all background
    // jobs. This function should remove jobs from the jobs queue once all
    // processes belonging to a job have completed.

    size_t arr_size;
    Job *job_arr = as_array_JobQueue(job_queue, &arr_size); 

    int last_pid;
    bool complete[arr_size];
    
    // iterate over jobs and check if last process is complete
    for (int j = 0; j < arr_size; j++) {
        last_pid = peek_front_ProcessQueue(&(job_arr[j].pid_queue)).pid;
        complete[j] = true;
        // check if last process exists
        if (kill(last_pid, 0) == 0) {
            complete[j] = false;
        } else {
            // if job complete, call complete for job
            print_job_bg_complete(job_arr[j].job_id, last_pid, job_arr[j].cmd_str);
        }
    }

    // TODO: reinitialize job queue 
    destroy_JobQueue(job_queue);
    *job_queue = new_JobQueue(1);
    for (int i = 0; i < arr_size; i++) {
        if (!complete[i])
            push_back_JobQueue(job_queue, job_arr[i]);
    }

    job_queue = NULL;
    free(job_arr);
}

// Prints the job id number, the process id of the first process belonging to
// the Job, and the command string associated with this job
void print_job(int job_id, pid_t pid, const char* cmd) {
    printf("[%d]\t%8d\t%s\n", job_id, pid, cmd);
    fflush(stdout);
}

// Prints a start up message for background processes
void print_job_bg_start(int job_id, pid_t pid, const char* cmd) {
    printf("Background job started: ");
    print_job(job_id, pid, cmd);
}

// Prints a completion message followed by the print job
void print_job_bg_complete(int job_id, pid_t pid, const char* cmd) {
    printf("Completed: \t");
    print_job(job_id, pid, cmd);
}

/***************************************************************************
 * Functions to process commands
 ***************************************************************************/
// Run a program reachable by the path environment variable, relative path, or
// absolute path
void run_generic(GenericCommand cmd) {
    // Execute a program with a list of arguments. The `args` array is a NULL
    // terminated (last string is always NULL) list of strings. The first element
    // in the array is the executable
    char* exec = cmd.args[0];
    char** args = cmd.args;

    execvp(exec, args); 

    perror("ERROR: Failed to execute program");
}

// Print strings
void run_echo(EchoCommand cmd) {
    // Print an array of strings. The args array is a NULL terminated (last
    // string is always NULL) list of strings.
    char** str = cmd.args;

    // TODO: Implement echo
    for (int i = 0; (str[i] != NULL); i++)
        printf("%s ", str[i]);
    printf("\n");

    // free str
    for (int i = 0; (str[i] != NULL); i++)
        str[i] = NULL;
    str = NULL;

    // Flush the buffer before returning
    fflush(stdout);
}

// Sets an environment variable
void run_export(ExportCommand cmd) {
    // Write an environment variable
    const char* env_var = cmd.env_var;
    const char* val = cmd.val;

    setenv(env_var, val, 1);
}

// Changes the current working directory
void run_cd(CDCommand cmd) {
    // Get the directory name
    const char* dir = cmd.dir;

    // Check if the directory is valid
    if (dir == NULL) {
        perror("ERROR: Failed to resolve path");
        return;
    }

    char *newdir = realpath(dir, NULL);

    // TODO: Change directory
    if (chdir(newdir) < 0)
        fprintf(stderr, "Failed to change directory\n");

    // TODO: Update the PWD environment variable to be the new current working
    // directory and optionally update OLD_PWD environment variable to be the old
    // working directory.

    // update OLD_PWD env var to old PWD
    setenv("OLD_PWD", getenv("PWD"), 1);

    char *wd_buf = getcwd(NULL, 256);
    setenv("PWD", wd_buf, 1);

    free(newdir);
    free(wd_buf);
}

// Sends a signal to all processes contained in a job
void run_kill(KillCommand cmd) {
    int signal = cmd.sig;
    int job_id = cmd.job;

    JobQueue *job_queue = get_job_queue();
    size_t arr_size;
    Job *job_arr = as_array_JobQueue(job_queue, &arr_size);

    int index_killed = -1;

    // find and kill process
    for (int j = 0; j < arr_size; j++) {
        if (job_arr[j].job_id == job_id) {
            // kill all processes
            print_job_bg_complete(job_arr[j].job_id, peek_front_ProcessQueue(&(job_arr[j].pid_queue)).pid, job_arr[j].cmd_str);
            while (!is_empty_ProcessQueue(&(job_arr[j].pid_queue))) {
                // free up cmd_str
                free(job_arr[j].cmd_str);
                kill(pop_front_ProcessQueue(&(job_arr[j].pid_queue)).pid, signal);
            }
            destroy_ProcessQueue(&(job_arr[j].pid_queue));
            // destroy process queue 
            index_killed = j;
        }
    }

    // reinitialize job queue w/o killed process
    *job_queue = new_JobQueue(1);
    for (int i = 0; i < arr_size; i++) {
        if (i != index_killed)
            push_back_JobQueue(job_queue, job_arr[i]);
    }

    // mem cleanup
    job_queue = NULL;
    free(job_arr);

}


// Prints the current working directory to stdout
void run_pwd() {

    // TODO: use reliable size instead of 100
    char *wd_buf = getcwd(NULL, 100);
    printf("%s\n", wd_buf);

    // mem cleanup
    free(wd_buf);

    // Flush the buffer before returning
    fflush(stdout);
}

// Prints all background jobs currently in the job list to stdout
void run_jobs() {
    JobQueue *job_queue = get_job_queue();
    size_t arr_size;

    // get the queue as an array for iteration
    Job *job_arr = as_array_JobQueue(job_queue, &arr_size);
    for (int i = 0; i < arr_size; i++) {
        print_job(job_arr[i].job_id, peek_front_ProcessQueue(&(job_arr[i].pid_queue)).pid, job_arr[i].cmd_str);
    }

    // as_array_JobQueue has invalidated the queue, so we must reinitialize it
    // TODO: reinitialize job queue 
    *job_queue = new_JobQueue(1);
    for (int i = 0; i < arr_size; i++) {
        push_back_JobQueue(job_queue, job_arr[i]);
    }

    // mem cleanup
    job_queue = NULL;
    free(job_arr);

    // Flush the buffer before returning
    fflush(stdout);
}

/***************************************************************************
 * Functions for command resolution and process setup
 ***************************************************************************/

/**
 * @brief A dispatch function to resolve the correct @a Command variant
 * function for child processes.
 *
 * This version of the function is tailored to commands that should be run in
 * the child process of a fork.
 *
 * @param cmd The Command to try to run
 *
 * @sa Command
 */
void child_run_command(Command cmd) {
    CommandType type = get_command_type(cmd);

    switch (type) {
        case GENERIC:
            run_generic(cmd.generic);
            break;

        case ECHO:
            run_echo(cmd.echo);
            break;

        case PWD:
            run_pwd();
            break;

        case JOBS:
            run_jobs();
            break;

        case EXPORT:
            run_export(cmd.export);
            break;

        case CD:
        case KILL:
        case EXIT:
        case EOC:
            break;

        default:
            fprintf(stderr, "Unknown command type: %d\n", type);
    }
}

/**
 * @brief A dispatch function to resolve the correct @a Command variant
 * function for the quash process.
 *
 * This version of the function is tailored to commands that should be run in
 * the parent process (quash).
 *
 * @param cmd The Command to try to run
 *
 * @sa Command
 */
void parent_run_command(Command cmd) {
    CommandType type = get_command_type(cmd);

    switch (type) {
        case EXPORT:
            run_export(cmd.export);
            break;

        case CD:
            run_cd(cmd.cd);
            break;

        case KILL:
            run_kill(cmd.kill);
            break;

        case GENERIC:
        case ECHO:
        case PWD:
        case JOBS:
        case EXIT:
        case EOC:
            break;

        default:
            fprintf(stderr, "Unknown command type: %d\n", type);
    }
}

/**
 * @brief Creates one new process centered around the @a Command in the @a
 * CommandHolder setting up redirects and pipes where needed
 *
 * @note Processes are not the same as jobs. A single job can have multiple
 * processes running under it. This function creates a process that is part of a
 * larger job.
 *
 * @note Not all commands should be run in the child process. A few need to
 * change the quash process in some way
 *
 * @param holder The CommandHolder to try to run
 *
 * @sa Command CommandHolder
 */
void create_process(CommandHolder holder, int pipes[][2], int num_cmds, int process_index, Job *job) {
    // Read the flags field from the parser
    bool p_in  = holder.flags & PIPE_IN;
    bool p_out = holder.flags & PIPE_OUT;
    bool r_in  = holder.flags & REDIRECT_IN;
    bool r_out = holder.flags & REDIRECT_OUT;
    bool r_app = holder.flags & REDIRECT_APPEND; // This can only be true if r_out
    // is true

    // pipe indices
    int inpipe_index = process_index - 1;
    int outpipe_index = process_index;

    // fork process
    pid_t fork_pid;

    // set up redirect files
    int r_in_fd;
    int r_out_fd;

    // setup file descriptors
    if (r_out) {
        if (r_app) 
            r_out_fd = open(holder.redirect_out, O_WRONLY | O_CREAT | O_APPEND, 0666);
        else 
            r_out_fd = open(holder.redirect_out, O_WRONLY | O_CREAT, 0666);
    }
    if (r_in)
        r_in_fd = open(holder.redirect_in, O_RDONLY);

    // child process
    if ((fork_pid = fork()) == 0)
    {
        if (p_in) {
            // redirect read end of inpipe to stdin
            // dup2(pipes[inpipe][0], STDIN_FILENO);
            // close(pipes[inpipe][1]);
            dup2(pipes[inpipe_index][0], STDIN_FILENO);
            // close(pipes[inpipe_index][0]);
            close(pipes[inpipe_index][1]);
        } 
        if (p_out) {
            // redirect stdout to write end of pipe
            // dup2(pipes[outpipe][1], STDOUT_FILENO);
            // close(pipes[outpipe][0]);
            dup2(pipes[outpipe_index][1], STDOUT_FILENO);
            // close(pipes[outpipe_index][1]);
            close(pipes[outpipe_index][0]);
        }
        // close remaining pipes
        for (int i = 0; i < num_cmds; i++) {
            if (p_in && i == inpipe_index) continue;
            if (p_out && i == outpipe_index) continue;
            close(pipes[i][0]); close(pipes[i][1]);
        }

        if (r_in) {
            // redirect standard input of this command to file holder.redirect_in
            dup2(r_in_fd, STDIN_FILENO);
            close(r_in_fd);
        } 
        if (r_out) {
            // redirect stdout to file specified by holder.redirect_out 
            dup2(r_out_fd, STDOUT_FILENO);
            close(r_out_fd);
        }
        
        // TODO: somehow push child process to job's process queue
        pid_t child_pid = getpid();

        // execute stuff
        child_run_command(holder.cmd);

        exit(0);

    } else { 
        

        // push child process to back of pid_queue for job
        Process childproc = { fork_pid };
        push_back_ProcessQueue(&(job->pid_queue), childproc);

        // parent process
        parent_run_command(holder.cmd);
    }

    if (r_in) close(r_in_fd);
    if (r_out) close(r_out_fd);
    if (p_in) close(pipes[inpipe_index][0]);
    if (p_out) close(pipes[outpipe_index][1]);

}

int num_commands(CommandHolder* holders) {
    CommandHolder* temp = holders;
    int i;
    for (i = 0; (get_command_holder_type(temp[i]) != EOC); i++);
    temp = NULL;
    return i;
}

// Run a list of commands
void run_script(CommandHolder* holders) {
    if (holders == NULL)
        return;

    JobQueue *queue = get_job_queue();
    check_jobs_bg_status(queue);

    if (get_command_holder_type(holders[0]) == EXIT &&
            get_command_holder_type(holders[1]) == EOC) {
        end_main_loop();
        return;
    }

    CommandType type;

    // create new job 
    Job job;
    job.cmd_str = get_command_string();                  // assign command string
    job.pid_queue = new_ProcessQueue(1);                 // create process queue
    job.job_id = is_empty_JobQueue(queue) ? 1 : peek_back_JobQueue(queue).job_id + 1; 

    /* Initialize pipe array */
    int num_cmds = num_commands(holders);
    int pipes[num_cmds][2];
    for (int i = 0; i < num_cmds; i++)
        pipe(pipes[i]);

    // Run all commands in the `holder` array
    for (int i = 0; (type = get_command_holder_type(holders[i])) != EOC; ++i) {
        create_process(holders[i], pipes, num_cmds, i, &job);
    }

    if (!(holders[0].flags & BACKGROUND)) {
        // Not a background Job
        // TODO: Wait for all processes under the job to complete
        pid_t wait_pid = peek_back_ProcessQueue(&(job.pid_queue)).pid;
        waitpid(wait_pid, NULL, 0);

        free(job.cmd_str);
        destroy_ProcessQueue(&(job.pid_queue));
    }
    else {
        // A background job.
        
        // push new job to job queue
        push_back_JobQueue(queue, job);

        print_job_bg_start(job.job_id, peek_front_ProcessQueue(&(job.pid_queue)).pid, job.cmd_str);
    }
}
