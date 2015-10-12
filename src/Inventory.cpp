#include "Inventory.h"

#include "ScriptObject.h"

#include <iostream>

Inventory::Inventory()
{
    //ctor
}

Inventory::~Inventory()
{
    for(std::vector<ScriptObject*>::iterator it = mSQObjects.begin(); it != mSQObjects.end(); ++it)
    {
        //delete (*it);
    }
}

void Inventory::sq_push_back(Sqrat::Object obj)
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
    auto itemPtr = Sqrat::SharedPtr<Item>(new Item);
    itemPtr->setName(name);
    return itemPtr;
}

void Inventory::useItem(int index)
{
    //getItem(index)->use();
    getSQObject(getItem(index)->getName())->call("use");
}

void Inventory::useItemByName(std::string name)
{
    //getItemByName(name)->use();
    getSQObject(name)->call("use");
}

Sqrat::SharedPtr<Item> Inventory::getItemByName(std::string name)
{
    for (auto& item : mItems)
    {
        if (item->getName() == name)
            return item;
    }
}

ScriptObject* Inventory::getSQObject(std::string className)
{
    for (auto& obj : mSQObjects)
    {
        if (obj->getClassName() == className)
        {
            return obj;
        }
    }

    // no object exists, make new one
    ScriptObject* newObj = new ScriptObject(className);
    newObj->bind("use");
    newObj->bind("update");
    mSQObjects.push_back(newObj);
    return newObj;
}
