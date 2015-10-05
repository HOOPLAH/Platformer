#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <functional>

class InventoryItem
{
    public:
        InventoryItem();
        virtual ~InventoryItem();

        /*template <typename ...Args>
        void use(void f(Args...), Args... args)
        {
            std::function<void(Args...)>&& func = std::function<void(Args...)>(f);
            func(args...);
        }*/

        void use(){}

    protected:
};

#endif // INVENTORYITEM_H
