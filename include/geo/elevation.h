#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

float ** allocate_matrix(size_t m, size_t n);
float ** read_elevation_file(char * filename);
float get_elevation(float latitude, float longitude, float ** elevations);
