/**Q.1 Write the program to simulate Non-preemptive Shortest Job First (SJF) scheduling.  
The arrival time and first CPU burst for different n number of processes should  
be input  to the algorithm. The next CPU-burst should be generated randomly. The  
output should  give Gantt chart, turnaround time and waiting time for each process.  
Also find the average waiting time and turnaround time.      */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int main()
{
    int n, i, completed = 0, current = 0;
    int at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX];
    int done[MAX] = {0}, order[MAX];
    int min, idx;
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

        if (at[i] < 0)
        {
            printf("Invalid arrival time!\n");
            return 1;
        }

        bt[i] = rand() % 10 + 1;

        printf("Burst time of P%d = %d\n", i + 1, bt[i]);
    }

    // Non-preemptive SJF scheduling
    while (completed < n)
    {
        min = 9999;
        idx = -1;

        // Find shortest job among arrived processes
        for (i = 0; i < n; i++)
        {
            if (done[i] == 0 && at[i] <= current)
            {
                if (bt[i] < min)
                {
                    min = bt[i];
                    idx = i;
                }
            }
        }

        // If no process has arrived, move time forward
        if (idx == -1)
        {
            current++;
            continue;
        }

        // Execute selected process
        current += bt[idx];

        ct[idx] = current;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];

        done[idx] = 1;
        order[completed] = idx;
        completed++;

        avg_wt += wt[idx];
        avg_tat += tat[idx];
    }

    // Display Gantt chart
    printf("\nGantt Chart:\n");

    printf("|");
    for (i = 0; i < n; i++)
        printf(" P%d |", order[i] + 1);

    printf("\n");

    printf("%d", at[order[0]]);

    for (i = 0; i < n; i++)
        printf("\t%d", ct[order[i]]);

    // Display process table
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f",
           avg_wt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avg_tat / n);

    return 0;
}


/***Q.2  Write a simulation program for disk scheduling using LOOK algorithm.  
Accept total number of disk blocks, disk request string, and current head  
position from the user. isplay the list of requests in the order in which it is served. 
Also display the total number of head moments 
15, 30, 55, 90, 125, 140, 170 
Starting Head Position: 100          
Direction: Left             */



#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main()
{
    int request[MAX], n, head, i, j, temp;
    int total = 0, direction;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of requests!\n");
        return 1;
    }

    printf("Enter disk request sequence:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &request[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (0 for Left, 1 for Right): ");
    scanf("%d", &direction);

    if (head < 0 || (direction != 0 && direction != 1))
    {
        printf("Invalid input!\n");
        return 1;
    }

    // Sort requests in ascending order
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (request[j] > request[j + 1])
            {
                temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    printf("\nLOOK Disk Scheduling\n");
    printf("Seek Sequence: %d", head);

    if (direction == 0)
    {
        // Move left first
        for (i = n - 1; i >= 0; i--)
        {
            if (request[i] < head)
            {
                total += abs(head - request[i]);
                head = request[i];

                printf(" -> %d", head);
            }
        }

        // Reverse direction and move right
        for (i = 0; i < n; i++)
        {
            if (request[i] >= head)
            {
                total += abs(head - request[i]);
                head = request[i];

                printf(" -> %d", head);
            }
        }
    }
    else
    {
        // Move right first
        for (i = 0; i < n; i++)
        {
            if (request[i] > head)
            {
                total += abs(head - request[i]);
                head = request[i];

                printf(" -> %d", head);
            }
        }

        // Reverse direction and move left
        for (i = n - 1; i >= 0; i--)
        {
            if (request[i] <= head)
            {
                total += abs(head - request[i]);
                head = request[i];

                printf(" -> %d", head);
            }
        }
    }

    printf("\n\nTotal Head Movements = %d cylinders\n", total);

    return 0;
}