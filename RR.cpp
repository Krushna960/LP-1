#include<iostream>
using namespace std;

int main(){
    int n, qt;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], rt[n], bt[n], ct[n], tat[n], wt[n];
    int i, time = 0, remain = n;
    float avgwt = 0, avgtat = 0;

    for(i=0;i<n;i++){
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> at[i] >> bt[i];
        rt[i] = bt[i];
    }

    cout << "Enter time quantum: ";
    cin >> qt;

    //process scheduling
    while(remain != 0){
        for(i=0;i<n;i++){
            if(rt[i]>0 && at[i]<=time){
                if(rt[i]>qt){
                    //process run for time quantum
                    time += qt;
                    rt[i] -= qt;
                }else{
                    //process finishes in this round
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;//completion time
                    tat[i] = ct[i] - at[i];//turn around time
                    wt[i] = tat[i] - bt[i];//waiting time
                    avgwt += wt[i];
                    avgtat += tat[i];
                    remain--;
                }
            }
        }
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for(i=0;i<n;i++){
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }
    cout << "\nAverage Turn Around Time: " << avgtat/n;
    cout << "\nAverage Waiting Time: " << avgwt/n << "\n";
    return 0;
}
