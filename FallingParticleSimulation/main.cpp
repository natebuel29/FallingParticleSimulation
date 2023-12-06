#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Simulation.h"

int main(int argc, char* args[]){
    Simulation sim = Simulation(1024, 480);
    sim.simulate();

    return 0;
}