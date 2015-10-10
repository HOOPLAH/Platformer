#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include "SpriteObject.h"

#include <squirrel.h>

class InventoryItem : public SpriteObject
{
    public:
        InventoryItem(SpriteInfo& info);
        virtual ~InventoryItem();

        static void bindSquirrel(HSQUIRRELVM vm);

    private:
};

#endif // INVENTORYITEM_H
