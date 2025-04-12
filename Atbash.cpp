#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string text;
    char choice;

    cout << "Do you want to (E)ncrypt or (D)ecrypt using Atbash Cipher? ";
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
            if (islower(ch)) {
                ch = 'z' - (ch - 'a');
            } else if (isupper(ch)) {
                ch = 'Z' - (ch - 'A');
            }
        }
        else if (isdigit(ch)) {
            ch = '9' - (ch - '0');
        }
        else {
            cout << "Invalid character in message. Only letters and digits are allowed." << endl;
            return 1;
        }

        text[i] = ch;
    }

    cout << "Resulting message: " << text << endl;

    return 0;
}
