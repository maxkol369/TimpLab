#include <UnitTest++/UnitTest++.h>
#include "code.h"
#include <string>

std::string s = "FORTNITE";

SUITE(KeyTest) {
    TEST(ValidKey) {
        code cipher(4, "FORTNITE");
        CHECK_EQUAL("TERTOIFN", cipher.encryption(s));
    }
    TEST(LongKey) {
        CHECK_THROW(code(1, "FORTNITE"), cipher_error);
    }
}

struct KeyB_fixture {
    code * t;
    KeyB_fixture() {
        t = new code(4, "FORTNITE");
    }
    ~KeyB_fixture() {
        delete t;
    }
};

SUITE(EncryptTest) {
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        std::string input = "FORTNITE";
        CHECK_EQUAL("TERTOIFN", t->encryption(input));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        std::string input = "fortnite";
        CHECK_EQUAL("tertoifn", t->encryption(input));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        std::string input = "FORT NITE";
        CHECK_EQUAL("TERTOIFN", t->encryption(input));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        std::string input = "FORT4ITE";
        CHECK_THROW(t->encryption(input), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        std::string input = "";
        CHECK_THROW(t->encryption(input), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        std::string input = "2*2=5?";
        CHECK_THROW(t->encryption(input), cipher_error);
    }
    TEST(MaxShiftKey) {
        code cipher(8, "FORTNITE");
        std::string input1 = "ETINTROF";
        std::string input2 = "FORTNITE";
        CHECK_EQUAL("FORTNITE", cipher.transcript(input1, input2));
    }
}

SUITE(DecryptText) {
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        std::string input1 = "TERTOIFN";
        std::string input2 = "FORTNITE";
        CHECK_EQUAL("FORTNITE", t->transcript(input1, input2));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        std::string input1 = "tertoifn";
        std::string input2 = "fortnite";
        CHECK_EQUAL("fortnite", t->transcript(input1, input2));
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        std::string input1 = "FORTNITE";
        std::string input2 = "FORT NITE";
        CHECK_THROW(t->transcript(input1, input2), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        std::string input1 = "FORT4ITE";
        std::string input2 = "FORT4ITE";
        CHECK_THROW(t->transcript(input1, input2), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        std::string input1 = "FORTNITE!";
        std::string input2 = "FORTNITE!";
        CHECK_THROW(t->transcript(input1, input2), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        std::string input1 = "";
        std::string input2 = "";
        CHECK_THROW(t->transcript(input1, input2), cipher_error);
    }
    TEST(MaxShiftKey) {
        code cipher(8, "Serafime");
        std::string input1 = "ETINTROF";
        std::string input2 = "FORTNITE";
        CHECK_EQUAL("FORTNITE", cipher.transcript(input1, input2));
    }
}

int main(int argc, char **argv) {
    return UnitTest::RunAllTests();
}
