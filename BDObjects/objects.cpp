#include "objects.h"
/**
  Конструкторы
  */
Objects::Objects(){
    this->name = "";
    this->mod3d = "";
    this->img = "";
    this->objects.clear();
    this->objects.begin();
    this->type = this->consts.TYPE_CONST_OBJECT;
}
Objects::Objects(Objects* a){
    this->name = a->name;
    this->img = a->img;
    this->mod3d = a->mod3d;
    this->type = a->type;
    this->objects = a->objects;
}
Objects::Objects(QVector<QString> it, int pos){
    int i = pos;
    this->type = it[i++].toInt();
    this->name = it[i++];
    this->img = it[i++];
    this->mod3d = it[i];
    this->objects.clear();
    this->objects.begin();
}
BuildObject::BuildObject(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->type = this->consts.TYPE_CONST_BUILD_OBJECT;
}
BuildObject::BuildObject(BuildObject* a){
    this->name = a->getName();
    this->img = a->img;
    this->mod3d = a->mod3d;
    this->type = 1;
    this->objects = a->objects;
    this->x = a->x;
    this->y = a->y;
    this->z = a->z;
}
BuildObject::BuildObject(QVector<QString> it, int pos){
    int i = pos;
    this->type = it[i++].toInt();
    this->name = it[i++];
    this->img = it[i++];
    this->mod3d = it[i++];
    this->x = it[i++].toInt();
    this->y = it[i++].toInt();
    this->z = it[i].toInt();
    this->objects.clear();
    this->objects.begin();
}
OtherObject::OtherObject(){
    this->linkage = false;
    this->type = this->consts.TYPE_CONST_OTHER_OBJECT;
}
OtherObject::OtherObject(OtherObject* a){
    this->name = a->name;
    this->img = a->img;
    this->mod3d = a->mod3d;
    this->type = 2;
    this->objects = a->objects;
    this->x = a->x;
    this->y = a->y;
    this->z = a->z;
    this->linkage = a->linkage;
}
OtherObject::OtherObject(QVector<QString> it, int pos){
    int i = pos;
    this->type = it[i++].toInt();
    this->name = it[i++];
    this->img = it[i++];
    this->mod3d = it[i++];
    this->x = it[i++].toInt();
    this->y = it[i++].toInt();
    this->z = it[i++].toInt();
    this->linkage = it[i].toInt();
    this->objects.clear();
    this->objects.begin();
}
Wall::Wall(){
    this->type = this->consts.TYPE_CONST_WALL;
}
Floor::Floor(){
    this->type = this->consts.TYPE_CONST_FLOOR;
}
FurnitureObject::FurnitureObject(){
    this->type = this->consts.TYPE_CONST_FURNITURE_OBJECT;
}
OutboardObject::OutboardObject(){
    this->type = this->consts.TYPE_CONST_OUTBOARD_OBJECT;
}
StandingObject::StandingObject(){
    this->type = this->consts.TYPE_CONST_STANDING_OBJECT;
}
PutOnObject::PutOnObject(){
    this->type = this->consts.TYPE_CONST_PUT_ON_OBJECT;
}
NotPutOnObject::NotPutOnObject(){
    this->type = this->consts.TYPE_CONST_NOT_PUT_ON_OBJECT;
}
/**
  Диструкторы
  */
Objects::~Objects(){
    for(int i=0; i != this->objects.count(); i++){
        if (this->objects[i]->getObjectsCount() != 0){
            this->objects[i]->~Objects();
        }
    }
    this->objects.clear();
}
/**
  Вывод информации
  */
