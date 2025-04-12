#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string sanitizeInput(string text) {
    string result;
    for (char c : text) {
        if (isalpha(c))
            result += toupper(c);
    }
    return result;
}

string encryptAutoclave(string plaintext, string key) {
    plaintext = sanitizeInput(plaintext);
    key = sanitizeInput(key);

    string extendedKey = key + plaintext;
    extendedKey = extendedKey.substr(0, plaintext.length());

    string ciphertext = "";
    for (size_t i = 0; i < plaintext.length(); i++) {
        char p = plaintext[i];
        char k = extendedKey[i];
        char c = ((p - 'A') + (k - 'A')) % 26 + 'A';
        ciphertext += c;
    }
    return ciphertext;
}

string decryptAutoclave(string ciphertext, string key) {
    ciphertext = sanitizeInput(ciphertext);
    key = sanitizeInput(key);

    string extendedKey = key;
    string plaintext = "";

    for (size_t i = 0; i < ciphertext.length(); i++) {
        char k;
        if (i < key.length()) {
            k = key[i];
        } else {
            k = plaintext[i - key.length()]; 
        }
        char c = ciphertext[i];
        char p = ((c - k + 26) % 26) + 'A';
        plaintext += p;
        extendedKey += p;
    }
    return plaintext;
}

int main() {
    string text, key;
    int choice;

    cout << "Autoclave Cipher\n";
    cout << "1. Encrypt\n2. Decrypt\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "Enter plaintext: ";
        getline(cin, text);
        cout << "Enter key: ";
        getline(cin, key);
        string encrypted = encryptAutoclave(text, key);
        cout << "Encrypted Text: " << encrypted << endl;
    } else if (choice == 2) {
        cout << "Enter ciphertext: ";
        getline(cin, text);
        cout << "Enter key: ";
        getline(cin, key);
        string decrypted = decryptAutoclave(text, key);
        cout << "Decrypted Text: " << decrypted << endl;
    } else {
        cout << "Invalid option!" << endl;
    }

    return 0;
}
