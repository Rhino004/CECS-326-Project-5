# CECS-326-Project-5

# Page Replacement Algorithms

This program simulates two page replacement algorithms to manage virtual memory and page frames.
**FIFO (First-In-First-Out)** and **LRU (Least Recently Used)**,
It calculates and displays the number of page faults and the memory state at each step for a given page reference sequence and frame sizes.

## Prerequisites

- A C compiler (e.g., `gcc`) installed on your system.

## How to Compile the Code

`gcc -o paging paging.c`

## How to Run the Code

`/paging`

## Arguments

`Enter the Page Request Sequence (e.g. 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2): 7,0,1,2,0,3,0,4,2,3,0,3,2`
`Enter the Frame Sizes (e.g. 2, 3, 4): 2,3,4`

