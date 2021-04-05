#include "file.h"
#include "scene.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFromFile(Planet* planets, FILE* fp){
    char buff[1000];
    int row_count = 0;
    int field_count = 0;
    int i = 0;

    while(fgets(buff, 1000, fp)){
        field_count = 0;
        row_count++;
        if(row_count == 1){
            continue;
        }

        char* field = strtok(buff, ",");
        char str[10];
        while(field){
            if(field_count == 0){
                strcpy(str, field);
                planets[i].radius = atof(str);
            }
            if(field_count == 1){
                strcpy(str, field);
                planets[i].distance = atof(str);
            }
            if(field_count == 2){
                strcpy(str, field);
                planets[i].orbit_speed = atof(str);
            }
            if(field_count == 3){
                strcpy(str, field);
                planets[i].orbit = atof(str);
            }
            if(field_count == 4){
                strcpy(str, field);
                planets[i].rotation_speed = atof(str);
            }
            if(field_count == 5){
                strcpy(str, field);
                planets[i].rotation = atof(str);
            }
            if(field_count == 6){
                strcpy(str, field);
                planets[i].axis_tilt = atof(str);
            }

            field = strtok(NULL, ",");
            field_count++;

        }
        i++;

    }
}
