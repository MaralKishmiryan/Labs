#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>

struct HuffmanNode {
    char symbol;
    int frequency;
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;

    HuffmanNode(char sym, int freq) : symbol(sym), frequency(freq), left(nullptr), right(nullptr) {}
};

// Comparator for the priority queue
struct CompareNodes {
    bool operator()(std::shared_ptr<HuffmanNode> a, std::shared_ptr<HuffmanNode> b) {
        return a->frequency > b->frequency;
    }
};

std::shared_ptr<HuffmanNode> buildTree(const std::unordered_map<char, int>& frequencies) {
    std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, CompareNodes> pq;

    for (const auto& [symbol, freq] : frequencies) {
        pq.push(std::make_shared<HuffmanNode>(symbol, freq));
    }

    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();

        auto parent = std::make_shared<HuffmanNode>('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    return pq.top();
}

void generateCodes(std::shared_ptr<HuffmanNode> node, const std::string& code, std::unordered_map<char, std::string>& codes) {
    if (!node) return;

    if (!node->left && !node->right) {
        codes[node->symbol] = code;
        return;
    }

    generateCodes(node->left, code + "0", codes);
    generateCodes(node->right, code + "1", codes);
}

std::string encode(const std::string& input, const std::unordered_map<char, std::string>& codes) {
    std::string encoded;
    for (char ch : input) {
        encoded += codes.at(ch);
    }
    return encoded;
}

std::string decode(const std::string& encoded, std::shared_ptr<HuffmanNode> root) {
    std::string decoded;
    auto current = root;

    for (char bit : encoded) {
        current = (bit == '0') ? current->left : current->right;

        if (!current->left && !current->right) {
            decoded += current->symbol;
            current = root;
        }
    }

    return decoded;
}

int main() {
    std::string input = "this is an example for huffman encoding";

    std::unordered_map<char, int> frequencies;
    for (char ch : input) {
        frequencies[ch]++;
    }

    auto root = buildTree(frequencies);

    std::unordered_map<char, std::string> codes;
    generateCodes(root, "", codes);

    std::cout << "Huffman Codes:\n";
    for (const auto& [symbol, code] : codes) {
        std::cout << "'" << symbol << "': " << code << '\n';
    }

    std::string encoded = encode(input, codes);
    std::cout << "\nEncoded String: " << encoded << '\n';

    std::string decoded = decode(encoded, root);
    std::cout << "\nDecoded String: " << decoded << '\n';

    return 0;
}
