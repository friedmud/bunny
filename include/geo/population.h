#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#ifdef __cplusplus
extern "C"
{
#endif
float get_population(float latitude, float longitude, float ** populations);
float ** read_population_file( char * fname );

float ** pop_allocate_matrix(size_t m, size_t n);
void pop_dump_binary_file( float ** populations );
float ** pop_original_read_population_file(void);
float ** pop_olde_read_population_file(void);
#ifdef __cplusplus
}
#endif
