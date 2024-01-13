#ifndef _CITY_H
#define _CITY_H

#include <iostream>

using namespace std;

class Organism;

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

class City
{
protected:
	Organism *grid[GRID_HEIGHT][GRID_WIDTH]{};

private:
    int humanCount{};
    int zombieCount{};

public:
	City();

	virtual ~City();

	Organism *getOrganism( int x, int y );

	void setOrganism( Organism *organism, int x, int y );

	friend ostream& operator<<( ostream &output, City &city );

    bool hasDiversity() const;

    void humansMove();

    void zombiesMoveEat();

    void humansRecruit();

    void zombieDie();

     void zombieBreed();

    void reset();

    void moveRandomEmpty(Organism *organism, int x, int y);
};

#endif

