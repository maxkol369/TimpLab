#include "TableRouteCipher.h"
#include <algorithm>
#include <iostream>

Cipher::Cipher(int skey, string text) {
    key = getValidKey(skey, text);
}

string Cipher::encryption(string& text) {
    string t = getValidOpenText(text);
    int k = 0;
    int simvoli = t.size();
    int stroki = ((simvoli) / key);
    
    char** tabl = new char*[stroki];
    for (int i = 0; i < stroki; i++)
        tabl[i] = new char[key];

    for (int i = 0; i < stroki; i++)
        for (int j = 0; j < key; j++) {
            if (k < simvoli) {
                tabl[i][j] = t[k];
                k++;
            } else {
                tabl[i][j] = '0';
            }
        }

    k = 0;
    for (int j = key - 1; j >= 0; j--)
        for (int i = 0; i < stroki; i++) {
            if (tabl[i][j] != '0') {
                t[k] = tabl[i][j];
                k++;
            }
        }

    for (int i = 0; i < stroki; i++)
        delete[] tabl[i];
    delete[] tabl;

    return t;
}

inline string Cipher::getValidCipherText(string& s, string& open_text) {
    if (s.size() != open_text.size())
        throw cipher_error("Неправильно зашифрованный текст: " + s);
    return s;
}

string Cipher::transcript(string& text, string& open_text) {
    string t = getValidCipherText(text, open_text);
    int k = 0;
    int simvoli = t.size();
    int stroki = ((simvoli - 1) / key) + 1;

    char** tabl = new char*[stroki];
    for (int i = 0; i < stroki; i++)
        tabl[i] = new char[key];

    for (int j = key - 1; j >= 0; j--)
        for (int i = 0; i < stroki; i++) {
            if (k < simvoli) {
                tabl[i][j] = t[k];
                k++;
            } else {
                tabl[i][j] = '0';
            }
        }

    k = 0;
    for (int i = 0; i < stroki; i++)
        for (int j = 0; j < key; j++) {
            if (tabl[i][j] != '0') {
                t[k] = tabl[i][j];
                k++;
            }
        }

    for (int i = 0; i < stroki; i++)
        delete[] tabl[i];
    delete[] tabl;

    return t;
}

inline string Cipher::getValidOpenText(string& s) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());

    if (s.empty())
        throw cipher_error("Отсутствует открытый текст");

    for (char c : s)
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
            throw cipher_error("Некорректные символы в строке");

    return s;
}

inline int Cipher::getValidKey(int key, const string& Text) {
    if (key < 2 || key > Text.size())
        throw cipher_error("Некорректный размер ключа");
    
    return key;
}
