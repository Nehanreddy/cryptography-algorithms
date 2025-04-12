#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string generateKey(const string& text, const string& keyword) {
    string key;
    int keyLen = keyword.length();
    for (int i = 0, j = 0; i < text.length(); ++i) {
        if (isalpha(text[i])) {
            key += keyword[j % keyLen];
            j++;
        } else {
            key += text[i]; 
        }
    }
    return key;
}

int main() {
    string text, keyword, result;
    char choice;

    cout << "Do you want to (E)ncrypt or (D)ecrypt using Beaufort Cipher? ";
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
            int keyVal = keyCh - 'a';
            int plainVal = tolower(ch) - 'a';
            int cipherVal = (keyVal - plainVal + 26) % 26;
            char cipherChar = isLower ? ('a' + cipherVal) : ('A' + cipherVal);

            result += cipherChar;
        } else {
            cout << "Invalid character in message. Only letters allowed." << endl;
            return 1;
        }
    }

    cout << ((choice == 'E') ? "Encrypted" : "Decrypted") << " message: " << result << endl;

    return 0;
}
