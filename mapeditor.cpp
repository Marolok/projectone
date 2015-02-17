#include "mapeditor.h"
/**
  Конструктор.
  */
MapEditor::MapEditor(){
    this->activemap = "";
    this->map.clear();
    this->map.begin();
    QDir dir(QDir::currentPath());
    dir.mkdir("map");
}
/**

  */
void MapEditor::clearMap(){
    // Очистка памяти
    for(int i=0; i != this->map.count(); i++){
        if (this->map[i]->getObjectsCount() != 0){
            this->map[i]->~Objects();
        }
    }
    this->map.clear();
}

/**
  Диструктор
  */
MapEditor::~MapEditor(){
    // Запись в файл
    if (this->activemap != ""){
        this->CloseMap();
    }
    this->clearMap();
}
/**
  Переделывает последовательность слов в объекты.
  */
Objects* MapEditor::VectorObjectToObjects(QVector<QString> words){
    Objects* o;
    qDebug() << "1 VOTO - " << voto << " " << words[voto];
    switch (words[voto].toInt()){
        case 1:{
            o = new BuildObject(words,voto);
            voto += 7;
            break;
        }
        case 2:{
            o = new OtherObject(words,voto);
            voto += 8;
            break;
        }
        default:{
            o = new Objects(words, voto);
            voto += 4;
        }
    }
    qDebug() << "2 VOTO - " << voto << " " <<words[voto];
    if (words[voto] == "NULL"){
        voto++;
        qDebug() << "VOTO - " << voto;
        return o;
    }
    qDebug() << "3 VOTO - " << voto << " " <<words[voto];
    while (words.count() != voto){
        o->Add(VectorObjectToObjects(words));
        if (voto < words.count())
            qDebug() << "VOTO - " << voto << " " << words[voto];
    }
    return o;
}
/**
  Возвращает слова из строки
  */
QVector<QString> WordsInString1(QString str){
    QVector<QString> words;
    words.clear();
    words.begin();
    QString word = "";
    for(int i = 0; i != str.length(); i++){
        if(!(str[i] == '[' || str[i] == ']' || str[i] == '(' || str[i] == ')')){
            if (str[i] == ',' || str[i] == ' ' || i == str.length()-1){
                words.push_back(word);
                word = "";
            }
            else word += str[i];
        }
    }
    for(int i=0; i != words.count(); i++){
        qDebug() << words[i];
    }
    return words;
}

bool MapEditor::isActivMap(){
    if(this->activemap == "") return false;
    else return true;
}

/**
  Создает карту в директории /map, если есть, иначе возвращает ошибку
  */
int MapEditor::CreateMap(QString filename){
    //if (activemap == filename) return errors.MES_MAP_FILE_SELECT();
    QDir dir(QDir::currentPath());
    dir.mkdir("map");
    dir.setPath(QDir::currentPath()+"/map");
    QFileInfoList dirContent = dir.entryInfoList(QStringList()
        << "*.txt", QDir::Files);
    QVector<QFileInfo> dc = dirContent.toVector();
    for (int i=0; i != dc.count(); i++){
        qDebug() << dc[i].filePath();
        if (filename == dc[i].fileName()){
            //activemap = filename;
            return errors.MES_MAP_EXIST_FILE();
        }
    }

    QFile file(QDir::currentPath()+"/map/"+filename);
    file.open(QIODevice::WriteOnly);
    file.close();
    //this->activemap = filename;
    return errors.MES_NOT_ERROR();
}
/**
  Открывает существующую карту в директории /map, если нет то возвращает ошибку.
  При существующем файле делает его активным и загружает.
  */
int MapEditor::SelectMap(QString filename){
    if (activemap == filename) return errors.MES_MAP_FILE_SELECT();
    QDir dir(QDir::currentPath()+"/map");
    QFileInfoList dirContent = dir.entryInfoList(QStringList()
        << "*.txt", QDir::Files);
    QVector<QFileInfo> dc = dirContent.toVector();
    qDebug() << "\nSelectMap - " + dir.path();
    for (int i=0; i != dc.count(); i++){
        if (filename == dc[i].fileName()){
            //Спросить о сохранении активного файла.
            //TODO Полностью загрузить карту из файла.

            QFile file(dc[i].filePath());
            if (file.open(QIODevice::ReadOnly)){
                while(!file.atEnd()){
                    QString filedata = file.readLine();
                    qDebug() << "\nwords";
                    QVector<QString> words = WordsInString1(filedata);
                    qDebug() << "\nVOTO - "<< words.count()<<"\n";
                    voto = 0;
                    map.push_back((BuildObject*)VectorObjectToObjects(words));
                    filedata = "";
                    qDebug() << "\nVOTO - end\n";
                }
                file.close();
            }
            this->activemap = filename;
            return errors.MES_NOT_ERROR();
        }
    }
    return errors.MES_MAP_NOT_EXIST_FILE();
}
/**
  Закрывает активный файл, предварительно сохранив его.
  */
