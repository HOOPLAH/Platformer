#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
    public:
        Item();
        virtual ~Item();

        virtual void use(){mCount--;}
        virtual void update(){}

        int getStackSize(){return mStackSize;}
        int getCount(){return mCount;}
        std::string getName(){return mName;}

        void setStackSize(int size){mStackSize=size;}
        void setCount(int count){mCount=count;}
        void setName(std::string name){mName=name;}

    protected:
        int mStackSize;
        int mCount;
        std::string mName;
};

#endif // ITEM_H
