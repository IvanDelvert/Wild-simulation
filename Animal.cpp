#include "Animal.h"
#include "MainWindow.h"
#include <QRandomGenerator>

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

    switch (scenario)
        {

        case 1:

            break;
        case 2:

            break;
        case 3:

            break;

    }



}


Rabbit::Rabbit() : Animal(){
    alive = true;
    age = 0;
    angry = 0;
    sexualMatuity = 10;
}


