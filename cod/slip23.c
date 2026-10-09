/**Q.1   Implement the C program to accept n integers to be sorted. Main function  
creates child process using fork system call. Parent process sorts the integers 
using bubble sort and waits for child process using wait system call. Child  
process sorts the integers using insertion sort */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 100

// Bubble Sort for Parent Process
void bubbleSort(int a[], int n)
{
    int i, j, temp;

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
}

// Insertion Sort for Child Process
void insertionSort(int a[], int n)
{
    int i, j, key;

    for (i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

// Display Array
void display(int a[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main()
{
    int a[MAX], n, i;
    pid_t pid;

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

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }

    else if (pid == 0)
    {
        // Child Process
        printf("\nChild Process (Insertion Sort)\n");

        insertionSort(a, n);

        printf("Sorted Array: ");
        display(a, n);

        exit(0);
    }

    else
    {
        // Parent Process
        printf("\nParent Process (Bubble Sort)\n");

        bubbleSort(a, n);

        printf("Sorted Array: ");
        display(a, n);

        // Wait for child process
        wait(NULL);

        printf("\nParent process completed.\n");
    }

    return 0;
}



/**Q.2 Write the program to simulate Non-preemptive Shortest Job First (SJF)  
scheduling. The arrival time and first CPU-burst for different n number of  
processes should be input to the algorithm. The next CPU-burst should be 
generated randomly. The output should give Gantt chart, turnaround time  
and waiting time for each process. Also find the average waiting time 
and turnaround time. */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int main()
{
    int n, i, time = 0, completed = 0;
    int at[MAX], bt[MAX];
    int ct[MAX], tat[MAX], wt[MAX];
    int done[MAX] = {0};

    int gantt[MAX], gantt_time[MAX];
    int g = 0, selected, min_bt;

    float avg_wt = 0, avg_tat = 0;

    srand(time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of processes!\n");
        return 1;
    }

    // Input arrival times and generate burst times
    for (i = 0; i < n; i++)
    {
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        if (at[i] < 0)
        {
            printf("Invalid arrival time!\n");
            return 1;
        }

        // Generate random burst time
        bt[i] = rand() % 10 + 1;

        printf("Burst time of P%d = %d\n", i + 1, bt[i]);
    }

    // Non-Preemptive SJF Scheduling
    while (completed < n)
    {
        selected = -1;
        min_bt = 999999;

        // Find process with shortest burst time
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && done[i] == 0)
            {
                if (bt[i] < min_bt)
                {
                    min_bt = bt[i];
                    selected = i;
                }
            }
        }

        // CPU Idle
        if (selected == -1)
        {
            if (g == 0 || gantt[g - 1] != -1)
            {
                gantt[g] = -1;
                gantt_time[g] = time;
                g++;
            }

            time++;
            continue;
        }

        // Record process in Gantt chart
        gantt[g] = selected;
        gantt_time[g] = time;
        g++;

        // Execute process completely
        time += bt[selected];

        ct[selected] = time;
        done[selected] = 1;
        completed++;
    }

    gantt_time[g] = time;

    // Calculate turnaround and waiting times
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

    // Display averages
    printf("\nAverage Waiting Time = %.2f",
           avg_wt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avg_tat / n);

    return 0;
}