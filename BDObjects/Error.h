#ifndef ERROR_H
#define ERROR_H

#include <QDebug>
#include <QString>
#include <sstream>

typedef struct {
    int id_error;
    QString text_error;
} err_struct;

class Error{
public:
    int NOT_ERROR;
    int OBJ_EXIST_DATABASE;
    int OBJ_NOT_EXIST_DATABASE;
    int OBJ_INCORRECT_TYPE;
    int OBJ_INCORRECT_NAME;
    int OBJ_EXIST_OBJECT;
    int OBJ_NOT_EXIST_OBJECT;
    int MAP_NOT_OBJECT;
    int MAP_YES_OBJECT;
    int MAP_BUILD_OBJECT;
    int MAP_EXIST_FILE;
    int MAP_NOT_EXIST_FILE;
    int MAP_FILE_SELECT;
    int MAP_FILE_NOT_SELECT;
    int BD_CLEAR;

    err_struct back_error;

    Error(){
        this->NOT_ERROR = 0;
        this->OBJ_EXIST_DATABASE = 1;
        this->OBJ_NOT_EXIST_DATABASE = 2;
        this->OBJ_INCORRECT_TYPE = 3;
        this->OBJ_INCORRECT_NAME = 4;
        this->OBJ_EXIST_OBJECT = 5;
        this->OBJ_NOT_EXIST_OBJECT = 6;
        this->MAP_NOT_OBJECT = 7;
        this->MAP_YES_OBJECT = 8;
        this->MAP_BUILD_OBJECT = 9;
        this->MAP_EXIST_FILE = 10;
        this->MAP_NOT_EXIST_FILE = 11;
        this->MAP_FILE_SELECT = 12;
        this->MAP_FILE_NOT_SELECT = 13;
        this->BD_CLEAR = 14;

        back_error.id_error = -1;
        back_error.text_error = "";
    }

    /**
     * Сообщение - "Операция выполнена успешно"
     * @brief MES_NOT_ERROR
     * @return
     */
    int MES_NOT_ERROR(){
        back_error.id_error = NOT_ERROR;
        back_error.text_error = "The operation was successful.";
        qDebug() << back_error.text_error;
        return this->NOT_ERROR;
    }

    /**
     * Сообщение - "Объект с таким именем уже существует в БД"
     * @brief MES_OBJ_EXIST_DATABASE
     * @return
     */
    int MES_OBJ_EXIST_DATABASE(){
        back_error.id_error = OBJ_EXIST_DATABASE;
        back_error.text_error =
                "ERROR in database: Object with this name exist in database.";
        qDebug() << back_error.text_error;
        return this->OBJ_EXIST_DATABASE;
    }

    /**
     * Сообщение - "Объект с таким именем не существует в БД"
     * @brief MES_OBJ_NOT_EXIST_DATABASE
     * @return
     */
    int MES_OBJ_NOT_EXIST_DATABASE(){
        back_error.id_error = OBJ_NOT_EXIST_DATABASE;
        back_error.text_error = "ERROR in database: Object with this name don't exist in database.";
        qDebug() << back_error.text_error;
        return this->OBJ_NOT_EXIST_DATABASE;
    }

    /**
     * Сообщение - "Некорректный тип"
     * @brief MES_OBJ_INCORRECT_TYPE
     * @return
     */
    int MES_OBJ_INCORRECT_TYPE(){
        back_error.id_error = OBJ_INCORRECT_TYPE;
        back_error.text_error = "ERROR in database: Incorrect type.";
        qDebug() << back_error.text_error;
        return this->OBJ_INCORRECT_TYPE;
    }

    /**
     * Сообщение - "Некорректное имя"
     * @brief MES_OBJ_INCORRECT_NAME
     * @return
     */
    int MES_OBJ_INCORRECT_NAME(){
        back_error.id_error = OBJ_INCORRECT_NAME;
        back_error.text_error = "ERROR in database: Incorrect name.";
        qDebug() << back_error.text_error;
        return this->OBJ_INCORRECT_NAME ;
    }

    /**
     * Сообщение - "Объект с таким именем существует в объекте"
     * @brief MES_OBJ_EXIST_OBJECT
     * @return
     */
    int MES_OBJ_EXIST_OBJECT(){
        back_error.id_error = OBJ_EXIST_OBJECT;
        back_error.text_error =
                "ERROR in object: Object with this name exist in object.";
        qDebug() << back_error.text_error;
        return this->OBJ_EXIST_OBJECT;
    }

