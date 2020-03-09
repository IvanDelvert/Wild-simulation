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



QVector <Animal> mapMatrix[160][240];

/*
 * Builder of the main window
 * */
MainWindow::MainWindow(QWidget *parent) : QWidget(parent){

    setFixedSize(WIDTH,HIGHT);
    startSimulation = false;
    initParameterWindow();
    loadImage();
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


/*
 * Delete the layout that initialize the parameters for the simulation
 * */
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

/*
 * SLOT after the click on the "OK" button. Initialisation of the number of species
 * */
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
/*
 *
 *
 *
 * */
void MainWindow::initWildPos(){
    for(int i=0;i<numberRabbit;i++){
        Rabbit r;
        int xRandRabbit = QRandomGenerator::global()->bounded(240);
        int yRandRabbit = QRandomGenerator::global()->bounded(160);
        r.setPos(xRandRabbit*5,yRandRabbit*5);
        r.setAnimalImage(rabbitImage);
        rabbitWild.push_back(r);
    }


    for(int i=0;i<numberWolf;i++){
        Wolf w;
        int xRandWolf = QRandomGenerator::global()->bounded(240);
        int yRandWolf = QRandomGenerator::global()->bounded(160);
        w.setPos(xRandWolf*5,yRandWolf*5);
        w.setAnimalImage(wolfImage);
        wolfWild.push_back(w);
    }


}

/*
 * Method that add age for each animals and erase dead animals from differents lists
 * */
void MainWindow::eraseOldAnimal(){
    for(int i=0;i<rabbitWild.size();i++){
        if(rabbitWild[i].age > rabbitWild[i].lifeExpectancy){
            rabbitWild.erase(rabbitWild.begin()+i);
        }
        else{
            rabbitWild[i].age++;
        }
    }   
    for(int i=0;i<wolfWild.size();i++){
        if(wolfWild[i].age > wolfWild[i].lifeExpectancy){
            wolfWild.erase(wolfWild.begin()+i);
        }
        else{
            wolfWild[i].age++;
        }
    }
}



/*
 * Calculation of the new position of the wolfs and the rabbits
 *
 * */
void MainWindow::moveWild(){
    int n = rabbitWild.size();

    for(int i=0;i<n;i++){
        rabbitWild[i].moveAnimal(WIDTH-400,HIGHT,5);
        mapMatrix[(rabbitWild[i].Y_pos)/5][(rabbitWild[i].X_pos)/5].push_back(rabbitWild[i]);
    }


    int r = wolfWild.size();
    for(int i=0;i<r;i++){
        wolfWild[i].moveAnimal(WIDTH-400,HIGHT,5);
        mapMatrix[(wolfWild[i].Y_pos)/5][(wolfWild[i].X_pos)/5].push_back(wolfWild[i]);
    }
}

/*
 * Creattion of 'n' new rabbit
 *
 * */
void MainWindow::rabbitReproduction(int n){
    for(int k=1;k<=n;k++){
        Rabbit r;
        int xRandRabbit = QRandomGenerator::global()->bounded(240);
        int yRandRabbit = QRandomGenerator::global()->bounded(160);
        r.setPos(xRandRabbit*5,yRandRabbit*5);
        r.setAnimalImage(rabbitImage);
        rabbitWild.push_back(r);
    }
}

/*
 * Creattion of 'n' new wolf
 *
 * */
void MainWindow::wolfReproduction(int n){
    for(int k=1;k<=n;k++){
        Wolf w;
        int xRandWolf = QRandomGenerator::global()->bounded(240);
        int yRandWolf = QRandomGenerator::global()->bounded(160);
        w.setPos(xRandWolf*5,yRandWolf*5);
        w.setAnimalImage(wolfImage);
        wolfWild.push_back(w);
    }

}


/*
 * In a list w of animals (rabbit + wolf), check the number of rabbit to remove
 * Remove this number of rabbit from 'rabbitWild' vector
 *
 * */
void MainWindow::wolfEatRabbit(QVector<Animal> w){
    int wolf =0;
    int rabbit =0;
    int currentKill =0;
    QVector<Animal>::iterator it;
    for(it = w.begin();it != w.end();it++){
        if(it->type ==0){rabbit++;}
        else{wolf++;}
    }

    QVector<Rabbit>::iterator itt;
    int numberOfKill = qMin(rabbit,wolf);
    if(numberOfKill > 1){qInfo()<<"Number of kill: "<<numberOfKill<<endl;}
    int i=1;
    while(i<=numberOfKill){
        for(it = w.begin();it != w.end();it++){
            if(it->type == 0){
                for(itt = rabbitWild.begin();itt != rabbitWild.end();){
                    if(itt->X_pos == it->X_pos && itt->Y_pos == it->Y_pos){
                        itt = rabbitWild.erase(rabbitWild.begin()+std::distance(rabbitWild.begin(),itt));
                        i++;
                    }
                    else{
                        itt++;
                    }
                }

            }
        }
    }

}

/*
 * Determination of the type of collision:
 *  return 0 ---> Collision between rabbits
 *  return 1 ---> Collision between wolfs
 *  return 2 ---> Collision between rabbits and wolfs
 * */
int MainWindow::scenarioCollision(QVector<Animal> w){
    int count =0;
     QVector<Animal>::iterator it;
     for(it = w.begin();it != w.end();it++){
          count += it->type;
      }
     if(count == 0){return 0;}
     else if(count == w.size()){return 1;}
     else{return 2;}
}


/*
* Manage the collision thanks to the 'matrixMap'
*
 * */
void MainWindow::manageCollision(){
    bool onlyRabbit;
    for(int i=0;i<160;i++){
        for(int j=0;j<240;j++){
            if(mapMatrix[i][j].size() !=0){
                if(mapMatrix[i][j].size()== 1){
                    mapMatrix[i][j].clear();
                }
                else{

                    int cas = scenarioCollision(mapMatrix[i][j]);
                    //Case just Rabbit
                    if(cas == 0){
                        // qInfo()<<"work"<<endl;
                        int A = (mapMatrix[i][j].size())/2;
                        rabbitReproduction(A);
                        mapMatrix[i][j].clear();
                    }
                    else if(cas == 1){
                        int A = (mapMatrix[i][j].size())/2;
                        wolfReproduction(A);
                        mapMatrix[i][j].clear();
                    }

                    else{
                        //  qInfo()<<"Before eat rabbit"<<endl;
                        wolfEatRabbit(mapMatrix[i][j]);
                        // qInfo()<<"After eat rabbit"<<endl;
                        mapMatrix[i][j].clear();
                    }


                }
            }
        }

    }

}

/*
 * Event that perform the display of each species
 *
 * */
void MainWindow::paintEvent(QPaintEvent *e){

    Q_UNUSED(e);
    QPainter qp(this);
    qp.setPen(Qt::white);

    if(startSimulation){
        qp.drawLine(1200,0,1200,800);
        int n = rabbitWild.size();
        for(int i=0;i<n;i++){
            qp.drawImage(rabbitWild[i].X_pos,rabbitWild[i].Y_pos,rabbitWild[i].animalImage);
        }
        int r = wolfWild.size();
        for(int i=0;i<r;i++){
            qp.drawImage(wolfWild[i].X_pos,wolfWild[i].Y_pos,wolfWild[i].animalImage);
        }
    }

}

/*
 * Main loop for the simulation
 *
 * */

void MainWindow::timerEvent(QTimerEvent *e){

    Q_UNUSED(e);

    eraseOldAnimal();
    moveWild();
    manageCollision();
    repaint();

    if(rabbitWild.size() + wolfWild.size() > 500000){killTimer(timerID);}
    qInfo()<<rabbitWild.size()<<endl;


}
