#pragma once
/** @file document.h
 *  @brief The document representation.
 *
 */

#include "item.h"
#include "point.h"
#include "line.h"
#include "logger.h"
#include <vector>

namespace svge {

/**
 * @brief Create new item of type T
 * @param args - list of arguments for a constructor, except item id
 *        item id will be generated and provided as a first argument of
 *        the constuctor
 * @return an item of type T*
 */
template<typename T, typename... Args>
inline T* create_item(item_id_t id, Args&&... args)
{
    return new T(id, std::forward<Args>(args)...);
}

class Document : public ComplexItem
{
    public:
        using base = ComplexItem;

        Document(const LoggerPtr& logger)
            : ComplexItem(0), logger_(logger), next_id_(1) {}
        ~Document() {}

        void reset()
        {
            clear();
            reset_id();
        }

        item_id_t create_item(item_type_t type)
        {
            Item* item = nullptr;
            switch(type) {
                case item_type_t::Point:
                    item = create_item<Point>(next_id());
                    break;
                case item_type_t::Line:
                    item = create_item<Line>(next_id());
                    break;
                default:
                    break;
            }
            return item->id();
        }

        void delete_item(item_id_t id)
        {

        }

        std::ostream& write(std::ostream& out) override
        {
            out << id_;
            return base::write(out);
        }

        std::istream& read(std::istream& in) override
        {
            in >> id_;
            return base::read(in);
        }

    private:
        LoggerPtr logger_;
        item_id_t next_id_;

        item_id_t next_id() { return next_id_++; }
        void reset_id() { next_id_ = 1; }
};

using DocumentUPtr = std::unique_ptr<Document>;

}
