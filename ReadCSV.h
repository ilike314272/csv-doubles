#ifndef CSV_MAPD_H
#define CSV_MAPD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELD_LENGTH 100

typedef struct {
    char** k;  // Array of keys
    double* v;  // Array of values
    size_t l;  // Number of entries
} CSV_MAPd;

void ReadCSV_dm(const char* FILE_NAME, CSV_MAPd* map);
int MapSearch_CSV(const char* term, CSV_MAPd* map);
void Free_CSV_MAPd(CSV_MAPd* map);

#endif 
