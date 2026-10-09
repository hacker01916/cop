/**Q.1 Write a simulation program for disk scheduling using LOOK algorithm. 
Accept total number of disk blocks, disk request string, and current head 
position from the user. Display the list of requests in the order in which it  
is served. Also display the total number of head moments.  
86, 147, 91, 177, 45, 12, 130 
Starting Head Position: 60 
Direction: Right           */


#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, j, head, temp;
    int requests[100];
    int total = 0, current;
    int pos = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100)
    {
        printf("Invalid number of requests!\n");
        return 1;
    }

    printf("Enter disk request queue:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    current = head;

    // Sort requests in ascending order
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Find first request greater than or equal to head
    while (pos < n && requests[pos] < head)
        pos++;

    printf("\nLOOK Disk Scheduling\n");
    printf("Seek Sequence: %d", head);

    // Move right
    for (i = pos; i < n; i++)
    {
        total += abs(requests[i] - current);
        current = requests[i];

        printf(" -> %d", current);
    }

    // Reverse direction and move left
    for (i = pos - 1; i >= 0; i--)
    {
        total += abs(requests[i] - current);
        current = requests[i];

        printf(" -> %d", current);
    }

    printf("\n\nTotal Head Movements = %d\n", total);

    return 0;
}


/**Q.2 Write the simulation program to implement demand paging and show  
the page scheduling and total number of page faults according to the LRU  
(using counter method) page replacement algorithm. Assume the memory  
of n   frames. 
Reference String : 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2    */


#include <stdio.h>

#define MAX 100

int main()
{
    int pages[] = {
        3, 5, 7, 2, 5, 1, 2,
        3, 1, 5, 3, 1, 6, 2
    };

    int n = 14;
    int frames[MAX], counter[MAX];
    int f, i, j, time = 0, faults = 0;
    int found, victim, min;

    printf("Enter number of frames: ");
    scanf("%d", &f);

    if (f <= 0 || f > MAX)
    {
        printf("Invalid number of frames!\n");
        return 1;
    }

    // Initialize frames and counters
    for (i = 0; i < f; i++)
    {
        frames[i] = -1;
        counter[i] = 0;
    }

    printf("\nLRU Page Replacement (Counter Method)\n");
    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++)
    {
        found = 0;
        time++;

        // Check whether page is present
        for (j = 0; j < f; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                counter[j] = time;
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

            // If memory is full, find LRU page
            if (victim == -1)
            {
                min = counter[0];
                victim = 0;

                for (j = 1; j < f; j++)
                {
                    if (counter[j] < min)
                    {
                        min = counter[j];
                        victim = j;
                    }
                }
            }

            // Replace page and update counter
            frames[victim] = pages[i];
            counter[victim] = time;

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