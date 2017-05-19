#include "population.h"
/*
int main(void)
{
	float ** populations = read_population_file("pop.bin");

	// Test Denver, CO
	float denver_lat = 39.760032;
	float denver_long = -104.975970;
	float denver_population = get_population(denver_lat, denver_long, populations);
	printf("denver population = %lf\n", denver_population);

	// Test Chicago
	float chicago_lat = 41.882137;
	float chicago_long = -87.631382;
	float chicago_population = get_population(chicago_lat, chicago_long, populations);
	printf("chicago population = %lf\n", chicago_population);

	// Test Idaho Falls
	float mccammon_lat = 42.648856;
	float mccammon_long = -112.193871;
	float mccammon_population = get_population(mccammon_lat, mccammon_long, populations);
	printf("mccammon population = %lf\n", mccammon_population);

	// Test Lake Michigan
	float lake_michigan_lat = 42.541066;
	float lake_michigan_long =  -87.076482;
	float lake_michigan_population = get_population(lake_michigan_lat, lake_michigan_long, populations);
	printf("lake_michigan population = %lf\n", lake_michigan_population);

	return 0;
        }*/

float ** read_population_file( char * fname )
{
	int N_lat = 9240;
	int N_long = 20520;
	float ** populations = pop_allocate_matrix(N_lat, N_long);

	FILE * in = fopen(fname, "rb");

	size_t num_elements = N_lat * N_long;

	fread(populations[0], sizeof(float), num_elements, in);

	fclose(in);

	return populations;
}

void pop_dump_binary_file( float ** populations )
{
	FILE * out = fopen("pop.bin", "wb");

	int N_lat = 9240;
	int N_long = 20520;
	size_t num_elements = N_lat * N_long;

	fwrite(populations[0], sizeof(float), num_elements, out);

	fclose(out);
}

float ** pop_original_read_population_file(void)
{
	FILE * in =  fopen("pop.xyz", "r");

	int N_lat = 9240;
	int N_long = 20520;

	float ** populations = pop_allocate_matrix(N_lat, N_long);

	for( int i = 0; i < N_lat; i++ )
	{
		for( int j = 0; j < N_long; j++ )
		{
			// Read data from file
			float longitude, latitude;
			int population_type;
			fscanf(in, "%f\t%f\t%d\n", &longitude, &latitude, &population_type);

			// Store in array
			populations[N_lat-1-i][j] = population_type;
		}
	}

	fclose(in);

	return populations;
}



float ** pop_allocate_matrix(size_t m, size_t n)
{
	float * full = (float *)   calloc( m * n, sizeof( float  ));
	float ** M   = (float **)  calloc( m    , sizeof( float *));
	for( int i = 0; i < m; i++ )
		M[i] = &full[i*n];
	return M;
}

float get_population(float latitude, float longitude, float ** populations)
{
	float delta = 0.0083333333333;
	float long_min = -181.0;
	float lat_min = 7.0;
	int N_lat = 9240;
	int N_long = 20520;

	int lat_idx  = (latitude-lat_min) / delta;
	int long_idx = (longitude-long_min) / delta;

	assert(lat_idx >= 0 && lat_idx < N_lat );
	assert(long_idx >= 0 && long_idx < N_long );

	return populations[lat_idx][long_idx];
}

float ** pop_olde_read_population_file(void)
{
	FILE * in =  fopen("pop.asc", "r");

	int N_lat = 9240;
	int N_long = 20520;

	float ** populations = pop_allocate_matrix(N_lat, N_long);

	float max = -10000;
	int idx = 0;
	for( int i = 0; i < N_lat; i++ )
	{
		for( int j = 0; j < N_long; j++ )
		{
			// Read data from file
			float population;
			fscanf(in, "%f", &population);

			// Store in array
			populations[N_lat-1-i][j] = population;
			if( population > max )
				max = population;
			//populations[N_lat-1-i][N_long-1-j] = population;
		}
	}
	printf("max population = %f\n", max);

	fclose(in);

	return populations;
}

/*
void see_population( float ** populations )
{
	FILE * fp = fopen("view.dat", "w");
	float delta = 0.0083333333333;
	float long_min = -180.0;
	float lat_min = -60.0;
	int N_lat = 9240;
	int N_long = 20520;

	for( int i = 0; i < 174; i++ )
	{
		float y = lat_min + delta/2.0 + delta*i;
		for( int j = 0; j < 432; j++ )
		{
			float x = long_min + delta/2.0 + delta*i;
			float pop = get_population(y, x, populations);
			fprintf(fp,"%f ", pop);
		}
		fprintf(fp,"\n");
	}
}
*/