QString Objects::ShowInfo(){
    if (this->type == 1)
        return ((new BuildObject((BuildObject*)this))->ShowInfo());
    if (this->type == 2)
        return ((new OtherObject((OtherObject*)this))->ShowInfo());
    std::stringstream out;
    out << this->type << " " << this->name.toStdString() << " ["
        << this->img.toStdString() << "] [" << this->mod3d.toStdString()
        << "] [";
    if (this->objects.count() == 0){
        out << "NULL]";
        qDebug() << "\n" << QString::fromStdString(out.str()) << "\n";
        return QString::fromStdString(out.str());
    }
    for(int i = 0; i != this->objects.count(); i++){
        if (i != this->objects.count()-1)
            out << "(" <<this->objects[i]->ShowInfo().toStdString() << "),";
        else out << "(" <<this->objects[i]->ShowInfo().toStdString() << ")]";
    }
    qDebug() << "\n" << QString::fromStdString(out.str()) << "\n";
    return QString::fromStdString(out.str());
}
QString BuildObject::ShowInfo(){
    if (this->type == 2)
        return ((new OtherObject((OtherObject*)this))->ShowInfo());
    std::stringstream out;
    out << this->type << " " << this->name.toStdString() << " ["
        << this->img.toStdString() << "] [" << this->mod3d.toStdString()
        << "] " << this->x << " " << this->y << " " << this->z <<" [";
    if (this->objects.count() == 0){
        out << "NULL]";
        qDebug() << "\n" << QString::fromStdString(out.str()) << "\n";
        return QString::fromStdString(out.str());
    }
    for(int i = 0; i != this->objects.count(); i++){
        if (i != this->objects.count()-1)
            out << "(" <<this->objects[i]->ShowInfo().toStdString() << "),";
        else out << "(" <<this->objects[i]->ShowInfo().toStdString() << ")]";
    }
    qDebug() << "\n" << QString::fromStdString(out.str()) << "\n";
    return QString::fromStdString(out.str());
}
QString OtherObject::ShowInfo(){
    std::stringstream out;
    out << this->type << " " << this->name.toStdString() << " ["
        << this->img.toStdString() << "] [" << this->mod3d.toStdString()
        << "] " << this->x << " " << this->y << " " << this->z << " "
        << this->linkage << " [";
    if (this->objects.count() == 0){
        out << "NULL]";
        qDebug() << "\n" << QString::fromStdString(out.str()) << "\n";
        return QString::fromStdString(out.str());
    }
    for(int i = 0; i != this->objects.count(); i++){
        if (i != this->objects.count()-1)
            out << "(" <<this->objects[i]->ShowInfo().toStdString() << "),";
        else out << "(" <<this->objects[i]->ShowInfo().toStdString() << ")]";
    }
    qDebug() << "\n" << QString::fromStdString(out.str()) << "\n";
    return QString::fromStdString(out.str());
}
/**
  Сравнение двух объектов
  */
bool operator==(const Objects& left, const Objects& right) {
    return (left.name == right.name && left.img == right.img &&
            left.mod3d == right.mod3d);
}
bool operator==(const BuildObject& left, const BuildObject& right) {
    return (left.name == right.name && left.img == right.img &&
            left.mod3d == right.mod3d && left.x == right.x &&
            left.y == right.y);
}
bool operator==(const OtherObject& left, const OtherObject& right) {
    return (left.name == right.name && left.img == right.img &&
            left.mod3d == right.mod3d && left.x == right.x &&
            left.y == right.y && left.linkage == right.linkage);
}
/**
  Добавление объекта в объект
  */
int Objects::Add(Objects *obj){
    for(int i=0; i != this->objects.count(); i++){
        if (obj == this->objects[i]){
            return errors.MES_OBJ_EXIST_OBJECT();
        }
    }
    Objects* new_obj = new Objects(obj);
    this->objects.push_back(new_obj);
    return errors.MES_NOT_ERROR();
}
/**
  Удаление объекта из объекта
  */
int Objects::Del(Objects *obj){
    int i;
    for(i=0; i != this->objects.count(); i++){
        if (*obj == *(this->objects[i])){
            this->objects.remove(i);
            return errors.MES_NOT_ERROR();
        }
    }
    return errors.MES_OBJ_NOT_EXIST_OBJECT();
}
/**
  Переименование
  */
void Objects::ReName(QString name){
    this->name = name;
}
/**
  Изменение картинки
  */
void Objects::ReImg(QString img){
    this->img = img;
}
/**
  Изменение 3D модели
  */
void Objects::Re3DMod(QString mod3d){
    this->mod3d = mod3d;
}
/**
  Изменение идентификатора типа
  */
void Objects::ReType(int type){
    this->type = type;
}
