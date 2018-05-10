#pragma once

#include "logger.h"
#include <map>
#include <iostream>

class TrieNode
{
    public:
        using type_t = char;
        using node_t = TrieNode;
        using children_t = std::map<type_t, node_t>;
        using iterator = children_t::iterator;

        TrieNode() {}
        TrieNode(TrieNode&& rv) = default;
        TrieNode(const TrieNode& v) = default;

        TrieNode& operator=(TrieNode&& rv) = default;
        TrieNode& operator=(const TrieNode& v) = default;

        iterator find(type_t v)
        {
        }

        bool operator==(const type_t& other) const { return value_ == other; }
        bool operator!=(const type_t& other) const { return !operator==(other); }
        bool operator==(const TrieNode& other) const { return operator==(other.value_); }
        bool operator!=(const TrieNode& other) const { return !operator==(other.value_); }

    private:
        type_t value_;
        children_t children_;
};

class Trie
{
    public:
        using node_t = TrieNode;
        Trie() {}

        T find(const std::string& /*data*/)
        {
        }

        void add(const std::string& data)
        {
            node_t& current = root_;
            for (const auto& e : data) {
                std::cout << e << " ";
                auto it = root_.find(e);
                if (root_.contains(e)) {
                }
            }
            std::cout << '\n';
        }

    private:
        node_t root_;
};
