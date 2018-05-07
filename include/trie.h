#pragma once

#include <map>

template<typename T>
class TrieNode
{
    public:
        using node_t = TrieNode<T>;
        using children_t = std::map<T, node_t>;

        TrieNode() {}
        TrieNode(TrieNode&& rv) = default;
        TrieNode(const TrieNode& v) = default;

        TrieNode& operator=(TrieNode&& rv) = default;
        TrieNode& operator=(const TrieNode& v) = default;

    private:
        T value_;
        children_t children_;
};

template<typename T>
class Trie
{
    public:
        using node_t = TrieNode<T>;
        Trie() {}

        T find(std::string data)
        {
        }

    private:
        node_t root_;
};
