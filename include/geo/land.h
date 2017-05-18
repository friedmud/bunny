#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#ifdef __cplusplus
extern "C"
{
#endif

float get_land_type(float latitude, float longitude, short ** land_types);
short ** read_land_file( char * filename );

short ** allocate_short_matrix(size_t m, size_t n);
void dump_binary_file( short ** land_types );
short ** original_read_land_file(char * filename);
#ifdef __cplusplus
}
#endif
