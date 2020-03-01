#include "Animal.h"
#include "MainWindow.h"
#include <QRandomGenerator>
#include <QDebug>

Animal::Animal(){

}


void Animal::setPos(int x, int y){
    X_pos = x;
    Y_pos = y;
}


/*
 *
 *
 * */
int Animal::getScenarioPos(int width, int hight,int imageSize){
    int res = 0;


    if(Y_pos == 0){
        if(X_pos==0){res =1;}
        else if(X_pos == (width - imageSize)){res = 2;}
        else{res =5;}
    }

    else if(X_pos ==(width - imageSize)){
        if(Y_pos==0){res=2;}
        else if(Y_pos ==(hight -imageSize)){res=3;}
        else{res = 6;}
    }

    else if(Y_pos == (hight -imageSize)){
        if(X_pos==(width - imageSize)){res =3;}
        else if(X_pos == 0){res = 4;}
        else{res =7;}
    }

    else if(X_pos == 0){
        if(Y_pos==(hight - imageSize)){res =4;}
        else if(Y_pos == 0){res = 1;}
        else{res =8;}
    }


    return res;
}


void Animal::moveAnimal(int width, int hight,int imageSize){
    int scenario = this->getScenarioPos(width, hight,imageSize);
    int i;
    switch (scenario)
    {

    case 0:
        i = QRandomGenerator::global()->bounded(4);
        if(i == 1){
            X_pos += imageSize;
        }

        else if(i == 2){
            X_pos -= imageSize;
        }

        else if(i == 3){
            Y_pos -= imageSize;
        }

        else{Y_pos += imageSize;}

        break;

    case 1:
        i = QRandomGenerator::global()->bounded(2);
        if(i == 1){
            X_pos += imageSize;
        }

        else{Y_pos += imageSize;}

        break;
    case 2:
        i = QRandomGenerator::global()->bounded(2);
        if(i == 1){
            X_pos -= imageSize;
        }

        else{Y_pos += imageSize;}

        break;
    case 3:
        i = QRandomGenerator::global()->bounded(2);
        if(i == 1){
            X_pos -= imageSize;
        }

        else{Y_pos -= imageSize;}

        break;
    case 4:
        i = QRandomGenerator::global()->bounded(2);
        if(i == 1){
            X_pos += imageSize;
        }

        else{Y_pos -= imageSize;}
        break;

    case 5:
        i = QRandomGenerator::global()->bounded(3);
        if(i == 1){
            X_pos += imageSize;
        }

        else if(i == 2){
            X_pos -= imageSize;
        }

        else{Y_pos += imageSize;}

        break;

    case 6:
        i = QRandomGenerator::global()->bounded(3);
        if(i == 1){
            Y_pos += imageSize;
        }

        else if(i == 2){
            Y_pos -= imageSize;
        }

        else{X_pos -= imageSize;}

        break;


    case 7:
        i = QRandomGenerator::global()->bounded(3);
        if(i == 1){
            X_pos += imageSize;
        }

        else if(i == 2){
            X_pos -= imageSize;
        }

        else{Y_pos -= imageSize;}

        break;

    case 8:
        i = QRandomGenerator::global()->bounded(3);
        if(i == 1){
            Y_pos += imageSize;
        }

        else if(i == 2){
            Y_pos -= imageSize;
        }

        else{X_pos += imageSize;}

        break;
    }
}

void Animal::setAnimalImage(QImage i){
    this->animalImage = i;
}


Rabbit::Rabbit() : Animal(){
    alive = true;
    age = 0;
    angry = 0;
    sexualMatuity = 10;
}

Wolf::Wolf() : Animal(){
    alive = true;
    age = 0;
    angry = 0;
    sexualMatuity = 100;
}



