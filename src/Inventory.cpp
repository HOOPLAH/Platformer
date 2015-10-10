#include "Inventory.h"

Inventory::Inventory()
{
    //ctor
}

Inventory::~Inventory()
{
    //dtor
}

void Inventory::sq_push_back(Sqrat::Object& obj)
{
    Sqrat::SharedPtr<Item> item = obj.Cast<Sqrat::SharedPtr<Item>>();
    mItems.push_back(item);
}

void Inventory::push_back(Sqrat::SharedPtr<Item> item)
{
    mItems.push_back(item);
}

Sqrat::SharedPtr<Item> Inventory::createItemByName(std::string name)
{
    Item* item = new Item();
    item->setName(name);

    auto itemPtr = Sqrat::SharedPtr<Item>(item);
    //delete item;
    return itemPtr;
}

void Inventory::useItem(int index)
{
    getItem(index)->use();
    getSQObject(getItem(index)->getName()).call("use");
}

void Inventory::useItemByName(std::string name)
{
    getItemByName(name)->use();
    getSQObject(name).call("use");
}

Sqrat::SharedPtr<Item> Inventory::getItemByName(std::string name)
{
    for (auto& item : mItems)
    {
        if (item->getName()==name)
            return item;
    }
}

ScriptObject Inventory::getSQObject(std::string className)
{
    auto obj = ScriptObject(className, Sqrat::DefaultVM::Get());
    obj.bind("use");
    return obj;
}
