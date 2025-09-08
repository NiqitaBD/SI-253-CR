#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int ALPHABET_SIZE = 26;

bool validateKey(int key) {
    return key >= 1 && key <= 25;
}

string preprocessText(const string& text) {
    string result;
    for (char c : text) {
        if (isalpha(c)) { // Verificăm dacă caracterul este alfabetic
            result += toupper(c);
        } else if (c != ' ') {
            cout << "Caractere permise: doar A-Z sau a-z si spatii.\n";
            return "";
        }
    }
    return result;
}

string encrypt(const string& message, int key) {
    string result;
    for (char c : message) {
        int pos = ALPHABET.find(c);
        int newPos = (pos + key) % ALPHABET_SIZE;
        result += ALPHABET[newPos];
    }
    return result;
}

string decrypt(const string& cipher, int key) {
    string result;
    for (char c : cipher) {
        int pos = ALPHABET.find(c);
        if (pos == string::npos) continue;
        int newPos = (pos - key + ALPHABET_SIZE) % ALPHABET_SIZE;
        result += ALPHABET[newPos];
    }
    return result;
}

int main() {
    int key;
    string choice, text;

    cout << "Alegeti operatia (criptare/decriptare): ";
    cin >> choice;

    cout << "Introduceti cheia (1 - 25): ";
    cin >> key;
    if (!validateKey(key)) {
        cout << "Cheia trebuie sa fie intre 1 si 25!\n";
        return 1;
    }

    cin.ignore(); // curăță newline-ul rămas după citirea lui key
    cout << "Introduceti textul: ";
    getline(cin, text); // citește linia întreagă, inclusiv spațiile

    string processed = preprocessText(text);
    cout << "Text procesat: " << processed << endl;
    if (processed.empty()) return 1;

    if (choice == "criptare") {
        cout << "Criptograma: " << encrypt(processed, key) << endl;
    } else if (choice == "decriptare") {
        cout << "Mesaj decriptat: " << decrypt(processed, key) << endl;
    } else {
        cout << "Optiune invalida! Folositi 'criptare' sau 'decriptare'.\n";
    }

    return 0;
}