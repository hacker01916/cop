/**------------------------------------------------------------------------------------------------- 
Q.1 Write a C program to simulate Banker’s algorithm for the purpose of   
        Deadlock avoidance. The following snapshot of system, A, B, C and D are  
        the resource type. 
Process Allocation Max Available 
 A B C A B C A B C 
P0 0 1 0 0 0 0 0 0 0 
P1 2 0 0 2 0 2    
P2 3 0 3 0 0 0    
P3 2 1 1 1 0 0    
P4 0 0 2 0 0 2    
                                 Implement the following Menu. 
a. Accept Available 
b. Display Allocation, Max 
c. Display the contents of need matrix 
d. Display Available    */


#include <stdio.h>

#define P 5
#define R 3

int allocation[P][R];
int max[P][R];
int need[P][R];
int available[R];

void accept_available()
{
    int i;

    printf("\nEnter Available resources (A B C):\n");

    for (i = 0; i < R; i++)
        scanf("%d", &available[i]);

    printf("Available resources accepted.\n");
}

void accept_matrices()
{
    int i, j;

    printf("\nEnter Allocation Matrix:\n");

    for (i = 0; i < P; i++)
    {
        printf("P%d: ", i);
        for (j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);
    }

    printf("\nEnter Max Matrix:\n");

    for (i = 0; i < P; i++)
    {
        printf("P%d: ", i);
        for (j = 0; j < R; j++)
            scanf("%d", &max[i][j]);
    }

    for (i = 0; i < P; i++)
    {
        for (j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }
}

void display_allocation_max()
{
    int i, j;

    printf("\nAllocation Matrix:\n");
    printf("     A  B  C\n");

    for (i = 0; i < P; i++)
    {
        printf("P%d   ", i);
        for (j = 0; j < R; j++)
            printf("%2d ", allocation[i][j]);
        printf("\n");
    }

    printf("\nMax Matrix:\n");
    printf("     A  B  C\n");

    for (i = 0; i < P; i++)
    {
        printf("P%d   ", i);
        for (j = 0; j < R; j++)
            printf("%2d ", max[i][j]);
        printf("\n");
    }
}

void display_need()
{
    int i, j;

    printf("\nNeed Matrix:\n");
    printf("     A  B  C\n");

    for (i = 0; i < P; i++)
    {
        printf("P%d   ", i);
        for (j = 0; j < R; j++)
            printf("%2d ", need[i][j]);
        printf("\n");
    }
}

void display_available()
{
    int i;

    printf("\nAvailable Resources:\n");

    for (i = 0; i < R; i++)
        printf("%d ", available[i]);

    printf("\n");
}

void safety_check()
{
    int work[R], finish[P] = {0};
    int safe_seq[P];
    int count = 0, i, j, found;

    for (i = 0; i < R; i++)
        work[i] = available[i];

    while (count < P)
    {
        found = 0;

        for (i = 0; i < P; i++)
        {
            if (finish[i] == 0)
            {
                for (j = 0; j < R; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == R)
                {
                    for (j = 0; j < R; j++)
                        work[j] += allocation[i][j];

                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
            break;
    }

    if (count == P)
    {
        printf("\nSystem is in SAFE state.\n");
        printf("Safe Sequence: ");

        for (i = 0; i < P; i++)
            printf("P%d ", safe_seq[i]);

        printf("\n");
    }
    else
    {
        printf("\nSystem is in UNSAFE state.\n");
    }
}

int main()
{
    int choice;

    accept_matrices();
    accept_available();

    do
    {
        printf("\n--- BANKER'S ALGORITHM MENU ---\n");
        printf("1. Accept Available\n");
        printf("2. Display Allocation and Max\n");
        printf("3. Display Need Matrix\n");
        printf("4. Display Available\n");
        printf("5. Check Safe State\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                accept_available();
                break;

            case 2:
                display_allocation_max();
                break;

            case 3:
                display_need();
                break;

            case 4:
                display_available();
                break;

            case 5:
                safety_check();
                break;

            case 6:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}



/**Q.2 Write the simulation program for demand paging and show the page 
 scheduling and total number of page faults according the optimal  
 page replacement algorithm.  Assume the memory of n frames. 
    Reference String: 8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2  */


#include <stdio.h>

#define MAX 100

int main()
{
    int pages[MAX], frames[MAX];
    int n, f, i, j, k;
    int faults = 0, found, victim;
    int farthest, next;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    if (n <= 0 || n > MAX || f <= 0 || f > MAX)
    {
        printf("Invalid input!\n");
        return 1;
    }

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement\n");
    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        // Check whether page is already present
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
            printf("%d\t", pages[i]);

            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frames[j]);
            }

            printf("\tHit\n");
        }
        else
        {
            faults++;

            // Find an empty frame
            victim = -1;

            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                {
                    victim = j;
                    break;
                }
            }

            // If no empty frame, find optimal victim
            if (victim == -1)
            {
                farthest = -1;

                for (j = 0; j < f; j++)
                {
                    next = -1;

                    for (k = i + 1; k < n; k++)
                    {
                        if (pages[k] == frames[j])
                        {
                            next = k;
                            break;
                        }
                    }

                    // Page is never used again
                    if (next == -1)
                    {
                        victim = j;
                        break;
                    }

                    if (next > farthest)
                    {
                        farthest = next;
                        victim = j;
                    }
                }
            }

            frames[victim] = pages[i];

            printf("%d\t", pages[i]);

            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frames[j]);
            }

            printf("\tPage Fault\n");
        }
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}