#ifndef ANIMAL_H
#define ANIMAL_H


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


};

class Rabbit : public Animal{

    public:

        Rabbit();

};


#endif // ANIMAL_H
