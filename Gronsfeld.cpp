#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string generateNumericKey(const string& text, const string& key) {
    string fullKey;
    for (int i = 0, j = 0; i < text.length(); ++i) {
        if (isalpha(text[i])) {
            fullKey += key[j % key.length()];
            j++;
        } else {
            fullKey += text[i]; 
        }
    }
    return fullKey;
}

int main() {
    string text, key, result;
    char choice;

    cout << "Do you want to (E)ncrypt or (D)ecrypt using Gronsfeld Cipher? ";
    cin >> choice;
    choice = toupper(choice);

    if (choice != 'E' && choice != 'D') {
        cout << "Invalid choice. Please enter E or D." << endl;
        return 1;
    }

    cout << "Enter the message: ";
    cin >> text;

    cout << "Enter the numeric key (digits only): ";
    cin >> key;

    // Validate key
    for (char digit : key) {
        if (!isdigit(digit)) {
            cout << "Invalid key. Only digits (0–9) are allowed." << endl;
            return 1;
        }
    }

    string fullKey = generateNumericKey(text, key);

    for (int i = 0; i < text.length(); ++i) {
        char ch = text[i];

        if (isalpha(ch)) {
            bool isLower = islower(ch);
            char base = isLower ? 'a' : 'A';

            int shift = fullKey[i] - '0';

            if (choice == 'E') {
                ch = (ch - base + shift) % 26 + base;
            } else {
                ch = (ch - base - shift + 26) % 26 + base;
            }

            result += ch;
        } else {
            cout << "Invalid character in message. Only letters are allowed." << endl;
            return 1;
        }
    }

    if (choice == 'E')
        cout << "Encrypted message: " << result << endl;
    else
        cout << "Decrypted message: " << result << endl;

    return 0;
}
