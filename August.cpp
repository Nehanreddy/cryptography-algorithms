#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string text;
    char choice;
    int key = 1;
    cout << "Do you want to (E)ncrypt or (D)ecrypt using Caesar Cipher (Shift 1)? ";
    cin >> choice;
    choice = toupper(choice);

    if (choice != 'E' && choice != 'D') {
        cout << "Invalid choice. Please enter E for Encrypt or D for Decrypt." << endl;
        return 1;
    }

    cout << "Enter the message: ";
    cin >> text;
    for (int i = 0; i < text.length(); ++i) {
        char ch = text[i];

        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            int shift = (choice == 'E') ? key : (26 - key);
            ch = (ch - base + shift) % 26 + base;
        } else {
            cout << "Invalid character in message. Only letters are allowed." << endl;
            return 1;
        }

        text[i] = ch;
    }

    if (choice == 'E')
        cout << "Encrypted message: " << text << endl;
    else
        cout << "Decrypted message: " << text << endl;

    return 0;
}
