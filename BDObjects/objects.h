#ifndef OBJECTS_H
#define OBJECTS_H

#include <QString>
#include <QVector>
#include <sstream>
#include <QDebug>

#include "TypeConst.h"
#include "BDObjects/Error.h"

class Objects{
protected:
    int type;
    QString name;
    QString img;
    QString mod3d;
    QVector<Objects*> objects;

    TypeConst consts;
    Error errors;
public:
    Objects();
    Objects(Objects* a);
    Objects(QVector<QString> it, int pos);
    ~Objects();
    QString ShowInfo();
    int Add(Objects* obj);
    int Del(Objects* obj);
    void DelAll() { this->objects.clear(); }
    void ReName(QString name);
    void ReType(int type);
    void Re3DMod(QString mod3d);
    void ReImg(QString img);

    QString getName(){ return this->name; }
    int getType(){ return this->type; }
    QString getImg() { return this->img; }
    QString get3DMod() { return this->mod3d; }
    Objects* getObject(int i) {return new Objects(this->objects[i]); }
    int getObjectsCount(){ return this->objects.count(); }

    friend bool operator==(const Objects& left, const Objects& right);
    /**
      Операция присваивания
      */
    Objects& operator=(const Objects& right){
        if (this == &right) {
            return *this;
        }
        this->name = right.name;
        this->img = right.img;
        this->mod3d = right.mod3d;
        this->type = right.type;
        this->objects = right.objects;
        return *this;
    }
};

//  BuildObject
class BuildObject: public Objects{
public:
    int x;
    int y;
    int z;

    BuildObject();
    BuildObject(BuildObject* a);
    BuildObject(QVector<QString> it, int pos);
    QString ShowInfo();

    friend bool operator==(const BuildObject& left, const BuildObject& right);
    /**
      Операция присваивания
      */
    BuildObject& operator=(const BuildObject& right){
        if (this == &right) {
            return *this;
        }
        this->name = right.name;
        this->img = right.img;
        this->mod3d = right.mod3d;
        this->type = right.type;
        this->objects = right.objects;
        this->x = right.x;
        this->y = right.y;
        this->z = right.z;
        return *this;
    }
};

/** OTHER **/
class OtherObject: public BuildObject{
public:
    bool linkage;

    OtherObject();
    OtherObject(OtherObject* a);
    OtherObject(QVector<QString> it, int pos);
    QString ShowInfo();

    friend bool operator==(const OtherObject& left, const OtherObject& right);
    /**
      Операция присваивания
      */
    OtherObject& operator=(const OtherObject& right){
        if (this == &right) {
            return *this;
        }
        this->name = right.name;
        this->img = right.img;
        this->mod3d = right.mod3d;
        this->type = right.type;
        this->objects = right.objects;
        this->x = right.x;
        this->y = right.y;
        this->z = right.z;
        this->linkage = right.linkage;
        return *this;
    }
};

/** CTEHA **/
class Wall: public BuildObject{
public:
    Wall();
};

/** POL **/
class Floor: public BuildObject{
public:
    Floor();
};

// FurnitureObjects
class FurnitureObject: public Objects{
public:
    FurnitureObject();
};
/** Объекты, которые висят **/
class OutboardObject: public FurnitureObject{
public:
    OutboardObject();
};
/** Объекты, которые стоят **/
class StandingObject: public FurnitureObject{
public:
    StandingObject();
};
/** Объекты, на которые можно поставить объект **/
class PutOnObject: public StandingObject{
public:
    PutOnObject();
};
/** Объекты, на которые нельзя поставить объект **/
class NotPutOnObject: public StandingObject{
public:
    NotPutOnObject();
};

#endif // OBJECTS_H
