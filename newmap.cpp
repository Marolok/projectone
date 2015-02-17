#include "newmap.h"
#include "ui_newmap.h"

#include <QMessageBox>
#include "BDObjects/Error.h"

NewMap::NewMap(MapEditor *me, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewMap)
{
    ui->setupUi(this);

    this->me = me;
}

NewMap::~NewMap()
{
    delete ui;
}

void NewMap::on_pushButton_2_clicked()
{
    this->close();
}

void NewMap::on_pushButton_clicked(){
    Error error;
    if(me->CreateMap(ui->lineEdit->text()) == error.MES_NOT_ERROR()){
        QMessageBox::information(this, "Create map", me->backError());
        this->close();
    }
    else{
        QMessageBox::information(this, "Create map", me->backError());
    }
}
