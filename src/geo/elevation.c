#include "elevation.h"

int main(void)
{
	float ** elevations = read_elevation_file();

	// Test Denver, CO
	float denver_lat = 39.760032;	
	float denver_long = -104.975970;
	float denver_elevation = get_elevation(denver_lat, denver_long, elevations);
	printf("denver elevation = %lf\n", denver_elevation);

	// Test Chicago
	float chicago_lat = 41.886578;	
	float chicago_long = -87.729444;
	float chicago_elevation = get_elevation(chicago_lat, chicago_long, elevations);
	printf("chicago elevation = %lf\n", chicago_elevation);

	return 0;
}

float ** allocate_matrix(size_t m, size_t n)
{
	float * full = (float *)   calloc( m * n, sizeof( float  ));
	float ** M   = (float **)  calloc( m    , sizeof( float *));
	for( int i = 0; i < m; i++ )
		M[i] = &full[i*n];
	return M;
}

float get_elevation(float latitude, float longitude, float ** elevations)
{
	float delta = 0.01666666667;
	float long_min = -130.350000000000023;
	float long_max = -59.0666666666666487;
	float lat_min = 21.899999999999995;
	float lat_max = 50.9833333333333272;
	int N_lat = 1746;
	int N_long = 4278;

	int lat_idx  = (latitude-lat_min) / delta;
	int long_idx = (longitude-long_min) / delta;

	assert(lat_idx >= 0 && lat_idx < N_lat );
	assert(long_idx >= 0 && long_idx < N_long );

	return elevations[lat_idx][long_idx];
}

float ** read_elevation_file(void)
{
	FILE * in =  fopen("etopo1.xyz", "r");

	int N_lat = 1746;
	int N_long = 4278;

	float ** elevations = allocate_matrix(N_lat, N_long);

	int idx = 0;
	for( int i = 0; i < N_lat; i++ )
	{
		for( int j = 0; j < N_long; j++ )
		{
			// Read data from file
			float longitude, latitude, elevation;
			fscanf(in, "%f\t%f\t%f\n", &longitude, &latitude, &elevation);

			// Store in array
			elevations[N_lat-1-i][j] = elevation;
		}
	}

	fclose(in);

	return elevations;
}

