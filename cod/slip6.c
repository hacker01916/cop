/**Q.1. Write a program to simulate Sequential file allocation method. Assume disk with 
n number of blocks. Give value of n as input. Randomly mark some block as  
allocated and accordingly maintain the list of free blocks Write menu driver  
program with menu options as mentioned below and implement each option. 
 Show Bit Vector 
 Create New File 
 Show Directory 
 Exit           */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_FILES 50

struct File
{
    char name[30];
    int start;
    int length;
};

int main()
{
    int n;
    int bitVector[100];
    struct File directory[MAX_FILES];

    int fileCount = 0;
    int choice;
    int i, j;

    // Seed random number generator
    srand(time(NULL));

    printf("Enter number of disk blocks: ");
    scanf("%d", &n);

    // Initially all blocks are free
    for (i = 0; i < n; i++)
    {
        bitVector[i] = 0;
    }

    // Randomly allocate some blocks
    for (i = 0; i < n / 4; i++)
    {
        int block = rand() % n;
        bitVector[block] = 1;
    }

    do
    {
        printf("\n\n===== SEQUENTIAL FILE ALLOCATION =====");
        printf("\n1. Show Bit Vector");
        printf("\n2. Create New File");
        printf("\n3. Show Directory");
        printf("\n4. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            // ------------------------------------------------
            // Show Bit Vector
            // ------------------------------------------------
            case 1:

                printf("\nBit Vector:\n");

                for (i = 0; i < n; i++)
                {
                    printf("%d ", bitVector[i]);

                    if ((i + 1) % 20 == 0)
                        printf("\n");
                }

                printf("\n");

                printf("\n0 = Free Block");
                printf("\n1 = Allocated Block\n");

                break;

            // ------------------------------------------------
            // Create New File
            // ------------------------------------------------
            case 2:
            {
                char fileName[30];
                int blocks;
                int start = -1;
                int count = 0;
                int found = 0;

                if (fileCount >= MAX_FILES)
                {
                    printf("\nDirectory is full!");
                    break;
                }

                printf("\nEnter file name: ");
                scanf("%s", fileName);

                printf("Enter number of blocks required: ");
                scanf("%d", &blocks);

                // Find contiguous free blocks
                for (i = 0; i <= n - blocks; i++)
                {
                    count = 0;

                    for (j = i; j < i + blocks; j++)
                    {
                        if (bitVector[j] == 0)
                            count++;
                        else
                            break;
                    }

                    if (count == blocks)
                    {
                        start = i;
                        found = 1;
                        break;
                    }
                }

                if (found == 1)
                {
                    // Allocate blocks
                    for (i = start; i < start + blocks; i++)
                    {
                        bitVector[i] = 1;
                    }

                    strcpy(directory[fileCount].name, fileName);
                    directory[fileCount].start = start;
                    directory[fileCount].length = blocks;

                    fileCount++;

                    printf("\nFile created successfully!");
                    printf("\nStarting Block = %d", start);
                    printf("\nLength = %d blocks", blocks);

                    printf("\nAllocated Blocks: ");

                    for (i = start; i < start + blocks; i++)
                    {
                        printf("%d ", i);
                    }

                    printf("\n");
                }
                else
                {
                    printf("\nFile cannot be created.");
                    printf("\nRequired contiguous blocks are not available.");
                }

                break;
            }

            // ------------------------------------------------
            // Show Directory
            // ------------------------------------------------
            case 3:

                if (fileCount == 0)
                {
                    printf("\nDirectory is empty.");
                }
                else
                {
                    printf("\n\n===== DIRECTORY =====\n");

                    printf("File Name\tStart\tLength\n");

                    for (i = 0; i < fileCount; i++)
                    {
                        printf("%s\t\t%d\t%d\n",
                               directory[i].name,
                               directory[i].start,
                               directory[i].length);
                    }
                }

                break;

            // ------------------------------------------------
            // Exit
            // ------------------------------------------------
            case 4:

                printf("\nProgram terminated.");
                break;

            default:

                printf("\nInvalid choice!");
        }

    } while (choice != 4);

    return 0;
}


