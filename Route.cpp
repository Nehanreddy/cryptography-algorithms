#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>  

using namespace std;

string encryptRouteCipher(string plaintext, int rows, int cols) {
   
    plaintext.erase(remove(plaintext.begin(), plaintext.end(), ' '), plaintext.end());

    // Padding with 'X' if needed
    while (plaintext.length() < rows * cols) {
        plaintext += 'X';
    }

    vector<vector<char>> matrix(rows, vector<char>(cols));
    int index = 0;
    for (int i = 0; i < rows && index < plaintext.size(); ++i) {
        for (int j = 0; j < cols && index < plaintext.size(); ++j) {
            matrix[i][j] = plaintext[index++];
        }
    }

    string cipher;
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            cipher += matrix[i][j];
        }
    }

    return cipher;
}


string decryptRouteCipher(string ciphertext, int rows, int cols) {
    vector<vector<char>> matrix(rows, vector<char>(cols));
    int index = 0;
    for (int j = 0; j < cols && index < ciphertext.size(); ++j) {
        for (int i = 0; i < rows && index < ciphertext.size(); ++i) {
            matrix[i][j] = ciphertext[index++];
        }
    }

    string plaintext;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            plaintext += matrix[i][j];
        }
    }

    return plaintext;
}

int main() {
    string choice, text;
    int rows, cols;

    cout << "Enter E for encryption or D for decryption: ";
    cin >> choice;
    cin.ignore();

    cout << "Enter the number of rows and columns (e.g., 4 5): ";
    cin >> rows >> cols;
    cin.ignore();

    if (choice == "E" || choice == "e") {
        cout << "Enter plaintext: ";
        getline(cin, text);

        string encrypted = encryptRouteCipher(text, rows, cols);
        cout << "Encrypted message: " << encrypted << endl;
    } else if (choice == "D" || choice == "d") {
        cout << "Enter ciphertext: ";
        getline(cin, text);

        string decrypted = decryptRouteCipher(text, rows, cols);
        cout << "Decrypted message: " << decrypted << endl;
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
