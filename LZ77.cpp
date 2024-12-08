#include <iostream>
#include <string>
#include <sstream>

constexpr int WINDOW_SIZE = 4096;
constexpr int MAX_ENCODED_LENGTH = 1024;

struct Match {
    int offset = 0;
    int length = 0;
    char next_char = '\0';
};

Match findLongestMatch(const std::string& data, int pos, int window_size) {
    Match best_match = {0, 0, data[pos]};
    int end = std::min(pos + window_size, static_cast<int>(data.length()));

    for (int i = std::max(0, pos - window_size); i < pos; i++) {
        int length = 0;
        while (pos + length < end && data[i + length] == data[pos + length]) {
            length++;
        }
        if (length > best_match.length) {
            best_match.offset = pos - i;
            best_match.length = length;
            best_match.next_char = data[pos + length];
        }
    }
    return best_match;
}

std::string encode(const std::string& input) {
    std::ostringstream encoded;
    int pos = 0;
    int input_length = input.length();

    while (pos < input_length) {
        Match match = findLongestMatch(input, pos, WINDOW_SIZE);
        encoded << "(" << match.offset << ", " << match.length << ", '" << match.next_char << "') ";
        pos += match.length + 1;
    }

    return encoded.str();
}

std::string decode(const std::string& encoded) {
    std::ostringstream decoded;
    int decoded_index = 0;
    size_t cursor = 0;

    while (cursor < encoded.length()) {
        int offset, length;
        char next_char;

        if (sscanf(encoded.c_str() + cursor, "(%d, %d, '%c')", &offset, &length, &next_char) == 3) {
            std::string decoded_str = decoded.str();
            if (offset > 0) {
                int start = decoded_index - offset;
                for (int i = 0; i < length; i++) {
                    decoded << decoded_str[start + i];
                    decoded_index++;
                }
            }
            decoded << next_char;
            decoded_index++;
        }
        while (cursor < encoded.length() && encoded[cursor] != ' ') cursor++;
        if (cursor < encoded.length() && encoded[cursor] == ' ') cursor++;
    }

    return decoded.str();
}

int main() {
    std::string input = "ABABABABA";
    std::cout << "Input: " << input << std::endl;

    std::string encoded = encode(input);
    std::cout << "Encoded: " << encoded << std::endl;

    std::string decoded = decode(encoded);
    std::cout << "Decoded: " << decoded << std::endl;

    return 0;
}S
