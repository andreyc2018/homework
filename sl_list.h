#pragma once

#include <iterator>
#include <iostream>

/*! List node
 */
template <typename T>
struct Node
{
    T data_;
    struct Node<T>* next_;
};

/*! Single linked list
 */
template <typename T, class Allocator = std::allocator<T>>
class single_linked_list
{
        using node = Node<T>;
        using node_alloc_t = typename Allocator::template rebind<node>::other;

        /*! An iterator for the list
         */
        class sl_iterator : public std::iterator<std::forward_iterator_tag, T>
        {
            public:
                using base = std::iterator<std::forward_iterator_tag, T>;
                using iterator = sl_iterator;

                sl_iterator(node* ptr) : ptr_(ptr) {}

                typename base::reference operator*()
                {
                    return ptr_->data_;
                }

                //! pre-increment
                iterator& operator++()
                {
                    ptr_ = ptr_->next_; return *this;
                }

                //! post-increment
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
        using size_type = size_t;
        using iterator = sl_iterator;
        using allocator_type = Allocator;

        single_linked_list()
            : head_(nullptr)
            , node_alloc_(node_alloc_t()) {}

        explicit single_linked_list(const allocator_type& alloc)
            : head_(nullptr)
            , node_alloc_(alloc) {}

        explicit single_linked_list(size_type n,
                                    const allocator_type& alloc = allocator_type())
            : head_(nullptr), node_alloc_(alloc)
        {
            resize(n);
        }

        ~single_linked_list()
        {
            destroy_node(head_);
        }

        void resize(size_type n)
        {
            node* tmp_head = nullptr;
            node* tmp_next = nullptr;
            for (size_t i = 0; i < n; ++i) {
                tmp_next = tmp_head;
                tmp_head = make_node();
                tmp_head->next_ = tmp_next;
            }

            for (node *orig = head_, *tmp = tmp_head;
                 orig != nullptr && tmp != nullptr;
                 orig = orig->next_, tmp = tmp->next_)
            {
                tmp->data_ = orig->data_;
            }

            destroy_node(head_);
            head_ = tmp_head;
        }

        template<typename... Args>
        void emplace_front(Args&&... args)
        {
            node* tmp = make_node(std::forward<Args>(args)...);
            tmp->next_ = head_;
            head_ = tmp;
        }

        void push_front(const value_type& v)
        {
            node* tmp = make_node(v);
            tmp->next_ = head_;
            head_ = tmp;
        }

        reference front()
        {
            return head_->data_;
        }

        iterator begin() const { return sl_iterator(head_); };
        iterator end() const { return sl_iterator(nullptr); };

    private:
        node* head_;
        node_alloc_t node_alloc_;

        template<typename... Args>
        node* make_node(Args&&... args)
        {
            node* tmp = node_alloc_.allocate(1);
            tmp->next_ = nullptr;
            node_alloc_.construct(&(tmp->data_), std::forward<Args>(args)...);
            return tmp;
        }

        void destroy_node(Node<T>* ptr)
        {
            while(ptr) {
                Node<T>* next = ptr->next_;
                node_alloc_.destroy(&(ptr->data_));
                node_alloc_.deallocate(ptr, 1);
                ptr = next;
            }
        }
};
