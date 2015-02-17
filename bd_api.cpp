#include "bd_api.h"
/**
  Возвращает список слов из строки.
  */
QVector<QString> WordsInString(QString str){
    QVector<QString> words;
    words.clear();
    words.begin();
    QString word = "";
    for(int i = 0; i != str.length(); i++){
        if (str[i] == '[' || str[i] == ']') i++;
        if (str[i] == ' ' || i == str.length()-1){
            words.push_back(word);
            word = "";
        }
        else word += str[i];
    }
    return words;
}
/**
  Конструктор. Считывает всю БД из файла.
  */
BD_API::BD_API(){
    //Загрузить все объекты из файла
    this->bd_obj.clear();
    this->bd_obj.begin();
    this->bd_file =  "BD_OBJECTS";
    QString filedata;
    QFile file(bd_file);
    if (file.open(QIODevice::ReadOnly)){
        while(!file.atEnd()){
            filedata = file.readLine();
            QVector<QString> words = WordsInString(filedata);
            switch (words[0].toInt()){
                case 1:{
                    BuildObject* bo = new BuildObject(words,0);
                    this->Add(bo);
                    break;
                }
                case 2:{
                    OtherObject* oo = new OtherObject(words,0);
                    this->Add(oo);
                    break;
                }
                default:{
                    Objects* o = new Objects(words,0);
                    this->Add(o);
                }
            }
            filedata = "";
        }
        file.close();
    }
    else{
        qDebug()<< "\nERROR in database: Not file for open - *//BD_OBJECTS\n";
    }
}
/**
  Диструктор.
  Записывет всю БД в файл. Тип файла: тип имя img 3d other
  */
BD_API::~BD_API(){
    for(int i = 0; i != this->bd_obj.count(); i++)
        this->bd_obj[i]->~Objects();
}
/**
  Добавляет объект в БД.
  */
int BD_API::Add(Objects* obj){
    if (obj->get3DMod() == "" || obj->getImg() == "" || obj->getName() == ""){
        return this->errors.MES_OBJ_INCORRECT_NAME();
    }
    for(int i = 0; i != this->bd_obj.count(); i++){
        if (this->bd_obj[i] == *obj){
            return errors.MES_OBJ_EXIST_DATABASE();
        }
    }
    switch (obj->getType()){
        case 1:{
            BuildObject* bo = new BuildObject((BuildObject*)obj);
            this->bd_obj.push_back(bo);
            break;
        }
        case 2:{
            OtherObject* oo = new OtherObject((OtherObject*)obj);
            this->bd_obj.push_back(oo);
            break;
        }
        default:{
            Objects* o = new Objects(obj);
            this->bd_obj.push_back(o);
        }
    }
    //this->bd_obj.push_back(this->ReturnObject(obj->type)->Objects(obj));
    return errors.MES_NOT_ERROR();
}
/**
  Удаляяет объект из БД.
  */
int BD_API::Del(Objects* obj){
    for(int i = 0; i != this->bd_obj.count(); i++){
        if (this->bd_obj[i] == *obj){
            this->bd_obj.remove(i);
            return errors.MES_NOT_ERROR();
        }
    }
    return errors.MES_OBJ_NOT_EXIST_DATABASE();
}
/**
  Копирует объект БД. имена должны быть разные.
  */
int BD_API::Copy(Objects* obj, QString name){
    for(int i = 0; i != this->bd_obj.count(); i++){
        if (this->bd_obj[i] == *obj){
            Objects* o;
            switch (obj->getType()){
                case (1):{
                    o =(Objects*) new BuildObject((BuildObject*)bd_obj[i]);
                    break;
                }
                case (2):{
                    o =(Objects*) new OtherObject((OtherObject*)bd_obj[i]);
                    break;
                }
                default:{
                    o = new Objects(bd_obj[i]);
                }
            }
            o->ReName(name);
            if(BD_API::Add(o) != errors.OBJ_EXIST_DATABASE){
                return errors.MES_NOT_ERROR();
            }
            else{
                return errors.MES_OBJ_EXIST_DATABASE();
            }
        }
    }
    return errors.MES_OBJ_NOT_EXIST_DATABASE();
}
/**
  Возвращает "чистые" объекты.
  */
Objects* BD_API::ReturnObject(int type){
    if (type == consts.TYPE_CONST_OBJECT) return new Objects();
    if (type == consts.TYPE_CONST_BUILD_OBJECT) return new BuildObject();
    if (type == consts.TYPE_CONST_OTHER_OBJECT) return new OtherObject();
    if (type == consts.TYPE_CONST_WALL) return new Wall();
    if (type == consts.TYPE_CONST_FLOOR) return new Floor();
    if (type == consts.TYPE_CONST_FURNITURE_OBJECT)
        return new FurnitureObject();
    if (type == consts.TYPE_CONST_OUTBOARD_OBJECT) return new OutboardObject();
    if (type == consts.TYPE_CONST_STANDING_OBJECT) return new StandingObject();
    if (type == consts.TYPE_CONST_PUT_ON_OBJECT) return new PutOnObject();
    if (type == consts.TYPE_CONST_NOT_PUT_ON_OBJECT)
        return new NotPutOnObject();
    errors.MES_OBJ_INCORRECT_TYPE();
    return NULL;
}
/**
  Возвращает указатель на существующие объекты.
  */
Objects* BD_API::ReturnObject(QString name, int type){
    for(int i = 0; i != this->bd_obj.count(); i++){
        if (this->bd_obj[i]->getType() == type &&
                this->bd_obj[i]->getName() == name)
            return this->bd_obj[i];
    }
    qDebug() << "\nERROR in database: Incorrect type or name.";
    return NULL;
}
/**
  Возвращает указателы на существующие объекты.
  */
Objects* BD_API::ReturnObjectNumb(int n){
    return bd_obj[n];
}
/**
  Возвращает всю БД (имя тип) записанную с строку. Выводит Бд в консоль.
  */
QString BD_API::ShowAll(){
    qDebug() << "\n DATABASE OBJECT \n";
    std::stringstream out;
    for(int i = 0; i != bd_obj.count(); i++){
        out << bd_obj[i]->getName().toStdString() << " "
            << bd_obj[i]->getType() << "\n";
    }
    qDebug() << QString::fromStdString(out.str());
    return QString::fromStdString(out.str());
}
/**
  Записывает всю БД в файл.
  */
int BD_API::BackUp(){
    if (this->bd_obj.count() == 0) return errors.MES_BD_CLEAR();
    QFile* file = new QFile(bd_file);
    if (file->open(QIODevice::WriteOnly)){
        QTextStream stream (file);
        stream.setCodec("UTF-8");
        for(int i = 0; i != bd_obj.count(); i++){
            stream << bd_obj[i]->ShowInfo() << "\n";
        }
        stream.flush();
    }
    file->close();
    delete file;
    return errors.MES_NOT_ERROR();
}
/**
  Возвращает описание последней ошибки.
  */
QString BD_API::backError(){
    return ("BD_API back error: "+this->errors.back_error.text_error);
}
