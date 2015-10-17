#include "Inventory.h"

Inventory::Inventory()
{
    //ctor
}

Inventory::~Inventory()
{
    //dtor
}

std::unique_ptr<Item>& Inventory::getItem(std::string name)
{
    for (auto& item : mItems)
    {
        if (item->getName() == name)
            return item;
    }
}
