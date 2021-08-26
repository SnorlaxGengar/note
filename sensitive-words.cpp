#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>

using namespace std;

struct TreeNode {
    // fast to index
    unordered_map<char, TreeNode *> children;
    // some words have common prefix, so need a tag to indict word end
    bool isLeaf {false};
};

void print(TreeNode *root) {
    if (!root || root->children.empty()) {
        return;
    }

    for (const auto &child : root->children) {
        if (child.second->isLeaf) {
            cout << '[' << child.first << ']';

        } else {
            cout << child.first;
        }

        print(child.second);
    }
}

void filter(string &sentence, const vector<string> words) {
    // build sensitive words into trie tree
    TreeNode *root = new TreeNode();

    for (const string &word : words) {
        TreeNode *cur = root;

        for (char ch : word) {
            auto it = cur->children.find(ch);

            if (it == cur->children.end()) {
                TreeNode *newNode = new TreeNode();
                cur->children.insert(make_pair(ch, newNode));
                cur = newNode;

            } else {
                cur = it->second;
            }
        }

        cur->isLeaf = true;
    }

    print(root);
    cout << endl;
    // mark sensitive word begin
    auto begin = sentence.end();
    // sensitive words root node
    auto cur = root;

    for (auto it = sentence.begin(); it != sentence.end(); ++it) {
        char ch = *it;
        auto child = cur->children.find(ch);

        if (child == cur->children.end()) {
            if (cur->isLeaf) {
                std::fill(begin, it, '*');
            }

            begin = sentence.end();
            cur = root;
            continue;
        }

        if (begin == sentence.end()) {
            begin = it;
        }

        cur = child->second;
    }

    // the last word
    if (cur->isLeaf) {
        std::fill(begin, sentence.end(), '*');
    }

    // FIXME:release the sensitive words tree
}

void filter_sensitive(string &sentence, const vector<string> &words) {
    TreeNode *root = new TreeNode;

    for (const string &word : words) {
        TreeNode *last = root;

        for (char ch : word) {
            auto it = last->children.find(ch);

            if (it == last->children.end()) {
                auto node = new TreeNode;
                last->children.insert(make_pair(ch, node));
                last = node;

            } else {
                last = it->second;
            }
        }

        last->isLeaf = true;
    }

    // printTrieTree(root);
    // cout << endl;

    if (root->children.empty()) {
        return;
    }

    TreeNode *cur = root;
    auto begin = sentence.end();

    for (auto it = sentence.begin(); it != sentence.end(); ++it) {
        char ch = *it;

        if (cur->children.find(ch) == cur->children.end()) {
            if (cur->isLeaf) {
                fill(begin, it, '*');
                --it;
                begin = sentence.end();
                cur = root;

            } else {
                // 部分匹配到words需要重头开始
                begin = sentence.end();
                cur = root;
            }

            continue;
        }

        if (begin == sentence.end()) {
            begin = it;
        }

        cur = cur->children[ch];
    }

    if (cur->isLeaf) {
        fill(begin, sentence.end(), '*');
        begin = sentence.end();
        cur = root;
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cerr << "usage: " << argv[0] << " sentence" << endl;
        exit(1);
    }

    string sentence(argv[1]);
    cout << sentence << endl;
    vector<string> words{"app", "apple", "fuck", "god"};
    filter_sensitive(sentence, words);
    cout << sentence << endl;
    return 0;
}
