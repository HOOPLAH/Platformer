#ifndef SCRIPTOBJECT_H
#define SCRIPTOBJECT_H

#include <string>

#include <squirrel.h>
#include <sqext.h>
#include <sqrat.h>

class ScriptObject
{
    public:
        ScriptObject(std::string className);
        ~ScriptObject();

        std::string getClassName(){return mClassName;}

        void bind(std::string funcName){mClass.bind(funcName.c_str());}
        void call(std::string funcName){mInstance.call(funcName.c_str());}

    private:
        std::string mClassName;
        sqext::SQIClass mClass;
        sqext::SQIClassInstance mInstance;
};

#endif // SCRIPTOBJECT_H
