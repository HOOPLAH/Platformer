#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>

#include <sqrat.h>

#include "ScriptObject.h"
#include "Item.h"

class Inventory
{
    public:
        Inventory();
        ~Inventory();

        void sq_push_back(Sqrat::Object obj);
        void push_back(Sqrat::SharedPtr<Item> item);

        Sqrat::SharedPtr<Item> createItemByName(std::string name);
        void useItem(int index);
        void useItemByName(std::string name);

        Sqrat::SharedPtr<Item> getItem(int index){return mItems[index];}
        Sqrat::SharedPtr<Item> getItemByName(std::string name);
        std::vector<Sqrat::SharedPtr<Item>>& getItemList(){return mItems;}

        ScriptObject* getSQObject(std::string className);
        std::vector<ScriptObject*> getSQObjectList(){return mSQObjects;}

    private:
        std::vector<Sqrat::SharedPtr<Item>> mItems;
        std::vector<ScriptObject*> mSQObjects;
};

#endif // INVENTORY_H
