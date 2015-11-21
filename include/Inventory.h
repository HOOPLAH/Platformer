#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <memory>

#include "Assets.h"
#include "Item.h"

class Inventory
{
    public:
        Inventory();
        ~Inventory();

        void push_back(std::unique_ptr<Item> item){mItems.push_back(std::move(item));}

        std::unique_ptr<Item>& getItem(int index){return mItems[index];}
        std::unique_ptr<Item>& getItem(std::string name);
        std::vector<std::unique_ptr<Item>>& getItemList(){mItems;}

    private:
        std::vector<std::unique_ptr<Item>> mItems;
};

class InventoryHUD
{
    public:
        InventoryHUD(sf::Vector2f pos) : mInventoryBar(Assets::sprites["inventorybar"], pos), mInventoryIndex(0),
                                         mCurrentInventoryItem(Assets::sprites["curinventory"], pos){}
        ~InventoryHUD(){}

        void draw(sf::RenderTarget& target)
        {
            mInventoryBar.draw(target, 1.f);

            for (std::size_t i = 0; i < mInventoryItems.size(); i++)
            {
                auto item = mInventoryItems[i];
                auto pos = mInventoryBar.getRenderPosition();
                item.setPosition(pos + (sf::Vector2f(16 + (31*i), 16)-item.getCenter()));
                item.draw(target, 1.f);
            }

            mCurrentInventoryItem.setPosition(sf::Vector2f((2*mInventoryIndex)+31*mInventoryIndex, 0) + mInventoryBar.getRenderPosition());
            mCurrentInventoryItem.draw(target, 1.f);
        }

        void handleEvents(sf::Event& event, std::size_t inventorySize)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                auto original = mInventoryIndex;

                if (event.key.code == sf::Keyboard::Num1)
                    mInventoryIndex = 0;
                else if (event.key.code == sf::Keyboard::Num2)
                    mInventoryIndex = 1;
                else if (event.key.code == sf::Keyboard::Num3)
                    mInventoryIndex = 2;
                else if (event.key.code == sf::Keyboard::Num4)
                    mInventoryIndex = 3;
                else if (event.key.code == sf::Keyboard::Num5)
                    mInventoryIndex = 4;
                else if (event.key.code == sf::Keyboard::Num6)
                    mInventoryIndex = 5;
                else if (event.key.code == sf::Keyboard::Num7)
                    mInventoryIndex = 6;
                else if (event.key.code == sf::Keyboard::Num8)
                    mInventoryIndex = 7;
                else if (event.key.code == sf::Keyboard::Num9)
                    mInventoryIndex = 8;

                if (mInventoryIndex >= inventorySize)
                    mInventoryIndex = original;
            }
        }

        void addInventoryItem(SpriteObject item){mInventoryItems.push_back(item);}

        std::size_t getInventoryIndex(){return mInventoryIndex;}
        void setInventoryIndex(std::size_t i){mInventoryIndex=i;}

    private:
        SpriteObject mInventoryBar;
        SpriteObject mCurrentInventoryItem;
        std::size_t mInventoryIndex;

        Inventory mInventory;
        std::vector<SpriteObject> mInventoryItems;
};

#endif // INVENTORY_H
