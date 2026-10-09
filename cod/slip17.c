/**Q.1 Write the program to simulate Non-preemptive Shortest Job First (SJF) 
scheduling. The arrival time and first CPU-burst for different n number of  
processes should be input to the algorithm. The next CPU-burst should be 
generated randomly. The output should give Gantt chart, turnaround time and  
waiting time for each process. Also find the average waiting time and  
turnaround time     */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int main()
{
    int n, i, time = 0, completed = 0;
    int at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX];
    int done[MAX] = {0};
    int order[MAX], start[MAX];
    int idx, min;

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
        idx = -1;
        min = 999999;

        // Find shortest job among arrived processes
        for (i = 0; i < n; i++)
        {
            if (done[i] == 0 && at[i] <= time)
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
            time++;
            continue;
        }

        // Execute selected process
        start[completed] = time;
        order[completed] = idx;

        time += bt[idx];

        ct[idx] = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];

        done[idx] = 1;
        completed++;

        avg_wt += wt[idx];
        avg_tat += tat[idx];
    }

    // Display Gantt Chart
    printf("\nGantt Chart:\n");

    printf("|");
    for (i = 0; i < n; i++)
        printf(" P%d |", order[i] + 1);

    printf("\n%d", start[0]);

    for (i = 0; i < n; i++)
        printf("\t%d", ct[order[i]]);

    // Display process table
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i],
               tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f",
           avg_wt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avg_tat / n);

    return 0;
}


/**Q.2 Write a program to simulate Sequential (Contiguous) file allocation method. 
Assume disk with n number of blocks. Give value of n as input. Randomly  
mark some block as allocated and accordingly maintain the list of free 
blocks. Write menu driven program with menu options as mentioned  
below and implement each option. 
a. Show Bit Vector 
b. Create New File 
c. Show Directory 
d. Delete File 
e. Exit           */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 100
#define MAX_FILES 50

struct File
{
    char name[30];
    int start;
    int length;
    int used;
};

int bit[MAX];
struct File dir[MAX_FILES];

int n;

// Display Bit Vector
void show_bitvector()
{
    int i;

    printf("\nBit Vector:\n");

    for (i = 0; i < n; i++)
        printf("%d ", bit[i]);

    printf("\n");
}

// Create File
void create_file()
{
    char name[30];
    int length, i, j, start;
    int free_slot = -1;

    printf("\nEnter file name: ");
    scanf("%29s", name);

    // Check duplicate file name
    for (i = 0; i < MAX_FILES; i++)
    {
        if (dir[i].used && strcmp(dir[i].name, name) == 0)
        {
            printf("File already exists!\n");
            return;
        }
    }

    // Find free directory entry
    for (i = 0; i < MAX_FILES; i++)
    {
        if (!dir[i].used)
        {
            free_slot = i;
            break;
        }
    }

    if (free_slot == -1)
    {
        printf("Directory is full!\n");
        return;
    }

    printf("Enter number of blocks required: ");
    scanf("%d", &length);

    if (length <= 0 || length > n)
    {
        printf("Invalid block count!\n");
        return;
    }

    // Find consecutive free blocks
    start = -1;

    for (i = 0; i <= n - length; i++)
    {
        int found = 1;

        for (j = i; j < i + length; j++)
        {
            if (bit[j] == 1)
            {
                found = 0;
                break;
            }
        }

        if (found)
        {
            start = i;
            break;
        }
    }

    if (start == -1)
    {
        printf("Contiguous free blocks not available!\n");
        return;
    }

    // Allocate blocks
    for (i = start; i < start + length; i++)
        bit[i] = 1;

    // Update directory
    strcpy(dir[free_slot].name, name);
    dir[free_slot].start = start;
    dir[free_slot].length = length;
    dir[free_slot].used = 1;

    printf("File created successfully!\n");
    printf("Starting Block = %d\n", start);
    printf("Allocated Blocks: ");

    for (i = start; i < start + length; i++)
        printf("%d ", i);

    printf("\n");
}

// Display Directory
void show_directory()
{
    int i, found = 0;

    printf("\nFile Name\tStart Block\tLength\n");

    for (i = 0; i < MAX_FILES; i++)
    {
        if (dir[i].used)
        {
            printf("%s\t\t%d\t\t%d\n",
                   dir[i].name,
                   dir[i].start,
                   dir[i].length);

            found = 1;
        }
    }

    if (!found)
        printf("Directory is empty.\n");
}

// Delete File
void delete_file()
{
    char name[30];
    int i, j;

    printf("\nEnter file name to delete: ");
    scanf("%29s", name);

    for (i = 0; i < MAX_FILES; i++)
    {
        if (dir[i].used && strcmp(dir[i].name, name) == 0)
        {
            // Free allocated blocks
            for (j = dir[i].start;
                 j < dir[i].start + dir[i].length; j++)
            {
                bit[j] = 0;
            }

            dir[i].used = 0;

            printf("File deleted successfully!\n");
            return;
        }
    }

    printf("File not found!\n");
}

int main()
{
    int choice, i, allocated;

    srand(time(NULL));

    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of blocks!\n");
        return 1;
    }

    // Initialize bit vector
    for (i = 0; i < n; i++)
        bit[i] = 0;

    // Initialize directory
    for (i = 0; i < MAX_FILES; i++)
        dir[i].used = 0;

    // Randomly allocate some blocks
    allocated = n / 4;

    for (i = 0; i < allocated; i++)
    {
        int pos = rand() % n;
        bit[pos] = 1;
    }

    printf("\nInitial disk allocation completed.\n");

    do
    {
        printf("\n--- FILE ALLOCATION MENU ---\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create File\n");
        printf("3. Show Directory\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                show_bitvector();
                break;

            case 2:
                create_file();
                break;

            case 3:
                show_directory();
                break;

            case 4:
                delete_file();
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}