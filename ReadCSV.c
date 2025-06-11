#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ReadCSV.h"

#define MAX_FIELD_LENGTH 100

void ReadCSV_dm(const char* FILE_NAME, CSV_MAPd* map) {
	FILE *file = fopen(FILE_NAME, "r");
	if (!file) { perror("Error opening file"); return; }
	
	char *line = NULL;
	size_t line_length= 0;
	int read;

	map->k = NULL;
	map->v = NULL;
	map->l = 0;

	size_t index = 0;

	while ((read = getline(&line, &line_length, file)) != -1) {
		double value;
		char key[MAX_FIELD_LENGTH];
		if (sscanf(line, "%99[^,],%lf", key, &value) == 2) {
			char** temp_k = (char**)realloc(map->k, sizeof(char*) * (index+1));
			double* temp_v = (double*)realloc(map->v, sizeof(double) * (index+1));
			
			if (!temp_k || !temp_v) {
				perror("Reallocation error");
				Free_CSV_MAPd(map);
				
				for (size_t i=0; i<index; ++i) {
					free(map->k[i]);
				}
				free(map->k);
				free(map->v);

				free(line);
				fclose(file);
				return;
			}

			map->k = temp_k;
			map->v = temp_v;

			map->k[index] = strdup(key);
			map->v[index] = value;
			index++;
		}
	}

	map->l = index;
	free(line);
	fclose(file);
}

int MapSearch_CSV (const char* term, CSV_MAPd* map) {
	for (size_t i=0; i<map->l; ++i) if (!strcmp(map->k[i],term)) return i;
	printf("N/A\n");
	return -1; // Sentinel
}

void Free_CSV_MAPd(CSV_MAPd* map) {
	if (!map->k || !map->v) return;

	for (size_t i=0; i<map->l; ++i) {
		free(map->k[i]);
	}
	free(map->k);
	free(map->v);
}
