#include <QPainter>
#include <QTime>
#include<QDebug>
#include<QLabel>
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QSpinBox>
#include <QRandomGenerator>
#include "MainWindow.h"
#include "Animal.h"



MainWindow::MainWindow(QWidget *parent) : QWidget(parent){

    setFixedSize(WIDTH,HIGHT);
    startSimulation = false;

    initParameterWindow();


    loadImage();

    qInfo()<<numberRabbit<<endl;

}


/*
 * Load the PNG image of the rabbit and the wolf
 * */
void MainWindow::loadImage(){

    rabbitImage.load("c:\\Users\\Ivan\\wildSimulation\\img\\rabbit.png");
    wolfImage.load("c:\\Users\\Ivan\\wildSimulation\\img\\wolf.png");

}


void MainWindow::initParameterWindow(){

         numberOfRabbit = new QSpinBox;
         numberOfWolf = new QSpinBox;
         timerEdit = new QSpinBox;

        numberOfRabbit->setRange(0,30000);
        numberOfWolf->setRange(0,30000);
        timerEdit->setRange(50,5000);


        formLayout = new QFormLayout;
        formLayout->addRow("Number of rabbit: " ,numberOfRabbit);
        formLayout->addRow("Number of wolf: " ,numberOfWolf);
        formLayout->addRow("Time simulation (ms): " ,timerEdit);


        boutonLayout = new QHBoxLayout;
        QPushButton *validate = new QPushButton("OK");
        QPushButton *quit = new QPushButton("Quit");

        QWidget::connect(quit,SIGNAL(clicked()),this,SLOT(quit()));
        QWidget::connect(validate,SIGNAL(clicked()),this,SLOT(clickInitParameters()));

        boutonLayout->addWidget(quit);
        boutonLayout->addWidget(validate);

        mainLayout = new QVBoxLayout;
        mainLayout->setContentsMargins(650,300,650,400);
        mainLayout->addLayout(formLayout);
        mainLayout->addLayout(boutonLayout);



        this->setLayout(mainLayout);

}



void MainWindow::clearLayout(QLayout *layout){
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}




void MainWindow::clickInitParameters(){

    numberRabbit = numberOfRabbit->value();
    numberWolf = numberOfWolf->value();
    int t = timerEdit->value();
    clearLayout(formLayout);
    clearLayout(boutonLayout);


   setStyleSheet("background-color:black;");

   initWildPos();
   startSimulation = true;
   timerID = startTimer(t);

   qInfo()<<"Rabbit "<<numberRabbit<<"Wolf: "<<numberWolf<<endl;


}

//TODO improve this method
//TODO Change name method
//IDEA May be the QImage by animal is not a not idea?
void MainWindow::initWildPos(){
    for(int i=0;i<numberRabbit;i++){
        Rabbit r;
        r.setPos((QRandomGenerator::global()->bounded(240))*5,(QRandomGenerator::global()->bounded(160))*5);
        r.setAnimalImage(rabbitImage);
        wild.append(r);
    }

    for(int i=0;i<numberWolf;i++){
        Wolf w;
        w.setPos((QRandomGenerator::global()->bounded(240))*5,(QRandomGenerator::global()->bounded(160))*5);
        w.setAnimalImage(wolfImage);
        wild.append(w);
    }


}

void MainWindow::moveWild(){

    int n = wild.size();
    for(int i=0;i<n;i++){
        wild[i].moveAnimal(WIDTH-400,HIGHT,5);
    }
}


/*
 *
 *
 * */
void MainWindow::paintEvent(QPaintEvent *e){

    Q_UNUSED(e);



    QPainter qp(this);
    qp.setPen(Qt::white);

    if(startSimulation){

        qp.drawLine(1200,0,1200,800);
        int n = wild.size();
        for(int i=0;i<n;i++){
            qp.drawImage(wild[i].X_pos,wild[i].Y_pos,wild[i].animalImage);
        }
    }
}

/*
 * Loop for the modelization of the population dynamics
 *
 * */

void MainWindow::timerEvent(QTimerEvent *e){

    Q_UNUSED(e);

    moveWild();
    repaint();


}
