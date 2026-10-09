/**Q.1 Write a program to simulate Linked file allocation method. Assume disk with ‘n’ number of blocks. 
Give value of ‘n’ as input. Randomly mark some block as allocated and accordingly maintain the list of 
free blocks Write menu driver program with menu options as mentioned below and implement each 
option. 
 Show Bit Vector 
 Create New File 
 Show Directory 
 Exit           */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_FILES 20

struct File
{
    char name[30];
    int start;
    int blocks;
    int blockList[MAX];
};

struct File directory[MAX_FILES];

int bitVector[MAX];
int n;
int fileCount = 0;

/* Show Bit Vector */
void showBitVector()
{
    printf("\n--- Bit Vector ---\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", bitVector[i]);
    }

    printf("\n");
}

/* Create New File */
void createFile()
{
    char filename[30];
    int blocks;

    if (fileCount >= MAX_FILES)
    {
        printf("\nDirectory is full!\n");
        return;
    }

    printf("\nEnter file name: ");
    scanf("%s", filename);

    printf("Enter number of blocks required: ");
    scanf("%d", &blocks);

    /* Count free blocks */
    int freeBlocks = 0;

    for (int i = 0; i < n; i++)
    {
        if (bitVector[i] == 0)
            freeBlocks++;
    }

    if (freeBlocks < blocks)
    {
        printf("\nNot enough free blocks available!\n");
        return;
    }

    /*
       Allocate blocks
       Linked allocation can use non-contiguous blocks.
    */
    int count = 0;

    strcpy(directory[fileCount].name, filename);
    directory[fileCount].blocks = blocks;

    for (int i = 0; i < n && count < blocks; i++)
    {
        if (bitVector[i] == 0)
        {
            bitVector[i] = 1;

            directory[fileCount].blockList[count] = i;
            count++;
        }
    }

    directory[fileCount].start =
        directory[fileCount].blockList[0];

    fileCount++;

    printf("\nFile created successfully!\n");

    printf("File Name: %s\n", filename);
    printf("Linked Blocks: ");

    for (int i = 0; i < blocks; i++)
    {
        printf("%d", directory[fileCount - 1].blockList[i]);

        if (i < blocks - 1)
            printf(" -> ");
    }

    printf("\n");
}

/* Show Directory */
void showDirectory()
{
    if (fileCount == 0)
    {
        printf("\nDirectory is empty!\n");
        return;
    }

    printf("\n--- Directory ---\n");

    printf("%-15s %-10s %-10s\n",
           "File Name", "Start", "Blocks");

    for (int i = 0; i < fileCount; i++)
    {
        printf("%-15s %-10d %-10d\n",
               directory[i].name,
               directory[i].start,
               directory[i].blocks);

        printf("Linked List: ");

        for (int j = 0; j < directory[i].blocks; j++)
        {
            printf("%d", directory[i].blockList[j]);

            if (j < directory[i].blocks - 1)
                printf(" -> ");
        }

        printf("\n");
    }
}

/* Main Function */
int main()
{
    int choice;

    printf("Enter number of blocks: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of blocks!\n");
        return 0;
    }

    /* Initially all blocks are free */
    for (int i = 0; i < n; i++)
    {
        bitVector[i] = 0;
    }

    while (1)
    {
        printf("\n=================================\n");
        printf(" Linked File Allocation\n");
        printf("=================================\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Exit\n");

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
                printf("\nProgram terminated.\n");
                exit(0);

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}



/**Q.2     Write a simulation program for disk scheduling using FCFS algorithm.  
Accept total number of disk blocks, disk request string, and current  
head position from the user. Display the list of requests in the  
order in which it is served. Also display the total number of head moments. 
55, 58, 39, 18, 90, 160, 150, 38, 184 
Start Head Position: 50   */


#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    int request[100];
    int head;
    int totalMovement = 0;

    printf("Enter total number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk request string:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &request[i]);
    }

    printf("Enter current head position: ");
    scanf("%d", &head);

    printf("\n--- FCFS Disk Scheduling ---\n");

    printf("Seek Sequence: %d", head);

    for (int i = 0; i < n; i++)
    {
        int movement = abs(request[i] - head);

        printf(" -> %d", request[i]);

        printf("\nHead movement from %d to %d = %d",
               head, request[i], movement);

        totalMovement += movement;

        head = request[i];
    }

    printf("\n\nTotal Head Movement = %d cylinders\n",
           totalMovement);

    printf("Average Head Movement = %.2f cylinders\n",
           (float)totalMovement / n);

    return 0;
}