#ifndef ITEM_H
#define ITEM_H

#include <string>

struct ItemDef {
    std::string name;
    bool stackable = false;
    int value = 1; // alch value, store value
};

struct ItemStack {
    const ItemDef* def;
    int quantity;
};

#endif
