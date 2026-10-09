/**Q.1 Write the program to simulate Round Robin (RR) scheduling. The arrival  
time and first CPU-burst for different n number of processes should be  
input to the algorithm. Also give the time quantum as input. The next CPU  
burst should be generated randomly. The output should give Gantt chart, 
turnaround time and waiting time for each process. Also find the average  
waiting time and turnaround time.   */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20
#define MAX_GANTT 10000

int main()
{
    int n, tq, i, time = 0, completed = 0;
    int at[MAX], bt[MAX], rem[MAX];
    int ct[MAX], tat[MAX], wt[MAX];

    int queue[MAX_GANTT];
    int gantt[MAX_GANTT], gantt_time[MAX_GANTT];

    int front = 0, rear = 0;
    int in_queue[MAX] = {0};
    int g = 0, p, exec_time;

    float avg_wt = 0, avg_tat = 0;

    srand(time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of processes!\n");
        return 1;
    }

    for (i = 0; i < n; i++)
    {
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        if (at[i] < 0)
        {
            printf("Invalid arrival time!\n");
            return 1;
        }

        bt[i] = rand() % 10 + 1;
        rem[i] = bt[i];

        printf("Burst time of P%d = %d\n", i + 1, bt[i]);
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    if (tq <= 0)
    {
        printf("Invalid time quantum!\n");
        return 1;
    }

    // Round Robin Scheduling
    while (completed < n)
    {
        // Add newly arrived processes
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && !in_queue[i] && rem[i] > 0)
            {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }

        // CPU idle if queue is empty
        if (front == rear)
        {
            gantt[g] = -1;
            gantt_time[g] = time;
            g++;

            time++;
            continue;
        }

        // Select process from ready queue
        p = queue[front++];

        gantt[g] = p;
        gantt_time[g] = time;
        g++;

        if (rem[p] > tq)
            exec_time = tq;
        else
            exec_time = rem[p];

        time += exec_time;
        rem[p] -= exec_time;

        // Add processes that arrived during execution
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && !in_queue[i] && rem[i] > 0)
            {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }

        if (rem[p] == 0)
        {
            ct[p] = time;
            completed++;
        }
        else
        {
            // Reinsert unfinished process
            queue[rear++] = p;
        }
    }

    gantt_time[g] = time;

    // Calculate TAT and WT
    for (i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    // Display Gantt Chart
    printf("\nGantt Chart:\n");

    for (i = 0; i < g; i++)
    {
        if (gantt[i] == -1)
            printf("| Idle ");
        else
            printf("| P%d ", gantt[i] + 1);
    }

    printf("|\n");

    for (i = 0; i <= g; i++)
        printf("%-6d", gantt_time[i]);

    // Display process table
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i],
               ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f",
           avg_wt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avg_tat / n);

    return 0;
}


/**Q.2 Implement the C program that accepts an integer array. Main function  
forks child process. Parent process sorts an integer array and passes  
the sorted array to child process through the command line arguments of 
execve() system call. The child process uses execve() system call to load new  
program that uses this sorted array for performing the binary search the  
particular item in the array. */

/**Program 1: Parent Process (parent.c) */

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

    char *args[MAX + 4];
    char numbers[MAX][20];
    char key_str[20];

    printf("Enter number of integers: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of integers!\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter element to search: ");
    scanf("%d", &key);

    // Bubble Sort
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

    // Convert sorted array into strings
    args[0] = "./search";

    for (i = 0; i < n; i++)
    {
        sprintf(numbers[i], "%d", a[i]);
        args[i + 1] = numbers[i];
    }

    sprintf(key_str, "%d", key);
    args[n + 1] = key_str;
    args[n + 2] = NULL;

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }

    else if (pid == 0)
    {
        // Child loads new program
        execve("./search", args, NULL);

        perror("execve failed");
        exit(1);
    }

    else
    {
        // Parent waits for child
        wait(NULL);

        printf("\nParent process completed.\n");
    }

    return 0;
}





/**Program 2: Child Process (search.c) */


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a[100];
    int n, key;
    int low, high, mid;
    int i, found = 0;

    // Validate command-line arguments
    if (argc < 3 || argc > 102)
    {
        printf("Invalid arguments!\n");
        return 1;
    }

    n = argc - 2;

    // Convert arguments into integers
    for (i = 0; i < n; i++)
        a[i] = atoi(argv[i + 1]);

    key = atoi(argv[argc - 1]);

    printf("\nChild Process (Binary Search)\n");

    printf("Sorted Array: ");

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\nSearching for: %d\n", key);

    // Binary Search
    low = 0;
    high = n - 1;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

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
        printf("Element found at position %d\n", mid + 1);
    else
        printf("Element not found!\n");

    return 0;
}

/**gcc parent.c -o parent
gcc search.c -o search
./parent */