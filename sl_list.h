#pragma once

#include <iterator>
#include <iostream>

template <typename T>
struct Node
{
    Node() : data_(), next_(nullptr) {}
    ~Node() {}
    T data_;
    struct Node<T>* next_;
};

template <typename T, class Allocator = std::allocator<T>>
class sl_list
{
        using node = Node<T>;
        using node_alloc_t = typename Allocator::template rebind<node>::other;

        class sl_iterator : public std::iterator<std::forward_iterator_tag, T>
        {
            public:
                using base = std::iterator<std::forward_iterator_tag, T>;
                using iterator = sl_iterator;

                sl_iterator(node* ptr) : ptr_(ptr) {}

                typename base::reference operator*() { return ptr_->data_; }

                // pre-increment
                iterator& operator++()
                {
                    ptr_ = ptr_->next_;
                    return *this;
                }

                // post-increment
                iterator operator++(int)
                {
                    sl_iterator tmp(ptr_);
                    ptr_ = ptr_->next_;
                    return tmp;
                }

                bool operator==(const iterator& b) const
                {
                    return ptr_ == b.ptr_;
                }

                bool operator!=(const iterator& b) const
                {
                    return !(*this == b);
                }

            private:
                node* ptr_;
        };

    public:
        using value_type = T;
        using reference = T&;
//        using const_reference = const T&;
        using iterator = sl_iterator;
//        using const_iterator = const sl_iterator;
        using allocator_type = Allocator;

        sl_list(size_t size, const allocator_type& alloc = allocator_type())
            : root_(nullptr), tail_(nullptr), alloc_(alloc)
        {
            node_alloc_t node_alloc = alloc_;
            node* tmp = nullptr;
            for (size_t i = 0; i < size; ++i) {
                if (tmp != nullptr) {
                    tmp = tmp->next_ = node_alloc.allocate(1);
                }
                else {
                    tmp = root_ = node_alloc.allocate(1);
                }
                node_alloc.construct(tmp);
            }
        }
//        sl_list(const sl_list& b);
        ~sl_list()
        {
            node_alloc_t node_alloc = alloc_;
            Node<T>* tmp = root_;
            while(tmp) {
                Node<T>* next = tmp->next_;
                node_alloc.destroy(tmp);
                node_alloc.deallocate(tmp, 1);
                tmp = next;
            }
        }

//        sl_list& operator=(const sl_list& b);

        iterator begin() const { return sl_iterator(root_); };
        iterator end() const { return sl_iterator(tail_); };

//        void swap(sl_list& b);

    private:
        node* root_;
        node* tail_;
        allocator_type alloc_;
};

//template <typename T, class Allocator = std::allocator<T>>
//bool operator==(const sl_list<T, Allocator>& a, const sl_list<T, Allocator>& b)
//{
//    return std::equal(a.begin(), a.end(), b.begin(), b.end());
//}

//template <typename T, class Allocator = std::allocator<T>>
//bool operator!=(const sl_list<T, Allocator>& a, const sl_list<T, Allocator>& b)
//{
//    return !(a == b);
//}

//template <typename T, class Allocator = std::allocator<T>>
//void swap(sl_list<T, Allocator>& a, sl_list<T, Allocator>& b)
//{
//    a.swap(b);
//}
