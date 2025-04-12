#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string text;
    char choice;
    int key;

    cout << "Do you want to (E)ncrypt or (D)ecrypt? ";
    cin >> choice;

    choice = toupper(choice);

    if (choice != 'E' && choice != 'D') {
        cout << "Invalid choice. Please enter E for Encrypt or D for Decrypt." << endl;
        return 1;
    }

    cout << "Enter the message: ";
    cin >> text;
    cout << "Enter the key: ";
    cin >> key;

    for (int i = 0; i < text.length(); ++i) {
        char ch = text[i];
        if (isalnum(ch)) {
            if (islower(ch)) {
                if (choice == 'E')
                    ch = (ch - 'a' + key) % 26 + 'a';
                else
                    ch = (ch - 'a' - key + 26) % 26 + 'a';
            }
            else if (isupper(ch)) {
                if (choice == 'E')
                    ch = (ch - 'A' + key) % 26 + 'A';
                else
                    ch = (ch - 'A' - key + 26) % 26 + 'A';
            }
            else if (isdigit(ch)) {
                if (choice == 'E')
                    ch = (ch - '0' + key) % 10 + '0';
                else
                    ch = (ch - '0' - key + 10) % 10 + '0';
            }
        } else {
            cout << "Invalid character in message. Only letters and digits are allowed." << endl;
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
