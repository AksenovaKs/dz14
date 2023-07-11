#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* curr = root;

        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = new TrieNode();
            }
            curr = curr->children[c];
        }

        curr->isEndOfWord = true;
    }

    bool search(string word) {
        TrieNode* curr = root;

        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                return false;
            }
            curr = curr->children[c];
        }

        return curr->isEndOfWord;
    }

    void autoComplete(string partialWord) {
        TrieNode* curr = root;

        for (char c : partialWord) {
            if (curr->children.find(c) == curr->children.end()) {
                return;
            }
            curr = curr->children[c];
        }

        autoCompleteHelper(curr, partialWord);
    }

    void autoCompleteHelper(TrieNode* node, string word) {
        if (node->isEndOfWord) {
            cout << word << endl;
        }

        if (node->children.empty()) {
            return;
        }

        for (auto& kv : node->children) {
            autoCompleteHelper(kv.second, word + kv.first);
        }
    }
};

int main() {
    Trie dictionary;

    // Здесь добавьте нужные слова в словарь
    dictionary.insert("apple");
    dictionary.insert("banana");
    dictionary.insert("cherry");
    dictionary.insert("grape");
    dictionary.insert("orange");
    dictionary.insert("oran");

    string input;

    while (true) {
        cout << "Введите часть слова: ";
        cin >> input;

        dictionary.autoComplete(input);
    }

    return 0;
}