int MapEditor::CloseMap(){
    if (activemap == "") return errors.MES_MAP_FILE_NOT_SELECT();    
    qDebug() << "\nCLOSE MAP";
    QFile file(QDir::currentPath()+"/map/"+activemap);
    if (file.open(QIODevice::WriteOnly)){
        QTextStream stream (&file);
        stream.setCodec("UTF-8");
        for(int i=0; i != map.count(); i++){
            QString info = map[i]->ShowInfo();
            qDebug() <<"info " << info;
            stream << info << "\n";
        }
        stream.flush();
    }
    file.close();
    this->activemap = "";
    this->clearMap();
    return errors.MES_NOT_ERROR();
}
/**
  Проверяет ячейку поля на занятость
  */
int MapEditor::SaerchPos(int x, int y, int z){
    for(int i = 0; i != this->map.count(); i++){
        if (map[i]->x == x && map[i]->y == y && map[i]->z == z) return i;
    }
    return -1;
}
/**
  Возвращает состояние ячейки поля
  */
int MapEditor::FreedomPos(int x, int y, int z){
    if (this->SaerchPos(x,y,z) != -1) return errors.MAP_YES_OBJECT;
    else return errors.MAP_NOT_OBJECT;
}
/**
  Добавляет объект на карту
  */
int MapEditor::AddObj(int x, int y, int z, QString name, int type){
    if (activemap == "") return errors.MES_MAP_FILE_NOT_SELECT();
    qDebug() << "ADD OBJECT TO MAP " << name << " " << type << "\n";
    if (type > 0 && type < 7 && type != 5){
        BuildObject* o;
        o = new BuildObject((BuildObject*)this->bd.ReturnObject(name,type));
        o->ReType(type);
        if (o != NULL){
            if (this->FreedomPos(x,y,z) == errors.MAP_NOT_OBJECT){
                o->x = x;
                o->y = y;
                o->z = z;
                this->map.push_back(o);
                return errors.MES_NOT_ERROR();
            }
            return errors.MES_MAP_YES_OBJECT(x,y,z);
        }
        return errors.MES_OBJ_NOT_EXIST_DATABASE();
    }
    return errors.MES_MAP_BUILD_OBJECT();
}
/**
  Удаляет объект с карты
  */
int MapEditor::DelObj(int x, int y, int z){
    if (activemap == "") return errors.MES_MAP_FILE_NOT_SELECT();
    int i = this->SaerchPos(x,y,z);
    if (i != -1){
        this->map.remove(i);
        return errors.MES_NOT_ERROR();
    }
    return errors.MES_MAP_NOT_OBJECT(x,y,z);
}
/**
  Передвигает объект в другую ячейку
  */
int MapEditor::ObjTo(int old_x, int old_y, int old_z,
                     int new_x, int new_y, int new_z){
    if (activemap == "") return errors.MES_MAP_FILE_NOT_SELECT();
    if (old_x == new_x && old_y == new_y && old_z == new_z)
        return errors.MES_NOT_ERROR();
    if (this->FreedomPos(old_x, old_y, old_z) == errors.MAP_NOT_OBJECT){
        return errors.MES_MAP_NOT_OBJECT(old_x, old_y, old_z);
    }
    if (this->FreedomPos(new_x, new_y, new_z) == errors.MAP_YES_OBJECT){
        return errors.MES_MAP_YES_OBJECT(new_x, new_y, new_z);
    }
    int i = this->SaerchPos(old_x, old_y, old_z);
    this->map[i]->x = new_x;
    this->map[i]->y = new_y;
    this->map[i]->z = new_z;
    return errors.MES_NOT_ERROR();
}
/**
  Возвращает информацию об объектах на карте + Выводит в консоль.
  */
QString MapEditor::ShowMap(bool full){
    std::stringstream out;
    for(int i = 0; i != this->map.count(); i++){
        //можно отсортировать
        if (full == false){
            out << "[" << map[i]->x << "," << map[i]->y << "," << map[i]->z << "] "
                << map[i]->getName().toStdString() << " "
                << map[i]->getType() << "\n";
        }
        else out << map[i]->ShowInfo().toStdString() << "\n";
    }
    qDebug() << "\n--- MAP OBJECT ---";
    qDebug() << QString::fromStdString(out.str());
    qDebug() << "------";
    return QString::fromStdString(out.str());
}
/**
  Возвращает ссылку на объект, который находится на активной карте
    по координатам.
  */
Objects* MapEditor::ReturnObject(int x, int y, int z){
    if (activemap == "") {
        errors.MES_MAP_FILE_NOT_SELECT();
        return NULL;
    }
    int i = this->SaerchPos(x,y,z);
    if (i != -1){
        errors.MES_NOT_ERROR();
        return map[i];
    }
    errors.MES_MAP_NOT_OBJECT(x,y,z);
    return NULL;
}
/**
  Возвращает ссылку на объект, который находится на активной карте
    по номеру.
  */
Objects* MapEditor::ReturnObject(int n){
    if (activemap == "") {
        errors.MES_MAP_FILE_NOT_SELECT();
        return NULL;
    }
    return map[n];
}
/**
  Выводит последную ошибку
  */
QString MapEditor::backError(){
    return ("MapEditor back error: "+this->errors.back_error.text_error);
}
