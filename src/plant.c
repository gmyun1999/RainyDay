#include "plant.h"

PLANT plants[] = {
    {"Rose", 20.0, 60.0, 1.0, 200.0},
    {"Tulip", 15.0, 55.0, 0.8, 150.0},
    {"Sunflower", 25.0, 70.0, 1.5, 250.0},
    {"Daisy", 18.0, 50.0, 0.6, 100.0}
};

int plant_count = sizeof(plants) / sizeof(plants[0]);
int plant_index = 0;
int plant_quantity = 0;
