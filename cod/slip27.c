/**Q.1 Write a simulation program for disk scheduling using SSTF algorithm. 
Accept total number of disk blocks, disk request string, and current head 
position from the user. Display the list of requests in the order in which it 
is served. Also display the total number of head moments.  
30, 10, 60, 95, 120, 150, 175 
Start Head Position: 50  */

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main()
{
    int n;
    int requests[MAX];
    int visited[MAX] = {0};
    int head;
    int total_movement = 0;
    int i, j;
    int nearest, distance, min_distance;

    printf("Enter total number of disk requests: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of requests!\n");
        return 1;
    }

    printf("Enter disk request string:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter current head position: ");
    scanf("%d", &head);

    printf("\nSSTF Service Order:\n");
    printf("%d", head);

    for (i = 0; i < n; i++)
    {
        nearest = -1;
        min_distance = 999999;

        // Find closest unvisited request
        for (j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                distance = abs(head - requests[j]);

                if (distance < min_distance)
                {
                    min_distance = distance;
                    nearest = j;
                }
            }
        }

        visited[nearest] = 1;

        total_movement += abs(head - requests[nearest]);

        head = requests[nearest];

        printf(" -> %d", head);
    }

    printf("\n\nTotal Head Movement = %d cylinders\n",
           total_movement);

    return 0;
}




/**Q.2 Write the simulation program to implement demand paging  
and show the page scheduling and total number of page faults according 
to the LRU (using counter method) page replacement algorithm. Assume 
the memory of n frames. 
Reference String : 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2   */


#include <stdio.h>

#define MAX_FRAMES 20
#define REF_SIZE 14

int main()
{
    int reference[] = {
        3, 5, 7, 2, 5, 1, 2,
        3, 1, 5, 3, 1, 6, 2
    };

    int frames[MAX_FRAMES];
    int counter[MAX_FRAMES];

    int n;
    int page_faults = 0;
    int i, j;
    int found;
    int position;
    int min_counter;

    printf("Enter number of memory frames: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_FRAMES)
    {
        printf("Invalid number of frames!\n");
        return 1;
    }

    // Initialize frames and counters
    for (i = 0; i < n; i++)
    {
        frames[i] = -1;
        counter[i] = -1;
    }

    printf("\nLRU Page Replacement - Counter Method\n");
    printf("---------------------------------------------\n");

    printf("Page\t");

    for (i = 0; i < n; i++)
        printf("F%d\t", i + 1);

    printf("Status\n");

    printf("---------------------------------------------\n");

    // Process reference string
    for (i = 0; i < REF_SIZE; i++)
    {
        int page = reference[i];

        found = 0;
        position = -1;

        // Search page in frames
        for (j = 0; j < n; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                position = j;
                break;
            }
        }

        // Page hit
        if (found)
        {
            counter[position] = i;
        }
        else
        {
            page_faults++;

            // Find empty frame
            position = -1;

            for (j = 0; j < n; j++)
            {
                if (frames[j] == -1)
                {
                    position = j;
                    break;
                }
            }

            // If no empty frame, find LRU page
            if (position == -1)
            {
                min_counter = counter[0];
                position = 0;

                for (j = 1; j < n; j++)
                {
                    if (counter[j] < min_counter)
                    {
                        min_counter = counter[j];
                        position = j;
                    }
                }
            }

            frames[position] = page;
            counter[position] = i;
        }

        // Display frames
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
    printf("Total Page Faults = %d\n", page_faults);

    return 0;
}