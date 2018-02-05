#pragma once
/**
 * @file item.h
 *  @brief The base classes for the graphic primitives.
 */

#include <map>
#include <iostream>

namespace svge {

class Item;

using item_id_t = size_t;

enum class item_type_t : uint8_t
{
    Unknown, Document, Point, Line
};

/**
 * @brief Create new item of type T
 * @param args - list of arguments for a constructor, except item id
 *        item id will be generated and provided as a first argument of
 *        the constuctor
 * @return an item of type T*
 */
template<typename T, typename... Args>
inline T* new_item(item_id_t id, Args&&... args)
{
    return new T(id, std::forward<Args>(args)...);
}

class IItemCreator
{
    public:
        virtual ~IItemCreator() {}

        virtual Item* create(item_type_t type) = 0;
};

Item* create_item(item_type_t type)
{
    Item* item = nullptr;
    switch(type) {
        case item_type_t::Point:
            item = new_item<Point>(next_id());
            break;
        case item_type_t::Line:
            item = new_item<Line>(next_id());
            break;
        default:
            break;
    }
    return item;
}

/**
 * @brief The Item is a base class of a Composite pattern.
 *
 * All derived classes must have the constructors that accept
 * an item id of type item_id_t as a first parameter.
 */
class Item
{
    public:
        Item(item_id_t v, item_type_t t) : id_(v), type_(t) {}
        virtual ~Item() {}

        item_id_t id() const { return id_; }
        item_type_t type() const { return type_; }
        virtual std::ostream& write(std::ostream& out) = 0;
        virtual std::istream& read(std::istream& in) = 0;

    protected:
        item_id_t id_;
        item_type_t type_;
};

using items_t = std::map<item_id_t, Item*>;

/**
 * @brief The SimpleItem is a leaf class in the Composite pattern
 */
class SimpleItem : public Item
{
    public:
        SimpleItem(item_id_t v, item_type_t t) : Item (v, t) {}
        ~SimpleItem() {}
};

/**
 * @brief The ComplexItem is a container class for the other Items
 *        in the Composite pattern
 */
class ComplexItem : public Item
{
    public:
        ComplexItem(item_id_t v, item_type_t t) : Item(v, t) {}
        ~ComplexItem()
        {
            clear();
        }

        std::ostream& write(std::ostream& out) override
        {
            for (auto& v : items_) {
                out << static_cast<uint8_t>(v.second->type());
                v.second->write(out);
            }
            return out;
        }

        std::istream& read(std::istream& in) override
        {
            size_t items_size = 0;
            in >> items_size;
            for (size_t i = 0; i < items_size; ++i) {
                uint8_t type;
                in >> type;
                auto item = create_item(static_cast<item_type_t>(type));
                item->read(in);
                add_item(item);
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
