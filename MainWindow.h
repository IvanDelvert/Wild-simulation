#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
#include <QSpinBox>
#include <QLayout>
#include <QFormLayout>
#include <QLabel>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QPieSeries>
#include "Animal.h"

#pragma once

using namespace QtCharts;

class MainWindow : public QWidget {

    Q_OBJECT



    public:
        MainWindow(QWidget *parent = 0);

        static const int WIDTH = 1600;
        static const int HIGHT = 800;

    public slots:
        void clickInitParametersSLOT();
        void endSimulationSLOT();
        void downloadCsvFile ();
        void restartSimulation();

    protected:
       void paintEvent(QPaintEvent *);
       void timerEvent(QTimerEvent *);
       void keyPressEvent(QKeyEvent *);


    private:


        QImage rabbitImage;
        QImage wolfImage;
        QImage rabbitPicto;
        QImage wolfPicto;
        QImage downloadPicto;
        QImage backPicto;

        QSpinBox *numberOfRabbit;
        QSpinBox *numberOfWolf;
        QSpinBox *timerEdit;

        QVBoxLayout *mainLayout;
        QFormLayout *formLayout;
        QHBoxLayout *boutonLayout;
        QHBoxLayout *QSpinBoxLayout;
        QHBoxLayout *textSPinBoxLayout;
        QVBoxLayout *titleLayout;

        QHBoxLayout *imageLayout;

        QLabel *deadRabbitNumber;
        QLabel *deadWolfNumber;
        QLabel *newRabbitNumber;
        QLabel *newWolfNumber;

        QPieSeries *donut;
        QPieSlice *wolfSlice;
        QPieSlice *rabbitSlice;
        
        QLineSeries *rabbitSerie;
        QLineSeries *wolfSerie;

        //live Data
        QHBoxLayout *boxTitle;
        QHBoxLayout *boxGraphic;
        QGridLayout *gridLayout;


        //Grid Layout:
        QVBoxLayout *deadRabbitVBOX;
        QVBoxLayout *deadWolfVBOX;
        QVBoxLayout *newRabbitVBOX;
        QVBoxLayout *newWolfVBOX;

        QString stringData;

        //LastWindow
        QVBoxLayout *mainBox;
        QHBoxLayout *buttonDownloadBox;
        QHBoxLayout *buttonBackBox;


        //Button on the simulation page
        QHBoxLayout *stopSimulationBox;


        int timerID;

        int numberRabbit;
        int numberWolf;

        int numberDeadRabbit = 0;
        int numberDeadWolf = 0;
        int numberNewrabbit =0;
        int numberNewWolf =0;

        qreal numberGeneration = -50;

        bool startSimulation;
        bool firstSimulation = true;
        bool clickOnEndSimulation = false;
        bool firstPage = true;

        QVector<Rabbit> rabbitWild;
        QVector<Wolf> wolfWild;


        void loadImage();
        void initParameterWindow();
        void initLiveDataWindow();
        void clearLayout(QLayout *layout);
        void initWildPos();
        void moveWild();
        void eraseOldAnimal();
        void checkCollission();
        bool isOutside(int xAnimal, int yAnimal,int xlimit,int ylimit);
        void manageCollision();
        void rabbitReproduction(int n);
        void wolfReproduction(int n);
        void wolfEatRabbit(QVector<Animal> w);
        int scenarioCollision(QVector<Animal> w);
        void updateLiveData();
        void updateGraphicSerie();
        void endSimulation();
        void displayFinalWindow();
        bool endSimulationFlag();


};





#endif // MAINWINDOW_H
