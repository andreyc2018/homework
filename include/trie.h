#pragma once

#include "logger.h"
#include <map>
#include <iostream>

class TrieNode
{
    public:
        using container_t = std::string;
        using type_t = container_t::value_type;
        using node_t = TrieNode;
        using children_t = std::map<type_t, node_t>;
        using iterator = children_t::iterator;
        using const_iterator = children_t::const_iterator;

        TrieNode() {}
        TrieNode(TrieNode&& rv) = default;
        TrieNode(const TrieNode& v) = default;

        TrieNode& operator=(TrieNode&& rv) = default;
        TrieNode& operator=(const TrieNode& v) = default;

        iterator find(type_t v) { return children_.find(v); }
        const_iterator find(type_t v) const { return children_.find(v); }

        iterator end() { return children_.end(); }
        const_iterator end() const { return children_.end(); }

        bool operator==(const type_t& r) const { return value_ == r; }
        bool operator!=(const type_t& r) const { return !operator==(r); }
        bool operator==(const TrieNode& r) const { return operator==(r.value_); }
        bool operator!=(const TrieNode& r) const { return !operator==(r.value_); }

    private:
        type_t value_;
        children_t children_;
};

class Trie
{
    public:
        using node_t = TrieNode;
        using container_t = node_t::container_t;

        Trie() {}

//        T find(const std::string& /*data*/)
//        {
//        }

        void add(const container_t& data)
        {
            node_t& current = root_;
            for (size_t i = 0; i < data.size(); ++i) {
                auto& e = data[i];
                std::cout << e << " ";
                if (current != e) {
                    auto it = current.find(e);
                    if (it != current.end()) {
                    }
                }
            }
            std::cout << '\n';
        }

    private:
        node_t root_;
};
