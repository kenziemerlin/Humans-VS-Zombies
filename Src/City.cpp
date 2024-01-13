//
// Created by kenzi on 2023-12-10.
//
#include <vector>
#include "../Headers/City.h"
#include "../Headers/Organism.h"  // Include the header for the Organism class
#include "../Headers/GameSpecs.h"
#include "../Headers/Human.h"
#include "../Headers/Zombie.h"
#include <cstring>
#include <random>

#define GREEN_TEXT "\033[32m"
#define RED_TEXT "\033[31m"
#define RESET_COLOR "\033[0m"


default_random_engine generator;

City::City() {
    // Initialize the grid with nullptr
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            grid[i][j] = nullptr;
        }
    }
}


City::~City() {
    // Perform cleanup if needed
}

Organism* City::getOrganism(int x, int y) {
    // Add bounds checking if necessary
    return grid[y][x];
}

void City::setOrganism(Organism* organism, int x, int y) {
    // Add bounds checking if necessary
    grid[y][x] = organism;
}
void City::humansMove() {
    for(int x = 0; x < GRID_HEIGHT; x++) {
        for (int y = 0; y < GRID_WIDTH; y++) {
            Organism *temp = this->grid[x][y];
            if (temp != nullptr) {

                if (temp->getType() == HUMAN_CH && !temp->hasMoved()) {

                    int direction = rand() % 4;
                    bool moved = false;

                    if (direction == 0 && y > 0) {
                        Organism *temp2 = this->grid[x][y - 1];
                        if (temp2 == nullptr) {
                            this->grid[x][y - 1] = temp;
                            this->grid[x][y] = nullptr;
                            moved = true;

                        }
                    } else if (direction == 1 && y < GRID_WIDTH - 1) {
                        Organism *temp2 = this->grid[x][y + 1];
                        if (temp2 == nullptr) {
                            this->grid[x][y + 1] = temp;
                            this->grid[x][y] = nullptr;
                            moved = true;
                        }
                    } else if (direction == 2 && x > 0) {
                        Organism *temp2 = this->grid[x - 1][y];
                        if (temp2 == nullptr) {
                            this->grid[x - 1][y] = temp;
                            this->grid[x][y] = nullptr;
                            moved = true;
                        }
                    } else if (direction == 3 && x < GRID_HEIGHT - 1) {
                        Organism *temp2 = this->grid[x + 1][y];
                        if (temp2 == nullptr) {
                            this->grid[x + 1][y] = temp;
                            this->grid[x][y] = nullptr;
                            moved = true;
                        }
                    }
                    if (moved) {
                        temp->addStep();
                    }
                    temp->setMoved(true);
                }
            }
        }
    }
}


//chat gpt helped me through this function <3
void City::zombiesMoveEat() {
    for (int x = 0; x < GRID_HEIGHT; x++) {
        for (int y = 0; y < GRID_WIDTH; y++) {
            Organism *temp = this->grid[x][y];
            if (temp != nullptr && temp->getType() == ZOMBIE_CH && !temp->hasMoved()) {
                // Collect potential move locations
                std::vector<std::pair<int, int>> moveLocations;

                // Check if there is a human in any adjacent cell
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        int newX = x + i;
                        int newY = y + j;

                        // Check if the coordinates are within bounds
                        if (newX >= 0 && newX < GRID_HEIGHT && newY >= 0 && newY < GRID_WIDTH) {
                            Organism *neighbor = this->grid[newX][newY];
                            if (neighbor != nullptr && neighbor->getType() == HUMAN_CH) {
                                moveLocations.emplace_back(newX, newY);
                            }
                        }
                    }
                }

                // If there are human spots, choose a random one and eat the human
                if (!moveLocations.empty()) {
                    std::uniform_int_distribution<int> distribution(0, moveLocations.size() - 1);
                    int randomIndex = distribution(generator);

                    std::pair<int, int> chosenLocation = moveLocations[randomIndex];
                    this->grid[chosenLocation.first][chosenLocation.second] = temp;
                    this->grid[x][y] = nullptr;
                    temp->addStep();
                } else {
                    // If no human spots, move to a random empty spot
                    moveRandomEmpty(temp, x, y);
                    temp->addNoEat();
                }

                temp->setMoved(true);
            }
        }
    }
}

void City::moveRandomEmpty(Organism* organism, int x, int y) {
    // Collect empty spots
    std::vector<std::pair<int, int>> emptySpots;

    // Check all adjacent cells
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newX = x + i;
            int newY = y + j;

            // Check if the coordinates are within bounds
            if (newX >= 0 && newX < GRID_HEIGHT && newY >= 0 && newY < GRID_WIDTH) {
                if (this->grid[newX][newY] == nullptr) {
                    emptySpots.emplace_back(newX, newY);
                }
            }
        }
    }

    // If there are empty spots, choose a random one
    if (!emptySpots.empty()) {
        std::uniform_int_distribution<int> distribution(0, emptySpots.size() - 1);
        int randomIndex = distribution(generator);

        std::pair<int, int> chosenSpot = emptySpots[randomIndex];
        this->grid[chosenSpot.first][chosenSpot.second] = organism;
        this->grid[x][y] = nullptr;
        organism->addStep();
    }
}

