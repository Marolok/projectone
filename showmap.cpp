#include "showmap.h"
#include "ui_showmap.h"

showmap::showmap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showmap)
{
    ui->setupUi(this);
}

showmap::showmap(QWidget *parent, QString str, QString file) :
    QWidget(parent),
    ui(new Ui::showmap)
{
    ui->setupUi(this);
    ui->textEdit->setText(str);
    this->setWindowTitle(file);
}

showmap::~showmap()
{
    delete ui;
}

void showmap::on_pushButton_clicked()
{
    this->close();
}
