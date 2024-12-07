#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

// Function to check if a page is in memory array
bool PageInMemory(int memory[], int frameSize, int page) {
    for (int i = 0; i < frameSize; i++) {
        if (memory[i] == page) { return true; }
    }
    return false;
}

// Function to print memory state
void PrintMemoryState(int memory[], int frameSize) {
    printf("[");
    for (int i = 0; i < frameSize; i++) {
        if (memory[i] == -1) { printf("-"); }
        else { printf("%d", memory[i]); }
        if (i < frameSize - 1) { printf(", "); }
    }
    printf("]");
}

// FIFO Page Replacement Algorithm
void FIFO(int pages[], int pageCount, int frameSize) {
    printf("\nFIFO Algorithm (Frames: %d):\n", frameSize);
    int memory[MAX_FRAMES];
    int pageFaults = 0, nextToReplace = 0;

    // Initialize memory
    for (int i = 0; i < frameSize; i++) { memory[i] = -1; }

    printf("Step | Page | Memory State      | Page Fault?\n");
    printf("-----|------|-------------------|------------\n");

    for (int i = 0; i < pageCount; i++) {
        printf("%4d | %4d | ", i + 1, pages[i]);
        if (!PageInMemory(memory, frameSize, pages[i])) {
            memory[nextToReplace] = pages[i];
            nextToReplace = (nextToReplace + 1) % frameSize; // Circular queue logic
            pageFaults++;
            PrintMemoryState(memory, frameSize);
            printf("      | Yes\n");
        } else {
            PrintMemoryState(memory, frameSize);
            printf("      | No\n");
        }
    }
    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

// LRU Page Replacement Algorithm
void LRU(int pages[], int pageCount, int frameSize) {
    int frames[MAX_FRAMES], lastUsed[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    printf("\nLRU Algorithm (Frames: %d):\n", frameSize);
    printf("Step | Page | Memory State      | Page Fault?\n");
    printf("-----|------|-------------------|------------\n");

    for (int i = 0; i < pageCount; i++) {
        printf("%4d | %4d | ", i + 1, pages[i]);
        if (!PageInMemory(frames, frameSize, pages[i])) {
            int lruIndex = 0;
            for (int j = 1; j < frameSize; j++) {
                if (lastUsed[j] < lastUsed[lruIndex]) { lruIndex = j; }
            }
            frames[lruIndex] = pages[i];
            lastUsed[lruIndex] = i;
            pageFaults++;
            PrintMemoryState(frames, frameSize);
            printf("      | Yes\n");
        } else {
            for (int j = 0; j < frameSize; j++) {
                if (frames[j] == pages[i]) {
                    lastUsed[j] = i;
                    break;
                }
            }
            PrintMemoryState(frames, frameSize);
            printf("      | No\n");
        }
    }
    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

int main() {
    char pageInput[256];
    char frameInput[256];
    int pages[MAX_PAGES], pageCount = 0;
    int frameSizes[MAX_FRAMES], frameCount = 0;

    // Input: Page Request Sequence
    printf("Enter the Page Request Sequence (e.g. 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2): ");
    scanf(" %[^\n]", pageInput);

    // Parse the page sequence
    char *token = strtok(pageInput, ",");
    while (token != NULL && pageCount < MAX_PAGES) {
        pages[pageCount++] = atoi(token);
        token = strtok(NULL, ",");
    }

    // Input: Number of Frames
    printf("Enter the Frame Sizes (e.g. 2, 3, 4): ");
    scanf(" %[^\n]", frameInput);

    // Parse the frame sizes
    token = strtok(frameInput, ",");
    while (token != NULL && frameCount < MAX_FRAMES) {
        frameSizes[frameCount++] = atoi(token);
        token = strtok(NULL, ",");
    }

    // Run algorithms for each frame size
    for (int i = 0; i < frameCount; i++) {
        FIFO(pages, pageCount, frameSizes[i]);
        LRU(pages, pageCount, frameSizes[i]);
    }

    return 0;
}