void City::humansRecruit() {
    for (int x = 0; x < GRID_HEIGHT; x++) {
        for (int y = 0; y < GRID_WIDTH; y++) {
            Organism *temp = this->grid[x][y];
            if (temp != nullptr && temp->getType() == HUMAN_CH) {
                int steps = temp->getSteps();
                if ( steps == HUMAN_BREED) {
                    temp->resetSteps();
                    int existingHumanX = x;
                    int existingHumanY = y;

                    // Attempt to recruit a new human up to 4 times
                    for (int attempt = 0; attempt < 4; attempt++) {
                        int newX, newY;
                        switch (attempt) {
                            case 0:
                                newX = existingHumanX;
                                newY = existingHumanY - 1;
                                break;
                            case 1:
                                newX = existingHumanX;
                                newY = existingHumanY + 1;
                                break;
                            case 2:
                                newX = existingHumanX - 1;
                                newY = existingHumanY;
                                break;
                            case 3:
                                newX = existingHumanX + 1;
                                newY = existingHumanY;
                                break;
                            default:
                                continue;  // Invalid direction, try again
                        }

                        // Check if the new position is within bounds and unoccupied
                        if (newX >= 0 && newX < GRID_HEIGHT && newY >= 0 && newY < GRID_WIDTH &&
                            this->grid[newX][newY] == nullptr) {
                            //  new Human and place it in the grid
                            Human *newHuman = new Human;
                            this->grid[newX][newY] = newHuman;
                            break;  // Exit the loop after successful recruitment
                        }
                    }
                }
            }
        }
    }
}

void City::zombieDie(){
    for (int x = 0; x < GRID_HEIGHT; x++) {
        for (int y = 0; y < GRID_WIDTH; y++) {
            Organism *temp = this->grid[x][y];
            if (temp != nullptr) {
                if (temp->getType() == ZOMBIE_CH){
                    int eaten = temp->getNoEat();
                    if (eaten == ZOMBIE_STARVE) {
                        temp->resetNoEat();
                        delete temp;
                        this->grid[x][y] = nullptr;
                        Human *newHuman = new Human;
                        this->grid[x][y] = newHuman;
                    }
                }
            }
        }
    }
}

void City::zombieBreed(){
    for (int x = 0; x < GRID_HEIGHT; x++) {
        for (int y = 0; y < GRID_WIDTH; y++) {
            Organism *temp = this->grid[x][y];
            if (temp != nullptr && temp->getType() == ZOMBIE_CH) {
                int steps = temp->getSteps();
                if (steps == ZOMBIE_BREED || temp->hasMoved()) {
                    if (steps == ZOMBIE_BREED){
                        temp->resetSteps();
                    }

                    int existingHumanX = x;
                    int existingHumanY = y;

                    // Attempt to recruit a new zombie up to 8 times
                    for (int attempt = 0; attempt < 8; attempt++) {
                        int newX, newY;

                        switch (attempt) {
                            case 0:
                                newX = existingHumanX;
                                newY = existingHumanY - 1;
                                break;
                            case 1:
                                newX = existingHumanX;
                                newY = existingHumanY + 1;
                                break;
                            case 2:
                                newX = existingHumanX - 1;
                                newY = existingHumanY;
                                break;
                            case 3:
                                newX = existingHumanX + 1;
                                newY = existingHumanY;
                                break;
                            case 4:
                                newX = existingHumanX + 1;
                                newY = existingHumanY + 1;
                                break;
                            case 5:
                                newX = existingHumanX + 1;
                                newY = existingHumanY - 1;
                                break;
                            case 6:
                                newX = existingHumanX - 1;
                                newY = existingHumanY - 1;
                                break;
                            case 7:
                                newX = existingHumanX - 1;
                                newY = existingHumanY + 1;
                                break;
                            default:
                                continue;
                        }

                        // Check if the new position is within bounds and unoccupied
                        if (newX >= 0 && newX < GRID_HEIGHT && newY >= 0 && newY < GRID_WIDTH && this->grid[newX][newY]->getType() == HUMAN_CH) {
                            //new zombie and place it in the grid
                            Zombie *newZombie = new Zombie;
                            this->grid[newX][newY] = newZombie;
                            break;  // Exit the loop after successful recruitment
                        }
                    }
                }
            }
        }
    }
}

void City::reset() {
    for (int x = 0; x < GRID_HEIGHT; x++) {
        for (int y = 0; y < GRID_WIDTH; y++) {
            Organism* temp = this->grid[x][y];
            if (temp != nullptr) {
                temp->setMoved(false);
            }
        }
    }
}



ostream& operator<<(ostream& output, City& city) {
    city.humanCount = 0;
    city.zombieCount = 0;
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            Organism *temp = city.grid[i][j];
            if (temp == nullptr){
                output << SPACE_CH;
            }
            else if (temp->getType() == HUMAN_CH){
                output << GREEN_TEXT << HUMAN_CH << RESET_COLOR;
                city.humanCount++;
            }
            else if (temp->getType() == ZOMBIE_CH){
                output << RED_TEXT << ZOMBIE_CH << RESET_COLOR;
                city.zombieCount++;
            }
        }
        output << '\n';
    }
    output << "HUMAN COUNT: " << city.humanCount << endl;
    output << "ZOMBIE COUNT: " << city.zombieCount << endl;
    return output;
}

bool City::hasDiversity() const {
    return (humanCount != 0 && zombieCount != 0);
}
