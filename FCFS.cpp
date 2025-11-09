#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of precess: ";
    cin >> n;

    int at[n], bt[n], ct[n], tat[n], wt[n];
    float avg_tat = 0, avg_wt = 0;

    // input
    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> at[i] >> bt[i];
    }
    // first process completion time
    ct[0] = at[0] + bt[0];

    // completion time
    for (int i = 1; i < n; i++)
    {
         if(at[i] > ct[i-1]){
            ct[i] = at[i] + bt[i];
         } else {
            ct[i] = ct[i - 1] + bt[i];
         }
    }

    // turn around time and waiting time
    for (int i = 0; i < n; i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    // output
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t" 
        << at[i] << "\t" 
        << bt[i] << "\t" 
        << ct[i] << "\t" 
        << tat[i] << "\t" 
        << wt[i] << "\n";
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage Turn Around Time: " << (avg_tat / n);
    cout << "\nAverage Waiting Time: " << (avg_wt / n) << "\n";
    return 0;
}