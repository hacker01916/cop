/**Q.1 Write a C program to illustrate the concept of orphan process. Parent process creates  
a child and terminates before child has finished its task. So child process becomes 
orphan process. (Use fork(), sleep(), getpid(), getppid   */



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
        // Child process
        printf("\nChild Process Started\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        printf("\nChild is sleeping for 5 seconds...\n");
        sleep(5);

        printf("\nChild Process After Parent Termination\n");
        printf("Child PID  : %d\n", getpid());
        printf("New Parent PID : %d\n", getppid());

        printf("\nChild process completed.\n");
    }

    else
    {
        // Parent process
        printf("\nParent Process\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        printf("\nParent is sleeping for 1 second...\n");
        sleep(1);

        printf("\nParent process terminating.\n");
        exit(0);
    }

    return 0;
}


/**Q.2 Write the program to simulate Preemptive Priority scheduling. The arrival time  
and first CPU-burst and priority for different n number of processes should be  
input to the algorithm. The next CPU-burst should be generated randomly.  
The output should give Gantt chart, turnaround time and waiting time for  
each process. Also find the average waiting time and turnaround time  */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int main()
{
    int n, i, time = 0, completed = 0;
    int at[MAX], bt[MAX], rt[MAX];
    int priority[MAX], ct[MAX], tat[MAX], wt[MAX];
    int gantt_process[10000], gantt_time[10000];
    int selected, min_priority;
    int g = 0, prev = -2;

    float avg_wt = 0, avg_tat = 0;

    srand(time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of processes!\n");
        return 1;
    }

    // Input process details
    for (i = 0; i < n; i++)
    {
        printf("\nEnter arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter priority for P%d: ", i + 1);
        scanf("%d", &priority[i]);

        if (at[i] < 0 || priority[i] < 0)
        {
            printf("Invalid input!\n");
            return 1;
        }

        // Generate random burst time from 1 to 10
        bt[i] = rand() % 10 + 1;
        rt[i] = bt[i];

        printf("Burst time of P%d = %d\n", i + 1, bt[i]);
    }

    // Preemptive Priority Scheduling
    while (completed < n)
    {
        selected = -1;
        min_priority = 999999;

        // Find highest-priority arrived process
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && rt[i] > 0)
            {
                if (priority[i] < min_priority)
                {
                    min_priority = priority[i];
                    selected = i;
                }
            }
        }

        // CPU is idle
        if (selected == -1)
        {
            if (prev != -1)
            {
                gantt_process[g] = -1;
                gantt_time[g] = time;
                g++;
                prev = -1;
            }

            time++;
            continue;
        }

        // Record Gantt chart when process changes
        if (selected != prev)
        {
            gantt_process[g] = selected;
            gantt_time[g] = time;
            g++;
            prev = selected;
        }

        // Execute process for one time unit
        rt[selected]--;
        time++;

        // Check process completion
        if (rt[selected] == 0)
        {
            ct[selected] = time;
            completed++;
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

    // Display Gantt chart
    printf("\nGantt Chart:\n");

    for (i = 0; i < g; i++)
    {
        if (gantt_process[i] == -1)
            printf("| Idle ");
        else
            printf("| P%d ", gantt_process[i] + 1);
    }

    printf("|\n");

    for (i = 0; i <= g; i++)
        printf("%-6d", gantt_time[i]);

    // Display process table
    printf("\n\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], priority[i],
               ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f",
           avg_wt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avg_tat / n);

    return 0;
}