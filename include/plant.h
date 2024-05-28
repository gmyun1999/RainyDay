#ifndef PLANT_H
#define PLANT_H

typedef struct plant {
    char* name;
    float temperature;
    float humidity;
    float water_amount;
    float light_intensity;
} PLANT;

extern PLANT plants[];
extern int plant_count;
extern int plant_index;
extern int plant_quantity;

#endif // PLANT_H
