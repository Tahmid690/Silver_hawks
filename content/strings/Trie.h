/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Status: 
 */
struct TrieNode {
    TrieNode* child[26];
    int wordCount;     // Number of times this word was inserted
    int prefixCount;   // Number of words that share this prefix
    TrieNode() {
        wordCount = 0;
        prefixCount = 0;
        for (int i = 0; i < 26; ++i)
            child[i] = nullptr;
    }
};
struct Trie {
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    // Inserts a word into the trie
    void insert(const string &word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->child[idx])
                node->child[idx] = new TrieNode();
            node = node->child[idx];
            node->prefixCount++;
        }
        node->wordCount++;
    }
    // Returns true if the word exists in the trie
    bool search(const string &word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->child[idx])
                return false;
            node = node->child[idx];
        }
        return node->wordCount > 0;
    }
    // Returns true if there is any word in the trie that starts with the given prefix
    bool startsWith(const string &prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->child[idx])
                return false;
            node = node->child[idx];
        }
        return true;
    }
    // Returns how many times a word has been inserted
    int countWordsEqualTo(const string &word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->child[idx]) return 0;
            node = node->child[idx];
        }
        return node->wordCount;
    }
    // Returns how many words start with the given prefix
    int countWordsStartingWith(const string &prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->child[idx]) return 0;
            node = node->child[idx];
        }
        return node->prefixCount;
    }
    // Deletes one occurrence of the word from the trie
    void erase(const string &word) {
        if (!search(word)) return;
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            node = node->child[idx];
            node->prefixCount--;
        }
        node->wordCount--;
    }
    // Optional: free memory
    void clear(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < 26; ++i)
            clear(node->child[i]);
        delete node;
    }
    ~Trie() {
        clear(root);
    }
};
