/**Q.1 Write the simulation program for demand paging and show the page  
scheduling and total number of page faults according the optimal page 
replacement algorithm. Assume the memory of ‘n’ frames. 
Reference String: 8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2 */

#include <stdio.h>

int main()
{
    int pages[100];
    int frames[20];

    int n, f;
    int i, j, k;
    int faults = 0;
    int hits = 0;

    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for (i = 0; i < f; i++)
    {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++)
    {
        int found = 0;

        // Check page hit
        for (j = 0; j < f; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            hits++;
        }
        else
        {
            faults++;

            // Empty frame available
            int empty = -1;

            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                {
                    empty = j;
                    break;
                }
            }

            if (empty != -1)
            {
                frames[empty] = pages[i];
            }
            else
            {
                int replaceIndex = -1;
                int farthest = -1;

                // Find page used farthest in future
                for (j = 0; j < f; j++)
                {
                    int nextUse = -1;

                    for (k = i + 1; k < n; k++)
                    {
                        if (frames[j] == pages[k])
                        {
                            nextUse = k;
                            break;
                        }
                    }

                    // Page is never used again
                    if (nextUse == -1)
                    {
                        replaceIndex = j;
                        break;
                    }

                    if (nextUse > farthest)
                    {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }

                frames[replaceIndex] = pages[i];
            }
        }

        printf("%d\t", pages[i]);

        for (j = 0; j < f; j++)
        {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if (found)
            printf("\tHit");
        else
            printf("\tPage Fault");

        printf("\n");
    }

    printf("\nTotal Page References = %d", n);
    printf("\nTotal Page Faults = %d", faults);
    printf("\nTotal Page Hits = %d\n", hits);

    return 0;
}

/**Q.2 Write the program to simulate Non-preemptive Shortest Job First (SJF) scheduling.  
the arrival time and first CPU burst for different n number of processes should be 
input to the algorithm. The next CPU burst should be generated randomly. The 
output should give Gantt chart, turnaround time and waiting time for each process. 
Also find the average waiting time and turnaround time. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process
{
    int pid;
    int arrival;
    int burst;
    int nextBurst;
    int totalBurst;
    int completion;
    int turnaround;
    int waiting;
    int completed;
};

int main()
{
    struct Process p[20];

    int n;
    int i, j;
    int currentTime = 0;
    int completed = 0;

    float avgWaiting = 0;
    float avgTurnaround = 0;

    srand(time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input arrival time and first CPU burst
    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nProcess P%d\n", i + 1);

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Enter First CPU Burst: ");
        scanf("%d", &p[i].burst);

        // Generate random next CPU burst
        p[i].nextBurst = (rand() % 9) + 2;

        // Total CPU burst
        p[i].totalBurst = p[i].burst + p[i].nextBurst;

        p[i].completed = 0;
    }

    printf("\n\n===== PROCESS INFORMATION =====\n");

    printf("Process\tArrival\tFirst Burst\tNext Burst\tTotal Burst\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].nextBurst,
               p[i].totalBurst);
    }

    printf("\n\n===== GANTT CHART =====\n");

    printf("0");

    while (completed < n)
    {
        int shortest = -1;
        int minBurst = 9999;

        // Find shortest job among arrived processes
        for (i = 0; i < n; i++)
        {
            if (p[i].completed == 0 &&
                p[i].arrival <= currentTime)
            {
                if (p[i].totalBurst < minBurst)
                {
                    minBurst = p[i].totalBurst;
                    shortest = i;
                }
            }
        }

        // No process has arrived
        if (shortest == -1)
        {
            currentTime++;

            printf(" -> idle -> %d", currentTime);

            continue;
        }

        // Execute selected process
        printf(" -> P%d -> %d",
               p[shortest].pid,
               currentTime + p[shortest].totalBurst);

        currentTime += p[shortest].totalBurst;

        p[shortest].completion = currentTime;

        p[shortest].turnaround =
            p[shortest].completion - p[shortest].arrival;

        p[shortest].waiting =
            p[shortest].turnaround - p[shortest].totalBurst;

        if (p[shortest].waiting < 0)
            p[shortest].waiting = 0;

        p[shortest].completed = 1;

        completed++;
    }

    // Display results
    printf("\n\n===== SJF RESULT =====\n");

    printf("Process\tAT\tBurst\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].totalBurst,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);

        avgWaiting += p[i].waiting;
        avgTurnaround += p[i].turnaround;
    }

    avgWaiting /= n;
    avgTurnaround /= n;

    printf("\nAverage Waiting Time = %.2f",
           avgWaiting);

    printf("\nAverage Turnaround Time = %.2f\n",
           avgTurnaround);

    return 0;
}