#include <iostream>
#include <string>

void encrypt(std::string &text, int shift) {
    for (char &ch : text) {
        ch = (ch + shift) % 128;
    }
}

void decrypt(std::string &text, int shift) {
    encrypt(text, 128 - (shift % 128));
}

int main() {
    std::string text;
    int shift;

    std::cout << "Enter text: ";
    std::getline(std::cin, text);

    std::cout << "Enter shift (1-127): ";
    std::cin >> shift;

    if (shift < 1 || shift > 127) {
        std::cout << "Shift must be between 1 and 127." << std::endl;
        return 1;
    }

    encrypt(text, shift);
    std::cout << "Encrypted text: " << text << std::endl;

    decrypt(text, shift);
    std::cout << "Decrypted text: " << text << std::endl;

    return 0;
}
