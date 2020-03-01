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

        int WIDTH = 1600;
        int HIGHT = 800;

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
        void eraseDeadAnimal();


};





#endif // MAINWINDOW_H
