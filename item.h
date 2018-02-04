#pragma once
/**
 * @file item.h
 *  @brief The base classes for the graphic primitives.
 */

#include <map>
//#include <iostream>

namespace svge {

using item_id_t = size_t;

enum class item_type_t
{
    Point, Line
};

/**
 * @brief The Item is a base class of a Composite pattern.
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
        virtual std::ostream& write(std::ostream& out) = 0;
        virtual std::istream& read(std::istream& in) = 0;

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
 * @brief The ComplexItem is a container class for the other Items
 *        in the Composite pattern
 */
class ComplexItem : public Item
{
    public:
        ComplexItem(const item_id_t& v) : Item(v) {}
        ~ComplexItem()
        {
            clear();
        }

        std::ostream& write(std::ostream& out) override
        {
            for (auto& v : items_) {
                v.second->write(out);
            }
            return out;
        }

        std::istream& read(std::istream& in) override
        {
            for (auto& v : items_) {
                v.second->read(in);
            }
            return in;
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

        void clear()
        {
            for (auto& v : items_) {
                delete v.second;
            }
            items_.clear();
        }

    protected:
        items_t items_;
};

}
