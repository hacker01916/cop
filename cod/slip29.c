/**Q.1 Implement the C program that accepts an integer array. Main function 
forks child process. Parent process sorts an integer array and passes the  
sorted array to child process through the command line arguments of 
execve() system call. The child process uses execve() system call to load new  
program that uses this sorted array for performing the binary search the 
particular item in the array */

/**Program 1: main.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 100

int main()
{
    int a[MAX], n, i, j, temp, key;
    pid_t pid;

    char *args[MAX + 3];
    char str[MAX][20];
    char key_str[20];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid size!\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter element to search: ");
    scanf("%d", &key);

    /* Bubble Sort */
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("\nSorted Array: ");

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    /*
     * Prepare arguments for execve()
     */
    args[0] = "./search";

    for (i = 0; i < n; i++)
    {
        sprintf(str[i], "%d", a[i]);
        args[i + 1] = str[i];
    }

    sprintf(key_str, "%d", key);
    args[n + 1] = key_str;
    args[n + 2] = NULL;

    /* Create child */
    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    else if (pid == 0)
    {
        /* Child process */
        execve("./search", args, NULL);

        perror("execve failed");
        exit(1);
    }

    else
    {
        /* Parent waits for child */
        wait(NULL);

        printf("\nParent process completed.\n");
    }

    return 0;
}


/**Program 2: search.c */


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a[100];
    int n, key;
    int low, high, mid;
    int i;
    int found = 0;

    /*
     * Last argument is search key.
     * Remaining arguments are array elements.
     */
    n = argc - 2;

    if (n <= 0)
    {
        printf("Invalid arguments!\n");
        return 1;
    }

    /* Convert command-line arguments to integers */
    for (i = 0; i < n; i++)
        a[i] = atoi(argv[i + 1]);

    key = atoi(argv[argc - 1]);

    printf("\nChild Process\n");
    printf("Searching for: %d\n", key);

    /* Binary Search */
    low = 0;
    high = n - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (a[mid] == key)
        {
            found = 1;
            break;
        }
        else if (a[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    if (found)
        printf("Element %d found at position %d\n",
               key, mid + 1);
    else
        printf("Element %d not found\n", key);

    return 0;
}

/**gcc search.c -o search
gcc main.c -o main
./main */





/**Q.2 Write the program to simulate FCFS CPU-scheduling. The arrival time  
and first CPU- burst for different n number of processes should be input  
to the algorithm. The next CPU-burst should be generated randomly. The  
output should give Gantt chart, turnaround time and waiting time for each  
process. Also find the average waiting time and turnaround time */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int main()
{
    int n;
    int at[MAX], bt[MAX], next_bt[MAX];
    int ct[MAX], tat[MAX], wt[MAX];

    int i, j, temp;
    int time = 0;

    float avg_wt = 0;
    float avg_tat = 0;

    srand(time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of processes!\n");
        return 1;
    }

    /* Input arrival time and first CPU burst */
    for (i = 0; i < n; i++)
    {
        printf("\nProcess P%d\n", i + 1);

        printf("Enter arrival time: ");
        scanf("%d", &at[i]);

        printf("Enter first CPU burst: ");
        scanf("%d", &bt[i]);

        /* Generate next CPU burst randomly */
        next_bt[i] = rand() % 10 + 1;
    }

    /*
     * FCFS requires processes to be ordered
     * according to arrival time.
     */
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (at[i] > at[j])
            {
                /* Swap arrival time */
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                /* Swap burst time */
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                /* Swap next burst */
                temp = next_bt[i];
                next_bt[i] = next_bt[j];
                next_bt[j] = temp;
            }
        }
    }

    /*
     * Calculate completion time.
     */
    for (i = 0; i < n; i++)
    {
        /* CPU remains idle until process arrives */
        if (time < at[i])
            time = at[i];

        time += bt[i];

        ct[i] = time;

        tat[i] = ct[i] - at[i];

        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    /* Gantt Chart */
    printf("\n\nGantt Chart:\n");
    printf(" ");

    for (i = 0; i < n; i++)
    {
        printf("--------");
    }

    printf("\n|");

    for (i = 0; i < n; i++)
    {
        printf("  P%d   |", i + 1);
    }

    printf("\n ");

    for (i = 0; i < n; i++)
    {
        printf("--------");
    }

    printf("\n");

    /* Display time values */
    printf("%d", at[0] > 0 ? 0 : at[0]);

    for (i = 0; i < n; i++)
    {
        printf("\t%d", ct[i]);
    }

    printf("\n");

    /* Process table */
    printf("\nProcess\tAT\tFirst BT\tNext BT\tCT\tTAT\tWT\n");
    printf("---------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               i + 1,
               at[i],
               bt[i],
               next_bt[i],
               ct[i],
               tat[i],
               wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f",
           avg_wt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avg_tat / n);

    return 0;
}