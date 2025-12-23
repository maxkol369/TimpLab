#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("ПАРПА",modAlphaCipher("ПАР").encrypt("ААААА"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("ПАРУ",modAlphaCipher("ПАРУС").encrypt("ААААА"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("ПАРПА",modAlphaCipher("пар").encrypt("ААААА"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("П1"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("П,А"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("П А Р"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"),cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("Г");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("СДЗЖШСУ", p->encrypt("ОБЕДХОР"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("СДЗЖШСУ", p->encrypt("обедхор"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("СДЗЖШСУ", p->encrypt("ОБЕД ХОР!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("СДЗЖШСУ", p->encrypt("55ОБЕДХОР"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("3*3=9?"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("НАДГФНП", modAlphaCipher("Я").encrypt("ОБЕДХОР"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ПОСТАВТЕМНОГОБАЛЛОВ", p->decrypt("ТСФХГЕХИПРСЖСДГООСЕ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("тсфХГЕХИПРСЖСДГООСЕ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("ТСФХГЕХИ ПРСЖСДГООСЕ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("55ФХГЕХИПРСЖСДГООСЕ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("ТСФХГЕХИПРСЖСДГООСЕ!"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ПОСТАВТЕМНОГОБАЛЛОВ", modAlphaCipher("Я").decrypt("ОНРСЯБСДЛМНВНАЯККНБ"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
