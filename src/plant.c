#include "plant.h"

PLANT plants[] = {
    {"Rose", 20.0, 30.0, 200.0},
    {"Tulip", 15.0, 30.0, 150.0},
    {"Sunflower", 25.0, 30.0, 250.0}
};

int plant_count = sizeof(plants) / sizeof(plants[0]);
int plant_index = 0;
int plant_quantity = 0;
