#ifndef BD_API_H
#define BD_API_H

#include <QVector>
#include <QString>
#include <iostream>
#include <sstream>
#include <string>
#include <QFile>
#include <QTextStream>

#include "BDObjects/objects.h"
#include "BDObjects/TypeConst.h"
#include "BDObjects/Error.h"

class BD_API{
private:
    TypeConst consts;
    Error errors;
    QVector<Objects*> bd_obj;

    QString bd_file;

public:
    BD_API();
    ~BD_API();

    int BackUp();

    int Add(Objects* obj);
    int Del(Objects* obj);
    int Copy(Objects* obj, QString name);
    QString ShowAll();

    Objects *ReturnObject(int type);
    Objects *ReturnObject(QString name, int type);

    Objects* ReturnObjectNumb(int n);
    int getCountObject(){ return bd_obj.count(); }

    QString backError();
};
#endif // BD_API_H
