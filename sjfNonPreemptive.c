
#include <stdio.h>
int findShortestProcess(int arrivalTime[], int burstTime[], int timeCounter, int n)
{
    int pid = -1, lowestBurstTime = 10000;
    for (int i = 0; i < n; i++)
    {
        if (arrivalTime[i] <= timeCounter && burstTime[i] >= 0 && burstTime[i] < lowestBurstTime)
        {
            pid = i;
            lowestBurstTime = burstTime[i];
        }
    }
    return pid;
}

float findAvg(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return (float)sum / n;
}
int main()
{
    // printf("Hello World");
    int n;
    printf("Enter the number of process :");
    scanf("%d", &n);
    int burstTime[n], OriginalBurstTime[n], arrivalTime[n], waitingTime[n], turnAroundTime[n], processOrder[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time of process %d : ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Enter the burst time of process %d : ", i + 1);
        scanf("%d", &burstTime[i]);
        OriginalBurstTime[i] = burstTime[i];
    }

    int timeCounter = 0, processesCompleted = 0;

    while (processesCompleted < n)
    {
        int pid = findShortestProcess(arrivalTime, burstTime, timeCounter, n);
        if (pid == -1)
        {
            timeCounter++;
            continue;
        }
        processOrder[processesCompleted] = pid;
        waitingTime[pid] = timeCounter - arrivalTime[pid];
        turnAroundTime[pid] = waitingTime[pid] + burstTime[pid];
        timeCounter += burstTime[pid];
        burstTime[pid] = -1;
        processesCompleted++;
    }

    printf("\nprocess\tarrivalTime\tburstTime\twaitingTime\tTurnAroundTime");
    for (int i = 0; i < n; i++)
    {
        printf("\n%d\t%d\t%d\t%d\t%d", processOrder[i] + 1, arrivalTime[processOrder[i]], OriginalBurstTime[processOrder[i]], waitingTime[processOrder[i]], turnAroundTime[processOrder[i]]);
    }

    printf("\n\nAverage waiting Time : %f", findAvg(waitingTime, n));
    printf("\n\nAverage turnAroundTime Time : %f", findAvg(turnAroundTime, n));

    return 0;
}
