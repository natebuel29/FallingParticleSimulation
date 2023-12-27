#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Simulation.h"

int main(int argc, char* args[]){
    Simulation sim = Simulation(925, 500);
    sim.simulate();

    return 0;
}