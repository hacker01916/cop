/*Q.1 Write a C program to simulate Banker’s algorithm for the purpose of deadlock 
avoidance. Consider the following snapshot of system, A, B, C and D is the resource type. 
Process Allocation Max Available 
 A B C D A B C D A B C D 
P0 0 0 1 2 0 0 1 2 1 5 2 0 
P1 1 0 0 0 1 7 5 0     
P2 1 3 5 4 2 3 5 6     
P3 0 6 3 2 0 6 5 2     
P4 0 0 1 4 0 6 5 6     
a)  Calculate and display the content of need matrix? 
b)  Is the system in safe state? If display the safe sequence.*/


#include <stdio.h>

int main()
{
    int n = 5, m = 4;
    
    int allocation[5][4] = {
        {0, 0, 1, 2},
        {1, 0, 0, 0},
        {1, 3, 5, 4},
        {0, 6, 3, 2},
        {0, 0, 1, 4}
    };

    int max[5][4] = {
        {1, 0, 1, 2},
        {1, 7, 5, 0},
        {2, 3, 5, 6},
        {0, 6, 5, 2},
        {0, 6, 5, 6}
    };

    int available[4] = {1, 5, 2, 0};

    int need[5][4];
    int finish[5] = {0};
    int work[4];
    int safeSequence[5];

    int i, j, count = 0;

    // Calculate Need Matrix
    printf("Need Matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Initialize Work
    for (j = 0; j < m; j++)
        work[j] = available[j];

    // Banker's Safety Algorithm
    while (count < n)
    {
        int found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int canExecute = 1;

                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canExecute = 0;
                        break;
                    }
                }

                if (canExecute)
                {
                    for (j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            break;
        }
    }

    if (count == n)
    {
        printf("\nSystem is in SAFE state.\n");

        printf("Safe Sequence: ");

        for (i = 0; i < n; i++)
        {
            printf("P%d", safeSequence[i]);

            if (i != n - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is NOT in safe state.\n");
    }

    return 0;
}



/**/Q.2 Write a simulation program for disk scheduling using SSTF algorithm. 
  Accept total number of disk blocks, disk request string, and current head 
  position from the user. Display the list of requests in the order in which 
  it is served. Also display the total number of head moments. 
   98, 183, 37, 122, 14, 124, 65 
   Start Head Position: 53 */

 #include <stdio.h>
#include <stdlib.h>

int main()
{
    int request[] = {98, 183, 37, 122, 14, 124, 65};
    int n = 7;
    int head = 53;

    int visited[7] = {0};
    int totalMovement = 0;

    int i, j;
    int current = head;

    printf("SSTF Disk Scheduling\n");

    printf("Seek Sequence: %d", head);

    for (i = 0; i < n; i++)
    {
        int minDistance = 9999;
        int index = -1;

        // Find nearest unvisited request
        for (j = 0; j < n; j++)
        {
            if (visited[j] == 0)
            {
                int distance = abs(current - request[j]);

                if (distance < minDistance)
                {
                    minDistance = distance;
                    index = j;
                }
            }
        }

        visited[index] = 1;

        totalMovement += minDistance;
        current = request[index];

        printf(" -> %d", current);
    }

    printf("\n");

    printf("Total Head Movement = %d cylinders\n",
           totalMovement);

    return 0;
}