#include <string>
#include <stdexcept>

using namespace std;

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error (const std::string& what_arg) :
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg) :
        std::invalid_argument(what_arg) {}
};

class TableRouteCipher {
    int key;
public:
    TableRouteCipher() = delete;
    TableRouteCipher(int skey);
    string encrypt(string& text);
    string decrypt(string& text);
};
