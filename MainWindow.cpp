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
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QPieSeries>
#include "MainWindow.h"
#include "Animal.h"

using namespace QtCharts;



QVector <Animal> mapMatrix[160][240];

/*
 * Builder of the main window
 * */
MainWindow::MainWindow(QWidget *parent) : QWidget(parent){

    setFixedSize(WIDTH,HIGHT);
    startSimulation = false;
    loadImage();
    initParameterWindow();

}


/*
 * Load the PNG image of the rabbit and the wolf
 * */
void MainWindow::loadImage(){

    rabbitImage.load("c:\\Users\\Ivan\\wildSimulation\\img\\rabbit.png");
    wolfImage.load("c:\\Users\\Ivan\\wildSimulation\\img\\wolf.png");
    wolfPicto.load("c:\\Users\\Ivan\\wildSimulation\\img\\wolf_picto.png");
    rabbitPicto.load("c:\\Users\\Ivan\\wildSimulation\\img\\rabbit_picto.png");

}


void MainWindow::initParameterWindow(){

        setStyleSheet("background-color:#112233;");
        QFont spinBoxLabelFont("Tahoma", 11);
        QFont titleAppFont("Tahoma", 40,QFont::Bold);

        titleLayout = new QVBoxLayout;
        QLabel *titleText = new QLabel;
        titleText->setText("Population dynamics simulation");
        titleText->setFont(titleAppFont);
        titleText->setAlignment(Qt::AlignHCenter);
        titleText->setStyleSheet(QStringLiteral("QLabel{color: rgb(255,255,255);}"));
        titleLayout->addWidget(titleText);

        numberOfRabbit = new QSpinBox;
        numberOfRabbit->setAlignment(Qt::AlignCenter);
        numberOfRabbit->setStyleSheet("QSpinBox{"
                                      "background-color: #ffffff;"
                                      "font-weight: bold;"
                                      "}"


                                                        );

        numberOfWolf = new QSpinBox;
        numberOfWolf->setAlignment(Qt::AlignCenter);
        numberOfWolf->setStyleSheet("QSpinBox{"
                                    "background-color: #ffffff;"
                                    "font-weight: bold;"
                                    "}"


                                                      );
        timerEdit = new QSpinBox;

        numberOfRabbit->setRange(0,30000);
        numberOfWolf->setRange(0,30000);
        timerEdit->setRange(50,6000);

        imageLayout = new QHBoxLayout;
        QLabel *imgRabbitPicto = new QLabel;
        imgRabbitPicto->setPixmap(QPixmap::fromImage(rabbitPicto).scaled(295,200,Qt::KeepAspectRatio));
        QLabel *imgWolfPicto = new QLabel;
        imgWolfPicto->setPixmap(QPixmap::fromImage(wolfPicto));

        imageLayout->addWidget(imgRabbitPicto);
        imageLayout->addWidget(imgWolfPicto);
        imageLayout->setContentsMargins(150,0,150,0);

        QSpinBoxLayout = new QHBoxLayout;
        QSpinBoxLayout->addWidget(numberOfRabbit);
        QSpinBoxLayout->addWidget(numberOfWolf);
        QSpinBoxLayout->setContentsMargins(150,0,150,0);

        textSPinBoxLayout = new QHBoxLayout;
        textSPinBoxLayout->setContentsMargins(150,0,150,0);
            QLabel *rabbitTextSpinBox = new QLabel;
            rabbitTextSpinBox->setText("Number of rabbit");
            rabbitTextSpinBox->setFont(spinBoxLabelFont);
            rabbitTextSpinBox->setStyleSheet(QStringLiteral("QLabel{color: rgb(255,255,255);}"));
            rabbitTextSpinBox->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
            //rabbitTextSpinBox->setStyleSheet("background-color:#112233;");
            QLabel *wolfTextSpinBox = new QLabel;
            wolfTextSpinBox->setText("Number of wolf");
            wolfTextSpinBox->setFont(spinBoxLabelFont);
            wolfTextSpinBox->setStyleSheet(QStringLiteral("QLabel{color: rgb(255,255,255);}"));
            wolfTextSpinBox->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
            textSPinBoxLayout->addWidget(rabbitTextSpinBox);
            textSPinBoxLayout->addWidget(wolfTextSpinBox);

        boutonLayout = new QHBoxLayout;
        QPushButton *validate = new QPushButton("OK");
        validate->setStyleSheet("QPushButton{"
                                    "background-color: #fdfdfd;"
                                    "border-style: outset;"
                                    "border-width: 1px;"
                                    "border-radius: 10px;"
                                    "border-color: black;"
                                    "font: 12px;"
                                    "padding: 6px;}"
                                "QPushButton:hover{"
                                    "background-color: #fcfcfc;"
                                    "border-style: outset;"
                                    "border-width: 1px;"
                                    "border-radius: 10px;"
                                    "border-color: black;"
                                    "font: 12px;"
                                    "padding: 6px;}"
                                );


        QPushButton *quit = new QPushButton("Quit");
        quit->setStyleSheet("QPushButton{"
                            "background-color: #fdfdfd;"
                            "border-style: outset;"
                            "border-width: 1px;"
                            "border-radius: 10px;"
                            "border-color: black;"
                            "font: 12px;"
                            "padding: 6px;}"
                        "QPushButton:hover{"
                            "background-color: #fcfcfc;"
                            "border-style: outset;"
                            "border-width: 1px;"
                            "border-radius: 10px;"
                            "border-color: black;"
                            "font: 12px;"
                            "padding: 6px;}"
                        );


        QWidget::connect(quit,SIGNAL(clicked()),this,SLOT(quit()));
        QWidget::connect(validate,SIGNAL(clicked()),this,SLOT(clickInitParameters()));

        boutonLayout->addWidget(quit);
        boutonLayout->addWidget(validate);
        boutonLayout->setContentsMargins(150,0,150,0);

        mainLayout = new QVBoxLayout;
        mainLayout->setContentsMargins(350,5,350,150);
        mainLayout->addLayout(titleLayout);
        mainLayout->addLayout(imageLayout);
        mainLayout->addLayout(QSpinBoxLayout);
        mainLayout->addLayout(textSPinBoxLayout);
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
    clearLayout(titleLayout);
    clearLayout(imageLayout);
    clearLayout(QSpinBoxLayout);
    clearLayout(textSPinBoxLayout);
    clearLayout(boutonLayout);



   setStyleSheet("background-color:#112233;");
   initLiveDataWindow();


   initWildPos();
   startSimulation = true;
   timerID = startTimer(t);

}


