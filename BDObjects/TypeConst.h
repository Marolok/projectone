#ifndef TYPECONST_H
#define TYPECONST_H

#include <QMap>

class TypeConst{
public:
    int TYPE_CONST_OBJECT;
    int TYPE_CONST_BUILD_OBJECT;
    int TYPE_CONST_OTHER_OBJECT;
    int TYPE_CONST_WALL;
    int TYPE_CONST_FLOOR;
    int TYPE_CONST_FURNITURE_OBJECT;
    int TYPE_CONST_OUTBOARD_OBJECT;
    int TYPE_CONST_STANDING_OBJECT;
    int TYPE_CONST_PUT_ON_OBJECT;
    int TYPE_CONST_NOT_PUT_ON_OBJECT;

    QMap<int, QString> types;

    TypeConst(){
        TYPE_CONST_OBJECT = 0;
        types.insert(0, "Objects");
        TYPE_CONST_BUILD_OBJECT = 1;
        types.insert(1,"BuildObject");
        TYPE_CONST_OTHER_OBJECT = 2;
        types.insert(2,"OtherObject");
        TYPE_CONST_WALL = 3;
        types.insert(3,"Wall");
        TYPE_CONST_FLOOR = 4;
        types.insert(4,"Floor");
        TYPE_CONST_FURNITURE_OBJECT = 5;
        types.insert(5,"FurnitureObject");
        TYPE_CONST_OUTBOARD_OBJECT = 6;
        types.insert(6,"OutboardObject");
        TYPE_CONST_STANDING_OBJECT = 7;
        types.insert(7,"StandingObject");
        TYPE_CONST_PUT_ON_OBJECT = 8;
        types.insert(8,"PutOnObject");
        TYPE_CONST_NOT_PUT_ON_OBJECT = 9;
        types.insert(9,"NotPutOnObject");
    }

    bool itIsType(QString type_s){
        return (type_s == "Objects" ||
                type_s == "BuildObject" ||
                type_s == "OtherObject" ||
                type_s == "Wall" ||
                type_s == "Floor" ||
                type_s == "FurnitureObject" ||
                type_s == "OutboardObject" ||
                type_s == "StandingObject" ||
                type_s == "PutOnObject" ||
                type_s == "NotPutOnObject");
    }
};

#endif // TYPECONST_H
