cmake_minimum_required(VERSION 3.26)
project(HumansVsZombies)

set(CMAKE_CXX_STANDARD 23)

add_executable(HumansVsZombies main.cpp
        Src/Human.cpp
        Src/Organism.cpp
        Src/City.cpp
        Src/Zombie.cpp)