//TODO UPDATE THE NUMBER OF DEAD RABBIT WITH NATURAL DEATH
void MainWindow::initLiveDataWindow(){
    mainLayout->setContentsMargins(1202,5,0,0);

    QFont titleFont("MS Sans Serif", 14, QFont::Bold);
    QFont dataTextFont("Tahoma", 10);
    QFont dataNumberFont("Tahoma", 22,QFont::Bold);


     QLabel *label = new QLabel();
     label->setText("Live data");
     label->setAlignment(Qt::AlignHCenter);
     label->setFont(titleFont);
     label->setStyleSheet(QStringLiteral("QLabel{color: rgb(255,255,255);}"));
     label->setContentsMargins(10,0,0,0);

     QChartView *chartView = new QChartView;
     chartView->setRenderHint(QPainter::Antialiasing);
     QChart *chart = chartView->chart();
     chart->legend()->setVisible(false);
     chart->setTitle("Proportion rabbit VS wolf");
     chart->setAnimationOptions(QChart::AllAnimations);
     chart->setBackgroundVisible(false);

     donut = new QPieSeries;
     qInfo()<<numberRabbit<<endl;
     qreal wolfPourcentage = (double(numberRabbit) / (numberRabbit + numberWolf))*100;
     qreal rabbitPourcentage = (double(numberWolf) / (numberRabbit + numberWolf))*100;
     wolfSlice = new QPieSlice(QString("%1").arg(wolfPourcentage) +"%", wolfPourcentage);
     rabbitSlice = new QPieSlice(QString("%1").arg(rabbitPourcentage) +"%", rabbitPourcentage);
     wolfSlice->setLabelVisible(true);
     wolfSlice->setLabelColor(Qt::white);
     wolfSlice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
     wolfSlice->setColor(Qt::red);
     rabbitSlice->setLabelVisible(true);
     rabbitSlice->setLabelColor(Qt::white);
     rabbitSlice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
     rabbitSlice->setColor(QColor(65,205,82));

     donut->append(wolfSlice);
     donut->append(rabbitSlice);

     donut->setHoleSize(0);
     donut->setPieSize(0.95);
    //SET THE SIZE


    chartView->chart()->addSeries(donut);

     //TODO A CONNECTION WITH THE TIMER EVENT


     //Title
     QHBoxLayout *boxTitle = new QHBoxLayout;
     boxTitle->addWidget(label);

     //Graphic
     QHBoxLayout *boxGraphic = new QHBoxLayout;
     boxGraphic->addWidget(chartView);

     //Number
     QGridLayout *gridLayout = new QGridLayout;
    // gridLayout->setSpacing(5);

     QVBoxLayout *deadRabbitVBOX = new QVBoxLayout;
         QLabel *deadRabbitText = new QLabel();
            deadRabbitText->setText("Dead rabbit");
            deadRabbitText->setStyleSheet(QStringLiteral("QLabel{color: rgb(255,255,255);}"));
            //deadRabbitText->setStyleSheet("border: 1px solid red");
            deadRabbitText->setAlignment(Qt::AlignHCenter);
            deadRabbitText->setFont(dataTextFont);
            deadRabbitNumber = new QLabel();
            deadRabbitNumber->setText("0");
            deadRabbitNumber->setStyleSheet(QStringLiteral("QLabel{color: rgb(255,255,255);}"));
            //deadWolfNumber->setStyleSheet("border: 1px solid red");
            deadRabbitNumber->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
            deadRabbitNumber->setFont(dataNumberFont);
      deadRabbitVBOX->addWidget(deadRabbitNumber);
      deadRabbitVBOX->addWidget(deadRabbitText);

      QVBoxLayout *deadWolfVBOX = new QVBoxLayout;
          QLabel *deadWolfText = new QLabel();
             deadWolfText->setText("Dead wolf");
             deadWolfText->setStyleSheet("QLabel{color: rgb(255,255,255);}");
             //deadWolfText->setStyleSheet("border: 1px solid red");
             deadWolfText->setAlignment(Qt::AlignHCenter);
             deadWolfText->setFont(dataTextFont);
             deadWolfNumber = new QLabel();
             deadWolfNumber->setText("0");
             deadWolfNumber->setStyleSheet(QStringLiteral("QLabel{color: rgb(255,255,255);}"));
             deadWolfNumber->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
             deadWolfNumber->setFont(dataNumberFont);
             //deadWolfNumber->setStyleSheet("border: 1px solid red");
       deadWolfVBOX->addWidget(deadWolfNumber);
       deadWolfVBOX->addWidget(deadWolfText);

       QVBoxLayout *newRabbitVBOX = new QVBoxLayout;
           QLabel *newRabbitText = new QLabel();
              newRabbitText->setText("Newborn rabbit");
              newRabbitText->setStyleSheet(QStringLiteral("QLabel{color: rgb(255,255,255);}"));
              newRabbitText->setAlignment(Qt::AlignHCenter);
              newRabbitText->setFont(dataTextFont);
              newRabbitNumber = new QLabel();
              newRabbitNumber->setText("0");
              newRabbitNumber->setStyleSheet(QStringLiteral("QLabel{color: rgb(255,255,255);}"));
              newRabbitNumber->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
              newRabbitNumber->setFont(dataNumberFont);
        newRabbitVBOX->addWidget(newRabbitNumber);
        newRabbitVBOX->addWidget(newRabbitText);


        QVBoxLayout *newWolfVBOX = new QVBoxLayout;
            QLabel *newWolfText = new QLabel();
               newWolfText->setText("Newborn wolves");
               newWolfText->setStyleSheet(QStringLiteral("QLabel{color: rgb(255,255,255);}"));
               newWolfText->setAlignment(Qt::AlignHCenter);
               newWolfText->setFont(dataTextFont);
               newWolfNumber = new QLabel();
               newWolfNumber->setText("0");
               newWolfNumber->setStyleSheet(QStringLiteral("QLabel{color: rgb(255,255,255);}"));
               newWolfNumber->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
               newWolfNumber->setFont(dataNumberFont);
         newWolfVBOX->addWidget(newWolfNumber);
         newWolfVBOX->addWidget(newWolfText);


      gridLayout->addLayout(deadRabbitVBOX,0,0,1,1);
      gridLayout->addLayout(deadWolfVBOX,0,1,1,1);
      gridLayout->addLayout(newRabbitVBOX,1,0,1,1);
      gridLayout->addLayout(newWolfVBOX,1,1,1,1);
     //QHBoxLayout *deadWolf = new QHBoxLayout;


     mainLayout->addLayout(boxTitle);
     mainLayout->addLayout(boxGraphic);
     mainLayout->addLayout(gridLayout);




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
            numberDeadRabbit++;
        }
        else{
            rabbitWild[i].age++;
        }
    }   
    for(int i=0;i<wolfWild.size();i++){
        if(wolfWild[i].age > wolfWild[i].lifeExpectancy){
            wolfWild.erase(wolfWild.begin()+i);
            numberDeadWolf++;

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
        //increment variable for live data
        numberNewrabbit++;
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
        //increment variable for live data
        numberNewWolf++;
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
    numberDeadRabbit += numberOfKill;
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

void MainWindow::updateLiveData(){
    deadRabbitNumber->setText(QString::number(numberDeadRabbit));
    deadWolfNumber->setText(QString::number(numberDeadWolf));
    newWolfNumber->setText(QString::number(numberNewWolf));
    newRabbitNumber->setText(QString::number(numberNewrabbit));

    int nR = rabbitWild.size();
    int nW = wolfWild.size();

    qreal wolfPourcentage = (double(nW) / (nR + nW))*100;
    qreal rabbitPourcentage = (double(nR) / (nR + nW))*100;
    wolfSlice->setLabel(QString("%1").arg(wolfPourcentage) +"%");
    wolfSlice->setValue(wolfPourcentage);
    rabbitSlice->setLabel(QString("%1").arg(rabbitPourcentage) +"%");
    rabbitSlice->setValue(rabbitPourcentage);

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
    updateLiveData();
    repaint();

    if(rabbitWild.size() + wolfWild.size() > 500000){killTimer(timerID);}
    //qInfo()<<rabbitWild.size()<<endl;


}
