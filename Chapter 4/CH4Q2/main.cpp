#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define MAX 100

int main() {
    vector<string> keyword;
    vector<int> L;
    vector<int> R;
    string S;
    string temp;
    int count = 0;
    int wordlength = 0;

    for (int i = 0; i < MAX; i++) {
        cin >> temp;

        if (temp == "end") {
            break;
        }

        count = count + 1;

        keyword.push_back(temp);
    }

    for (int i = 0; i < count; i++) {
        wordlength = max(keyword[i].length(), keyword[i + 1].length());

        string longer;
        string shorter;
        int llen = 0;

        if (keyword[i].length() > keyword[i + 1].length()) {
            longer = keyword[i];
            shorter = keyword[i + 1];
            shorter = string(shorter.rbegin(), shorter.rend());
        }

        else {
            longer = keyword[i + 1];
            shorter = keyword[i];
            shorter = string(shorter.rbegin(), shorter.rend());
        }

        for (int j = 0; j < wordlength; j++) {
            if (longer[j] == shorter[j]) {
                llen = llen + 1;
            }

            else {
                break;
            }
        }

        L.push_back(llen);
    }

    for (int i = 0; i < count; i++) {
        wordlength = max(keyword[i].length(), keyword[i + 1].length());

        string longer;
        string shorter;
        int rlen = 0;

        if (keyword[i].length() > keyword[i + 1].length()) {
            longer = keyword[i];
            shorter = keyword[i + 1];
            longer = string(longer.rbegin(), longer.rend());
        }

        else {
            longer = keyword[i + 1];
            shorter = keyword[i];
            longer = string(longer.rbegin(), longer.rend());
        }

        for (int j = 0; j < wordlength; j++) {
            if (longer[j] == shorter[j]) {
                rlen = rlen + 1;
            }

            else {
                break;
            }
        }

        R.push_back(rlen);
    }

    // Not finished
}
