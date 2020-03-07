#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
#include <QSpinBox>
#include <QLayout>
#include <QFormLayout>
#include "Animal.h"



class MainWindow : public QWidget {

    Q_OBJECT



    public:
        MainWindow(QWidget *parent = 0);

        static const int WIDTH = 1600;
        static const int HIGHT = 800;

    public slots:
        void clickInitParameters();

    protected:
       void paintEvent(QPaintEvent *);
       void timerEvent(QTimerEvent *);
       //void keyPressEvent(QKeyEvent *);


    private:


        QImage rabbitImage;
        QImage wolfImage;

        QSpinBox *numberOfRabbit;
        QSpinBox *numberOfWolf;
        QSpinBox *timerEdit;

        QVBoxLayout *mainLayout;
        QFormLayout *formLayout;
        QHBoxLayout *boutonLayout;



        int timerID;

        int numberRabbit;
        int numberWolf;

        bool startSimulation;

        QVector<Rabbit> rabbitWild;
        QVector<Wolf> wolfWild;


        void loadImage();
        void initParameterWindow();
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


};





#endif // MAINWINDOW_H
