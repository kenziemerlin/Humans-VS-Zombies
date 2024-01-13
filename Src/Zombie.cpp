//
// Created by kenzi on 2023-12-10.
//
#include "../Headers/GameSpecs.h"
#include "../Headers/Zombie.h"
#include "../Headers/City.h"

Zombie::Zombie() : Organism() {
    this->type = ZOMBIE_CH;
    this->steps = 0;
    this->eat = 0;
}

/*Zombie::Zombie(City* city, int width, int height) : Organism(city, width, height) {
    this->type = ZOMBIE_CH;
    this->steps = 0;
    this->eat = 0;

}*/

// Destructor
Zombie::~Zombie() {

}
