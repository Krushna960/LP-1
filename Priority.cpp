#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[10], bt[10], pr[10], ct[10], tat[10], wt[10];
    bool done[10] = {false};
    float total_tat = 0, total_wt = 0;

    // Input
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time, Burst Time, and Priority for P" << i + 1 << ": ";
        cin >> at[i] >> bt[i] >> pr[i];
    }

    int time = 0, completed = 0;

    while (completed < n) {
        int index = -1;
        int highest = 9999; // smaller number = higher priority

        // Find process with highest priority among arrived
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !done[i] && pr[i] < highest) {
                highest = pr[i];
                index = i;
            }
        }

        // If no process has arrived yet
        if (index == -1) {
            time++;
            continue;
        }

        // Execute selected process completely
        time += bt[index];
        ct[index] = time;
        tat[index] = ct[index] - at[index];
        wt[index] = tat[index] - bt[index];

        done[index] = true;
        completed++;
    }

    cout << "\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    cout << "--------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << pr[i]
             << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
        total_tat += tat[i];
        total_wt += wt[i];
    }

    cout << "\nAverage Turnaround Time = " << total_tat / n;
    cout << "\nAverage Waiting Time = " << total_wt / n << endl;

    return 0;
}
