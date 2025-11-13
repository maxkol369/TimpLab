#include <iostream>
#include <string>
#include "TableRouteCipher.h"

using namespace std;

int main() {
    string text;
    int key;
    int choice;
    
    cout << "===================================" << endl;
    cout << "       ШИФР ПЕРЕСТАНОВКИ" << endl;
    cout << "===================================" << endl;
    
    // Ввод текста
    cout << "Введите текст: ";
    cin >> text;
    
    // Ввод ключа
    cout << "Введите количество столбцов: ";
    cin >> key;
    
    // Проверка ключа
    if (key <= 0) {
        cout << "Ошибка: ключ должен быть больше 0" << endl;
        return 1;
    }
    
    // Создаем шифратор
    TableRouteCipher cipher(key);
    
    // Основной цикл
    while (true) {
        cout << endl;
        cout << "Текущий текст: " << text << endl;
        cout << "Ключ: " << key << " столбцов" << endl;
        cout << endl;
        cout << "1 - Зашифровать" << endl;
        cout << "2 - Расшифровать" << endl;
        cout << "0 - Выйти" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        
        if (choice == 1) {
            string result = cipher.encrypt(text);
            cout << "Результат шифрования: " << result << endl;
            text = result;
        }
        else if (choice == 2) {
            string result = cipher.decrypt(text);
            cout << "Результат расшифровки: " << result << endl;
            text = result;
        }
        else if (choice == 0) {
            cout << "Выход из программы" << endl;
            break;
        }
        else {
            cout << "Неверный выбор" << endl;
            // Очищаем буфер при неверном вводе
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    return 0;
}