/**Q.2 Write a simulation program for disk scheduling using C-SCAN algorithm. 
Accept total number of disk blocks, disk request string, and current head position 
from the user. Display the list of requests in the order in which it is served. 
also display  the total number of head movements (Assume disk size=200) 
15, 45, 75, 105, 135, 165, 195, 80 
Starting Head Position: 100 
Direction: Righ */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_FILES 50

struct File
{
    char name[30];
    int start;
    int length;
};

int main()
{
    int n;
    int bitVector[100];
    struct File directory[MAX_FILES];

    int fileCount = 0;
    int choice;
    int i, j;

    // Seed random number generator
    srand(time(NULL));

    printf("Enter number of disk blocks: ");
    scanf("%d", &n);

    // Initially all blocks are free
    for (i = 0; i < n; i++)
    {
        bitVector[i] = 0;
    }

    // Randomly allocate some blocks
    for (i = 0; i < n / 4; i++)
    {
        int block = rand() % n;
        bitVector[block] = 1;
    }

    do
    {
        printf("\n\n===== SEQUENTIAL FILE ALLOCATION =====");
        printf("\n1. Show Bit Vector");
        printf("\n2. Create New File");
        printf("\n3. Show Directory");
        printf("\n4. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            // ------------------------------------------------
            // Show Bit Vector
            // ------------------------------------------------
            case 1:

                printf("\nBit Vector:\n");

                for (i = 0; i < n; i++)
                {
                    printf("%d ", bitVector[i]);

                    if ((i + 1) % 20 == 0)
                        printf("\n");
                }

                printf("\n");

                printf("\n0 = Free Block");
                printf("\n1 = Allocated Block\n");

                break;

            // ------------------------------------------------
            // Create New File
            // ------------------------------------------------
            case 2:
            {
                char fileName[30];
                int blocks;
                int start = -1;
                int count = 0;
                int found = 0;

                if (fileCount >= MAX_FILES)
                {
                    printf("\nDirectory is full!");
                    break;
                }

                printf("\nEnter file name: ");
                scanf("%s", fileName);

                printf("Enter number of blocks required: ");
                scanf("%d", &blocks);

                // Find contiguous free blocks
                for (i = 0; i <= n - blocks; i++)
                {
                    count = 0;

                    for (j = i; j < i + blocks; j++)
                    {
                        if (bitVector[j] == 0)
                            count++;
                        else
                            break;
                    }

                    if (count == blocks)
                    {
                        start = i;
                        found = 1;
                        break;
                    }
                }

                if (found == 1)
                {
                    // Allocate blocks
                    for (i = start; i < start + blocks; i++)
                    {
                        bitVector[i] = 1;
                    }

                    strcpy(directory[fileCount].name, fileName);
                    directory[fileCount].start = start;
                    directory[fileCount].length = blocks;

                    fileCount++;

                    printf("\nFile created successfully!");
                    printf("\nStarting Block = %d", start);
                    printf("\nLength = %d blocks", blocks);

                    printf("\nAllocated Blocks: ");

                    for (i = start; i < start + blocks; i++)
                    {
                        printf("%d ", i);
                    }

                    printf("\n");
                }
                else
                {
                    printf("\nFile cannot be created.");
                    printf("\nRequired contiguous blocks are not available.");
                }

                break;
            }

            // ------------------------------------------------
            // Show Directory
            // ------------------------------------------------
            case 3:

                if (fileCount == 0)
                {
                    printf("\nDirectory is empty.");
                }
                else
                {
                    printf("\n\n===== DIRECTORY =====\n");

                    printf("File Name\tStart\tLength\n");

                    for (i = 0; i < fileCount; i++)
                    {
                        printf("%s\t\t%d\t%d\n",
                               directory[i].name,
                               directory[i].start,
                               directory[i].length);
                    }
                }

                break;

            // ------------------------------------------------
            // Exit
            // ------------------------------------------------
            case 4:

                printf("\nProgram terminated.");
                break;

            default:

                printf("\nInvalid choice!");
        }

    } while (choice != 4);

    return 0;
}