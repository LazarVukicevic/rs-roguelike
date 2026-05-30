#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "item.h"
#include <string>

class Inventory {
    std::vector<Item> inventory_;
    const size_t kMaxSlots = 28;
    public:
        bool AddItem(const Item& item);
        bool RemoveItem(const std::string& name, int quantity = 1);
        bool IsFull();
        auto begin()       { return inventory_.begin(); }
        auto end()         { return inventory_.end(); }
        auto begin() const { return inventory_.cbegin(); }
        auto end()   const { return inventory_.cend(); }
};

#endif