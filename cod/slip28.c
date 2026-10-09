/**Q.1 Write a simulation program for disk scheduling using SCAN algorithm. 
Accept total number of disk blocks, disk request string, and current head  
position from the user. Display the list of requests in the order in which it 
is served. Also display the total number of head moments. 
10, 25, 75, 90, 130, 145, 180, 55 
Starting Head position= 80 
Direction: Left    */


#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main()
{
    int n, disk_size;
    int requests[MAX];
    int left[MAX], right[MAX];
    int l = 0, r = 0;
    int head;
    int i, j, temp;
    int total_movement = 0;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &disk_size);

    printf("Enter number of disk requests: ");
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

    /*
     * Separate requests into left and right
     */
    for (i = 0; i < n; i++)
    {
        if (requests[i] < head)
            left[l++] = requests[i];
        else if (requests[i] > head)
            right[r++] = requests[i];
    }

    /*
     * Sort left side in descending order
     */
    for (i = 0; i < l - 1; i++)
    {
        for (j = i + 1; j < l; j++)
        {
            if (left[i] < left[j])
            {
                temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }
        }
    }

    /*
     * Sort right side in ascending order
     */
    for (i = 0; i < r - 1; i++)
    {
        for (j = i + 1; j < r; j++)
        {
            if (right[i] > right[j])
            {
                temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }
        }
    }

    printf("\nSCAN Service Order:\n");
    printf("%d", head);

    /*
     * Direction = LEFT
     */

    // Service left requests
    for (i = 0; i < l; i++)
    {
        total_movement += abs(head - left[i]);
        head = left[i];

        printf(" -> %d", head);
    }

    // Move to disk boundary 0
    if (head != 0)
    {
        total_movement += head;
        head = 0;

        printf(" -> %d", head);
    }

    // Reverse direction and service right requests
    for (i = 0; i < r; i++)
    {
        total_movement += abs(head - right[i]);
        head = right[i];

        printf(" -> %d", head);
    }

    printf("\n\nTotal Head Movement = %d cylinders\n",
           total_movement);

    return 0;
}



/**Q.2 Write the simulation program for demand paging and show the page  
scheduling and total number of page faults according the MFU  
page replacement algorithm. Assume the memory of n frames. 
Reference String: 8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2 */


#include <stdio.h>

#define MAX_FRAMES 20
#define REF_SIZE 15

int main()
{
    int reference[] = {
        8, 5, 7, 8, 5,
        7, 2, 3, 7, 3,
        5, 9, 4, 6, 2
    };

    int frames[MAX_FRAMES];
    int frequency[MAX_FRAMES];
    int load_time[MAX_FRAMES];

    int n;
    int page_faults = 0;
    int time = 0;

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

    /* Process reference string */
    for (i = 0; i < REF_SIZE; i++)
    {
        int page = reference[i];

        found = 0;
        position = -1;

        /* Check whether page is already present */
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
            page_faults++;

            /* Find empty frame */
            for (j = 0; j < n; j++)
            {
                if (frames[j] == -1)
                {
                    position = j;
                    break;
                }
            }

            /* If no empty frame, find MFU page */
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
                        /*
                         * Tie: replace the page
                         * loaded earlier.
                         */
                        if (load_time[j] < load_time[position])
                        {
                            position = j;
                        }
                    }
                }
            }

            frames[position] = page;
            frequency[position] = 1;
            load_time[position] = time;
        }

        time++;

        /* Display page table */
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