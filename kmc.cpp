#include<iostream>
#include<string>
#include<cctype>
#include<windows.h>

using namespace std;

void typeWrite(string s) {
    for (char c : s) {
        cout << c;
        Sleep(50);
    }
}

string keyExtender(string key, int length, bool showCycles) {
    string extended = "";
    string current = key;
    int pos = 0;
    int cycle = 1;
    if (showCycles) {
        cout << "Key Extension Cycles:" << endl;
        cout << "Cycle " << cycle << ": " << current << endl;
    }
    while (extended.length() < length) {
        for (char c : current) {
            if (extended.length() >= length) break;
            extended += c;
            pos++;
            if (pos >= key.length()) {
                // increment current
                for (size_t i = 0; i < current.length(); i++) {
                    if (isupper(current[i])) {
                        current[i] = (current[i] - 'A' + 1) % 26 + 'A';
                    } else if (islower(current[i])) {
                        current[i] = (current[i] - 'a' + 1) % 26 + 'a';
                    }
                }
                cycle++;
                if (showCycles) {
                    cout << "Cycle " << cycle << ": " << current << endl;
                }
                pos = 0;
            }
        }
    }
    if (showCycles) {
        cout << "Final Extended Key: " << extended.substr(0, length) << endl << endl;
    }
    return extended.substr(0, length);
}

string encrypt(string ptext, string ekey) {
    string ctext = "";
    for (size_t i = 0; i < ptext.length(); i++) {
        char p = ptext[i];
        char k = ekey[i];
        char encrypted_char;
        if (isupper(p)) {
            int shift = toupper(k) - 'A';
            encrypted_char = (p - 'A' + shift) % 26 + 'A';
        } else if (islower(p)) {
            int shift = tolower(k) - 'a';
            encrypted_char = (p - 'a' + shift) % 26 + 'a';
        } else {
            encrypted_char = p;
        }
        ctext += encrypted_char;
    }
    return ctext;
}

string decrypt(string ctext, string ekey) {
    string ptext = "";
    for (size_t i = 0; i < ctext.length(); i++) {
        char c = ctext[i];
        char k = ekey[i];
        if (isupper(c)) {
            int shift = toupper(k) - 'A';
            ptext += (c - 'A' - shift + 26) % 26 + 'A';
        } else if (islower(c)) {
            int shift = tolower(k) - 'a';
            ptext += (c - 'a' - shift + 26) % 26 + 'a';
        } else {
            ptext += c;
        }
    }
    // Replace %20 with spaces
    size_t pos = 0;
    while ((pos = ptext.find("%20", pos)) != string::npos) {
        ptext.replace(pos, 3, " ");
        pos += 1;
    }
    return ptext;
}

int main(){
    typeWrite("Welcome to Key Morph Vigenere Cipher.....\n"
        "It works by extending the key by incrementing each character after every full cycle through the key characters.\n\n"
        "It is a type of Symmetric Key Cryptography.\n\n");

    string ptext, key, extendedKey, ctext, dtext;
    int plen=0, klen=0;

    typeWrite("\nEnter Plain Text: ");
    getline(cin, ptext);
    // Replace spaces with %20
    for (size_t i = 0; i < ptext.length(); ++i) {
        if (ptext[i] == ' ') {
            ptext.replace(i, 1, "%20");
            i += 2;
        }
    }
    plen = ptext.length();
    typeWrite("\nEnter Key: ");
    getline(cin, key);
    // Replace spaces with %20
    for (size_t i = 0; i < key.length(); ++i) {
        if (key[i] == ' ') {
            key.replace(i, 1, "%20");
            i += 2;
        }
    }
    klen = key.length();

    typeWrite("\nDo you want to display all cycles of key extension? (y/n): ");
    char choice;
    cin >> choice;
    bool showCycles = (choice == 'y' || choice == 'Y');
    cin.ignore(); // Ignore the newline character left in the input buffer

    extendedKey = keyExtender(key, plen, showCycles);
    ctext = encrypt(ptext, extendedKey);
    dtext = decrypt(ctext, extendedKey);

    typeWrite("\nExtended Key: " + extendedKey + "\n\n");
    typeWrite("Cipher Text: " + ctext + "\n\n");
    typeWrite("Decrypted Text: " + dtext + "\n\n");

    return 0;
}
