#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "QString"
#include "QVector"
#include "sstream"
#include <iostream>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "BDObjects/Error.h"
#include "BDObjects/TypeConst.h"
#include "BDObjects/objects.h"
#include "bd_api.h"

class MapEditor{
private:
    QString activemap;
    QVector<BuildObject*> map;
    Error errors;
    BD_API bd;

    int voto;
    Objects* VectorObjectToObjects(QVector<QString> words);

    int SaerchPos(int x, int y, int z);
    int FreedomPos(int x, int y, int z);


public:
    MapEditor();
    ~MapEditor();
// Работа с QDir
    int CreateMap(QString filename);
    int SelectMap(QString filename);
    int CloseMap();
    bool isActivMap();
//
    int AddObj(int x, int y, int z, QString name, int type);
    int DelObj(int x, int y, int z);
    int ObjTo(int old_x, int old_y, int old_z,
              int new_x, int new_y, int new_z);
    void clearMap();
    /**
      Возвращает количество объектов на карте.
      */
    int getCountObjects(){
        return map.count();
    }

    QString ShowMap(bool full);
    Objects* ReturnObject(int x, int y, int z);
    Objects* ReturnObject(int n);

    QString backError();
};

#endif // MAPEDITOR_H
