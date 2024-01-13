#ifndef _Organism_H
#define _Organism_H

#include <iostream>

using namespace std;

class City;

class Organism
{
protected:

    int steps = 0;
    int eat = 0;
	bool moved;
    char type = 'D'; //D for default


public:
	Organism();

	virtual ~Organism();

    char getType();

    void addStep();

    int getSteps();

    void addNoEat();

    int getNoEat();

    void resetNoEat();

    void resetSteps();

	friend ostream& operator<<( ostream &output, Organism *organism );

    void setMoved(bool b);

    bool hasMoved();
};

#endif
