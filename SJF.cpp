#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[10], bt[10], ct[10], tat[10], wt[10];
    bool done[10] = {false};
    float avg_tat = 0, avg_wt = 0;

    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time for P" << i + 1 << ": ";
        cin >> at[i] >> bt[i];
    }

    int completed = 0, time = 0;

    while (completed < n) {
        int idx = -1, min_bt = 9999;

        // Find process with shortest burst time among arrived
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !done[i] && bt[i] < min_bt) {
                min_bt = bt[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++; // No process has arrived yet
            continue;
        }

        time += bt[idx];
        ct[idx] = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        done[idx] = true;
        completed++;
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "---------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i]
             << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    cout << "\nAverage Turnaround Time = " << avg_tat / n;
    cout << "\nAverage Waiting Time = " << avg_wt / n << endl;

    return 0;
}
