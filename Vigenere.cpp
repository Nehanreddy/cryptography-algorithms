#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to repeat or truncate the keyword to match the message length
string generateKey(const string& text, const string& keyword) {
    string key;
    int keyLen = keyword.length();
    for (int i = 0, j = 0; i < text.length(); ++i) {
        if (isalpha(text[i])) {
            key += keyword[j % keyLen];
            j++;
        } else {
            key += text[i]; // to preserve non-alphabet characters if needed
        }
    }
    return key;
}

int main() {
    string text, keyword, result;
    char choice;

    cout << "Do you want to (E)ncrypt or (D)ecrypt using Vigenère Cipher? ";
    cin >> choice;
    choice = toupper(choice);

    if (choice != 'E' && choice != 'D') {
        cout << "Invalid choice. Please enter E or D." << endl;
        return 1;
    }

    cout << "Enter the message: ";
    cin >> text;

    cout << "Enter the keyword: ";
    cin >> keyword;

    string key = generateKey(text, keyword);

    for (int i = 0; i < text.length(); ++i) {
        char ch = text[i];

        if (isalpha(ch)) {
            bool isLower = islower(ch);
            char base = isLower ? 'a' : 'A';

            char keyCh = tolower(key[i]);
            int shift = keyCh - 'a';

            if (choice == 'E') {
                ch = (ch - base + shift) % 26 + base;
            } else {
                ch = (ch - base - shift + 26) % 26 + base;
            }

            result += ch;
        } else {
            cout << "Invalid character in message. Only letters allowed." << endl;
            return 1;
        }
    }

    if (choice == 'E')
        cout << "Encrypted message: " << result << endl;
    else
        cout << "Decrypted message: " << result << endl;

    return 0;
}
