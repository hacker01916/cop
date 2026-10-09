/**Q.1 Write a program to simulate Linked file allocation method. Assume disk with ‘n’ 
number of blocks. Give value of ‘n’ as input. Randomly mark some block as  
allocated  and accordingly maintain the list of free blocks Write menu driven  
program with menu options as mentioned below and implement each option. 
a. Show Bit Vector 
b. Create New File 
c. Show Directory 
d. Delete File 
e. Exit   */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define MAX_FILES 50

struct File
{
    char name[30];
    int start;
    int count;
    int used;
};

int bit[MAX];
int next[MAX];
struct File directory[MAX_FILES];

int n;

// Initialize disk blocks randomly
void initialize()
{
    int i;

    for (i = 0; i < n; i++)
    {
        bit[i] = rand() % 2;
        next[i] = -1;
    }

    for (i = 0; i < MAX_FILES; i++)
        directory[i].used = 0;
}

// Display bit vector
void showBitVector()
{
    int i;

    printf("\nBit Vector:\n");

    for (i = 0; i < n; i++)
        printf("%d ", bit[i]);

    printf("\n");

    printf("0 = Free, 1 = Allocated\n");
}

// Create new file
void createFile()
{
    char name[30];
    int blocks, i, count = 0;
    int available[MAX];
    int start = -1, last = -1;
    int slot = -1;

    printf("\nEnter file name: ");
    scanf("%29s", name);

    // Check duplicate filename
    for (i = 0; i < MAX_FILES; i++)
    {
        if (directory[i].used &&
            strcmp(directory[i].name, name) == 0)
        {
            printf("File already exists!\n");
            return;
        }

        if (!directory[i].used && slot == -1)
            slot = i;
    }

    if (slot == -1)
    {
        printf("Directory is full!\n");
        return;
    }

    printf("Enter number of blocks required: ");
    scanf("%d", &blocks);

    if (blocks <= 0 || blocks > n)
    {
        printf("Invalid number of blocks!\n");
        return;
    }

    // Find free blocks
    for (i = 0; i < n; i++)
    {
        if (bit[i] == 0)
        {
            available[count++] = i;

            if (count == blocks)
                break;
        }
    }

    if (count < blocks)
    {
        printf("Not enough free blocks!\n");
        return;
    }

    // Allocate and link blocks
    for (i = 0; i < blocks; i++)
    {
        int b = available[i];

        bit[b] = 1;

        if (start == -1)
            start = b;

        if (last != -1)
            next[last] = b;

        last = b;
    }

    next[last] = -1;

    // Update directory
    strcpy(directory[slot].name, name);
    directory[slot].start = start;
    directory[slot].count = blocks;
    directory[slot].used = 1;

    printf("\nFile created successfully!\n");
    printf("Allocated blocks: ");

    int current = start;

    while (current != -1)
    {
        printf("%d -> ", current);
        current = next[current];
    }

    printf("NULL\n");
}

// Display directory
void showDirectory()
{
    int i, current;

    printf("\nFile Name\tStart Block\tBlock Chain\n");

    for (i = 0; i < MAX_FILES; i++)
    {
        if (directory[i].used)
        {
            printf("%s\t\t%d\t\t",
                   directory[i].name,
                   directory[i].start);

            current = directory[i].start;

            while (current != -1)
            {
                printf("%d -> ", current);
                current = next[current];
            }

            printf("NULL\n");
        }
    }
}

// Delete file
void deleteFile()
{
    char name[30];
    int i, current, temp, found = 0;

    printf("\nEnter file name to delete: ");
    scanf("%29s", name);

    for (i = 0; i < MAX_FILES; i++)
    {
        if (directory[i].used &&
            strcmp(directory[i].name, name) == 0)
        {
            found = 1;

            current = directory[i].start;

            while (current != -1)
            {
                temp = next[current];

                bit[current] = 0;
                next[current] = -1;

                current = temp;
            }

            directory[i].used = 0;

            printf("File deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("File not found!\n");
}

int main()
{
    int choice;

    srand(time(NULL));

    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of blocks!\n");
        return 1;
    }

    initialize();

    do
    {
        printf("\n\n--- LINKED FILE ALLOCATION ---\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                showBitVector();
                break;

            case 2:
                createFile();
                break;

            case 3:
                showDirectory();
                break;

            case 4:
                deleteFile();
                break;

            case 5:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}


/**Q.2   
[15 Marks] 
Write the program to simulate Non-preemptive Priority scheduling.  
The arrival time and first CPU-burst for different n number of processes 
should be input to the algorithm. The next CPU-burst should be generated  
randomly. The output should give Gantt chart, turnaround time and waiting 
time for each process. Also find the average waiting time and turnaround time */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int main()
{
    int n, i, j, time = 0, completed = 0;
    int at[MAX], bt[MAX], priority[MAX];
    int ct[MAX], tat[MAX], wt[MAX], done[MAX] = {0};

    int gantt[MAX], gantt_time[MAX];
    int g = 0, selected, min_priority;

    float avg_wt = 0, avg_tat = 0;

    srand(time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of processes!\n");
        return 1;
    }

    // Input process details
    for (i = 0; i < n; i++)
    {
        printf("\nEnter arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter priority for P%d: ", i + 1);
        scanf("%d", &priority[i]);

        if (at[i] < 0 || priority[i] < 0)
        {
            printf("Invalid input!\n");
            return 1;
        }

        // Generate random burst time
        bt[i] = rand() % 10 + 1;

        printf("Burst time of P%d = %d\n", i + 1, bt[i]);
    }

    // Non-preemptive Priority Scheduling
    while (completed < n)
    {
        selected = -1;
        min_priority = 999999;

        // Find highest-priority arrived process
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && done[i] == 0)
            {
                if (priority[i] < min_priority)
                {
                    min_priority = priority[i];
                    selected = i;
                }
            }
        }

        // CPU Idle
        if (selected == -1)
        {
            if (g == 0 || gantt[g - 1] != -1)
            {
                gantt[g] = -1;
                gantt_time[g] = time;
                g++;
            }

            time++;
            continue;
        }

        // Record process in Gantt chart
        gantt[g] = selected;
        gantt_time[g] = time;
        g++;

        // Execute process completely
        time += bt[selected];

        ct[selected] = time;
        done[selected] = 1;
        completed++;
    }

    gantt_time[g] = time;

    // Calculate TAT and WT
    for (i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    // Display Gantt Chart
    printf("\nGantt Chart:\n");

    for (i = 0; i < g; i++)
    {
        if (gantt[i] == -1)
            printf("| Idle ");
        else
            printf("| P%d ", gantt[i] + 1);
    }

    printf("|\n");

    for (i = 0; i <= g; i++)
        printf("%-6d", gantt_time[i]);

    // Display process table
    printf("\n\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], priority[i],
               ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f",
           avg_wt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avg_tat / n);

    return 0;
}