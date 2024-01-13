#include "../Headers/Human.h"
#include "../Headers/GameSpecs.h"

//
// Created by kenzi on 2023-12-10.
//
Human::Human() : Organism() {
    this->type = HUMAN_CH;
}

/*Human::Human(City* city, int width, int height) : Organism(city, width, height) {
    this->type = HUMAN_CH;

}*/
// Destructor
Human::~Human() {

}
