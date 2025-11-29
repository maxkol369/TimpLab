#include "TableRouteCipher.h"
#include <locale>
#include <codecvt>
#include <iostream>

TableRouteCipher::TableRouteCipher(int skey) { 
    key = skey; 
}
string TableRouteCipher::encrypt(string& text)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wtext = converter.from_bytes(text);
    
    int k = 0;
    int simvoli = wtext.size();
    
    if (simvoli % key != 0) {
        throw cipher_error("Длина текста должна быть кратна ключу");
    }  
    int stroki = simvoli / key;
    
    wchar_t** tabl = new wchar_t*[stroki];
    for(int i = 0; i < stroki; i++)
        tabl[i] = new wchar_t[key];
    
    for(int i = 0; i < stroki; i++)
        for(int j = 0; j < key; j++) {
            if(k < simvoli) {
                tabl[i][j] = wtext[k];
                k++;
            }
        }
    
    k = 0;

    for(int j = key - 1; j >= 0; j--)
        for(int i = 0; i < stroki; i++) {
            wtext[k] = tabl[i][j];
            k++;
        }
    
    text = converter.to_bytes(wtext);
    
    for(int i = 0; i < stroki; i++)
        delete[] tabl[i];
    delete[] tabl;
    
    return text;
}

string TableRouteCipher::decrypt(string& text)
{
  
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wtext = converter.from_bytes(text);
    
    int k = 0;
    int simvoli = wtext.size();
    
    if (simvoli % key != 0) {
        throw cipher_error("Длина текста должна быть кратна ключу");
    }
    
    int stroki = simvoli / key;

    wchar_t** tabl = new wchar_t*[stroki];
    for(int i = 0; i < stroki; i++)
        tabl[i] = new wchar_t[key];

    for(int j = key - 1; j >= 0; j--)
        for(int i = 0; i < stroki; i++) {
            if (k < simvoli) {
                tabl[i][j] = wtext[k];
                k++;
            }
        }
    
    k = 0;

    for(int i = 0; i < stroki; i++)
        for(int j = 0; j < key; j++) {
            wtext[k] = tabl[i][j];
            k++;
        }
    text = converter.to_bytes(wtext);
    
    for(int i = 0; i < stroki; i++)
        delete[] tabl[i];
    delete[] tabl;
    
    return text;
}
