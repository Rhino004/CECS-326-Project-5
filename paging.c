#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

// Function to check if a page is in memory array
bool PageInMemory(int memory[], int frameSize, int page){
    for (int i =0; i<frameSize; i++){
        if (memory[i] == page){
            return true;
        }
    }
    return false;
}

// Function to print memory state
void PrintMemoryState(int memory[], int frameSize){
    printf("[");
    for (int i = 0; i < frameSize; i++)
    {
        if (memory[i] == -1){
            printf("-");
        }
        else{
            printf("%d", memory[i]);
        }
        if (i < frameSize - 1){
            printf(", ");
        }
    }
    printf("]");
}

// FIFO Page Replacement Algorithm
void FIFO(int pages[], int pageCount, int frameSize)
{
    printf("\nFIFO Algorithm:\n");
    int memory[MAX_FRAMES];
    int pageFaults = 0, nextToReplace = 0;

    // Initialize memory
    for (int i = 0; i < frameSize; i++)
    {
        memory[i] = -1;
    }
    printf("\nFIFO Page Replacement:\n");
    printf("Step | Page | Memory State      | Page Fault?\n");
    printf("-----|------|-------------------|------------\n");

    for (int i = 0; i < pageCount; i++)
    {
        printf("%4d | %4d | ", i + 1, pages[i]);
        if (!PageInMemory(memory, frameSize, pages[i]))
        {
            memory[nextToReplace] = pages[i];
            nextToReplace = (nextToReplace + 1) % frameSize; // Circular queue logic
            pageFaults++;
            PrintMemoryState(memory, frameSize);
            printf("      | Yes\n");
        }
        else
        {
            PrintMemoryState(memory, frameSize);
            printf("      | No\n");
        }
    }

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

// LRU Page Replacement Algorithm
void LRU(int pages[], int pageCount, int frameSize){
    int frames[MAX_FRAMES], lastUsed[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < frameSize; i++)
    {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    printf("\nLRU Page Replacement:\n");
    printf("Step | Page | Memory State      | Page Fault?\n");
    printf("-----|------|-------------------|------------\n");

    for (int i = 0; i < pageCount; i++)
    {
        printf("%4d | %4d | ", i + 1, pages[i]);
        if (!PageInMemory(frames, frameSize, pages[i]))
        {
            int lruIndex = 0;
            for (int j = 1; j < frameSize; j++)
            {
                if (lastUsed[j] < lastUsed[lruIndex])
                {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = pages[i];
            lastUsed[lruIndex] = i;
            pageFaults++;
            PrintMemoryState(frames, frameSize);
            printf("      | Yes\n");
        }
        else
        {
            for (int j = 0; j < frameSize; j++)
            {
                if (frames[j] == pages[i])
                {
                    lastUsed[j] = i;
                    break;
                }
            }
            PrintMemoryState(frames, frameSize);
            printf("      | No\n");
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES], pageCount;
    int frameSize = 2; //frameSiaze can be a random # less than MaxFrame

    // Input
    printf("Enter the number of pages: ");
    scanf("%d", &pageCount); //the size of the reference sequence

    printf("Enter the page reference sequence: ");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]); // the string given
    }
    
    // Run FIFO with 2 frame
    FIFO(pages, pageCount, frameSize);
    // Run LRU with 2 frame
    LRU(pages, pageCount, frameSize);

    frameSize = 3;
    // Run FIFO with 3 frame
    FIFO(pages, pageCount, frameSize);
    // Run LRU with 3 frame
    LRU(pages, pageCount, frameSize);

    frameSize = 4;
    // Run FIFO with 4 frame
    FIFO(pages, pageCount, frameSize);
    // Run LRU with 4 frame
    LRU(pages, pageCount, frameSize);

    return 0;
}