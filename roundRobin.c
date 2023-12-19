#include <stdio.h>

int at[100], bt[100], rt[100], temp[100];
float wait_time = 0, turn_time = 0;

int main()
{
    int c, j, n, time, r, flag = 0, time_q, ltt, i, wt = 0;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    r = n;

    // Input arrival and burst time for each process
    for (c = 0; c < n; c++)
    {
        printf("Enter arrival time of P%d: ", c + 1);
        scanf("%d", &at[c]);
        printf("Enter burst time of P%d: ", c + 1);
        scanf("%d", &bt[c]);
        rt[c] = bt[c];
        temp[c] = bt[c];
        printf("\n");
    }

    // Input time quantum
    printf("Enter time quantum: ");
    scanf("%d", &time_q);

    printf("\n\n\tProcess\tArrival Time\tTurnaround Time\tWaiting Time\n\n");

    // Perform round robin scheduling
    for (time = 0, c = 0; r != 0;)
    {
        if (rt[c] <= time_q && rt[c] > 0)
        {
            time = time + rt[c];
            rt[c] = 0;
            flag = 1;
        }
        else if (rt[c] > 0)
        {
            rt[c] = rt[c] - time_q;
            time = time + time_q;
        }

        if (rt[c] == 0 && flag == 1)
        {
            wt = 0;
            wt = time - at[c] - bt[c];
            r--;

            // Print the turnaround time and waiting time for each process
            printf("\tP%d\t%d\t%d\t%d\n", c + 1, at[c], time - at[c], wt);

            ltt = time - at[c];
            wait_time = wait_time + time - at[c] - bt[c];
            turn_time = turn_time + time - at[c];
            flag = 0;
        }

        if (c == n - 1)
            c = 0;
        else if (at[c + 1] <= time)
            c++;
        else
            c = 0;
    }

    j = 0;

    printf("\n\n\n");
    printf("Gantt Chart ");
    printf("\n\n\n");
    printf("\t");

    // Print the Gantt Chart
    for (i = at[0]; i < time;)
    {
        if (bt[j] >= time_q)
        {
            printf("P%d\t", j + 1);
            i += time_q;
            bt[j] = bt[j] - time_q;
        }
        else if (bt[j] > 0)
        {
            printf("P%d\t", j + 1);
            i += bt[j];
            bt[j] = 0;
        }
        j++;

        if (j >= n)
        {
            j = 0;
        }
    }

    printf("\n");
    j = 0;
    printf("\t");

    // Print the time sequence
    for (i = at[0]; i < time;)
    {
        if (temp[j] >= time_q)
        {
            printf("%d\t", i + time_q);
            i += time_q;
            temp[j] = temp[j] - time_q;
        }
        else if (temp[j] > 0)
        {
            printf("%d\t", i + temp[j]);
            i += temp[j];
            temp[j] = 0;
        }
        j++;

        if (j >= n)
        {
            j = 0;
        }
    }

    printf("\n\n\n");
    printf("\nAverage waiting time = %f\n", wait_time / n);
    printf("Average turnaround time = %f\n", turn_time / n);

    return 0;
}
