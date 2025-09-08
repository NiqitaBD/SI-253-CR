#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int ALPHABET_SIZE = 26;

bool validateKey1(int key) {
    return key >= 1 && key <= 25;
}

bool validateKey2(const string& key2) {
    if (key2.size() < 7) return false;
    for (char c : key2) {
        if (!isalpha(c)) return false; // doar litere
    }
    return true;
}

string preprocessText(const string& text) {
    string result;
    for (char c : text) {
        if (isalpha(c)) {
            result += toupper(c);
        } else if (c == ' ') {
            result += ' '; // păstrăm spațiile
        } else {
            cout << "Caractere permise: doar A-Z, a-z si spatii.\n";
            return "";
        }
    }
    return result;
}

// criptare cu 2 chei
string encrypt(const string& message, int key1, const string& key2) {
    string result;
    int n = key2.size();
    for (int i = 0, j = 0; i < (int)message.size(); i++) {
        char c = message[i];
        if (c == ' ') { 
            result += ' ';
            continue;
        }
        int pos = ALPHABET.find(c);
        int k2 = toupper(key2[j % n]) - 'A'; // shift suplimentar
        int newPos = (pos + key1 + k2) % ALPHABET_SIZE;
        result += ALPHABET[newPos];
        j++;
    }
    return result;
}

// decriptare cu 2 chei
string decrypt(const string& cipher, int key1, const string& key2) {
    string result;
    int n = key2.size();
    for (int i = 0, j = 0; i < (int)cipher.size(); i++) {
        char c = cipher[i];
        if (c == ' ') {
            result += ' ';
            continue;
        }
        int pos = ALPHABET.find(c);
        int k2 = toupper(key2[j % n]) - 'A';
        int newPos = (pos - key1 - k2 + ALPHABET_SIZE * 10) % ALPHABET_SIZE;
        result += ALPHABET[newPos];
        j++;
    }
    return result;
}

int main() {
    int key1;
    string key2, choice, text;

    cout << "Alegeti operatia (criptare/decriptare): ";
    cin >> choice;

    cout << "Introduceti cheia 1 (1 - 25): ";
    cin >> key1;
    if (!validateKey1(key1)) {
        cout << "Cheia 1 trebuie sa fie intre 1 si 25!\n";
        return 1;
    }

    cout << "Introduceti cheia 2 (minim 7 litere): ";
    cin >> key2;
    if (!validateKey2(key2)) {
        cout << "Cheia 2 invalida! Trebuie doar litere si lungime >= 7.\n";
        return 1;
    }

    cin.ignore();
    cout << "Introduceti textul: ";
    getline(cin, text);

    string processed = preprocessText(text);
    if (processed.empty()) return 1;

    if (choice == "criptare") {
        cout << "Criptograma: " << encrypt(processed, key1, key2) << endl;
    } else if (choice == "decriptare") {
        cout << "Mesaj decriptat: " << decrypt(processed, key1, key2) << endl;
    } else {
        cout << "Optiune invalida! Folositi 'criptare' sau 'decriptare'.\n";
    }

    return 0;
}
