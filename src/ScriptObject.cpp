#include "ScriptObject.h"

ScriptObject::ScriptObject(std::string className) :
    mClassName(className),
    mClass(className.c_str(), Sqrat::DefaultVM::Get()),
    mInstance(mClass.New())
{
    //ctor
}

ScriptObject::~ScriptObject()
{
    //dtor
}
