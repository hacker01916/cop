/***Q.1) Write a C Menu driven Program to implement following functionality 
a) Accept Available 
b) Display Allocation, Max 
c) Display the contents of need matrix 
d) Display Available 
 
Process Allocation Max Available 
 A B C A B C A B C 
P0 2 3 2 9 7 5 3 3 2 
P1 4 0 0 5 2 2    
P2 5 0 4 1 0 4    
P3 4 3 3 4 4 4    
P4 2 2 4 6 5 5    
  */
#include <stdio.h>
#define MAX_P 10
#define MAX_R 10

int main()
{
    int n, r;
    int allocation[MAX_P][MAX_R];
    int max[MAX_P][MAX_R];
    int need[MAX_P][MAX_R];
    int available[MAX_R];
    int finish[MAX_P] = {0};
    int safeSequence[MAX_P];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &r);

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Maximum Matrix
    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available
    printf("\nEnter Available Resources:\n");
    for (int j = 0; j < r; j++)
    {
        scanf("%d", &available[j]);
    }

    // Calculate Need Matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Display Allocation Matrix
    printf("\n--- Allocation Matrix ---\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t", i);
        for (int j = 0; j < r; j++)
        {
            printf("%d\t", allocation[i][j]);
        }
        printf("\n");
    }

    // Display Max Matrix
    printf("\n--- Max Matrix ---\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t", i);
        for (int j = 0; j < r; j++)
        {
            printf("%d\t", max[i][j]);
        }
        printf("\n");
    }

    // Display Need Matrix
    printf("\n--- Need Matrix ---\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t", i);
        for (int j = 0; j < r; j++)
        {
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }

    // Display Available
    printf("\n--- Available Resources ---\n");
    for (int j = 0; j < r; j++)
    {
        printf("%d\t", available[j]);
    }
    printf("\n");

    // Banker's Algorithm
    int count = 0;

    while (count < n)
    {
        int found = 0;

        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int possible = 1;

                for (int j = 0; j < r; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if (possible)
                {
                    for (int j = 0; j < r; j++)
                    {
                        available[j] += allocation[i][j];
                    }

                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if (!found)
        {
            printf("\nSystem is NOT in a safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE state.\n");

    printf("Safe Sequence: ");

    for (int i = 0; i < n; i++)
    {
        printf("P%d", safeSequence[i]);

        if (i != n - 1)
            printf(" -> ");
    }

    printf("\n");

    return 0;
}




/**Q.2 Write a C program that behaves like a shell which displays the command    
prompt ‘$’. It accepts the command, tokenize the command line and  
execute it  by creating the child process. Also implement the additional 
 command ‘count’ as 
a. $ count c filename: It will display the number of characters in   
given file 
b. $ count w filename: It will display the number of words in given   
file  
c. $ count l filename: It will display the number of lines in given    
file   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100

void countFile(char option, char *filename)
{
    FILE *fp;
    int ch;
    int characters = 0;
    int words = 0;
    int lines = 0;
    int inWord = 0;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror("File cannot be opened");
        return;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        characters++;

        if (ch == '\n')
            lines++;

        if (ch == ' ' || ch == '\n' || ch == '\t')
        {
            inWord = 0;
        }
        else if (inWord == 0)
        {
            words++;
            inWord = 1;
        }
    }

    fclose(fp);

    if (option == 'c')
        printf("Number of characters: %d\n", characters);

    else if (option == 'w')
        printf("Number of words: %d\n", words);

    else if (option == 'l')
        printf("Number of lines: %d\n", lines);

    else
        printf("Invalid count option\n");
}

int main()
{
    char command[MAX];
    char *args[20];
    int status;

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        fgets(command, MAX, stdin);

        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0)
            continue;

        // Tokenize command
        int i = 0;
        char *token = strtok(command, " ");

        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;

        // Exit shell
        if (strcmp(args[0], "exit") == 0)
        {
            printf("Exiting shell...\n");
            break;
        }

        // count command
        if (strcmp(args[0], "count") == 0)
        {
            if (i != 3)
            {
                printf("Usage: count c/w/l filename\n");
                continue;
            }

            countFile(args[1][0], args[2]);
            continue;
        }

        // Create child process
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
        }
        else if (pid == 0)
        {
            // Child process
            execvp(args[0], args);

            perror("Command execution failed");
            exit(1);
        }
        else
        {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}