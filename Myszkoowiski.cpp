#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

vector<int> getKeyOrder(const string& key) {
    vector<pair<char, int>> keyChars;
    for (int i = 0; i < key.length(); i++) {
        keyChars.push_back(make_pair(toupper(key[i]), i));
    }

    sort(keyChars.begin(), keyChars.end());

    vector<int> keyOrder(key.length());
    int order = 1;
    map<char, int> seen;
    for (size_t i = 0; i < keyChars.size(); i++) {
        char ch = keyChars[i].first;
        int idx = keyChars[i].second;
        if (seen.count(ch) == 0)
            seen[ch] = order++;
        keyOrder[idx] = seen[ch];
    }

    return keyOrder;
}

string encryptMyszkowski(const string& plaintext, const string& key) {
    string text = plaintext;
    text.erase(remove(text.begin(), text.end(), ' '), text.end());

    int cols = key.length();
    vector<int> keyOrder = getKeyOrder(key);
    int rows = (text.length() + cols - 1) / cols;

    vector<vector<char>> grid(rows, vector<char>(cols, ' '));
    int idx = 0;

    for (int i = 0; i < rows && idx < text.length(); i++) {
        for (int j = 0; j < cols && idx < text.length(); j++) {
            grid[i][j] = text[idx++];
        }
    }

    cout << "\nEncryption Grid:\n";
    for (size_t i = 0; i < key.length(); i++) cout << key[i] << " ";
    cout << "\n";
    for (size_t i = 0; i < keyOrder.size(); i++) cout << keyOrder[i] << " ";
    cout << "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }

    string cipher;
    for (int order = 1; order <= *max_element(keyOrder.begin(), keyOrder.end()); order++) {
        vector<int> columns;
        for (int j = 0; j < cols; j++) {
            if (keyOrder[j] == order)
                columns.push_back(j);
        }
        for (int i = 0; i < rows; i++) {
            for (int col : columns) {
                if (grid[i][col] != ' ')
                    cipher += grid[i][col];
            }
        }
    }

    return cipher;
}

string decryptMyszkowski(const string& cipher, const string& key) {
    int cols = key.length();
    vector<int> keyOrder = getKeyOrder(key);
    int rows = (cipher.length() + cols - 1) / cols;

    vector<vector<char>> grid(rows, vector<char>(cols, ' '));
    int idx = 0;

    for (int order = 1; order <= *max_element(keyOrder.begin(), keyOrder.end()); order++) {
        vector<int> columns;
        for (int j = 0; j < cols; j++) {
            if (keyOrder[j] == order)
                columns.push_back(j);
        }
        for (int i = 0; i < rows && idx < cipher.length(); i++) {
            for (int col : columns) {
                if (idx < cipher.length())
                    grid[i][col] = cipher[idx++];
            }
        }
    }

    cout << "\nDecryption Grid:\n";
    for (size_t i = 0; i < key.length(); i++) cout << key[i] << " ";
    cout << "\n";
    for (size_t i = 0; i < keyOrder.size(); i++) cout << keyOrder[i] << " ";
    cout << "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }

    string plain;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] != ' ')
                plain += grid[i][j];
        }
    }

    return plain;
}

int main() {
    string text, key;
    int choice;

    cout << "Myszkowski Transposition Cipher\n";
    cout << "1. Encrypt\n2. Decrypt\nChoose (1/2): ";
    cin >> choice;
    cin.ignore();

    cout << "Enter the key: ";
    getline(cin, key);

    cout << (choice == 1 ? "Enter plaintext: " : "Enter ciphertext: ");
    getline(cin, text);

    if (choice == 1) {
        string encrypted = encryptMyszkowski(text, key);
        cout << "\nEncrypted Text: " << encrypted << endl;
    } else {
        string decrypted = decryptMyszkowski(text, key);
        cout << "\nDecrypted Text: " << decrypted << endl;
    }

    return 0;
}
