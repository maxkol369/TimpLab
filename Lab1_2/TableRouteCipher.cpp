#include "TableRouteCipher.h"
#include <iostream>
#include <vector>

using namespace std;

TableRouteCipher::TableRouteCipher(int skey) { 
    key = skey; 
}

string TableRouteCipher::encrypt(string& text) {
    int text_length = text.size();
    int rows = (text_length + key - 1) / key;
    
    // Создаем таблицу
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    // Заполняем таблицу слева направо, сверху вниз
    int index = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < key; j++) {
            if(index < text_length) {
                table[i][j] = text[index];
                index++;
            }
        }
    }
    
    // Читаем таблицу сверху вниз, справа налево
    string result;
    for(int j = key - 1; j >= 0; j--) {
        for(int i = 0; i < rows; i++) {
            if(table[i][j] != ' ') {
                result += table[i][j];
            }
        }
    }
    
    return result;
}

string TableRouteCipher::decrypt(string& text) {
    int text_length = text.size();
    int rows = (text_length + key - 1) / key;
    
    // Создаем таблицу
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    // Заполняем таблицу сверху вниз, справа налево
    int index = 0;
    for(int j = key - 1; j >= 0; j--) {
        for(int i = 0; i < rows; i++) {
            if(index < text_length) {
                table[i][j] = text[index];
                index++;
            }
        }
    }
    
    // Читаем таблицу слева направо, сверху вниз
    string result;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < key; j++) {
            if(table[i][j] != ' ') {
                result += table[i][j];
            }
        }
    }
    
    return result;
}
