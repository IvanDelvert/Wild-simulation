#ifndef ANIMAL_H
#define ANIMAL_H

#include<QImage>
class MainWindow;

class Animal {

    public:

        int age;
        int X_pos;
        int Y_pos;
        int angry;
        int sexualMatuity;
        QImage animalImage;
        bool alive;

        Animal();

        void setPos(int x, int y);
        int getScenarioPos(int width, int hight,int imageSize);
        void moveAnimal(int width, int hight,int imageSize);
        void setAnimalImage(QImage i);



};

class Rabbit : public Animal{

    public:

        Rabbit();


};

class Wolf : public Animal{

    public:

        Wolf();

};



#endif // ANIMAL_H
