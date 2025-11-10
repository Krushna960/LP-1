#include <iostream>
using namespace std;

int main() {
    int n, f;
    cout << "Enter number of pages: ";
    cin >> n;

    int pages[30];
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> f;

    int frame[10];
    for (int i = 0; i < f; i++)
        frame[i] = -1; // initially all frames empty

    int page_faults = 0, next = 0;

    cout << "\nPage\tFrames\t\tStatus\n";
    cout << "---------------------------------\n";

    for (int i = 0; i < n; i++) {
        bool hit = false;

        // Check if page already present
        for (int j = 0; j < f; j++) {
            if (frame[j] == pages[i]) {
                hit = true;
                break;
            }
        }

        if (!hit) {
            // Replace the oldest page (FIFO)
            frame[next] = pages[i];
            next = (next + 1) % f;
            page_faults++;
        }

        cout << pages[i] << "\t";
        for (int j = 0; j < f; j++) {
            if (frame[j] != -1)
                cout << frame[j] << " ";
            else
                cout << "- ";
        }
        cout << "\t" << (hit ? "Hit" : "Fault") << endl;
    }

    cout << "\nTotal Page Faults = " << page_faults << endl;
    cout << "Total Hits = " << n - page_faults << endl;
    cout << "Hit Ratio = " << (float)(n - page_faults) / n << endl;
    cout << "Miss Ratio = " << (float)page_faults / n << endl;

    return 0;
}
