/**Q.1 Write the program to simulate FCFS CPU scheduling. The arrival time and 
first CPU- burst for different n number of processes should be input to the  
algorithm. The next CPU-burst should be generated randomly. The output  
should give Gantt chart, turnaround time and waiting time for each process. 
Also find the average waiting time and turnaround time. */



#include <stdio.h>

#define MAX 20

int main()
{
    int n, i, j, temp;
    int at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX], p[MAX];
    int current = 0;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of processes!\n");
        return 1;
    }

    for (i = 0; i < n; i++)
    {
        p[i] = i + 1;

        printf("Enter Arrival Time and Burst Time for P%d: ", p[i]);
        scanf("%d %d", &at[i], &bt[i]);

        if (at[i] < 0 || bt[i] <= 0)
        {
            printf("Invalid input!\n");
            return 1;
        }
    }

    // Sort processes by arrival time
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculate CT, TAT and WT
    for (i = 0; i < n; i++)
    {
        if (current < at[i])
            current = at[i];

        current += bt[i];
        ct[i] = current;

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    // Display Gantt Chart
    printf("\nGantt Chart:\n");

    printf("|");
    for (i = 0; i < n; i++)
        printf("  P%d  |", p[i]);

    printf("\n%d", at[0]);

    for (i = 0; i < n; i++)
        printf("\t%d", ct[i]);

    // Display table
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}


/**Q.2 Implement the C program to accept n integers to be sorted. Main  
function creates child process using fork system call. Parent process sorts 
the integers using bubble sort and waits for child process using wait system  
call child process sorts the integers using insertion sort    */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100

// Bubble Sort
void bubble_sort(int a[], int n)
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

// Insertion Sort
void insertion_sort(int a[], int n)
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
        printf("Invalid input!\n");
        return 1;
    }

    printf("Enter integers:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }

    else if (pid == 0)
    {
        // Child Process
        printf("\nChild Process (Insertion Sort)\n");

        insertion_sort(a, n);

        printf("Sorted Array: ");
        display(a, n);

        exit(0);
    }

    else
    {
        // Parent Process
        printf("\nParent Process (Bubble Sort)\n");

        bubble_sort(a, n);

        printf("Sorted Array: ");
        display(a, n);

        wait(NULL);

        printf("\nParent process: Child process completed.\n");
    }

    return 0;
}