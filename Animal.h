#ifndef ANIMAL_H
#define ANIMAL_H

class MainWindow;

class Animal {

    public:

        int age;
        int X_pos;
        int Y_pos;
        int angry;
        int sexualMatuity;

        bool alive;

        Animal();

        void setPos(int x, int y);
        int getScenarioPos(int width, int hight,int imageSize);
        void moveAnimal(int width, int hight,int imageSize);


};

class Rabbit : public Animal{

    public:

        Rabbit();

};


#endif // ANIMAL_H
