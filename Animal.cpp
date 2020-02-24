#include "Animal.h"


Animal::Animal(){

}


Rabbit::Rabbit() : Animal(){
    alive = true;
    age = 0;
    angry = 0;
    sexualMatuity = 10;
}

void Animal::setPos(int x, int y){
    X_pos = x;
    Y_pos = y;
}

