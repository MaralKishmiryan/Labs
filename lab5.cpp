#include <iostream>
#include <cstring>

void runLengthEncode(const std::string &input, std::string &output) {
    int count;
    output.clear();
    int length = input.length();

    for (int i = 0; i < length; i++) {
        count = 1;
        while (i + 1 < length && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        output += input[i];
        output += std::to_string(count);
    }
}

int main() {
    std::string input = "aaabbbccdaa";
    std::string output;

    runLengthEncode(input, output);
    std::cout << "Input: " << input << std::endl;
    std::cout << "Encoded: " << output << std::endl;

    return 0;
}
