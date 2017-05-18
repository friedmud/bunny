#include "land.h"
/* Key:
 * 1  - Broadleaf Evergreen Forest
 * 2  - Broadleaf Deciduous Forest
 * 3  - Needleleaf Evergreen Forest
 * 4  - Needleleaf Deciduous Forest
 * 5  - Mixed Forest
 * 6  - Tree Open
 * 7  - Shrub
 * 8  - Herbaceous
 * 9  - Herbaceous with Sparse Tree/Shrub
 * 10 - Sparse vegetation
 * 11 - Cropland
 * 12 - Paddy field
 * 13 - Cropland / Other Vegetation Mosaic
 * 14 - Mangrove
 * 15 - Wetland
 * 16 - Bare area,consolidated(gravel,rock)
 * 17 - Bare area,unconsolidated (sand)
 * 18 - Urban
 * 19 - Snow / Ice 
 * 20 - Water bodies
 */

int main(void)
{
	short ** land_types = read_land_file();

	// Test Denver, CO
	float denver_lat = 39.760032;	
	float denver_long = -104.975970;
	short denver_land_type = get_land_type(denver_lat, denver_long, land_types);
	printf("denver land_type = %d\n", denver_land_type);

	free(land_types[0]);
	free(land_types);

	return 0;
}

short ** allocate_short_matrix(size_t m, size_t n)
{
	short * full = (short *)   calloc( m * n, sizeof( short  ));
	short ** M   = (short **)  calloc( m    , sizeof( short *));
	for( int i = 0; i < m; i++ )
		M[i] = &full[i*n];
	return M;
}

float get_land_type(float latitude, float longitude, short ** land_types)
{
	float delta = 0.0041666667;
	float long_min = -180;
	float long_max = -0;
	float lat_min = 0;
	float lat_max = 90;;
	int N_lat = 21600;
	int N_long = 43200;

	int lat_idx  = (latitude-lat_min) / delta;
	int long_idx = (longitude-long_min) / delta;

	assert(lat_idx >= 0 && lat_idx < N_lat );
	assert(long_idx >= 0 && long_idx < N_long );

	return land_types[lat_idx][long_idx];
}

short ** read_land_file( void )
{
	int N_lat = 21600;
	int N_long = 43200;
	short ** land_types = allocate_short_matrix(N_lat, N_long);

	FILE * in = fopen("lc.bin", "rb");

	size_t num_elements = N_lat * N_long;

	fread(land_types[0], sizeof(short), num_elements, in);

	fclose(in);

	return land_types;
}

void dump_binary_file( short ** land_types )
{
	FILE * out = fopen("lc.bin", "wb");

	int N_lat = 21600;
	int N_long = 43200;
	size_t num_elements = N_lat * N_long;

	fwrite(land_types[0], sizeof(short), num_elements, out);

	fclose(out);
}

short ** original_read_land_file(void)
{
	FILE * in =  fopen("lc.xyz", "r");

	int N_lat = 21600;
	int N_long = 43200;

	short ** land_types = allocate_short_matrix(N_lat, N_long);

	for( int i = 0; i < N_lat; i++ )
	{
		for( int j = 0; j < N_long; j++ )
		{
			// Read data from file
			float longitude, latitude;
			int land_type;
			fscanf(in, "%f\t%f\t%d\n", &longitude, &latitude, &land_type);

			// Store in array
			land_types[N_lat-1-i][j] = land_type;
		}
	}

	fclose(in);

	return land_types;
}

