#include <string>
#include <unordered_map>
#include <memory>
#include <cassert>
#include <iostream>

#include "leetcode_000_common.h"

using namespace std;

class Solution {
    struct Node {
        explicit Node(bool is_word_):is_word(is_word_) {}
        std::unordered_map<char, std::unique_ptr<Node>> children;
        bool is_word = false;
    };
    using Trie = std::unordered_map<char, std::unique_ptr<Node>>;

    void insertWord(const std::string& word) {
        if (word.empty()){
            return;
        }
        if (trie_.count(word[0]) == 0) {
            trie_.insert(
                    make_pair(
                            word[0],
                            make_unique<Node>( word.size() == 1 )
                            ));
        }
        // not sure why reference would not work. Seems to try to destroy object...
        auto n = trie_[word[0]].get();

        for (auto ch_iter = cbegin(word)+1; ch_iter < cend(word); ++ch_iter) {
            // if character is not already in map, add it
            if (n->children.count(*ch_iter) == 0) {
                auto ins = n->children.insert(
                        std::make_pair(
                                *ch_iter,
                                make_unique<Node>(ch_iter+1 == cend(word))
                                ));
                n = ins.first->second.get();
            }
            else {
                if (ch_iter+1 == cend(word)) {
                    n->is_word = true;
                }
                n = n->children[*ch_iter].get();
            }
        }
    }

    static std::string trieLongestWord() {
        return "";
    }

    void printNode(char c, Node* n) {
        cout << c << " word: " << (n->is_word ? "true" : "false" ) << "\n";
        for (auto iter = cbegin(n->children); iter != cend(n->children); ++iter) {
            printNode(iter->first, iter->second.get());
        }
    }

    void printTrie() {
        for (auto iter = cbegin(trie_); iter != cend(trie_); ++iter) {
            printNode(iter->first, iter->second.get());
        }
    }

public:
    string longestWord(const vector<string>& words) {
        for (const auto& word: words) {
            cout << "Adding " << word << "\n";
            insertWord(word);
            cout << "Trie after addition " << "\n";
            printTrie();
        }
        return trieLongestWord();
    }

private:
    Trie trie_;
};
//using Solution = Solution3;

int main() {
    vector<string> in1 {"k","ki","kir","kira", "kiran"};
    Solution s;
    auto out1 = s.longestWord(in1);
    assert(out1 == "kiran");
    std::cout << "out 1: " << out1 << std::endl;
    return 0;
}