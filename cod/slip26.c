/**Q.1 Write the program to simulate Preemptive Priority scheduling. The arrival    
time and first CPU-burst and priority for different n number of processes 
should be input to the algorithm. The next CPU-burst should be generated */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int main()
{
    int n, i;
    int at[MAX], bt[MAX], rem[MAX], priority[MAX];
    int ct[MAX], tat[MAX], wt[MAX];
    int completed[MAX] = {0};

    int time = 0;
    int completed_count = 0;
    int selected, highest_priority;

    float avg_wt = 0, avg_tat = 0;

    srand(time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of processes!\n");
        return 1;
    }

    /* Input process information */
    for (i = 0; i < n; i++)
    {
        printf("\nProcess P%d\n", i + 1);

        printf("Enter arrival time: ");
        scanf("%d", &at[i]);

        printf("Enter first CPU burst: ");
        scanf("%d", &bt[i]);

        printf("Enter priority: ");
        scanf("%d", &priority[i]);

        rem[i] = bt[i];
    }

    /*
     * Preemptive Priority Scheduling
     * Smaller priority number = higher priority
     */
    while (completed_count < n)
    {
        selected = -1;
        highest_priority = 9999;

        /* Find highest-priority arrived process */
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time &&
                rem[i] > 0 &&
                priority[i] < highest_priority)
            {
                highest_priority = priority[i];
                selected = i;
            }
        }

        /* CPU idle */
        if (selected == -1)
        {
            time++;
            continue;
        }

        /*
         * Execute for one time unit.
         * This allows preemption whenever
         * a higher-priority process arrives.
         */
        rem[selected]--;
        time++;

        /* Process completed */
        if (rem[selected] == 0)
        {
            ct[selected] = time;
            completed[selected] = 1;
            completed_count++;
        }
    }

    /* Calculate TAT and WT */
    for (i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    /* Generate next CPU burst */
    printf("\nGenerated Next CPU Bursts:\n");

    for (i = 0; i < n; i++)
    {
        int next_burst = rand() % 10 + 1;

        printf("P%d -> Next CPU Burst = %d\n",
               i + 1, next_burst);
    }

    /* Display result */
    printf("\n--------------------------------------------------\n");
    printf("Process\tAT\tFirst BT\tPriority\tCT\tTAT\tWT\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t\t%d\t\t%d\t%d\t%d\n",
               i + 1,
               at[i],
               bt[i],
               priority[i],
               ct[i],
               tat[i],
               wt[i]);
    }

    printf("--------------------------------------------------\n");

    printf("\nAverage Waiting Time = %.2f",
           avg_wt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avg_tat / n);

    return 0;
}



/**Q.2 Write the simulation program for demand paging and show the page scheduling  
and total number of page faults according the FIFO page replacement algorithm. 
Assume the memory of n frames. 
Reference String: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6  */

#include <stdio.h>

#define MAX_FRAMES 20
#define REF_COUNT 15

int main()
{
    int ref[] = {
        3, 4, 5, 6, 3,
        4, 7, 3, 4, 5,
        6, 7, 2, 4, 6
    };

    int frames[MAX_FRAMES];
    int n;
    int pointer = 0;
    int faults = 0;

    int i, j;
    int found;

    printf("Enter number of memory frames: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_FRAMES)
    {
        printf("Invalid number of frames!\n");
        return 1;
    }

    /* Initialize frames */
    for (i = 0; i < n; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement\n");
    printf("-----------------------------------\n");

    printf("Page\t");

    for (i = 0; i < n; i++)
        printf("F%d\t", i + 1);

    printf("Status\n");
    printf("-----------------------------------\n");

    /* Process reference string */
    for (i = 0; i < REF_COUNT; i++)
    {
        found = 0;

        /* Check whether page is already present */
        for (j = 0; j < n; j++)
        {
            if (frames[j] == ref[i])
            {
                found = 1;
                break;
            }
        }

        /* Page fault */
        if (!found)
        {
            frames[pointer] = ref[i];

            pointer = (pointer + 1) % n;

            faults++;
        }

        printf("%d\t", ref[i]);

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

    printf("-----------------------------------\n");
    printf("Total Page Faults = %d\n", faults);

    return 0;
}