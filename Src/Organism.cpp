#include "../Headers/Organism.h"

//
// Created by kenzi on 2023-12-10.
//
Organism::Organism() : steps(0) {

}

Organism::~Organism(){

}

char Organism::getType(){
    if (this == nullptr) {
        // Handle the case where 'this' is null
        return '\0'; // or some other default value
    }
    return this->type;
}

void Organism::addStep() {
    steps++;
}

int Organism::getSteps() {
    return steps;
}

void Organism::addNoEat() {
    eat++;
}

int Organism::getNoEat() {
    return eat;
}

void Organism::resetNoEat() {
    eat = 0;
}

void Organism::resetSteps() {
    steps = 0;
}
std::ostream& operator<<(std::ostream& output, Organism* organism) {
    // Implementation for printing Organism details
    return output;
}

void Organism::setMoved(bool b) {
    moved = b;
}

bool Organism::hasMoved() {
    return moved;
}
