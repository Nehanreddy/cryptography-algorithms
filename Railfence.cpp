#include <iostream>
#include <string>
using namespace std;

string encryptMessage(string plaintext, int rails) {
   
    char rail[rails][plaintext.length()];

   
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < plaintext.length(); j++) {
            rail[i][j] = '\n';
        }
    }

    bool moveDown = false;
    int row = 0, col = 0;
    for (int i = 0; i < plaintext.length(); i++) {
        if (row == 0 || row == rails - 1) {
            moveDown = !moveDown;
        }
        rail[row][col++] = plaintext[i];
        moveDown ? row++ : row--;
    }
    string ciphertext;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < plaintext.length(); j++) {
            if (rail[i][j] != '\n') {
                ciphertext.push_back(rail[i][j]);
            }
        }
    }
    return ciphertext;
}

string decryptMessage(string ciphertext, int rails) {
    char rail[rails][ciphertext.length()];

    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < ciphertext.length(); j++) {
            rail[i][j] = '\n';
        }
    }

    bool moveDown = true;
    int row = 0, col = 0;

    for (int i = 0; i < ciphertext.length(); i++) {
        if (row == 0) {
            moveDown = true;
        }
        if (row == rails - 1) {
            moveDown = false;
        }
        rail[row][col++] = '*';
        moveDown ? row++ : row--;
    }

    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < ciphertext.length(); j++) {
            if (rail[i][j] == '*' && index < ciphertext.length()) {
                rail[i][j] = ciphertext[index++];
            }
        }
    }

    string plaintext;
    row = 0, col = 0;
    for (int i = 0; i < ciphertext.length(); i++) {
        if (row == 0) {
            moveDown = true;
        }
        if (row == rails - 1) {
            moveDown = false;
        }

        if (rail[row][col] != '*') {
            plaintext.push_back(rail[row][col++]);
        }
        moveDown ? row++ : row--;
    }
    return plaintext;
}

int main() {
    int rails;
    string input;
    char choice;

    cout << "Enter E for encryption or D for decryption: ";
    cin >> choice;
    cout << "Enter the number of rails: ";
    cin >> rails;

    if (choice == 'E' || choice == 'e') {
        cout << "Enter plaintext (no spaces allowed): ";
        cin >> input;
        string encryptedMessage = encryptMessage(input, rails);
        cout << "Encrypted Message: " << encryptedMessage << endl;
    } 
    else if (choice == 'D' || choice == 'd') {
        cout << "Enter ciphertext (no spaces allowed): ";
        cin >> input;
        string decryptedMessage = decryptMessage(input, rails);
        cout << "Decrypted Message: " << decryptedMessage << endl;
    } 
    else {
        cout << "Invalid choice. Please enter E for encryption or D for decryption." << endl;
    }

    return 0;
}