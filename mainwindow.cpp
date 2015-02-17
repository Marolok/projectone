#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    bd_api = new BD_API();
    me = new MapEditor();
    ui->centralWidget->installEventFilter(this);
    H = 32;

    activ_x = -1;
    activ_y = -1;

    koord_x = 0;
    koord_y = 0;

    this->endActiveObj = "";
    this->endActiveObjParent = "";

    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(false);

    ui->action_4->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    //this->bd_api->~BD_API();
    //this->me->~MapEditor();
}

QString MainWindow::backError(){
    return (bd_api->backError()+"\n"+me->backError());
}
/**
  Перерисовка окна.
  */
void MainWindow::paintEvent(QPaintEvent *){
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

    for(int i=0; i<bd_api->getCountObject(); i++){
        Objects* obj = bd_api->ReturnObjectNumb(i);
        QStandardItem* item = new QStandardItem(obj->getName());
        QIcon icon;
        icon.addFile(obj->getImg());
        item->setIcon(icon);
        switch (obj->getType()){
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

    QPainter painter(this);

    int w = this->geometry().width()-
            ui->frame->geometry().width()-90;
    int h = this->geometry().height()-100;

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.drawRect(40,60,w,h);

    //Сетка
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    int k1 = 0;
    int k2 = 0;
    for(int i=60; i<=h+60;){
        painter.drawLine(40,i,w+40,i);
        i += H;
        k1++;
    }
    for(int i=40; i<=w+40;){
        painter.drawLine(i,60,i,h+60);
        i += H;
        k2++;
    }

    //Вывод карты
    if(this->me->isActivMap()){
        for(int i=0; i<this->me->getCountObjects(); i++){
            BuildObject* bo =(BuildObject*) this->me->ReturnObject(i);
            if(bo->x < k2+koord_x && bo->y < k1+koord_y &&
                    bo->x >= koord_x && bo->y >= koord_y){
                QImage img(bo->getImg());
                //QPainter painter(this);
                int x = (bo->x-koord_x)*H+40;
                int y = (bo->y-koord_y)*H+60;
                //qDebug() << "PRINT IMG " << x << " " << y << "\n";
                painter.drawImage(x+1,y+1,img.scaledToHeight(H-2));
            }
        }
    }

    //Замулевываем огрехи
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(40,60,w,h);

    if(activ_x != -1 && activ_y != -1){
        int x = activ_x*H+40;
        int y = activ_y*H+60;
        painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine));
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(x,y,H,H);
    }

    painter.setPen(Qt::NoPen);
    QColor color(240,240,240);
    painter.setBrush(color);
    painter.drawRect(w+41,50,40,h+20);

    painter.drawRect(40,h+61,w+41,40);

    //Информация
    std::stringstream out;
    out << "[" << koord_x << ":" << koord_y <<"]";
    ui->label_3->setText(QString::fromStdString(out.str()));

}
/**
 * Отслеживает все взаимодействия с формой.
 * @brief eventFilter
 * @param obj
 * @param event
 * @return
 */
bool MainWindow::eventFilter(QObject * obj, QEvent *event){
    // Получение и вывод координат нажатия кнопкой мыши.
    if ((event->type() == QEvent::MouseButtonPress)){
        int x1, x2, y1, y2;
        this->window()->geometry().getCoords(&x1,&y1,&x2,&y2);
        int px = this->cursor().pos().x()-x1-40;
        int py = this->cursor().pos().y()-y1-65;
        int w = this->geometry().width()-
                ui->frame->geometry().width()-90;
        int h = this->geometry().height()-100;

        if(px < w && py < h && px > 0 && py > 0){
            std::stringstream out;
            out << px/H << " " << py/H;
            ui->label_2->setText(QString::fromStdString(out.str()));
            if(px/H != activ_x || py/H != activ_y){
                activ_x = px/H;
                activ_y = py/H;
            }
            else{
                activ_x = -1;
                activ_y = -1;
            }
            this->repaint();
        }

        //Добавеление объекта на поле
        if(ui->label->text() != "Active object"){
            TypeConst types;
            qDebug() << "TO ADD OBJECT TO MAP " << this->endActiveObj
                     << " " << this->endActiveObjParent << "\n";
            this->me->AddObj(px/H, py/H, 0, this->endActiveObj,
                            types.types.key(this->endActiveObjParent));
            this->repaint();
        }
        //-------------------------
    }
    //-------------------------

}
/**
  Выход
  */
void MainWindow::on_action_triggered(){
    this->close();
}

void MainWindow::mouseMoveEvent(QMouseEvent* pe){
//НАХЕРА????
}
/**
  Загрузка карты.
  */
void MainWindow::on_action_2_triggered(){

    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open file...")
                                                    ,"./map/",
                                                    tr("KMC Map (*.txt)"));
    int pos=0;
    for(int i=0; i!=filename.length();i++){
        if(filename[i] == '/') pos = i;
    }
    //std::cout << "\n--------" << filename->toStdString() << "\n";
    filename.replace(0,pos+1,"");

    me->SelectMap(filename);
    this->repaint();

    if(me->isActivMap()){
        ui->action_2->setEnabled(false);
        ui->action_4->setEnabled(true);
    }
}
/**
  Вывод информации об объекте.
  */
void MainWindow::on_treeView_activated(const QModelIndex &index){
    qDebug() << index.data().toString() << index.row() <<index.row();
    TypeConst types;
    this->endActiveObj = index.data().toString();
    this->endActiveObjParent = index.parent().data().toString();
    if (!types.itIsType(index.data().toString())){
        ObjectInfo* objInfo = new ObjectInfo(
                    this->bd_api,
                    index.data().toString(),
                    index.parent().data().toString());
        objInfo->show();
    }
}
/**
  Активация объекта.
  */
void MainWindow::on_treeView_clicked(const QModelIndex &index){
    this->endActiveObj = index.data().toString();
    this->endActiveObjParent = index.parent().data().toString();
    ui->label->setText(index.parent().data().toString() + "|" +
            index.data().toString());
}
/**
  Добавление нового объетка.
  */
void MainWindow::on_pushButton_5_clicked(){
    ObjectInfo* objInfo = new ObjectInfo(this->bd_api);
    objInfo->show();
}
/**
  Вывод информации об объекте.
  */
void MainWindow::on_treeView_doubleClicked(const QModelIndex &index){
    this->on_treeView_activated(index);
}
/**
  Настройки
  */
void MainWindow::on_action_3_triggered(){
    //Использовать вектор строк.
}

void MainWindow::on_action_4_triggered(){
    me->CloseMap();
    me->clearMap();
    if(!me->isActivMap()){
        ui->action_2->setEnabled(true);
        ui->action_4->setEnabled(false);
    }
    this->repaint();
}

void MainWindow::on_action_5_triggered(){    
    NewMap* nm = new NewMap(this->me);
    nm->show();
}

void MainWindow::on_pushButton_2_clicked(){
    //<---
    koord_x -= 1;
    this->repaint();
}

void MainWindow::on_pushButton_3_clicked(){
    //^
    koord_y -= 1;
    this->repaint();
}

void MainWindow::on_pushButton_clicked(){
    // --->
    koord_x += 1;
    this->repaint();
}

void MainWindow::on_pushButton_4_clicked(){
    // down
    koord_y += 1;
    this->repaint();
}
