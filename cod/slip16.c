/**Q.1 Write the simulation program to implement demand paging and show the page  
scheduling and total number of page faults according to the LRU  
(using counter method) page replacement algorithm. Assume the memory of 
n frames. 
Reference String : 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2      */


#include <stdio.h>

#define MAX 100

int main()
{
    int pages[] = {3, 5, 7, 2, 5, 1, 2,
                   3, 1, 5, 3, 1, 6, 2};

    int n = 14, frames[MAX], counter[MAX];
    int f, i, j, time = 0, faults = 0;
    int found, victim, min;

    printf("Enter number of frames: ");
    scanf("%d", &f);

    if (f <= 0 || f > MAX)
    {
        printf("Invalid number of frames!\n");
        return 1;
    }

    // Initialize frames and counters
    for (i = 0; i < f; i++)
    {
        frames[i] = -1;
        counter[i] = 0;
    }

    printf("\nLRU Page Replacement (Counter Method)\n");
    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++)
    {
        found = 0;
        time++;

        // Check whether page is present
        for (j = 0; j < f; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                counter[j] = time;
                break;
            }
        }

        if (found)
        {
            printf("%d\t", pages[i]);

            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frames[j]);
            }

            printf("\tHit\n");
        }
        else
        {
            faults++;

            // Find an empty frame
            victim = -1;

            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                {
                    victim = j;
                    break;
                }
            }

            // If memory is full, find least recently used page
            if (victim == -1)
            {
                min = counter[0];
                victim = 0;

                for (j = 1; j < f; j++)
                {
                    if (counter[j] < min)
                    {
                        min = counter[j];
                        victim = j;
                    }
                }
            }

            // Replace page and update counter
            frames[victim] = pages[i];
            counter[victim] = time;

            printf("%d\t", pages[i]);

            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frames[j]);
            }

            printf("\tPage Fault\n");
        }
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}

/**Q.2 Write a C program that behaves like a shell which displays the command    
[15 Marks] 
prompt ‘$’. It accepts the command, tokenize the command line and execute it  
by creating the child process. Also implement the additional command ‘count’ as 
a $ count c filename: It will display the number of characters in   
given  file 
b $ count w filename: It will display the number of words in given   
file  
c $ count l filename: It will display the number of lines in given  file   */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX 100

// Function to count characters, words and lines
void count_file(char option, char filename[])
{
    FILE *fp;
    int ch, characters = 0, words = 0, lines = 0;
    int in_word = 0;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror("File opening failed");
        return;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        characters++;

        if (ch == '\n')
            lines++;

        if (isspace((unsigned char)ch))
        {
            in_word = 0;
        }
        else if (!in_word)
        {
            words++;
            in_word = 1;
        }
    }

    fclose(fp);

    if (option == 'c')
        printf("Number of characters = %d\n", characters);

    else if (option == 'w')
        printf("Number of words = %d\n", words);

    else if (option == 'l')
        printf("Number of lines = %d\n", lines);

    else
        printf("Invalid count option!\n");
}

int main()
{
    char command[MAX];
    char *args[20];
    char *token;
    pid_t pid;
    int i;

    while (1)
    {
        printf("\nMyShell> ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        // Tokenize command
        i = 0;
        token = strtok(command, " \t");

        while (token != NULL && i < 19)
        {
            args[i++] = token;
            token = strtok(NULL, " \t");
        }

        args[i] = NULL;

        if (args[0] == NULL)
            continue;

        // Exit command
        if (strcmp(args[0], "exit") == 0)
            break;

        // Custom count command
        if (strcmp(args[0], "count") == 0)
        {
            if (args[1] == NULL || args[2] == NULL)
            {
                printf("Usage: count c|w|l filename\n");
                continue;
            }

            if (strlen(args[1]) != 1)
            {
                printf("Invalid count option!\n");
                continue;
            }

            count_file(args[1][0], args[2]);
            continue;
        }

        // Create child process
        pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
        }
        else if (pid == 0)
        {
            // Execute command in child
            execvp(args[0], args);

            perror("Command execution failed");
            exit(1);
        }
        else
        {
            // Parent waits for child
            waitpid(pid, NULL, 0);
        }
    }

    printf("Shell terminated.\n");

    return 0;
}