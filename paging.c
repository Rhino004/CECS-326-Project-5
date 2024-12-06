#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

// Function to check if a page is in memory
bool PageInMemory(int page, int memory[], int frameSize){
    return false;
}

// Function to print memory state
void PrintMemoryState(int memory[], int frameSize){
    printf("\n");
}

// FIFO Page Replacement Algorithm
void FIFO(int pages[], int pageCount, int frameSize)
{
}

// LRU Page Replacement Algorithm
void LRU(int pages[], int pageCount, int frameSize){

}

int main() {
    int pages[MAX_PAGES], pageCount, frameSize;

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
}