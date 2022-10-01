#ifndef _PERLIN_NOISE_H_
#define _PERLIN_NOISE_H_

typedef struct meta_data meta_data_t;
struct meta_data
{
    int octaves;
    double gain;
    double lacunarity;

    int seed;
    double frequency;
};

#endif
