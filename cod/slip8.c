/**Q.1 Write a program to simulate Index file allocation method. Assume disk with 
‘n’ number of blocks. Give value of ‘n’ as input. Randomly mark some block  
as allocated  and accordingly maintain the list of free blocks Write menu driven      
program with menu options as mentioned above and implement each option 
 Show Bit Vector 
 Create New File 
 Show Directory 
 Exit  */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILES 50
#define MAX_BLOCKS 100

struct File
{
    char name[30];
    int indexBlock;
    int blocks[50];
    int blockCount;
};

int main()
{
    int n;
    int bitVector[MAX_BLOCKS];

    struct File directory[MAX_FILES];

    int fileCount = 0;
    int choice;
    int i, j;

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
        printf("\n\n===== INDEXED FILE ALLOCATION =====");
        printf("\n1. Show Bit Vector");
        printf("\n2. Create New File");
        printf("\n3. Show Directory");
        printf("\n4. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            // -----------------------------
            // Show Bit Vector
            // -----------------------------
            case 1:

                printf("\nBit Vector:\n");

                for (i = 0; i < n; i++)
                {
                    printf("%d ", bitVector[i]);

                    if ((i + 1) % 20 == 0)
                        printf("\n");
                }

                printf("\n\n0 = Free");
                printf("\n1 = Allocated\n");

                break;

            // -----------------------------
            // Create New File
            // -----------------------------
            case 2:
            {
                char fileName[30];
                int requiredBlocks;
                int indexBlock;
                int count = 0;

                if (fileCount >= MAX_FILES)
                {
                    printf("\nDirectory is full!");
                    break;
                }

                printf("\nEnter file name: ");
                scanf("%s", fileName);

                printf("Enter number of data blocks required: ");
                scanf("%d", &requiredBlocks);

                // Find free index block
                indexBlock = -1;

                for (i = 0; i < n; i++)
                {
                    if (bitVector[i] == 0)
                    {
                        indexBlock = i;
                        break;
                    }
                }

                if (indexBlock == -1)
                {
                    printf("\nNo free index block available!");
                    break;
                }

                // Find required data blocks
                for (i = 0; i < n && count < requiredBlocks; i++)
                {
                    if (bitVector[i] == 0 && i != indexBlock)
                    {
                        directory[fileCount].blocks[count] = i;
                        count++;
                    }
                }

                if (count < requiredBlocks)
                {
                    printf("\nNot enough free blocks!");
                    break;
                }

                // Allocate index block
                bitVector[indexBlock] = 1;

                // Allocate data blocks
                for (i = 0; i < requiredBlocks; i++)
                {
                    bitVector[directory[fileCount].blocks[i]] = 1;
                }

                // Store file information
                strcpy(directory[fileCount].name, fileName);

                directory[fileCount].indexBlock = indexBlock;
                directory[fileCount].blockCount = requiredBlocks;

                fileCount++;

                printf("\nFile created successfully!");

                printf("\nIndex Block = %d", indexBlock);

                printf("\nData Blocks = ");

                for (i = 0; i < requiredBlocks; i++)
                {
                    printf("%d ",
                           directory[fileCount - 1].blocks[i]);
                }

                printf("\n");

                break;
            }

            // -----------------------------
            // Show Directory
            // -----------------------------
            case 3:

                if (fileCount == 0)
                {
                    printf("\nDirectory is empty.");
                }
                else
                {
                    printf("\n\n========== DIRECTORY ==========\n");

                    printf("File\tIndex Block\tData Blocks\n");

                    for (i = 0; i < fileCount; i++)
                    {
                        printf("%s\t%d\t\t",
                               directory[i].name,
                               directory[i].indexBlock);

                        for (j = 0;
                             j < directory[i].blockCount;
                             j++)
                        {
                            printf("%d ",
                                   directory[i].blocks[j]);
                        }

                        printf("\n");
                    }
                }

                break;

            // -----------------------------
            // Exit
            // -----------------------------
            case 4:

                printf("\nProgram terminated.");
                break;

            default:

                printf("\nInvalid choice!");
        }

    } while (choice != 4);

    return 0;
}


/**Q.2 Write a program that demonstrates the use of nice () system call. After a 
child process is started using fork(), assign higher priority to the child using  
nice() system call */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    pid_t pid;

    printf("Parent Process Started\n");
    printf("Parent PID = %d\n", getpid());

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }

    else if (pid == 0)
    {
        // Child Process

        int oldNice;
        int newNice;

        printf("\nChild Process Started\n");
        printf("Child PID = %d\n", getpid());

        // Get current nice value
        errno = 0;
        oldNice = nice(0);

        printf("Initial Nice Value = %d\n", oldNice);

        // Increase priority
        errno = 0;
        newNice = nice(-5);

        if (newNice == -1 && errno != 0)
        {
            perror("nice");
        }
        else
        {
            printf("New Nice Value = %d\n", newNice);
            printf("Child priority increased.\n");
        }

        printf("Child Process is running...\n");

        for (long i = 0; i < 500000000; i++)
        {
            // CPU intensive work
        }

        printf("Child Process Finished\n");
    }

    else
    {
        // Parent Process

        printf("\nParent is waiting for child...\n");

        wait(NULL);

        printf("Child Process Completed\n");
        printf("Parent Process Finished\n");
    }

    return 0;
}