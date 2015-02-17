#include "objectinfo.h"
#include "ui_objectinfo.h"

ObjectInfo::ObjectInfo(BD_API* bd_api, QString name, QString type_s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectInfo)
{
    ui->setupUi(this);
    initComboBox();

    this->bd_api = bd_api;
    TypeConst types;
    obj = bd_api->ReturnObject(name, types.types.key(type_s));

    initValues();
}

ObjectInfo::ObjectInfo(BD_API* bd_api, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectInfo)
{
    ui->setupUi(this);

    this->bd_api = bd_api;

    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_7->setDisabled(true);

    initComboBox();
    this->on_comboBox_activated(0);
}
/**
  Инициализация ComboBox объектами.
  */
void ObjectInfo::initComboBox(){
    ui->comboBox->addItem("Object");
    ui->comboBox->addItem("BuildObject");
    ui->comboBox->addItem("OtherObject");
    ui->comboBox->addItem("Wall");
    ui->comboBox->addItem("Floor");
    ui->comboBox->addItem("FurnitureObject");
    ui->comboBox->addItem("OutboardObject");
    ui->comboBox->addItem("StandingObject");
    ui->comboBox->addItem("PutOnObject");
    ui->comboBox->addItem("NotPutOnObject");
}
/**
  Инициализация формы согласно полученному объекту.
  */
void ObjectInfo::initValues(){
    ui->comboBox->setCurrentIndex(obj->getType());
    this->on_comboBox_activated(obj->getType());
    ui->lineEdit->setText(obj->getName());
    ui->lineEdit_2->setText(obj->getImg());
    ui->lineEdit_3->setText(obj->get3DMod());
    if (obj->getType() > 0 && obj->getType() < 5){
        ui->spinBox->setValue(((BuildObject*)obj)->x);
        ui->spinBox_2->setValue(((BuildObject*)obj)->y);
        ui->spinBox_3->setValue(((BuildObject*)obj)->z);
        if (obj->getType() == 2){
            ui->checkBox->setChecked(((OtherObject*)obj)->linkage);
        }
    }
    if(obj->getObjectsCount() != 0){
        initTree();
    }
}
/**
    Инициализация дерева объектов.
  */
void ObjectInfo::initTree(){
    QStandardItemModel* standardModel = new QStandardItemModel;
    QStandardItem *rootNode = standardModel->invisibleRootItem();
    QIcon ico;

    QStandardItem *objects = new QStandardItem("Objects");
    QStandardItem *buildobjects = new QStandardItem("BuildObject");
    QStandardItem *otherobjects = new QStandardItem("OtherObject");
    QStandardItem *wall =  new QStandardItem("Wall");
    QStandardItem *floor =  new QStandardItem("Floor");
    QStandardItem *furnitureobjects =   new QStandardItem("FurnitureObject");
    QStandardItem *outboardobjects =    new QStandardItem("OutboardObject");
    QStandardItem *standingobject =  new QStandardItem("StandingObject");
    QStandardItem *puton =  new QStandardItem("PutOnObject");
    QStandardItem *notputon =  new QStandardItem("NotPutOnObject");

    rootNode->appendRow(objects);
    ico.addFile("./img/ball_r.png");
    objects->setIcon(ico);
    ico.addFile("./img/ball_b.png");
    objects->appendRow(buildobjects);
    objects->appendRow(furnitureobjects);

    buildobjects->setIcon(ico);
    furnitureobjects->setIcon(ico);
    ico.addFile("./img/ball_g.png");

    buildobjects->appendRow(otherobjects);
    buildobjects->appendRow(wall);
    buildobjects->appendRow(floor);
    furnitureobjects->appendRow(outboardobjects);
    furnitureobjects->appendRow(standingobject);


    otherobjects->setIcon(ico);
    wall->setIcon(ico);
    floor->setIcon(ico);
    outboardobjects->setIcon(ico);
    standingobject->setIcon(ico);

    ico.addFile("./img/ball_o.png");
    puton->setIcon(ico);
    notputon->setIcon(ico);
    standingobject->appendRow(puton);
    standingobject->appendRow(notputon);

    for(int i=0; i<obj->getObjectsCount(); i++){
        Objects* object = obj->getObject(i);
        QStandardItem* item = new QStandardItem(object->getName());

        ico.addFile(object->getImg());
        item->setIcon(ico);
        //qDebug() << obj->getName() << obj->getType();
        switch (object->getType()){
            case 0:{ objects->appendRow(item); break;}
            case 1:{ buildobjects->appendRow(item); break;}
            case 2:{ otherobjects->appendRow(item); break;}
            case 3:{ wall->appendRow(item); break;}
            case 4:{ floor->appendRow(item); break;}
            case 5:{ furnitureobjects->appendRow(item); break;}
            case 6:{ outboardobjects->appendRow(item); break;}
            case 7:{ standingobject->appendRow(item); break;}
            case 8:{ puton->appendRow(item); break;}
            case 9:{ notputon->appendRow(item); break;}
        }
    }

    ui->treeView->setModel(standardModel);
    ui->treeView->expandAll();
}

ObjectInfo::~ObjectInfo(){
    delete ui;
}

void ObjectInfo::paintEvent(QPaintEvent *){
    //HAXEPA????
}
/**
  Закрытие формы.
  */
