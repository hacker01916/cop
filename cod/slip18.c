/**Q.1. Write the program to simulate Preemptive Shortest Job First (SJF) scheduling.  
The arrival time and first CPU burst for different n number of processes should  
be input to the algorithm. The next CPU burst should be generated randomly.  
The output should give Gantt chart, turnaround time and waiting time for each  
process.  Also find the average waiting time and turnaround time */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int main()
{
    int n, i, current_time = 0, completed = 0;
    int at[MAX], bt[MAX], rt[MAX];
    int ct[MAX], tat[MAX], wt[MAX];
    int gantt[10000], gantt_time[10000];
    int g = 0, selected, min;

    float avg_wt = 0, avg_tat = 0;

    srand(time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of processes!\n");
        return 1;
    }

    // Input arrival time and generate burst time
    for (i = 0; i < n; i++)
    {
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        if (at[i] < 0 || at[i] >= 10000)
        {
            printf("Invalid arrival time!\n");
            return 1;
        }

        bt[i] = rand() % 10 + 1;
        rt[i] = bt[i];

        printf("Burst time of P%d = %d\n", i + 1, bt[i]);
    }

    // Preemptive SJF Scheduling
    while (completed < n)
    {
        selected = -1;
        min = 999999;

        // Find process with shortest remaining time
        for (i = 0; i < n; i++)
        {
            if (at[i] <= current_time && rt[i] > 0)
            {
                if (rt[i] < min)
                {
                    min = rt[i];
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
                gantt_time[g] = current_time;
                g++;
            }

            current_time++;
            continue;
        }

        // Record process change
        if (g == 0 || gantt[g - 1] != selected)
        {
            gantt[g] = selected;
            gantt_time[g] = current_time;
            g++;
        }

        // Execute process for one time unit
        rt[selected]--;
        current_time++;

        // Check process completion
        if (rt[selected] == 0)
        {
            ct[selected] = current_time;
            completed++;
        }
    }

    gantt_time[g] = current_time;

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




/** Q.3 Write a C program to illustrate the concept of orphan process. Parent process  
creates a child and terminates before child has finished its task. So child process  
becomes orphan process. (Use fork(), sleep(), getpid(), getppid()    */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

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
        // Child Process
        printf("\nChild Process Started\n");

        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        fflush(stdout);

        printf("\nChild is sleeping for 5 seconds...\n");
        fflush(stdout);

        sleep(5);

        printf("\nChild Process After Parent Termination\n");

        printf("Child PID      : %d\n", getpid());
        printf("New Parent PID : %d\n", getppid());

        printf("\nChild process completed.\n");
    }

    else
    {
        // Parent Process
        printf("\nParent Process\n");

        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        printf("\nParent is sleeping for 1 second...\n");

        fflush(stdout);

        sleep(1);

        printf("\nParent process terminating.\n");
        fflush(stdout);

        exit(0);
    }

    return 0;
}

