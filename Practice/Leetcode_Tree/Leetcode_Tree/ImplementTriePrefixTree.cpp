#include "Tree.h"

// MySolution
struct TrieNode {
    TrieNode() : _next(26, nullptr), _isEnd(false) {}
    vector<TrieNode*> _next;
    bool _isEnd = false;
};

class Trie {
public:
    Trie() {
        _root = new TrieNode;
    }

    void insert(string word) {
        TrieNode* cur = _root;
        for (auto c : word) {
            if (cur->_next[c - 'a'] == nullptr) {
                cur->_next[c - 'a'] = new TrieNode;
            }
            cur = cur->_next[c - 'a'];
        }
        cur->_isEnd = true;
    }

    bool search(string word) {
        TrieNode* cur = _root;
        for (auto c : word) {
            // wordû�������ߵ����˵��û�д���õ���
            if (cur->_next[c - 'a'] == nullptr) {
                return false;
            }
            cur = cur->_next[c - 'a'];
        }
        if (cur->_isEnd) {
            return true;
        }
        return false;
        // word�ߵ���󣬵��ǲ��Ǵ���ĵ������˵��ֻ��һ��ǰ׺

    }

    bool startsWith(string prefix) {
        TrieNode* cur = _root;
        for (auto c : prefix) {
            // prefixû�������ߵ����˵��û�и�ǰ׺
            if (cur->_next[c - 'a'] == nullptr) {
                return false;
            }
            cur = cur->_next[c - 'a'];
        }
        return true;
    }
    TrieNode* _root = nullptr;
};