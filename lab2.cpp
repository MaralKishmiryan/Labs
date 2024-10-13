#include <iostream>
#include <cstring>

void encrypt(std::string &text, int shift) {
    for (char &ch : text) {
        if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' + shift) % 26 + 'a'; 
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' + shift) % 26 + 'A'; 
        }
    }
}

void decrypt(std::string &text, int shift) {
    encrypt(text, 26 - (shift % 26)); 
}

int main() {
    std::string text;
    int shift;

    std::cout << "Enter text: ";
    std::getline(std::cin, text); // Read the entire line

    std::cout << "Enter key (1-25): ";
    std::cin >> shift;

    // Ensure shift is in the valid range
    if (shift < 1 || shift > 25) {
        std::cerr << "Shift must be between 1 and 25." << std::endl;
        return 1;
    }

    encrypt(text, shift);
    std::cout << "Encrypted text: " << text << std::endl;

    decrypt(text, shift);
    std::cout << "Decrypted text: " << text << std::endl;

    return 0;
}