    /**
     * Сообщение - "Объект с таким именем не существует в объекте"
     * @brief MES_OBJ_NOT_EXIST_OBJECT
     * @return
     */
    int MES_OBJ_NOT_EXIST_OBJECT(){
        back_error.id_error = OBJ_NOT_EXIST_OBJECT;
        back_error.text_error =
                "ERROR in object: Object with this name don't exist in object.";
        qDebug() << back_error.text_error;
        return this->OBJ_NOT_EXIST_OBJECT;
    }

    /**
     * Сообщение - "Ячейка с координатами [x,y,z] свободна"
     * @brief MES_MAP_NOT_OBJECT
     * @param x
     * @param y
     * @param z
     * @return
     */
    int MES_MAP_NOT_OBJECT(int x, int y, int z){
        back_error.id_error = MAP_NOT_OBJECT;
        std::stringstream out;
        out << x << "," << y << "," << z;
        back_error.text_error = "ERROR in map: This coordinats [";
        back_error.text_error += QString::fromStdString(out.str());
        back_error.text_error += "] is freedom.";
        qDebug() << back_error.text_error;
        return this->MAP_NOT_OBJECT ;
    }

    /**
     * Сообщение - "Ячейка с координатами [x,y,z] занята"
     * @brief MES_MAP_YES_OBJECT
     * @param x
     * @param y
     * @param z
     * @return
     */
    int MES_MAP_YES_OBJECT(int x, int y, int z){
        back_error.id_error = MAP_YES_OBJECT;
        std::stringstream out;
        out << x << "," << y << "," << z;
        back_error.text_error =
                "ERROR in map: This coordinats ["+
                QString::fromStdString(out.str())+
                "] is occupied.";
        qDebug() << back_error.text_error;
        return this->MAP_YES_OBJECT;
    }

    /**
     * Сообщение - "Неккоректный тип. Ожидался BuildObject(типы 1,2,3,4,6)"
     * @brief MES_MAP_BUILD_OBJECT
     * @return
     */
    int MES_MAP_BUILD_OBJECT(){
        back_error.id_error = MAP_BUILD_OBJECT;
        back_error.text_error =
                "ERROR in map: Incorrect type. Require BuildObject(type";
        back_error.text_error += " by 1,2,3,4,6).";
        qDebug() << back_error.text_error;
        return this->MAP_BUILD_OBJECT;
    }

    /**
     * Сообщение - "Файл с таким именем уже существует"
     * @brief MES_MAP_EXIST_FILE
     * @return
     */
    int MES_MAP_EXIST_FILE(){
        back_error.id_error = MAP_EXIST_FILE;
        back_error.text_error = "ERROR in map: File with this name is exist.";
        qDebug() << back_error.text_error;
        return MAP_EXIST_FILE;
    }

    /**
     * Сообщение - "Файла с таким именем не существует"
     * @brief MES_MAP_NOT_EXIST_FILE
     * @return
     */
    int MES_MAP_NOT_EXIST_FILE(){
        back_error.id_error = MAP_NOT_EXIST_FILE;
        back_error.text_error =
                "ERROR in map: File with this name is not exist.";
        qDebug() << back_error.text_error;
        return MAP_NOT_EXIST_FILE;
    }

    /**
     * Сообщение - "Этот файл уже выбран"
     * @brief MES_MAP_FILE_SELECT
     * @return
     */
    int MES_MAP_FILE_SELECT(){
        back_error.id_error = MAP_FILE_SELECT;
        back_error.text_error = "ERROR in map: It file is selected now.";
        qDebug() << back_error.text_error;
        return MAP_FILE_SELECT;
    }

    /**
     * Сообщение - "Вы не выбрали файл"
     * @brief MES_MAP_FILE_NOT_SELECT
     * @return
     */
    int MES_MAP_FILE_NOT_SELECT(){
        back_error.id_error = MAP_FILE_NOT_SELECT;
        back_error.text_error = "ERROR in map: You are not select file";
        qDebug() << back_error.text_error;
        return MAP_FILE_NOT_SELECT;
    }

    /**
     * Сообщение - "БД пуста"
     * @brief MES_BD_CLEAR
     * @return
     */
    int MES_BD_CLEAR(){
        back_error.id_error = BD_CLEAR;
        back_error.text_error = "ERROR in BD: DataBase is clear.";
        qDebug() << back_error.text_error;
        return BD_CLEAR;
    }
};

#endif // ERROR_H
