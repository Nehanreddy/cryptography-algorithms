#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to compute modular inverse of a under modulo m using Extended Euclidean Algorithm
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) return 0;

    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;

        // m is remainder now, process same as Euclid's algorithm
        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to check if a and m are coprime
bool isCoprime(int a, int m) {
    while (m != 0) {
        int temp = m;
        m = a % m;
        a = temp;
    }
    return a == 1;
}

int main() {
    string text;
    char choice;
    int a, b;

    cout << "Do you want to (E)ncrypt or (D)ecrypt using Affine Cipher? ";
    cin >> choice;
    choice = toupper(choice);

    if (choice != 'E' && choice != 'D') {
        cout << "Invalid choice. Please enter E for Encrypt or D for Decrypt." << endl;
        return 1;
    }

    cout << "Enter the message: ";
    cin >> text;

    cout << "Enter key 'a' (must be coprime with 26): ";
    cin >> a;
    cout << "Enter key 'b': ";
    cin >> b;

    if (!isCoprime(a, 26)) {
        cout << "Invalid key 'a'. It must be coprime with 26." << endl;
        return 1;
    }

    int a_inv = modInverse(a, 26); // Needed for decryption

    for (int i = 0; i < text.length(); ++i) {
        char ch = text[i];

        if (isalpha(ch)) {
            bool isLower = islower(ch);
            char base = isLower ? 'a' : 'A';
            int x = ch - base;

            if (choice == 'E') {
                // Encryption: E(x) = (a * x + b) mod 26
                x = (a * x + b) % 26;
            } else {
                // Decryption: D(x) = a_inv * (x - b) mod 26
                x = (a_inv * (x - b + 26)) % 26;
            }

            ch = base + x;
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
