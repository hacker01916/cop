/**Q.1 Write the simulation program for demand paging and show the page  
scheduling and total number of page faults according the MFU page 
replacement algorithm. Assume the memory of n frames. 
Reference String: 8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2 */


#include <stdio.h>

#define MAX 100

int main()
{
    int pages[] = {8, 5, 7, 8, 5, 2, 3,
                   7, 3, 5, 9, 4, 6, 2};

    int n = 14;
    int frames[MAX], freq[MAX];
    int f, i, j, faults = 0;
    int found, victim, max;

    printf("Enter number of frames: ");
    scanf("%d", &f);

    if (f <= 0 || f > MAX)
    {
        printf("Invalid number of frames!\n");
        return 1;
    }

    // Initialize frames and frequency counters
    for (i = 0; i < f; i++)
    {
        frames[i] = -1;
        freq[i] = 0;
    }

    printf("\nMFU Page Replacement Algorithm\n");
    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        // Check whether page is present
        for (j = 0; j < f; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                freq[j]++;
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

            // If memory is full, find MFU page
            if (victim == -1)
            {
                max = freq[0];
                victim = 0;

                for (j = 1; j < f; j++)
                {
                    if (freq[j] > max)
                    {
                        max = freq[j];
                        victim = j;
                    }
                }
            }

            // Replace page and initialize frequency
            frames[victim] = pages[i];
            freq[victim] = 1;

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


/**Q.2 Write a program that demonstrates the use of nice() system call.  
After a child process is  started using fork(), assign higher priority to the  
child using nice() system call.            */



#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <errno.h>

int main()
{
    pid_t pid;
    int nice_value;

    // Display parent process details
    nice_value = getpriority(PRIO_PROCESS, 0);

    printf("Parent Process\n");
    printf("Parent PID: %d\n", getpid());
    printf("Parent Nice Value: %d\n", nice_value);

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }

    else if (pid == 0)
    {
        // Child process
        printf("\nChild Process\n");
        printf("Child PID: %d\n", getpid());

        // Increase child nice value
        errno = 0;

        if (nice(10) == -1 && errno != 0)
        {
            perror("Nice failed");
            exit(1);
        }

        // Display updated nice value
        nice_value = getpriority(PRIO_PROCESS, 0);

        printf("Updated Child Nice Value: %d\n",
               nice_value);

        printf("Child process completed.\n");
        exit(0);
    }

    else
    {
        // Parent process
        wait(NULL);

        printf("\nParent process completed.\n");
    }

    return 0;
}