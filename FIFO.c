#include <stdio.h>

void FIFO_PageReplacement(int pages[], int n, int framesCount) {
    int frames[framesCount]; // Store the frames
    int front = 0;           // Points to the next frame to replace
    int pageFaults = 0;      // Count of page faults
    int found;

    // Initialize frames with -1 (indicating empty)
    for (int i = 0; i < framesCount; i++) {
        frames[i] = -1;
    }

    // Process each page in the reference string
    for (int i = 0; i < n; i++) {
        found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If the page is not found, replace the oldest page
        if (!found) {
            frames[front] = pages[i];
            front = (front + 1) % framesCount; // Circular increment
            pageFaults++;

            // Display frame contents
            printf("Page %d caused a page fault: ", pages[i]);
            for (int j = 0; j < framesCount; j++) {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int n, framesCount;

    // Input number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];

    // Input the reference string
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &framesCount);

    // Call the FIFO function
    FIFO_PageReplacement(pages, n, framesCount);

    return 0;
}
