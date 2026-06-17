#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "item.h"

class Inventory {
    std::vector<ItemStack> inventory_;
    public:
        const size_t kMaxSlots = 28;
        bool AddItem(const ItemDef& def, int amount = 1);
        bool RemoveItem(const ItemDef& def, int quantity = 1);
        bool IsFull();
        auto begin()       { return inventory_.begin(); }
        auto end()         { return inventory_.end(); }
        auto begin() const { return inventory_.cbegin(); }
        auto end()   const { return inventory_.cend(); }
        ItemStack atIndex(int index) { return inventory_[index]; }
        size_t Size()      { return inventory_.size(); }
};

#endif