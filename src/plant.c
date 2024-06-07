#include "plant.h"

PLANT plants[] = {
    {"tomato", 60.0, 150.0, 200.0},
    {"Lettuce", 80.0, 150.0, 150.0},
    {"apple_mint", 40.0, 150.0, 250.0}
};

int plant_count = sizeof(plants) / sizeof(plants[0]);
int plant_index = 0;
int plant_quantity = 0;
