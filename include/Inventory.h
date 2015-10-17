#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <memory>

#include "Item.h"

class Inventory
{
    public:
        Inventory();
        ~Inventory();

        void push_back(std::unique_ptr<Item> item){mItems.push_back(std::move(item));}

        std::unique_ptr<Item>& getItem(int index){return mItems[index];}
        std::unique_ptr<Item>& getItem(std::string name);

    private:
        std::vector<std::unique_ptr<Item>> mItems;
};

#endif // INVENTORY_H
