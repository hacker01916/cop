/**Q.1. Implement the C program that accepts an integer array. Main function forks  
child process. Parent process sorts an integer array and passes the sorted array 
to child process through the command line arguments of execve() system call. 
The child process uses execve() system call to load new program that uses this  
sorted array for performing the binary search the particular item in the array.   */

/**Improved Parent Program (parent.c) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100

int main()
{
    int a[MAX], n, i, j, temp;
    pid_t pid;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid input!\n");
        return 1;
    }

    printf("Enter array elements:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // Sort array using Bubble Sort
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("\nSorted Array: ");

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process: pass sorted array to exec
        char *args[MAX + 2];

        args[0] = "./search";

        for (i = 0; i < n; i++)
        {
            args[i + 1] = malloc(12);
            sprintf(args[i + 1], "%d", a[i]);
        }

        args[n + 1] = NULL;

        execl("./search", "search", args[1],
              args[2], args[3], args[4], args[5], NULL);

        perror("exec failed");
        exit(1);
    }
    else
    {
        // Parent waits for child
        wait(NULL);
        printf("\nParent process completed.\n");
    }

    return 0;
}

/**Improved Parent Program (parent.c) */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100

int main()
{
    int a[MAX], n, i, j, temp;
    pid_t pid;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid input!\n");
        return 1;
    }

    printf("Enter array elements:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // Bubble Sort
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("\nSorted Array: ");

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        char *args[MAX + 2];

        args[0] = "search";

        for (i = 0; i < n; i++)
        {
            args[i + 1] = malloc(12);
            sprintf(args[i + 1], "%d", a[i]);
        }

        args[n + 1] = NULL;

        execv("./search", args);

        perror("execv failed");
        exit(1);
    }
    else
    {
        wait(NULL);
        printf("\nParent process completed.\n");
    }

    return 0;
}

/**Program 2: Child Process (search.c) */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a[100], n, key;
    int low, high, mid, i, found = 0;

    n = argc - 1;

    if (n <= 0 || n > 100)
    {
        printf("Invalid array!\n");
        return 1;
    }

    for (i = 0; i < n; i++)
        a[i] = atoi(argv[i + 1]);

    printf("\nChild Process (Binary Search)\n");

    printf("Sorted Array: ");

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\nEnter element to search: ");
    scanf("%d", &key);

    low = 0;
    high = n - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (a[mid] == key)
        {
            found = 1;
            break;
        }
        else if (a[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    if (found)
        printf("Element %d found at position %d\n",
               key, mid + 1);
    else
        printf("Element %d not found\n", key);

    return 0;
}

/**gcc parent.c -o parent
gcc search.c -o search
./parent               
*/



/**Q.2   Write the simulation program for demand paging and show the page scheduling  
and total number of page faults according the FIFO page replacement 
algorithm. Assume the memory of n frames. 
Reference String: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6 */

#include <stdio.h>

#define MAX 100

int main()
{
    int pages[MAX], frames[MAX];
    int n, f, i, j;
    int pointer = 0, faults = 0, found;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of pages!\n");
        return 1;
    }

    printf("Enter reference string:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    if (f <= 0 || f > MAX)
    {
        printf("Invalid number of frames!\n");
        return 1;
    }

    // Initialize frames
    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement\n");
    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        // Check if page is already present
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
            // Page fault
            frames[pointer] = pages[i];

            pointer = (pointer + 1) % f;

            faults++;

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

