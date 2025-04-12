#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

string preprocessText(const string& input) {
    string cleaned;
    for (char ch : input) {
        if (isalpha(ch)) {
            cleaned += toupper(ch);
        }
    }
    return cleaned;
}

void countNgrams(const string& text, int n) {
    if (text.length() < n) {
        cout << "Text is too short for " << n << "-grams.\n";
        return;
    }

    map<string, int> ngramFreq;

    for (size_t i = 0; i <= text.length() - n; ++i) {
        string ngram = text.substr(i, n);
        ngramFreq[ngram]++;
    }

    cout << "\n--- " << n << "-gram Frequencies ---\n";
    for (const auto& entry : ngramFreq) {
        cout << entry.first << " : " << entry.second << '\n';
    }
}

int main() {
    string input;
    int choice;

    cout << "Enter the text: ";
    getline(cin, input);

    string cleanedText = preprocessText(input);

    cout << "\nChoose N-gram type:\n";
    cout << "1. Unigram\n";
    cout << "2. Bigram (Digram)\n";
    cout << "3. Trigram\n";
    cout << "4. Tetragram\n";
    cout << "Enter choice (1-4): ";
    cin >> choice;

    switch (choice) {
        case 1:
            countNgrams(cleanedText, 1);
            break;
        case 2:
            countNgrams(cleanedText, 2);
            break;
        case 3:
            countNgrams(cleanedText, 3);
            break;
        case 4:
            countNgrams(cleanedText, 4);
            break;
        default:
            cout << "Invalid choice.\n";
    }

    return 0;
}
