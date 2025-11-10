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
        frame[i] = -1;

    int page_faults = 0;

    cout << "\nPage\tFrames\t\tStatus\n";
    cout << "-----------------------------------\n";

    for (int i = 0; i < n; i++) {
        bool hit = false;

        // Check if page is already in frame
        for (int j = 0; j < f; j++) {
            if (frame[j] == pages[i]) {
                hit = true;
                break;
            }
        }

        if (!hit) {
            int pos = -1;

            // If frame has empty space
            for (int j = 0; j < f; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, find the optimal one to replace
            if (pos == -1) {
                int farthest = -1, replace_index = -1;
                for (int j = 0; j < f; j++) {
                    int next_use = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (frame[j] == pages[k]) {
                            next_use = k;
                            break;
                        }
                    }
                    // If not used again
                    if (next_use == -1) {
                        replace_index = j;
                        break;
                    }
                    if (next_use > farthest) {
                        farthest = next_use;
                        replace_index = j;
                    }
                }
                pos = replace_index;
            }

            frame[pos] = pages[i];
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
