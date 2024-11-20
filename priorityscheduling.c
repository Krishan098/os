#include <stdio.h>

// Function to calculate waiting time
void calculateWaitingTime(int processes[], int n, int burstTime[], int waitingTime[]) {
    waitingTime[0] = 0; // First process has no waiting time

    for (int i = 1; i < n; i++) {
        waitingTime[i] = burstTime[i - 1] + waitingTime[i - 1];
    }
}

// Function to calculate turnaround time
void calculateTurnaroundTime(int processes[], int n, int burstTime[], int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }
}

// Function to sort processes by priority
void sortProcessesByPriority(int processes[], int n, int burstTime[], int priority[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (priority[j] > priority[j + 1]) { // Higher priority (lower number) first
                // Swap priorities
                int tempPriority = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = tempPriority;

                // Swap burst times
                int tempBurst = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = tempBurst;

                // Swap process numbers
                int tempProcess = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = tempProcess;
            }
        }
    }
}

// Function to calculate and display average time
void calculateAverageTime(int processes[], int n, int burstTime[], int priority[]) {
    int waitingTime[n], turnaroundTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Sort processes by priority
    sortProcessesByPriority(processes, n, burstTime, priority);

    // Calculate waiting and turnaround times
    calculateWaitingTime(processes, n, burstTime, waitingTime);
    calculateTurnaroundTime(processes, n, burstTime, waitingTime, turnaroundTime);

    printf("Processes   Burst Time   Priority   Waiting Time   Turnaround Time\n");

    // Display process details and calculate totals
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
        printf("    %d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i], burstTime[i], priority[i], waitingTime[i], turnaroundTime[i]);
    }

    // Calculate and display average times
    printf("\nAverage Waiting Time = %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time = %.2f\n", (float)totalTurnaroundTime / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burstTime[n], priority[n];

    // Input burst times and priorities for each process
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &priority[i]);
    }

    // Calculate and display results
    calculateAverageTime(processes, n, burstTime, priority);

    return 0;
}
