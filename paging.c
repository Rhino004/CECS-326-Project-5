#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

// Function to check if a page is in memory
bool PageInMemory(int page, int memory[], int frameSize){
    for (int i =0; i<frameSize; i++){
        if (memory[i] == page){
            return true;
        }
    }
    return false;
}

// Function to print memory state
void PrintMemoryState(int memory[], int frameSize){
    printf("Memory: ");
    for(int i = 0; i< frameSize; i++){
        if (memory[i] == -1){
            printf("_");
        }else{
            printf("%d", memory[i]);
        }
    }
    printf("\n");
}

// FIFO Page Replacement Algorithm
void FIFO(int pages[], int pageCount, int frameSize)
{
    printf("\nFIFO Algorithm:\n");
    int memory[MAX_FRAMES];
    int front = 0; // Points to the oldest page
    int pageFaults = 0;

    // Initialize memory with -1
    for (int i = 0; i < frameSize; i++)
    {
        memory[i] = -1;
    }

    for (int i = 0; i < pageCount; i++)
    {
        if (!isPageInMemory(pages[i], memory, frameSize))
        {
            memory[front] = pages[i];
            front = (front + 1) % frameSize; // Circular queue logic
            pageFaults++;
            printf("Page %d caused a fault. ", pages[i]);
        }
        else
        {
            printf("Page %d did not cause a fault. ", pages[i]);
        }
        printMemoryState(memory, frameSize);
    }

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

// LRU Page Replacement Algorithm
void LRU(int pages[], int pageCount, int frameSize){
    printf("\nLRU Algorithm:\n");
    int memory[MAX_FRAMES], recent[MAX_FRAMES];
    int pageFaults = 0;

    // Initialize memory and recent usage trackers
    for (int i = 0; i < frameSize; i++)
    {
        memory[i] = -1;
        recent[i] = -1;
    }

    for (int i = 0; i < pageCount; i++)
    {
        if (!isPageInMemory(pages[i], memory, frameSize))
        {
            int lruIndex = 0;

            // Find the least recently used page
            for (int j = 1; j < frameSize; j++)
            {
                if (recent[j] < recent[lruIndex])
                {
                    lruIndex = j;
                }
            }

            memory[lruIndex] = pages[i];
            pageFaults++;
            printf("Page %d caused a fault. ", pages[i]);
        }
        else
        {
            printf("Page %d did not cause a fault. ", pages[i]);
        }

        // Update recent usage
        for (int j = 0; j < frameSize; j++)
        {
            if (memory[j] != -1)
            {
                recent[j]++;
            }
        }
        recent[i % frameSize] = 0;

        printMemoryState(memory, frameSize);
    }

    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES], pageCount;
    int frameSize = 3; //frameSiaze can be between 1-10

    // Input
    printf("Enter the number of pages: ");
    scanf("%d", &pageCount);

    printf("Enter the page reference sequence: ");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }
    
    // Run FIFO
    Fifo(pages, pageCount, frameSize);
    // Run LRU
    LRU(pages, pageCount, frameSize);

    return 0;
}