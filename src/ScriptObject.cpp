#include "ScriptObject.h"

ScriptObject::ScriptObject(std::string className, HSQUIRRELVM vm) :
    mClassName(className),
    mClass(className.c_str(), vm),
    mInstance(mClass.New())
{
    //ctor
}

ScriptObject::~ScriptObject()
{
    //dtor
}
