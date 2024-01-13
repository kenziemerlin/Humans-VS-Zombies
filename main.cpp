//
// Created by W0068332 on 11/21/2021.
//
//Example main.cpp
//This supposes that city->step() calls the move method of each organism in the city
//in a single pass causing each to perform all tasks that it can.

#include <iostream>
#include <thread>
#include "Headers/City.h"
#include "Headers/GameSpecs.h"
#include "Headers/Human.h"
#include "Headers/Zombie.h"



using namespace std;

void ClearScreen()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main() {
        srand(time(nullptr));
        City *city = new City();

        for (int i = 0; i < HUMAN_STARTCOUNT; ++i) {
            Human *human = new Human;
            int x = 0;
            int y = 0;
            while (true) {
                x = rand() % GRID_WIDTH;
                y = rand() % GRID_HEIGHT;

                if (city->getOrganism(x, y) == nullptr){
                    break;
                }
            }
            city->setOrganism(human,x ,y);

        }

        for (int i = 0; i < ZOMBIE_STARTCOUNT; ++i) {
            Zombie *zombie = new Zombie;
            int x = 0;
            int y = 0;
            while (true) {
                x = rand() % GRID_WIDTH;
                y = rand() % GRID_HEIGHT;

                if (city->getOrganism(x, y) == nullptr){
                    break;
                }
            }
            city->setOrganism(zombie,x ,y);

        }
        cout << *city;
        // Set the interval in milliseconds
        chrono::milliseconds interval(100);

        int generation = 1;
        while (city->hasDiversity() && generation <= ITERATIONS) {

            auto start = chrono::steady_clock::now();

            // Perform the simulation step
            ClearScreen();
            cout << "GENERATION " << generation << endl;
            city->humansMove();
            city->zombiesMoveEat();
            city->humansRecruit();
            city->zombieDie();
            city->zombieBreed();
            city->reset();
            cout << *city;

            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);

            // Sleep for the remaining time in the interval
            if (elapsed < interval) {
                this_thread::sleep_for(interval - elapsed);
            }
            generation++;

        }
        // Cleanup
        delete city;

}//end main

