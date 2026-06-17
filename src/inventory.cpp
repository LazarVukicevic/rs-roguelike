#include "inventory.h"

bool Inventory::IsFull() {
    return inventory_.size() >= kMaxSlots;
}

bool Inventory::AddItem(const ItemDef& def, int amount) {
    if (def.stackable) {
        for (auto& stack : inventory_) {
            if (stack.def->name == def.name) {
                stack.quantity += amount;
                return true;
            }
        }
    }
    if (IsFull()) {
        return false;
    }
    inventory_.push_back({&def, amount});
    return true;
}

bool Inventory::RemoveItem(const std::string& name, int quantity) {
    for (auto it = inventory_.begin(); it != inventory_.end(); ++it) {
        if (it->def->name == name) {
            if (it->quantity > quantity) {
                it->quantity -= quantity;
            } else {
                inventory_.erase(it);
            }
            return true;
        }
    }
    return false;
}
