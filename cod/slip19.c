/**Q.1 Write the program to simulate Preemptive Priority scheduling. The arrival time  
and first CPU-burst and priority for different n number of processes should be 
input to the algorithm. The next CPU-burst should be generated.  */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int main()
{
    int n, i, time = 0, completed = 0;
    int at[MAX], bt[MAX], rt[MAX], priority[MAX];
    int ct[MAX], tat[MAX], wt[MAX];
    int gantt[10000], gantt_time[10000];
    int g = 0, selected, min_priority;

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

        // Generate random burst time
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

        // Record process change
        if (g == 0 || gantt[g - 1] != selected)
        {
            gantt[g] = selected;
            gantt_time[g] = time;
            g++;
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



/**Q.2   
Write a program that demonstrates the use of nice() system call.  
After a child process is started using fork(), assign higher priority to the  
child using nice() system call  */


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
    errno = 0;
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

        // Assign higher nice value
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