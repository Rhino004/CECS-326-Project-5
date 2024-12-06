#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

// Function to check if a page is in memory


// Function to print memory state


// FIFO Page Replacement Algorithm


// LRU Page Replacement Algorithm


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
    
    // Run LRU

}