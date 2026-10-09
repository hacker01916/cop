/**   Q.1 Implement the Menu driven Banker's algorithm for accepting Allocation,      
                 Max from user 
a) Accept Available 
b) Display Allocation, Max 
c) Find Need and display It, 
d) Display Available 
   Consider the system with 3 resources types A, B, and C with 7, 2, 6 instances  
   respectively consider the following snapshot: 
 
Process Allocation Request 
 A B C A B C 
P0 0 1 0 0 0 0 
P1 4 0 0 5 2 2 
P2 5 0 4 1 0 4 
P3 4 3 3 4 4 4 
P4 2 2 4 6 5 5  */

#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n = 5, m = 3; // 5 processes (P0-P4) and 3 resources (A, B, C)
    
    // Initial snapshot data from the problem statement
    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0},
        {4, 0, 0},
        {5, 0, 4},
        {4, 3, 3},
        {2, 2, 4}
    };
    
    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0},
        {9, 2, 2},
        {6, 0, 8},
        {8, 7, 7},
        {8, 7, 9}
    };
    
    int total_instances[3] = {7, 2, 6}; // Total instances of A, B, C
    int available[MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int choice, i, j;

    // Calculate Available = Total Instances - Sum of Allocations
    for (j = 0; j < m; j++) {
        int allocated_sum = 0;
        for (i = 0; i < n; i++) {
            allocated_sum += allocation[i][j];
        }
        available[j] = total_instances[j] - allocated_sum;
        if (available[j] < 0) available[j] = 0; // Safeguard
    }

    // Calculate Need Matrix initially: Need = Max - Allocation
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    do {
        printf("\n--- Banker's Algorithm Menu ---\n");
        printf("1. Accept Available Resources\n");
        printf("2. Display Allocation and Max Matrix\n");
        printf("3. Display Need Matrix\n");
        printf("4. Display Available Resources\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter available resources for A, B, C: ");
                for (j = 0; j < m; j++) {
                    scanf("%d", &available[j]);
                }
                printf("Available resources updated successfully.\n");
                break;

            case 2:
                printf("\nProcess\tAllocation (A B C)\tMax (A B C)\n");
                for (i = 0; i < n; i++) {
                    printf("P%d\t%d  %d  %d\t\t%d  %d  %d\n", i,
                           allocation[i][0], allocation[i][1], allocation[i][2],
                           max[i][0], max[i][1], max[i][2]);
                }
                break;

            case 3:
                printf("\nProcess\tNeed Matrix (A B C)\n");
                for (i = 0; i < n; i++) {
                    printf("P%d\t%d  %d  %d\n", i, need[i][0], need[i][1], need[i][2]);
                }
                break;

            case 4:
                printf("\nAvailable Resources: A=%d, B=%d, C=%d\n", available[0], available[1], available[2]);
                break;

            case 5:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (1);

    return 0;
}

/**Q.2     Write a simulation program for disk scheduling using SCAN algorithm.  
Accept total Number of disk blocks, disk request string, and current  
head position from the user. Display the list of requests in the  
order in which it is served. Also display the total number of head moments. 
     82, 170, 43, 140, 24, 16, 190, 65 
     Starting Head position= 50 
     Direction: Left  */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int request[100];
    int n, diskSize;
    int head;
    int direction;

    int i, j, temp;
    int totalMovement = 0;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &diskSize);

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk request string:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &request[i]);
    }

    printf("Enter current head position: ");
    scanf("%d", &head);

    printf("Enter direction (0 = Left, 1 = Right): ");
    scanf("%d", &direction);

    // Sort requests
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (request[i] > request[j])
            {
                temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    printf("\nSCAN Seek Sequence: %d", head);

    if (direction == 0)
    {
        // Move LEFT

        for (i = n - 1; i >= 0; i--)
        {
            if (request[i] < head)
            {
                totalMovement += abs(head - request[i]);
                head = request[i];

                printf(" -> %d", head);
            }
        }

        // Go to left end
        totalMovement += head;
        head = 0;

        printf(" -> %d", head);

        // Reverse direction
        for (i = 0; i < n; i++)
        {
            if (request[i] > head)
            {
                totalMovement += abs(head - request[i]);
                head = request[i];

                printf(" -> %d", head);
            }
        }
    }
    else
    {
        // Move RIGHT

        for (i = 0; i < n; i++)
        {
            if (request[i] > head)
            {
                totalMovement += abs(head - request[i]);
                head = request[i];

                printf(" -> %d", head);
            }
        }

        // Go to right end
        totalMovement += (diskSize - 1) - head;
        head = diskSize - 1;

        printf(" -> %d", head);

        // Reverse direction
        for (i = n - 1; i >= 0; i--)
        {
            if (request[i] < head)
            {
                totalMovement += abs(head - request[i]);
                head = request[i];

                printf(" -> %d", head);
            }
        }
    }

    printf("\n\nTotal Head Movement = %d cylinders\n",
           totalMovement);

    return 0;
}