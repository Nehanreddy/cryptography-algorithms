#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 26;

vector<vector<int>> multiplyMatrix(const vector<vector<int>>& key, const vector<int>& block) {
    int n = key.size();
    vector<vector<int>> result(n, vector<int>(1, 0));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            result[i][0] += key[i][k] * block[k];
        }
        result[i][0] %= MOD;
    }
    return result;
}

int determinant(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    if (n == 1) return matrix[0][0];

    int det = 0, sign = 1;
    for (int i = 0; i < n; i++) {
        vector<vector<int>> minor(n - 1, vector<int>(n - 1));
        for (int j = 1; j < n; j++) {
            for (int k = 0, col = 0; k < n; k++) {
                if (k == i) continue;
                minor[j - 1][col++] = matrix[j][k];
            }
        }
        det += sign * matrix[0][i] * determinant(minor);
        sign *= -1;
    }
    return (det % MOD + MOD) % MOD;
}

int modInverse(int a) {
    a = a % MOD;
    for (int x = 1; x < MOD; ++x)
        if ((a * x) % MOD == 1)
            return x;
    return -1;
}

vector<vector<int>> adjoint(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> adj(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vector<vector<int>> minor(n - 1, vector<int>(n - 1));
            for (int k = 0, row = 0; k < n; k++) {
                if (k == i) continue;
                for (int l = 0, col = 0; l < n; l++) {
                    if (l == j) continue;
                    minor[row][col++] = matrix[k][l];
                }
                row++;
            }
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign * determinant(minor)) % MOD;
            if (adj[j][i] < 0) adj[j][i] += MOD;
        }
    }
    return adj;
}


string encrypt(const string& plaintext, const vector<vector<int>>& key) {
    string modifiedText = plaintext;
    int n = key.size();
    int padding = n - (modifiedText.length() % n);
    if (padding != n) modifiedText += string(padding, 'X');

    string ciphertext = "";
    for (int i = 0; i < modifiedText.length(); i += n) {
        vector<int> block(n);
        for (int j = 0; j < n; j++)
            block[j] = modifiedText[i + j] - 'A';

        vector<vector<int>> result = multiplyMatrix(key, block);
        for (auto& row : result)
            ciphertext += (char)(row[0] + 'A');
    }
    return ciphertext;
}


string decrypt(const string& ciphertext, const vector<vector<int>>& key) {
    int det = determinant(key);
    int invDet = modInverse(det);
    if (invDet == -1) {
        return "Key matrix is not invertible. Decryption not possible.";
    }

    vector<vector<int>> adj = adjoint(key);
    int n = key.size();
    vector<vector<int>> inverseKey(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            inverseKey[i][j] = (adj[i][j] * invDet) % MOD;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (inverseKey[i][j] < 0) inverseKey[i][j] += MOD;

    return encrypt(ciphertext, inverseKey);
}

int main() {
    vector<vector<int>> key(3, vector<int>(3));
    string input;
    char choice;

    cout << "HILL CIPHER (3x3)\n";
    cout << "Enter E for encryption or D for decryption: ";
    cin >> choice;
    choice = toupper(choice);

    cout << "Enter the 3x3 key matrix (row-wise, integers mod 26):\n";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> key[i][j];

    if (choice == 'E') {
        cout << "Enter plaintext (UPPERCASE only): ";
        cin >> input;
        string cipher = encrypt(input, key);
        cout << "Encrypted Text: " << cipher << endl;
    } else if (choice == 'D') {
        cout << "Enter ciphertext (UPPERCASE only): ";
        cin >> input;
        string plain = decrypt(input, key);
        cout << "Decrypted Text: " << plain << endl;
    } else {
        cout << "Invalid choice. Use E or D." << endl;
    }

    return 0;
}