void ObjectInfo::on_pushButton_6_clicked(){
    this->close();
}
/**
  Получение пути к изображениию объекта.
  */
void ObjectInfo::on_pushButton_clicked(){
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open file..."),
                "./",
                tr("Image (*.png)"));
    if (filename != "") ui->lineEdit_2->setText(filename);
}
/**
  Получение пути к 3D объекту.
  */
void ObjectInfo::on_pushButton_2_clicked(){
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open file..."),
                "./",
                tr("3D mod (*.obj)"));
    ui->lineEdit_3->setText(filename);
}
/**
  Настройка видимости виджетов на форме.
  */
void ObjectInfo::on_comboBox_activated(int index){
    qDebug() << " Activateed ComboBox. Index - "<< index;
    if (index > 0 && index < 5){
        ui->label_5->setVisible(true);
        ui->spinBox->setVisible(true);
        ui->label_6->setVisible(true);
        ui->spinBox_2->setVisible(true);
        ui->label_7->setVisible(true);
        ui->spinBox_3->setVisible(true);

        ui->label_9->setVisible(false);
        ui->checkBox->setVisible(false);
        if (index == 2){
            ui->label_9->setVisible(true);
            ui->checkBox->setVisible(true);
        }
    }
    else{
        ui->label_5->setVisible(false);
        ui->spinBox->setVisible(false);
        ui->label_6->setVisible(false);
        ui->spinBox_2->setVisible(false);
        ui->label_7->setVisible(false);
        ui->spinBox_3->setVisible(false);
        ui->label_9->setVisible(false);
        ui->checkBox->setVisible(false);
    }
}
/**
  Добавление объектов.
  */
void ObjectInfo::on_pushButton_3_clicked(){
    Objects* obj = bd_api->ReturnObject(ui->comboBox->currentIndex());
    obj->ReName(ui->lineEdit->text());
    obj->ReImg(ui->lineEdit_2->text());
    obj->Re3DMod(ui->lineEdit_3->text());
    if (obj->getType() > 0 && obj->getType() < 5){
        ((BuildObject*)obj)->x = ui->spinBox->value();
        ((BuildObject*)obj)->y = ui->spinBox_2->value();
        ((BuildObject*)obj)->z = ui->spinBox_3->value();
        if (obj->getType() == 2){
            ((OtherObject*)obj)->linkage = ui->checkBox->checkState();
        }
    }
    Error err;
    QString mess = "";
    int func = bd_api->Add(obj);
    if(func == err.NOT_ERROR){
        mess = "Object is added successfully.\n";
    }
    else{
        if(func == err.OBJ_INCORRECT_NAME){
            mess = "Check the input fields.\n";
        }
        else{
            mess = "Object is exist in database.\n";
        }
    }
    if (func == err.NOT_ERROR){
        if(bd_api->BackUp() == err.NOT_ERROR){
            mess += "Database is saved.";
        }
        else{
            mess += "Database is not saved.";
        }
        QMessageBox::information(this, "Add object", mess);
        this->close();
    }
    QMessageBox::information(this, "Add object", mess);
}
/**
  Удаление объекта.
  */
void ObjectInfo::on_pushButton_7_clicked(){
    QString mess = "";
    Error err;
    if(bd_api->Del(this->obj) == err.NOT_ERROR){
        mess = "Object is deleted from the database.\n";
    }
    else{
        mess = "Object is not exist in database.\n";
    }
    if(bd_api->BackUp() == err.NOT_ERROR){
        mess += "Database is saved.";
    }
    else{
        mess += "Database is not saved.";
    }
    QMessageBox::information(this, "Delete object", mess);
    this->close();
}
/**
  Сохранение изменений ---
  */
void ObjectInfo::on_pushButton_5_clicked(){
    if(ui->lineEdit->text() == "" ||
       ui->lineEdit_2->text() =="" ||
       ui->lineEdit_3->text() == "")
    {
        QMessageBox::information(this,
                                 "Change object",
                                 "Check the input fields.");
    }
    else{
        obj->ReType(ui->comboBox->currentIndex());
        obj->ReName(ui->lineEdit->text());
        obj->ReImg(ui->lineEdit_2->text());
        obj->Re3DMod(ui->lineEdit_3->text());
        if (obj->getType() > 0 && obj->getType() < 5){
            ((BuildObject*)obj)->x = ui->spinBox->value();
            ((BuildObject*)obj)->y = ui->spinBox_2->value();
            ((BuildObject*)obj)->z = ui->spinBox_3->value();
            if (obj->getType() == 2){
                ((OtherObject*)obj)->linkage = ui->checkBox->checkState();
            }
        }
        Error err;
        QString mess = "";
        if(bd_api->Add(obj) == err.NOT_ERROR){
            mess = "Object is changed.\n";
        }
        else{
            mess = "Object is changed.\n";
        }
        if(bd_api->BackUp() == err.NOT_ERROR){
            mess += "Database is saved.";
        }
        else{
            mess += "Database is not saved.";
        }
        QMessageBox::information(this, "Change object", mess);
        this->close();
    }
}
/**
  Создание копии объекта.
  */
void ObjectInfo::on_pushButton_4_clicked(){
    ObjQuestion* oq = new ObjQuestion(this->bd_api, this->obj);
    oq->show();
}
