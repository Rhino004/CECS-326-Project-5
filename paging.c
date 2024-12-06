#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

// Function to check if a page is in memory
bool isPageInMemory(int frames[], int frameSize, int page) {
    for (int i = 0; i < frameSize; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to print memory state
void printMemoryState(int frames[], int frameSize) {
    printf("[");
    for (int i = 0; i < frameSize; i++) {
        if (frames[i] == -1) {
            printf("-");
        } else {
            printf("%d", frames[i]);
        }
        if (i < frameSize - 1) {
            printf(", ");
        }
    }
    printf("]");
}

// FIFO Page Replacement Algorithm
int fifoPageReplacement(int pages[], int pageCount, int frameSize) {
    int frames[MAX_FRAMES];
    int pageFaults = 0, nextToReplace = 0;

    // Initialize frames
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
    }

    printf("\nFIFO Page Replacement:\n");
    printf("Step | Page | Memory State      | Page Fault?\n");
    printf("-----|------|-------------------|------------\n");

    for (int i = 0; i < pageCount; i++) {
        printf("%4d | %4d | ", i + 1, pages[i]);
        if (!isPageInMemory(frames, frameSize, pages[i])) {
            frames[nextToReplace] = pages[i];
            nextToReplace = (nextToReplace + 1) % frameSize;
            pageFaults++;
            printMemoryState(frames, frameSize);
            printf("      | Yes\n");
        } else {
            printMemoryState(frames, frameSize);
            printf("      | No\n");
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
    return pageFaults;
}

// LRU Page Replacement Algorithm
int lruPageReplacement(int pages[], int pageCount, int frameSize) {
    int frames[MAX_FRAMES], lastUsed[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    printf("\nLRU Page Replacement:\n");
    printf("Step | Page | Memory State      | Page Fault?\n");
    printf("-----|------|-------------------|------------\n");

    for (int i = 0; i < pageCount; i++) {
        printf("%4d | %4d | ", i + 1, pages[i]);
        if (!isPageInMemory(frames, frameSize, pages[i])) {
            int lruIndex = 0;
            for (int j = 1; j < frameSize; j++) {
                if (lastUsed[j] < lastUsed[lruIndex]) {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = pages[i];
            lastUsed[lruIndex] = i;
            pageFaults++;
            printMemoryState(frames, frameSize);
            printf("      | Yes\n");
        } else {
            for (int j = 0; j < frameSize; j++) {
                if (frames[j] == pages[i]) {
                    lastUsed[j] = i;
                    break;
                }
            }
            printMemoryState(frames, frameSize);
            printf("      | No\n");
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
    return pageFaults;
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
    printf("Enter the number of frames: ");
    scanf("%d", &frameSize);

    // Run FIFO
    fifoPageReplacement(pages, pageCount, frameSize);
    // Run LRU
    lruPageReplacement(pages, pageCount, frameSize);

    return 0;

}
