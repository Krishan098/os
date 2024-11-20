#include <stdio.h>

// Function to calculate waiting time using Round Robin
void calculateWaitingTime(int processes[], int n, int burstTime[], int waitingTime[], int quantum) {
    int remainingBurstTime[n];
    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = burstTime[i]; // Copy burst times
    }

    int t = 0; // Current time

    while (1) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (remainingBurstTime[i] > 0) {
                done = 0; // There are processes still pending

                if (remainingBurstTime[i] > quantum) {
                    t += quantum;
                    remainingBurstTime[i] -= quantum;
                } else {
                    t += remainingBurstTime[i];
                    waitingTime[i] = t - burstTime[i];
                    remainingBurstTime[i] = 0;
                }
            }
        }

        if (done == 1) break; // Exit loop when all processes are done
    }
}

// Function to calculate turnaround time
void calculateTurnaroundTime(int processes[], int n, int burstTime[], int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }
}

// Function to calculate and display average time
void calculateAverageTime(int processes[], int n, int burstTime[], int quantum) {
    int waitingTime[n], turnaroundTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Calculate waiting and turnaround times
    calculateWaitingTime(processes, n, burstTime, waitingTime, quantum);
    calculateTurnaroundTime(processes, n, burstTime, waitingTime, turnaroundTime);

    printf("Processes   Burst Time   Waiting Time   Turnaround Time\n");

    // Display process details and calculate totals
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
        printf("    %d\t\t%d\t\t%d\t\t%d\n", processes[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }

    // Calculate and display average times
    printf("\nAverage Waiting Time = %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time = %.2f\n", (float)totalTurnaroundTime / n);
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burstTime[n];

    // Input burst times for each process
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Calculate and display results
    calculateAverageTime(processes, n, burstTime, quantum);

    return 0;
}
