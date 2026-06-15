#include "inventory.h"

bool Inventory::IsFull() {
    return inventory_.size() >= kMaxSlots;
}

bool Inventory::AddItem(const Item& item) {
    for (auto it = inventory_.begin(); it != inventory_.end(); ++it) {
        if (it->name == item.name) {
            if (item.stackable) {
                it->quantity++;
                return true;
            }
            break;
        }
    }
    if (IsFull()) {
        return false;
    }
    inventory_.push_back(item);
    return true;
}

bool Inventory::RemoveItem(const std::string& name, int quantity) {
    for (auto it = inventory_.begin(); it != inventory_.end(); ++it) {
        if (it->name == name) {
            if (it ->quantity > quantity) {
                it->quantity -= quantity;
            } else {
                inventory_.erase(it);
            }
            return true;
        }
    }
    return false;
}
