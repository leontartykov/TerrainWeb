#ifndef _PERLIN_ORIGINAL_H_
#define _PERLIN_ORIGINAL_H_

#include <iterator>
#include <algorithm>
#include <random>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "../base_noise.h"
#include "perlin_noise_struct.h"

class PerlinNoise: BaseNoise
{
    private:
        unsigned char _p[512];
        unsigned int _seed;

        double fade(double t);
        double lerp(double t, double a, double b);
        double map(double value, double old_min, double old_max, double new_min, double new_max);
        double gradient(int hash, double x, double y, double z);

    public:
        PerlinNoise(unsigned int seed);
        ~PerlinNoise();
        void reseed(unsigned int seed);

        double noise2D(double x, double y);
        double accumulatedNoise2D(double x, double y, meta_data_t &meta_data);
};

#endif
