#pragma once

#include <map>
#include <memory>
#include <string>
#include <atomic>

namespace svge {

using item_id_t = size_t;

/**
 * @brief The Item is a base class a Composite pattern.
 * @link https://en.wikipedia.org/wiki/Composite_pattern
 *
 * All derived classes must have the constructors that accept
 * an item id of type item_id_t as a first parameter.
 */
class Item
{
    public:
        Item(const item_id_t& v) : id_(v) {}
        virtual ~Item() {}

        item_id_t id() const { return id_; }

    protected:
        const item_id_t id_;
};

using items_t = std::map<item_id_t, Item*>;

/**
 * @brief The SimpleItem is a leaf class in the Composite pattern
 */
class SimpleItem : public Item
{
    public:
        SimpleItem(const item_id_t& v) : Item (v) {}
        ~SimpleItem() {}
};

/**
 * @brief The ComplexItem is a container class in the Composite pattern
 */
class ComplexItem : public Item
{
    public:
        ComplexItem(const item_id_t& v) : Item(v) {}
        ~ComplexItem()
        {
            for (auto& v : items_) {
                delete v.second;
            }
            items_.clear();
        }

    protected:
        bool add_item(Item* v)
        {
            auto rc = items_.insert(std::make_pair(v->id(), v));
            return rc.second;
        }

        void remove_item(const item_id_t& v)
        {
            items_.erase(v);
        }

    protected:
        items_t items_;
};

/**
 * @brief generate an id for an item
 * @return generated id
 */
inline item_id_t generate_id()
{
    static std::atomic<item_id_t> next_id(1);
    item_id_t id = next_id;
    next_id.fetch_add(1, std::memory_order_relaxed);
    return id;
}

/**
 * @brief Create new item of type T
 * @param args - list of arguments for a constructor, except item id
 *        item id will be generated and provided as a first argument of
 *        the constuctor
 * @return an item of type T* via pointer to the base type Item
 */
template<typename T, typename... Args>
inline T* create_item(Args&&... args)
{
    return new T(generate_id(), std::forward<Args>(args)...);
}

}
