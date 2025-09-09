#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int ALPHABET_SIZE = 26;

bool validateKey(int key) {
    return key >= 1 && key <= 25;
}

bool validateKey_2(const string& key2) {
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
            continue;
        } else {
            cout << "Caractere permise: doar A-Z, a-z si spatii.\n";
            return "";
        }
    }
    return result;
}

string encrypt(const string& message, int key) {
    string result;
    for (char c : message) {
        if (c == ' ') { 
            result += ' ';
            continue;
        }
        int pos = ALPHABET.find(c);
        int newPos = (pos + key) % ALPHABET_SIZE;
        result += ALPHABET[newPos];
    }
    return result;
}

string encrypt_2(const string& message, int key1, const string& key2) {
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

string decrypt(const string& cipher, int key) {
    string result;
    for (char c : cipher) {
        if (c == ' ') {
            result += " ";
            continue;
        }
        int pos = ALPHABET.find(c);
        if (pos == string::npos) continue;
        int newPos = (pos - key + ALPHABET_SIZE) % ALPHABET_SIZE;
        result += ALPHABET[newPos];
    }
    return result;
}

string decrypt_2(const string& cipher, int key1, const string& key2) {
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
    while (true) {
        int action;
        string text;
        cout << "[1] O cheie \n[2] 2 chei \n[3] Iesire\n";
        cin >> action;

        if (action == 1 || action == 2) {
            string choice;
            cout << "Alegeti operatia (criptare/decriptare): ";
            cin >> choice;
            
            cin.ignore();
            cout << "Introduceti textul: ";
            getline(cin, text); // citește linia întreagă, inclusiv spațiile

            string processed = preprocessText(text);
            cout << "Text procesat: " << processed << endl;
            if (processed.empty()) continue;


            int key;
            cout << "Introduceti cheia (1 - 25): ";
            cin >> key;
            if (!validateKey(key)) {
                cout << "Cheia trebuie sa fie intre 1 si 25!\n";
                continue;
            }

            string key_2;
            if (action == 2) {
                cout << "Introduceti cheia 2 (minim 7 litere): ";
                cin >> key_2;
                if (!validateKey_2(key_2)) {
                    cout << "Cheia 2 invalida! Trebuie doar litere si lungime >= 7.\n";
                    continue;
                }
            }

            string final;
            if (choice == "criptare") {
                if (action == 1) {
                    final = encrypt(processed, key);
                } else if (action == 2) {
                    final = encrypt_2(processed, key, key_2);
                }
                cout << "Criptograma: " << final << endl;
            } else if (choice == "decriptare") {
                if (action == 1) {
                    final = decrypt(processed, key);
                } else if (action == 2) {
                    final = decrypt_2(processed, key, key_2);
                }
                cout << "Mesaj decriptat: " << final << endl;
            } else {
                cout << "Optiune invalida! Folositi 'criptare' sau 'decriptare'.\n";
            }
        } else if (action == 3) {
            cout << "Exit";
            return 0;
        } else { 
            cout << "Valoare invalida";
            return 0;
        }
    }
    
    return 0;
}
