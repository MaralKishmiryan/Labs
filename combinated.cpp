#include <iostream>
#include <string>
#include <sstream>

void caesarEncrypt(std::string &text, int shift) {
    for (char &ch : text) {
        if (ch >= ' ' && ch <= '~') {
            ch = ((ch - ' ') + shift) % 95 + ' ';
        }
    }
}

void runLengthEncode(const std::string &input, std::string &output) {
    std::ostringstream oss;
    int count;
    int length = input.length();

    for (int i = 0; i < length; i++) {
        count = 1;
        while (i + 1 < length && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        oss << input[i] << count;
    }
    output = oss.str();
}

void encode(const std::string &input, std::string &output, int shift) {
    std::string encryptedText = input;
    caesarEncrypt(encryptedText, shift);
    runLengthEncode(encryptedText, output);
}

void runLengthDecode(const std::string &input, std::string &output) {
    std::ostringstream oss;
    int i = 0;

    while (i < input.length()) {
        char character = input[i++];
        int count = 0;

        while (i < input.length() && input[i] >= '0' && input[i] <= '9') {
            count = count * 10 + (input[i] - '0');
            i++;
        }

        for (int k = 0; k < count; k++) {
            oss << character;
        }
    }
    output = oss.str();
}

void caesarDecrypt(std::string &text, int shift) {
    for (char &ch : text) {
        if (ch >= ' ' && ch <= '~') {
            ch = ((ch - ' ') - shift + 95) % 95 + ' ';
        }
    }
}

void decode(const std::string &input, std::string &output, int shift) {
    std::string decodedText;
    runLengthDecode(input, decodedText);
    output = decodedText;
    caesarDecrypt(output, shift);
}

int main() {
    std::string text;
    std::string encodedText;
    std::string decodedText;
    int shift;

    std::cout << "Enter text: ";
    std::getline(std::cin, text);
    std::cout << "Enter shift (1-94): ";
    std::cin >> shift;

    if (shift < 1 || shift > 94) {
        std::cerr << "Shift must be between 1 and 94." << std::endl;
        return 1;
    }

    encode(text, encodedText, shift);
    std::cout << "Encoded text: " << encodedText << std::endl;
    decode(encodedText, decodedText, shift);
    std::cout << "Decoded text: " << decodedText << std::endl;

    return 0;
}
