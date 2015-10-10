#include "InventoryItem.h"

#include <sqrat.h>

InventoryItem::InventoryItem(SpriteInfo& info) : SpriteObject(info, sf::Vector2f())
{
    //ctor
}

InventoryItem::~InventoryItem()
{
    //dtor
}

void InventoryItem::bindSquirrel(HSQUIRRELVM vm)
{
    Sqrat::Class<InventoryItem> item(vm, "InventoryItem");
    item.Ctor<SpriteInfo&>();
    //item.Func("initialize", &<class>::initialize);
    Sqrat::RootTable(vm).Bind("InventoryItem", item);
}
