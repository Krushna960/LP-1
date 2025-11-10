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

    int frame[10], last_used[10];
    for (int i = 0; i < f; i++) {
        frame[i] = -1;       // empty frames
        last_used[i] = -1;   // time of last use
    }

    int page_faults = 0;

    cout << "\nPage\tFrames\t\tStatus\n";
    cout << "-----------------------------------\n";

    for (int i = 0; i < n; i++) {
        bool hit = false;

        // Check if page already in frame
        for (int j = 0; j < f; j++) {
            if (frame[j] == pages[i]) {
                hit = true;
                last_used[j] = i; // update recent use time
                break;
            }
        }

        if (!hit) {
            int pos = -1;

            // Find empty frame
            for (int j = 0; j < f; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, replace least recently used page
            if (pos == -1) {
                int lru = 9999, min_index = -1;
                for (int j = 0; j < f; j++) {
                    if (last_used[j] < lru) {
                        lru = last_used[j];
                        min_index = j;
                    }
                }
                pos = min_index;
            }

            frame[pos] = pages[i];
            last_used[pos] = i;
            page_faults++;
        }

        // Display current status
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
