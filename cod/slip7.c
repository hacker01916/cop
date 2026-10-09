/**--------------------------------------------------------------------------------------------------- 
Q.1 Consider the following snapshot of the system. 
 
Process Allocation Max Available 
 A B C D A B C D A B C D 
P0 2 0 0 1 4 2 1 2 3 3 2 1 
P1 3 1 2 1 5 2 5 2     
P2 2 1 0 3 2 3 1 6     
P3 1 3 1 2 1 4 2 4     
P4 1 4 3 2 3 6 6 5     
Using Resource –Request algorithm to Check whether the current system is in  
safe state or not  */

#include <stdio.h>

int main()
{
    int n = 5, m = 4;

    int allocation[5][4] = {
        {2, 0, 0, 1},
        {3, 1, 2, 1},
        {2, 1, 0, 3},
        {1, 3, 1, 2},
        {1, 4, 3, 2}
    };

    int max[5][4] = {
        {4, 2, 1, 2},
        {5, 2, 5, 2},
        {2, 3, 1, 6},
        {1, 4, 2, 4},
        {3, 6, 6, 5}
    };

    int available[4] = {3, 3, 2, 1};

    int need[5][4];
    int finish[5] = {0};
    int work[4];
    int safeSequence[5];

    int i, j, count = 0;

    /* Calculate Need Matrix */
    printf("Need Matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    /* Initialize Work */
    for (j = 0; j < m; j++)
    {
        work[j] = available[j];
    }

    /* Safety Algorithm */
    while (count < n)
    {
        int found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int possible = 1;

                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if (possible)
                {
                    for (j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            break;
        }
    }

    if (count == n)
    {
        printf("\nSystem is in SAFE STATE.\n");

        printf("Safe Sequence: ");

        for (i = 0; i < n; i++)
        {
            printf("P%d", safeSequence[i]);

            if (i != n - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is NOT in SAFE STATE.\n");
    }

    return 0;
}



/**  Q2. Write a program that demonstrates the use of nice() system call. After a       
    child process is started using fork(), assign higher priority to the child using       
    nice()system call.*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    printf("Parent Process Started\n");
    printf("Parent PID = %d\n", getpid());

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    else if (pid == 0)
    {
        // Child process
        int oldNice, newNice;

        printf("\nChild Process Started\n");
        printf("Child PID = %d\n", getpid());

        oldNice = nice(0);

        printf("Child Initial Nice Value = %d\n", oldNice);

        // Increase priority by decreasing nice value
        errno = 0;

        newNice = nice(-5);

        if (newNice == -1 && errno != 0)
        {
            perror("nice");
        }
        else
        {
            printf("Child Nice Value after nice(-5) = %d\n",
                   newNice);
            printf("Child priority has been increased.\n");
        }

        printf("Child is executing...\n");

        for (long i = 0; i < 500000000; i++)
        {
            // CPU intensive work
        }

        printf("Child Process Finished\n");
    }

    else
    {
        // Parent process
        printf("\nParent waiting for child...\n");

        wait(NULL);

        printf("Child Process Completed.\n");
        printf("Parent Process Finished.\n");
    }

    return 0;
}