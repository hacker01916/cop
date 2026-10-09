/**Q.1 Write a C program to illustrate the concept of orphan process. Parent process 
creates a child and terminates before child has finished its task. So child 
process becomes orphan process. (Use fork(), sleep(), getpid(), getppid()  */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }

    else if (pid == 0)
    {
        // Child process
        printf("Child process started.\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        printf("Child is sleeping...\n");
        sleep(5);

        // Parent has terminated by now
        printf("\nAfter parent termination:\n");
        printf("Child PID  : %d\n", getpid());
        printf("New Parent PID : %d\n", getppid());

        printf("Child process completed.\n");
    }

    else
    {
        // Parent process
        printf("Parent process started.\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        printf("Parent is terminating...\n");
        exit(0);
    }

    return 0;
}


/**Q.2 Write a C program that behaves like a shell which displays the command 
prompt ‘$’. It accepts the command, tokenize the command line and  
execute it by creating the child process. Also implement the additional 
command  ‘search’ as   
a. $ search   f filename pattern : It will search the first occurrence of 
pattern in the given file  
b. $ search a filename pattern : It will search all the occurrence of 
pattern in the given file  
c. $ search c filename pattern : It will count the number of occurrence 
of pattern in the given file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 100
#define SIZE 1024

// Search first occurrence
void searchA(char *filename, char *pattern)
{
    FILE *fp;
    char line[SIZE];
    int line_no = 0;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror("File opening failed");
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        line_no++;

        if (strstr(line, pattern) != NULL)
        {
            printf("First occurrence found at line %d:\n", line_no);
            printf("%s", line);
            fclose(fp);
            return;
        }
    }

    printf("Pattern not found.\n");

    fclose(fp);
}

// Search all occurrences
void searchB(char *filename, char *pattern)
{
    FILE *fp;
    char line[SIZE];
    int line_no = 0;
    int found = 0;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror("File opening failed");
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        line_no++;

        if (strstr(line, pattern) != NULL)
        {
            printf("Occurrence at line %d: %s",
                   line_no, line);
            found = 1;
        }
    }

    if (!found)
        printf("Pattern not found.\n");

    fclose(fp);
}

// Count occurrences
void searchC(char *filename, char *pattern)
{
    FILE *fp;
    char line[SIZE];
    char *pos;
    int count = 0;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror("File opening failed");
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        pos = line;

        while ((pos = strstr(pos, pattern)) != NULL)
        {
            count++;
            pos += strlen(pattern);
        }
    }

    printf("Number of occurrences = %d\n", count);

    fclose(fp);
}

// Handle search command
void searchCommand(char *args[])
{
    if (args[1] == NULL ||
        args[2] == NULL ||
        args[3] == NULL)
    {
        printf("Usage: search a/b/c filename pattern\n");
        return;
    }

    if (strcmp(args[1], "a") == 0)
    {
        searchA(args[2], args[3]);
    }
    else if (strcmp(args[1], "b") == 0)
    {
        searchB(args[2], args[3]);
    }
    else if (strcmp(args[1], "c") == 0)
    {
        searchC(args[2], args[3]);
    }
    else
    {
        printf("Invalid search option.\n");
    }
}

int main()
{
    char command[SIZE];
    char *args[MAX];
    int argc;
    pid_t pid;

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        // Remove newline
        command[strcspn(command, "\n")] = '\0';

        // Ignore empty command
        if (strlen(command) == 0)
            continue;

        // Tokenize command
        argc = 0;

        args[argc] = strtok(command, " ");

        while (args[argc] != NULL && argc < MAX - 1)
        {
            argc++;
            args[argc] = strtok(NULL, " ");
        }

        args[argc] = NULL;

        // Exit shell
        if (strcmp(args[0], "exit") == 0)
        {
            printf("Exiting shell...\n");
            break;
        }

        // Handle search command
        if (strcmp(args[0], "search") == 0)
        {
            pid = fork();

            if (pid < 0)
            {
                perror("Fork failed");
            }
            else if (pid == 0)
            {
                searchCommand(args);
                exit(0);
            }
            else
            {
                wait(NULL);
            }
        }

        // Execute normal Linux commands
        else
        {
            pid = fork();

            if (pid < 0)
            {
                perror("Fork failed");
            }
            else if (pid == 0)
            {
                execvp(args[0], args);

                perror("Command execution failed");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
    }

    return 0;
}