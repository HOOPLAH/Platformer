#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include "SpriteObject.h"

class InventoryItem : public SpriteObject
{
    public:
        InventoryItem(SpriteInfo& info);
        virtual ~InventoryItem();

    private:
};

#endif // INVENTORYITEM_H
