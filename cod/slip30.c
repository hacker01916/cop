/**Q.1 Write the program to simulate Round Robin (RR) CPU-scheduling. The arrival 
        time  and first CPU- burst for different n number of processes should be input  
       to the algorithm. Also give the time quantum as input. Assume the fixed IO 
       waiting time (2 units). The next CPU-burst should be generated randomly.  
       The  output should give Gantt chart, turnaround time and waiting time for 
       each process. Also find the average waiting time and turnaround time */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20
#define IO_WAIT 2

typedef struct
{
    int pid;
    int at;
    int bt1;
    int bt2;
    int remaining;
    int completion;
    int io_done;
    int in_queue;
} Process;

int main()
{
    Process p[MAX];
    int n, tq;
    int time = 0;
    int completed = 0;
    int i;

    int queue[1000];
    int front = 0, rear = 0;

    float avg_wt = 0, avg_tat = 0;

    srand(time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    if (n <= 0 || n > MAX || tq <= 0)
    {
        printf("Invalid input!\n");
        return 1;
    }

    /* Input first CPU burst */
    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nProcess P%d\n", i + 1);

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter First CPU Burst: ");
        scanf("%d", &p[i].bt1);

        /* Generate next CPU burst randomly */
        p[i].bt2 = rand() % 10 + 1;

        p[i].remaining = p[i].bt1;
        p[i].completion = 0;
        p[i].io_done = 0;
        p[i].in_queue = 0;
    }

    printf("\nGenerated Next CPU Bursts:\n");

    for (i = 0; i < n; i++)
        printf("P%d -> %d units\n", i + 1, p[i].bt2);

    printf("\nGantt Chart:\n");


    while (completed < n)
    {
        /* Add newly arrived processes to ready queue */
        for (i = 0; i < n; i++)
        {
            if (p[i].at <= time &&
                p[i].remaining > 0 &&
                p[i].in_queue == 0)
            {
                queue[rear++] = i;
                p[i].in_queue = 1;
            }
        }

        /* CPU idle */
        if (front == rear)
        {
            printf("[Idle %d-%d] ", time, time + 1);
            time++;
            continue;
        }

        /* Select process from ready queue */
        int current = queue[front++];

        int execution;

        if (p[current].remaining < tq)
            execution = p[current].remaining;
        else
            execution = tq;

        printf("[P%d %d-%d] ",
               p[current].pid,
               time,
               time + execution);

        /* Execute process */
        time += execution;
        p[current].remaining -= execution;

        /* Add newly arrived processes */
        for (i = 0; i < n; i++)
        {
            if (p[i].at <= time &&
                p[i].remaining > 0 &&
                p[i].in_queue == 0)
            {
                queue[rear++] = i;
                p[i].in_queue = 1;
            }
        }

        /* Process completed its first CPU burst */
        if (p[current].remaining == 0)
        {
            /*
             * Fixed I/O waiting time = 2 units.
             * After I/O, the generated next CPU burst is available.
             *
             * For this simulation, the process is considered
             * completed after its first CPU burst.
             */
            time += IO_WAIT;

            p[current].completion = time;

            completed++;

            p[current].in_queue = 0;
        }
        else
        {
            /* Not finished: put it at end of ready queue */
            queue[rear++] = current;
        }
    }

    printf("\n");

    /* Calculate TAT and WT */
    for (i = 0; i < n; i++)
    {
        int tat = p[i].completion - p[i].at;
        int wt = tat - p[i].bt1 - IO_WAIT;

        if (wt < 0)
            wt = 0;

        avg_tat += tat;
        avg_wt += wt;
    }

    /* Display table */
    printf("\n---------------------------------------------------------\n");
    printf("Process\tAT\tBT\tNext BT\tCT\tTAT\tWT\n");
    printf("---------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        int tat = p[i].completion - p[i].at;
        int wt = tat - p[i].bt1 - IO_WAIT;

        if (wt < 0)
            wt = 0;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt1,
               p[i].bt2,
               p[i].completion,
               tat,
               wt);
    }

    printf("---------------------------------------------------------\n");

    printf("Average Waiting Time = %.2f\n",
           avg_wt / n);

    printf("Average Turnaround Time = %.2f\n",
           avg_tat / n);

    return 0;
}


/**Q.2   Write the simulation program for demand paging and show the page  
   scheduling and total number of page faults according the MFU  
   page replacement algorithm. Assume the memory of n frames. 
          Reference String: 2,5,2,8,5,4,1,2,3,2,6,1,2,5,9,8   */



#include <stdio.h>

#define MAX_FRAMES 20
#define REF_SIZE 16

int main()
{
    int ref[REF_SIZE] = {
        2, 5, 2, 8, 5, 4, 1, 2,
        3, 2, 6, 1, 2, 5, 9, 8
    };

    int frames[MAX_FRAMES];
    int frequency[MAX_FRAMES];
    int load_time[MAX_FRAMES];

    int n;
    int faults = 0;
    int i, j;
    int found;
    int position;
    int max_frequency;

    printf("Enter number of memory frames: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_FRAMES)
    {
        printf("Invalid number of frames!\n");
        return 1;
    }

    /* Initialize frames */
    for (i = 0; i < n; i++)
    {
        frames[i] = -1;
        frequency[i] = 0;
        load_time[i] = -1;
    }

    printf("\nMFU Page Replacement\n");
    printf("---------------------------------------------\n");

    printf("Page\t");

    for (i = 0; i < n; i++)
        printf("F%d\t", i + 1);

    printf("Status\n");

    printf("---------------------------------------------\n");

    for (i = 0; i < REF_SIZE; i++)
    {
        int page = ref[i];

        found = 0;
        position = -1;

        /* Search page in memory */
        for (j = 0; j < n; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                position = j;
                break;
            }
        }

        if (found)
        {
            /* Page hit */
            frequency[position]++;
        }
        else
        {
            /* Page fault */
            faults++;

            /* Find empty frame */
            for (j = 0; j < n; j++)
            {
                if (frames[j] == -1)
                {
                    position = j;
                    break;
                }
            }

            /* Memory full: find MFU page */
            if (position == -1)
            {
                position = 0;
                max_frequency = frequency[0];

                for (j = 1; j < n; j++)
                {
                    if (frequency[j] > max_frequency)
                    {
                        max_frequency = frequency[j];
                        position = j;
                    }
                    else if (frequency[j] == max_frequency)
                    {
                        /* Tie: replace older page */
                        if (load_time[j] < load_time[position])
                        {
                            position = j;
                        }
                    }
                }
            }

            frames[position] = page;
            frequency[position] = 1;
            load_time[position] = i;
        }

        /* Display frames */
        printf("%d\t", page);

        for (j = 0; j < n; j++)
        {
            if (frames[j] == -1)
                printf("-\t");
            else
                printf("%d\t", frames[j]);
        }

        if (found)
            printf("Hit\n");
        else
            printf("Page Fault\n");
    }

    printf("---------------------------------------------\n");
    printf("Total Page Faults = %d\n", faults);

    return 0;
}