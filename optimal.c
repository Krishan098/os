#include <stdio.h>

// Function to find the page to replace using the optimal algorithm
int findOptimalPage(int frames[], int framesCount, int pages[], int n, int currentIndex) {
    int farthest = currentIndex;
    int index = -1;

    for (int i = 0; i < framesCount; i++) {
        int j;
        for (j = currentIndex; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == n) {
            return i; // If the page is not used again, replace it
        }
    }

    return (index == -1) ? 0 : index; // Replace the page that is used farthest
}

// Function to implement the Optimal Page Replacement Algorithm
void Optimal_PageReplacement(int pages[], int n, int framesCount) {
    int frames[framesCount]; // Store the frames
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

        // If the page is not found, replace a page
        if (!found) {
            int replaceIndex = -1;

            // If there are empty slots, use them first
            for (int j = 0; j < framesCount; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            // If all slots are full, find the optimal page to replace
            if (replaceIndex == -1) {
                replaceIndex = findOptimalPage(frames, framesCount, pages, n, i + 1);
            }

            frames[replaceIndex] = pages[i];
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

    // Call the Optimal function
    Optimal_PageReplacement(pages, n, framesCount);

    return 0;
}
