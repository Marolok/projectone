#include "objquestion.h"
#include "ui_objquestion.h"

ObjQuestion::ObjQuestion(BD_API *bd_api, Objects* obj, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjQuestion)
{
    ui->setupUi(this);
    this->bd_api = bd_api;
    this->obj = obj;

    ui->lineEdit->setText("");
}

ObjQuestion::~ObjQuestion()
{
    delete ui;
}

void ObjQuestion::on_pushButton_2_clicked(){
    this->close();
}

void ObjQuestion::on_pushButton_clicked(){
    Error err;
    int func = bd_api->Copy(obj,ui->lineEdit->text());
    QString mess = "";
    if (func == err.NOT_ERROR)
        mess = "Copy of the object is created successfully.\n";
    else
        mess = "Object with the same name already exists in the database.";

    if (func == err.NOT_ERROR){
        if(bd_api->BackUp() == err.NOT_ERROR){
            mess += "Database is saved.";
        }
        else{
            mess += "Database is not saved.";
        }
        QMessageBox::information(this, "Copy object", mess);
        this->close();
    }
    else{
        QMessageBox::information(this, "Copy object", mess);
    }
}
