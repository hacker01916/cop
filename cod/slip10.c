/**Q.1 Write the program to simulate Round Robin (RR) scheduling. The arrival  
time and first CPU burst for different n number of processes should be  
input to the algorithm. Also give the time quantum as input. The next CPU 
burst should be generated randomly. The output should give Gantt chart, 
turnaround time and waiting time for each process. Also find the average  
waiting time and turnaround time.   */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

struct Process {
    int pid;
    int at;             // Arrival time
    int bt;             // Current CPU burst
    int remaining;      // Remaining burst
    int completion;
    int turnaround;
    int waiting;
    int finished;
};

int main() {
    struct Process p[MAX];
    int n, tq;
    int time = 0;
    int completed = 0;
    int queue[MAX * 100];
    int front = 0, rear = 0;
    int visited[MAX] = {0};
    float avgWT = 0, avgTAT = 0;

    srand(time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter Arrival Time and First CPU Burst:\n");

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &p[i].at);

        printf("P%d First CPU Burst: ", i + 1);
        scanf("%d", &p[i].bt);

        p[i].remaining = p[i].bt;
        p[i].finished = 0;
        p[i].completion = 0;
        p[i].turnaround = 0;
        p[i].waiting = 0;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    /* Start from earliest arrival time */
    time = p[0].at;

    for (int i = 1; i < n; i++) {
        if (p[i].at < time)
            time = p[i].at;
    }

    /* Add processes that have already arrived */
    for (int i = 0; i < n; i++) {
        if (p[i].at <= time && !visited[i]) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    printf("\n\n========== GANTT CHART ==========\n");
    printf(" ");

    while (completed < n) {

        /* If ready queue is empty, CPU remains idle */
        if (front == rear) {
            time++;

            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int index = queue[front++];

        int start = time;
        int execute;

        if (p[index].remaining > tq)
            execute = tq;
        else
            execute = p[index].remaining;

        time += execute;
        p[index].remaining -= execute;

        printf("| P%d ", p[index].pid);

        /* Add newly arrived processes */
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[index].remaining > 0) {

            /*
             * Generate next CPU burst randomly
             * if current burst is completed by quantum.
             */
            if (execute == tq) {
                int nextBurst = (rand() % 5) + 1;

                printf("(Next Burst=%d) ", nextBurst);

                p[index].remaining = nextBurst;
            }

            queue[rear++] = index;
        }
        else {
            p[index].finished = 1;
            p[index].completion = time;
            completed++;

            p[index].turnaround =
                p[index].completion - p[index].at;

            p[index].waiting =
                p[index].turnaround - p[index].bt;

            avgWT += p[index].waiting;
            avgTAT += p[index].turnaround;
        }
    }

    printf("|\n");

    printf("\n========== PROCESS DETAILS ==========\n");

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);
    }

    printf("\nAverage Waiting Time    = %.2f",
           avgWT / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avgTAT / n);

    return 0;
}

/**Q.2 Write a simulation program for disk scheduling using Look  
algorithm. Accept total number of disk blocks, disk request string, 
and current head position from the user. Display the list of request in 
the order in which it is served. Also display the total number of head  
moments.          
55, 58, 39, 18, 90, 160, 150, 38.         
Start Head Position: 100 
Direction: Left                      */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, j;
    int request[100];
    int head, direction;
    int total_movement = 0;
    int temp;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    printf("Enter number of disk requests: ");
    scanf("%d", &j);

    printf("Enter disk request string:\n");
    for (i = 0; i < j; i++)
        scanf("%d", &request[i]);

    printf("Enter current head position: ");
    scanf("%d", &head);

    printf("Enter direction (1 = Left, 2 = Right): ");
    scanf("%d", &direction);

    /* Sort the request string */
    for (i = 0; i < j - 1; i++)
    {
        for (int k = i + 1; k < j; k++)
        {
            if (request[i] > request[k])
            {
                temp = request[i];
                request[i] = request[k];
                request[k] = temp;
            }
        }
    }

    printf("\nRequest sequence: %d", head);

    if (direction == 1)
    {
        /* Move towards LEFT */
        for (i = j - 1; i >= 0; i--)
        {
            if (request[i] < head)
            {
                total_movement += abs(head - request[i]);
                head = request[i];

                printf(" -> %d", head);
            }
        }

        /* Reverse direction */
        for (i = 0; i < j; i++)
        {
            if (request[i] > head)
            {
                total_movement += abs(head - request[i]);
                head = request[i];

                printf(" -> %d", head);
            }
        }
    }
    else
    {
        /* Move towards RIGHT */
        for (i = 0; i < j; i++)
        {
            if (request[i] > head)
            {
                total_movement += abs(head - request[i]);
                head = request[i];

                printf(" -> %d", head);
            }
        }

        /* Reverse direction */
        for (i = j - 1; i >= 0; i--)
        {
            if (request[i] < head)
            {
                total_movement += abs(head - request[i]);
                head = request[i];

                printf(" -> %d", head);
            }
        }
    }

    printf("\n\nTotal Head Movement = %d cylinders\n",
           total_movement);

    return 0;
}
